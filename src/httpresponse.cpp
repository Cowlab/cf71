/**
 * @file  httpresponse.cpp
 * @brief Class to handle a response to an HTTP request
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
#include <QString>
#include <QTcpSocket>
#include "httpcontent.h"
#include "httpresponse.h"

/**
 * @brief Default constructor
 *
 */
httpResponse::httpResponse()
{
    mRetCode = 404;
    mContent = 0;
    mContentType = "text/plain";
}

/**
 * @brief Default destructor
 *
 */
httpResponse::~httpResponse()
{
    if (mContent)
    {
        delete mContent;
        mContent = 0;
    }
}

/**
 * @brief Get the content for this response
 *
 * @return httpContent* Pointer to to current
 */
httpContent *httpResponse::getContent(void)
{
    return mContent;
}

/**
 * @brief Send the response to the remote client
 *
 * @param sock Pointer to the socket connected to the client
 */
void httpResponse::send(QTcpSocket *sock)
{
    QByteArray rspBuffer;

    QString reason;
    if (mRetCode == 200)      reason = "OK";
    else if (mRetCode == 403) reason = "Forbidden";
    else if (mRetCode == 404) reason = "Not Found";
    QString statusLine = QString("HTTP/1.1 %1 %2\r\n").arg(mRetCode).arg(reason);
    rspBuffer.append(statusLine);

    QString headerLine;
    headerLine = QString("Content-type: %1\r\n").arg(mContentType);
    rspBuffer.append(headerLine);
    // Append an empty line to finish the header
    rspBuffer.append("\r\n");

    // Send response header to remote
    sock->write(rspBuffer);

    if (mContent)
    {
        const QByteArray &data = mContent->getData();
        sock->write(data);
    }
}

/**
 * @brief Set the content of this response
 *
 * @param content Pointer to the httpContent to use as response
 */
void httpResponse::setContent(httpContent *content)
{
    // If another content has previously been set ... remove it
    if (mContent)
        delete mContent;
    // Save the specified content
    mContent = content;
}

/**
 * @brief Set the MIME type of the response content
 *
 * @param type String of the content MIME type
 */
void httpResponse::setContentType(const QString &type)
{
    mContentType = type;
}

/**
 * @brief Set the result code of the response
 *
 * @param code Integer, result code
 */
void httpResponse::setStatusCode(int code)
{
    mRetCode = code;
}
