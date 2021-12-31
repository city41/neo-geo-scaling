#include "tests.h"

#define TRANSPARENT_BOTTOM_ROW_TILE_INDEX 278
#define FIRST_TILE_OFFSET 261
#define PALETTE_INDEX 2
#define BLANK_TILE_INDEX 260

s16 spriteIndex = 1;

void basicScale(s16 x, s16 y, u8 height, s16 scale) {
    *REG_VRAMMOD = 1;
    *REG_VRAMADDR = ADDR_SCB1 + spriteIndex * SCB1_SPRITE_ENTRY_SIZE;

    for (u8 ty = 0; ty < height; ++ty) {
        *REG_VRAMRW = ty + FIRST_TILE_OFFSET;
        *REG_VRAMRW = (PALETTE_INDEX << 8);
    }

    *REG_VRAMMOD = SCB234_SIZE;
    *REG_VRAMADDR = ADDR_SCB2 + spriteIndex;

    *REG_VRAMRW = scale;

    *REG_VRAMRW = (TO_SCREEN_Y(y) << 7) | height;
    *REG_VRAMRW = TO_SCREEN_X(x) << 7;

    ++spriteIndex;
}

void basicScaleTileZeroToEnd(s16 x, s16 y, s16 scale) {
    const s8 height = 4;

    *REG_VRAMMOD = 1;
    *REG_VRAMADDR = ADDR_SCB1 + spriteIndex * SCB1_SPRITE_ENTRY_SIZE;

    u8 ty = 0;
    for (ty = 0; ty < height; ++ty) {
        *REG_VRAMRW = ty + FIRST_TILE_OFFSET;
        *REG_VRAMRW = (PALETTE_INDEX << 8);
    }

    for (; ty < 32; ++ty) {
        *REG_VRAMRW = BLANK_TILE_INDEX;
        *REG_VRAMRW = (PALETTE_INDEX << 8);
    }

    *REG_VRAMMOD = SCB234_SIZE;
    *REG_VRAMADDR = ADDR_SCB2 + spriteIndex;

    *REG_VRAMRW = scale;

    *REG_VRAMRW = (TO_SCREEN_Y(y) << 7) | height;
    *REG_VRAMRW = TO_SCREEN_X(x) << 7;

    ++spriteIndex;
}

void withTransparentBottomRow(s16 x, s16 y, u8 height, s16 scale) {
    *REG_VRAMMOD = 1;
    *REG_VRAMADDR = ADDR_SCB1 + spriteIndex * SCB1_SPRITE_ENTRY_SIZE;

    for (u8 ty = 0; ty < (height - 1); ++ty) {
        *REG_VRAMRW = ty + FIRST_TILE_OFFSET;
        *REG_VRAMRW = (PALETTE_INDEX << 8);
    }

    *REG_VRAMRW = TRANSPARENT_BOTTOM_ROW_TILE_INDEX;
    *REG_VRAMRW = (PALETTE_INDEX << 8);

    *REG_VRAMMOD = SCB234_SIZE;
    *REG_VRAMADDR = ADDR_SCB2 + spriteIndex;

    *REG_VRAMRW = scale;

    *REG_VRAMRW = (TO_SCREEN_Y(y) << 7) | height;
    *REG_VRAMRW = TO_SCREEN_X(x) << 7;

    ++spriteIndex;
}

void withTransparentBottomRowTileZeroToEnd(s16 x, s16 y, s16 scale) {
    const s8 height = 3;

    *REG_VRAMMOD = 1;
    *REG_VRAMADDR = ADDR_SCB1 + spriteIndex * SCB1_SPRITE_ENTRY_SIZE;

    u8 ty = 0;
    for (ty = 0; ty < height; ++ty) {
        *REG_VRAMRW = ty + FIRST_TILE_OFFSET;
        *REG_VRAMRW = (PALETTE_INDEX << 8);
    }

    *REG_VRAMRW = TRANSPARENT_BOTTOM_ROW_TILE_INDEX;
    *REG_VRAMRW = (PALETTE_INDEX << 8);
    ++ty;

    for (; ty < 32; ++ty) {
        *REG_VRAMRW = BLANK_TILE_INDEX;
        *REG_VRAMRW = (PALETTE_INDEX << 8);
    }

    *REG_VRAMMOD = SCB234_SIZE;
    *REG_VRAMADDR = ADDR_SCB2 + spriteIndex;

    *REG_VRAMRW = scale;

    *REG_VRAMRW = (TO_SCREEN_Y(y) << 7) | height;
    *REG_VRAMRW = TO_SCREEN_X(x) << 7;

    ++spriteIndex;
}