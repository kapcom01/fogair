#include <string.h>
#include "raylib.h"
#include "map.h"
#include "passage.c"

#define ARRAY_SIZE(x)  (sizeof(x) / sizeof((x)[0]))
#define STATIC_ASSERT(e) typedef char assert_failed[(e) ? 1 : -1]

Rectangle snaps[SNAPS_COUNT] = {0};
Rectangle rooms[ROOMS_COUNT] = {0};

Rectangle room_shapes_pool[] = {
    {0, 0, MAP_TILE_SIZE *  5,  5 * MAP_TILE_SIZE}, // 5x5
    {0, 0, MAP_TILE_SIZE * 13,  5 * MAP_TILE_SIZE}, // 13x5
    {0, 0, MAP_TILE_SIZE * 21,  5 * MAP_TILE_SIZE}, // 21x5
    {0, 0, MAP_TILE_SIZE * 21, 13 * MAP_TILE_SIZE}, // 21x13
    {0, 0, MAP_TILE_SIZE * 13, 13 * MAP_TILE_SIZE}, // 13x13
    {0, 0, MAP_TILE_SIZE * 21, 21 * MAP_TILE_SIZE}, // 21x21
    {0, 0, MAP_TILE_SIZE *  5, 13 * MAP_TILE_SIZE}, // 5x13
    {0, 0, MAP_TILE_SIZE *  5, 21 * MAP_TILE_SIZE}, // 5x21
    {0, 0, MAP_TILE_SIZE * 13, 21 * MAP_TILE_SIZE}, // 13x21
};

MapTile Map[MAP_GRID_X][MAP_GRID_Y] = {0};

void initialize_tiles(void) {
    for(int i=0; i<MAP_GRID_X; ++i) {
        for (int j=0; j<MAP_GRID_Y; ++j) {
            Map[i][j].rec.x      = (float) MAP_TILE_SIZE * i;
            Map[i][j].rec.y      = (float) MAP_TILE_SIZE * j;
            Map[i][j].rec.width  = (float) MAP_TILE_SIZE;
            Map[i][j].rec.height = (float) MAP_TILE_SIZE;
            Map[i][j].texture    = 0;
            Map[i][j].room_index = -1;
            Map[i][j].fog        = true;
        }
    }
}

void set_room_tiles(int room_index) {
    const int x_start = ((int) rooms[room_index].x) / MAP_TILE_SIZE;
    const int y_start = ((int) rooms[room_index].y) / MAP_TILE_SIZE;
    const int x_end   = ((int) rooms[room_index].width) / MAP_TILE_SIZE + x_start;
    const int y_end   = ((int) rooms[room_index].height) / MAP_TILE_SIZE + y_start;

    for(int i=(x_start); i<(x_end); ++i) {
        for(int j=(y_start); j<(y_end); ++j) {
            if (i == x_start && j == y_start) {
                Map[i][j].texture = kWall_NW;
            }
            else if (i == x_end-1 && j == y_end-1) {
                Map[i][j].texture = kWall_SE;
            }
            else if (j == y_start && i == x_end-1) {
                Map[i][j].texture = kWall_NE;
            }
            else if (i == x_start && j == y_end-1) {
                Map[i][j].texture = kWall_SW;
            }
            else if (i == x_start) {
                Map[i][j].texture = kWall_W;
            }
            else if (i == x_end-1) {
                Map[i][j].texture = kWall_E;
            }
            else if (j == y_start) {
                Map[i][j].texture = kWall_N;
            }
            else if (j == y_end-1) {
                Map[i][j].texture = kWall_S;
            }
            else {
                Map[i][j].texture = kRoom;
            }
            Map[i][j].room_index = room_index;
        }
    }
    // Map[x_start+1][y_start+1].texture = kDebugId;
}

