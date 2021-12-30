#include "tests.h"
#include <ngdevkit/neogeo.h>

#define BLACK 0x8000
#define WHITE 0x7FFF
#define BROWN 0x6743
#define MMAP_BACKDROP_COLOR_INDEX ((volatile u16*)0x401FFE)

#define PALETTE_SIZE 2
const u16 palette[PALETTE_SIZE] = { BLACK, WHITE };

void init_palette() {
    for (u8 i = 0; i < PALETTE_SIZE; ++i) {
        MMAP_PALBANK1[i] = palette[i];
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

    u8 palette = 0;

    while (*text) {
        u16 tileIndex = *text + 1;

        *REG_VRAMRW = (palette << 12) | tileIndex;

        text += 1;
    }
}

int main() {
    init_palette();
    fix_clear();

    *MMAP_BACKDROP_COLOR_INDEX = BROWN;

    fix_print(10, 14, "Hello Neo Geo!");

    control();

    for (;;) { }

    return 0;
}
