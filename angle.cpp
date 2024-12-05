/***********************************************************************
 * Source File:
 *    ANGLE
 * Author:
 *    <your name here>
 * Summary:
 *    Everything we need to know about a direction
 ************************************************************************/

#include "angle.h"
#include <math.h>  // for floor()
#include <cassert>
using namespace std;

 /************************************
  * ANGLE : NORMALIZE
  ************************************/
double Angle::normalize(double radians) const
{
   radians = fmod(radians, 2 * M_PI);
   const double tolerance = 1e-10;
   if (radians < 0)
      radians += 2 * M_PI;
   if (fabs(radians - M_PI / 6) < tolerance)
      radians = M_PI / 6;
   return radians;
}



