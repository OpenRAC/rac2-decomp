#include "common.h"
extern float D_L18_001B1270 __attribute__((sda));
extern int D_L18_001B1240 __attribute__((sda)), D_L18_001B1244 __attribute__((sda));
extern int D_L18_001B1268 __attribute__((sda));
extern u8 D_L18_001B1248 __attribute__((sda));
extern int D_L18_001B124C __attribute__((sda)), D_L18_001B1250 __attribute__((sda));
extern u32 D_00138320[];
extern char D_L18_001B1360[];
extern float vec_distance_xy(void *, void *), mat_fast_helper_a(float, float);
extern int func_PAL_002B5E30(void *, float);
extern int func_PAL_002B5E10(void *);
extern int enemy_aim_at_target(void *);
extern int func_PAL_L01_00323068(void *, void *);
extern int FastDecTimer(short *), vec_fast_helper_a(u8 *);
extern void func_PAL_002A7650(void *, int, int), moby_set_state(void *, int, int);
extern void func_PAL_L18_0042BA90(void *, int, int, float), func_PAL_L18_0042BAE0(void *);
extern u8 *func_PAL_L18_0042D088(void *, int);
extern int math_random_int_range(int, int), func_001163B0(void);
extern void STUB_printf(const char *, ...);

/* The two member stores of the reload: as members they do not conflict with the fixed scalar D_L18_001B1268,
   so its load is free to move ahead of the first store, as in retail. */
typedef struct { u8 pad[0x392]; u16 cooldown; short phase; short delay; } Timers;

/* func_PAL_L18_0042D3B8, the PAL copy of func_L18_00428738: the same C, with its timers scaled to 50 Hz and
   the burst's phase counted in fifths instead of sixths. */
/* Advance the shared enemy's ranged attack and its two muzzle timers. */
int func_PAL_L18_0042D3B8(u8 *object)
{
    u8 *state = *(u8 **)(object + 0x68);
    int changed = 0;
    switch (*(short *)(object + 0xAA)) {
    case 0xEC0:
        if (object[0xBC] != 1) {
            if (vec_distance_xy(object + 0x10, state + 0x220) < D_L18_001B1270)
                func_PAL_002B5E10(object);
            else func_PAL_L01_00323068(object, state + 0x220);
        } else {
            if (D_00138320[1] & 0x80) *(u16 *)(state + 0x392) = (D_L18_001B1240 * 5 + 2) / 6;
            FastDecTimer((short *)(state + 0x392));
        }
        if (*(float *)(object + 0x18) < *(float *)(state + 0x90)) {
            func_PAL_002A7650(object, 0, 3);
            changed = 1;
            moby_set_state(object, 12, -1);
        }
        enemy_aim_at_target(object);
        if (*(short *)(state + 0x392) == 0) {
            if (object[0xBC] != 1) {
                func_PAL_L18_0042BAE0(object);
                changed = 1;
                *(u16 *)(state + 0x396) = (D_L18_001B1244 * 5 + 2) / 6;
                func_PAL_L18_0042BA90(object, 2, 0, 10.0f);
                moby_set_state(object, 4, 6);
            } else changed = 1;
        }
        break;
    case 0xED4:
    case 0xEE1:
        if (object[0xBC] != 1) {
            u8 *target = *(u8 **)(state + 0x230);
            func_PAL_002B5E30(object, mat_fast_helper_a(*(float *)(target + 0x10) - *(float *)(object + 0x10),
                                             *(float *)(target + 0x14) - *(float *)(object + 0x14)));
        }
        switch (object[0x42]) {
        case 10:
            if (object[0x60] & 2) {
                func_PAL_L18_0042BA90(object, 11, 0, 10.0f);
                *(float *)(object + 0x48) = 3.0f;
                {
                    u8 bursts = D_L18_001B1248;
                    *(short *)(state + 0x394) = 0;
                    state[0x39D] = bursts;
                }
            }
            break;
        case 11:
            if (*(short *)(object + 0xAA) == 0xEE1) {
                if (*(short *)(state + 0x394) % 5 == 0) {
                    func_PAL_L18_0042D088(object, 0);
                    vec_fast_helper_a(state + 0x39D);
                }
                if ((*(short *)(state + 0x394) + 2) % 5 == 0) func_PAL_L18_0042D088(object, 1);
            } else if (*(short *)(object + 0xAA) == 0xED4 && *(short *)(state + 0x394) % 5 != 0) {
                func_PAL_L18_0042D088(object, 0);
                vec_fast_helper_a(state + 0x39D);
            }
            {
                int controlled = object[0xBC];
                if (controlled == 1) {
                    changed = (D_00138320[0] & 0x80) ? changed : controlled;
                } else if (state[0x39D] == 0) func_PAL_L18_0042BA90(object, 12, 0, 10.0f);
            }
            break;
        case 12:
            if (object[0x60] & 2) {
                changed = 1;
                ((Timers *)state)->delay = (math_random_int_range(D_L18_001B124C, D_L18_001B1250) * 5 + 2) / 6;
                ((Timers *)state)->cooldown = (D_L18_001B1268 * 5 + 2) / 6;
                func_PAL_L18_0042BA90(object, (func_001163B0() & 1) | 4, 0, 10.0f);
                moby_set_state(object, 2, 6);
            }
            break;
        }
        break;
    default:
        STUB_printf(D_L18_001B1360);
        break;
    }
    return changed;
}
