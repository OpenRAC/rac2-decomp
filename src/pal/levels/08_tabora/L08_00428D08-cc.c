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

void func_PAL_L08_00428D08(char *a0) {
    char *s1 = a0;
    char *s0 = *(char **)(s1 + 0x68);

    if (*(u8 *)(s1 + 0xBC) != 0) {
        *(u8 *)(s1 + 0xBC) = 0;
        if (*(s16 *)(s0 + 0x1BA) < 0xa7) {
            *(s16 *)(s0 + 0x1BA) = (s16)(((int)(math_random_int_range(0x12C, 0x168)) * 5 + 2) / 6);
        }
    }
    if (*(s32 *)(s0 + 0x144) == 2) {
        FastDecTimer(s0 + 0x1BA);
    }
    if (*(u16 *)(s1 + 0x96) < 0x7FFD) {
        *(u16 *)(s1 + 0x96) += 1;
    }
    FastDecTimer(s0 + 0x1B8);
    FastDecTimer(s0 + 0x1BC);
    if (*(u8 *)(s1 + 0x20) >= 2) {
        moby_set_ease_target_height((Ent *)s1, *(f32 *)(s0 + 0x1B0));
    }
}

