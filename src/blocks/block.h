#ifndef BLOCK_H
#define BLOCK_H

#include <cglm/cglm.h>

#include "../util/shader.h"

// find a good way to make meshes
extern const float cube_data[6*6*5];
// extern const float cube_uvs[6*6*2];


typedef enum BlockID {
    AIR = 0,
    GRASS_BLOCK = 1,
} BlockID;

typedef struct Block {
    BlockID id;
} Block;

void draw_mesh(Block *block, vec3 position, Shader *shader);

#endif