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
    condmutex.cpp \
    main.cpp \
    mainwindow.cpp \
    videoplayer.cpp \
    videoplayer_audio.cpp \
    videoplayer_video.cpp \
    videoslider.cpp \
    videowidget.cpp

HEADERS += \
    README.h \
    condmutex.h \
    mainwindow.h \
    videoplayer.h \
    videoslider.h \
    videowidget.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target


# ========================================配置【windows】========================================

win32:{
message("running at windows")
FFMPEG_HOME = D:\dev_tools\msys64\usr\local\ffmpeg
SDL_HOME = D:\dev_tools\msys64\mingw64
}

# ========================================配置【mac】========================================

mac:{
message("running at mac")
FFMPEG_HOME = /usr/local/Cellar/ffmpeg
SDL_HOME = /usr/local/Cellar/sdl2
}

# ========================================导入库========================================

# 设置 FFmpeg 头文件的位置，以便Qt能够找到它们
INCLUDEPATH += $${FFMPEG_HOME}/include
# 设置 FFmpeg 导入库的位置
LIBS += -L$${FFMPEG_HOME}/lib -lavcodec -lavformat -lavutil -lswresample -lswscale


# 设置 SDL 头文件的位置，以便Qt能够找到它们
INCLUDEPATH += $${SDL_HOME}/include
# 设置 SDL 导入库的位置
LIBS += -L$${SDL_HOME}/lib -lSDL2
# 另外关于 dll 的配置，可以放在编译出的可执行文件的同级目录，或者添加到环境变量中。

# ========================================命令说明========================================
# message()可以用来打印
# $${}可以用来取值：.pro中定义的变量
# $$()可以用来取值：系统环境变量中的值

