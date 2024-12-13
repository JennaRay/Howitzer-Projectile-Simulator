/**********************************************************************
 * Suurce File:
 *    SIMULATION
 * Author:
 *    <your name here>
 * Summary:
 *    Execute one simulation of a projectile being fired.
 ************************************************************************/

 #include "simulation.h"  // for SIMULATION
#include "ground.h"
#include "howitzer.h"
#include "projectile.h"
#include "uiInteract.h"

void Simulator::setup()
{
   // generate position for the howitzer
   howitzer.generatePosition(posUpperRight);

   // reset the ground
   ground.reset(howitzer.getPosition());

   // reset the projectile
   projectile.reset();
}

