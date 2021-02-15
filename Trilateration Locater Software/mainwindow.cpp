/** @file mainwindow.cpp
*   @brief This is a cpp file to the gui file for the mainwindow and login interface
*
*   interfaces with the database to function as a login and account deletion and hub gui for user
*   @author Bradley Assaly-Nesrallah
*/

#include <QMessageBox>
#include "mainwindow.h"
#include "ui_mainwindow.h"          //includes header and qt libraries


MainWindow::MainWindow(QWidget *parent):            //instantiate the mainwindow
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);                              //setup the ui
    if(!connOpen())
        ui->label->setText("Failed to open the database");      //handle errors
    else
        ui->label->setText("Connected to the database");


}

void MainWindow::connClose(){                               //close sql connection to db
    mydb.close();
    mydb.removeDatabase(QSqlDatabase::defaultConnection);
}

bool MainWindow::connOpen(){                               //open sql connection to db

    mydb=QSqlDatabase::addDatabase("QSQLITE");
    mydb.setDatabaseName("/Users/bradley/3307.db");

    if(!mydb.open()){
        qDebug()<<("Failed to open the database");          //troubleshoot db connection
        return false;
    }
    else{
        qDebug()<<("Connected to database");
        return true;
    }
}

MainWindow::~MainWindow()                   //destructor
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()                //gui interface for pushbutton 1 logs/verify user
{
    QString username,password;
    username=ui->lineEdit_username->text();
    password=ui->lineEdit_password->text();             //parse input text

    if(!connOpen()){
        qDebug()<<"Failed to open database";                //connect to db
        return;
    }
    connOpen();
    QSqlQuery qry;                                      //check if username and password
    if(qry.exec("select * from user where username='"+username +"'and password='"+password+"'")){
        int count=0;
        while(qry.next()){                                  //count instances in db
            count++;
        }
        if(count==1){
            connClose();
            ui->label->setText("username and password is correct");             //if correct and unique opens locationtracker
            this->hide();
            Locationtracker locationtracker;
            locationtracker.setModal(true);
            locationtracker.exec();
        }
        if(count>1)
            ui->label->setText("Duplicate username and password is correct");       //otherwise warns user
        if(count<1)
            ui->label->setText("username and password is invalid");

    }
}

void MainWindow::on_pushButton_2_clicked()                          //gui interface for pushbutton 2 adds user
{
    QString username,password,userID;
    username=ui->lineEdit_username1->text();                        //parses text for button 3
    password=ui->lineEdit_password1->text();
    userID=ui->lineEdit_userID->text();

    if(!connOpen()){
        qDebug()<<"Failed to open database";                        //opens db connection
        return;
    }
    connOpen();
    QSqlQuery qry;

    qry.prepare("insert into user values('"+userID+"','"+username+"','"+password+"')"); //inserts user and id to db
    if(qry.exec()){
        connClose();
        QMessageBox::information(this,tr("Save"),tr("User Added"));                     //informs user of status
    }
    else{
        connClose();
        QMessageBox::warning(this,tr("Error"),qry.lastError().text());
    }
}

void MainWindow::on_pushButton_3_clicked()                  //gui interface for pushbutton 3 deletes user
{
    QString password,userID;
    password=ui->lineEdit_password2->text();
    userID=ui->lineEdit_userID1->text();                        //parses text

    connOpen();
    QSqlQuery qry;

    qry.prepare("delete from user where userID='"+userID+"'and password='"+password+"'");       //deletes user qry
    if(qry.exec()){
        connClose();
        QMessageBox::information(this,tr("Delete"),tr("User Deleted"));         //informs user of result
    }
    else{
        connClose();
        QMessageBox::warning(this,tr("Error"),qry.lastError().text());
    }
}

void MainWindow::on_pushButton_4_clicked()                              //push button 4 displays users from db
{
    MainWindow conn;
    QSqlQueryModel * modal=new QSqlQueryModel();                         //query into db

    conn.connOpen();
    QSqlQuery* qry = new QSqlQuery(conn.mydb);                           //displays user table
    qry->prepare("select username, userID from user");
    qry->exec();
    modal->setQuery(*qry);
    ui->tableView->setModel(modal);                                     //close connection

    conn.connClose();
    qDebug() <<(modal->rowCount());

}
