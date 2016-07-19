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

#include "tomatime.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Tomatime w;
    w.show();


    return a.exec();
}
