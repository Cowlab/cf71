/**
 * @file  httpconnection.cpp
 * @brief Handle one HTTP connection between server and client
 *
 * @author Saint-Genest Gwenael <gwen@cowlab.fr>
 * @copyright Cowlab (c) 2017
 *
 * @par Warning
 * CF71 is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License
 * version 3 as published by the Free Software Foundation. You
 * should have received a copy of the GNU Lesser General Public
 * License along with this program, see LICENSE file for more details.
 * This program is distributed WITHOUT ANY WARRANTY see README file.
 */
#include "httpconnection.h"
#include "httpresponse.h"
#include <QDebug>

/**
 * @brief Default constructor
 * @param socket Pointer to a connected QTcpSocket
 *
 */
httpConnection::httpConnection(QObject *parent) : QObject(parent)
{
    mSocket = 0;
    mState  = REQ_LINE;
    mMethod = UNKNOWN;
    mResponse = 0;
}

/**
 * @brief Default destructor
 *
 */
httpConnection::~httpConnection()
{
    if (mResponse)
    {
        delete mResponse;
        mResponse = 0;
    }
}

/**
 * @brief Debug the received header (dump to console)
 *
 */
void httpConnection::dumpHeader()
{
    qWarning() << "== httpConnection::dumpHeader ==";

    QMapIterator<QString, QString> i(mHeaders);
    while (i.hasNext())
    {
        i.next();
        qWarning() << " -" << i.key() << "=>" << i.value();
    }
}

/**
 * @brief httpConnection::getHeader
 *
 * @param key Name of the header entry to find
 * @return QString Value for the header entry
 */
const QString httpConnection::getHeader(const QString &key)
{
    if ( ! mHeaders.contains(key) )
        return QString();

    return mHeaders.value(key);
}

/**
 * @brief Get value of query argument, identified by his name
 *
 * @param name Name of the argument to find
 * @return QString Value of the query argument
 */
const QString httpConnection::getQueryArg(const QString &name)
{
    if ( ! mQueryArgs.contains(name) )
        return QString();

    return mQueryArgs.value(name);
}

/**
 * @brief Get the response object for this connection
 *
 * @return Pointer to the response object for connection
 */
httpResponse *httpConnection::getResponse(void)
{
    // If no response object available
    if (mResponse == 0)
        // Allocate a new response
        mResponse = new httpResponse();

    return mResponse;
}

/**
 * @brief  Get the URI of the request
 * @return String
 *
 */
const QString & httpConnection::getUri(void)
{
    return mUri;
}

/**
 * @brief Slot called when data are received on socket
 *
 */
void httpConnection::receive()
{
    if (mSocket == 0)
        return;

    try {
        while (mSocket->bytesAvailable())
        {
            switch (mState)
            {
            case REQ_LINE:   recvReqFirst();  break;
            case REQ_HEADER: recvReqHeader(); break;
            default:
                return;
            }
        }
    } catch (...) {
        qWarning() << "httpConnection::receive() EXCEPTION";
        mState = REQ_ERROR;
    }
}

/**
 * @brief Receive and process the first line of a request
 *
 */
void httpConnection::recvReqFirst()
{
    if (mSocket == 0)
        return;

    int rxLen = mSocket->bytesAvailable();
    QByteArray line = mSocket->readLine(rxLen + 1).trimmed();
    if (line.size() == 0)
        return;
    line = line.trimmed();

    QList<QByteArray> fields = line.split(' ');
    if (fields.size() != 3)
        throw -2;
    // Decode requested method
    QString method = fields.at(0);
    if (method == "GET")
        mMethod = GET;
    else if (method == "POST")
        mMethod = POST;
    else if (method == "PUT")
        mMethod = PUT;
    else if (method == "HEAD")
        mMethod = HEAD;
    else if (method == "OPTION")
        mMethod = OPTIONS;
    else
        throw -3;

    QString uri = fields.at(1);
    int sep = uri.indexOf('?');
    if (sep >= 0)
    {
        // Get the query string ...
        QString queryString = uri.mid(sep + 1);
        // ... and remove it after URI
        uri.truncate(sep);

        // Decode query string and extract arguments
        QStringList args = queryString.split('&');
        for (int i = 0; i < args.size(); ++i)
        {
            QString arg = args.at(i);
            // Search the name/value separator ('=')
            int argSep = arg.indexOf('=');
            if (argSep <= 0)
                continue;
            // Extract argument name and value
            QString argName  = arg.left(argSep);
            QString argValue = arg.mid(argSep + 1);
            // Save argument
            mQueryArgs.insert(argName, argValue);
        }
    }
    mUri = uri;

    mState = REQ_HEADER;
}

/**
 * @brief Receive and process header lines of a request
 *
 */
void httpConnection::recvReqHeader()
{
    if (mSocket == 0)
        return;

    int rxLen = mSocket->bytesAvailable();
    while(rxLen > 0)
    {
        QByteArray ln = mSocket->readLine(rxLen + 1);
        int lineLen = ln.size();
        if (lineLen == 0)
            break;
        // If line is empty, this is the header/body separator
        if (ln == "\r\n")
        {
            mState = REQ_BODY;
            emit headerReceived();
            break;
        }
        ln = ln.trimmed();

        int sep = ln.indexOf(':');
        if (sep > 0)
        {
            QString headerKey = ln.left(sep);
            QString headerValue = ln.mid(sep + 1).trimmed();
            if (mHeaders.contains(headerKey))
                mHeaders.remove(headerKey);
            mHeaders.insert(headerKey, headerValue);
        }
        else
            qWarning() << "RX: unknown strange line " << ln;
        rxLen -= lineLen;
    }
}

/**
 * @brief Send the response for the current connection
 *
 */
void httpConnection::sendResponse(void)
{
    if (mSocket == 0)
        return;

    httpResponse *rsp = getResponse();

    if (rsp == 0) {
        qWarning() << "httpConnection::sendResponse() No Response !";
        return;
    }

    rsp->send( mSocket );

    mSocket->close();
}

/**
 * @brief Set the client socket for this connection
 * @param socket Pointer to the QSocket connected with the client
 */
void httpConnection::setSocket(QTcpSocket *socket)
{
    mSocket = socket;
    connect(mSocket, SIGNAL(readyRead()), this, SLOT(receive()));
}
