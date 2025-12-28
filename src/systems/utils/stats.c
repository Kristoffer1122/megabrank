#include <string.h>
#include "stats.h"

Stats player_stats;

void init_stats(Stats* stats) {
    if (stats == NULL)
        return;

    stats->strength = 10;
    stats->agility = 10;
    stats->intelligence = 10;
    stats->endurance = 10;
    stats->luck = 10;
}

void increase_stat(Stats* stats, const char* stat_name, float amount) {
    if (stats == NULL || stat_name == NULL)
        return;

    if (strcmp(stat_name, "strength") == 0) {
        stats->strength += amount;
    } else if (strcmp(stat_name, "agility") == 0) {
        stats->agility += amount;
    } else if (strcmp(stat_name, "intelligence") == 0) {
        stats->intelligence += amount;
    } else if (strcmp(stat_name, "endurance") == 0) {
        stats->endurance += amount;
    } else if (strcmp(stat_name, "luck") == 0) {
        stats->luck += amount;
    }
}

void decrease_stat(Stats* stats, const char* stat_name, float amount) {
    if (stats == NULL || stat_name == NULL)
        return;

    if (strcmp(stat_name, "strength") == 0) {
        stats->strength -= amount;
    } else if (strcmp(stat_name, "agility") == 0) {
        stats->agility -= amount;
    } else if (strcmp(stat_name, "intelligence") == 0) {
        stats->intelligence -= amount;
    } else if (strcmp(stat_name, "endurance") == 0) {
        stats->endurance -= amount;
    } else if (strcmp(stat_name, "luck") == 0) {
        stats->luck -= amount;
    }
}


