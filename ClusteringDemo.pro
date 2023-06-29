#-------------------------------------------------
#
# Project created by QtCreator 2013-03-07T20:35:10
#
#-------------------------------------------------

QT       += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ClusteringDemo
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    vcolor.cpp \
    cdcanvas.cpp \
    clistermethod.cpp \
    qcluster.cpp \
    qcpoint.cpp \
    qabstractcluster.cpp \
    qmatrixclusters.cpp \
    fviewmatrix.cpp \
    cddendrogram.cpp \
    dendrogramdialog.cpp \
    methodselectdialog.cpp \
    clustermeasure.cpp \
    measureselectdialog.cpp

HEADERS  += mainwindow.h \
    cdcanvas.h \
    vcolor.h \
    clistermethod.h \
    qcluster.h \
    qcpoint.h \
    qabstractcluster.h \
    qmatrixclusters.h \
    fviewmatrix.h \
    cddendrogram.h \
    dendrogramdialog.h \
    methodselectdialog.h \
    clustermeasure.h \
    measureselectdialog.h

FORMS    += mainwindow.ui \
    fviewmatrix.ui \
    dendrogramdialog.ui \
    methodselectdialog.ui \
    aboutdialog.ui \
    createdialog.ui \
    measureselectdialog.ui \
    fillrounddialog.ui

RESOURCES += \
    Icons.qrc \
    translations.qrc

win32 {
        RC_FILE += applico.rc
        OTHER_FILES += applico.rc
}

TRANSLATIONS = cldemo_ru_RU.ts
