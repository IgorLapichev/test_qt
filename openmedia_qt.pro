QT       += quick widgets core

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    src/Comparator.cpp \
    src/ComparatorFactory.cpp \
    src/TestManager.cpp \
    src/Utils.cpp \
    src/main.cpp

HEADERS += \
    src/Comparator.h \
    src/ComparatorFactory.h \
    src/TestManager.h \
    src/Utils.h

FORMS +=

RESOURCES += \
    openmedia_qt.qrc


PROJECT_DIR                = $$PWD
OPENSSL_PATH               = $$PROJECT_DIR/3rdparty/OpenSSL-Win64

INCLUDEPATH    +=   $$OPENSSL_PATH/include
LIBS           += -L$$OPENSSL_PATH/lib -llibcrypto64MD
PRE_TARGETDEPS +=   $$OPENSSL_PATH/lib/libcrypto64MD.lib

QMAKE_POST_LINK = $$QMAKE_COPY $$shell_path($$OPENSSL_PATH/bin/libcrypto-1_1-x64.dll) $$shell_path($$DESTDIR)


# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
