#include "include_asm.h"

#include "common.h"
extern void func_PAL_L00_00416638(void *);
extern void ref_L00_00410D20_00(void (*)(void *), void *);
extern void func_PAL_L00_004169B0(void *);
extern void set_moby_color(void *, int, int, int);
extern int FastTweenColor(int, int, float);
extern float math_fast_sin_or_cos_a(float);
extern void target_apply_slot_color(void *);
extern void vec_clear_128(void *);
extern void tumbling_piece_spawn(void *, void *, void *, void *, void *, int, int, int, void *, float);
extern int math_random_int_range(int, int);
extern void vec_build_spherical_offset(void *, float, float, float);
extern float math_random_angle(void);
extern float math_random_float_range(float, float);
extern int func_001163B0(void);
extern int coll_process_hit(void *, int, void *, int, float);
extern int vec_fast_helper_b(void *);
extern int math_fast_float_d(void *);
extern float FastAddRotations(float, float);
typedef struct {
    char data[0x18];
    char *target;
    char end[0x14];
} ParticleEffectSlot;
extern char g_hero_state[];
extern ParticleEffectSlot ref_L00_00410D20_01[];
extern char *ref_L00_00410D20_02[];

void func_PAL_L01_004186E8(char *m) {
    float a[4], b[4];
    int i;

    qcopy_nc(m + 0x10, g_hero_state);
    for (i = 0; i < 30; i++) {
        char *s;
        char *other;
        int dead;

        if (!ref_L00_00410D20_01[i].target)
            continue;
        s = (char *)&ref_L00_00410D20_01[i];
        *(float *)(s + 0xC) = FastAddRotations(*(float *)(s + 0xC), 0.25132746f);
        dead = 0;
        if (*(signed char *)(*(char **)(s + 0x18) + 0x20) < 0)
            dead = 1;
        if (!*(int *)(*(char **)(s + 0x18) + 0x98))
            dead = 1;
        if (math_fast_float_d(s))
            dead = 1;
        if (vec_fast_helper_b(s + 0x1C)) {
            int count, j;
            char *target = *(char **)(s + 0x18);

            *(float *)(s + 0x1C) = *(float *)(s + 0x14);
            count = coll_process_hit(target + 0x10, 0, target, 0, 8.0f);
            for (j = 0; j < count; j++) {
                other = ref_L00_00410D20_02[j];
                if ((*(unsigned short *)(other + 0x34) & 0x1000) && other &&
                    *(unsigned char *)(other + 0x20) != 254 && *(unsigned char *)(other + 0x20) != 253 &&
                    *(short *)(*(char **)(other + 0x24) + 0x46) == 5)
                    goto collide;
            }
        }
    random_particles:
        if (func_001163B0() % 11 == 0) {
            int j, count;

            {
                float scale = math_random_float_range(0.3f, 0.65f) * 0.0009764999849721789f;
                float x = *(float *)(*(char **)(s + 0x18) + 0xC) * scale;
                float y = math_random_angle();
                float z = math_random_angle();

                vec_build_spherical_offset(a, x, y, z);
            }
            {
                float scale = math_random_float_range(0.3f, 0.65f) * 0.0009764999849721789f;
                float x = *(float *)(*(char **)(s + 0x18) + 0xC) * scale;
                float y = math_random_angle();
                float z = math_random_angle();

                vec_build_spherical_offset(b, x, y, z);
            }
            j = math_random_int_range(5, 15);
            count = math_random_int_range(15, 30);
            tumbling_piece_spawn(m, *(char **)(s + 0x18), *(char **)(s + 0x18), a, b, 0, j, count, s, 0.0f);
        }
        if (dead) {
            target_apply_slot_color(s);
            *(char **)(s + 0x18) = 0;
            continue;
        }
        goto timer;
    collide:
        vec_clear_128(a);
        tumbling_piece_spawn(m, *(char **)(s + 0x18), other, a, a, 1, 10, 30, s, *(float *)(s + 0x10));
        tumbling_piece_spawn(m, *(char **)(s + 0x18), other, a, a, 0, 10, 30, s, 0.0f);
        goto random_particles;
    timer:
        if (*(int *)(s + 0x24) == 0) {
            int c = FastTweenColor(*(int *)(s + 4), *(int *)(s + 8),
                                  (math_fast_sin_or_cos_a(*(float *)(s + 0xC)) + 1.0f) * 0.5f);

            set_moby_color(*(char **)(s + 0x18), c & 255, (c >> 8) & 255, (c >> 16) & 255);
        } else
            --*(int *)(s + 0x24);
    }
    func_PAL_L00_004169B0(m);
    ref_L00_00410D20_00(func_PAL_L00_00416638, m);
}

