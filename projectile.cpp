/***********************************************************************
 * Source File:
 *    PROJECTILE
 * Author:
 *    <your name here>
 * Summary:
 *    Everything we need to know about a projectile
 ************************************************************************/


 #include "projectile.h"
 #include "angle.h"
#include "physics.h"
#include "acceleration.h"
#include <iostream>
#include <iomanip>
 using namespace std;

 void Projectile::advance(double simulationTime)
 {
    cout << std::fixed << std::setprecision(4);
    PositionVelocityTime pvt;
    if (flightPath.empty())
       return;
    PositionVelocityTime prev = flightPath.back();
    //setup needed variables
    v = prev.v;
    a = Angle(atan2(v.getDX(), v.getDY()));
    pos = prev.pos;
    acceleration = Acceleration();
    //cout << "velocity: " << v.getSpeed() << endl;
    double time = simulationTime - prev.t;
    pvt.t = simulationTime;
    double y = pos.getMetersY();
    double gravity = -gravityFromAltitude(y);
    //cout << "gravity: " << gravity << endl;
    double sos = speedSoundFromAltitude(y);
    //cout <<"Speed of Sound: " << sos << endl;
    double mach = v.getSpeed() / sos;
    //cout <<"Mach: " << mach << endl;
    double drag_c = dragFromMach(mach);
    //cout <<"Drag Coefficient: " << drag_c << endl;
    double density = densityFromAltitude(y);
    //cout <<"Air Density: " << density << endl;
    double drag = forceFromDrag(density, drag_c, radius, v.getSpeed());
    //cout <<"Drag force: " << drag << endl;
    double a_drag = accelerationFromForce(drag, mass);
    //cout << "Acceleration from drag force: " << a_drag << endl;
    acceleration.addDDX(-sin(a.getRadians()) * a_drag);
    acceleration.addDDY(gravity - cos(a.getRadians()) * a_drag);
    

    //update projectile variables
    pos.add(acceleration, v, time);
    v.add(acceleration, time);
    a.setDxDy(v.getDX(), v.getDY());
    //set pvt and add it
    pvt.pos = pos;
    pvt.v = v;
    flightPath.push_back(pvt);

 }

