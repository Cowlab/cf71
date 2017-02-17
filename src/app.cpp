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

/**
 * @brief Default constructor
 * @param parent Pointer to the parent object
 *
 */
App::App(QObject *parent) : QObject(parent)
{
    mServer  = 0;
    mWindow  = 0;
    mSystray = 0;
    mUseSystray = false;

    QSettings config;
    if ( ! config.contains("http_port") )
        config.setValue("http_port", QVariant((int)6144));
    if ( ! config.contains("use_systray") )
        config.setValue("use_systray", QVariant((bool)true));
}

/**
 * @brief Slot called when the main window is closed
 *
 */
void App::dialogClosed()
{
    // Sanity check
    if (mWindow == 0)
        return;

    // Delete the window
    delete mWindow;
    mWindow = 0;

    // If the app does not use systray ...
    if ( ! mUseSystray)
    {
        // ... the finish the app itself
        qApp->quit();
    }
}

/**
 * @brief Initialize system tray icon
 *
 */
void App::initSystray(void)
{
    QMenu *trayMenu = new QMenu();
    // Create and insert "Open" menu entry
    QAction *actOpen = new QAction(tr("&Open"), this);
    connect(actOpen, SIGNAL(triggered()), this, SLOT(openDialog()));
    trayMenu->addAction(actOpen);
    // Create and insert "Quit" menu entry
    QAction *act = new QAction(tr("&Quit"), this);
    connect(act, SIGNAL(triggered()), qApp, SLOT(quit()));
    trayMenu->addAction(act);

    // Load icon file
    QIcon icon = QIcon(":/icon.png");

    // Create and load tray icon
    mSystray = new QSystemTrayIcon(this);
    mSystray->setContextMenu(trayMenu);
    mSystray->setIcon(icon);
    mSystray->show();
}

/**
 * @brief Get the current status of HTTP server
 *
 * @return boolean Server status (True if started)
 */
bool App::isServerStarted(void)
{
    return mServer->isStarted();
}

/**
 * @brief Open the main window
 *
 */
void App::openDialog(void)
{
    // If the main window is already open
    if (mWindow)
    {
        // Set focus to the window
        mWindow->setFocus();
        return;
    }
    // Create and display the main window
    mWindow = new window(0, this);
    connect(mWindow, SIGNAL(closed()),            this, SLOT(dialogClosed()));
    connect(mWindow, SIGNAL(updateSystray(bool)), this, SLOT(systrayUpdate(bool)));
    mWindow->show();
}

/**
 * @brief Init and start CF71 app
 *
 */
void App::start(void)
{
    startServer();

    QSettings config;
    if (config.value("use_systray").toBool() == true)
    {
        initSystray();
        mUseSystray = true;
    }
    else
        openDialog();
}

/**
 * @brief Start the HTTP server
 *
 * @return boolean Server status (True if started)
 */
bool App::startServer(void)
{
    // Create a new web server
    if (mServer == 0)
        mServer = new httpServer(this);

    return mServer->start();
}

/**
 * @brief Stop the HTTP server
 *
 * @return boolean Server status (False if stopped)
 */
bool App::stopServer(void)
{
    // Sanity check
    if (mServer == 0)
        return false;

    return mServer->stop();
}

/**
 * @brief Update the systray state (enable or disable)
 *
 * @param state New systray value requested
 */
void App::systrayUpdate(bool state)
{
    // If the new requested state is : enabled
    if (state == true)
    {
        if (mSystray == 0)
        {
            initSystray();
            mUseSystray = true;
        }
    }
    // Else, the new requested state is : disable
    else
    {
        if (mSystray)
        {
            delete mSystray;
            mSystray = 0;
            mUseSystray = false;
        }
    }
}

/* EOF */
