TEMPLATE = app

QT += widgets multimedia

CONFIG += c++11

SOURCES += src/main.cpp \
    src/pomodoro.cpp \
    src/trayicon.cpp \
    src/mainwindow.cpp \
    src/settings.cpp \
    src/settingsdialog.cpp \
    src/sounds.cpp

RESOURCES += \
    resources/resources.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)

HEADERS += \
    src/pomodoro.h \
    src/trayicon.h \
    src/mainwindow.h \
    src/settings.h \
    src/settingsdialog.h \
    src/sounds.h \
    src/utils.h

INCLUDEPATH += src

FORMS += \
    src/mainwindow.ui \
    src/settingsdialog.ui
