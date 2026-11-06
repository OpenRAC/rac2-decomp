/* func_PAL_L05_0041E068, the PAL copy of func_L05_00419370: the same C, where both effect lifetimes are scaled for 50 Hz. */
#include "common.h"

extern int D_001A79F0;
typedef struct { char pad[0x68]; char *state; char rest[0x94]; } EffectOwner;
extern EffectOwner *D_L05_001B251C;
extern int D_L05_001B1024 __attribute__((sda));
/* The resident level index is also read through its GP address view. */
extern int current_level_gp SDATA(D_001A79F0);
extern float D_L05_001A8F20[4] __attribute__((sda));
extern int func_002ACCA8(void *, int);
extern void func_00282F20(void *, void *, float);
extern void func_00282CC0(void *, void *, void *);
extern float func_002A7878(float, float);
extern void func_00281EB8(void *, int, int, int, float, float, float);
extern char *func_002BDCE8(void *, float, float, int, void *, int, float, float, int);
extern int func_002A7820(int, int);
extern int func_00283CF0(float);

void func_PAL_L05_0041E068(char *object)
{
    float local[4];
    char *state = *(char **)(object + 0x68);
    char *other;
    char *axis;
    float t, a;
    char *effect, *detail;
    int kind, scale;

    if (D_001A79F0 == 5 || D_001A79F0 == 25) {
        other = ((EffectOwner *)((char *)D_L05_001B251C + (*(int *)(state + 0xA4) << 8)))->state;
        if (D_001A79F0 == 25 ||
            (!func_002ACCA8(object + 0x10, *(int *)(other + 4)) &&
             !func_002ACCA8(object + 0x10, *(int *)(other + 8)) &&
             !func_002ACCA8(object + 0x10, *(int *)(other + 12)) &&
             !func_002ACCA8(object + 0x10, *(int *)(other + 16)))) {
            char *p;
            float *life;
            int i;

            axis = object + 0xC0;
            p = state + 0xB0;
            life = (float *)(state + 0x1B0);
            for (i = 15; i >= 0; i--) {
                if (*life <= 0.0f) {
                    qcopy(p, axis);
                    *(float *)(p) += func_002A7878(-0.2f, 0.2f);
                    *(float *)(p + 4) += func_002A7878(-0.2f, 0.2f);
                    *(float *)(p + 8) += func_002A7878(-0.2f, 0.2f);
                    func_00282F20(p, p, func_002A7878(24.0f, 30.0f));
                    func_00282CC0(p, p, object + 0x10);
                    *life = func_002A7878(11.0f, 14.0f);
                }
                qcopy(local, axis);
                t = func_002A7878(0.15f, 0.25f);
                func_00282F20(local, local, -t);
                *life -= t;
                func_00282CC0(p, p, local);
                a = func_002A7878(0.07f, 0.12f);
                t = func_002A7878(0.0f, 1.0f);
                func_00281EB8(p, 0x47, 0x7F7F6464, 0, a, 0.0f, t);
                life++;
                p += 16;
            }
        }
    }
    if (D_L05_001B1024 && current_level_gp == 15) {
        float *life = (float *)(state + 0x1B0);
        int i;

        axis = object + 0xC0;
        kind = 0x44;
        scale = 6;
        state += 0xB0;
        for (i = 3; i >= 0; i--) {
            if (*life <= 0.0f) {
                qcopy(state, axis);
                *(float *)state += func_002A7878(-0.2f, 0.2f);
                *(float *)(state + 4) += func_002A7878(-0.2f, 0.2f);
                *(float *)(state + 8) += func_002A7878(-0.2f, 0.2f);
                func_00282F20(state, state, func_002A7878(15.0f, 30.0f));
                func_00282CC0(state, state, object + 0x10);
                *life = func_002A7878(10.0f, 30.0f);
            }
            qcopy(local, axis);
            t = func_002A7878(0.15f, 0.25f);
            func_00282F20(local, local, -t);
            *life -= t;
            func_00282CC0(state, state, local);
            effect = func_002BDCE8(state, 2.0f, 1.03f, 1, D_L05_001A8F20, 0x0A786E64, 1.045f, 210000.0f, 0);
            if (effect) {
                effect[3] = kind;
                *(short *)(effect + 10) = (func_002A7820(40, 70) * 5 + 2) / scale;
            }
            effect = func_002BDCE8(state, 1.8f, 1.03f, 1, D_L05_001A8F20, 0x0AADA196, 1.045f, 210000.0f, 0);
            if (effect) {
                effect[3] = kind;
                detail = effect + 0x20;
                *(short *)(effect + 10) = (func_002A7820(40, 70) * 5 + 2) / scale;
                effect[9] = func_00283CF0(4.0f) + 0x40;
                *(float *)(detail + 0x1C) = 20.0f;
                *(int *)(detail + 4) = 3;
                detail[10] = 0x7F;
                detail[11] = effect[10];
            }
            state += 16;
            life++;
        }
    }
}
