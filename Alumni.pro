QT       += core gui
QT       += sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Data_S.cpp \
    FilterHeaderView.cpp \
    FindWidget.cpp \
    ShowFilterWidget.cpp \
    connectConfig.cpp \
    dataWindow.cpp \
    main.cpp \
    mainWindow.cpp \
    tablewindow.cpp

HEADERS += \
    Data.h \
    Data_S.h \
    FilterHeaderView.h \
    FindWidget.h \
    ShowFilterWidget.h \
    connectConfig.h \
    dataWindow.h \
    information.h \
    mainWindow.h \
    tablewindow.h

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
QMAKE_TARGET_COPYRIGHT = AnglesD
QMAKE_TARGET_DESCRIPTION = Alumni Systen
QMAKE_TARGET_COMPANY = D1005562341
QMAKE_TARGET_PRODUCT = Alumni
VERSION = 1.0.2.3
DEFINES += APP_VERSION=\\\"$$VERSION\\\"

DISTFILES +=

RESOURCES += \
    alumni.qrc
RC_ICONS = image.ico
