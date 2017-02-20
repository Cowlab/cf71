/**
 * @file  httpconnection.h
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
#ifndef HTTPCONNECTION_H
#define HTTPCONNECTION_H

#include <QMap>
#include <QTcpSocket>
#include "httpresponse.h"

/**
 * @class httpConnection
 * @brief Handle one HTTP connection between server and client
 *
 */
class httpConnection : public QObject
{
    Q_OBJECT
public:
    enum recvState {REQ_NONE, REQ_LINE, REQ_HEADER, REQ_BODY, REQ_ERROR};
    enum METHOD   {UNKNOWN, GET, POST, PUT, HEAD, OPTIONS};
public:
    explicit httpConnection(QObject *parent = 0);
    ~httpConnection();
    void dumpHeader();
    const QString   getHeader(const QString &key);
    const QString   getQueryArg(const QString &name);
    httpResponse   *getResponse(void);
    QTcpSocket     *getSocket(void);
    const QString & getUri(void);
    void  sendResponse(void);
    void  setSocket(QTcpSocket *socket);
signals:
    void headerReceived();
    void sendComplete();
private slots:
    void receive();
    void written(qint64 len);
protected:
    void recvReqFirst();
    void recvReqHeader();
private:
    recvState   mState;
    METHOD      mMethod;
    QTcpSocket *mSocket;
    QString     mUri;
    httpResponse *mResponse;
    QMap<QString,QString> mHeaders;
    QMap<QString,QString> mQueryArgs;
};

#endif // HTTPCONNECTION_H
