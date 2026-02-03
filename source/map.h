#ifndef _MAP_H_
#define _MAP_H_

#include <stdint.h>
#include "raylib.h"
#include "Tiles.h"

// configurable macros
#define WINDOW_WIDTH  1280
#define WINDOW_HEIGHT 720
#define MAP_TILE_SIZE 24
#define ROOMS_COUNT   5

// not configurable macros
#define MAP_GRID_X ( WINDOW_WIDTH / MAP_TILE_SIZE )
#define MAP_GRID_Y ( WINDOW_HEIGHT / MAP_TILE_SIZE )

#define PASSAGE_SIZE 3 // dependent on assets
#define ROOM_MIN_SIZE ( PASSAGE_SIZE + 2 )
#define ROOM_MIN_DISTANCE 3
#define SNAPS_SIZE   ( ROOM_MIN_SIZE + ROOM_MIN_DISTANCE )
#define SNAPS_SIZE_X ( MAP_GRID_X / SNAPS_SIZE )
#define SNAPS_SIZE_Y ( MAP_GRID_Y / SNAPS_SIZE )
#define SNAPS_COUNT ( SNAPS_SIZE_X * SNAPS_SIZE_Y )

typedef enum {
    kWall_NW = 1,
    kWall_N,
    kWall_NE,
    kWall_E,
    kWall_SE,
    kWall_S,
    kWall_SW,
    kWall_W,
    kPassWall_NW,
    kPassWall_N,
    kPassWall_NE,
    kPassWall_E,
    kPassWall_SE,
    kPassWall_S,
    kPassWall_SW,
    kPassWall_W,
    kRoom,
    kDoor,
    kStairs,
    kReserved,
    kPlayer,
    kDebugId,
    kTileTextureSize
} TileTexture;

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
    TileTexture texture;
    int room_index;
    bool fog;
} MapTile;

extern MapTile Map[MAP_GRID_X][MAP_GRID_Y];

void GenerateRandomMap(void);

#endif
