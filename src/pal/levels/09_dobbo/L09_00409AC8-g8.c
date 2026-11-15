#include "include_asm.h"
#include "common.h"
extern f32 D_L09_001B13F0 __attribute__((sda));
extern f32 D_L09_001B13F4 __attribute__((sda));
extern s32 D_L09_001A79F0 __attribute__((sda));
extern s32 D_L09_001A9040 __attribute__((sda));
extern char *D_L09_001B285C __attribute__((sda));
extern s32 func_323340(char *a0, char *a1, s32 a2);
extern int moby_is_hero_or_special(char *a0);
extern s32 g_current_map_index;
extern void dobbo_wandering_init_vars(void);
extern float fast_vec_dist(char *a0, char *a1);
extern void moby_update_ground_check(void *a0);
extern s32 moby_apply_damage_to_object(char *a0, char *a1, s32 a2);
extern void dobbo_alert_wandering_group(char *a0);
extern void dobbo_destroy_with_debris(char *a0);
extern s32 weapon_select_aim_target(char *a0, s32 a1, s32 a2, s32 a3, f32 f12, f32 f13);
extern char D_L09_001B9A00[];
extern s32 D_L09_001B2878;
extern u8 *D_L09_001B285C_1;
extern s32 D_L09_001B1420[2];
extern s32 FastTweenColor(s32, s32, f32);
extern s32 D_L09_001B2388;
extern f32 FastAddRotations(f32, f32);
extern f32 math_fast_sin_or_cos_b(f32);

/* Releases the record the sub-object holds once the resident mode word says 9, then
   rebuilds the sub-object's effect. */
void func_PAL_L09_00409DC8(char *a0) {
    char *s0 = a0;
    char *s1 = *(char **)(s0 + 0x68);
    s32 s2;
    s16 idx;

    if (*(u8 *)(s0 + 0x20) == 0) {
        dobbo_wandering_init_vars();
    }
    if (*(u8 *)(s0 + 0x31) != 0) {
        if (fast_vec_dist(s0 + 0x10, D_L09_001B9A00) < 24.0f) {
            moby_update_ground_check(s0);
            *(u8 *)(s0 + 0x6F) = 0x16;
        }
    }
    s2 = moby_apply_damage_to_object(s0, s1 + 0x50, 0);
    if (g_current_map_index == 9) {
        idx = *(s16 *)(s1 + 0xC0);
        if (idx != -1) {
            if (moby_is_hero_or_special(D_L09_001B285C + (idx << 8)) == 0) {
                D_L09_001A9040 = 0;
            }
            *(s16 *)(s1 + 0xC0) = -1;
        }
    }
    if (s2 != 0) {
        dobbo_alert_wandering_group(s0);
        if (s2 >= 4) {
            dobbo_destroy_with_debris(s0);
        }
    }
    if (*(u8 *)(s0 + 0x95) != 3 && *(u8 *)(s0 + 0x95) != 4) {
        *(s16 *)(s1 + 0x334) = weapon_select_aim_target(s0, *(s32 *)(s1 + 0x230), 0, 0, 16.0f, 0.0f);
    }
}

extern float D_L09_001B13F4 __attribute__((sda));
extern float math_random_float_range(float, float);
extern int FloatToInt(float);
extern float math_random_signed_float_range(float, float);
extern float math_random_angle(void);
extern void moby_set_state(char *, int, int);
extern void func_PAL_002A7E68(char *, int, int, int);
typedef struct DobboEmitter {
    u8 pad_0[0x28];
    u8 f_28;
    u8 pad_29[0x1];
    u8 f_2A;
    u8 pad_2B[0x5];
    float f_30;
    u8 pad_34[0x14];
    u8 f_48;
    u8 pad_49[0x1];
    u8 f_4A;
    u8 pad_4B[0x15];
    u8 f_60;
    u8 pad_61[0x1F];
    float f_80;
    float f_84;
    u8 pad_88[0x4];
    float f_8C;
    u8 pad_90[0x8];
    s32 f_98;
    u8 pad_9C[0x64];
    float f_100;
    float f_104;
    float f_108;
    float f_10C;
    float f_110;
    u8 pad_114[0x1C];
    float f_130;
    float f_134;
    s32 f_138;
    s32 f_13C;
    u8 pad_140[0x90];
    float f_1D0;
    float f_1D4;
    u8 pad_1D8[0x4];
    float f_1DC;
    u8 pad_1E0[0x2];
    short f_1E2;
    short f_1E4;
    u8 pad_1E6[0x2];
    u8 f_1E8;
    u8 f_1E9;
    u8 pad_1EA[0x4A];
    s32 f_234;
    u8 pad_238[0x10C];
    float f_344;
    float f_348;
} DobboEmitter;

/* Runs on the object's first update: copies its position into the record, rolls its size and
   timings and fills in the record's defaults. */
void func_PAL_L09_00409BC0(char *obj)
{
    DobboEmitter *rec = *(DobboEmitter **)(obj + 0x68);
    float size, spin;
    int count;

    qcopy((char *)rec + 0x300, obj + 0x10);
    size = math_random_float_range(1.0f, 1.333f);
    rec->f_344 = size;
    *(float *)(obj + 0x2C) = *(float *)(*(char **)(obj + 0x24) + 0x24) * size;
    rec->f_48 = FloatToInt(15.0f);
    rec->f_4A = FloatToInt(4.0f);
    count = 3;
    rec->f_98 = count;
    rec->f_8C = 0.4f;
    rec->f_60 = 0xB;
    rec->f_30 = 0.333f;
    rec->f_2A = 2;
    rec->f_84 = rec->f_80 = 0.2f;
    rec->f_28 = count;
    rec->f_134 = 0.05f;
    rec->f_104 = rec->f_344 * 0.1f;
    rec->f_110 = 0.17453295f;
    rec->f_130 = 0.52359885f;
    rec->f_100 = rec->f_344 * 0.3f;
    rec->f_10C = rec->f_108 = 0.1f;
    rec->f_138 |= 0x80;
    spin = math_random_signed_float_range(18.0f, 22.0f);
    rec->f_1E8 = 7;
    rec->f_1E9 = 6;
    rec->f_1DC = spin * 0.017453294f;
    rec->f_1E2 = 0x64;
    rec->f_1E4 = 0x96;
    rec->f_13C = rec->f_234;
    rec->f_1D4 = 1.75f;
    rec->f_1D0 = D_L09_001B13F4 * 0.020000001f;
    rec->f_348 = math_random_angle();
    moby_set_state(obj, 1, 0);
    if (*(u8 *)(obj + 0x43) != 0)
        func_PAL_002A7E68(obj, 0, 0, 0);
    *(s32 *)(obj + 0x9C) = 0xC;
    *(unsigned short *)(obj + 0x34) |= 0x1000;
}
