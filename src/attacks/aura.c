#include "aura.h"
#include "../core/time.h"
#include "../entities/enemies.h"
#include "../entities/player.h"
#include "../game/camera.h"
#include <raylib.h>
#include <raymath.h>
#include <stdio.h>
#include <stdlib.h>

#define AURA_FRAME_COUNT 60
#define AURA_RING_COUNT 12

void init_aura(Aura *aura) {
  if (aura == NULL)
    return;

  aura->frame_count = AURA_FRAME_COUNT;
  // allocate memory for frames of texture
  aura->frames = (Texture2D *)malloc(sizeof(Texture2D) * aura->frame_count);

  // load all textures
  for (int i = 0; i < aura->frame_count; i++) {
    char path[256];
    snprintf(path, sizeof(path),
             "assets/pixelfire/png/blue/start/burning_start_%d.png", i + 1);
    aura->frames[i] = LoadTexture(path);
  }

  aura->current_frame = 0;
  aura->frame_timer = 0.1f;
}

void aura_attack() {
  // for enemies within aura radius
  for (int i = 0; i < ENEMY_MAX_COUNT; i++) {
    if (enemy_list.enemies[i].alive == true) {
      float distance =
          Vector2Distance((Vector2){player.position.x, player.position.z},
                          (Vector2){enemy_list.enemies[i].position.x,
                                    enemy_list.enemies[i].position.z});
      // if enemy is within aura radius
      if (distance <= aura.radius) {
        // Apply damage or effect to enemy
        enemy_list.enemies[i].health -= 20 * Time.delta_time;
        if (enemy_list.enemies[i].health <= 0) {
          enemy_list.enemies[i].alive = false;
        }
      }
    } else {
      continue;
    }
  }
  draw_aura(&aura);
}

void draw_aura(Aura *aura) {
  if (aura == NULL)
    return;

  Texture2D current_texture = aura->frames[aura->current_frame];

  float angle = (2 * PI) / AURA_RING_COUNT;

  Vector3 aura_position = {player.position.x + (cosf(angle) * aura->radius),
                           player.position.y + 1.0f,
                           player.position.z + (sinf(angle) * aura->radius)};

  // draw rings of fire around player
  for (int x = 0; x < AURA_RING_COUNT; x++) {
    aura_position.x = player.position.x + (cosf(angle * x) * aura->radius);
    aura_position.y = player.position.y + 0.5f;
    aura_position.z = player.position.z + (sinf(angle * x) * aura->radius);
    DrawBillboard(game_camera.camera, current_texture, aura_position, 1.0f,
                  aura->color);
  }
  // DrawBillboard(game_camera.camera, current_texture, aura_position, 1.0f,
  // aura->color);
}

void unload_aura(Aura *aura) {
  if (aura == NULL)
    return;

  UnloadTexture(aura->texture);
  free(aura->frames);
}
