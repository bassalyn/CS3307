/** @file locationtracker.h
*   @brief This is a header file to location of the source and perform and display computation
*
*   Takes the coordinates of each beacon and the sources and displays visually,
*   also determines coordinates and outputs the source
*   @author Bradley Assaly-Nesrallah
*/

#ifndef LOCATIONTRACKER_H

#define LOCATIONTRACKER_H

#include <QDialog>
#include <QtSql>
#include <QtDebug>      //include Qt libraries
#include <QFileInfo>

namespace Ui {

/**
*   @brief This is a class to track the location of the source and implement the gui
*
*   has all of the methods to graphically display and interface with both the user and sql
*/
class Locationtracker;
}

/**
*   @brief The locationtracker class inherits the features of qt dialog
*
*   has all of the methods of the dialog functionality of Qdialog in QT gui
*/
class Locationtracker : public QDialog
{
    Q_OBJECT

public:
    /**
    *   @brief This is a constructor for the locationtracker
    *
    *   @param nullptr from a parent Qwidget object
    */
    explicit Locationtracker(QWidget *parent = nullptr);
    /**
    *   @brief This is a destructor for locationtracker
    *
    *   basic destructor for locationtracker
    */
    ~Locationtracker();

private slots:

    /**
    *   @brief This is a function to implement gui action when pushbutton is activated for first call
    *
    *   this function is used to interface with gui when performing computation action,
    *   also interfaces with the sql database, and calls functions to modify the data
    *   @return void
    */
    void on_pushButton_clicked();

    /**
    *   @brief This is a function to implement gui action when pushbutton2 when user activates button2
    *
    *   this function is used to interface with gui when performing an action
    *   interfaces with the sqlite database, calls certain computations to obtain and modify the data
    *   also stores results to database, which can be viewed visually
    *   @return void
    */
    void on_pushButton_2_clicked();

    /**
    *   @brief This is a function to implement gui action when pushbutton3 when user activates button3
    *
    *   this function is used to interface with gui when performing an action
    *   interfaces with the sqlite database, calls the audioprocessing and display functions
    *   also stores results to database
    *   @return void
    */
    void on_pushButton_3_clicked();



    /**
    *   @brief This is a function to implement gui action when pushbutton4 when user activates button4
    *
    *   this function is used by the user to visualize the sql database table storing the results of each computation
    *   every time this is done it refreshes the results for each user
    *   @return void
    */
    void on_pushButton_4_clicked();


    /**
    *   @brief This is a function to make a visual plot given input coordinates
    *
    *   this function is used by the user to create a scatter plot for all three beacons
    *   and also displays the source distinctly, returns each upon call
    *   @param x1 double to represent the x coordinate of beacon 1
    *   @param x2 double to represent the x coordinate of beacon 2
    *   @param x3 double to represent the x coordinate of beacon 3
    *   @param y1 double to represent the y coordinate of beacon 1
    *   @param y2 double to represent the y coordinate of beacon 2
    *   @param y3 double to represent the y coordinate of beacon 3
    *   @param xs double to represent the x coordinate of the source
    *   @param ys double to represent the y coordinate of the source
    *   @return void
    */
    void makePlot(double x1, double y1, double x2, double y2, double x3, double y3, double xs, double ys );


private:
    Ui::Locationtracker *ui;
    QSqlDatabase mydb;
    QVector<double> qv_x, qv_y, qv_sx,qv_sy;
};

#endif // LOCATIONTRACKER_H
