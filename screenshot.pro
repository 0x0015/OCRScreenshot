QT += widgets
#requires(qtConfig(filedialog))

HEADERS             = screenshot.h \
                      options.h
SOURCES             = main.cpp \
                      screenshot.cpp \
                      options.cpp
CONFIG+=c++17
LIBS+=-ltesseract
LIBS+=-llept
RESOURCES = images.qrc
include(vendor/vendor.pri)
# install
