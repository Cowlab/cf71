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

/**
 * @class PageStatic
 * @brief This class return a content from a static file
 */
class PageStatic: public Page
{
public:
    explicit PageStatic(const QString &uri);
    void process(void);
private:
    QString mUri;
};

#endif // PAGESTATIC_H
