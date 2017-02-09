/**
 * @file  usbcontrol.cpp
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
#include "usbcontrol.h"
#include "usbdevice.h"

/**
 * @brief Default constructor
 *
 */
UsbControl::UsbControl()
{
    int r;
    r = libusb_init(&mLibCtx);
    if (r < 0)
        throw -1;

    libusb_set_debug(mLibCtx, 3);
}

/**
 * @brief Get a cached device, identified by his cache index
 * @param index Position of the requested device
 * @return Pointer to the device
 */
UsbDevice *UsbControl::getDevice(int index)
{
    if (index > mDeviceList.count())
        return 0;

    return mDeviceList.at(index);
}

/**
 * @brief Refresh the list of connected devices
 * @return Number of devices
 */
int UsbControl::refreshList(void)
{
    libusb_device **devs;

    ssize_t cnt = libusb_get_device_list(mLibCtx, &devs);

    for (int i = 0; i < cnt; ++i)
    {
        UsbDevice *newDev = new UsbDevice(this, devs[i]);
        mDeviceList.append(newDev);
    }
    return cnt;
}
