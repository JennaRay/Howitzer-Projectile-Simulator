/**********************************************************************
 * Header File:
 *    PROJECTILE
 * Author:
 *    <your name here>
 * Summary:
 *    Everything we need to know about a projectile
 ************************************************************************/

#pragma once

#include <list>
#include "position.h"
#include "velocity.h"
#include "physics.h"
#include "uiDraw.h"
#include "angle.h"
#include "acceleration.h"

#define DEFAULT_PROJECTILE_WEIGHT 46.7       // kg
#define DEFAULT_PROJECTILE_RADIUS 0.077545   // m

// forward declaration for the unit test class
class TestProjectile; 

 /**********************************************************************
  * Projectile
  *    Everything we need to know about a projectile
  ************************************************************************/
class Projectile
{
public:
   // Friend the unit test class
   friend ::TestProjectile;

   // create a new projectile with the default settings
   Projectile() : mass(DEFAULT_PROJECTILE_WEIGHT), radius(DEFAULT_PROJECTILE_RADIUS), isFired(false) {}

   void reset()
   {
      mass = DEFAULT_PROJECTILE_WEIGHT;
      radius = DEFAULT_PROJECTILE_RADIUS;
      flightPath.clear();
      a = Angle();
      pos = Position();
      v = Velocity();
      acceleration = Acceleration();
      isFired = false;
   };

   Position getPosition() const
   {
       return pos; // Return the current position of the projectile
   }
   Velocity getVelocity() const
   {
      return v; // Return the current velocity of the projectile
   }

   // advance the round forward until the next unit of time
   void advance(double simulationTime);


   void fire(const Angle& a, const Position& pos, const Velocity& v, double t)
   {
      this->a = a;
      this->pos = pos;
      this->v = v;
      acceleration = Acceleration();
      acceleration.set(a, v.getSpeed());

      Velocity velocity(v);
      //if (a.isLeft())
      //   velocity.reverse();
      PositionVelocityTime pvt;
      pvt.pos = pos;
      pvt.v = velocity;
      pvt.t = t;
      flightPath.push_back(pvt);

      isFired = true;
   }
   bool checkIsFired() { return isFired; }
   void draw(ogstream& gout, double time) const
   {
      if (flightPath.empty())
         return;
      for (auto i = flightPath.rbegin(); i != flightPath.rend(); ++i)
      {
         gout.drawProjectile(i->pos, time - i->t);
      }
      gout.drawProjectile(flightPath.back().pos, 0);
   }

private:

   // keep track of one moment in the path of the projectile
   struct PositionVelocityTime
   {
      PositionVelocityTime() : pos(), v(), t(0.0) {}
      Position pos;
      Velocity v;
      double t;
   };
   Angle a;
   Position pos;
   Velocity v;
   Acceleration acceleration;
   double mass;           // weight of the M795 projectile. Defaults to 46.7 kg
   double radius;         // radius of M795 projectile. Defaults to 0.077545 m
   std::list<PositionVelocityTime> flightPath;
   bool isFired;
};