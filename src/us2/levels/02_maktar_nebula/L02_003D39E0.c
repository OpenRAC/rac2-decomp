#include "include_asm.h"
#include "names.h"

typedef int TI128 __attribute__((mode(TI)));

extern void armed_enemy_release_held_object(char *, TI128 *);
extern void enemy_release_effect_record(char *);
extern void moby_set_anim_type_three(char *, int, int);
extern void part_queue_moby_for_glow(char *, int, void *);
extern void mem_clear(void *, int, int);
extern void AttachManipulator(char *, int, void *);
extern void vec_random_direction(char *, float, float);
extern void part_spawn_masked_debris(char *, int, char *, float, float, float, float, int);

/* func_US2_L02_003D39E0, the USA v2.00 copy of func_L02_003D2488: the same C, plus clearing
   bit 0x1000 of the halfword at +0x34. */
void armed_enemy_drop_held_and_reset_us2(char *self, int flag1, int flag2) {
    char *state = *(char **)(self + 0x68);
    float vec[4];

    if (*(char **)(state + 0x2E4) != 0) {
        *(TI128 *)vec = *(TI128 *)(*(char **)(state + 0x2E4) + 0x10);
        armed_enemy_release_held_object(self, (TI128 *)vec);
    }
    if (*(unsigned char *)(state + 0x291) == 0) {
        mem_clear(state + 0x290, 0, 0x40);
        AttachManipulator(self, 3, state + 0x290);
        *(float *)(state + 0x2B0) = *(float *)(state + 0x2B4) = *(float *)(state + 0x2B8) = 0.0001f;
        *(unsigned char *)(state + 0x292) = 1;
        vec_random_direction((char *)vec, 0.016666668f, 0.050000004f);
        part_spawn_masked_debris(self, 0x20, (char *)vec, 3.0f, 6.0f, 3.0f, 6.0f, 0xFF);
    }
    *(int *)(self + 0x98) = 0;
    *(unsigned short *)(self + 0x34) &= 0xEFFF;
    if (flag1 == 0)
        moby_set_anim_type_three(self, 0, -1);
    if (flag2 == 0)
        part_queue_moby_for_glow(self, 0, enemy_release_effect_record);
    else
        enemy_release_effect_record(self);
}
