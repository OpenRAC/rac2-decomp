#include "include_asm.h"

#include "common.h"
extern float D_L23_001B13C8 __attribute__((sda));
extern float D_L23_001B13CC __attribute__((sda));
extern char *g_mothership_boss_moby __attribute__((sda));
extern char D_L23_001BA500[];
extern char *part_find_owned_effect_slot(char *, int, int);
extern void FastDecTimer(char *);
extern int mothership_is_held(void);
extern void func_PAL_L23_00423838(void);
extern void func_PAL_002AC290(char *, char *);
extern void func_PAL_002AC3C0(char *, char *);
extern void func_PAL_L23_004217B0(char *);
extern void mothership_attach_hit_effect(char *);
extern float math_random_signed_float_range(float, float);
extern float FastAddRotations(float, float);
extern float math_random_float_range(float, float);
extern float math_fast_sin_or_cos_a(float);
extern float math_fast_sin_or_cos_b(float);
extern char *func_PAL_002735D0(char *, int, int, int, char *, char *, float *, float, float, int);
extern void func_PAL_003120C0(void);

/* Updates the hit state of the object, and when its mask word still has bits set, spawns one
   particle per set bit (at most ten, fewer the fuller the value at +0x20 is), each launched at
   a random angle and speed, and clears the bit. */
void func_PAL_L23_0041B078(char *arg0) {
    char *state = *(char **)(arg0 + 0x68);
    char *hit;
    int n;
    int i;
    float vec[3];

    hit = part_find_owned_effect_slot(arg0, 0x30000, 1);
    *(unsigned char *)(arg0 + 0xA8) = 0xFF;
    FastDecTimer(state + 0x26);
    if (hit != 0) {
        if (*(short *)(state + 0x26) != 0 || (g_mothership_boss_moby != 0 && mothership_is_held() != 0)) {
            if (mothership_is_held() != 0)
                func_PAL_L23_00423838();
            hit = 0;
        }
    }
    if (hit != 0) {
        *(unsigned char *)(state + 0x147) = 0xFF;
        func_PAL_002AC290(arg0, state + 0x140);
        func_PAL_L23_004217B0(*(char **)(hit + 0x20));
        if (*(float *)(state + 0x20) <= D_L23_001B13CC) {
            mothership_attach_hit_effect(hit);
            *(float *)(state + 0x20) = D_L23_001B13CC;
        } else {
            *(float *)(state + 0x20) = *(float *)(state + 0x20) - *(float *)(hit + 0x2C);
        }
        if (*(float *)(state + 0x20) <= D_L23_001B13CC)
            *(float *)(state + 0x20) = D_L23_001B13CC;
        if (*(short *)(*(char **)(hit + 0x20) + 0xAA) != 0x118F)
            *(short *)(state + 0x26) = 0x11;
        if (*(unsigned short *)(arg0 + 0x7C) != 0) {
            float f;

            f = *(float *)(state + 0x20) / D_L23_001B13C8;
            n = 10 - (int)(f * 10.0f);
            if (*(float *)(state + 0x20) <= D_L23_001B13CC)
                n = 10;
            for (i = 0; i < n; i++) {
                int mask = *(unsigned short *)(arg0 + 0x7C);

                if ((mask >> i) & 1) {
                    float angle, speed;
                    char *p;
                    char *base = D_L23_001BA500;
                    float spread = 90.0f;
                    float per_tick = 0.020000001f;
                    float to_rad = 0.017453294f;

                    *(unsigned short *)(arg0 + 0x7C) = mask & ~(1 << i);
                    angle = FastAddRotations(math_random_signed_float_range(spread, 120.0f) * to_rad,
                                          *(float *)(base + 0x158));
                    speed = math_random_float_range(2.0f, 4.0f) * per_tick;
                    vec[0] = math_fast_sin_or_cos_a(angle) * speed;
                    vec[1] = math_fast_sin_or_cos_b(angle) * speed;
                    vec[2] = 0.0f;
                    vec[2] = math_random_float_range(5.0f, 8.0f) * per_tick;
                    p = func_PAL_002735D0(arg0, 1, *(short *)(arg0 + 0xAA), i, arg0 + 0x10, arg0 + 0xF0,
                                      vec, spread, 15.0f, 0xFF);
                    if (p != 0)
                        *(void (**)(void))(p + 0x64) = func_PAL_003120C0;
                }
            }
        }
    }
    func_PAL_002AC3C0(arg0, state + 0x140);
}
