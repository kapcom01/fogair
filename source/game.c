#include <stdint.h>

#include "raylib.h"
#include "map.h"

#include "debug.c"


Texture2D MapTileTypeTextures;
Rectangle MapTileTypeTexturesRec[kTileTextureSize] = {0};

struct {
    uint16_t x_in_tiles;
    uint16_t y_in_tiles;
    MapTile *map_tile;
    uint16_t steps;
} player;

void ResetLevel(void);

// WEB_PLATFORM
void get_input(void);

void draw_frame(void) {
    BeginDrawing();

    // PLATFORM_WEB
    get_input();

    ClearBackground(BLACK);

    // DrawText(TextFormat("Steps: %d", player.steps), 5, 5, 20, RAYWHITE);

    for(uint16_t i=0; i<MAP_GRID_X; ++i) {
        for (uint16_t j=0; j<MAP_GRID_Y; ++j) {
            if ( Map[i][j].texture == 0 /*|| Map[i][j].fog*/ ) continue;
            DrawTexturePro(MapTileTypeTextures, MapTileTypeTexturesRec[Map[i][j].texture], Map[i][j].rec, (Vector2){0, 0}, 0, WHITE);
            // draw_room_index(i, j);
            // draw_map_grid(i, j);
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

    MapTileTypeTexturesRec[0].x = 320;
    MapTileTypeTexturesRec[0].y = 0;
    MapTileTypeTexturesRec[0].width = 32;
    MapTileTypeTexturesRec[0].height = 32;

    // room wall

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

    // passage wall

    MapTileTypeTexturesRec[kPassWall_NW].x = 0;
    MapTileTypeTexturesRec[kPassWall_NW].y = 0;
    MapTileTypeTexturesRec[kPassWall_NW].width = 32;
    MapTileTypeTexturesRec[kPassWall_NW].height = 32;

    MapTileTypeTexturesRec[kPassWall_N].x = 32;
    MapTileTypeTexturesRec[kPassWall_N].y = 0;
    MapTileTypeTexturesRec[kPassWall_N].width = 32;
    MapTileTypeTexturesRec[kPassWall_N].height = 32;

    MapTileTypeTexturesRec[kPassWall_NE].x = 64;
    MapTileTypeTexturesRec[kPassWall_NE].y = 0;
    MapTileTypeTexturesRec[kPassWall_NE].width = 32;
    MapTileTypeTexturesRec[kPassWall_NE].height = 32;

    MapTileTypeTexturesRec[kPassWall_E].x = 64;
    MapTileTypeTexturesRec[kPassWall_E].y = 32;
    MapTileTypeTexturesRec[kPassWall_E].width = 32;
    MapTileTypeTexturesRec[kPassWall_E].height = 32;

    MapTileTypeTexturesRec[kPassWall_SE].x = 64;
    MapTileTypeTexturesRec[kPassWall_SE].y = 64;
    MapTileTypeTexturesRec[kPassWall_SE].width = 32;
    MapTileTypeTexturesRec[kPassWall_SE].height = 32;

    MapTileTypeTexturesRec[kPassWall_S].x = 32;
    MapTileTypeTexturesRec[kPassWall_S].y = 64;
    MapTileTypeTexturesRec[kPassWall_S].width = 32;
    MapTileTypeTexturesRec[kPassWall_S].height = 32;

    MapTileTypeTexturesRec[kPassWall_SW].x = 0;
    MapTileTypeTexturesRec[kPassWall_SW].y = 64;
    MapTileTypeTexturesRec[kPassWall_SW].width = 32;
    MapTileTypeTexturesRec[kPassWall_SW].height = 32;

    MapTileTypeTexturesRec[kPassWall_W].x = 0;
    MapTileTypeTexturesRec[kPassWall_W].y = 32;
    MapTileTypeTexturesRec[kPassWall_W].width = 32;
    MapTileTypeTexturesRec[kPassWall_W].height = 32;

    // other

    MapTileTypeTexturesRec[kRoom].x = 352;
    MapTileTypeTexturesRec[kRoom].y = 0;
    MapTileTypeTexturesRec[kRoom].width = 32;
    MapTileTypeTexturesRec[kRoom].height = 32;

    MapTileTypeTexturesRec[kDoor].x = 352;
    MapTileTypeTexturesRec[kDoor].y = 0;
    MapTileTypeTexturesRec[kDoor].width = 32;
    MapTileTypeTexturesRec[kDoor].height = 32;

    MapTileTypeTexturesRec[kStairs].x = 196; // 352 // 480
    MapTileTypeTexturesRec[kStairs].y = 0;
    MapTileTypeTexturesRec[kStairs].width = 32;
    MapTileTypeTexturesRec[kStairs].height = 32;

    MapTileTypeTexturesRec[kReserved].x = 480;
    MapTileTypeTexturesRec[kReserved].y = 64;
    MapTileTypeTexturesRec[kReserved].width = 32;
    MapTileTypeTexturesRec[kReserved].height = 32;

    MapTileTypeTexturesRec[kPlayer].x = 256;
    MapTileTypeTexturesRec[kPlayer].y = 0;
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
            if ( Map[i][j].room_index == 1
                && Map[i][j].texture == kRoom ) {
                player.x_in_tiles = i;
                player.y_in_tiles = j;
                player.map_tile = &Map[i][j];
                player.map_tile->texture = kPlayer;
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
    
    if ( Map[new_x_in_tiles][new_y_in_tiles].texture == kRoom 
        || Map[new_x_in_tiles][new_y_in_tiles].texture == kDebugId) {
        Map[player.x_in_tiles][player.y_in_tiles].texture = kRoom; // TODO(Manolis): BUG: Room OR Passage OR Door ???
        player.x_in_tiles = new_x_in_tiles;
        player.y_in_tiles = new_y_in_tiles;
        player.map_tile = &Map[new_x_in_tiles][new_y_in_tiles];
        player.map_tile->texture = kPlayer;
        player.steps++;
        RevealPlayerSurroundings();
    }
    else if ( Map[new_x_in_tiles][new_y_in_tiles].texture == kStairs ) {
        ResetLevel();
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
    else if ( IsKeyPressedRepeat(KEY_UP) ) {
        MovePlayer(KEY_UP);
    }
    else if ( IsKeyPressedRepeat(KEY_DOWN) ) {
        MovePlayer(KEY_DOWN);
    }
    else if ( IsKeyPressedRepeat(KEY_LEFT) ) {
        MovePlayer(KEY_LEFT);
    }
    else if ( IsKeyPressedRepeat(KEY_RIGHT) ) {
        MovePlayer(KEY_RIGHT);
    }
    // else if ( IsKeyPressed(KEY_SPACE) ) {
    //     ResetLevel();
    // }
    
}

void ResetLevel(void) {
    GenerateRandomMap();
    InitializeTextures();
    SetupPlayer();
    RevealPlayerSurroundings();
}

int main() {
    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "fogair");
    SetTargetFPS(60);
    // ToggleFullscreen();
    SetTraceLogLevel(LOG_DEBUG);
    
    ResetLevel();

    while (!WindowShouldClose()) {
        draw_frame();
        // get_input();
    }

    CloseWindow();

    return 0;
}
