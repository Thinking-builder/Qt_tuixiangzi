QT       += core gui network


greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    Role.cpp \
    chooselevelscene.cpp \
    choosemodescene.cpp \
    client.cpp \
    gamemap.cpp \
    main.cpp \
    mainscene.cpp \
    mystartbtn.cpp \
    net_game.cpp \
    playscene.cpp \
    roomcreateor.cpp \
    sever.cpp

HEADERS += \
    Role.h \
    chooselevelscene.h \
    choosemodescene.h \
    client.h \
    gamemap.h \
    mainscene.h \
    mystartbtn.h \
    net_game.h \
    playscene.h \
    roomcreateor.h \
    sever.h

FORMS += \
    client.ui \
    mainscene.ui \
    sever.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    IMG.qrc
