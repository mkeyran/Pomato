TEMPLATE = app

QT += widgets

CONFIG += c++11

SOURCES += main.cpp \
    pomodoro.cpp \
    trayicon.cpp \
    mainwindow.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)

HEADERS += \
    pomodoro.h \
    trayicon.h \
    mainwindow.h

QMAKE_CXXFLAGS += --std=c++11

FORMS += \
    mainwindow.ui
