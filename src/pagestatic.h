/**
 * @file  pagestatic.h
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
#ifndef PAGESTATIC_H
#define PAGESTATIC_H

#include "page.h"

class PageStatic: public Page
{
public:
    PageStatic();
    void process(void);
};

#endif // PAGESTATIC_H
