#include "names.h"
/* func_PAL_L08_00428D08, the PAL copy of func_L08_004237F0: the same C, where scale func_327898(0x12C, 0x168); rename func_327898 becomes func_002A7820; rename func_2F9A90 becomes func_00282978; rename func_329EC0 becomes func_L08_00329EC0. */
typedef unsigned char u8;
typedef unsigned short u16;
typedef short s16;
typedef int s32;
typedef float f32;

typedef struct { u8 pad[0x100]; } Ent;

extern int FastDecTimer();
extern s32 math_random_int_range(s32, s32);
extern void moby_set_ease_target_height(Ent *, f32);

/* Counts down the sandfly timers; the +0x1BA one gets a fresh random value (PAL: 50 Hz scaled) when it is flagged. */
void sandfly_tick_timers_pal(char *moby_in) {
    char *moby = moby_in;
    char *vars = *(char **)(moby + 0x68);

    if (*(u8 *)(moby + 0xBC) != 0) {
        *(u8 *)(moby + 0xBC) = 0;
        if (*(s16 *)(vars + 0x1BA) < 0xa7) {
            *(s16 *)(vars + 0x1BA) = (s16)(((int)(math_random_int_range(0x12C, 0x168)) * 5 + 2) / 6);
        }
    }
    if (*(s32 *)(vars + 0x144) == 2) {
        FastDecTimer(vars + 0x1BA);
    }
    if (*(u16 *)(moby + 0x96) < 0x7FFD) {
        *(u16 *)(moby + 0x96) += 1;
    }
    FastDecTimer(vars + 0x1B8);
    FastDecTimer(vars + 0x1BC);
    if (*(u8 *)(moby + 0x20) >= 2) {
        moby_set_ease_target_height((Ent *)moby, *(f32 *)(vars + 0x1B0));
    }
}

