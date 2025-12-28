#include "camera.h"
#include <raymath.h>

void InitGameCamera(GameCamera *cam, Vector3 initial_position) {
  cam->camera.position = initial_position;
  cam->camera.target = (Vector3){0.0f, 0.0f, 0.0f};
  cam->camera.up = (Vector3){0.0f, 1.0f, 0.0f};
  cam->camera.fovy = 60.0f;
  cam->camera.projection = CAMERA_PERSPECTIVE;

  cam->offset = (Vector3){0.0f, 10.0f, 10.0f};
  cam->smoothness = 2.0f;
  cam->rotation_speed = 0.01f;

  cam->angle_horizontal = PI;
  cam->angle_vertical = -20.0f * DEG2RAD;
  cam->distance = 10.0f;
}

void UpdateGameCamera(GameCamera *cam, Vector3 target_position) {

  // get mouse movement
  Vector2 mouse_delta = GetMouseDelta();

  // update rotation angles based on mouse
  cam->angle_horizontal -= mouse_delta.x * cam->rotation_speed;
  cam->angle_vertical +=
      mouse_delta.y *
      cam->rotation_speed;

  float max_angle = 89.0f * DEG2RAD;
  float min_angle = -89.0f * DEG2RAD;

   // clamp angle
  if (cam->angle_vertical > max_angle)
    cam->angle_vertical = max_angle;
  if (cam->angle_vertical < min_angle)
    cam->angle_vertical = min_angle;

  // mouse wheel zoom
  float wheel = GetMouseWheelMove();
  cam->distance -= wheel * 2.0f;

  // Clamp distance
  if (cam->distance < 3.0f)
    cam->distance = 3.0f;
  if (cam->distance > 30.0f)
    cam->distance = 30.0f;

  float x =
      cam->distance * cosf(cam->angle_vertical) * sinf(cam->angle_horizontal);
  float y = cam->distance * sinf(cam->angle_vertical);
  float z =
      cam->distance * cosf(cam->angle_vertical) * cosf(cam->angle_horizontal);

  // offset to torso
  Vector3 target_offset =
      (Vector3){target_position.x, target_position.y + 2.0f, target_position.z};

  cam->camera.position =
      (Vector3){target_offset.x + x, target_offset.y + y, target_offset.z + z};

  cam->camera.target = target_offset;
}

void SetCameraMode(GameCamera *cam, CameraMode mode) { cam->mode = mode; }

void SetCameraOffset(GameCamera *cam, Vector3 offset) { cam->offset = offset; }
