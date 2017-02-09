/**
 * @file  pageusb.h
 * @brief This class is an HTTP page for USB
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
#ifndef PAGEUSB_H
#define PAGEUSB_H

#include "page.h"

class UsbControl;

/**
 * @class PageUsb
 * @brief This class is an HTTP page for USB
 *
 */
class PageUsb: public Page
{
public:
    PageUsb();
    ~PageUsb();
    void process(void);
private:
    UsbControl *mUsb;
};

#endif // PAGEUSB_H
