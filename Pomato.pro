TEMPLATE = subdirs

SUBDIRS += src UGlobalHotkey
UGlobalHotkey.file = libs/UGlobalHotkey/uglobalhotkey.pro
src.file = src/Pomato.pro
app.depends = UGlobalHotkey

QMAKE_CXXFLAGS += -std=c++11
