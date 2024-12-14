/***********************************************************************
 * Header File:
 *    GROUND 
 * Author:
 *    Br. Helfrich
 * Summary:
 *    Represents the ground in the artillery simulation
 ************************************************************************/

#pragma once

#include "position.h"   // for Point
#include "uiDraw.h"

// forward declaration for the Ground unit tests
class TestGround;

 /***********************************************************
  * GROUND
  * The ground class
  ***********************************************************/
class Ground
{
   // unit test access
   friend ::TestGround;

public:
   // the constructor generates the ground
   Ground(const Position &posUpperRight);
   Ground() : ground(nullptr), iHowitzer(0), iTarget(0) {
       int width = static_cast<int>(posUpperRight.getMetersX());
       ground = new double[width];

       // Generate random terrain
       double elevation = 50.0; // Start elevation (meters)
       for (int i = 0; i < width; ++i)
       {
           elevation += (rand() % 21 - 10); // Random changes in elevation
           ground[i] = std::max(0.0, elevation); // Keep elevation non-negative
       }

       // Place the target randomly
       iTarget = rand() % width;

       // Place the howitzer randomly
       iHowitzer = rand() % width;
   }
   
   // reset the game
   void reset(Position& posHowitzer);

   // draw the ground on the screen
   void draw(ogstream& gout) const;

   // determine how high the Point is off the ground
   double getElevationMeters(const Position& pos) const;

   // where the the target located?
   Position getTarget() const;

private:
   double * ground;               // elevation of the ground, in pixels 
   int iTarget;                   // the location of the target, in pixels
   int iHowitzer;                 // the location of the howitzer
   Position posUpperRight;        // size of the screen
};
