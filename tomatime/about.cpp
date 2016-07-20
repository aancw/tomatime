#include "about.h"
#include "ui_about.h"

About::About(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::About)
{
    ui->setupUi(this);
    // Recenter form
    QRect position = frameGeometry();
    position.moveCenter(QDesktopWidget().availableGeometry().center());
    move(position.topLeft());
}

About::~About()
{
    delete ui;
}
