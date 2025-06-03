QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    assembler.cpp \
    globalvariable.cpp \
    handlefunction.cpp \
    instructions.cpp \
    main.cpp \
    mainwindow.cpp \
    memory.cpp \
    registers.cpp

HEADERS += \
    MessageBox.h \
    assembler.h \
    globalvariable.h \
    handlefunction.h \
    instructions.h \
    mainwindow.h \
    memory.h \
    registers.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    picture/Folder Silhouette PNG Free, Folder Vector Icon, Folder Icons, Folder Clipart, Folder Icon PNG Image For Free Download.jfif \
    picture/Folder Silhouette PNG Free, Folder Vector Icon, Folder Icons, Folder Clipart, Folder Icon PNG Image For Free Download.jfif \
    picture/Folder Silhouette PNG Free, Folder Vector Icon, Folder Icons, Folder Clipart, Folder Icon PNG Image For Free Download.jfif \
    picture/Folder Silhouette PNG Free, Folder Vector Icon, Folder Icons, Folder Clipart, Folder Icon PNG Image For Free Download.jfif

RESOURCES += \
    Picture.qrc
