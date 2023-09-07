
#ifndef _GAME_ENGINE_H
#define _GAME_ENGINE_H

#include "sprites.h"
#include "stdlib.h"
#include <arch/zxn.h>

int add_game_object(int tag, int x, int y, int dx, int dy, const void *sprite_data);
int add_player_object(int x, int y, int dx, int dy, const void *sprite_data);
void move_player(int x, int y);
void reset_game_objects();
void set_game_object_color(int slot, int color);

// ----------------------------------------------------------------
// Type Definitions

typedef struct sprite_info {
    uint8_t tag;    // User tag
    uint8_t slot;   // Sprite slot
	uint8_t color;  // Palette color
    uint8_t x;      // X coordinate in pixels
    uint8_t y;      // Y coordinate in pixels
    uint8_t dx;     // Horizontal displacement in pixels
    uint8_t dy;     // Vertical displacement in pixels
} sprite_info_t;

#endif
