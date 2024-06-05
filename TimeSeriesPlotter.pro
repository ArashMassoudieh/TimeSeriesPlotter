QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets charts

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

INCLUDEPATH += ../QAquifolium/ \
    ../Utilities/ \


SOURCES += \
    chartview.cpp \
    main.cpp \
    mainwindow.cpp \
    qplotter.cpp \
    qplotwindow.cpp

HEADERS += \
    ../QAquifolium/aquifolium/src/BTC.hpp \
    ../QAquifolium/aquifolium/src/BTCSet.hpp \
    chartview.h \
    mainwindow.h \
    qplotter.h \
    qplotwindow.h

FORMS += \
    mainwindow.ui \
    qplotwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
