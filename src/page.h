/**
 * @file  page.h
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
#ifndef PAGE_H
#define PAGE_H

#include "httpconnection.h"

class Page
{
public:
    Page();
    httpConnection *connection(void);
    void setConnection(httpConnection *conn);
    virtual void process(void);
private:
    httpConnection *mConnection;
};

#endif // PAGE_H
