/** @file mainwindow.h
*   @brief This is a header file to the gui file for the mainwindow and login interface
*
*   interfaces with the database to function as a login and account deletion and hub gui for user
*   @author Bradley Assaly-Nesrallah
*/

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtSql>
#include <QtDebug>              //import Qt libraries and locationtracker header file
#include <QFileInfo>
#include "locationtracker.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE



/**
*   @brief This is a class to visualize a login hub for the user and interface with sql
*
*   has all of the methods to graphically display and interface with both the user and sql
*   as well as login and account deletion features
*/
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    /**
    *   @brief This is a function to close the connection with the sql database
    *
    *   closes the connection with the given database
    *   @return void
    */
    void connClose();

    /**
    *   @brief This is a function to open a connection with the sql database
    *
    *   opens a connection with the sql database
    *   @return boolean to verify if successful (true) otherwise false
    */
    bool connOpen();
    QSqlDatabase mydb;  //global var for databse


public:
    /**
    *   @brief This is a constructor for the mainwindow
    *
    *   @param nullptr from a parent Qwidget object
    */
    MainWindow(QWidget *parent = nullptr);

    /**
    *   @brief This is a basic destructor for the locationtracker
    *
    *   @param nullptr from a parent Qwidget object
    */
    ~MainWindow();

private slots:

    /**
    *   @brief This is a function to implement gui action when pushbutton is activated for first call
    *
    *   this function is used represent a login screen for the gui interface on this window,
    *   also interfaces with the sql database, and calls functions to modify the data
    *   @return void
    */
    void on_pushButton_clicked();

    /**
    *   @brief This is a function to implement gui action when pushbutton2 when user activates button2
    *
    *   this function is used to function as a account creation process for the gui
    *   interfaces with the sqlite database, calls the audioprocessing and display functions
    *   also stores results to database
    *   @return void
    */
    void on_pushButton_2_clicked();

    /**
    *   @brief This is a function to implement gui action when pushbutton3 when user activates button3
    *
    *   this function is used to function as a account deletion process for the gui
    *   interfaces with the sqlite database, calls the audioprocessing and display functions
    *   also stores results to database
    *   @return void
    */
    void on_pushButton_3_clicked();


    /**
    *   @brief This is a function to implement gui action when pushbutton4 when user activates button4
    *
    *   this function is used to display the user table stored in the device
    *   interfaces with the sqlite database, calls the audioprocessing and display functions
    *   also stores results to database
    *   @return void
    */

    void on_pushButton_4_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
