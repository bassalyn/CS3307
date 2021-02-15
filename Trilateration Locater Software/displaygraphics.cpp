/** @file displaygraphics.cpp
*   @brief This is a file to display the results of the coordinates visually
*
*   Takes the coordinates of each beacon and the sources and displays visually
*   @author Bradley Assaly-Nesrallah
*/
#include <QMessageBox>
#include <iostream>
#include <fstream>      //include header and libraries
#include "displaygraphics.h"

const int xdistance = 40;  //standard defined x and y distance for max size graph
const int ydistance = 50;



void printgraph(int x1, int y1, int x2, int y2, int x3, int y3, int xsource, int ysource){
   FILE *fptr;
   fptr = fopen("output.txt", "a");
  if (x1 > xdistance || x1 < 0 || x2 > xdistance || x2 < 0 || x3 > xdistance || x3 < 0 ){
    throw "invalid beacon x coordinate";   //if invalid x throws errors
  }
  if (y1 > ydistance || y1 < 0 || y2 > ydistance || y2 < 0 || y3 > xdistance || y3 < 0 ){
    throw "invalid beacon y coordinate"; //if invalid y coordinate throws erros
  }
  if (xsource > xdistance || xsource < 0 || ysource > ydistance || ysource < 0 ){
    throw "invalid source coordinate";  //if invalid source coordinate throws errors
  }
  for (int j = ydistance; j > 0 ; j--){
    for (int i =0 ; i<= xdistance; i++){    //loops through and prints locations
      if ((i == x1 && j == y1) || (i == x2 && j == y2) ||(i == x3 && j == y3)){
        fprintf(fptr,"B");
        printf("B");
      }else if ((i == xsource && j == ysource)){
        printf("S");
        fprintf(fptr,"S");

      }else if (i == xdistance){  //newline at max x distance
        printf("\n");
        fprintf(fptr,"\n");

      }else{
        printf("+");              // + for empty space
        fprintf(fptr,"+");

      }
    }
  }
  printf("\n\n");
}
