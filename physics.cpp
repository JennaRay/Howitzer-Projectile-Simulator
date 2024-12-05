/***********************************************************************
 * Source File:
 *    PHYSICS
 * Author:
 *    <your name here>
 * Summary:
 *    Laws of motion, effects of gravity, wind resistence, etc.
 ************************************************************************/

#include "physics.h"  // for the prototypes
#include <iostream>
using namespace std;

/*********************************************************
* LINEAR INTERPOLATION
* From a list of domains and ranges, linear interpolate
*********************************************************/
double linearInterpolation(const Mapping mapping[], int numMapping, double domain)
{
   //numMapping = length of map?
   //mapping[] holds pairings of domain and range {d, r}
   //domain is input for the output we're trying to find
   double d = domain;
   double d0 = 0.0;
   double d1 = 0.0;
   double r0 = 0.0;
   double r1 = 0.0;

   //if d is out of range, return the last range
   if (d >= mapping[numMapping - 1].domain)
   {
      return mapping[numMapping - 1].range;
   }
   if (d <= mapping[0].domain)
   {
      return mapping[0].range;
   }

   for (int i = 0; i < numMapping; i++)
   {
      if (domain >= mapping[i].domain && domain <= mapping[i + 1].domain)
      {
         d0 = mapping[i].domain;
         d1 = mapping[i + 1].domain;
         r0 = mapping[i].range;
         r1 = mapping[i + 1].range;
      }
   }

   return linearInterpolation(d0, r0, d1, r1, d);
}

/*********************************************************
 * GRAVITY FROM ALTITUDE
 * Determine gravity coefficient based on the altitude
 *********************************************************/
double gravityFromAltitude(double altitude)
{
   //domain = altitude, range = gravity
   Mapping mapping[20] =
   {
      {0, 9.807},
      {1000, 9.804},
      {2000, 9.801},
      {3000, 9.797},
      {4000, 9.794},
      {5000,  9.791},
      {6000, 9.788},
      {7000, 9.785},
      {8000, 9.782},
      {9000, 9.779},
      {10000, 9.776},
      {15000, 9.761},
      {20000, 9.745},
      {25000, 9.730},
      {30000, 9.715},
      {40000, 9.684},
      {50000, 9.654},
      {60000, 9.624},
      {70000, 9.594},
      {80000, 9.564}
   };
   int len = 20;
   double d = altitude;

   return linearInterpolation(mapping, len, d);
}

/*********************************************************
 * DENSITY FROM ALTITUDE
 * Determine the density of air based on the altitude
 *********************************************************/
double densityFromAltitude(double altitude)
{
   //domain = altitude, range = air density
   Mapping mapping[20] =
   {
      {0, 1.225},
      {1000, 1.112},
      {2000, 1.007},
      {3000, 0.9093},
      {4000, 0.8194},
      {5000,  0.7364},
      {6000, 0.6601},
      {7000, 0.5900},
      {8000, 0.5258},
      {9000, 0.4671},
      {10000, 0.4135},
      {15000, 0.1948},
      {20000, 0.08891},
      {25000, 0.04008},
      {30000, 0.01841},
      {40000, 0.003996},
      {50000, 0.001027},
      {60000, 0.0003097},
      {70000, 0.0000828},
      {80000, 0.0000185}
   };
   int len = 20;
   double d = altitude;

   return linearInterpolation(mapping, len, d);
}

/*********************************************************
 * SPEED OF SOUND FROM ALTITUDE
 * determine the speed of sound for a given altitude.
 ********************************************************/
double speedSoundFromAltitude(double altitude)
{
   //domain = altitude, range = speed of sound
   Mapping mapping[20] =
   {
      {0, 340.0},
      {1000, 336.0},
      {2000, 332.0},
      {3000, 328.0},
      {4000, 324.0},
      {5000,  320.0},
      {6000, 316.0},
      {7000, 312.0},
      {8000, 308.0},
      {9000, 303.0},
      {10000, 299.0},
      {15000, 295.0},
      {20000, 295.0},
      {25000, 295.0},
      {30000, 305.0},
      {40000, 324.0},
      {50000, 337.0},
      {60000, 319.0},
      {70000, 289.0},
      {80000, 269.0}
   };
   int len = 20;
   double d = altitude;

   return linearInterpolation(mapping, len, d);
}


/*********************************************************
 * DRAG FROM MACH
 * Determine the drag coefficient for a M795 shell given speed in Mach
 *********************************************************/
double dragFromMach(double speedMach)
{
   //domain = mach, range = drag coefficient
   Mapping mapping[] =
   {
      {0.000, 0.0000},
      {0.300, 0.1629},
      {0.500, 0.1659},
      {0.700, 0.2031},
      {0.890, 0.2597},
      {0.920, 0.3010},
      {0.960, 0.3287},
      {0.980, 0.4002},
      {1.000, 0.4258},
      {1.020, 0.4335},
      {1.060, 0.4483},
      {1.240, 0.4064},
      {1.530, 0.3663},
      {1.990, 0.2897},
      {2.870, 0.2297},
      {2.890, 0.2306},
      {5.000, 0.2656}
   };
   int len = 17;
   double d = speedMach;

   if (speedMach == 0.0)
   {
      return 0.0;
   }
   return linearInterpolation(mapping, len, d);
}