int generate_rooms(void) {
    int debug_collisions = 0;
    int n=0;

    for (n=0; n<ARRAY_SIZE(rooms);) {
        if (debug_collisions > 300) break; // TODO(Manolis): Fix this INFINITE COLLISION BUG

        int snap  = GetRandomValue(0, SNAPS_COUNT-1);
        int shape = GetRandomValue(0, ARRAY_SIZE(room_shapes_pool)-1);
        Rectangle new_room = {0};
        new_room = room_shapes_pool[shape];
        new_room.x = snaps[snap].x;
        new_room.y = snaps[snap].y;

        // TODO(Manolis): Find a better solution to avoid collisions
        bool collision = false;
        for (int r = n; r > 0; --r) {
            if (CheckCollisionRecs(new_room, rooms[r-1])) {
                collision = true;
                debug_collisions++;
                break;
            }
        }
        if (new_room.x + new_room.width > WINDOW_WIDTH
                || new_room.y + new_room.height > WINDOW_HEIGHT) {
            collision = true;
            debug_collisions++;
        }
        if (collision) continue;
        rooms[n] = new_room;
        TraceLog(LOG_DEBUG, "ROOM %d collisions: %d",
            n+1,
            debug_collisions);
        set_room_tiles(n);
        n++;
        debug_collisions = 0;
    }
    return n;
}


TileDirection calculate_route(const int room_src, const int room_dst) {
    const int src_x = rooms[room_src].x / MAP_TILE_SIZE;
    const int src_y = rooms[room_src].y / MAP_TILE_SIZE;
    const int dst_x = rooms[room_dst].x / MAP_TILE_SIZE;
    const int dst_y = rooms[room_dst].y / MAP_TILE_SIZE;
    
    const int  src_h = rooms[room_src].height / MAP_TILE_SIZE;
    const int  src_w = rooms[room_src].width  / MAP_TILE_SIZE;
    const int  dst_h = rooms[room_dst].height / MAP_TILE_SIZE;
    const int  dst_w = rooms[room_dst].width  / MAP_TILE_SIZE;

    TileDirection direction = 0;

    // src_w > dst_w
    if ( (src_x >= dst_x && src_x <= dst_x+dst_w)
        || (src_x+src_w >= dst_x && src_x+src_w <= dst_x+dst_w) ) {
        if (src_y <= dst_y) {
            return kSouth;
        }
        else {
            return kNorth;
        }
    }

    // src_w < dst_w
    if ( (dst_x >= src_x && dst_x <= src_x+src_w)
        || (dst_x+dst_w >= src_x && dst_x+dst_w <= src_x+src_w) ) {
        if (src_y <= dst_y) {
            return kSouth;
        }
        else {
            return kNorth;
        }
    }
    
    // src_h > dst_h
    if ( (src_y >= dst_y && src_y <= dst_y+dst_h)
        || (src_y+src_h >= dst_y && src_y+src_h <= dst_y+dst_h) ) {
        if (src_x <= dst_x) {
            return kEast;
        }
        else {
            return kWest;
        }
    }

    // src_h < dst_h
    if ( (dst_y >= src_y && dst_y <= src_y+src_h)
        || (dst_y+dst_h >= src_y && dst_y+dst_h <= src_y+src_h) ) {
        if (src_x <= dst_x) {
            return kEast;
        }
        else {
            return kWest;
        }
    }

    if (src_y < dst_y) {
        direction += kSouth;
    }
    else if (src_y > dst_y) {
        direction += kNorth;
    }
    
    if (src_x < dst_x) {
        direction += kEast;
    }
    else if (src_x > dst_x) {
        direction += kWest;
    }

    return direction;
}

