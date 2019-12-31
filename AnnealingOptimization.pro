QT -= gui

CONFIG += c++11 console
CONFIG -= app_bundle

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
        annealing.cpp \
        bounds.cpp \
        main.cpp \
        optimizer.cpp \
        options.cpp \
        result.cpp

HEADERS += \
    annealing.h \
    bounds.h \
    help_types.h \
    optimizer.h \
    options.h \
    result.h

DISTFILES +=

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

LIBS += -L$$PWD/../../../../usr/local/lib/ -lgsl
INCLUDEPATH += $$PWD/../../../../usr/local/include
DEPENDPATH += $$PWD/../../../../usr/local/include
PRE_TARGETDEPS += $$PWD/../../../../usr/local/lib/libgsl.a

LIBS += -L$$PWD/../../../../usr/local/lib/ -lgslcblas
INCLUDEPATH += $$PWD/../../../../usr/local/include
DEPENDPATH += $$PWD/../../../../usr/local/include
PRE_TARGETDEPS += $$PWD/../../../../usr/local/lib/libgslcblas.a
