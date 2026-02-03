#include "raylib.h"
#include "map.h"

void build_door_north(int x, int y) {
    Map[x+1][y].texture = kPassWall_SE;
    Map[x+2][y].texture = kRoom;
    Map[x+3][y].texture = kPassWall_SW;
}

void build_door_south(int x, int y) {
    Map[x+1][y].texture = kPassWall_NE;
    Map[x+2][y].texture = kRoom;
    Map[x+3][y].texture = kPassWall_NW;
}

void build_door_west(int x, int y) {
    Map[x][y+1].texture = kPassWall_SE;
    Map[x][y+2].texture = kRoom;
    Map[x][y+3].texture = kPassWall_NE;
}

void build_door_east(int x, int y) {
    Map[x][y+1].texture = kPassWall_SW;
    Map[x][y+2].texture = kRoom;
    Map[x][y+3].texture = kPassWall_NW;
}

int passage_to_north(int x, int y) {
	build_door_north(x, y);
    while (Map[x][--y].room_index < 0) {
if(        Map[x+1][y].texture != kRoom)         Map[x+1][y].texture = kPassWall_E;
        Map[x+2][y].texture = kRoom;
        if(Map[x+3][y].texture != kRoom) Map[x+3][y].texture = kPassWall_W;
    }
    build_door_south(x, y);
    return Map[x][y].room_index;
}

int passage_to_south(int x, int y) {
	build_door_south(x, y);
    while (Map[x][++y].room_index < 0) {
        if(Map[x+1][y].texture != kRoom) Map[x+1][y].texture = kPassWall_E;
        Map[x+2][y].texture = kRoom;
        if(Map[x+3][y].texture != kRoom) Map[x+3][y].texture = kPassWall_W;
    }
    build_door_north(x, y);
    return Map[x][y].room_index;
}

int passage_to_west(int x, int y) {
	build_door_west(x, y);
    while (Map[--x][y].room_index < 0) {
        if(Map[x][y+1].texture != kRoom) Map[x][y+1].texture = kPassWall_S;
        Map[x][y+2].texture = kRoom;
        if(Map[x][y+3].texture != kRoom) Map[x][y+3].texture = kPassWall_N;
    }
    build_door_east(x, y);
    return Map[x][y].room_index;
}

int passage_to_east(int x, int y) {
	build_door_east(x, y);
    while (Map[++x][y].room_index < 0) {
        if(Map[x][y+1].texture != kRoom) Map[x][y+1].texture = kPassWall_S;
        Map[x][y+2].texture = kRoom;
        if(Map[x][y+3].texture != kRoom) Map[x][y+3].texture = kPassWall_N;
    }
    build_door_west(x, y);
    return Map[x][y].room_index;
}

void build_turn_northwest(int x, int y) {
	Map[x][y+1].texture = kWall_N;
	Map[x][y+2].texture = kRoom;
	Map[x][y+3].texture = kWall_S;

	Map[x+1][y+1].texture = kWall_N;
	Map[x+1][y+2].texture = kRoom;
	Map[x+1][y+3].texture = kPassWall_NE;
	
	if (Map[x+2][y+1].texture != kRoom) Map[x+2][y+1].texture = kWall_N; // possible crossroad
	Map[x+2][y+2].texture = kRoom;
	Map[x+2][y+3].texture = kRoom;

	Map[x+3][y+1].texture = kWall_NE;
	if (Map[x+3][y+2].texture != kRoom) Map[x+3][y+2].texture = kWall_E; // possible crossroad
	Map[x+3][y+3].texture = kWall_E;
}

void build_turn_northeast(int x, int y) {
	Map[x+1][y+1].texture = kWall_NW;
	if (Map[x+1][y+2].texture != kRoom) Map[x+1][y+2].texture = kWall_W; // possible crossroad
	Map[x+1][y+3].texture = kWall_W;
	
	if (Map[x+2][y+1].texture != kRoom) Map[x+2][y+1].texture = kWall_N; // possible crossroad
	Map[x+2][y+2].texture = kRoom;
	Map[x+2][y+3].texture = kRoom;

	Map[x+3][y+1].texture = kWall_N;
	Map[x+3][y+2].texture = kRoom;
	Map[x+3][y+3].texture = kPassWall_NW;

	Map[x+4][y+1].texture = kWall_N;
	Map[x+4][y+2].texture = kRoom;
	Map[x+4][y+3].texture = kWall_S;
}

void build_turn_southwest(int x, int y) {
	Map[x  ][y].texture = 0;
	Map[x+1][y].texture = kWall_W;
	Map[x+2][y].texture = kRoom;
	Map[x+3][y].texture = kWall_E;

	Map[x  ][y+1].texture = kWall_N;
	Map[x+1][y+1].texture = kPassWall_SE;
	Map[x+2][y+1].texture = kRoom;
	Map[x+3][y+1].texture = kWall_E;

	Map[x  ][y+2].texture = kRoom;
	Map[x+1][y+2].texture = kRoom;	
	Map[x+2][y+2].texture = kRoom;
	if (Map[x+3][y+2].texture != kRoom) Map[x+3][y+2].texture = kWall_E; // possible crossroad

	Map[x  ][y+3].texture = kWall_S;
	Map[x+1][y+3].texture = kWall_S;
	if (Map[x+2][y+3].texture != kRoom) Map[x+2][y+3].texture = kWall_S; // possible crossroad
	Map[x+3][y+3].texture = kWall_SE;
}

