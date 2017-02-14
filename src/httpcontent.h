/**
 * @file  httpContent.h
 * @brief Base class for an HTTP content
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
#ifndef HTTPCONTENT_H
#define HTTPCONTENT_H

#include <QByteArray>
#include "jsonelement.h"

/**
 * @class httpContent
 * @brief Base class for an HTTP content
 *
 */
class httpContent
{
public:
    httpContent();
    ~httpContent();
    void  append(const QString &str);
    const QByteArray &getData(void);
    void  setJson(jsonElement *root);

private:
    QByteArray   mData;
    jsonElement *mJson;
};

#endif // HTTPCONTENT_H
