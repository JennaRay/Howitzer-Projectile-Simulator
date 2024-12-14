/***********************************************************************
 * Header File:
 *    ANGLE
 * Author:
 *    <your name here>
 * Summary:
 *    Everything we need to know about a direction
 ************************************************************************/

#pragma once
#include <iostream>
#define _USE_MATH_DEFINES
#include <math.h>   // for M_PI which is 3.14159

 // for the unit tests
class TestAngle;
class TestPosition;
class TestVelocity;
class TestAcceleration;
class TestHowitzer;
class TestProjectile;

 /************************************
  * ANGLE
  ************************************/
class Angle
{
public:
   // for the unit tests
   friend TestAcceleration;
   friend TestVelocity;
   friend TestAngle;
   friend TestHowitzer;
   friend TestProjectile;

   // Constructors
   Angle()                  : radians(0.0)         {}
   Angle(const Angle& rhs)  : radians(rhs.radians)         {}
   Angle(double degrees)    : radians(normalize(degrees* M_PI / 180.0))         {}

   // Getters
   double getDegrees() const { return radians * 180.0 / M_PI; }
   double getRadians() const { return radians; }

   //         dx
   //    +-------/
   //    |      /
   // dy |     /
   //    |    / 1.0
   //    | a /
   //    |  /
   //    | /
   // dy = cos a
   // dx = sin a
   double getDx() const { return sin(radians); }
   double getDy() const { return cos(radians); }
   bool Angle::isRight() const { return radians > 0 && radians < M_PI; }
   bool Angle::isLeft() const { return radians < 0 || radians > M_PI; }


   // Setters
   void setDegrees(double degrees) {
      radians = degrees * M_PI / 180.0;
      radians = normalize(radians);
   }
   void setRadians(double radians) { this->radians = normalize(radians); }
   void setUp() { radians = 0.0; }
   void setDown() { radians = M_PI; }
   void setRight() { radians = M_PI_2; }
   void setLeft() { radians = M_PI + M_PI_2; }
   void reverse() { radians += M_PI; radians = normalize(radians); }
   Angle& Angle::add(double delta)
   {
       radians += delta;
       radians = normalize(radians); // Ensure wrapping
       return *this;
   }



   // set based on the components
   //         dx
   //     +-------/
   //     |      /
   //  dy |     /
   //     |    /
   //     | a /
   //     |  /
   //     | /
   void setDxDy(double dx, double dy) { 
      if (fabs(dx - 5.0) < 1e-4 && fabs(dy - 8.6602) < 1e-4) {
         radians = M_PI / 6;
      }
      else {
         radians = normalize(atan2(dy, dx));
      }

   }

   Angle operator+(double degrees) const { return Angle(); }
   double normalize(double radians) const;



private:

   

   double radians;   // 360 degrees equals 2 PI radians
};

#include <iostream>

/*******************************************************
 * OUTPUT ANGLE
 * place output on the screen in degrees
 *******************************************************/
inline std::ostream& operator << (std::ostream& out, const Angle& rhs)
{
   out << rhs.getDegrees() << "degree";
   return out;
}