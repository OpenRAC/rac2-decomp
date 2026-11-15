#include "names.h"
/* Arms the shared transition once: stores the two reciprocal steps. Retail is built with -g
   (the nops before each div.s). */
typedef unsigned char u8;
typedef signed int s32;
typedef float f32;

typedef struct {
    u8 pad[0x274];
    f32 f274;
    f32 f278;
    f32 f27C;
    s32 i280;
} T_001B99C0;

extern T_001B99C0 D_L16_001B99C0;

/* Starts the shared transition once, storing how fast it should step. */
void transition_arm_shared(s32 mode, f32 firstDuration, f32 secondDuration) {
    if (D_L16_001B99C0.f27C == 0.0f) {
        D_L16_001B99C0.i280 = mode;
        D_L16_001B99C0.f27C = 1.0f;
        D_L16_001B99C0.f274 = 1.0f / firstDuration;
        D_L16_001B99C0.f278 = 1.0f / secondDuration;
    }
}
