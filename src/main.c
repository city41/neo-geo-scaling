#include "paletteDefs.h"
#include "tests.h"
#include <ngdevkit/neogeo.h>

#define BLACK 0x8000
#define WHITE 0x7FFF
#define BROWN 0x6743
#define MMAP_BACKDROP_COLOR_INDEX ((volatile u16*)0x401FFE)

void init_palettes() {
    for (u8 i = 0; i < NUM_PALETTE_ENTRIES; ++i) {
        MMAP_PALBANK1[i] = palettes[i];
    }
}

void fix_clear() {
    u8 palette = 0;
    u16 tileValue = (palette << 12) | 0xFF;

    *REG_VRAMADDR = ADDR_FIXMAP;
    *REG_VRAMMOD = 1;

    for (u16 i = 0; i < 40 * 32; ++i) {
        *REG_VRAMRW = tileValue;
    }
}

void fix_print(u16 x, u16 y, const u8* text) {
    *REG_VRAMADDR = ADDR_FIXMAP + (x * 32) + y;

    *REG_VRAMMOD = 32;

    u8 palette = 1;

    while (*text) {
        u16 tileIndex = *text + 1;

        *REG_VRAMRW = (palette << 12) | tileIndex;

        text += 1;
    }
}

int main() {
    init_palettes();
    fix_clear();

    *MMAP_BACKDROP_COLOR_INDEX = BROWN;

    fix_print(12, 28, "Scaling sandbox");

    control(10, 1);

    naiveScale(30, 2, SCALE_Y_HALF);
    withTransparentBottomRow(50, 3, SCALE_Y_HALF);

    naiveScale(50, 3, SCALE_Y_QUARTER);
    withTransparentBottomRow(70, 4, SCALE_Y_QUARTER);

    for (;;) { }

    return 0;
}
