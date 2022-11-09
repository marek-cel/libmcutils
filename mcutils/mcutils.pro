QT -= core gui

TEMPLATE = lib

################################################################################

DESTDIR = $$PWD/../lib
TARGET = mcutils

VERSION = 0.1.0

################################################################################

unix: target.path = /usr/local/lib
!isEmpty(target.path): INSTALLS += target

################################################################################

CONFIG += c++17

################################################################################

unix:  CONFIG(release, debug|release): QMAKE_CXXFLAGS += -O2
win32: CONFIG(release, debug|release): QMAKE_CXXFLAGS += -O2

win32-msvc*: QMAKE_LFLAGS += /INCREMENTAL:NO

################################################################################

win32-msvc*: DEFINES += \
    NOMINMAX \
    _CRT_SECURE_NO_DEPRECATE \
    _SCL_SECURE_NO_WARNINGS \
    _USE_MATH_DEFINES

win32-msvc*: CONFIG(release, debug|release): DEFINES += NDEBUG
win32-msvc*: CONFIG(debug, debug|release):   DEFINES += _DEBUG

unix:  DEFINES += _LINUX_
win32: DEFINES += WIN32 _WINDOWS

win32-msvc*: DEFINES += MCUTILS_DLL_EXPORTS

################################################################################

INCLUDEPATH += ../

unix: INCLUDEPATH += \
    /usr/include/libxml2

win32: INCLUDEPATH += \
    $(LIBXML_DIR)/include

################################################################################

win32: LIBS += \
    -L$(LIBXML_DIR)/lib \
    -llibxml2 \
    -lws2_32

################################################################################

include($$PWD/mcutils.pri)
