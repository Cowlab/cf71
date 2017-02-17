/**
 * @file  app.h
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
#ifndef APP_H
#define APP_H

#include <QObject>
#include "window.h"

class httpServer;
class QSystemTrayIcon;

/**
 * @class App
 * @brief The App class is the central arbitrer of program
 *
 */
class App : public QObject
{
    Q_OBJECT
public:
    explicit App(QObject *parent = 0);
    void initSystray(void);
    void start(void);
    bool isServerStarted(void);
    bool startServer(void);
    bool stopServer(void);
private slots:
    void openDialog();
    void dialogClosed();
    void systrayUpdate(bool state);

private:
    httpServer      *mServer;
    QSystemTrayIcon *mSystray;
    bool             mUseSystray;
    window          *mWindow;
};

#endif // APP_H
