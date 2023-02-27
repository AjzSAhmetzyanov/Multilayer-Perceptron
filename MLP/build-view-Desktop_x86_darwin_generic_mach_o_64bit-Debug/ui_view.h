/********************************************************************************
** Form generated from reading UI file 'view.ui'
**
** Created by: Qt User Interface Compiler version 6.2.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_VIEW_H
#define UI_VIEW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>
#include <render_scene.h>

QT_BEGIN_NAMESPACE

class Ui_view
{
public:
    QWidget *centralwidget;
    render_scene *scene;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *view)
    {
        if (view->objectName().isEmpty())
            view->setObjectName(QString::fromUtf8("view"));
        view->resize(1076, 880);
        centralwidget = new QWidget(view);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        scene = new render_scene(centralwidget);
        scene->setObjectName(QString::fromUtf8("scene"));
        scene->setGeometry(QRect(720, 430, 351, 401));
        view->setCentralWidget(centralwidget);
        menubar = new QMenuBar(view);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 1076, 21));
        view->setMenuBar(menubar);
        statusbar = new QStatusBar(view);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        view->setStatusBar(statusbar);

        retranslateUi(view);

        QMetaObject::connectSlotsByName(view);
    } // setupUi

    void retranslateUi(QMainWindow *view)
    {
        view->setWindowTitle(QCoreApplication::translate("view", "view", nullptr));
    } // retranslateUi

};

namespace Ui {
    class view: public Ui_view {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_VIEW_H
