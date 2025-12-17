#include "camera.h"
#include <raymath.h>

void InitGameCamera(GameCamera *cam, Vector3 initial_position) {
  cam->camera.position = initial_position;
  cam->camera.target = (Vector3){0.0f, 0.0f, 0.0f};
  cam->camera.up = (Vector3){0.0f, 1.0f, 0.0f};
  cam->camera.fovy = 60.0f;
  cam->camera.projection = CAMERA_PERSPECTIVE;

  cam->offset = (Vector3){0.0f, 10.0f, 10.0f};
  cam->smoothness = 5.0f;
  cam->rotation_speed = 0.1f;
}

void UpdateGameCamera(GameCamera *cam, Vector3 target_position) {
    // Raylib's third person camera with mouse control
    cam->camera.target = target_position;
   cam->camera.position = Vector3Add(target_position, cam->offset);
    UpdateCamera(&cam->camera, CAMERA_THIRD_PERSON);
}

void SetCameraMode(GameCamera *cam, CameraMode mode) {
  cam->mode = mode;
}

void SetCameraOffset(GameCamera *cam, Vector3 offset) { cam->offset = offset; }
