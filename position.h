/***********************************************************************
 * Header File:
 *    POSITION
 * Author:
 *    <your name here>
 * Summary:
 *    Everything we need to know about a location on the screen.
 ************************************************************************/


#pragma once

#include <iostream> 
#include <cmath>

class TestPosition;
class Acceleration;
class Velocity;
class TestGround;
class TestHowitzer;
class TestProjectile;


/*********************************************
 * Position
 * A single position on the field in Meters
 *********************************************/
class Position
{
public:
   friend ::TestPosition;
   friend ::TestGround;
   friend ::TestHowitzer;
   friend ::TestProjectile;


   // constructors
   Position() : x(0), y(0) {}
   Position(double x, double y);
   Position(const Position& pt) : x(pt.getMetersX()), y(pt.getMetersY()) {}
   Position& operator = (const Position& pt);

   // getters
   double getMetersX()       const { return this->x; }
   double getMetersY()       const { return this->y; }
   double getPixelsX()       const { return this->x / this->metersFromPixels; }
   double getPixelsY()       const { return this->y / this->metersFromPixels; }
   double getZoom()          const { return this->metersFromPixels; }

   // setters
   void setZoom(double z) { this->metersFromPixels = z; }
   void setMeters(double xMeters, double yMeters) { this->x = xMeters; this->y = yMeters; }
   void setMetersX(double xMeters) { this->x = xMeters; }
   void setMetersY(double yMeters) { this->y = yMeters; }
   void setPixelsX(double xPixels) { x = xPixels * metersFromPixels; }
   void setPixelsY(double yPixels) { y = yPixels * metersFromPixels; }
   double addMetersX(double x) { return this->x += x; }
   double addMetersY(double y) { return this->y += y; }
   double addPixelsX(double x) { return this->x += x * metersFromPixels; }
   double addPixelsY(double y) { return this->y += y * metersFromPixels; }
   void add(const Acceleration& a, const Velocity& v, double t);
   void reverse() { x = x * -1; y = y * -1; }



private:
   double x;                 // horizontal position
   double y;                 // vertical position
   static double metersFromPixels;
};



// stream I/O useful for debugging
std::ostream& operator << (std::ostream& out, const Position& pt);
std::istream& operator >> (std::istream& in, Position& pt);


/*********************************************
 * PT
 * Trivial point
 *********************************************/
struct PT
{
   double x;
   double y;
};



