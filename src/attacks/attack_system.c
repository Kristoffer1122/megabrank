#include "attack_system.h"
#include "../attacks/aura.h"

attack_function attacks[] = {
    aura_attack,
};

int attack_count = sizeof(attacks) / sizeof(attacks[0]);

// call all attacks
void call_attacks() {
  for (int i = 0; i < attack_count; i++) {
    attacks[i]();
  }
}
