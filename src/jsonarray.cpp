/**
 * @file  jsonarray.cpp
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
#include "jsonarray.h"
#include "jsonstring.h"

/**
 * @brief Constructor
 *
 */
jsonArray::jsonArray()
{
    mChildren.clear();
}

/**
 * @brief Default destructor
 *
 */
jsonArray::~jsonArray()
{
    // Delete all child elements (if any)
    while( mChildren.size() )
    {
        jsonElement *e = mChildren.back();
        mChildren.pop_back();
        delete e;
    }
}

/**
 * @brief Insert a JSON element as an item of the array
 *
 * @param item Pointer to the element to add into child list
 */
void jsonArray::add(jsonElement *item)
{
    mChildren.push_back( item );
}

/**
 * @brief Insert a string value as an item of this array
 *
 * @param value String to add as a new array item
 */
void jsonArray::add(const QString &value)
{
    jsonString *newItem = new jsonString(value);
    mChildren.push_back( newItem );
}

/**
 * @brief Render members of JSON array
 *
 */
void jsonArray::renderBody(void)
{
    QList<jsonElement *>::iterator item;
    for (item = mChildren.begin(); item != mChildren.end(); ++item)
    {
        // If item is not the first, insert separator
        if (item != mChildren.begin())
            append(", ");

        // Insert object member value
        (*item)->setRenderBuffer(mBuffer);
        (*item)->render();
    }
}

/**
 * @brief Render the "head" of the JSON array tag
 *
 */
void jsonArray::renderHead(void)
{
    append( "[" );
}

/**
 * @brief Render the "tail" of the JSON array tag
 *
 */
void jsonArray::renderTail(void)
{
    append( "]" );
}
