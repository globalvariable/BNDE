#ifndef CARTESIAN_H
#define CARTESIAN_H

#include <math.h>


typedef struct 
{
	double height;
	double lateral;
	double depth;
} CartesianCoordinates;


double distance_btwn_two_points(CartesianCoordinates *point_1, CartesianCoordinates *point_2);








#endif
