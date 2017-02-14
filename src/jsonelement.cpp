/**
 * @file  jsonelement.cpp
 * @brief This is a generic class to handle a JSON element
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
#include "jsonelement.h"

/**
 * @brief Default constructor
 *
 */
jsonElement::jsonElement()
{
    mBuffer = 0;
    mName.clear();
}

/**
 * @brief Default destructor
 *
 */
jsonElement::~jsonElement()
{

}

/**
 * @brief Append a string to the output buffer
 *
 * @param str Reference to the string to append
 */
void jsonElement::append(const QString &str)
{
    // Sanity check
    if (mBuffer == 0)
        return;

    mBuffer->append(str);
}

/**
 * @brief Get the name of this element
 *
 * @return QString The current element name
 */
QString jsonElement::getName(void)
{
    return mName;
}

/**
 * @brief This method produce the JSON (text) code of this object
 *
 */
void jsonElement::render(void)
{
    // Render a first part named "head"
    renderHead();
    // Render a second part named "body"
    renderBody();
    // Render a third part named "tail"
    renderTail();
}

/**
 * @brief Default render for the "head" of this element
 *
 */
void jsonElement::renderHead(void)
{
}

/**
 * @brief Default render for the "body" of this element
 *
 */
void jsonElement::renderBody(void)
{
}

/**
 * @brief Default rendre for the "tail" of this element
 *
 */
void jsonElement::renderTail(void)
{
}

/**
 * @brief Set the name of this object
 *
 * @param name New name to set
 */
void jsonElement::setName(const QString &name)
{
    mName = name;
}

/**
 * @brief Set the output buffer to use for rendering element
 *
 * @param buffer Pointer to the output buffer
 */
void jsonElement::setRenderBuffer(QByteArray *buffer)
{
    mBuffer = buffer;
}
