TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt
LIBS += -ltins
SOURCES += main.cpp \
    ap_info.cpp \
    capture.cpp

HEADERS += \
    ap_info.h \
    capture.h
