/**
 * @file  jsonobject.cpp
 * @brief This class handle a JSON object
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
#include "jsonobject.h"
#include "jsonstring.h"

/**
 * @brief Default constructor
 *
 */
jsonObject::jsonObject()
{
    mChildren.clear();
}

/**
 * @brief Default destructor
 *
 */
jsonObject::~jsonObject()
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
 * @brief Insert a JSON element as child of this one
 *
 * @param name Name of this object member
 * @param item Pointer to the element to add into child list
 */
void jsonObject::add(const QString &name, jsonElement *item)
{
    item->setName( name );
    mChildren.push_back( item );
}

/**
 * @brief Insert a string key/value as child of this json-object
 *
 * @param name Name of the new string member
 * @param value Value of the string member
 */
void jsonObject::add(const QString &name, const QString &value)
{
    jsonString *newItem = new jsonString(value);
    newItem->setName( name );
    mChildren.push_back( newItem );
}

/**
 * @brief Render members of JSON object
 *
 */
void jsonObject::renderBody(void)
{
    QList<jsonElement *>::iterator item;
    for (item = mChildren.begin(); item != mChildren.end(); ++item)
    {
        QString ss;
        // If item is not the first, insert separator
        if (item != mChildren.begin())
            ss += ", ";

        // Insert object member name
        ss += "\"";
        ss += (*item)->getName();
        ss += "\":";
        append(ss);

        // Insert object member value
        (*item)->setRenderBuffer(mBuffer);
        (*item)->render();
    }
}

/**
 * @brief Render the "head" of the JSON object tag
 *
 */
void jsonObject::renderHead(void)
{
    append( "{" );
}

/**
 * @brief Render the "tail" of the JSON object tag
 *
 */
void jsonObject::renderTail(void)
{
    append( "}" );
}
