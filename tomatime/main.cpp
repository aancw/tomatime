#include "tomatime.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Tomatime w;
    w.show();


    return a.exec();
}
