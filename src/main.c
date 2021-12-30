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

    s16 fpy = 13;

    // exporing the graphical artifacting beyond the scaled tiles
    basicScale(16, 10, FULL_SCALE);
    fix_print(2, fpy, "0");

    withTransparentBottomRow(48, 10, FULL_SCALE);
    fix_print(6, fpy, "1");

    basicScale(80, 10, SCALE_Y_HALF);
    fix_print(10, fpy, "2");

    withTransparentBottomRow(112, 10, SCALE_Y_HALF);
    fix_print(14, fpy, "3");

    basicScale(144, 10, SCALE_Y_QUARTER);
    fix_print(18, fpy, "4");

    basicScaleTileZeroToEnd(176, 10, SCALE_Y_QUARTER);
    fix_print(22, fpy, "5");

    withTransparentBottomRow(208, 10, SCALE_Y_QUARTER);
    fix_print(26, fpy, "6");

    withTransparentBottomRowTileZeroToEnd(240, 10, SCALE_Y_QUARTER);
    fix_print(30, fpy, "7");

    // exploring what the "last line is transparent" can accomplish
    fpy = 26;
    withTransparentBottomRow(16, 122, FULL_SCALE);
    fix_print(2, fpy, "8");

    withTransparentBottomRow(48, 122, (0xF << 8) | 200);
    fix_print(6, fpy, "9");

    withTransparentBottomRow(80, 122, (0xF << 8) | 90);
    fix_print(10, fpy, "10");

    basicScale(112, 122, FULL_SCALE);
    fix_print(14, fpy, "11");

    basicScale(144, 122, (0xF << 8) | 200);
    fix_print(18, fpy, "12");

    basicScale(176, 122, (0xF << 8) | 90);
    fix_print(22, fpy, "13");

    for (;;) { }

    return 0;
}
