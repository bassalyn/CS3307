/** @file locationtracker.c
*   @brief This is a cpp file to location of the source and perform and display computation
*
*   Takes the coordinates of each beacon and the sources and displays visually,
*   also determines coordinates and outputs the source
*   @author Bradley Assaly-Nesrallah
*/

#include <QMessageBox>
#include "locationtracker.h"
#include "ui_locationtracker.h"     //Include Qt libraries and header files
#include "audioprocessing.h"
#include "mainwindow.h"
#include "displaygraphics.h"


Locationtracker::Locationtracker(QWidget *parent) :             //set up the initial instance of locationtracer
    QDialog(parent),
    ui(new Ui::Locationtracker)
{
    ui->setupUi(this);                                          //create instance of blank plot
    makePlot(0,0,0,0,0,0,0,0);

    mydb=QSqlDatabase::addDatabase("QSQLITE");
    mydb.setDatabaseName("/Users/bradley/3307.db");             //connect to db

    if(!mydb.open())
        ui->label->setText("Failed to open the database");
    else
        ui->label->setText("Connected to database");
}

Locationtracker::~Locationtracker()                                     //destructor
{
    delete ui;
}


void Locationtracker::on_pushButton_clicked()       //first pushbutton to compute audioprocessing
{
    QString x1,x2,x3,y1,y2,y3,d1,d2,d3,userID,trialID;      //string to parse from gui
    x1=ui->lineEdit_x1->text();
    x2=ui->lineEdit_x2->text();
    x3=ui->lineEdit_x3->text();
    y1=ui->lineEdit_y1->text();
    y2=ui->lineEdit_y2->text();
    y3=ui->lineEdit_y3->text();
    d1=ui->lineEdit_d1->text();                                 //parses inputs from the gui
    d2=ui->lineEdit_d2->text();
    d3=ui->lineEdit_d3->text();
    userID=ui->lineEdit_userID->text();
    trialID=ui->lineEdit_trialID->text();

    try{
        bool ok1,ok2,ok3,ok4,ok5,ok6,ok7,ok8,ok9;       //bools to store try catch errors
        orderedPair pair = audioprocessing(x1.toInt(&ok1,10),y1.toInt(&ok2,10),x2.toInt(&ok3,10),y2.toInt(&ok4,10),x3.toInt(&ok5,10),y3.toInt(&ok6,10),d1.toDouble(&ok7),d2.toDouble(&ok8),d3.toDouble(&ok9));
        QString temp = "The source coordinate was (" + QString::number(pair.getX()) + "," + QString::number(pair.getY()) + ")";
        QMessageBox::information(this,tr("Success"),temp);          //computes sources calls audioprocessing

    MainWindow conn;
    if(!conn.connOpen()){
        qDebug()<<"Failed to open database";            //checks if db connection
        return;
    }
    conn.connOpen();
    QSqlQuery qry;          //prepares insert query using parsed data

    qry.prepare("insert into result values('"+x1+"','"+y1+"','"+x2+"','"+y2+"','"+x3+"','"+y3+"','"+QString::number(pair.getX())+"','"+QString::number(pair.getY())+"','"+userID+"','"+trialID+"')");
    if(qry.exec()){
        QMessageBox::information(this,tr("Save"),tr("Result Added to Database"));   //if execs adds to db
    }
    else{
        QMessageBox::warning(this,tr("Error"),qry.lastError().text());
    }
    conn.connClose();                                                   //otherwise error message and closes conn
    makePlot(x1.toDouble(&ok1),y1.toDouble(&ok2),x2.toDouble(&ok3),y2.toDouble(&ok4),x3.toDouble(&ok5),y3.toDouble(&ok6),(double)pair.getX(),(double)pair.getY());
                                                        //makes plot
    }catch(const char* msg){
        QMessageBox::warning(this,tr("Error"),msg);         //handles errors
    }


}

void Locationtracker::on_pushButton_2_clicked()         //gui action for push button 2 for sound processing
{
    int d1 = (rand() % 50 );
    int d2 = (rand() % 50 );                            //generates sound data
    int d3 = (rand() % 50 );
    QString temp = "The source audio readings for the beacons were : Beacon 1 ="+ QString::number(d1) + "dB ,Beacon 2=" + QString::number(d2)+"dB, Beacon 3="+QString::number(d3)+"dB";
    QMessageBox::information(this,tr("Success"),temp);          //displays results in Qmessagebox
}


