#ifndef PLAYER_H
#define PLAYER_H

#include <raylib.h>

typedef struct {
  bool is_moving;
  int health;
  float max_step_height;
  float jump_force;
  float speed;
  float direction;
  Vector3 velocity;
  Vector3 position;
  Model model;
  Texture2D texture;
  int attacks[];

} Player;

extern Player player;

void init_player(Player* player);

void update_player(Player* player, float camera_angle);

void update_attacks(Player* player);

void draw_player(Player* player);

void unload_player(Player* player);

#endif
