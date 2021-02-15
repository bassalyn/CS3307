/** @file audioprocessing.h
*   @brief This is a header file to calculate a source from beacon and sound volumes
*
*   This file has conversions of decibel to distance, uses beacon struct to hold values
*   and trilaterates to determine the coordinate of the source.
*   @author Bradley Assaly-Nesrallah
*/
#ifndef AUDIOPROCESSING_H
#define AUDIOPROCESSING_H

/**
*   @brief This is a class to hold the data of a beacon
*
*   contains the x,y coordinates as int and a double for distance
*/
class beacon{
/*
*  variables x,y coordiantes and distance
*/
private:
  int x,y;
  double distance;

public:
/**
*  @brief construct for beacon
*  @return void
*/
  beacon(int x1, int y1, double d1);

/**
*  @brief getter for x value
*  @return int x
*/
  int getX();

/**
*  @brief getter for y value
*  @return int y
*/
  int getY();

/**
*  @brief getter for x value
*  @return int x
*/

  double getD();
};

/**
*   @brief This is a class to hold the data of an ordered pair
*
*   contains the x,y coordinates as ints
*/
class orderedPair{
private:
  int x, y;

public:
/**
*  @brief construct for ordered pair
*  @return void
*/
  orderedPair(int x1, int y1);

/**
*  @brief getter for x value
*  @return int x
*/
  int getX();

/**
*  @brief getter for y value
*  @return int y
*/
  int getY();
};

/**
*   @brief method to convert a decibel input to a distance using inversquare law
*
*   Uses the standard distance and volume, and by inverse square law computes distance
*   @param decibels is the volume recorded from a beacon
*   @return the distance in a double to the source from a beacon
*   @author Bradley Assaly-Nesrallah
*/
double inverseSquare(double decibels);

/**
*   @brief method trilaterate determine source from three beacons
*
*   Uses the trilateration algorithm to determine source of three beacons with known distance to source
*   @param beacon1 is the coordinate and distance to source of first beacon
*   @param beacon2 is the coordinate and distance to source of second beacon
*   @param beacon3 is the coordinate and distance to source of third beacon
*   @return ordered pair representing coordinates fo source
*   @author Bradley Assaly-Nesrallah
*/
orderedPair trilateration(beacon beacon1, beacon beacon2, beacon beacon3);

/**
*   @brief method to pass coordinates and distances to trilaterate algorithm
*
*   Use inverseSquare, constructors of beacon and trilaterate to find source coordinates
*   @param x1 is the x coordinate of first beacon
*   @param y1 is the y coordinate of first beacon
*   @param x2 is the x coordinate of second beacon
*   @param y2 is the y coordinate of second beacon
*   @param x3 is the x coordinate of third beacon
*   @param y3 is the y coordinate of third beacon
*   @param d1 is the decibel recording from beacon1
*   @param d2 is the decibel recording from beacon2
*   @param d3 is the decibel recording from beacon3
*   @return ordered pair representing coordinates fo source
*   @author Bradley Assaly-Nesrallah
*/
orderedPair audioprocessing(int x1,int y1,int x2,int y2,int x3,int y3,double d1, double d2, double d3);

#endif
