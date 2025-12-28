#include "enemies.h"
#include "../time/time.h"
#include <raylib.h>
#include <raymath.h>
#include <stdio.h>

// global enemy list
int enemy_count = sizeof(enemy_list.enemies) / sizeof(enemy_list.enemies[0]);

void init_enemy(EnemyList *enemy_list, EnemyType enemy_type) {

  enemy_list->enemy_count = ENEMY_MAX_COUNT;

  for (int x = 0; x < ENEMY_MAX_COUNT; x++) {
    enemy_list->enemies[x].position =
        (Vector3){GetRandomValue(-50, 50), 0.0f, GetRandomValue(-50, 50)};
  }

  switch (enemy_type) {
  case ENEMY_TYPE_ZOMBIE:
    for (int x = 0; x < ENEMY_MAX_COUNT; x++) {
      enemy_list->enemies[x].enemy_type = ENEMY_TYPE_ZOMBIE;
      enemy_list->enemies[x].health = 100;
      enemy_list->enemies[x].attack = 10;
      enemy_list->enemies[x].defense = 5;
      snprintf(enemy_list->enemies[x].name, sizeof(enemy_list->enemies[x].name),
               "Zombie_%d", x);
    }
    break;
  case ENEMY_TYPE_ALIEN:
    for (int x = 0; x < ENEMY_MAX_COUNT; x++) {
      enemy_list->enemies[x].enemy_type = ENEMY_TYPE_ALIEN;
      enemy_list->enemies[x].health = 80;
      enemy_list->enemies[x].attack = 15;
      enemy_list->enemies[x].defense = 3;
      snprintf(enemy_list->enemies[x].name, sizeof(enemy_list->enemies[x].name),
               "Alien_%d", x);
    }
    break;
  case ENEMY_TYPE_ROBOT:
    for (int x = 0; x < ENEMY_MAX_COUNT; x++) {
      enemy_list->enemies[x].enemy_type = ENEMY_TYPE_ROBOT;
      enemy_list->enemies[x].health = 120;
      enemy_list->enemies[x].attack = 8;
      enemy_list->enemies[x].defense = 10;
      snprintf(enemy_list->enemies[x].name, sizeof(enemy_list->enemies[x].name),
               "Robot_%d", x);
    }
    break;
  }
}

void update_enemies(EnemyList *enemy_list, Vector3 target) {
  // NOTE: change this later
  for (int x = 0; x < enemy_count; x++) {
    Vector3 direction =
        Vector3Subtract(target, enemy_list->enemies[x].position);
    float length = Vector3Length(direction);
    if (length > 0.1f) {
      Vector3 normalized_direction = Vector3Scale(direction, 1.0f / length);
      enemy_list->enemies[x].position = Vector3Add(
          enemy_list->enemies[x].position,
          Vector3Scale(normalized_direction,
                       enemy_list->enemies[x].speed * Time.delta_time));
    }
  }
}

void draw_enemies(EnemyList *enemy_list) {
  for (int x = 0; x < enemy_list->enemy_count; x++)
    if (enemy_list->enemies[x].alive == true) {
      switch (enemy_list->enemies[x].enemy_type) {
      case ENEMY_TYPE_ZOMBIE:
        DrawSphere(enemy_list->enemies[x].position, 0.5f, GREEN);
        break;
      case ENEMY_TYPE_ALIEN:
        DrawSphere(enemy_list->enemies[x].position, 0.5f, BLUE);
        break;
      case ENEMY_TYPE_ROBOT:
        DrawSphere(enemy_list->enemies[x].position, 0.5f, GRAY);
        break;
      }
    } else {
       // enemy dead
      DrawSphere(enemy_list->enemies[x].position, 0.5f, RED);
    }
}

// void unload_enemies(EnemyList *enemy_list) {
//    for (int x = 0; x < enemy_count; x++) {
//      // Currently nothing to unload, but placeholder for future resources
//    }
// }