void Locationtracker::on_pushButton_3_clicked()         //gui action for push button 4 to insert into db
{
    QString userID;
    int x1 = (rand() % 40 );
    int x2 = (rand() % 40 );
    int x3 = (rand() % 40 );
    int y1 = (rand() % 40 );
    int y2 = (rand() % 40 );                                //generates coordinates and sound data
    int y3 = (rand() % 40 );
    int d1 = (rand() % 50 );
    int d2 = (rand() % 50 );
    int d3 = (rand() % 50 );
    userID=ui->lineEdit_userID3->text();                        //parses user id
    int trialID= rand();
    try{
    orderedPair pair = audioprocessing(x1,y1,x2,y2,x3,y3,d1,d2,d3);         //computes source location
    QString temp = "The source coordinate was (" + QString::number(pair.getX()) + "," + QString::number(pair.getY()) + ")";
    QMessageBox::information(this,tr("Success"),temp);              //outputs result
    MainWindow conn;
    if(!conn.connOpen()){
        qDebug()<<"Failed to open database";            //handles error
        return;
    }
    conn.connOpen();
    QSqlQuery qry;                                          //prepares insert query

    qry.prepare("insert into result values('"+QString::number(x1)+"','"+QString::number(y1)+"','"+QString::number(x2)+"','"+QString::number(y2)+"','"+QString::number(x3)+"','"+QString::number(y3)+"','"+QString::number(pair.getX())+"','"+QString::number(pair.getY())+"','"+userID+"','"+QString::number(trialID)+"')");
    if(qry.exec()){
        QMessageBox::information(this,tr("Save"),tr("Result Added to Database"));       //inserts to database
    }
    else{
        QMessageBox::warning(this,tr("Error"),qry.lastError().text());      //plots the results with makeplot
    }
    makePlot((double) x1,(double) y1,(double)x2,(double)y2,(double)x3,(double)y3,(double)pair.getX(),(double)pair.getY());

    }catch(const char* msg){
        QMessageBox::warning(this,tr("Error"),msg);                         //handles errors
    }
}


void Locationtracker::on_pushButton_4_clicked()         //function for pushbutton 4 displays results in sql database
{
    MainWindow conn;
    QSqlQueryModel * modal=new QSqlQueryModel();                    //creates model

    conn.connOpen();                                            //connects to db and queries
    QSqlQuery* qry = new QSqlQuery(conn.mydb);
    qry->prepare("select * from result");
    qry->exec();                                            //displays results
    modal->setQuery(*qry);
    ui->tableView->setModel(modal);

    conn.connClose();
    qDebug() <<(modal->rowCount());                         //closes conn and debugs
}


void Locationtracker::makePlot(double x1, double y1, double x2, double y2, double x3, double y3, double xs, double ys ){    //makes plot

    // create graph and assign data to it:
    qv_x.clear();
    qv_y.clear();
    qv_sy.clear();                          //clears current data in table
    qv_sx.clear();
    ui->customPlot->addGraph();
    ui->customPlot->graph(0)->setScatterStyle(QCPScatterStyle::ssDiamond);
    ui->customPlot->graph(0)->setLineStyle(QCPGraph::lsNone);           //defines graph visually
    ui->customPlot->addGraph();
    ui->customPlot->graph(1)->setScatterStyle(QCPScatterStyle::ssStar);
    ui->customPlot->graph(1)->setLineStyle(QCPGraph::lsNone);
    qv_sx.append(xs);
    qv_sy.append(ys);
    qv_x.append(x1);                //adds values to table
    qv_y.append(y1);
    qv_x.append(x2);
    qv_x.append(y2);
    qv_y.append(x3);
    qv_y.append(y3);
    ui->customPlot->graph(0)->setData(qv_x,qv_y);
    ui->customPlot->graph(1)->setData(qv_sx,qv_sy);     //plots values
    // give the axes some labels:
    ui->customPlot->xAxis->setLabel("x");       //sets label
    ui->customPlot->yAxis->setLabel("y");
    // set axes ranges, so we see all data:
    ui->customPlot->xAxis->setRange(0, 50);         //sets range
    ui->customPlot->yAxis->setRange(0, 50);
    ui->customPlot->replot();                       //replots
}
