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
#include "jsonarray.h"
#include "jsonobject.h"
#include "usbcontrol.h"

/**
 * @brief Default constructor
 *
 */
PageUsb::PageUsb()
{
    mUsb = 0;
}

/**
 * @brief Default destructor
 *
 */
PageUsb::~PageUsb()
{
    if (mUsb)
        delete mUsb;
}

/**
 * @brief Process a request and create a resulting content
 *
 */
void PageUsb::process(void)
{
    if (mUsb == 0)
        mUsb = new UsbControl;

    // If a JSON content is requested
    if ( isJsonRequest() )
        resultJson();
    // Else, make an HTML content as result
    else
        resultHtml();
}

/**
 * @brief Create a HTML content as result
 *
 */
void PageUsb::resultHtml(void)
{
    QString htmlContent = "<h2>List USB devices</h2>";
    htmlContent += "<ul>";

    int count = mUsb->refreshList();

    for (int i = 0; i < count; ++i)
    {
        UsbDevice *dev = mUsb->getDevice(i);
        QString VID = QString("%1").arg(dev->getVid(), 4, 16, QChar('0'));
        QString PID = QString("%1").arg(dev->getPid(), 4, 16, QChar('0'));

        QString pos = QString("%1.%2.%3").arg(dev->getConnBus()).arg(dev->getConnPort()).arg(dev->getConnDevice());
        htmlContent += "<li>" + VID + ":" + PID + "@" + pos + "</li>";
    }
    htmlContent += "</ul>";

    httpContent *content = new httpContent();
    content->append(htmlContent);

    httpResponse *response = connection()->getResponse();
    response->setStatusCode(200);
    response->setContentType("text/html");
    response->setContent(content);
}

/**
 * @brief Create a JSON content as result
 *
 */
void PageUsb::resultJson(void)
{
    jsonObject *jContent = new jsonObject();
    jContent->add("result", "success");

    jsonArray *jList = new jsonArray();
    jContent->add("list", jList);

    for (int i = 0; i < mUsb->refreshList(); ++i)
    {
        UsbDevice *dev = mUsb->getDevice(i);

        QString VID = QString("%1").arg(dev->getVid(), 4, 16, QChar('0'));
        QString PID = QString("%1").arg(dev->getPid(), 4, 16, QChar('0'));
        // Get conenction infos
        QString busID  = QString("%1").arg(dev->getConnBus());
        QString portID = QString("%1").arg(dev->getConnPort());
        QString devID  = QString("%1").arg(dev->getConnDevice());

        jsonObject *item = new jsonObject();
        item->add("vid", VID);
        item->add("pid", PID);
        item->add("conn_bus",    busID);
        item->add("conn_port",   portID);
        item->add("conn_device", devID);

        jList->add(item);
    }

    setContent(jContent);
}