void build_turn_southeast(int x, int y) {
	Map[x+1][y].texture = kWall_W;
	Map[x+2][y].texture = kRoom;
	Map[x+3][y].texture = kWall_E;

	Map[x+1][y+1].texture = kWall_W;
	Map[x+2][y+1].texture = kRoom;
	Map[x+3][y+1].texture = kPassWall_SW;

	if (Map[x+1][y+2].texture != kRoom) Map[x+1][y+2].texture = kWall_W; // possible crossroad
	Map[x+2][y+2].texture = kRoom;
	Map[x+3][y+2].texture = kRoom;

	Map[x+1][y+3].texture = kWall_SW;
	if (Map[x+2][y+3].texture != kRoom) Map[x+2][y+3].texture = kWall_S; // possible crossroad
	Map[x+3][y+3].texture = kWall_S;
}

int passage_to_northwest(int x, int y, int turn) {
	build_door_north(x, y);
    while (--y > turn+3) {
        if (Map[x][y].room_index >= 0) {
        	build_door_south(x, y);
        	break;
        }
if (        Map[x+1][y].texture != kRoom)         Map[x+1][y].texture = kPassWall_E;
        Map[x+2][y].texture = kRoom;
        if (Map[x+3][y].texture != kRoom) Map[x+3][y].texture = kPassWall_W;
    }
    if (Map[x][y].room_index < 0) { // clear path
    	y -= 3;
    	build_turn_northwest(x, y);
   	    while (Map[--x][y].room_index < 0) {
	        if (Map[x][y+1].texture != kRoom) Map[x][y+1].texture = kPassWall_S;
	        Map[x][y+2].texture = kRoom;
	        if (Map[x][y+3].texture != kRoom) Map[x][y+3].texture = kPassWall_N;
	    }
	    build_door_east(x, y);
    }
    return Map[x][y].room_index;
}

int passage_to_northeast(int x, int y, int turn) {
	build_door_north(x, y);
    while (--y > turn+3) {
        if (Map[x][y].room_index >= 0) {
        	build_door_south(x, y);
        	break;
        }
        if (Map[x+1][y].texture != kRoom) Map[x+1][y].texture = kPassWall_E;
        Map[x+2][y].texture = kRoom;
        if (Map[x+3][y].texture != kRoom) Map[x+3][y].texture = kPassWall_W;
    }
    if (Map[x][y].room_index < 0) { // clear path
    	y -= 3; // fixed?: yes
    	build_turn_northeast(x, y);
    	x += 4;
   	    while (Map[++x][y].room_index < 0) {
	        if (Map[x][y+1].texture != kRoom) Map[x][y+1].texture = kPassWall_S;
	        Map[x][y+2].texture = kRoom;
	        if (Map[x][y+3].texture != kRoom) Map[x][y+3].texture = kPassWall_N;
	    }
	    build_door_west(x, y);
    }
    return Map[x][y].room_index;
}

int passage_to_southwest(int x, int y, int turn) {
	build_door_south(x, y);
    while (++y < turn) {
        if (Map[x][y].room_index >= 0) {
        	build_door_north(x, y);
        	break;
        }
        if (Map[x+1][y].texture != kRoom) Map[x+1][y].texture = kPassWall_E;
        Map[x+2][y].texture = kRoom;
        if (Map[x+3][y].texture != kRoom) Map[x+3][y].texture = kPassWall_W;
    }
    if (Map[x][y].room_index < 0) { // clear path
    	build_turn_southwest(x, y);
   	    while (Map[--x][y].room_index < 0) {
	        if (Map[x][y+1].texture != kRoom) Map[x][y+1].texture = kPassWall_S;
	        Map[x][y+2].texture = kRoom;
	        if (Map[x][y+3].texture != kRoom) Map[x][y+3].texture = kPassWall_N;
	    }
	    build_door_east(x, y);
    }
    return Map[x][y].room_index;
}

int passage_to_southeast(int x, int y, int turn) {
	build_door_south(x, y);
    while (++y < turn) {
        if (Map[x][y].room_index >= 0) {
        	build_door_north(x, y);
        	break;
        }
        if (Map[x+1][y].texture != kRoom) Map[x+1][y].texture = kPassWall_E;
        Map[x+2][y].texture = kRoom;
        if (Map[x+3][y].texture != kRoom) Map[x+3][y].texture = kPassWall_W;
    }
    if (Map[x][y].room_index < 0) { // clear path
    	build_turn_southeast(x, y);
    	x += 3;
   	    while (Map[++x][y].room_index < 0) {
	        if (Map[x][y+1].texture != kRoom) Map[x][y+1].texture = kPassWall_S;
	        Map[x][y+2].texture = kRoom;
	        if (Map[x][y+3].texture != kRoom) Map[x][y+3].texture = kPassWall_N;
	    }
	    build_door_west(x, y);
    }
    return Map[x][y].room_index;
}
