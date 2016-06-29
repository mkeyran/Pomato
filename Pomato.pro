TEMPLATE = app

QT += widgets multimedia

CONFIG += c++11

SOURCES += main.cpp \
    pomodoro.cpp \
    trayicon.cpp \
    mainwindow.cpp \
    settings.cpp \
    settingsdialog.cpp

RESOURCES += qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)

HEADERS += \
    pomodoro.h \
    trayicon.h \
    mainwindow.h \
    settings.h \
    settingsdialog.h

QMAKE_CXXFLAGS += --std=c++11

FORMS += \
    mainwindow.ui \
    settingsdialog.ui
