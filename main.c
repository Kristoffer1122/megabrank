#include "camera/camera.h"
#include "player/animations.h"
#include "player/player.h"
#include "time/time.h"
#include <raylib.h>
#include <raymath.h>

int main() {

  InitWindow(1200, 800, "MEGABRANK");

  Player player = {0};
  init_player(&player);
  // Debug: Check if animation pointer is valid
  TraceLog(LOG_INFO, "Animation struct address: %p", (void *)&animation);

  // Try loading
  TraceLog(LOG_INFO, "About to load animation...");
  LoadAnimationFromM3D(&animation);

  TraceLog(LOG_INFO, "Animation loaded!"); // Initialize camera
   //
  GameCamera game_camera = {0};
  InitGameCamera(&game_camera, (Vector3){10.0f, 10.0f, 10.0f});
  SetCameraMode(&game_camera, CAMERA_THIRD_PERSON);

  DisableCursor();

  SetTargetFPS(60);

  while (!WindowShouldClose()) {
    Time.delta_time = GetFrameTime();
    Time.game_time += Time.delta_time;

    update_player(&player, game_camera.angle_horizontal);
    UpdateAnimation(&animation);
    UpdateGameCamera(&game_camera, player.position);

    BeginDrawing();
    ClearBackground((Color){135, 206, 235, 255});

    BeginMode3D(game_camera.camera);

    // draw_player(&player);
    DrawAnimation(&animation, player.position, 5.0f, WHITE);

    DrawPlane((Vector3){0.0f, 0.0f, 0.0f}, (Vector2){1000.0f, 1000.0f}, BLACK);
    DrawGrid(100, 10.0f);
    EndMode3D();

    EndDrawing();
  }

  UnloadAnimation(&animation);
  unload_player(&player);
  CloseWindow();
  return 0;
}
