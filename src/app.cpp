/**
 * @file  app.cpp
 * @brief Bridge to manage a probe using websocket
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
#include <QAction>
#include <QApplication>
#include <QMenu>
#include <QSystemTrayIcon>
#include "app.h"
#include "httpserver.h"

/**
 * @brief Default constructor
 * @param parent Pointer to the parent object
 *
 */
App::App(QObject *parent) : QObject(parent)
{
    mServer = 0;
}

/**
 * @brief Init and start CF21 app
 *
 */
void App::start(void)
{
    // Create a new web server
    mServer = new httpServer(this);
}
/* EOF */
