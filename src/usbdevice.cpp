/**
 * @file  usbdevice.cpp
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
#include "usbdevice.h"

/**
 * @brief Default constructor
 * @param parent Pointer to the parent QObject
 * @param dev Pointer to a libusb device to load
 */
UsbDevice::UsbDevice(QObject *parent, libusb_device *dev)
    : QObject(parent)
{
    mVID = 0;
    mPID = 0;
    if (dev)
        setDevice(dev);
}

/**
 * @brief Default destructor
 *
 */
UsbDevice::~UsbDevice()
{
    //
}

/**
 * @brief Get the USB bus number where device is connected
 *
 * @return integer Bus ID
 */
uint UsbDevice::getConnBus(void)
{
    return mBus;
}

/**
 * @brief Get the USB device number that identify the current device on the bus
 *
 * @return integer Device ID
 */
uint UsbDevice::getConnDevice(void)
{
    return mDev;
}

/**
 * @brief Get the USB port number where device is connected
 *
 * @return integer Port ID
 */
uint UsbDevice::getConnPort(void)
{
    return mPort;
}

/**
 * @brief Get the product-ID of the device
 *
 * @return integer Product ID
 */
ulong UsbDevice::getPid(void)
{
    return mPID;
}

/**
 * @brief Get the vendor-ID of the device
 *
 * @return integer Vendor ID
 */
ulong UsbDevice::getVid(void)
{
    return mVID;
}

/**
 * @brief Load device informations from a libusb device structure
 *
 * @param dev Pointer to the device struct from libusb
 */
void UsbDevice::setDevice(libusb_device *dev)
{
    libusb_device_descriptor desc;
    int r = libusb_get_device_descriptor(dev, &desc);
    if (r < 0)
        throw -1;

    mVID = desc.idVendor;
    mPID = desc.idProduct;

    mBus  = libusb_get_bus_number(dev);
    mPort = libusb_get_port_number(dev);
    mDev  = libusb_get_device_address(dev);
}
