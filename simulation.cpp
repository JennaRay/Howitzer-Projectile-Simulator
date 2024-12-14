#include "simulation.h"  // for SIMULATION
#include "ground.h"      // for Ground class
#include "howitzer.h"    // for Howitzer class
#include "uiDraw.h"      // for ogstream
#include "projectile.h"  // for Projectile class
#include "angle.h"       // for Angle class
#include "uiInteract.h"

// Main simulation function
void runSimulation(const Position& posUpperRight)
{
   Ground ground(posUpperRight);
   Position howitzerPos;
   ground.reset(howitzerPos);

   Projectile projectile;
   bool projectileFired = false;

   ogstream gout;
   bool isRunning = true;
   Angle howitzerAngle;
   double simulationTime = 0.0;

   while (isRunning)
   {
      gout.clear();

      // Draw the ground and howitzer
      ground.draw(gout);
      gout.drawHowitzer(howitzerPos, howitzerAngle.getDegrees(), simulationTime);

      // Draw the projectile if fired
      if (projectileFired)
      {
         projectile.advance(simulationTime);
         gout.drawProjectile(projectile.getPosition(), simulationTime); // Updated to draw the projectile
      }

      // Handle user input
      char input;
      std::cout << "Press U to increase angle, D to decrease, F to fire, or Q to quit: ";
      std::cin >> input;

        if (input == 'U' || input == 'u')
            howitzerAngle.add(0.1);
        else if (input == 'D' || input == 'd')
            howitzerAngle.add(-0.1);
        else if ((input == 'F' || input == 'f') && !projectileFired)
        {
            Velocity initialVelocity;
            projectile.fire(howitzerAngle, howitzerPos, initialVelocity, simulationTime);
            projectileFired = true;
        }
        else if (input == 'Q' || input == 'q')
        {
            isRunning = false;
        }


    }
}

void Simulator::setup()
{
    // generate position for the howitzer
    howitzer.generatePosition(posUpperRight);

    // reset the ground
    ground.reset(howitzer.getPosition());

    // reset the projectile
    projectile.reset();
}

void Simulator::handleInput(const Interface *pUI)
{
   if (pUI->isLeft())
      howitzer.rotate(-0.05);
   if (pUI->isRight())
      howitzer.rotate(0.05);
   if (pUI->isUp() && howitzer.isRight())
      howitzer.raise(0.003);
   else if (pUI->isUp() && howitzer.isLeft())
      howitzer.raise(-0.003);
   if (pUI->isDown() && howitzer.isRight())
      howitzer.raise(-0.003);
   else if (pUI->isDown() && howitzer.isLeft())
      howitzer.raise(0.003);
   if (pUI->isSpace())
   {  
      if (!projectile.checkIsFired())
      {
         Velocity velocity;
         velocity.set(howitzer.getElevation(), howitzer.getMuzzleVelocity());
         projectile.fire(howitzer.getElevation(), howitzer.getPosition(), velocity, simulationTime);
         simulationTime = 0.0;
      }
      
   }
}
