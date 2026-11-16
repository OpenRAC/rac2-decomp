#include "include_asm.h"

#include "common.h"
extern void moby_set_state(char *, int, int);
extern void moby_set_state();
extern int flag_set_first_pending(char *);
extern int math_fast_float_d(int *);
extern int FloatToInt(float);
extern int g_slot_reel_symbol_table[3][9];
typedef struct {
    char pad0[0x60];
    float pos[3];
    int timer[3];
    int mode[3];
    float speed[3];
    int want[3];
} State003E75A8;
extern int FloatToInt(float);

/* Advances the actor's three tracks (position +0x60, countdown +0x6C, mode +0x78, speed +0x84,
   wanted table entry +0x90), each position kept in [0, 9). The first time func_002B3868 agrees the
   countdowns are set (100 for the middle track, 50 and 180 for the others, swapped when bit 15 of
   +0x34 is set) and every mode becomes 1. Mode 1 moves the position back by its speed and becomes
   mode 2 when func_00282948 says its countdown is over. Mode 2 moves it the same way until the
   entry D_L02_002A53B0[track][(int)(position + 9) % 9] is the wanted one and the position is less
   than 0.2 above a whole number: the mode is then 0. Once all three modes are 0 the actor changes
   state (func_002A7750 with 4). */
void func_PAL_L02_003EB998(char *arg0) {
    State003E75A8 *st = *(State003E75A8 **)(arg0 + 0x68);
    int i;

    if (flag_set_first_pending(arg0)) {
        st->timer[1] = 83;
        st->timer[0] = 42;
        st->timer[2] = 150;
        if (*(u16 *)(arg0 + 0x34) & 0x8000) {
            st->timer[0] = 150;
            st->timer[2] = 42;
        }
        st->mode[0] = 1;
        st->mode[1] = 1;
        st->mode[2] = 1;
    }
    for (i = 0; i < 3; i++) {
        switch (st->mode[i]) {
        case 0:
            break;
        case 1:
            st->pos[i] = st->pos[i] - st->speed[i];
            if (st->pos[i] < 0.0f)
                st->pos[i] += 9.0f;
            if (math_fast_float_d(&st->timer[i]))
                st->mode[i] = 2;
            break;
        case 2:
            st->pos[i] = st->pos[i] - st->speed[i];
            if (st->pos[i] < 0.0f)
                st->pos[i] += 9.0f;
            if (g_slot_reel_symbol_table[i][FloatToInt(st->pos[i] + 9.0f) % 9] == st->want[i]) {
                if (st->pos[i] - (float)FloatToInt(st->pos[i]) < 0.2f)
                    st->mode[i] = 0;
            }
            break;
        }
        if (st->mode[0] == 0 && st->mode[1] == 0 && st->mode[2] == 0)
            moby_set_state(arg0, 4, -1);
    }
}
