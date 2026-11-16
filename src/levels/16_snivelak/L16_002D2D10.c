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

extern T_001B99C0 g_snivelak_hero_state;

/* Starts the shared transition once, storing how fast it should step. */
void transition_arm_shared(s32 mode, f32 first_duration, f32 second_duration) {
    if (g_snivelak_hero_state.f27C == 0.0f) {
        g_snivelak_hero_state.i280 = mode;
        g_snivelak_hero_state.f27C = 1.0f;
        g_snivelak_hero_state.f274 = 1.0f / first_duration;
        g_snivelak_hero_state.f278 = 1.0f / second_duration;
    }
}
