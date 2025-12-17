#include <raylib.h>
#ifndef PLAYER_H
#define PLAYER_H

typedef struct {
  int health;
  Vector3 position;
  float speed;
  float direction;
  Model model;
  Mesh mesh;

} Player;

extern Player player;

void init_player(Player* player);

void update_player(Player* player);

void draw_player(Player* player);

void unload_player(Player* player);

#endif
