QT -= gui

TEMPLATE = app

################################################################################

DESTDIR = $$PWD/../bin
TARGET = tests

################################################################################

CONFIG += console c++17
CONFIG -= app_bundle qt

################################################################################

unix: QMAKE_CXXFLAGS += -O0 \
    --coverage \
    -fno-default-inline \
    -fno-inline \
    -fno-inline-small-functions \
    -fprofile-arcs \
    -ftest-coverage \
    -pedantic

################################################################################

DEFINES += QT_DEPRECATED_WARNINGS
DEFINES += _GTEST_ _TESTS_

win32-msvc*: DEFINES += \
    NOMINMAX \
    _CRT_SECURE_NO_DEPRECATE \
    _SCL_SECURE_NO_WARNINGS \
    _USE_MATH_DEFINES

win32-msvc*: CONFIG(release, debug|release): DEFINES += NDEBUG
win32-msvc*: CONFIG(debug, debug|release):   DEFINES += _DEBUG

unix:  DEFINES += _LINUX_
win32: DEFINES += WIN32 _WINDOWS

################################################################################

INCLUDEPATH += ./ ../

unix: INCLUDEPATH += \
    /usr/include/libxml2

win32: INCLUDEPATH += \
    $(GTEST_DIR)/include \
    $(LIBXML_DIR)/include

################################################################################

LIBS += \
    -lgtest \
    -lgtest_main

unix: LIBS += \
    -L/lib \
    -L/usr/lib \
    -lgcov \
    -lxml2 \
    -pthread

win32: LIBS += \
    -L$(GTEST_DIR)/lib \
    -L$(LIBXML_DIR)/lib \
    -lws2_32  \
    -llibxml2

################################################################################

include(tests.pri)
include(../mcutils/mcutils.pri)
