#include "include_asm.h"

#include "common.h"
extern void moby_set_state(void *, int, int);
extern char *part_find_owned_effect_slot(void *, int, int);
extern float math_random_angle(void);
extern float math_random_float_range(float, float);
extern float math_fast_sin_or_cos_a(float), math_fast_sin_or_cos_b(float);
extern void *func_PAL_00303578(void *, void *, void *, int, int, int);
extern int D_L03_001AEC30 __attribute__((sda));
extern char D_L03_001AEC10[8] __attribute__((sda)), D_L03_001AEC08[8] __attribute__((sda)), D_L03_001AEC00[8] __attribute__((sda));
extern void func_PAL_L00_0032C328(void *, void *, void *, void *, int, int, int, int, int, int, int);
extern char *func_PAL_L00_003FB330(void *, int, int, int, int, int, int, int, int, int, int, int, float, float);
extern void moby_mark_spawned(void *);
extern int flag_set_first_pending(void *);
extern void timer_start_countdown(int, float);
extern float D_L03_001B2460;
extern char *CreateMoby(int);
extern char D_L03_001B9980[];
extern int D_L03_001A8FB4, D_L03_001A8FB0;

void func_PAL_L03_00386E60(char *m)
{
    float pos[4], vel[4];
    int i;
    char *p;
    switch (*(unsigned char *)(m + 0x20)) {
    case 0:
        *(unsigned short *)(m + 0x34) |= 0x1000;
        moby_set_state(m, 1, -1);
        break;
    case 1: {
        char *hit;
        hit = part_find_owned_effect_slot(m, 0x4010000, 0);
        if (hit) {
            hit = *(char **)(hit + 0x20);
            if (hit && *(short *)(hit + 0xAA) == 0x825)
                moby_set_state(m, 3, -1);
            else moby_set_state(m, 2, -1);
        }
        *(unsigned char *)(m + 0xA8) = 0xFF;
        break;
    }
    case 2: {
        char *position = m + 0x10;
        if (!D_L03_001AEC30) {
            D_L03_001AEC30 = 1;
            qcopy(pos, position);
            pos[2] += 0.5f;
            i = 9;
            do {
                float angle, speed;
                i--;
                angle = math_random_angle();
                speed = math_random_float_range(0, 1) * (0.020000001f);
                vel[0] = math_fast_sin_or_cos_a(angle) * speed;
                vel[1] = math_fast_sin_or_cos_b(angle) * speed;
                vel[2] = 0;
                vel[2] = math_random_float_range(5, 10) * (0.020000001f);
                func_PAL_00303578(m, pos, vel, 0, 100, 0);
            } while (i >= 0);
        }
        func_PAL_L00_0032C328(m, D_L03_001AEC10, D_L03_001AEC08, D_L03_001AEC00, 65535, 0, -1, 6, 65535, 255, 0);
        func_PAL_L00_003FB330(position, 0, 25, 20, 20, 20, 45, 1, 1, 1, 0, 0, 0.5f, 20);
        moby_mark_spawned(m);
        break;
    }
    case 3:
        if (flag_set_first_pending(m)) timer_start_countdown(1, 15);
        if (D_L03_001B2460 >= 1) {
            p = CreateMoby(0x1335);
            if (p) {
                qcopy(p + 0x10, D_L03_001B9980);
                *(unsigned char *)(p + 0x30) = 255;
            }
            D_L03_001A8FB4 = 2;
            D_L03_001A8FB0 = 12;
            moby_set_state(m, 1, -1);
        } else {
            unsigned int count = *(unsigned short *)(m + 0x96);
            unsigned int old = count++;
            *(unsigned short *)(m + 0x96) = count;
            if (old >= 51) moby_set_state(m, 1, -1);
        }
        break;
    }
}
