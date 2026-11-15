#include "include_asm.h"
#include "names.h"

typedef unsigned char u8;
extern void func_PAL_L03_003FBA58(u8 *, int);
extern int math_random_int_below(int);
extern float math_random_float_range(float, float);
extern void func_PAL_002A7E68(int, int, int, int);
extern void snd_resume_music_stream(void);
extern void math_fast_float_d(void *);
typedef struct { u8 pad[0x1B8]; int busy; u8 pad2[0x62]; short timer; u8 pad3[0x2074]; int action; int unknown; int weapon; } Player;
extern Player g_hero_state;
typedef struct { u8 pad[0x6C]; short id; u8 pad2[4]; short mode; } Voice;
extern Voice g_music_state;
extern float D_L03_001B3760 __attribute__((sda));

void func_PAL_L03_003FB700(u8 *entity) {
    u8 *state = *(u8 **)(entity + 0x68);
    float ratio = *(float *)(state + 0x20) / (float)*(short *)(state + 0x24);
    if (entity[0x20] == 2 && !state[0x41D]) func_PAL_L03_003FBA58(entity, 13);
    if (entity[0x20] == 6 && !*(unsigned short *)(state + 0x410)) {
        if (math_random_float_range(0, 1) > 0.3f) func_PAL_L03_003FBA58(entity, 1);
        else func_PAL_L03_003FBA58(entity, 0);
    }
    if (entity[0x20] >= 6) {
        if (entity[0x20] == 15 && !state[0x413]) func_PAL_L03_003FBA58(entity, 3);
        if (g_hero_state.action == 0x39 && !g_hero_state.busy) {
            int choice = math_random_int_below(3);
            if (choice == 0) func_PAL_L03_003FBA58(entity, 8);
            else if (choice == 1) {
                func_PAL_L03_003FBA58(entity, 9);
                g_hero_state.timer = 0xC8;
            }
        }
        if (g_hero_state.weapon == 7 && !g_hero_state.busy) {
            if (math_random_int_below(5) == 0 && !state[0x41A]) func_PAL_L03_003FBA58(entity, 10);
        }
        if (ratio < 0.8f && D_L03_001B3760 >= 0.8f && !math_random_int_below(2)) {
            func_PAL_L03_003FBA58(entity, 2);
        } else if (ratio < 0.6f && D_L03_001B3760 >= 0.6f && !math_random_int_below(2)) {
            func_PAL_L03_003FBA58(entity, 5);
        } else if (ratio < 0.4f && D_L03_001B3760 >= 0.4f && !math_random_int_below(2)) {
            func_PAL_L03_003FBA58(entity, 6);
        } else if (ratio < 0.2f && D_L03_001B3760 >= 0.2f && !math_random_int_below(2)) {
            func_PAL_L03_003FBA58(entity, 4);
        }
        D_L03_001B3760 = ratio;
    }
    if (g_music_state.mode == 3 && g_music_state.id < 6000) {
        func_PAL_002A7E68(*(int *)(state + 0x2C4), 1, 0, 8);
        snd_resume_music_stream();
    }
    math_fast_float_d(state + 0x408);
}
