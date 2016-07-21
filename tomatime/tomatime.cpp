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

Tomatime::Tomatime(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Tomatime)
{
    QCoreApplication::setOrganizationName("Tomatime");
    QCoreApplication::setOrganizationDomain("github.com");
    QCoreApplication::setApplicationName("tomatime");

    ui->setupUi(this);

    // Initialize value from setting
    QSettings setting;

    //setWorkingTime( setting.value("time/working").toInt() );
    //setBreakTime( (setting.value("time/break").isNull() == true ) ? setting.value("time/break", 5).toInt() : setting.value("time/break").toInt() );
    //setLongBreakTime( (setting.value("time/longbreak").isNull() ) ? setting.value("time/longbreak", 10).toInt() : setting.value("time/longbreak").toInt() );


    connect(ui->start_button, SIGNAL(clicked()),this, SLOT(clickedStartButton()));
    connect(ui->settings_button, SIGNAL(clicked()),this, SLOT(clickedSettingsButton()));
    connect(ui->stop_button, SIGNAL(clicked()),this, SLOT(clickedStopButton()));

    connect(ui->actionSettings, SIGNAL(triggered()),this,SLOT(settingsMenu()));
    connect(ui->actionAbout, SIGNAL(triggered()),this,SLOT(aboutMenu()));

    // Recenter form
    QRect position = frameGeometry();
    position.moveCenter(QDesktopWidget().availableGeometry().center());
    move(position.topLeft());

    // Init LCD
    //ui->lcdNumber->display(QTime(0,getWorkingTime(),0).toString());

    // Init working count
    workingCount = 0;

    // Init Timer mode
    // 0 = Working
    // 1 = Short Break
    // 2 = Long Break
    timerMode = 0;

    // Init System tray
    createActions();
    createTrayIcon();
    trayIcon->show();

}

Tomatime::~Tomatime()
{
    delete ui;

    // Prevent memory leak
    delete timer;
    delete timeValue;
    delete restoreAction;
    delete quitAction;
    delete trayIcon;
    delete trayIconMenu;

}

void Tomatime::clickedStartButton()
{
    QMessageBox msgBox;
    msgBox.setText("Minutes " +  QString::number(workingTime));
    msgBox.exec();
    this->startWork();
    workingCount++;
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
    int reminderTimeMiliSecond = getWorkingTime() * 60 * 1000;
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
    restoreAction = new QAction(tr("&Restore"), this);
    connect(restoreAction, SIGNAL(triggered()),this,SLOT(showNormal()));
    quitAction = new QAction(tr("&Exit"),this);
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

void Tomatime::showMessageTray(QString message)
{
    trayIcon->showMessage("Information", message, QSystemTrayIcon::Information, 10000);
}

void Tomatime::showMessageRemainingTime()
{
//    QString reminderTime = QString::number(timeBreak);
//    trayIcon->showMessage("Information", "Hi there! You only have " + reminderTime + " minutes left. But, keep spirit! :)  ", QSystemTrayIcon::Information, 10000);
}

void Tomatime::pomodoroIsOver()
{
    timer->stop(); //Stop the timer

    if(timerMode == 0){

        if((workingCount != 0) && (workingCount % 3) == 0){
            this->takeLongBreak();
            timerMode = 2;
            this->showMessageTray(tr("Take a long break!"));
            qWarning()<< "Long Break";
        }else{
            this->takeBreak();
            timerMode = 1;
            this->showMessageTray(tr("Take a short break!"));
            qWarning()<< "Short Break";
        }

        workingCount++;
    }else{
        this->startWork();
        timerMode = 0;
        this->showMessageTray(tr("Working time, do something great!"));
        qWarning()<< "Working";
    }

}

void Tomatime::clickedSettingsButton()
{
    settingDialog = new Settings(this);
    settingDialog->setAttribute(Qt::WA_DeleteOnClose);
    settingDialog->show();
}

void Tomatime::clickedStopButton()
{
    timer->stop();
    ui->lcdNumber->display("00:00");

    // Enable & disable button
    ui->stop_button->setEnabled(false);
    ui->start_button->setEnabled(true);
}

void Tomatime::startWork(){

    ui->labelInfo->setText(tr("Working time"));
    this->showMessageTray(tr("Working time, do something great!"));

    // Start pomodoro timer
    setTimer(getWorkingTime(), 0);
    timer->start(1000);

    // Disable start button
    ui->start_button->setEnabled(false);
    ui->stop_button->setEnabled(true);

}

void Tomatime::takeBreak(){
    ui->labelInfo->setText(tr("Take a short break"));

    // Start pomodoro timer
    setTimer(getBreakTime(), 0);
    timer->start(1000);
}

void Tomatime::takeLongBreak(){
    ui->labelInfo->setText(tr("Take a long break"));

    // Start pomodoro timer
    setTimer(getLongBreakTime(), 0);
    timer->start(1000);
}

void Tomatime::settingsMenu()
{
    settingDialog = new Settings(this);
    settingDialog->setAttribute(Qt::WA_DeleteOnClose);
    settingDialog->show();
}

void Tomatime::aboutMenu()
{
    aboutWidget = new About(this);
    aboutWidget->setAttribute(Qt::WA_DeleteOnClose);
    aboutWidget->show();
}

void Tomatime::setWorkingTime(int nWorkingTime)
{
   workingTime = nWorkingTime;

}

int Tomatime::getWorkingTime()
{
    return workingTime;
}

int Tomatime::getBreakTime()
{
    return breakTime;
}

int Tomatime::getLongBreakTime()
{
    return longBreakTime;
}

void Tomatime::setBreakTime(int nBreakTime)
{
   breakTime = nBreakTime;
}

void Tomatime::setLongBreakTime(int nLongBreakTime)
{
   longBreakTime = nLongBreakTime;
}
