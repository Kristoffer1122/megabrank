#ifndef ANIMATIONS_H
#define ANIMATIONS_H

#include <raylib.h>

typedef struct {
    Model model;
    ModelAnimation *animations;
    int animationCount;
    int currentAnimation;
    int currentFrame;
    float frameTime;
    float animFrameSpeed;
    bool isPaused;
} Animation;

extern Animation animation;

void LoadAnimationFromM3D(Animation *anim);  // Renamed for clarity
void UpdateAnimation(Animation *anim);
void DrawAnimation(Animation *anim, Vector3 position, float scale, Color tint);
void UnloadAnimation(Animation *anim);
void SetAnimationSpeed(Animation *anim, float speed);
void PlayAnimation(Animation *anim, int animIndex);

#endif
