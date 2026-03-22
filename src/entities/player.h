#ifndef PLAYER_H
#define PLAYER_H

#include <raylib.h>
#include "./enemies.h"

typedef struct {
  bool is_moving;
  int health;

  int experience;
  int level;
  int xp_to_next_level;

  float max_step_height;
  float jump_force;
  float speed;
  float direction;
  Vector3 velocity;
  Vector3 position;
  Model model;
  Texture2D texture;
  int kill_count;
  int attacks[];

} Player;

// experience struct and funcs
// NOTE: add experience multiplier later

// add exp to player
void add_experience(Player *player, int xp);

// level up the player, and make it harder to level up next time (1.5x)
void level_up(Player *player);

// start player funcs

extern Player player;

void init_player(Player* player);

void update_player(Player* player, float camera_angle);

void update_attacks(Player* player);

void update_kill_count(Player *player, int amount);

void respawn_player(Player *player);

void draw_player(Player* player);

void unload_player(Player* player);

#endif
