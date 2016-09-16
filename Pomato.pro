TEMPLATE = subdirs

SUBDIRS += src UGlobalHotkey
UGlobalHotkey.file = libs/UGlobalHotkey/uglobalhotkey.pro
src.file = src/Pomato.pro
app.depends = UGlobalHotkey

CONFIG += c++11
