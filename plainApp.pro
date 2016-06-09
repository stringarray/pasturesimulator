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

CONFIG(release, debug|release) {
    DESTDIR = release
} else {
    DESTDIR = debug
}

#for Windows
win32 {
    #in Windows, you can use & to separate commands
    copyfiles.commands += @echo NOW COPYING ADDITIONAL FILE(S) &
    copyfiles.commands += @call xcopy ..\\$${TARGET}\\pages $${DESTDIR}\\pages /S /E /C /I /Y

    QMAKE_CLEAN += /s /f /q DESTDIR && rd /s /q DESTDIR

}

#for Mac
macx {
     #commands would go here if I had them
}

QMAKE_EXTRA_TARGETS += copyfiles
POST_TARGETDEPS += copyfiles
