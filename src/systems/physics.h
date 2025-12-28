#ifndef PHYSICS_H 
#define PHYSICS_H 

#include <raylib.h>

// get maxDistance units below position
float GetGroundHeight(Vector3 position, Model *mapModel);

// check if we can move from here to there without collision
bool CanMoveTo(Vector3 from, Vector3 to, Model *mapModel);

#endif
