#include "player.h"
#include <raylib.h>

Player player = {0};

void init_player(Player *player) {
  player->health = 100;
  player->position = (Vector3){0.0f, 0.0f, 0.0f};
  player->speed = 0.0f;
  player->direction = 0.0f;

  // player model
  player->model = LoadModel("assets/models/knight/knight.obj");
}

void update_player(Player *player) {

  // Simple movement logic (WASD)
  if (IsKeyDown(KEY_W))
    player->position.z -= 1.0f;
  if (IsKeyDown(KEY_S))
    player->position.z += 1.0f;
  if (IsKeyDown(KEY_A))
    player->position.x -= 1.0f;
  if (IsKeyDown(KEY_D))
    player->position.x += 1.0f;
}

void draw_player(Player *player) {

  DrawModel(player->model, player->position, 2.0f, BLACK);

  // DrawCubeV(player->position, (Vector3){1.0f, 1.0f, 1.0f}, RED);
}

void unload_player(Player *player) { UnloadModel(player->model); }
