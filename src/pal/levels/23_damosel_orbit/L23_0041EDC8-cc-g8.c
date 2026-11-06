#include "common.h"

typedef int TI128 __attribute__((mode(TI)));

extern int D_L23_001B1438 __attribute__((sda));

extern int D_L23_001B1440 __attribute__((sda));

extern float D_L23_001B1448 __attribute__((sda));

extern int D_L23_001B3724;

extern int D_L23_001B1460 __attribute__((sda));

extern int D_L23_001B1464 __attribute__((sda));

extern int D_L23_001B372C;

extern int D_L23_001B3730;

extern void func_0029F978(char *, int, char *);

extern void func_00282D30(char *, char *, float);

extern void func_00283898(void *, int, float);

/* func_PAL_L23_0041EDC8, the PAL copy of func_L23_00419D60: the same C, with the two durations scaled for 50 Hz. */
/* Advances the three-phase transition and updates its state vectors. */
void func_PAL_L23_0041EDC8(char *obj) {
    char *state = *(char **)(obj + 0x68);
    float scale;
    float active_fade, inactive_fade, active_duration, inactive_duration;
    union {
        TI128 q;
        float f[4];
    } vec;

    if ((unsigned char)(*(unsigned char *)(obj + 0x20) - 8) < 3) {
        scale = 0.0f;
        if (D_L23_001B1438 == 0) {
            D_L23_001B1438 = 1;
            D_L23_001B3724 = D_L23_001B1440;
        } else if (D_L23_001B1438 != 2) {
            if (*(unsigned char *)(state + 0x471) == 0)
                func_0029F978(obj, 0x26, state + 0x470);
            vec.q = 0;
            vec.f[2] = 1.0f;
            vec.f[3] = 1.0f;
            scale = (float)(D_L23_001B1440 - D_L23_001B3724) * D_L23_001B1448;
            func_00282D30(state + 0x4A0, (char *)&vec, scale);
            D_L23_001B3724 = D_L23_001B3724 - 1;
            if (D_L23_001B3724 == -1)
                D_L23_001B1438 = 2;
        } else {
            D_L23_001B3724 = D_L23_001B1440;
            if (*(unsigned char *)(state + 0x471) == 0)
                func_0029F978(obj, 0x26, state + 0x470);
            vec.q = 0;
            vec.f[2] = 1.0f;
            vec.f[3] = 1.0f;
            scale = (float)D_L23_001B1440 * D_L23_001B1448;
            func_00282D30(state + 0x4A0, (char *)&vec, scale);
            if (*(unsigned char *)(state + 0x4B1) == 0)
                func_0029F978(obj, 0x27, state + 0x4B0);
            *(float *)(state + 0x578) = 1.4726216f;
            func_00283898(state + 0x4C0, 1, 1.4726216f);
        }
        qzero_nc(state + 0x480);
        active_duration = D_L23_001B1448 * (float)D_L23_001B1440 * 4.0f;
        *(unsigned char *)(state + 0x473) = 1;
        *(float *)(state + 0x47C) = 1.0f;
        *(float *)(state + 0x48C) = 1.0f;
        *(float *)(state + 0x49C) = 1.0f;
        active_fade = 1.0f - scale / active_duration;
        *(float *)(state + 0x498) = active_fade;
        *(float *)(state + 0x494) = active_fade;
        *(float *)(state + 0x490) = active_fade;
    } else if (D_L23_001B1438 != 0) {
        if (*(unsigned char *)(state + 0x471) == 0)
            func_0029F978(obj, 0x26, state + 0x470);
        vec.q = 0;
        vec.f[2] = 1.0f;
        vec.f[3] = 1.0f;
        scale = (float)D_L23_001B3724 * D_L23_001B1448;
        func_00282D30(state + 0x4A0, (char *)&vec, scale);
        D_L23_001B3724 = D_L23_001B3724 - 1;
        if (D_L23_001B3724 == -1) {
            D_L23_001B1438 = 0;
            D_L23_001B372C = ((s32)(D_L23_001B1460) * 5 + 2) / 6;
            D_L23_001B3730 = ((s32)(D_L23_001B1464) * 5 + 2) / 6;
        }
        qzero_nc(state + 0x480);
        inactive_duration = D_L23_001B1448 * (float)D_L23_001B1440;
        *(unsigned char *)(state + 0x473) = 1;
        *(float *)(state + 0x47C) = 1.0f;
        *(float *)(state + 0x48C) = 1.0f;
        *(float *)(state + 0x49C) = 1.0f;
        inactive_fade = 1.0f - scale / (inactive_duration * 2.0f);
        *(float *)(state + 0x498) = inactive_fade;
        *(float *)(state + 0x494) = inactive_fade;
        *(float *)(state + 0x490) = inactive_fade;
    }
}
