#include "include_asm.h"
#include "names.h"

typedef unsigned char u8;
extern int PlayMobySound(int index, int a1, char *a2);
extern u8 D_001A63A8_4[];
extern int math_random_int_below(int a0);
extern u8 g_hero_state[];
extern void moby_mark_spawned(void *);
extern void *part_find_owned_effect_slot(void *a0, int a1, int a2);
extern int math_random_int_below(int a0);
extern int snd_play_from_class_bank(int index, int value, char *object, int kind);
extern void func_PAL_002AD288(void *a0, void *a1, int a2, float f12, float f13);
extern int PlayMobySound(int index, int a1, char *a2);
extern void vec_scale_to_length(float *a0, void *a1, float f12);
extern void func_PAL_002B15D8(void *a0, int a1, void *a2, unsigned char a3,
                           float f12, float f13, float f14, float f15);
extern void moby_mark_spawned(void *object);
extern void moby_explode(u8 *a0, int a1, int a2);

void func_PAL_L22_003D8290(u8 *a0, int a1, int a2) {
    u8 *s0 = a0;
    void *s3;
    int s2;
    int s1;
    float buf[4];

    s3 = part_find_owned_effect_slot(a0, -1, 0);
    if (s3 == 0)
        return;
    if (*(short *)(s0 + 0xAA) == 0x1213) {
        s2 = 0xB;
        s1 = 0xF7F;
    } else {
        s2 = 0xC;
        s1 = 0xE0B;
    }
    snd_play_from_class_bank(s2 + math_random_int_below(3), 0, s0, s1);
    func_PAL_002AD288(s0, s0 + 0x10, -1, 2.0f, 13.0f);
    PlayMobySound(0, 0, s0);
    vec_scale_to_length(buf, s3 + 0x10, 0.28000003f);
    func_PAL_002B15D8(s0, 3, buf, 0xFF, 3.0f, 6.0f, 3.0f, 6.0f);
    moby_mark_spawned(s0);
}
