QT += widgets

SOURCES += main.cpp \
    mainwindow.cpp \
    view.cpp \
    sqmeter.cpp \
    animal.cpp \
    dialogstart.cpp \
    crain.cpp \
    mylogger.cpp \
    dialogresults.cpp

RESOURCES += \
    resources.qrc

HEADERS += \
    mainwindow.h \
    view.h \
    sqmeter.h \
    animal.h \
    dialogstart.h \
    crain.h \
    mylogger.h \
    dialogresults.h

FORMS += \
    dialogstart.ui \
    dialogresults.ui

DISTFILES += \
    simulatormodel.qmodel
