/**
 * @file  jsonstring.h
 * @brief This class handle a JSON string
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
#ifndef JSONSTRING_H
#define JSONSTRING_H

#include <QString>
#include "jsonelement.h"

/**
 * @class JsonString
 * @brief Class to handle a JSON string
 *
 */
class jsonString : public jsonElement
{
public:
    explicit jsonString(const QString &str);
    void renderBody(void);
private:
    QString mString;
};

#endif // JSONSTRING_H
