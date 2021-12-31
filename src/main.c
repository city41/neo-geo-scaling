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

    s16 fx = 2;
    const s16 fy = 2;

    const s16 y = 10;
    s16 x = 16;

    s8 fps[1] = { '0' };

    // sample 0
    basicScale(x, y, 17, FULL_SCALE);
    fix_print(fx, fy, fps);
    x += 32;
    fx += 4;
    fps[0]++;

    // sample 1
    basicScale(x, y, 4, SCALE_Y_HALF);
    fix_print(fx, fy, fps);
    x += 32;
    fx += 4;
    fps[0]++;

    // sample 2
    withTransparentBottomRow(x, y, 4, SCALE_Y_HALF);
    fix_print(fx, fy, fps);
    x += 32;
    fx += 4;
    fps[0]++;

    // sample 3
    basicScale(x, y, 4, SCALE_Y_QUARTER);
    fix_print(fx, fy, fps);
    x += 32;
    fx += 4;
    fps[0]++;

    // sample 4
    basicScaleTileZeroToEnd(x, y, SCALE_Y_QUARTER);
    fix_print(fx, fy, fps);
    x += 32;
    fx += 4;
    fps[0]++;

    // sample 5
    withTransparentBottomRowTileZeroToEnd(x, y, SCALE_Y_QUARTER);
    fix_print(fx, fy, fps);
    x += 32;
    fx += 4;
    fps[0]++;

    // sample 6
    basicScale(x, y, 16, SCALE_Y_HALF);
    fix_print(fx, fy, fps);
    x += 32;
    fx += 4;
    fps[0]++;

    // sample 7
    withTransparentBottomRow(x, y, 16, SCALE_Y_HALF);
    fix_print(fx, fy, fps);
    x += 32;
    fx += 4;
    fps[0]++;

    // sample 8
    withTransparentBottomRow(x, y, 17, SCALE_Y_HALF);
    fix_print(fx, fy, fps);
    x += 32;
    fx += 4;
    fps[0]++;

    // sample 9
    basicScale(x, y, 24, SCALE_Y_QUARTER);
    fix_print(fx, fy, fps);
    x += 32;
    fx += 4;
    fps[0]++;

    for (;;) { }

    return 0;
}
