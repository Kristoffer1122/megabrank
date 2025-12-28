#ifndef AURA_H
#define AURA_H

#include <raylib.h>

typedef struct {
    Vector3 position;
    float radius;
    Color color;
    float intensity;
} Aura;

extern Aura aura;

void aura_attack();

void draw_aura(Aura *aura);

#endif
