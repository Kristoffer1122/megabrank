#include "collision.h"
#include <float.h>
#include <raylib.h>
#include <raymath.h>

float GetGroundHeight(Vector3 position, Model *mapModel) {
  // ray downward from player position
  Ray ray = {.position = (Vector3){position.x, position.y + 10.0f, position.z},
             .direction = (Vector3){0.0f, -1.0f, 0.0f}};

  RayCollision collision = {0};
  float closestDistance = FLT_MAX;
  bool hitFound = false;

  // check collision with each mesh in the map
  for (int i = 0; i < mapModel->meshCount; i++) {
    RayCollision meshCollision =
        GetRayCollisionMesh(ray, mapModel->meshes[i],
                            MatrixIdentity()
        );

    if (meshCollision.hit && meshCollision.distance < closestDistance) {
      collision = meshCollision;
      closestDistance = meshCollision.distance;
      hitFound = true;
    }
  }

  if (hitFound) {
    // Return Y where the ray hit
    return collision.point.y;
  }

  // no ground found, return current height or 0
  return 0.0f;
}

bool CanMoveTo(Vector3 from, Vector3 to, Model *mapModel) {
  // cast ray from current position to target position
  Vector3 direction = Vector3Subtract(to, from);
  float distance = Vector3Length(direction);
  direction = Vector3Normalize(direction);

  Ray ray = {.position = (Vector3){from.x, from.y + 1.0f,
                                   from.z},
             .direction = direction};

  // check collision with each mesh
  for (int i = 0; i < mapModel->meshCount; i++) {
    RayCollision collision =
        GetRayCollisionMesh(ray, mapModel->meshes[i], MatrixIdentity());

    // if hit something closer than destination
    if (collision.hit && collision.distance < distance) {
      return false;
    }
  }

  return true;
}
