/**
 * @file  page.cpp
 * @brief This class define a generic Page skeleton
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
#include "page.h"
#include "httpcontent.h"

/**
 * @brief Default constructor
 *
 */
Page::Page()
{
    mConnection = 0;
}

/**
 * @brief Default destructor
 *
 */
Page::~Page()
{
    // Nothing to free
}

/**
 * @brief Get the HTTP connection
 *
 * @return httpConnection* Pointer to the connection object
 */
httpConnection *Page::connection(void)
{
    return mConnection;
}

/**
 * @brief Create and return a "Not Found" page (error 404)
 *
 */
void Page::error404(void)
{
    // Create an html content
    httpContent *content = new httpContent();
    content->append("<html><body><h1>404: Not found</h1></body></html>");

    // Create a response for the request
    httpResponse *response = connection()->getResponse();
    response->setStatusCode(404);
    response->setContentType("text/html");
    response->setContent(content);
}

/**
 * @brief Process the page : handle request and create resulting content
 *
 * This is a virtual method, the proces must be overloaded by each specific
 * page. This method is used as fallback if no specific page available. The
 * result is to return a "404" page.
 */
void Page::process(void)
{
    error404();
}

/**
 * @brief Set the connection to use for this page
 * @param conn Pointer to the (connected) client connection
 */
void Page::setConnection(httpConnection *conn)
{
    mConnection = conn;
}
