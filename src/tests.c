#include "tests.h"
#include <ngdevkit/neogeo.h>

#define ADDR_SCB1 0
#define ADDR_SCB2 0x8000
#define ADDR_SCB3 0x8200
#define ADDR_SCB4 0x8400

// how large, in words, the SCB2, SCB3 and SCB4 sections are (0x200)
#define SCB234_SIZE (ADDR_SCB4 - ADDR_SCB3)
#define SCB1_SPRITE_ENTRY_SIZE 64

#define TO_SCREEN_Y(inputY) (-((inputY) + 496) - 32)
#define TO_SCREEN_X(inputX) (inputX)

void control() {
    const s16 x = 10;
    const s16 y = 10;
    const s8 height = 4;

    *REG_VRAMMOD = 1;
    *REG_VRAMADDR = ADDR_SCB1 + 1 * SCB1_SPRITE_ENTRY_SIZE;

    for (u8 ty = 0; ty < height; ++ty) {
        *REG_VRAMRW = ty;
        *REG_VRAMRW = 0;
    }

    // append tile zero to the end, which is blank
    // requires sprites never be taller than 30 tiles
    *REG_VRAMRW = 0;
    *REG_VRAMRW = 0;

    *REG_VRAMMOD = SCB234_SIZE;
    *REG_VRAMADDR = ADDR_SCB2 + 1;

    // set scale (horizontal and vertical)
    *REG_VRAMRW = 0xfff;

    // TODO: if the sprite is sticky, x and y don't matter, should we skip them?
    // y position, height in tiles, whether it is sticky
    *REG_VRAMRW = (TO_SCREEN_Y(y) << 7) | height;
    // x position
    *REG_VRAMRW = TO_SCREEN_X(x) << 7;
}
