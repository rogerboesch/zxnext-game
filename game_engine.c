
#include <arch/zxn.h>
#include <input.h>
#include <z80.h>
#include <intrinsic.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include "game_engine.h"

#pragma output CRT_ORG_CODE = 0x8184
#pragma output REGISTER_SP = 0xFF58
#pragma output CLIB_MALLOC_HEAP_SIZE = 0
#pragma output CLIB_STDIO_HEAP_SIZE = 0
#pragma output CLIB_FOPEN_MAX = -1

// ----------------------------------------------------------------
// Function Prototypes
// Define IDE_FRIENDLY in your C IDE to disable Z88DK C extensions and avoid
// parser errors/warnings in the IDE. Do NOT define IDE_FRIENDLY when compiling
// the code with Z88DK.

#ifdef IDE_FRIENDLY
#define __z88dk_fastcall
#define __preserves_regs(...)
#endif

// ----------------------------------------------------------------
// Function Prototypes

static void init_hardware(void);
static void init_isr(void);
static void create_background(void);
static void create_sprites(void);
static void update_sprites(void);

// ----------------------------------------------------------------
// Function Prototypes (must be implemented in game)

extern void game_collision(sprite_info_t sprite1, sprite_info_t sprite2);
extern void game_begin(void);
extern void game_update(uint8_t key);
extern void game_end(void);

// ----------------------------------------------------------------
// Sprite handling

#define SPRITE_HALF 8

static int number_of_sprites = 0;
static int player_slot = -1; 

#define MAX_NUMBER_OF_SPRITES 64
static sprite_info_t sprite[MAX_NUMBER_OF_SPRITES]; // TODO: Change to dynamic allocation

int add_game_object(int tag, int x, int y, int dx, int dy, const void *sprite_data) {
    if (number_of_sprites >= MAX_NUMBER_OF_SPRITES) {
        return -1;
    }

    int index = number_of_sprites++;

    sprite[index].tag = index;
    sprite[index].slot = index;
    sprite[index].x = x;
    sprite[index].y = y;
    sprite[index].dx = dx;
    sprite[index].dy = dy;
    sprite[index].color = 0;

    sprite_set_slot(index);
    sprite_set_pattern(sprite_data);

    sprite_set_slot(index);
    sprite_set_attributes(sprite[index].slot, sprite[index].x, sprite[index].y, sprite[index].color, 0, true);

	return index;
}

int add_player_object(int x, int y, int dx, int dy, const void *sprite_data) {
	player_slot = add_game_object(0, x, y, dx, dy, sprite_data);
	return player_slot;
}

void reset_game_objects() {
   for (int slot = 0; slot < number_of_sprites; ++slot) {
		sprite[slot].color = 0;

		sprite_set_slot(sprite[slot].slot);
		sprite_set_attributes(sprite[slot].slot, sprite[slot].x, sprite[slot].y, sprite[slot].color, 0, true);
    }
}

void set_game_object_color(int slot, int color) {
	sprite[slot].color = color;

	sprite_set_slot(sprite[slot].slot);
	sprite_set_attributes(sprite[slot].slot, sprite[slot].x, sprite[slot].y, sprite[slot].color, 0, true);
}

void move_player(int x, int y) {
    if (player_slot == -1) {
        return;
    }

    sprite[player_slot].x += sprite[player_slot].dx * x;
    sprite[player_slot].y += sprite[player_slot].dy * y;

    // If sprite is at the edge of the screen then change its direction.
    if ((sprite[player_slot].x == 0) || (sprite[player_slot].x >= 240)) {
    }

    if ((sprite[player_slot].y == 0) || (sprite[player_slot].y >= 176)) {
    }

    sprite_set_slot(sprite[player_slot].slot);
    sprite_set_attributes(sprite[player_slot].slot, sprite[player_slot].x, sprite[player_slot].y, 0, 0, true);
}

// ----------------------------------------------------------------
// Functions

static void init_hardware(void) {
    // Put Z80 in 28 MHz turbo mode.
    ZXN_NEXTREG(REG_TURBO_MODE, 0x03);

    // Disable RAM memory contention.
    ZXN_NEXTREGA(REG_PERIPHERAL_3, ZXN_READ_REG(REG_PERIPHERAL_3) | RP3_DISABLE_CONTENTION);
}

static void init_isr(void) {
    // Set up IM2 interrupt service routine:
    // Put Z80 in IM2 mode with a 257-byte interrupt vector table located
    // at 0x8000 (before CRT_ORG_CODE) filled with 0x81 bytes. Install an
    // empty interrupt service routine at the interrupt service routine
    // entry at address 0x8181.
    intrinsic_di();
    im2_init((void *) 0x8000);
    memset((void *) 0x8000, 0x81, 257);
    z80_bpoke(0x8181, 0xFB);
    z80_bpoke(0x8182, 0xED);
    z80_bpoke(0x8183, 0x4D);
    intrinsic_ei();
}

static void update_sprites(void) {
    for (int slot = 0; slot < number_of_sprites; ++slot) {
		if (slot != player_slot) {
			// Calculate next position of sprite.
			sprite[slot].x += sprite[slot].dx;
			sprite[slot].y += sprite[slot].dy;

			// If sprite is at the edge of the screen then change its direction.
			if ((sprite[slot].x == 0) || (sprite[slot].x >= 240)) {
				sprite[slot].dx = -sprite[slot].dx;
			}

			if ((sprite[slot].y == 0) || (sprite[slot].y >= 176)) {
				sprite[slot].dy = -sprite[slot].dy;
			}

			sprite_set_slot(sprite[slot].slot);
			sprite_set_attributes(sprite[slot].slot, sprite[slot].x, sprite[slot].y, sprite[slot].color, 0, true);
		}
    }
}

static bool intersects(sprite_info_t sprite1, sprite_info_t sprite2) {
	return (sprite1.x - SPRITE_HALF < sprite2.x + SPRITE_HALF &&
			sprite1.x + SPRITE_HALF > sprite2.x - SPRITE_HALF &&
			sprite1.y - SPRITE_HALF < sprite2.y + SPRITE_HALF &&
			sprite1.y + SPRITE_HALF > sprite2.y - SPRITE_HALF);
}

static bool test_sprites(void) {
	uint8_t test = sprite_get_system_state() && SPRITE_COLLISION_MASK;
	if (!test)
		return false;

    for (int slot = 0; slot < number_of_sprites; ++slot) {
		if (slot != player_slot) {
			if (intersects(sprite[player_slot], sprite[slot])) {
			    game_collision(sprite[player_slot], sprite[slot]);
            	return true;
            }
		}
	}

	return false;
}

int main(void) {
    init_hardware();
    init_isr();

    game_begin();

    sprite_set_layer_system(true, false, LAYER_PRIORITIES_S_L_U, false);

    while (true) {
        uint8_t key = in_inkey();
        if (key == 32) {
            // ESC
            break;
        }

        // Call game loop
        game_update(key);

        // Update game objects
        update_sprites();
        test_sprites();

        // Wait for vertical blanking interval.
        intrinsic_halt();
    }

    game_end();

    // Trig a soft reset. The Next hardware registers and I/O ports will be reset by NextZXOS after a soft reset.
    ZXN_NEXTREG(REG_RESET, RR_SOFT_RESET);

    return 0;
}
