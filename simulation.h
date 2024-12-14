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
   Simulator(const Position& posUpperRight) : ground(Ground(posUpperRight)), howitzer(Howitzer()), projectile(Projectile()), posUpperRight(posUpperRight) {};
   void setup();
   void draw(ogstream& gout, double time) const
   {
      projectile.draw(gout, simulationTime);
      ground.draw(gout);
      howitzer.draw(gout, simulationTime);
      gout.setPosition(Position(10000, 10000));
      gout << statement;
   };
   void displayStats(ogstream& gout);
   Position& getPos() { return posUpperRight; };
   void handleInput(const Interface* pUI);
   void advance()
   {
      projectile.advance(simulationTime);
      if (projectile.checkIsFired())
      {
         simulationTime += 0.5;

      }
   };
   void checkCollision()
   {
      if (projectile.checkIsFired())
         if (projectile.getPosition().getMetersY() <= 0)
         {
            if (projectile.getPosition().getMetersX() >= ground.getTarget().getMetersX() - 1000 && projectile.getPosition().getMetersX() <= ground.getTarget().getMetersX() + 1000)
            {
               projectile.hitGround();
               displayWin();
               setup();
            }
            else
            {
               projectile.hitGround();
               displayLoss();
               projectile.reset();
               simulationTime = -1.0;
            }
         }
   };
   void displayWin()
   {
      statement = "You hit the target!";
   };
   void displayLoss()
   {
      statement = "you missed the target. Try again!";
   };
private:
   Ground ground;
   Howitzer howitzer;
   Projectile projectile;
   Position posUpperRight;
   char* statement = "";
   double simulationTime = -1.0;
};
