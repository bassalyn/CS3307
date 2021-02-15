This is the final version of the project implemented using QT gui
all of the required functionality is implemented into the application.
The QT gui and QcustomPlot libraries are used.
First is the login/account management page with sql access to user db.
Second after logging in is the results, tracking, and visual display interface.

The complete application can be run by using the following commands to compile the QT project

qmake -3307group.pro
qmake
make

There is an accompanying SQL sqlite database 3307.db with two tables:

user (userID varchar(9), username varchar(30), password varchar(30), PRIMARY KEY (userID))

result (x1 int, y1 int, x2 int, y2 int, x3 int, y3 int, xsource int, ysource int, userID varchar(9), trialID int, PRIMARY KEY (trialID))

these should be in a corresponding folder to the directories directory in mainwindow and locationtracker
