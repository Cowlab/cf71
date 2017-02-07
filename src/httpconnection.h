/**
 * @file  httpconnection.h
 * @brief Handle one HTTP connection between server and client
 *
 * @author Saint-Genest Gwenael <gwen@hooligan0.net>
 * @copyright Cowlab (c) 2017
 *
 * @par Warning
 * CF21 is free software: you can redistribute it and/or modify
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
    explicit httpConnection(QTcpSocket *socket);
    void dumpHeader();
    void dummyResponse(void);
    const QString & getUri(void);
signals:
    void headerReceived();
private slots:
    void receive();
protected:
    void recvReqFirst();
    void recvReqHeader();
private:
    recvState   mState;
    METHOD      mMethod;
    QTcpSocket *mSocket;
    QString     mUri;
    QMap<QString,QString> mHeaders;
    QMap<QString,QString> mQueryArgs;
};

#endif // HTTPCONNECTION_H
