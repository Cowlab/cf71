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

Page::Page()
{
    mConnection = 0;
}

httpConnection *Page::connection(void)
{
    return mConnection;
}

void Page::process(void)
{
    //
}

/**
 * @brief Set the connection to use for this page
 * @param conn Pointer to the (connected) client connection
 */
void Page::setConnection(httpConnection *conn)
{
    mConnection = conn;
}
