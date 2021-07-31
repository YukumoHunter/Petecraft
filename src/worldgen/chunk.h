#ifndef CHUNK_H
#define CHUNK_H

#include "blocks/block.h"

typedef struct Chunk {
    int x;
    int y;
    Block blocks[32][32][256];
} Chunk;

#endif