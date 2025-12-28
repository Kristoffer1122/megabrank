#include "attacks.h"
#include "aura/aura.h"

attack_function attacks[] = {
    (void *)aura_attack,
};

// int attack_count = sizeof(attacks) / sizeof(attacks[0]);

// call all attacks
void call_attacks() {
  // for now just the aura attack, later we can loop through all attacks
  attacks[0]((void *)&aura);
}
