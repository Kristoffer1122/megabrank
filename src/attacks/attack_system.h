#ifndef ATTACK_SYSTEM_H
#define ATTACK_SYSTEM_H

#include "../attacks/aura.h"

typedef void (*attack_function)(void*);

extern attack_function attacks[];
extern int attack_count;

void call_attacks();

#endif