int create_passage(int from_room, int to_room) {
    int sx = rooms[from_room].x      / MAP_TILE_SIZE;
    int sy = rooms[from_room].y      / MAP_TILE_SIZE;
    int sw = rooms[from_room].width  / MAP_TILE_SIZE;
    int sh = rooms[from_room].height / MAP_TILE_SIZE;
    int dx = rooms[to_room].x        / MAP_TILE_SIZE;
    int dy = rooms[to_room].y        / MAP_TILE_SIZE;
    int dw = rooms[to_room].width    / MAP_TILE_SIZE;
    int dh = rooms[to_room].height   / MAP_TILE_SIZE;

    TileDirection route = calculate_route(from_room, to_room);

    int new_room_dst = to_room;

    switch (route) {
    case kNorth:
        while (sx < dx) sx += SNAPS_SIZE;
        new_room_dst = passage_to_north(sx, sy);
        break;
    case kSouth:
        sy += sh - 1;
        while (sx < dx) sx += SNAPS_SIZE;
        new_room_dst = passage_to_south(sx, sy);
        break;
    case kWest:
        dx += dw - 1;
        while (sy < dy) sy += SNAPS_SIZE;
        new_room_dst = passage_to_west(sx, sy);
        break;
    case kEast:
        sx += sw - 1;
        while (sy < dy) sy += SNAPS_SIZE;
        new_room_dst = passage_to_east(sx, sy);
        break;

    case kNorthWest:
        // if ( Map[sx+SNAPS_SIZE][sy].room_index == from_room) sx += SNAPS_SIZE;
        while ( Map[dx][(dy+SNAPS_SIZE)].room_index == to_room ) dy += SNAPS_SIZE;
        new_room_dst = passage_to_northwest(sx, sy, dy);
        break;
    case kNorthEast:
        while ( Map[dx][(dy+SNAPS_SIZE)].room_index == to_room ) dy += SNAPS_SIZE;
        new_room_dst = passage_to_northeast(sx, sy, dy);
        break;
    case kSouthWest:
        sy += sh-1;
        new_room_dst = passage_to_southwest(sx, sy, dy);
        break;
    case kSouthEast:
        sy += sh-1;
        new_room_dst = passage_to_southeast(sx, sy, dy);
        break;
    }

    TraceLog(LOG_DEBUG, "create_passage(%d, %d) => %d", from_room, to_room, new_room_dst);
    return new_room_dst;
}

void generate_snaps(void) {
    TraceLog(LOG_DEBUG, "SNAPS_COUNT: %d", SNAPS_COUNT);
    int n = 0;
    for (int y=0; y<SNAPS_SIZE_Y; ++y) {
        for (int x=0; x<SNAPS_SIZE_X; ++x) {
            // Map[SNAPS_SIZE * x][SNAPS_SIZE * y].texture = kPlayer;
            snaps[++n] = Map[SNAPS_SIZE * x][SNAPS_SIZE * y].rec;

        }
    }
}

void test_random_room_snaps(void) {
    for (int n=0; n<ARRAY_SIZE(rooms); ++n) {
        int snap  = GetRandomValue(0, SNAPS_COUNT-1);
        int shape = GetRandomValue(0, ARRAY_SIZE(room_shapes_pool)-1);
        rooms[n] = room_shapes_pool[shape];
        rooms[n].x = snaps[snap].x;
        rooms[n].y = snaps[snap].y;
        set_room_tiles(n);
    }
}

void GenerateRandomMap(void) {
    initialize_tiles();
    memset(snaps, 0, ARRAY_SIZE(snaps));
    memset(rooms, 0, ARRAY_SIZE(rooms));
    memset(Map,   0, ARRAY_SIZE(Map));

    STATIC_ASSERT(ARRAY_SIZE(snaps) == SNAPS_COUNT);

    generate_snaps();
    // test_snap_rooms();
    // test_random_room_snaps();

    int rooms_count = generate_rooms();
    
    bool rooms_with_passage[ARRAY_SIZE(rooms)] = {false};

    int connected_rooms = 0;
    rooms_with_passage[0] = true;

    int src = 0;
    int dst = 1;

    while ( rooms_count != connected_rooms) {
        int new_src = create_passage(src, dst);
        rooms_with_passage[new_src] = true;
        connected_rooms = 0;
        for (int i=0; i<rooms_count; i++) {
            if ( rooms_with_passage[i] == true ) connected_rooms++;
        }

        if (new_src == dst) {
            src = dst;
            dst = src+1;
        } else {
            src = new_src;
        }

        if (rooms_with_passage[src] && rooms_with_passage[dst]) {
            src=0;
            dst=0;
            // while ( rooms_with_passage[src] && src < rooms_count-2 ) src++;
            // dst = src+1;
            while ( rooms_with_passage[dst] && dst < rooms_count-1 ) dst++;
        }

        if (dst >= rooms_count) {
            break;
        }
    }

    // stairs
    const int stairs_x = (int) (rooms[rooms_count-1].x) / MAP_TILE_SIZE + 2;
    const int stairs_y = (int) (rooms[rooms_count-1].y) / MAP_TILE_SIZE + 2;
    Map[stairs_x][stairs_y].texture = kStairs;
}
