QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

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
    main.cpp \
    mainwindow.cpp \
    playthread.cpp

HEADERS += \
    mainwindow.h \
    playthread.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target


# ========================================配置【windows】========================================

win32:{
message("running at windows")
FFMPEG_HOME = ../../Libraries/ffmpeg
SDL_HOME = ../../Libraries/sdl
}

# ========================================配置【mac】========================================

mac:{
message("running at mac")
FFMPEG_HOME = /usr/local/Cellar/ffmpeg
SDL_HOME = /usr/local/Cellar/sdl
}

# ========================================导入库========================================

#INCLUDEPATH += $${FFMPEG_HOME}/include
#LIBS += -L$${FFMPEG_HOME}/lib -lavdevice -lavformat -lavutil -lavcodec

INCLUDEPATH += $${SDL_HOME}/include
LIBS += -L$${SDL_HOME}/lib -lSDL2

# 另外关于 dll 的配置，可以放在编译出的可执行文件的同级目录，或者添加到环境变量中。


# ========================================命令说明========================================
# message()可以用来打印
# $${}可以用来取值：.pro中定义的变量
# $$()可以用来取值：系统环境变量中的值
