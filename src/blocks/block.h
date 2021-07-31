#ifndef BLOCK_H
#define BLOCK_H

// find a good way to make meshes
// float cube_vertices[] = {
// 
// }

typedef enum BlockID {
    AIR = 0,
    GRASS_BLOCK = 1,
} BlockID;

typedef struct Block {
    BlockID id;
} Block;

void create_mesh();

#endif