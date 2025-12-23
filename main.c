#include "camera/camera.h"
#include "map/map.h"
#include "player/animations.h"
#include "player/player.h"
#include "time/time.h"
#include <raylib.h>
#include <raymath.h>

// global vars
Player player = {0};
GameCamera game_camera = {0};

int main() {

  InitWindow(1200, 800, "MEGABRANK");

  init_map(&map);
  init_player(&player);
  LoadAnimationFromM3D(&animation);

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
    DrawAnimation(&animation, player.position, player.direction, 5.0f, WHITE);

    draw_map(&map);
    DrawPlane((Vector3){0.0f, 0.0f, 0.0f}, (Vector2){1000.0f, 1000.0f}, BLACK);
    DrawGrid(100, 10.0f);
    EndMode3D();

    EndDrawing();
  }

  UnloadAnimation(&animation);
  unload_player(&player);
  unload_map(&map);
  CloseWindow();
  return 0;
}
