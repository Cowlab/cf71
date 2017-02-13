/**
 * @file  pagestatic.cpp
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
#include <QDebug>
#include <QFile>
#include "pagestatic.h"
#include "page.h"
#include "httpconnection.h"
#include "httpcontent.h"
#include "httpresponse.h"

/**
 * @brief Default constructor
 *
 * @param uri String of the requested URI
 */
PageStatic::PageStatic(const QString &uri) : Page()
{
    mUri = uri;
    if ( ! mUri.isEmpty() )
    {
        while(mUri.at(0) == '/')
        {
            // Remove the first char
            mUri = mUri.mid(1);
            // If string is now empty ... nothing more to do
            if (mUri.isEmpty())
                break;
        }
    }
}

void PageStatic::process(void)
{
    try {
        if (mUri.isEmpty())
            throw 404;

        QString fileName = QString(":/html/%1").arg(mUri);

        QFile dataFile(fileName);
        if ( ! dataFile.exists())
            throw 404;

        if (!dataFile.open(QIODevice::ReadOnly | QIODevice::Text))
            throw 403;

        QTextStream in(&dataFile);

        QString fileContent = in.readAll();

        httpContent *content = new httpContent();
        content->append(fileContent);

        httpResponse *response = connection()->getResponse();
        response->setStatusCode(200);
        response->setContentType("text/html");
        response->setContent(content);

    } catch (int ecode) {
#ifdef QT_DEBUG
        qWarning() << "PageStatic: Failed to load " << mUri;
#endif
        if (ecode == 404)
            error404();
    }
}
