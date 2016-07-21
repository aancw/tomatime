#ifndef SETTINGS_H
#define SETTINGS_H

#include <QDialog>
#include <QSettings>
#include <QDebug>
#include "tomatime.h"

class Tomatime;

namespace Ui {
class Settings;
}

class Settings : public QDialog
{
    Q_OBJECT

public:
    explicit Settings(QWidget *parent = 0);
    ~Settings();

private slots:
    void on_btnSave_clicked();

    void on_btnCancel_clicked();

signals:
    void emitTimerValue(int data);

private:
    Ui::Settings *ui;
    Tomatime *m_Tomatime;
};

#endif // SETTINGS_H
