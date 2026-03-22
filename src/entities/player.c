#include "player.h"
#include "../core/time.h"
#include "../game/map.h"
#include "../systems/animations.h"
#include "../systems/physics.h"
#include <raylib.h>
#include <raymath.h>

#define GRAVITY 9.81f
#define FALL_DEATH_THRESHOLD -50.0f
#define SPAWN_HEIGHT 5.0f

void init_player(Player *player) {
  player->health = 100;
  player->experience = 0;
  player->level = 1;
  player->xp_to_next_level = 100;
  player->speed = 5.0f;
  player->direction = 0.0f;
  player->max_step_height = 0.001f;
  player->jump_force = 5.0f;
  player->position = (Vector3){0.0f, 0.0f, 0.0f};
  player->velocity = (Vector3){0.0f, 0.0f, 0.0f};
  player->is_moving = false;
  player->kill_count = 0;
};

void update_player(Player *player, float camera_angle) {

  // don't process input if player is dead
  if (player->health <= 0) {
    return;
  }

  Vector2 input = {0};

  if (IsKeyDown(KEY_W))
    input.y = -1.0f;
  if (IsKeyDown(KEY_S))
    input.y = 1.0f;
  if (IsKeyDown(KEY_A))
    input.x = -1.0f;
  if (IsKeyDown(KEY_D))
    input.x = 1.0f;

  // jump if on ground
  if (IsKeyPressed(KEY_SPACE)) {
    float ground_height = GetGroundHeight(player->position, &map.model);
    if (player->position.y <= ground_height + 0.1f) {
      player->velocity.y = player->jump_force;
    }
  }

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

    float move_speed = player->speed * Time.delta_time;
    Vector3 target_position = {player->position.x + rotated_x * move_speed,
                               player->position.y,
                               player->position.z + rotated_z * move_speed};

    // move player
    if (CanMoveTo(player->position, target_position, &map.model)) {
      player->position.x += rotated_x * move_speed;
      player->position.z += rotated_z * move_speed;
    }

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

  // apply gravity to velocity
  player->velocity.y -= GRAVITY * Time.delta_time;

  // update vertical position from velocity
  player->position.y += player->velocity.y * Time.delta_time;

  // detect if player is moving based on input (velocity is not used for horizontal movement)
  player->is_moving = (input.x != 0.0f || input.y != 0.0f);

  if (player->is_moving) {
    PlayAnimation(&animation, ANIM_WALK);
  } else {
    PlayAnimation(&animation, ANIM_IDLE);
  }

  // distance to ground
  float ground_height = GetGroundHeight(player->position, &map.model);

  // stop falling when on the ground
  if (player->position.y <= ground_height + player->max_step_height) {
    player->position.y = ground_height;
    player->velocity.y = 0.0f;
  }

  // respawn if fallen off the map
  if (player->position.y < FALL_DEATH_THRESHOLD) {
    player->position = (Vector3){0.0f, SPAWN_HEIGHT, 0.0f};
    player->velocity = (Vector3){0.0f, 0.0f, 0.0f};
  }
}

void update_kill_count(Player *player, int amount) {
  player->kill_count += amount;
}

void respawn_player(Player *player) {
  player->health = 100;
  player->position = (Vector3){0.0f, SPAWN_HEIGHT, 0.0f};
  player->velocity = (Vector3){0.0f, 0.0f, 0.0f};
  player->direction = 0.0f;
  player->is_moving = false;
}

void draw_player(Player *player) {
  DrawModelEx(player->model, player->position, (Vector3){0.0f, 1.0f, 0.0f},
              player->direction * RAD2DEG, (Vector3){2.0f, 2.0f, 2.0f}, WHITE);
}

void unload_player(Player *player) { UnloadModel(player->model); }

// experience functions

void add_experience(Player *player, int xp) {
    player->experience += xp;

      // check for level up
      while (player->experience >= player->xp_to_next_level) {
          level_up(player);
      }
}

void level_up(Player *player ) {
    player->level += 1;
    // carry over excess experience to next level
    player->experience -= player->xp_to_next_level;
    // Increase XP needed for next level
    player->xp_to_next_level = (int)(player->xp_to_next_level * 1.5f); 
}
