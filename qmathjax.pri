QT       += core gui webenginewidgets svg webchannel

SOURCES += \
    $$PWD/MathJaxSVG.cpp \
    $$PWD/latextjs.cpp

HEADERS += \
    $$PWD/MathJaxSVG.h \
    $$PWD/latextjs.h

QTQUICK_COMPILER_SKIPPED_RESOURCES += $$PWD/qtmathjax.qrc

RESOURCES += \
    $$PWD/qtmathjax.qrc

