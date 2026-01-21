#include <stdint.h>

#include "Tiles.h"
#include "raylib.h"
#include "map.h"

const Color MapTileTypeColor[kTileTypeSize] = {
    RED, // Invalid room type
    DARKPURPLE,
    DARKBROWN,
    GREEN,
    ORANGE,
    BLUE,
};

Texture2D MapTileTypeTextures;
Rectangle MapTileTypeTexturesRec[kTileTypeSize] = {0};

struct {
    uint16_t x_in_tiles;
    uint16_t y_in_tiles;
    MapTile *map_tile;
    uint16_t steps;
} player;

// WEB_PLATFORM
void get_input(void);

void draw_frame(void) {
    BeginDrawing();

    // PLATFORM_WEB
    get_input();

    ClearBackground(BLACK);

    DrawText(TextFormat("Steps: %d", player.steps), 5, 5, 20, RAYWHITE);

    for(uint16_t i=0; i<MAP_GRID_X; ++i) {
        for (uint16_t j=0; j<MAP_GRID_Y; ++j) {
            if (Map[i][j].type == 0 || Map[i][j].fog) continue; // Todo(Manolis): Invalid type
            DrawTexturePro(MapTileTypeTextures, MapTileTypeTexturesRec[Map[i][j].type], Map[i][j].rec, (Vector2){0, 0}, 0, WHITE);
            /*
            DrawRectangleRec(Map[i][j].rec, MapTileTypeColor[Map[i][j].type]);
            DrawRectangleLinesEx(Map[i][j].rec, 1.0f, BLACK);
            #define DRAW_PARAMS Map[i][j].rec.x+2, Map[i][j].rec.y+1, 7, WHITE
            if (Map[i][j].type == kDebugId) DrawText(TextFormat("%d", Map[i][j].room_id), DRAW_PARAMS);
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
    }

    EndDrawing();
}

void InitializeTextures() {
    // MapTileTypeTextures = LoadTexture("assets/Tiles.png");
    Image TilesPng = {0};
    TilesPng.width = TILES_WIDTH;
    TilesPng.height = TILES_HEIGHT;
    TilesPng.format = TILES_FORMAT;
    TilesPng.data = TILES_DATA;
    TilesPng.mipmaps = 1;
    MapTileTypeTextures = LoadTextureFromImage(TilesPng);

    MapTileTypeTexturesRec[kWall_NW].x = 96;
    MapTileTypeTexturesRec[kWall_NW].y = 0;
    MapTileTypeTexturesRec[kWall_NW].width = 32;
    MapTileTypeTexturesRec[kWall_NW].height = 32;

    MapTileTypeTexturesRec[kWall_N].x = 128;
    MapTileTypeTexturesRec[kWall_N].y = 0;
    MapTileTypeTexturesRec[kWall_N].width = 32;
    MapTileTypeTexturesRec[kWall_N].height = 32;

    MapTileTypeTexturesRec[kWall_NE].x = 160;
    MapTileTypeTexturesRec[kWall_NE].y = 0;
    MapTileTypeTexturesRec[kWall_NE].width = 32;
    MapTileTypeTexturesRec[kWall_NE].height = 32;

    MapTileTypeTexturesRec[kWall_E].x = 160;
    MapTileTypeTexturesRec[kWall_E].y = 32;
    MapTileTypeTexturesRec[kWall_E].width = 32;
    MapTileTypeTexturesRec[kWall_E].height = 32;

    MapTileTypeTexturesRec[kWall_SE].x = 160;
    MapTileTypeTexturesRec[kWall_SE].y = 64;
    MapTileTypeTexturesRec[kWall_SE].width = 32;
    MapTileTypeTexturesRec[kWall_SE].height = 32;

    MapTileTypeTexturesRec[kWall_S].x = 128;
    MapTileTypeTexturesRec[kWall_S].y = 64;
    MapTileTypeTexturesRec[kWall_S].width = 32;
    MapTileTypeTexturesRec[kWall_S].height = 32;

    MapTileTypeTexturesRec[kWall_SW].x = 96;
    MapTileTypeTexturesRec[kWall_SW].y = 64;
    MapTileTypeTexturesRec[kWall_SW].width = 32;
    MapTileTypeTexturesRec[kWall_SW].height = 32;

    MapTileTypeTexturesRec[kWall_W].x = 96;
    MapTileTypeTexturesRec[kWall_W].y = 32;
    MapTileTypeTexturesRec[kWall_W].width = 32;
    MapTileTypeTexturesRec[kWall_W].height = 32;

    MapTileTypeTexturesRec[kRoom].x = 288;
    MapTileTypeTexturesRec[kRoom].y = 0;
    MapTileTypeTexturesRec[kRoom].width = 32;
    MapTileTypeTexturesRec[kRoom].height = 32;

    MapTileTypeTexturesRec[kDoor].x = 288;
    MapTileTypeTexturesRec[kDoor].y = 0;
    MapTileTypeTexturesRec[kDoor].width = 32;
    MapTileTypeTexturesRec[kDoor].height = 32;

    MapTileTypeTexturesRec[kPassage].x = 288;
    MapTileTypeTexturesRec[kPassage].y = 0;
    MapTileTypeTexturesRec[kPassage].width = 32;
    MapTileTypeTexturesRec[kPassage].height = 32;

    MapTileTypeTexturesRec[kPlayer].x = 512;
    MapTileTypeTexturesRec[kPlayer].y = 64;
    MapTileTypeTexturesRec[kPlayer].width = 32;
    MapTileTypeTexturesRec[kPlayer].height = 32;
}

void RevealPlayerSurroundings() {
    int32_t x = (int32_t) player.x_in_tiles;
    int32_t y = (int32_t) player.y_in_tiles;

    for (int32_t i=x-1; i<x+2; i++) {
        for (int32_t j=y-1; j<y+2; j++) {
            if (   i < 0
                || j < 0
                || i > MAP_GRID_X
                || j > MAP_GRID_Y) {
                continue;
            }
            Map[i][j].fog = false;
        }
    }
}

void SetupPlayer() {
    player.steps = 0;
    for(uint16_t i=0; i<MAP_GRID_X; ++i) {
        for (uint16_t j=0; j<MAP_GRID_Y; ++j) {
            if ( Map[i][j].room_id == 1
                && Map[i][j].type == kRoom ) {
                player.x_in_tiles = i;
                player.y_in_tiles = j;
                player.map_tile = &Map[i][j];
                player.map_tile->type = kPlayer;
                return;
            }
        }
    }
}

void MovePlayer(KeyboardKey key) {
    uint16_t new_x_in_tiles = player.x_in_tiles;
    uint16_t new_y_in_tiles = player.y_in_tiles;
    
    switch (key) {
    case KEY_UP:
        if ( new_y_in_tiles > 0 )
            new_y_in_tiles--;
        break;
    case KEY_DOWN:
        if ( new_y_in_tiles < MAP_GRID_Y )
            new_y_in_tiles++;
        break;
    case KEY_LEFT:
        if ( new_x_in_tiles > 0 )
            new_x_in_tiles--;
        break;
    case KEY_RIGHT:
        if ( new_x_in_tiles < MAP_GRID_X )
            new_x_in_tiles++;
        break;
    }
    
    if ( Map[new_x_in_tiles][new_y_in_tiles].type == kRoom 
        || Map[new_x_in_tiles][new_y_in_tiles].type == kPassage
        || Map[new_x_in_tiles][new_y_in_tiles].type == kDoor) {
        Map[player.x_in_tiles][player.y_in_tiles].type = kRoom; // TODO(Manolis): BUG: Room OR Passage OR Door ???
        player.x_in_tiles = new_x_in_tiles;
        player.y_in_tiles = new_y_in_tiles;
        player.map_tile = &Map[new_x_in_tiles][new_y_in_tiles];
        player.map_tile->type = kPlayer;
        player.steps++;
        RevealPlayerSurroundings();
    }
}

void get_input(void) {
    if ( IsKeyPressed(KEY_UP) ) {
        MovePlayer(KEY_UP);
    }
    else if ( IsKeyPressed(KEY_DOWN) ) {
        MovePlayer(KEY_DOWN);
    }
    else if ( IsKeyPressed(KEY_LEFT) ) {
        MovePlayer(KEY_LEFT);
    }
    else if ( IsKeyPressed(KEY_RIGHT) ) {
        MovePlayer(KEY_RIGHT);
    }
    
}

int main() {
    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Rogue-like game");
    SetTargetFPS(60);
    SetTraceLogLevel(LOG_DEBUG);
    
    GenerateRandomMap();
    InitializeTextures();
    SetupPlayer();
    RevealPlayerSurroundings();

    while (!WindowShouldClose()) {
        draw_frame();
        // get_input();
    }

    CloseWindow();

    return 0;
}
