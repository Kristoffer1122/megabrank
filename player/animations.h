#ifndef ANIMATIONS_H
#define ANIMATIONS_H

#include <raylib.h>

typedef enum {
      ANIM_IDLE,
      ANIM_WALK,
      ANIM_RUN,
      ANIM_JUMP,
      ANIM_ATTACK,
      ANIM_DIE
} AnimationType;

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

void LoadAnimation(Animation *anim);
void UpdateAnimation(Animation *anim);
void DrawAnimation(Animation *anim, Vector3 position, float direction, float scale, Color tint);
void UnloadAnimation(Animation *anim);
void SetAnimationSpeed(Animation *anim, float speed);
void PlayAnimation(Animation *anim, int animIndex);

#endif
