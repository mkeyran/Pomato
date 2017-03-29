TEMPLATE = subdirs

SUBDIRS += src UGlobalHotkey
UGlobalHotkey.file = libs/UGlobalHotkey/uglobalhotkey.pro
src.file = src/Pomato.pro
app.depends = UGlobalHotkey


target.path = /usr/bin
INSTALLS += target

CONFIG += c++11
