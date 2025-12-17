#ifndef CAMERA_H
#define CAMERA_H

#include <raylib.h>

typedef struct {
    Camera3D camera;
    CameraMode mode;
    Vector3 offset;        // Offset from target
    float smoothness;      // How smooth the follow is (0-1, higher = smoother)
    float rotation_speed;  // For free camera
} GameCamera;

void InitGameCamera(GameCamera* cam, Vector3 initial_position);
void UpdateGameCamera(GameCamera* cam, Vector3 target_position);
void SetCameraMode(GameCamera* cam, CameraMode mode);
void SetCameraOffset(GameCamera* cam, Vector3 offset);

#endif
