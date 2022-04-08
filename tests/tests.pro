QT -= gui

TEMPLATE = app

################################################################################

DESTDIR = $$PWD/../bin
TARGET = tests

################################################################################

CONFIG += console c++17
CONFIG -= app_bundle qt

################################################################################

QMAKE_CXXFLAGS += -O0 \
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
win32: DEFINES += WIN32 _WINDOWS IN_LIBXML

################################################################################

INCLUDEPATH += ./ ../

win32: INCLUDEPATH += \
    $(GTEST_DIR)/include \
    $(LIBXML_DIR)/include/libxml2

unix: INCLUDEPATH += \
    /usr/include/libxml2

################################################################################

LIBS += \
    -lgcov \
    -lgtest \
    -lgtest_main \
    -lgtest \
    -lgtest_main \
    -lxml2 \
    -pthread

win32: LIBS += \
    -L$(GTEST_DIR)/lib \
    -L$(LIBXML_DIR)/lib \
    -lwsock32 \
    -lws2_32

win32-g++: LIBS += \
    -liconv

unix: LIBS += \
    -L/lib \
    -L/usr/lib

################################################################################

include(tests.pri)
include(../mcutils/mcutils.pri)
