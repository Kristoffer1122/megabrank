#include "map.h"
#include <raylib.h>
#include <unistd.h>

Map map = {0};

void init_map(Map *map) {
  map->position = (Vector3){0.0f, 0.0f, 0.0f};
  map->scale = 1.0f;

  // NOTE: raylib likes to change working directory when loading models,
  // so we save current working directory and go back to it after loading
  char cwd[1024];
  getcwd(cwd, sizeof(cwd));

  map->model = LoadModel("assets/Castle/CastleOBJ.obj");

  // go back to start directory
  chdir(cwd);

  TraceLog(LOG_INFO, "Castle loaded:  %d meshes, %d materials",
           map->model.meshCount, map->model.materialCount);
}

void draw_map(Map *map) {
  DrawModel(map->model, map->position, map->scale, WHITE);
}

void unload_map(Map *map) { UnloadModel(map->model); }
