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

 /*********************************************
  * Simulation
  * Execute one simulation of a projectile being fired
  *********************************************/
class Simulator
{
public:
   Simulator(const Position& posUpperRight) : ground(Ground(posUpperRight)), howitzer(Howitzer()), projectile(Projectile()), posUpperRight(posUpperRight)  {};
   void draw(ogstream& gout, double time) const 
   {
      ground.draw(gout);
      howitzer.draw(gout, time);
   };
   Position& getPos() { return posUpperRight; };
private:
   Ground ground;
   Howitzer howitzer;
   Projectile projectile;
   Position posUpperRight;
};
