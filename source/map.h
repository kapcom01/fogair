#ifndef _MAP_H_
#define _MAP_H_

#include <stdint.h>

#include "raylib.h"

#define WINDOW_WIDTH  1280
#define WINDOW_HEIGHT 720
#define MAP_TILE_SIZE 16
#define MAP_GRID_X WINDOW_WIDTH / MAP_TILE_SIZE
#define MAP_GRID_Y WINDOW_HEIGHT / MAP_TILE_SIZE

typedef enum {
    kWall_NW = 1,
    kWall_N,
    kWall_NE,
    kWall_E,
    kWall_SE,
    kWall_S,
    kWall_SW,
    kWall_W,
    kRoom,
    kPassage,
    kDoor,
    kDebugId,
    kPlayer,
    kTileTypeSize
} TileType;

typedef enum {
    kNorth     = 1,
    kSouth     = 2,
    kEast      = 4,
    kWest      = 8,
    kNorthEast = 5,
    kNorthWest = 9,
    kSouthEast = 6,
    kSouthWest = 10,
} TileDirection;

typedef struct {
    Rectangle rec;
    TileType type;
    TileDirection direction;
    uint16_t room_id;
    bool fog;
} MapTile;

extern MapTile Map[MAP_GRID_X][MAP_GRID_Y];

void GenerateRandomMap(void);

#endif
