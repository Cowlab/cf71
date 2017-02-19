/**
 * @file  httpresponse.h
 * @brief Class to handle a response to an HTTP request
 *
 * @author Saint-Genest Gwenael <gwen@cowlab.fr>
 * @copyright Cowlab (c) 2017
 *
 * @par Warning
 * CF71 is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License
 * version 3 as published by the Free Software Foundation. You
 * should have received a copy of the GNU Lesser General Public
 * License along with this program, see LICENSE file for more details.
 * This program is distributed WITHOUT ANY WARRANTY see README file.
 */
#ifndef HTTPRESPONSE_H
#define HTTPRESPONSE_H

#include <QString>

class QTcpSocket;
class httpContent;

/**
 * @class httpResponse
 * @brief This class is used to handle a response to an HTTP request
 *
 */
class httpResponse
{
public:
    httpResponse();
    ~httpResponse();
    httpContent *getContent(void);
    void send(QTcpSocket *sock);
    void setContent(httpContent *content);
    void setContentType(const QString &type);
    void setStatusCode(int code);
private:
    int          mRetCode;
    QString      mContentType;
    httpContent *mContent;
};

#endif // HTTPRESPONSE_H
