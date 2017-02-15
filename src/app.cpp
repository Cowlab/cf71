/**
 * @file  app.cpp
 * @brief Bridge to manage a probe using websocket
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
#include <QAction>
#include <QApplication>
#include <QMenu>
#include <QSettings>
#include <QSystemTrayIcon>
#include "app.h"
#include "httpserver.h"
#include "window.h"

/**
 * @brief Default constructor
 * @param parent Pointer to the parent object
 *
 */
App::App(QObject *parent) : QObject(parent)
{
    mServer = 0;

    QSettings config;
    if ( ! config.contains("http_port") )
        config.setValue("http_port", QVariant((int)6144));
    if ( ! config.contains("use_systray") )
        config.setValue("use_systray", QVariant((bool)true));
}

/**
 * @brief Initialize system tray icon
 *
 */
void App::initSystray(void)
{
    QMenu *trayMenu = new QMenu();
    // Create and insert "Quit" menu entry
    QAction *act = new QAction(tr("&Quit"), this);
    connect(act, SIGNAL(triggered()), qApp, SLOT(quit()));
    trayMenu->addAction(act);

    // Load icon file
    QIcon icon = QIcon(":/icon.png");

    // Create and load tray icon
    QSystemTrayIcon *tray = new QSystemTrayIcon(this);
    tray->setContextMenu(trayMenu);
    tray->setIcon(icon);
    tray->show();
}

/**
 * @brief Init and start CF21 app
 *
 */
void App::start(void)
{
    // Create a new web server
    mServer = new httpServer(this);

    QSettings config;
    if (config.value("use_systray").toBool() == true)
        initSystray();
}
/* EOF */
