QT       += core gui webenginewidgets svg webchannel

SOURCES += \
    MathJaxSVG.cpp \
    latextjs.cpp

HEADERS += \
    MathJaxSVG.h \
    latextjs.h

QTQUICK_COMPILER_SKIPPED_RESOURCES += qtmathjax.qrc

RESOURCES += \
    qtmathjax.qrc

