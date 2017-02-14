/**
 * @file  jsonstring.cpp
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
#include "jsonstring.h"

/**
 * @brief Default constructor
 *
 */
jsonString::jsonString(const QString &str): mString(str)
{
    // Nothing to do
}

/**
 * @brief Render the JSON string
 *
 */
void jsonString::renderBody(void)
{
    QString result;

    result  = "\"";
    result += mString;
    result += "\"";

    append( result );
}
