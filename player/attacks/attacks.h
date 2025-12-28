#ifndef ATTACKS_H
#define ATTACKS_H

#include "aura/aura.h"

typedef void (*attack_function)(void*);

extern attack_function attacks[];
extern int attack_count;

void call_attacks();

#endif
