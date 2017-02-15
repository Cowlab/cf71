/**
 * @file  main.cpp
 * @brief Entry point of CF21. Load and start QApplication and App
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
#include <QApplication>
#include <QMessageBox>
#include <QSystemTrayIcon>
#include "app.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QApplication::setQuitOnLastWindowClosed(false);
    QApplication::setOrganizationName("Cowlab");
    QApplication::setApplicationName ("CF71");
    QApplication::setOrganizationDomain("cowlab.io");

    App probeApp;
    probeApp.start();

    return a.exec();
}
