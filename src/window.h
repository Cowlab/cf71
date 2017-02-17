/**
 * @file  window.h
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
#ifndef WINDOW_H
#define WINDOW_H

#include <QDialog>
#include <QString>

namespace Ui {
class window;
}

class App;

/**
 * @class window
 * @brief This class manage a dialog window used to get infos and configure app
 *
 */
class window : public QDialog
{
    Q_OBJECT

public:
    explicit window(QWidget *parent = 0, App *app = 0);
    ~window();
signals:
    void closed(void);
    void updateSystray(bool state);
protected:
    void closeEvent(QCloseEvent *e);
    void updateStatus(void);
private slots:
    void evtPassButton();
    void evtPortChanged(QString value);
    void evtPortButton();
    void evtServerButton();
    void evtSystrayCheck(int state);
private:
    Ui::window *ui;
    App        *mApp;
};

#endif // WINDOW_H
