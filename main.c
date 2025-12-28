#include "camera/camera.h"
#include "enemies/enemies.h"
#include "map/map.h"
#include "player/animations.h"
#include "player/attacks/attacks.h"
#include "player/player.h"
#include "time/time.h"
#include <raylib.h>
#include <raymath.h>

// global vars
Player player = {0};
EnemyList enemy_list = {0};
GameCamera game_camera = {0};

Aura aura = {
    .position = {0.0f},
    .radius = 5.0f,
    .color = BLUE,
    .intensity = 1.0f
};

int main() {

  InitWindow(1200, 800, "MEGABRANK");

  init_map(&map);

  init_player(&player);
  load_animation(&animation);

  init_enemy(&enemy_list, ENEMY_TYPE_ZOMBIE);

  InitGameCamera(&game_camera, (Vector3){10.0f, 10.0f, 10.0f});
  SetCameraMode(&game_camera, CAMERA_THIRD_PERSON);

  DisableCursor();

  SetTargetFPS(60);

  while (!WindowShouldClose()) {
    Time.delta_time = GetFrameTime();
    Time.game_time += Time.delta_time;

    update_player(&player, game_camera.angle_horizontal);
    update_animation(&animation);
    update_enemies(&enemy_list, player.position);
    UpdateGameCamera(&game_camera, player.position);

    BeginDrawing();
    ClearBackground((Color){135, 206, 235, 255});

    BeginMode3D(game_camera.camera);

    draw_animation(&animation, player.position, player.direction, 5.0f, WHITE);
    draw_enemies(&enemy_list);

    // call attacks player has
    call_attacks();

    draw_map(&map);
    // DrawPlane((Vector3){0.0f, 0.0f, 0.0f}, (Vector2){1000.0f, 1000.0f},
    // BLACK);
    DrawGrid(100, 10.0f);
    EndMode3D();

    EndDrawing();
  }

  unload_animation(&animation);
  unload_player(&player);
  // unload_enemies(&enemy_list);
  unload_map(&map);
  CloseWindow();
  return 0;
}
