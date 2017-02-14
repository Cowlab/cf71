##
 # @file  cf21.pro
 # @brief Project file for QT
 #
 # @author Saint-Genest Gwenael <gwen@hooligan0.net>
 # @copyright Cowlab (c) 2017
 #
 # @par Warning
 # CF21 is free software: you can redistribute it and/or modify
 # it under the terms of the GNU Lesser General Public License
 # version 3 as published by the Free Software Foundation. You
 # should have received a copy of the GNU Lesser General Public
 # License along with this program, see LICENSE file for more details.
 # This program is distributed WITHOUT ANY WARRANTY see README file.
##

QT       += core network svg

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET   = cf21
TEMPLATE = app

SOURCES += main.cpp\
    app.cpp \
    httpconnection.cpp \
    httpcontent.cpp    \
    httpresponse.cpp   \
    httpserver.cpp     \
    page.cpp           \
    pagestatic.cpp     \
    pageusb.cpp        \
    usbcontrol.cpp     \
    usbdevice.cpp      \
    jsonelement.cpp    \
    jsonobject.cpp     \
    jsonstring.cpp     \
    jsonarray.cpp

HEADERS += \
    app.h \
    httpconnection.h \
    httpcontent.h    \
    httpresponse.h   \
    httpserver.h     \
    page.h           \
    pagestatic.h     \
    pageusb.h        \
    usbcontrol.h     \
    usbdevice.h      \
    jsonelement.h    \
    jsonobject.h     \
    jsonstring.h     \
    jsonarray.h

LIBS    += -lusb-1.0

FORMS     +=
RESOURCES += html_content.qrc
