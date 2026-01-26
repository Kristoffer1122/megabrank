#include "./enemies.h"
#include "./player.h"
#include "../core/time.h"
#include <raylib.h>
#include <raymath.h>
#include <stdio.h>

void init_enemy(EnemyList *enemy_list, EnemyType enemy_type) {

  enemy_list->enemy_count = ENEMY_MAX_COUNT;

  for (int x = 0; x < ENEMY_MAX_COUNT; x++) {
    enemy_list->enemies[x].alive = true;
    enemy_list->enemies[x].speed = 2.0f;
    enemy_list->enemies[x].position =
        (Vector3){GetRandomValue(-50, 50), 0.0f, GetRandomValue(-50, 50)};
  }

  switch (enemy_type) {
  case ENEMY_TYPE_ZOMBIE:
    for (int x = 0; x < ENEMY_MAX_COUNT; x++) {
      enemy_list->enemies[x].enemy_type = ENEMY_TYPE_ZOMBIE;
      enemy_list->enemies[x].health = 100;
      enemy_list->enemies[x].health_bar_offset = (Vector3){0.0f, 1.5f, 0.0f};
      enemy_list->enemies[x].attack = 10;
      enemy_list->enemies[x].exp_reward = 10;
      enemy_list->enemies[x].defense = 5;
      snprintf(enemy_list->enemies[x].name, sizeof(enemy_list->enemies[x].name),
               "Zombie_%d", x);
    }
    break;
  case ENEMY_TYPE_ALIEN:
    for (int x = 0; x < ENEMY_MAX_COUNT; x++) {
      enemy_list->enemies[x].enemy_type = ENEMY_TYPE_ALIEN;
      enemy_list->enemies[x].health = 80;
      enemy_list->enemies[x].health_bar_offset = (Vector3){0.0f, 1.5f, 0.0f};
      enemy_list->enemies[x].attack = 15;
      enemy_list->enemies[x].exp_reward = 10;
      enemy_list->enemies[x].defense = 3;
      snprintf(enemy_list->enemies[x].name, sizeof(enemy_list->enemies[x].name),
               "Alien_%d", x);
    }
    break;
  case ENEMY_TYPE_ROBOT:
    for (int x = 0; x < ENEMY_MAX_COUNT; x++) {
      enemy_list->enemies[x].enemy_type = ENEMY_TYPE_ROBOT;
      enemy_list->enemies[x].health = 120;
      enemy_list->enemies[x].health_bar_offset = (Vector3){0.0f, 1.5f, 0.0f};
      enemy_list->enemies[x].attack = 8;
      enemy_list->enemies[x].exp_reward = 10;
      enemy_list->enemies[x].defense = 10;
      snprintf(enemy_list->enemies[x].name, sizeof(enemy_list->enemies[x].name),
               "Robot_%d", x);
    }
    break;
  }
}

void update_enemies(EnemyList *enemy_list, Vector3 target) {
  for (int i = 0; i < enemy_list->enemy_count; i++)
    if (enemy_list->enemies[i].alive == true)

      // make enemy move towards player
      // NOTE: we can later add pathfinding here
      // but for now just direct movement

      if (Vector3Distance(target, enemy_list->enemies[i].position) > 0.0f) {

        // Keep enemies on ground level
        enemy_list->enemies[i].position.y = 0.0f;

        Vector3 direction =
            Vector3Subtract(target, enemy_list->enemies[i].position);
        float length = Vector3Length(direction);

        if (length > 0.1f) {
          Vector3 normalized_direction = Vector3Scale(direction, 1.0f / length);

          float speed = enemy_list->enemies[i].speed;

          // move enemy towards player
          enemy_list->enemies[i].position = Vector3Add(
              enemy_list->enemies[i].position,
              Vector3Scale(normalized_direction, speed * Time.delta_time));
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

       // makeshift healthbar
       // DrawCube(enemy_list->enemies[x].health_bar_offset, 1.5f, 0.4f, 0.001f, WHITE);

       DrawCube(Vector3Add(enemy_list->enemies[x].position, 
                           (Vector3){enemy_list->enemies[x].health_bar_offset.x - 0.12f,
                           enemy_list->enemies[x].health_bar_offset.y,
                           enemy_list->enemies[x].health_bar_offset.y + 0.01f}),
                           0.012f * enemy_list->enemies[x].health, 0.3f, 0.001f, RED);

       DrawCube(Vector3Add(enemy_list->enemies[x].position, 
                           (Vector3){enemy_list->enemies[x].health_bar_offset.x - 0.12f,
                           enemy_list->enemies[x].health_bar_offset.y,
                           enemy_list->enemies[x].health_bar_offset.y - 0.01f}),
                           1.2f, 0.3f, 0.001f, RAYWHITE);


    } else {
       // increment player kill count
       player.kill_count += 1;
       add_experience(&player.experience, enemy_list->enemies[x].exp_reward);
      // enemy dead
      DrawSphere(enemy_list->enemies[x].position, 0.5f, RED);
    }
}

// void unload_enemies(EnemyList *enemy_list) {
//    for (int x = 0; x < enemy_count; x++) {
//      // Currently nothing to unload, but placeholder for future resources
//    }
// }
