QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    ../Controller/controller.cpp \
    ../Model/ActivateFunctions/ActivateFunction.cpp \
    ../Model/Graph/GraphNeuron.cpp \
    ../Model/Graph/GraphPerceptron.cpp \
    ../Model/Matrix/Matrix.cpp \
    ../Model/Network/Network.cpp \
    main.cpp \
    render_scene.cpp \
    view.cpp

HEADERS += \
    ../Controller/controller.h \
    ../Model/ActivateFunctions/ActivateFunction.h \
    ../Model/Graph/GraphNeuron.h \
    ../Model/Graph/GraphPerceptron.h \
    ../Model/Matrix/Matrix.h \
    ../Model/Network/Network.h \
    render_scene.h \
    view.h

FORMS += \
    view.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    ../Model/Weights/weigth_2.txt \
    ../Model/Weights/weigth_3.txt \
    ../Model/Weights/weigth_4.txt \
    ../Model/Weights/weigth_5.txt \
    ../Model/Weights/weigth_6.txt \
    images/bg.png

RESOURCES += \
    resources.qrc
