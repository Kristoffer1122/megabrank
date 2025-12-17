#ifndef TIME_H
#define TIME_H

// export variables
typedef struct {
    float delta_time;
    float game_time;
} GameTime;

extern GameTime Time;

#endif
