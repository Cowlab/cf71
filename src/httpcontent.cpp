/**
 * @file  httpContent.cpp
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
#include <QString>
#include "httpcontent.h"

/**
 * @brief Default constructor
 *
 */
httpContent::httpContent()
{

}

/**
 * @brief Append a string of text into content buffer
 * @param str Reference to the string to append
 *
 */
void httpContent::append(const QString &str)
{
    mData.append(str);
}

/**
 * @brief  Get access to the current data buffer
 * @return Reference to the data buffer
 */
const QByteArray &httpContent::getData(void)
{
    return mData;
}
