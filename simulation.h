/**********************************************************************
 * Header File:
 *    SIMULATION
 * Author:
 *    <your name here>
 * Summary:
 *    Execute one simulation of a projectile being fired.
 ************************************************************************/

#pragma once
#include "position.h"
#include "uiDraw.h"
#include "ground.h"
#include "howitzer.h"
#include "projectile.h"
#include "uiInteract.h"

 /*********************************************
  * Simulation
  * Execute one simulation of a projectile being fired
  *********************************************/
class Simulator
{
public:
   Simulator(const Position& posUpperRight) : ground(Ground(posUpperRight)), howitzer(Howitzer()), projectile(Projectile()), posUpperRight(posUpperRight)  {};
   void setup();
   void draw(ogstream& gout, double time) const 
   {
      ground.draw(gout);
      howitzer.draw(gout, simulationTime);
      projectile.draw(gout, simulationTime);
   };
   Position& getPos() { return posUpperRight; };
   void handleInput(const Interface* pUI);
   void advance()
   { 
      projectile.advance(simulationTime); 
      if (projectile.checkIsFired())
      {
         simulationTime += 0.1;
         if (ground.getElevationMeters(projectile.getPosition()) <= 0)
         {
            projectile.reset();
            simulationTime = -1.0;
         }
      }
   };
private:
   Ground ground;
   Howitzer howitzer;
   Projectile projectile;
   Position posUpperRight;
   double simulationTime = -1.0;
};
