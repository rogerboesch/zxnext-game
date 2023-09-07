#ifndef _SPRITES_H
#define _SPRITES_H

#include <arch/zxn.h>
#include <stdint.h>
#include <stdbool.h>
#include <intrinsic.h>

#define SPRITE_SLOT_MASK     0x3F
#define X_LSB_MASK           0x00FF
#define X_MSB_MASK           0x0100
#define X_MSB_SHIFT          8
#define PALETTE_OFFSET_SHIFT 4
#define SPRITE_VISIBLE_MASK  0x80

#define LAYER_PRIORITIES_S_L_U 0x0
#define LAYER_PRIORITIES_L_S_U 0x1
#define LAYER_PRIORITIES_S_U_L 0x2
#define LAYER_PRIORITIES_L_U_S 0x3
#define LAYER_PRIORITIES_U_S_L 0x4
#define LAYER_PRIORITIES_U_L_S 0x5
#define MAX_SPRITES_PER_SCANLINE_MASK 0x02
#define SPRITE_COLLISION_MASK 0x01
#define MIRROR_X_MASK 0x08
#define MIRROR_Y_MASK 0x04
#define ROTATE_MASK 0x02

void sprite_set_layer_system(bool sprites_visible, bool sprites_on_border, uint8_t layer_priorities, bool lores_mode);
uint8_t sprite_get_system_state(void);
void sprite_set_slot(uint8_t sprite_slot);
void sprite_set_pattern(const void *sprite_pattern);
void sprite_set_attributes(uint8_t sprite_pattern_slot, uint8_t x, uint8_t y, uint8_t palette_offset, uint8_t sprite_flags, bool visible);

#endif
