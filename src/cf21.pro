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
    httpserver.cpp \
    httpconnection.cpp

HEADERS += \
    app.h \
    httpserver.h \
    httpconnection.h

FORMS     +=
RESOURCES +=
