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

namespace Ui {
class Tomatime;
}

class Tomatime : public QMainWindow
{
    Q_OBJECT

public:
    explicit Tomatime(QWidget *parent = 0);
    ~Tomatime();
    QTimer* timer;
    QTime*  timeValue;
    int timerNumber;
    int totalSecond;
    int startMilliseconds;

private slots:
    void clickedStartButton();
    void setLcdNumber();
    void setTimer(int minutes, int seconds);
    void checkTime();
private:
    Ui::Tomatime *ui;
};

#endif // TOMATIME_H
