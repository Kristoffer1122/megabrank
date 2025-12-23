#ifndef MAP_H
#define MAP_H

#include <raylib.h>

typedef struct {
  Vector3 position;
  float scale;
  Model model;
  Texture texture;

} Map;

extern Map map;

void init_map(Map *map);
void draw_map(Map *map);
void unload_map(Map *map);

#endif
