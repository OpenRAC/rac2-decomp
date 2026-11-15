#include "include_asm.h"

#include "common.h"
extern f32 func_2E5318(f32 a, f32 b);
extern f32 func_2E4918(f32 a, f32 b);
extern f32 D_L07_001B0F84 __attribute__((sda));
extern u8 *g_moby_l07_array __attribute__((sda));
extern u8 *func_2CD050(s32 a);
extern s32 func_312FA8(u8 *a, s32 b, s32 c);
extern f32 func_313008(u8 *a, s32 b);
extern f32 D_L07_001B10B8 __attribute__((sda));
extern f32 D_L07_001B10BC __attribute__((sda));
extern u32 D_L07_001B10C0 __attribute__((sda));
extern f32 D_L07_001B0FD0 __attribute__((sda));
extern f32 D_L07_001B0E98 __attribute__((sda));
extern f32 D_L07_001B0E9C __attribute__((sda));
extern f32 D_L07_001B0EA0 __attribute__((sda));
extern f32 ApproachValue(f32 *value, f32 target, f32 step);
extern void moby_set_state(u8 *a, u8 b, s32 c);
extern f32 FastAddRotations(f32 a, f32 b);
extern s32 coll_cast_object_line(void *a, void *b, void *c, s32 d, f32 e, f32 f, s32 g, s32 h, s32 i);
extern f32 D_L07_001B173C;
extern u8 D_L07_001B1730 __attribute__((sda));
extern u16 **D_L07_001A9014;
extern u8 *D_L07_001B2954;
extern u8 *D_L07_001B295C;
extern s32 D_L07_001B1E90;
extern u8 *cam_alloc_override_slot(s32);
extern f32 func_2E49C8(f32 a, f32 b);
extern f32 func_2E5360(f32 a, f32 b);
extern f32 D_L07_001B17D4 __attribute__((sda));
extern f32 D_L07_001B17D8 __attribute__((sda));
extern u8 *D_L07_001B9250 __attribute__((nosda));
extern u8 *D_L07_001ADAAC MACRO_ADDR;
extern u8 D_L07_001B31A9;
extern u8 g_hero_state[];
extern u32 D_L07_001B1E08 MACRO_ADDR;
extern f32 fast_vec_dist(u8 *a, u8 *b);
extern f32 D_L07_001B0FD0 __attribute__((sda));
extern char g_hero_position[];
extern char D_L07_001B9200[];
extern u8 *D_L07_001C36C0[];
extern int coll_process_hit(void *, float, int, char *, void *);
extern int snd_play_from_class_bank(int, int, char *, int);
extern int coll_sweep_from_object(char *, char *, int, float, float, float, int, int, int);
extern void FastVecSub(void *, void *, void *);
extern void vec_scale_to_length(void *, void *, float);
extern void func_PAL_0032F3B8(char *, char *, char *, float);
extern void func_PAL_L07_003FB4A0(u8 *a);
extern void func_PAL_L07_003FB570(u8 *self, float *target);
extern void func_PAL_L07_003FB6B0(u8 *a0);

void func_PAL_L07_003FB110(u8 *a0)
{
    u8 *state;
    u8 *p;
    char *pos;
    char *tune;
    f32 dir[4];
    s32 n, k;

    state = *(u8 **)(a0 + 0x68);
    if (a0[0x20] != 1)
        func_PAL_L07_003FB4A0(a0);
    switch (a0[0x20]) {
    case 2:
        *(f32 *)(a0 + 0x2C) = *(f32 *)(*(u8 **)(a0 + 0x24) + 0x24) * D_L07_001B0FD0;
        func_PAL_L07_003FB570(a0, (float *)g_hero_position);
        func_PAL_L07_003FB6B0(a0);
        n = coll_process_hit(a0 + 0x10, 0.333f, 0, (char *)a0, 0);
        if (n > 0) {
            p = (u8 *)D_L07_001C36C0;
            for (k = n; k != 0; k--, p += 4) {
                u8 *other = *(u8 **)p;
                if (other == a0)
                    continue;
                if (other != *(u8 **)(a0 + 0xB8))
                    moby_set_state(a0, 3, -1);
            }
        }
        break;
    case 3:
        snd_play_from_class_bank(6, 0, (char *)a0, 0xE5F);
        pos = (char *)a0 + 0x10;
        coll_sweep_from_object((char *)a0, pos, 0x10000, 6.0f, 5.0f, 1.0f, 0, 1, 0);
        coll_sweep_from_object((char *)a0, pos, 1, 4.0f, (f32)state[0x34], 1.0f, 0, 1, 0);
        FastVecSub(dir, D_L07_001B9200, pos);
        vec_scale_to_length(dir, dir, 1.0f);
        func_PAL_0032F3B8((char *)a0, pos, (char *)dir, 0.0f);
        tune = D_L07_001B9200 - 0x140;
        *(f32 *)(tune + 0x180) = 0.1f;
        *(s32 *)(tune + 0x188) = 0x4B;
        *(f32 *)(tune + 0x160) = 0.2f;
        *(s32 *)(tune + 0x168) = 0x32;
        *(s32 *)(tune + 0x16C) = 0;
        *(s32 *)(a0 + 0x98) = 0;
        *(u16 *)(a0 + 0x34) = (*(u16 *)(a0 + 0x34) | 0x41) & 0xEFFF;
        moby_set_state(a0, 1, -1);
        break;
    }
}
