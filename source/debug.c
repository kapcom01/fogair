#include "raylib.h"
#include "map.h"

const Color MapTileDebugColor[kTileTextureSize] = {
    RED, // Invalid room type
    PURPLE,
    PURPLE,
    PURPLE,
    PURPLE,
    PURPLE,
    PURPLE,
    PURPLE,
    PURPLE,
    PURPLE,
    PURPLE,
    PURPLE,
    PURPLE,
    PURPLE,
    PURPLE,
    PURPLE,
    PURPLE,
    WHITE,
    WHITE,
    ORANGE,
    BROWN,
    GREEN,
    WHITE,
};

#define DRAW_PARAMS Map[i][j].rec.x+2, Map[i][j].rec.y+1, 7, WHITE

void draw_room_index(int i, int j) {
    if (Map[i][j].texture == kDebugId) DrawText(TextFormat("%d", Map[i][j].room_index), DRAW_PARAMS);
}

void draw_map_grid(int i, int j) {
	DrawRectangleRec(Map[i][j].rec, MapTileDebugColor[Map[i][j].texture]);
    DrawRectangleLinesEx(Map[i][j].rec, 1.0f, BLACK);

    /*
    switch (Map[i][j].direction) { 
    case kNorth:
        DrawText("N", DRAW_PARAMS);
        break;
    case kSouth:
        DrawText("S", DRAW_PARAMS);
        break;
    case kWest:
        DrawText("W", DRAW_PARAMS);
        break;
    case kEast:
        DrawText("E", DRAW_PARAMS);
        break;
    case kNorthEast:
        DrawText("NE", DRAW_PARAMS);
        break;
    case kSouthEast:
        DrawText("SE", DRAW_PARAMS);
        break;
    case kNorthWest:
        DrawText("NW", DRAW_PARAMS);
        break;
    case kSouthWest:
        DrawText("SW", DRAW_PARAMS);
        break;
    }
    */
}