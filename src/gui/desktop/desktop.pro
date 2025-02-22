QT       += widgets
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
    SnakeQt.cpp \ 
    TetrisQt.cpp \
    InfoPanel.cpp \
    GameMenu.cpp \
    main.cpp \
    mainwindow.cpp \ 
    ../../brick_game/snake/SnakeController.cpp \
    ../../brick_game/snake/SnakeModel.cpp \
    ../../brick_game/tetris/backend.c \
    ../../brick_game/tetris/figures.c



HEADERS += \
    SnakeQt.h \
    TetrisQt.h \
    InfoPanel.h \
    GameMenu.h \
    mainwindow.h \
    ../../brick_game/snake/SnakeController.h \
    ../../brick_game/snake/SnakeModel.h \
    ../../brick_game/struct.h \
    ../../brick_game/tetris/backend.h




# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
