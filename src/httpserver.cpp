/**
 * @file  httpserver.cpp
 * @brief Network layer of HTTP web server
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
#include <QDebug>
#include <QNetworkInterface>
#include <QTcpSocket>
#include "httpserver.h"
#include "httpconnection.h"
#include "httpcontent.h"
#include "httpresponse.h"
#include "page.h"
#include "pagestatic.h"
#include "pageusb.h"

/**
 * @brief Default constructor
 * @param parent Pointer to the parent QObject
 */
httpServer::httpServer(QObject *parent) : QTcpServer(parent)
{
    bool result = listen(QHostAddress::LocalHost, 6144);
    if (result != true)
        throw -1;

    connect(this, SIGNAL(newConnection()), this, SLOT(req()));
}

/**
 * @brief Slot called when receive a new connection request
 *
 */
void httpServer::req(void)
{
    QTcpSocket *clientSocket = nextPendingConnection();
    if (clientSocket == 0)
    {
        qWarning() << "httpSocket nextPendingConnection fails";
        return;
    }

    // Create a new httpConnection to handle the newly connected client
    httpConnection *client = new httpConnection(this);
    client->setSocket(clientSocket);
    connect(client, SIGNAL(headerReceived()),
            this,   SLOT  (reqHeadComplete()));
}

/**
 * @brief Slot called when the header of a request has been fully received
 *
 */
void httpServer::reqHeadComplete()
{
    // Search the sender of the received signal
    QObject *sender = QObject::sender();
    if (sender == 0)
        return;
    httpConnection *client = qobject_cast<httpConnection *>(sender);
    if (client == 0)
    {
        qWarning() << "httpServer:reqHeadComplete() not an httpConnection";
        return;
    }

#ifdef QT_DEBUG
    qWarning() << "Requested URI " << client->getUri();
#endif

    Page *pg = 0;
    if (client->getUri() == "/")
        pg = new PageStatic("index.html");
    else if (client->getUri().left(4).toLower() == "/usb")
        pg = new PageUsb();
    else if (client->getUri().left(5).toLower() == "/css/")
        pg = new PageStatic(client->getUri().mid(5));
    else if (client->getUri().left(4).toLower() == "/js/")
        pg = new PageStatic(client->getUri().mid(4));
    else
        pg = new Page();

    if (pg)
    {
        pg->setConnection(client);
        pg->process();
    }

    client->sendResponse();

    delete pg;
}
