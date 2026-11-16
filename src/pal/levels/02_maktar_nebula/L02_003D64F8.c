#include "include_asm.h"
#include "common.h"

typedef int TI128 __attribute__((mode(TI)));

extern void mem_clear(char *, int, int);
extern void AttachManipulator(char *, int, char *);
extern void vec_random_direction(char *, float, float);
extern void func_PAL_002B15D8(char *, int, char *, float, float, float, float, int);
extern void moby_set_anim_type_three_pal(char *, int, int);
extern void part_queue_moby_for_glow(char *, int, void *);
extern void func_PAL_L02_003D5F20(char *, TI128 *);
extern void enemy_release_effect_record(char *);

/* func_PAL_L02_003D64F8, the PAL copy of func_L02_003D2488: the same C, where 1/60 and 0.05 become 0.02 and 0.06,
   and the 0x1000 flag at +0x34 is cleared after the word at +0x98. */
void func_PAL_L02_003D64F8(char *self, int flag1, int flag2) {
    char *state = *(char **)(self + 0x68);
    float vec[4];

    if (*(char **)(state + 0x2E4) != 0) {
        *(TI128 *)vec = *(TI128 *)(*(char **)(state + 0x2E4) + 0x10);
        func_PAL_L02_003D5F20(self, (TI128 *)vec);
    }
    if (*(unsigned char *)(state + 0x291) == 0) {
        mem_clear(state + 0x290, 0, 0x40);
        AttachManipulator(self, 3, state + 0x290);
        *(float *)(state + 0x2B0) = *(float *)(state + 0x2B4) = *(float *)(state + 0x2B8) = 0.0001f;
        *(unsigned char *)(state + 0x292) = 1;
        vec_random_direction((char *)vec, 0.020000001f, 0.060000002f);
        func_PAL_002B15D8(self, 0x20, (char *)vec, 3.0f, 6.0f, 3.0f, 6.0f, 0xFF);
    }
    *(int *)(self + 0x98) = 0;
    *(unsigned short *)(self + 0x34) &= 0xEFFF;
    if (flag1 == 0)
        moby_set_anim_type_three_pal(self, 0, -1);
    if (flag2 == 0)
        part_queue_moby_for_glow(self, 0, enemy_release_effect_record);
    else
        enemy_release_effect_record(self);
}
