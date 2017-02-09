/**
 * @file  usbdevice.h
 * @brief Manage one specific USB device
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
#ifndef USBDEVICE_H
#define USBDEVICE_H

#include <QObject>
#include <libusb-1.0/libusb.h>

/**
 * @class UsbDevice
 * @brief Manage one specific USB device
 */
class UsbDevice : public QObject
{
    Q_OBJECT
public:
    explicit UsbDevice(QObject *parent, libusb_device *dev = 0);
    ~UsbDevice();
    ulong   getPid(void);
    ulong   getVid(void);
protected:
    void    setDevice(libusb_device *dev);
private:
    ulong   mVID;
    ulong   mPID;
};

#endif // USBDEVICE_H
