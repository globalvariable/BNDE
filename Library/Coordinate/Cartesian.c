#include "Cartesian.h"




double distance_btwn_two_points(CartesianCoordinates *point_1, CartesianCoordinates *point_2)
{
	return sqrt(pow(point_1->height - point_2->height, 2.0) + pow(point_1->lateral - point_2->lateral, 2.0) + pow(point_1->depth - point_2->depth, 2.0));
}

