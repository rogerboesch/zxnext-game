#include "sprites.h"


#define X_EXT(x) (((uint16_t) (x)) + 32)
#define X_LSB(x_ext) (uint8_t) ((x_ext) & X_LSB_MASK)
#define X_MSB(x_ext) (uint8_t) (((x_ext) & X_MSB_MASK) >> X_MSB_SHIFT)
#define Y_EXT(y) ((y) + 32)

#define LAYER_PRIORITIES_MASK  0x07
#define LAYER_PRIORITIES_SHIFT 2

void sprite_set_attributes(uint8_t sprite_pattern_slot, uint8_t x, uint8_t y, uint8_t palette_offset, uint8_t sprite_flags, bool visible)
{
    uint8_t pattern_slot = sprite_pattern_slot & SPRITE_SLOT_MASK;

    if (visible)
    {
        pattern_slot = pattern_slot | SPRITE_VISIBLE_MASK;
    }

    IO_SPRITE_ATTRIBUTE = X_LSB(X_EXT(x));
    IO_SPRITE_ATTRIBUTE = Y_EXT(y);
    IO_SPRITE_ATTRIBUTE = (palette_offset << PALETTE_OFFSET_SHIFT) | X_MSB(X_EXT(x)) | sprite_flags;
    IO_SPRITE_ATTRIBUTE = pattern_slot;
}

void sprite_set_layer_system(bool sprites_visible, bool sprites_on_border, uint8_t layer_priorities, bool lores_mode)
{
    uint8_t value = (layer_priorities & LAYER_PRIORITIES_MASK) << LAYER_PRIORITIES_SHIFT;

    if (sprites_visible)
    {
        value = value | RSLS_SPRITES_VISIBLE;
    }

    if (sprites_on_border)
    {
        value = value | RSLS_SPRITES_OVER_BORDER;
    }

    if (lores_mode)
    {
        value = value | RSLS_ENABLE_LORES;
    }

    IO_NEXTREG_REG = REG_SPRITE_LAYER_SYSTEM;
    IO_NEXTREG_DAT = value;
}

void sprite_set_pattern(const void *sprite_pattern)
{
    intrinsic_outi((void *) sprite_pattern, __IO_SPRITE_PATTERN, 256);
}


void sprite_set_slot(uint8_t sprite_slot)
{
    IO_SPRITE_SLOT = sprite_slot & SPRITE_SLOT_MASK;
}

uint8_t sprite_get_system_state(void)
{
    return IO_SPRITE_SLOT;
}
