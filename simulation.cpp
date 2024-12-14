#include "simulation.h"  // for SIMULATION
#include "ground.h"      // for Ground class
#include "howitzer.h"    // for Howitzer class
#include "uiDraw.h"      // for ogstream
#include "projectile.h"  // for Projectile class
#include "angle.h"       // for Angle class

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
            initialVelocity.setSpeed(100.0); // Replace with logic for initial velocity
            projectile.fire(howitzerAngle, howitzerPos, initialVelocity, simulationTime);
            projectileFired = true;
        }
        else if (input == 'Q' || input == 'q')
        {
            isRunning = false;
        }

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

