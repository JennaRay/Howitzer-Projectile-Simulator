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
#include <iomanip>

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
   void displayStats(ogstream& gout)
   {
      double altitude  = ground.getElevationMeters(projectile.getPosition());
      double speed = projectile.getVelocity().getSpeed();
      double distance = howitzer.getPosition().getMetersX() - projectile.getPosition().getMetersX();
      double hangTime = simulationTime;

      Position posUpperLeft = Position(23000, 19000);
      gout.setPosition(posUpperLeft);
      gout << std::fixed << std::setprecision(1);
      gout << "Altitude: " << altitude << "m\n";
      gout << "Speed: " << speed << "m/s\n";
      gout << "Distance: " << distance << "m\n";
      gout << "Hang Time: " << hangTime << "s";
      
   };
   Position& getPos() { return posUpperRight; };
   void handleInput(const Interface* pUI);
   void advance()
   { 
      projectile.advance(simulationTime); 
      if (projectile.checkIsFired())
      {
         simulationTime += 0.1;
      }
   };
private:
   Ground ground;
   Howitzer howitzer;
   Projectile projectile;
   Position posUpperRight;
   double simulationTime = -1.0;
};
