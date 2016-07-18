#include "tomatime.h"
#include "ui_tomatime.h"



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
   QWidget::setWindowTitle("Pomodoro Start - Tomatime");

   // Start pomodoro timer
   setTimer(1,0);
   timer->start(1000);
}
void Tomatime::setLcdNumber()
{
    timeValue->setHMS(0,timeValue->addSecs(-1).minute(),timeValue->addSecs(-1).second());
    ui->lcdNumber->display(timeValue->toString());

    checkTime();
}
void Tomatime::setTimer(int minutes, int seconds)
{
    timer = new QTimer();
    timeValue = new QTime(0,minutes,seconds);
    ui->lcdNumber->display(timeValue->toString());
    QObject::connect(timer,SIGNAL(timeout()),this,SLOT(setLcdNumber()));
    totalSecond = (minutes * 60) + seconds;
    startMilliseconds = totalSecond * 1000;
}
void Tomatime::checkTime()
{
    int Seconds;
    if (startMilliseconds - 1000 >= 0) //If not timeout
     {
         startMilliseconds = startMilliseconds - 1000; //Reduce the milliseconds with 1 secod (1000)
         Seconds = ((startMilliseconds % (1000*60*60)) % (1000*60)) / 1000;

         if (startMilliseconds <=0) //If timeout
         {
             timer->stop(); //Stop the timer
             QMessageBox msgBox;
             msgBox.setText("TimeOut");
             msgBox.exec();  //Display timeout message
         }
     }
     else
     {
         timer->stop(); //Stop the timer
         QMessageBox msgBox;
         msgBox.setText("TimeOut");
         msgBox.exec();//Display timeout message
     }
}
