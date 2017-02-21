/**
 * @file  websocket.cpp
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
#include <QCryptographicHash>
#include "websocket.h"

/**
 * @brief Default constructor
 *
 */
WebSocket::WebSocket(httpConnection *conn)
{
    mSocket = 0;
    if (conn)
        loadConnection(conn);
}

/**
 * @brief Opening handshake (see RFC6455 chap 1.3)
 *
 * @param conn Pointer to the HTTP connection to switch into WS
 */
void WebSocket::handshake(httpConnection *conn)
{
    // Sanity check
    if (conn == 0)
        return;

    QByteArray wsKey;
    wsKey.append( conn->getHeader("Sec-WebSocket-Key") );
    // Append the Magic GUID to received Key
    wsKey.append("258EAFA5-E914-47DA-95CA-C5AB0DC85B11");
    // Hash the key using SHA1
    QByteArray hash = QCryptographicHash::hash(wsKey, QCryptographicHash::Sha1);
    // Convert the result hash into Base64 string
    QString acceptKey = hash.toBase64();

    httpResponse *response = conn->getResponse();
    response->setStatusCode(101);
    response->setContentType("");
    response->insertHeader("Server",     "CF71");
    response->insertHeader("Upgrade",    "websocket");
    response->insertHeader("Connection", "Upgrade");
    response->insertHeader("Sec-WebSocket-Accept", acceptKey);
    response->insertHeader("Date", "Thu, 23 Feb 2017 23:20:29 GMT");
    // Send response
    response->send( mSocket );
}

/**
 * @brief Set the HTTP connection to use for WebSocket
 *
 * @param conn Pointer to a connected HTTP connection
 */
void WebSocket::loadConnection(httpConnection *conn)
{
    if (conn == 0)
        return;

    mSocket = conn->getSocket();
    connect(mSocket, SIGNAL(readyRead()), this, SLOT(receive()));
    conn->setSocket(0);

    handshake(conn);
}

/**
 * @brief Slot called when data are received on socket
 *
 */
void WebSocket::receive()
{
    qWarning() << "WebSocket::receive()";
    if (mSocket == 0)
        return;
}
