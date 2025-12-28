#include "aura.h"
#include "../../../enemies/enemies.h"
#include "../../player.h"
#include <raylib.h>
#include <raymath.h>
#include <stdlib.h>

void aura_attack() {
  // for enemies within aura radius
  for (int i = 0; i < ENEMY_MAX_COUNT; i++) {
    if (enemy_list.enemies[i].alive) {
      float distance =
          Vector2Distance((Vector2){player.position.x, player.position.z},
                          (Vector2){enemy_list.enemies[i].position.x,
                                    enemy_list.enemies[i].position.z});
      if (distance <= aura.radius) {
        // Apply damage or effect to enemy
        enemy_list.enemies[i].health -= 10; // Example damage value
      }
    }
  }
  draw_aura(&aura);
}

void draw_aura(Aura *aura) {
  if (aura == NULL)
    return;

  // Draw a simple sphere to represent the aura
  DrawSphereEx(player.position, aura->radius, 10, 10, aura->color);
}
