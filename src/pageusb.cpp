/**
 * @file  pageusb.cpp
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
#include "pageusb.h"
#include "httpcontent.h"
#include "httpresponse.h"
#include "usbcontrol.h"

PageUsb::PageUsb()
{
    mUsb = 0;
}

PageUsb::~PageUsb()
{
    if (mUsb)
        delete mUsb;
}

void PageUsb::process(void)
{
    if (mUsb == 0)
        mUsb = new UsbControl;

    httpResponse *response = connection()->getResponse();
    response->setStatusCode(200);
    response->setContentType("text/html");

    httpContent *content = new httpContent();
    QString htmlContent = "<html><body><h1>List USB devices</h1>";

    int count = mUsb->refreshList();

    for (int i = 0; i < count; ++i)
    {
        UsbDevice *dev = mUsb->getDevice(i);
        QString VID = QString("%1").arg(dev->getVid(), 4, 16, QChar('0'));
        QString PID = QString("%1").arg(dev->getPid(), 4, 16, QChar('0'));

        QString pos = QString("%1.%2.%3").arg(dev->getConnBus()).arg(dev->getConnPort()).arg(dev->getConnDevice());
        htmlContent += "<li>" + VID + ":" + PID + "@" + pos + "</li>";
    }
    htmlContent += "</body></html>";
    content->append(htmlContent);
    response->setContent(content);
}
