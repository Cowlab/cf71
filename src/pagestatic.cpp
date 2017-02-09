/**
 * @file  pagestatic.cpp
 * @brief This class manage pages for static content
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
#include <QDebug>
#include "pagestatic.h"
#include "page.h"
#include "httpconnection.h"
#include "httpcontent.h"
#include "httpresponse.h"

PageStatic::PageStatic() : Page()
{
    //
}

void PageStatic::process(void)
{
    httpResponse *response = connection()->getResponse();
    response->setStatusCode(200);
    response->setContentType("text/html");

    httpContent *content = new httpContent();
    content->append("<html><body><h1>Hello World !</h1></body></html>");
    response->setContent(content);
}
