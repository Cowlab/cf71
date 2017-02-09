/**
 * @file  usbcontrol.h
 * @brief Main object to manage USB
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
#ifndef USBCONTROL_H
#define USBCONTROL_H

#include <QObject>
#include <QList>
#include <libusb-1.0/libusb.h>
#include "usbdevice.h"

/**
 * @class UsbControl
 * @brief Main object to manage USB
 *
 */
class UsbControl : public QObject
{
    Q_OBJECT
public:
    UsbControl();
    int refreshList(void);
    UsbDevice *getDevice(int index);
private:
    libusb_context *mLibCtx;
    QList<UsbDevice *> mDeviceList;
};

#endif // USBCONTROL_H
