/**
 * @file  window.cpp
 * @brief Dialog window used to get infos and configure app
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
#include <QSettings>
#include "window.h"
#include "ui_window.h"

/**
 * @brief Default constructor
 *
 */
window::window(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::window)
{
    ui->setupUi(this);

    QSettings config;
    // Update the server port with current port value
    ui->lineEditPort->setText( config.value("http_port").toString() );
    // Update the "Enable systray" checkbox according to current config
    if (config.value("use_systray").toBool() == true)
        ui->cbSystray->setChecked(true);
    else
        ui->cbSystray->setChecked(false);

    connect(ui->lineEditPort,  SIGNAL(textChanged(QString)), this, SLOT(evtPortChanged(QString)));
    connect(ui->butPortUpdate, SIGNAL(clicked(bool)),        this, SLOT(evtPortButton()));
    connect(ui->cbSystray,     SIGNAL(stateChanged(int)),    this, SLOT(evtSystrayCheck(int)));
}

/**
 * @brief Default destructor
 *
 */
window::~window()
{
    delete ui;
}

void window::evtPortButton()
{
    int newPort = ui->lineEditPort->text().toInt();
    if ((newPort > 0) && (newPort < 65536))
    {
        QSettings config;
        config.setValue("http_port", QVariant((int)newPort));
        ui->butPortUpdate->setEnabled(false);
    }
}

void window::evtPortChanged(QString value)
{
    QSettings config;
    QString currentPort = config.value("http_port").toString();

    int port = value.toInt();
    if ((port <= 0) || (port > 65535))
    {
        ui->lineEditPort->setStyleSheet("background-color: rgb(255, 101, 101);");
        ui->butPortUpdate->setEnabled(false);
        return;
    }
    else
        ui->lineEditPort->setStyleSheet("");

    if (value != currentPort)
        ui->butPortUpdate->setEnabled(true);
    else
        ui->butPortUpdate->setEnabled(false);
}

void window::evtSystrayCheck(int state)
{
    QSettings config;
    if (state == Qt::Checked)
        config.setValue("use_systray", QVariant((bool)true));
    else
        config.setValue("use_systray", QVariant((bool)false));
}
