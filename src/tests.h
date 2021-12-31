#pragma once
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

#define FULL_SCALE  0xFFF
#define SCALE_Y_HALF 0xF80
#define SCALE_Y_QUARTER 0xF40

void basicScale(s16 x, s16 y, u8 height, s16 scale);
void basicScaleTileZeroToEnd(s16 x, s16 y, s16 scale);

void withTransparentBottomRow(s16 x, s16 y, u8 height, s16 scale);
void withTransparentBottomRowTileZeroToEnd(s16 x, s16 y, s16 scale);
