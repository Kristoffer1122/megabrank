#ifndef CAMERA_H
#define CAMERA_H

#include <raylib.h>

typedef struct {
  Camera3D camera;
  CameraMode mode;
  Vector3 offset;
  float smoothness;
  float rotation_speed;
  float angle_horizontal;
  float angle_vertical;
  float distance;
} GameCamera;

void InitGameCamera(GameCamera *cam, Vector3 initial_position);
void UpdateGameCamera(GameCamera *cam, Vector3 target_position);
void SetCameraMode(GameCamera *cam, CameraMode mode);
void SetCameraOffset(GameCamera *cam, Vector3 offset);

#endif
