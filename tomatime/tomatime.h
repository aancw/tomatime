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

class QAction;
class QMenu;

namespace Ui {
class Tomatime;
}

class Tomatime : public QMainWindow
{
    Q_OBJECT

public:
    explicit Tomatime(QWidget *parent = 0);
    ~Tomatime();

protected:
    void closeEvent(QCloseEvent *event);

private slots:
    void clickedStartButton();
    void setLcdNumber();
    void setTimer(int minutes, int seconds);
    void checkTime();

private:
    Ui::Tomatime *ui;
    QTimer* timer;
    QTime*  timeValue;
    int timerNumber;
    int totalSecond;
    int startMilliseconds;

    void createActions();
    void createTrayIcon();
    void showMessageTray();
    void showMessageRemainingTime();
    void pomodoroIsOver();

    QAction *restoreAction;
    QAction *quitAction;
    QSystemTrayIcon *trayIcon;
    QMenu   *trayIconMenu;
};

#endif // TOMATIME_H
