/********************************************************************************
** Form generated from reading UI file 'tomatime.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TOMATIME_H
#define UI_TOMATIME_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLCDNumber>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Tomatime
{
public:
    QWidget *centralWidget;
    QPushButton *start_button;
    QPushButton *settings_button;
    QLCDNumber *lcdNumber;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *Tomatime)
    {
        if (Tomatime->objectName().isEmpty())
            Tomatime->setObjectName(QStringLiteral("Tomatime"));
        Tomatime->resize(400, 300);
        Tomatime->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
        centralWidget = new QWidget(Tomatime);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        start_button = new QPushButton(centralWidget);
        start_button->setObjectName(QStringLiteral("start_button"));
        start_button->setGeometry(QRect(30, 100, 111, 51));
        QIcon icon;
        icon.addFile(QStringLiteral(":/play-icon/img/Video-play-icon.png"), QSize(), QIcon::Normal, QIcon::Off);
        start_button->setIcon(icon);
        settings_button = new QPushButton(centralWidget);
        settings_button->setObjectName(QStringLiteral("settings_button"));
        settings_button->setGeometry(QRect(240, 100, 121, 51));
        lcdNumber = new QLCDNumber(centralWidget);
        lcdNumber->setObjectName(QStringLiteral("lcdNumber"));
        lcdNumber->setGeometry(QRect(100, 100, 181, 51));
        Tomatime->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(Tomatime);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 400, 30));
        Tomatime->setMenuBar(menuBar);
        mainToolBar = new QToolBar(Tomatime);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        Tomatime->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(Tomatime);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        Tomatime->setStatusBar(statusBar);

        retranslateUi(Tomatime);

        QMetaObject::connectSlotsByName(Tomatime);
    } // setupUi

    void retranslateUi(QMainWindow *Tomatime)
    {
        Tomatime->setWindowTitle(QApplication::translate("Tomatime", "Tomatime", 0));
        start_button->setText(QApplication::translate("Tomatime", "Start", 0));
        settings_button->setText(QApplication::translate("Tomatime", "Settings", 0));
    } // retranslateUi

};

namespace Ui {
    class Tomatime: public Ui_Tomatime {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TOMATIME_H
