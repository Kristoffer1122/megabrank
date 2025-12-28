#ifndef AURA_H
#define AURA_H

#include <raylib.h>

typedef struct {
  long damage_per_second;
  int frame_count;
  Texture2D *frames;
  int current_frame;
  float frame_timer;
  Vector3 position;
  float radius;
  Color color;
  float intensity;
  Texture2D texture;
} Aura;

extern Aura aura;

void init_aura(Aura *aura);
void aura_attack();

void draw_aura(Aura *aura);

#endif
