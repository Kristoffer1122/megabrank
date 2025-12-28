// NOTE: the nice part about a game like this is that we can treat every enemy
// as the same enemy;

#ifndef ENEMIES_H
#define ENEMIES_H
#include <raylib.h>

#define ENEMY_MAX_COUNT 100

typedef enum {
  ENEMY_TYPE_ZOMBIE,
  ENEMY_TYPE_ALIEN,
  ENEMY_TYPE_ROBOT
} EnemyType;

typedef struct {
  bool alive;
  EnemyType enemy_type;
  char name[50];
  float speed;
  int health;
  int attack;
  int defense;
  Vector3 position;

} Enemy;

extern Enemy enemy;

typedef struct {
  Enemy enemies[100];
  int enemy_count;
} EnemyList;

extern EnemyList enemy_list;

void init_enemy(EnemyList *enemy_list, EnemyType enemy_type);
// make enemy move towards target, so we can add dummy targets later
void update_enemies(EnemyList *enemy_list, Vector3 target);
void draw_enemies(EnemyList *enemy_list);
void unload_enemies(EnemyList *enemy_list);

#endif
