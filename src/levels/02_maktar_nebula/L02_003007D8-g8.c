#include "include_asm.h"
#include "common.h"

typedef struct {
    float v[10];
} L02_Table10;

typedef struct {
    u8 pad00[0x34];
    s32 time;
} L02_Clock;

extern int g_current_map_index;

extern void DrawQuadWithRotatedUVs(void *, int, int, unsigned int, int);

extern float IntToFloat(int);

extern int FloatToInt(float);

extern int math_random_int_range(int, int);

extern L02_Table10 D_L02_001A9460;

extern float D_L02_001B2FE4;

extern L02_Clock D_L02_001BE200;

/* `sda` with a size of at most 8: the argument is the one-instruction `$gp` address, as retail has it. */
extern char D_L02_001A9420[8] __attribute__((sda));

/* The callback func_L02_00300CE8 queues while the game state is 2. It reads the frame counter at +0x34
   of D_L02_001BE200 (read afresh in every test, as retail does) and
   - for frames 0x10B-0x114, sets D_L02_001B2FE4 to that frame's entry of the ten-float table;
   - picks the overlay ids and the alpha for the frame's window: 1-0x136 id 0x46, cross-fading into id 0x47
     (alpha = (frame - 0x10E) / 40 * 127 of the new one, the rest for the old one) from frame 0x10F on;
     0x137-0x17C id 0x47; 0x17D-0x18F id 0x49 with a random extra in 0-2; 0x191-0x1B4 id 0x48, fading out
     (alpha 127 - (frame - 0x1A1) / 15 * 127, at least 0) after frame 0x1A1;
   - draws the ids (the second one with the complementary alpha) through func_L01_002E2608 with the colour
     (alpha << 24) | 0x808080.
   The window limits sit in variables: retail compares them through registers (`slt` with the limit in
   a2/a3) and keeps every test of the ladder separate, where constants would fold into range tests.
   The unit is built with -g: the line label that then precedes the first div.s (the scheduler moves the
   next line's `li` above it) makes the assembler pad it with the two nops retail has, and the second
   div.s, which has no label in front of it, stays unpadded. */
/* During the intro cutscene, shows the timed picture overlays and fades them into each other. */
void cutscene_draw_intro_overlays(void *unused) {
    L02_Table10 frameTable;
    int tableIndex, fadeFrame, alpha, overlayId, fadeOutId, extra;
    float fadeFraction;

    if (g_current_map_index == 2) {
        int first_end = 0x136, second_end = 0x17C, third_end = 0x190;

        frameTable = D_L02_001A9460;
        if (D_L02_001BE200.time >= 0x10B) {
            if (D_L02_001BE200.time < 0x115) {
                tableIndex = D_L02_001BE200.time - 0x10B;
                if (tableIndex < 10)
                    D_L02_001B2FE4 = frameTable.v[tableIndex];
            }
        }
        overlayId = -1;
        fadeOutId = -1;
        alpha = 0x80;
        extra = 0;
        if (D_L02_001BE200.time > 0 && D_L02_001BE200.time <= first_end) {
            fadeFrame = D_L02_001BE200.time - 0x10E;
            overlayId = 0x46;
            if (fadeFrame > 0) {
                overlayId = 0x47;
                fadeFraction = IntToFloat(fadeFrame);
                fadeFraction = fadeFraction / IntToFloat(0x28);
                fadeOutId = 0x46;
                alpha = FloatToInt(fadeFraction * 127.0f);
            }
        } else if (D_L02_001BE200.time > first_end && D_L02_001BE200.time <= second_end) {
            overlayId = 0x47;
        } else if (D_L02_001BE200.time > second_end && D_L02_001BE200.time < third_end) {
            extra = math_random_int_range(0, 3);
            overlayId = 0x49;
        } else if (D_L02_001BE200.time > third_end && D_L02_001BE200.time < 0x1B5) {
            fadeFrame = D_L02_001BE200.time - 0x1A1;
            overlayId = 0x48;
            if (fadeFrame > 0) {
                fadeFraction = IntToFloat(fadeFrame);
                fadeFraction = fadeFraction / IntToFloat(0xF);
                alpha = 0x7F - FloatToInt(fadeFraction * 127.0f);
            }
            if (alpha < 0)
                alpha = 0;
        }
        if (overlayId != -1) {
            if (fadeOutId == -1 || overlayId == fadeOutId) {
                DrawQuadWithRotatedUVs(D_L02_001A9420, overlayId, 0, (alpha << 24) | 0x808080, extra);
            } else {
                DrawQuadWithRotatedUVs(D_L02_001A9420, overlayId, 0, (alpha << 24) | 0x808080, extra);
                DrawQuadWithRotatedUVs(D_L02_001A9420, fadeOutId, 0, ((0x7F - alpha) << 24) | 0x808080, extra);
            }
        }
    }
}
