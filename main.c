#include "camera/camera.h"
#include "player/player.h"
#include "time/time.h"
#include <raylib.h>
#include <raymath.h>

int main() {

  InitWindow(1200, 800, "MEGABRANK");

  Player player = {0};
  init_player(&player);

  // Initialize camera
  GameCamera game_camera = {0};
  InitGameCamera(&game_camera, (Vector3){10.0f, 10.0f, 10.0f});
  SetCameraMode(&game_camera, CAMERA_THIRD_PERSON);

  DisableCursor();

  SetTargetFPS(60);

  while (!WindowShouldClose()) {
    Time.delta_time = GetFrameTime();
    Time.game_time += Time.delta_time;
    UpdateGameCamera(&game_camera, player.position);

    BeginDrawing();
    ClearBackground(RAYWHITE);

    BeginMode3D(game_camera.camera);

    update_player(&player);
    draw_player(&player);

    DrawGrid(100, 10.0f);
    EndMode3D();

    EndDrawing();
  }

  unload_player(&player);
  CloseWindow();
  return 0;
}
