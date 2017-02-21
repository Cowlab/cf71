/**
 * @file  websocket.h
 * @brief Communication interface using WebSocket protocol
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
#ifndef WEBSOCKET_H
#define WEBSOCKET_H

#include <QObject>
#include <QTcpSocket>
#include "httpconnection.h"

/**
 * @class WebSocket
 * @brief This class implement a communication layer through a websocket
 *
 */
class WebSocket : public QObject
{
    Q_OBJECT
public:
    WebSocket(httpConnection *conn = 0);
    void loadConnection(httpConnection *conn);
private slots:
    void receive();
protected:
    void handshake(httpConnection *conn);
private:
    QTcpSocket *mSocket;
};

#endif // WEBSOCKET_H
