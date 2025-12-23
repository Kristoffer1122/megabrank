#include "animations.h"
#include <raylib.h>
#include <raymath.h>
#include <stdlib.h>

Animation animation = {0};

void LoadAnimation(Animation *anim) {
  if (anim == NULL) {
    TraceLog(LOG_ERROR, "LoadAnimation: anim is NULL");
    return;
  }

  // Load M3D model
  anim->model = LoadModel("assets/models/knight/cavaleiro.m3d");

  if (anim->model.meshCount == 0) {
    TraceLog(LOG_ERROR, "Failed to load model");
    return;
  }

  // Load animations
  anim->animations = LoadModelAnimations("assets/models/knight/cavaleiro.m3d",
                                         &anim->animationCount);

  if (anim->animations == NULL || anim->animationCount == 0) {
    TraceLog(LOG_WARNING, "No animations found in file!");
    anim->animationCount = 0;
    return;
  }

  anim->currentAnimation = 0;
  anim->currentFrame = 0;
  anim->frameTime = 0.0f;
  anim->animFrameSpeed = 1.0f;
  anim->isPaused = false;

  TraceLog(LOG_INFO, "Loaded model with %d animations, %d bones",
           anim->animationCount, anim->model.boneCount);

  for (int i = 0; i < anim->animationCount; i++) {
    TraceLog(LOG_INFO, "Animation %d: %d frames, %d bones", i,
             anim->animations[i].frameCount, anim->animations[i].boneCount);
  }

  TraceLog(LOG_INFO, "Initializing animation to frame 0...");
  UpdateModelAnimation(anim->model, anim->animations[0], 0);
  TraceLog(LOG_INFO, "Animation initialized successfully");
}

void UpdateAnimation(Animation *anim) {
  if (anim == NULL || anim->animations == NULL || anim->animationCount == 0)
    return;

  if (anim->isPaused)
    return;

  // Update frame timing
  anim->frameTime += GetFrameTime() * anim->animFrameSpeed * 60.0f;

  // Only call UpdateModelAnimation when we advance to a new frame
  if (anim->frameTime >= 1.0f) {
    anim->frameTime = 0.0f;
    anim->currentFrame++;

    if (anim->currentFrame >=
        anim->animations[anim->currentAnimation].frameCount) {
      anim->currentFrame = 0;
    }

    // Update the model animation
    UpdateModelAnimation(anim->model, anim->animations[anim->currentAnimation],
                         anim->currentFrame);
  }
}

void DrawAnimation(Animation *anim, Vector3 position, float direction,
                   float scale, Color tint) {
  if (anim == NULL || anim->model.meshCount == 0)
    return;

  DrawModelEx(anim->model, position, (Vector3){0.0f, 1.0f, 0.0f},
              direction * RAD2DEG, (Vector3){scale, scale, scale}, tint);
}

void UnloadAnimation(Animation *anim) {
  if (anim == NULL)
    return;

  if (anim->animations != NULL) {
    UnloadModelAnimations(anim->animations, anim->animationCount);
  }

  UnloadModel(anim->model);
  *anim = (Animation){0};
}

void SetAnimationSpeed(Animation *anim, float speed) {
  if (anim != NULL) {
    anim->animFrameSpeed = speed;
  }
}

void PlayAnimation(Animation *anim, int animIndex) {
  if (anim == NULL)
    return;

  if (animIndex >= 0 && animIndex < anim->animationCount) {
    anim->currentAnimation = animIndex;
    anim->currentFrame = 0;
    anim->frameTime = 0.0f;
    anim->isPaused = false;
  }
}
