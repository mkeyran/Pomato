TEMPLATE = app

QT += widgets multimedia

CONFIG += c++11

SOURCES += main.cpp \
    pomodoro.cpp \
    trayicon.cpp \
    mainwindow.cpp \
    settings.cpp \
    settingsdialog.cpp \
    sounds.cpp

RESOURCES += \
    ../resources/resources.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)

HEADERS += \
    pomodoro.h \
    trayicon.h \
    mainwindow.h \
    settings.h \
    settingsdialog.h \
    sounds.h \
    utils.h


FORMS += \
    mainwindow.ui \
    settingsdialog.ui

INCLUDEPATH += \
            /usr/include/c++/6.2.1 \
            src \
            ../libs/UGlobalHotkey

LIBS += -L../libs/UGlobalHotkey -lUGlobalHotkey

target.path = /usr/bin
INSTALLS += target
