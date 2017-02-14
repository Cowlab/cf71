/**
 * @file  jsonarray.h
 * @brief This class handle a JSON array
 *
 * @author Saint-Genest Gwenael <gwen@cowlab.fr>
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
#ifndef JSONARRAY_H
#define JSONARRAY_H

#include <QList>
#include <QString>
#include "jsonelement.h"

/**
 * @class JsonArray
 * @brief Class to handle a JSON array
 *
 */
class jsonArray : public jsonElement
{
public:
    jsonArray();
    ~jsonArray();
    void add(jsonElement *item);
    void add(const QString &value);
    void renderBody(void);
    void renderHead(void);
    void renderTail(void);
private:
    QList<jsonElement *> mChildren;
};

#endif // JSONARRAY_H
