/**
 * @file  httpserver.h
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
#ifndef HTTPSERVER_H
#define HTTPSERVER_H

#include <QMap>
#include <QTcpServer>

/**
 * @class httpServer
 * @brief The httpServer class
 */
class httpServer : public QTcpServer
{
    Q_OBJECT
public:
    explicit httpServer(QObject *parent = 0);

private slots:
    void req(void);
    void reqHeadComplete();
};

#endif // HTTPSERVER_H
