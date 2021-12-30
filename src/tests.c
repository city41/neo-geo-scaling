#include "tests.h"

void control(s16 x, s16 spriteIndex) {
    const s16 y = 10;
    const s8 height = 4;
    const u8 palette = 2;

    *REG_VRAMMOD = 1;
    *REG_VRAMADDR = ADDR_SCB1 + spriteIndex * SCB1_SPRITE_ENTRY_SIZE;

    for (u8 ty = 0; ty < height; ++ty) {
        *REG_VRAMRW = ty + 1;
        *REG_VRAMRW = (palette << 8);
    }

    // append tile zero to the end, which is blank
    // requires sprites never be taller than 30 tiles
    *REG_VRAMRW = 0;
    *REG_VRAMRW = 0;

    *REG_VRAMMOD = SCB234_SIZE;
    *REG_VRAMADDR = ADDR_SCB2 + spriteIndex;

    // set scale (horizontal and vertical)
    *REG_VRAMRW = NO_SCALE;

    // TODO: if the sprite is sticky, x and y don't matter, should we skip them?
    // y position, height in tiles, whether it is sticky
    *REG_VRAMRW = (TO_SCREEN_Y(y) << 7) | height;
    // x position
    *REG_VRAMRW = TO_SCREEN_X(x) << 7;
}

void naiveScale(s16 x, s16 spriteIndex, s16 scale) {
    const s16 y = 10;
    const s8 height = 4;
    const u8 palette = 2;

    *REG_VRAMMOD = 1;
    *REG_VRAMADDR = ADDR_SCB1 + spriteIndex * SCB1_SPRITE_ENTRY_SIZE;

    for (u8 ty = 0; ty < height; ++ty) {
        *REG_VRAMRW = ty + 1;
        *REG_VRAMRW = (palette << 8);
    }

    // append tile zero to the end, which is blank
    // requires sprites never be taller than 30 tiles
    *REG_VRAMRW = 0;
    *REG_VRAMRW = 0;

    *REG_VRAMMOD = SCB234_SIZE;
    *REG_VRAMADDR = ADDR_SCB2 + spriteIndex;

    *REG_VRAMRW = scale;

    // TODO: if the sprite is sticky, x and y don't matter, should we skip them?
    // y position, height in tiles, whether it is sticky
    *REG_VRAMRW = (TO_SCREEN_Y(y) << 7) | height;
    // x position
    *REG_VRAMRW = TO_SCREEN_X(x) << 7;
}

void withTransparentBottomRow(s16 x, s16 spriteIndex, s16 scale) {
    const s16 y = 10;
    const s8 height = 3;
    const u8 palette = 2;

    *REG_VRAMMOD = 1;
    *REG_VRAMADDR = ADDR_SCB1 + spriteIndex * SCB1_SPRITE_ENTRY_SIZE;

    for (u8 ty = 0; ty < height; ++ty) {
        *REG_VRAMRW = ty + 1;
        *REG_VRAMRW = (palette << 8);
    }

    *REG_VRAMRW = 11;
    *REG_VRAMRW = (palette << 8);

    // append tile zero to the end, which is blank
    // requires sprites never be taller than 30 tiles
    *REG_VRAMRW = 0;
    *REG_VRAMRW = 0;

    *REG_VRAMMOD = SCB234_SIZE;
    *REG_VRAMADDR = ADDR_SCB2 + spriteIndex;

    *REG_VRAMRW = scale;

    // TODO: if the sprite is sticky, x and y don't matter, should we skip them?
    // y position, height in tiles, whether it is sticky
    *REG_VRAMRW = (TO_SCREEN_Y(y) << 7) | height;
    // x position
    *REG_VRAMRW = TO_SCREEN_X(x) << 7;
}