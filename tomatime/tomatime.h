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

#ifndef TOMATIME_H
#define TOMATIME_H

#include <QMainWindow>
#include <QPushButton>
#include <QMessageBox>
#include <QWidget>
#include <QRect>
#include <QDesktopWidget>
#include <QLCDNumber>
#include <QTimer>
#include <QTime>
#include <QSystemTrayIcon>
#include "settings.h"
#include "about.h"
#include <QDebug>
#include <QObject>


class QAction;
class QMenu;
class Settings;
class About;

namespace Ui {
class Tomatime;
}

class Tomatime : public QMainWindow
{
    Q_OBJECT

public:
    explicit Tomatime(QWidget *parent = 0);
    ~Tomatime();

    void setWorkingTime(int nWorkingTime);
    void setBreakTime(int nBreakTime);
    void setLongBreakTime(int nLongBreakTime);

    int getWorkingTime();
    int getBreakTime();
    int getLongBreakTime();


protected:
    void closeEvent(QCloseEvent *event);

protected slots:
    void clickedStartButton();
    void clickedStopButton();
    void clickedSettingsButton();
    void setLcdNumber();
    void checkTime();
    void settingsMenu();
    void aboutMenu();

public slots:
    void setTimer(int minutes, int seconds);

private:
    Ui::Tomatime *ui;
    QTimer* timer;
    QTime*  timeValue;

    int timerNumber;
    int totalSecond;
    int startMilliseconds;

    int workingTime;
    int breakTime;
    int longBreakTime;
    int workingCount;
    int timerMode;

    void createActions();
    void createTrayIcon();
    void showMessageTray(QString message);
    void showMessageRemainingTime();
    void pomodoroIsOver();
    void startWork();
    void takeBreak();
    void takeLongBreak();



    QAction *restoreAction;
    QAction *quitAction;
    QAction *settingsMenuAction;
    QSystemTrayIcon *trayIcon;
    QMenu   *trayIconMenu;

    Settings *settingDialog;
    About   *aboutWidget;
};

#endif // TOMATIME_H
