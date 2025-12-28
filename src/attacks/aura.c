#include "aura.h"
#include "../entities/enemies.h"
#include "../core/time.h"
#include "../entities/player.h"
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

      // make enemy move towards player
      if (Vector3Distance(player.position, enemy_list.enemies[i].position) >
          0.0f) {
        Vector3 direction =
            Vector3Subtract(player.position, enemy_list.enemies[i].position);
        float length = Vector3Length(direction);

        if (length > 0.1f) {
          Vector3 normalized_direction = Vector3Scale(direction, 1.0f / length);

          float speed = enemy_list.enemies[i].speed;

          // move enemy towards player
          enemy_list.enemies[i].position = Vector3Add(
              enemy_list.enemies[i].position,
              Vector3Scale(normalized_direction, speed * Time.delta_time));
        }

        if (distance <= aura.radius) {
          // Apply damage or effect to enemy
          enemy_list.enemies[i].health -= 20 * Time.delta_time;
          if (enemy_list.enemies[i].health <= 0) {
            enemy_list.enemies[i].alive = false;
          }
        }
      }
    }
    draw_aura(&aura);
  }
}

void draw_aura(Aura *aura) {
  if (aura == NULL)
    return;

  // Draw a simple sphere to represent the aura
  DrawSphereEx(player.position, aura->radius, 10, 10, aura->color);
}
