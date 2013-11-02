TEMPLATE = subdirs

SUBDIRS += QDHTLib
SUBDIRS += TestApp
SUBDIRS += QBencode

TestApp.depends += QBencode
TestApp.depends += QDHTLib

QDHTLib.depends += QBencode
