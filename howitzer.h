/**********************************************************************
 * Header File:
 *    HOWITZER
 * Author:
 *    <your name here>
 * Summary:
 *    Everything we need to know about a howitzer (aka the gun)
 ************************************************************************/

#pragma once

#include <list>
#include "angle.h"
#include "position.h"
#include "velocity.h"
#include "physics.h"
#include "uiDraw.h"


#pragma once

#define DEFAULT_MUZZLE_VELOCITY   827.00     // m/s
#define MIN_ELEVATION 0
#define MAX_ELEVATION (M_PI / 2)


 /**********************************************************************
  * Header File:
  *    HOWITZER
  * Author:
  *    <your name here>
  * Summary:
  *    Everything we need to know about a howitzer (aka the gun)
  ************************************************************************/

#pragma once

#include <list>
#include "angle.h"
#include "position.h"
#include "velocity.h"
#include "physics.h"
#include "uiDraw.h"


#pragma once

#define DEFAULT_MUZZLE_VELOCITY   827.00     // m/s


class TestHowitzer;

/*********************************************
 * Howitzer
 * Everything we need to know about a howitzer (aka the gun)
 *********************************************/
class Howitzer
{
public:
    // for unit tests
    friend ::TestHowitzer;
    double radians;

    // default constructor
    Howitzer() : muzzleVelocity(DEFAULT_MUZZLE_VELOCITY), elevation(45.0), radians(0.0) {}

    // draw
    void draw(ogstream& gout, double flightTime) const
    {
        gout.drawHowitzer(position,
            elevation.getRadians(),
            flightTime);
    }

    // where is the howitzer at right now?
    Position& getPosition() { return position; }

    // generate a new position for the howitzer
    void generatePosition(const Position& posUpperRight)
    {
        double xPixels = random(posUpperRight.getPixelsX() * 0.1,
            posUpperRight.getPixelsX() * 0.9);
        position.setPixelsX(xPixels);
        position.setPixelsY(0);
    }

    // get the muzzle velocity
    double getMuzzleVelocity() const { return muzzleVelocity; }
    bool isRight() const { return elevation.isRight(); }
    bool isLeft() const { return elevation.isLeft(); }
    // move the angle of the howitzer
    void rotate(double radian)
    {
        elevation.setRadians(elevation.getRadians() + radian);
        elevation.setRadians(elevation.normalize(elevation.getRadians()));
    }


    // raise (or lower) the howitzer
    void raise(double radian)
    {
        elevation.setRadians(elevation.getRadians() - radian);

    }

   


    void setMuzzleVelocity(double velocity) {
        if (velocity <= 0)
            throw std::invalid_argument("Muzzle velocity must be positive.");
        muzzleVelocity = velocity;
    }

    // get the elevation
    Angle& getElevation() { return elevation; }

private:
    Position position;      // initial position of the projectile
    double muzzleVelocity;  // muzzle velocity, defaults to 827.0 m/s
    Angle elevation;        // the elevation of the howitzer where 0 is up and positive is right.
	Angle angle;            // the angle of the howitzer
};