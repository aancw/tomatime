#ifndef ABOUT_H
#define ABOUT_H

#include <QMainWindow>
#include <QRect>
#include <QDesktopWidget>

namespace Ui {
class About;
}

class About : public QMainWindow
{
    Q_OBJECT

public:
    explicit About(QWidget *parent = 0);
    ~About();

private:
    Ui::About *ui;
};

#endif // ABOUT_H
