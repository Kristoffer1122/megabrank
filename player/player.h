#ifndef PLAYER_H
#define PLAYER_H

#include <raylib.h>

typedef struct {
  int health;
  Vector3 position;
  float speed;
  float direction;
  Vector3 velocity;
  float jump_force;
  float max_step_height;
  Model model;
  Texture2D texture;

} Player;

extern Player player;

void init_player(Player* player);

void update_player(Player* player, float camera_angle);

void draw_player(Player* player);

void unload_player(Player* player);

#endif
