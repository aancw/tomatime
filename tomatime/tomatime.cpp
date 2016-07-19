/*
    Author : aancw < cacaddv[at]gmail[dot]com >
    Updated on : 19 July 2016
    Tested OS : Arch Linux x64
    Compiler : Qt 5.7.0 (GCC 6.1.1 20160602, 64 bit)
    Version : 0.1

    Copyright (C) 2016  aancw

    Tomatime is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 2 of the License, or
    (at your option) any later version.

    Tomatime is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with Tomatime. If not, see <http://www.gnu.org/licenses/>.
*/

#include <QtGui>
#include "tomatime.h"
#include "ui_tomatime.h"
#define DEFAULT_POMODORO_TIME 6
#define DEFAULT_REMINDER_TIME 5


Tomatime::Tomatime(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Tomatime)
{
    ui->setupUi(this);

    QObject::connect(ui->start_button, SIGNAL(clicked()),this, SLOT(clickedStartButton()));

    // Recenter form
    QRect position = frameGeometry();
    position.moveCenter(QDesktopWidget().availableGeometry().center());
    move(position.topLeft());

    ui->lcdNumber->setVisible(false);
}

Tomatime::~Tomatime()
{
    delete ui;
}

void Tomatime::clickedStartButton()
{
   QMessageBox msgBox;
   msgBox.setWindowTitle("Tomatime");
   msgBox.setText("Pomodoro timer will be starting. Take your time and do your best :) ");
   msgBox.exec();
   ui->start_button->setVisible(false);
   ui->settings_button->setVisible(false);
   ui->lcdNumber->setVisible(true);
   QWidget::setWindowTitle("Pomodoro Start - Tomatime");

   // Start pomodoro timer
   setTimer(DEFAULT_POMODORO_TIME, 0);
   timer->start(1000);

   // Send application to system tray
   createActions();
   createTrayIcon();
   trayIcon->show();
   showMessageTray();
   this->hide();
}

void Tomatime::setLcdNumber()
{
    timeValue->setHMS(0, timeValue->addSecs(-1).minute(), timeValue->addSecs(-1).second());
    ui->lcdNumber->display(timeValue->toString());

    trayIcon->setToolTip(timeValue->toString());

    checkTime();
}

void Tomatime::setTimer(int minutes, int seconds)
{
    timer = new QTimer();
    timeValue = new QTime(0, minutes, seconds);
    ui->lcdNumber->display(timeValue->toString());
    QObject::connect(timer, SIGNAL(timeout()), this, SLOT(setLcdNumber()));

    // Record when timer is start
    totalSecond = (minutes * 60) + seconds;
    startMilliseconds = totalSecond * 1000;
}

void Tomatime::checkTime()
{
    int Seconds;
    int reminderTimeMiliSecond = DEFAULT_REMINDER_TIME * 60 * 1000;
    if (startMilliseconds - 1000 >= 0) //If not timeout
     {
         startMilliseconds = startMilliseconds - 1000; //Reduce the milliseconds with 1 secod (1000)
         Seconds = ((startMilliseconds % (1000*60*60)) % (1000*60)) / 1000;

        if (startMilliseconds <=0) //If timeout
        {
            pomodoroIsOver();
        }
        else if( startMilliseconds == reminderTimeMiliSecond ){
            showMessageRemainingTime();
        }
     }

}

void Tomatime::closeEvent(QCloseEvent *event)
{
    if(trayIcon->isVisible())
    {
        hide();
        event->ignore();
    }
}

void Tomatime::createActions()
{
    restoreAction = new QAction(tr("&restore"), this);
    connect(restoreAction, SIGNAL(triggered()),this,SLOT(showNormal()));
    quitAction = new QAction(tr("&exit"),this);
    connect(quitAction, SIGNAL(triggered()),qApp,SLOT(quit()));

}

void Tomatime::createTrayIcon()
{
    trayIconMenu = new QMenu(this);
    trayIconMenu->addAction(restoreAction);
    trayIconMenu->addSeparator();
    trayIconMenu->addAction(quitAction);

    trayIcon = new QSystemTrayIcon(this);
    QIcon icon(":/icon/img/icon-tomatime.png");

    trayIcon->setIcon(icon);
    trayIcon->setContextMenu(trayIconMenu);
}

void Tomatime::showMessageTray()
{
    trayIcon->showMessage("Information", "Hi there! Don't worry, i'm still working. Do your best! :)", QSystemTrayIcon::Information, 10000);
}

void Tomatime::showMessageRemainingTime()
{
    QString reminderTime = QString::number(DEFAULT_REMINDER_TIME);
    trayIcon->showMessage("Information", "Hi there! You only have " + reminderTime + " minutes left. But, keep spirit! :)  ", QSystemTrayIcon::Information, 10000);
}

void Tomatime::pomodoroIsOver()
{
    timer->stop(); //Stop the timer
    trayIcon->showMessage("Information", "Hi there! You need to take a break. Enjoy your time! :)", QSystemTrayIcon::Information, 10000);
    this->show();
}
