/** @file main.cpp
*   @brief This is a main file to instanstiate the first window
*
*   main program starts the main window via a Qappliction
*   @author Bradley Assaly-Nesrallah
*/

#include "mainwindow.h"  //include header and libraries
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);             //create instance of the mainwindow
    MainWindow w;
    w.show();
    return a.exec();
}
