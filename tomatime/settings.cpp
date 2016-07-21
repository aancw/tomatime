/*

    Copyright (C) 2016 Sucipto < chip@pringstudio.com >

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

#include "settings.h"
#include "ui_settings.h"

Settings::Settings(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Settings)
{
    QCoreApplication::setOrganizationName("Tomatime");
    QCoreApplication::setOrganizationDomain("github.com");
    QCoreApplication::setApplicationName("tomatime");

    ui->setupUi(this);

    // Initialize value from setting
    QSettings setting;
    ui->spinWorking->setValue(setting.value("time/working", 25).toInt());
    ui->spinBreak->setValue(setting.value("time/break", 5).toInt());
    ui->spinLongBreak->setValue(setting.value("time/longbreak", 15).toInt());

    // Connect to main window
    //connect(this,SIGNAL(emitTimerValue(int)),parent,SLOT(setw));
}

Settings::~Settings()
{
    delete ui;
}


void Settings::on_btnSave_clicked()
{
    QSettings setting;
    setting.setValue("time/working",ui->spinWorking->value());
    setting.setValue("time/break",ui->spinBreak->value());
    setting.setValue("time/longbreak",ui->spinLongBreak->value());

    // Change variable for realtime
    emit emitTimerValue(12);
    this->close();
}

void Settings::on_btnCancel_clicked()
{
    this->close();
}
