/** @file displaygraphics.h
*   @brief This is a header file to display the results of the coordinates visually
*
*   Takes the coordinates of each beacon and the sources and displays visually
*   @author Bradley Assaly-Nesrallah
*/

#include <QMessageBox>

#ifndef DISPLAYGRAPHICS_H
#define DISPLAYGRAPHICS_H      //header defines function


/**
*   @brief This is a method to print a graph of the beacons and source
*
*   Loops through and prints + on empty, B on beacon and S on source visually
*   @param x1 is the x coordinate of first beacon
*   @param y1 is the y coordinate of first beacon
*   @param x2 is the x coordinate of second beacon
*   @param y2 is the y coordinate of second beacon
*   @param x3 is the x coordinate of third beacon
*   @param y3 is the y coordinate of third beacon
*   @param xsource is the x coordinate of the source
*   @param ysource is the y coordinate of the source
*   @return void
*   @author Bradley Assaly-Nesrallah
*/
void printgraph(int x1, int y1, int x2, int y2, int x3, int y3, int xsource, int ysource);

#endif
