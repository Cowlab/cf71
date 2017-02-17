/**
 * @file  page.cpp
 * @brief This class define a generic Page skeleton
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
#include <QSettings>
#include "page.h"
#include "httpcontent.h"
#include "jsonobject.h"
#include "jsonarray.h"

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
    if (mConnection == 0)
        throw 99;
    return mConnection;
}

/**
 * @brief Create and return a "Forbidden" page (error 403)
 *
 */
void Page::error403(void)
{
    // Create an html content
    httpContent *content = new httpContent();
    content->append("<html><body><h1>403: Forbidden</h1></body></html>");

    // Create a response for the request
    httpResponse *response = connection()->getResponse();
    response->setStatusCode(403);
    response->setContentType("text/html");
    response->setContent(content);
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
 * @brief Test if the request is an XMLHttpRequest
 *
 * @return boolean True is the request if XMLHttpRequest
 */
bool Page::isJsonRequest(void)
{
    QString xHeader = connection()->getHeader("X-Requested-With");

    if (xHeader.toLower() == "xmlhttprequest")
        return true;

    return false;
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

/**
 * @brief Set a JSON element as result content
 *
 * @param json Pointer to the JSON element to use as result
 */
void Page::setContent(jsonElement *json)
{
    // Create an http content
    httpContent *content = new httpContent();
    content->setJson(json);

    // Create a response for the request
    httpResponse *response = connection()->getResponse();
    response->setStatusCode(200);
    response->setContentType("application/json");
    response->setContent(content);
}

/**
 * @brief Set the security flag
 *
 * @param en New security flag value (true to enable)
 */
void Page::setSecurity(bool en)
{
    mSecurity = en;
}

/**
 * @brief Test security flag and password
 *
 * @return boolean Security status (True if everything ok)
 */
bool Page::testSecurity(void)
{
    // If the page does not use security flag ... nothing more to do
    if ( ! useSecurity() )
        return true;

    // Get the password argument from request
    QString passArg = connection()->getQueryArg("password");

    // Get the current password
    QSettings config;
    QString pass = config.value("http_pass").toString();

    // Compare passwords
    if (passArg == pass)
        return true;

    // Security test fails ... load a default "403" error
    error403();
    return false;
}

/**
 * @brief Test if security flag is set
 *
 * @return boolean True if security flag is set
 */
bool Page::useSecurity(void)
{
    return mSecurity;
}
