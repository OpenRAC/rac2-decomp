#include "include_asm.h"

#include "common.h"
extern void *part_find_owned_effect_slot(void *, int, int);
extern s32 math_random_int_below(int);
extern int snd_play_from_class_bank(char *, int, void *, int);
extern void func_PAL_002AD288(void *, void *, int, float, float);
extern void moby_mark_spawned(void *object);

void func_PAL_L22_003EC9E0(u8 *a0, int a1, int a2) {
    u8 *s0 = a0;
    void *s3;
    s3 = part_find_owned_effect_slot(a0, -1, 0);
    if (s3 == 0)
        return;
    snd_play_from_class_bank(0xC + math_random_int_below(3), 0, s0, 0xE0B);
    func_PAL_002AD288(s0, s0 + 0x10, -1, 2.0f, 13.0f);
    moby_mark_spawned(s0);
}
