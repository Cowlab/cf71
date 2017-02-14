/**
 * @file  jsonelement.h
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
#ifndef JSONELEMENT_H
#define JSONELEMENT_H

#include <QByteArray>
#include <QString>

/**
 * @class jsonElement
 * @brief The jsonElement class
 */
class jsonElement
{
public:
    jsonElement();
    virtual ~jsonElement();
    QString getName(void);
    void    setName(const QString &name);
    void    setRenderBuffer(QByteArray *buffer);
public:
    virtual void render(void);
protected:
    void append(const QString &str);
    virtual void renderHead(void);
    virtual void renderBody(void);
    virtual void renderTail(void);
protected:
    QString     mName;
    QByteArray *mBuffer;
};

#endif // JSONELEMENT_H
