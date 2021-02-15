/** @file audioprocessing.cpp
*   @brief This is a file to calculate a source from beacon and sound volumes
*
*   This file has conversions of decibel to distance, uses beacon struct to hold values
*   and trilaterates to determine the coordinate of the source
*   @author Bradley Assaly-Nesrallah
*/

#include <iostream>     //include header and libraries for the file
#include <math.h>
#include "audioprocessing.h"

const double stddecibels = 50.0;    // standard volume and distance for inversesquared
const double stddistance = 10.0;    //defines constants from data for calculations


beacon::beacon(int x1, int y1, double d1){  //constructor
    x = x1;
    y = y1;
    distance = d1;
  }

int beacon::getX(){
    return x;
  }

int beacon::getY(){                     //getters
    return y;
  }

double beacon::getD(){
    return distance;
  }

orderedPair::orderedPair(int x1, int y1){   //constructor
    x = x1;
    y = y1;
  }

int orderedPair::getX(){              //getters
    return x;
  }

int orderedPair::getY(){
    return y;
  }

/*
  takes double decibel input returns distance double
*/
double inverseSquare(double decibels){    //computes distance of inverse squared decibel input
  if (decibels <0){
    return -1.0;                         //if negative returns -1
  }
  double distance;                      //otherwise computes and returns new distance
  distance = stddistance / (sqrt (decibels / stddecibels));
  return distance;
}

/*
trilateration takes three beacons as arguments and returns source coordinate
calculates magnitudes between points names magnitude
compute ex and ey using dot product
intermediate variables i, y, x, j computed,
finally computes final x y value and returns ordered pair object
*/

orderedPair trilateration(beacon beacon1, beacon beacon2, beacon beacon3){
  double p2p1magnitude = sqrt(pow(beacon2.getX()-beacon1.getX(),2)+pow(beacon2.getY()-beacon1.getY(),2));
  double exx = ((beacon2.getX()-beacon1.getX())/p2p1magnitude);
  double exy = ((beacon2.getY()-beacon1.getY())/p2p1magnitude);
  double i = (exx*(beacon3.getX()-beacon1.getX()))+(exy*(beacon3.getY()-beacon1.getY()));
  double p3p1magnitude = (sqrt(pow(beacon3.getX()-beacon1.getX()-i*exx,2)+ pow(beacon3.getY()-beacon3.getY()-i*exy,2)));
  double eyx = (beacon3.getX()-beacon1.getX()-i*exx)/p3p1magnitude;
  double eyy = (beacon3.getY()-beacon1.getY()-i*exy)/p3p1magnitude;
  double j = (eyx*(beacon3.getX()-beacon1.getX()))+(eyy*(beacon3.getY()-beacon1.getY()));
  double x = (pow(beacon1.getD(),2)-pow(beacon2.getD(),2)+pow(p2p1magnitude,2))/(2*p2p1magnitude);
  double y = (pow(beacon1.getD(),2)-pow(beacon3.getD(),2)+pow(i,2)+pow(j,2))/(2*j)- (i*x/j);
  double finalX = beacon1.getX()+x*exx+y*eyx;
  double finalY = beacon1.getY()+x*exy+y*eyy;
  return orderedPair(finalX,finalY);
}

/*
takes all 9 parameters and calls trilaterate, beacon constructor and inverse to return value
outputs ordered pair and handles invalid input of both coordinates and decibels
*/
orderedPair audioprocessing(int x1,int y1,int x2,int y2,int x3,int y3,double d1, double d2, double d3){
  if (x1 < 0 || x2 < 0 || x3 < 0 || y1 < 0 || y2 < 0 || y3 < 0){
      throw "invalid coordinate";     //handles negative coordinates throws
      return orderedPair(-1,-1);
  }
  if (inverseSquare(d1)==-1 ||inverseSquare(d2)==-1 || inverseSquare(d3)==-1){
    throw "invalid decibel";
    return orderedPair(-1,-1);      //throws error if negative coordinate
  }
  return trilateration(beacon(x1,y1,inverseSquare(d1)),beacon(x2,y2,inverseSquare(d2)),beacon(x3,y3,inverseSquare(d3)));
}
