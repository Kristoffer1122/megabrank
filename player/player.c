#include "player.h"
#include "../time/time.h"
#include <raylib.h>
#include <raymath.h>
#include <stdio.h>

void init_player(Player *player) {
  player->health = 100;
  player->position = (Vector3){0.0f, 0.0f, 0.0f};
  player->speed = 5.0f;
  player->direction = 0.0f;

  // player model and texture
  // player->model = LoadModel("assets/models/knight/knight.obj");
  // Texture2D texture = LoadTexture("assets/models/knight/armor.jpg");
  // player->model.materials[0].maps[MATERIAL_MAP_DIFFUSE].texture = texture;
  //
}

void update_player(Player *player, float camera_angle) {

  Vector2 input = {0};

  if (IsKeyDown(KEY_W))
    input.y = -1.0f;
  if (IsKeyDown(KEY_S))
    input.y = 1.0f;
  if (IsKeyDown(KEY_A))
    input.x = -1.0f;
  if (IsKeyDown(KEY_D))
    input.x = 1.0f;

  // only move if there's input
  if (input.x != 0.0f || input.y != 0.0f) {

    // normalize diagonal movement
    float length = sqrtf(input.x * input.x + input.y * input.y);
    input.x /= length;
    input.y /= length;

    // rotate input by camera angle
    float cos_angle = cosf(camera_angle);
    float sin_angle = sinf(camera_angle);

    float rotated_x = input.x * cos_angle + input.y * sin_angle;
    float rotated_z = -input.x * sin_angle + input.y * cos_angle;

    // move player
    float move_speed = player->speed * Time.delta_time;
    player->position.x += rotated_x * move_speed;
    player->position.z += rotated_z * move_speed;

    // player always faces movement direction
    float target_direction = atan2f(rotated_x, rotated_z);

    float rotation_speed = 10.0f;

    float angle_diff = target_direction - player->direction;

    while (angle_diff > PI)
      angle_diff -= 2.0f * PI;
    while (angle_diff < -PI)
      angle_diff += 2.0f * PI;

    player->direction += angle_diff * rotation_speed * Time.delta_time;
  }
}

void draw_player(Player *player) {
  DrawModelEx(player->model, player->position, (Vector3){0.0f, 1.0f, 0.0f},
              player->direction * RAD2DEG, (Vector3){2.0f, 2.0f, 2.0f}, WHITE);
}

void unload_player(Player *player) { UnloadModel(player->model); }
