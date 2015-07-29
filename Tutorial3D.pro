# 这是教程文件，介绍了从一个简单的程序到复杂程序的过程

QT += core gui widgets

# Qt 3D新增的
QT += 3dcore 3drenderer 3dinput 3dquick

SOURCES += \
    main.cpp \
    MainWindow.cpp

FORMS += \
    MainWindow.ui

HEADERS += \
    MainWindow.h
