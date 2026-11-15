#include "include_asm.h"

#include "common.h"
typedef int Q __attribute__((mode(TI)));
typedef union {
    Q q;
    float f[4];
} Vector;
typedef struct {
    char pad[0x80];
    float pos[4];
} Hero;
extern Hero g_hero_state;
extern float D_L20_001B1FE4 __attribute__((sda));
extern float D_L20_001B1FE8 __attribute__((sda));
extern Vector D_L20_001B2010 SDATA(D_L20_001B2010);
extern void yeedil_small_enemy_init_damage(char *), moby_mark_spawned(char *);
extern void moby_enter_state_six(char *), moby_set_state(char *, int, int);
extern void func_PAL_002A7E68(char *, int, int, int);
extern void matrix_mul_vec3(void *, void *, void *), FastVecAdd(void *, void *, void *);
extern void cam_moby_update(char *), euler_rotation_basis(void *, void *);
extern void ApproachValue(void *, float, float), vec_fast_normalize_helper(void *, void *, float);
extern float D_L20_001B2BE8;
extern float math_random_signed_float_range(float, float);
extern int FloatToInt(float);
extern char *part_find_owned_effect_slot(char *, int, int);
extern float func_PAL_002AA108(char *, char *);
extern void FastVecSub(void *, void *, void *);
extern int func_PAL_002B1A50(char *, char *, int);
extern int weapon_select_aim_target(char *, int, void *, int, float, float);

void func_PAL_L20_00445668(char *arg0) {
    char *st = *(char **)(arg0 + 0x68);
    Vector a;
    Vector b;

    if (*(unsigned char *)(arg0 + 0x20) == 0) {
        *(float *)(st + 0x170) = 0.5f;
        *(unsigned char *)(st + 0x150) = 5;
        *(int *)(st + 0x188) = 2;
        *(float *)(st + 0x174) = 0.6f;
        *(float *)(st + 0x17C) = 0.15f;
        *(float *)(st + 0x84) = 0.05f;
        *(float *)(st + 0x54) = 0.3f;
        *(float *)(st + 0x50) = 0.5f;
        *(float *)(st + 0x58) = 0.4f;
        *(float *)(st + 0x5C) = 2.0f;
        *(float *)(st + 0x60) = 1.57079649f;
        *(float *)(st + 0x80) = 0.785398245f;
        {
            float angle = math_random_signed_float_range(18.0f, 22.0f) * 0.0174532942f;
            float speed = D_L20_001B1FE4 * 0.020000001f;
            float accel = D_L20_001B1FE8 * 0.00040000002f;

            *(short *)(st + 0x132) = 0x64;
            *(short *)(st + 0x134) = 0x96;
            *(float *)(st + 0x12C) = angle;
            *(float *)(st + 0x78) = speed;
            *(float *)(st + 0x70) = accel;
            *(float *)(st + 0x74) = accel;
        }
        *(int *)(st + 0x88) |= 0x200;
        *(unsigned char *)(st + 0x48) = FloatToInt(8.0f);
        *(unsigned char *)(st + 0x4A) = FloatToInt(12.0f);
        *(unsigned char *)(st + 0x29) = 1;
        if (*(short *)(st + 0x24) == 0) {
            *(short *)(st + 0x24) = 3;
            *(float *)(st + 0x20) = 3.0f;
        }
        *(int *)(arg0 + 0x98) = 0;
        *(unsigned short *)(arg0 + 0x34) = (*(unsigned short *)(arg0 + 0x34) | 0x41) & 0xEFFF;
        moby_set_state(arg0, 6, 3);
        if (*(unsigned char *)(arg0 + 0x43) != 0) {
            func_PAL_002A7E68(arg0, 0, 0, 0);
        }
    }

    *(float *)(st + 0x180) = D_L20_001B2BE8;
    if (*(unsigned char *)(arg0 + 0x20) == 6) {
        return;
    }
    if (*(unsigned char *)(st + 0x2E) == 2) {
        *(int *)(arg0 + 0x98) = 0;
        *(unsigned short *)(arg0 + 0x34) = (*(unsigned short *)(arg0 + 0x34) | 0x41) & 0xEFFF;
        moby_set_state(arg0, 6, 3);
    }
    *(unsigned char *)(st + 0x2E) = 1;

    if (*(unsigned char *)(arg0 + 0x20) == 7 && *(float *)(st + 0x20) > 0.0f) {
        char *hit = part_find_owned_effect_slot(arg0, 0x10000, 0);
        float damage = func_PAL_002AA108(arg0, hit);

        ApproachValue(st + 0x20, 0.0f, damage);
        *(unsigned char *)(arg0 + 0xA8) = 0xFF;
        if (*(float *)(st + 0x20) <= 0.0f) {
            *(float *)(arg0 + 0xF4) = 0.0f;
            *(float *)(arg0 + 0xF0) = 0.0f;
            matrix_mul_vec3(&a, st + 0x230, arg0 + 0xC0);
            euler_rotation_basis(arg0 + 0xC0, arg0 + 0xF0);
            matrix_mul_vec3(&b, st + 0x230, arg0 + 0xC0);
            FastVecSub(&b, &b, &a);
            FastVecSub(arg0 + 0x10, arg0 + 0x10, &b);
        }
    } else {
        func_PAL_002B1A50(arg0, st + 0x140, 0);
    }
    weapon_select_aim_target(arg0, *(int *)(st + 0x270), 0, 0, 64.0f, 0.0f);

    if (*(int *)(st + 0x204) == 0) {
        char *g = (char *)&g_hero_state;

        *(char **)(st + 0x200) = *(char **)(g + 0x2290);
        qcopy(st + 0x1F0, *(char **)(g + 0x2290) + 0x10);
        *(int *)(st + 0x204) = 1;
    }
}
