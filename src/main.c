#include "attacks/attack_system.h"
#include "attacks/aura.h"
#include "core/time.h"
#include "entities/enemies.h"
#include "entities/player.h"
#include "game/camera.h"
#include "game/map.h"
#include "systems/animations.h"
#include <raylib.h>
#include <raymath.h>

// global vars
Player player = {0};
EnemyList enemy_list = {0};
GameCamera game_camera = {0};

Aura aura = {.position = {0.0f, 0.0f, 0.0f},
             .radius = 5.0f,
             .color = BLUE,
             .intensity = 0.2f};

int main() {

  InitWindow(1680, 960, "MEGABRANK");

  init_map(&map);

  init_player(&player);
  init_aura(&aura);
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

    DrawText("Use WASD to move, SPACE to jump", 10, 10, 20, DARKGRAY);
    DrawText(TextFormat("Enemies killed:💀 %d", player.kill_count), 10, 40, 20, DARKGRAY);

    // draw player health bar
    int bar_x = 10;
    int bar_y = 100;
    int bar_width = 200;
    int bar_height = 20;
    int health_width = (int)((float)player.health / 100.0f * bar_width);
    if (health_width < 0) health_width = 0;
    if (health_width > bar_width) health_width = bar_width;

    DrawRectangle(bar_x, bar_y, bar_width, bar_height, DARKGRAY);
    Color health_color = (player.health > 50) ? GREEN : (player.health > 25) ? YELLOW : RED;
    DrawRectangle(bar_x, bar_y, health_width, bar_height, health_color);
    DrawRectangleLines(bar_x, bar_y, bar_width, bar_height, BLACK);
    DrawText(TextFormat("HP: %d/100", player.health), bar_x + 5, bar_y + 2, 16, WHITE);

    DrawText(TextFormat("Level: %d, EXP: %d", player.level, player.experience), 10, 70, 20, DARKGRAY);

    // show death screen and respawn prompt
    if (player.health <= 0) {
      DrawRectangle(0, 0, GetScreenWidth(), GetScreenHeight(), (Color){0, 0, 0, 150});
      DrawText("YOU DIED", GetScreenWidth()/2 - 100, GetScreenHeight()/2 - 40, 40, RED);
      DrawText("Press R to respawn", GetScreenWidth()/2 - 110, GetScreenHeight()/2 + 10, 20, WHITE);

      if (IsKeyPressed(KEY_R)) {
        respawn_player(&player);
        init_enemy(&enemy_list, ENEMY_TYPE_ZOMBIE);
      }
    }
    EndDrawing();
  }

  unload_animation(&animation);
  unload_player(&player);
  unload_aura(&aura);
  unload_enemies(&enemy_list);
  unload_map(&map);
  CloseWindow();
  return 0;
}
