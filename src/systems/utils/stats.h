#ifndef STATS_H
#define STATS_H

typedef struct {
    float strength;
    float agility;
    float intelligence;
    float endurance;
    float luck;
} Stats;

extern Stats player_stats;

void init_stats(Stats* stats);
void increase_stat(Stats* stats, const char* stat_name, float amount);
void decrease_stat(Stats* stats, const char* stat_name, float amount);

#endif
