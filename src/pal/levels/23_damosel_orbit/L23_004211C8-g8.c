#include "include_asm.h"
#include "names.h"
extern char *g_mothership_boss_moby __attribute__((sda));
extern int PlayMobySound(int index, int a1, char *a2);
typedef int TI128 __attribute__((mode(TI)));
extern void matrix_mul_vec3(char *, char *, char *);
extern void FastVecAdd(char *, char *, char *);
extern void SpawnExplosion(char *, int, int, int, int, int, int, int, float, float, int, int, int, int);
extern char g_hero_state[];
extern void FastVecAdd(char *, char *, char *);

extern float math_fabs(float);
extern int D_L23_001B1694 __attribute__((sda));
extern int D_L23_001B1698 __attribute__((sda));

/* The fields of the level state, the object and the hero this function reads. */
typedef struct {
    char pad0[0x408];
    int handle;
    char pad40C[0x588 - 0x40C];
    float limit;
    char pad58C[0x5B8 - 0x58C];
    float dist;
    float range;
    float level;
} C0E8State;

typedef struct {
    char pad0[0x10];
    TI128 pos;
    unsigned char state;
} C0E8Moby;

typedef struct {
    char pad0[0x80];
    float pos[4];
    char pad90[0x1DC - 0x90];
    short busy;
    char pad1DE[0x33C - 0x1DE];
    int armed;
    int charge;
    char pad344[0x34E - 0x344];
    short heat;
} C0E8Hero;

extern int D_L23_001B141C __attribute__((sda));

extern float D_L23_001B168C __attribute__((sda));

extern float D_L23_001B1690 __attribute__((sda));

extern int D_L23_001B169C __attribute__((sda));

extern int D_L23_001B16A4 __attribute__((sda));

extern int D_L23_001B16A8 __attribute__((sda));

extern int D_L23_001B16AC __attribute__((sda));

extern float D_L23_001B16B0 __attribute__((sda));

extern float D_L23_001B36D0[4] __attribute__((sda));

extern int D_L23_001B371C;

extern int math_fast_float_d(int *);

extern void FastVecSub(float *, float *, float *);

extern void vec_scale_to_length(float *, float *, float);

extern void func_PAL_L00_003FB330(char *, int, int, int, int, int, int, int, float, float, int, int, int, int);

extern void func_PAL_L23_00423898(void *, int, int, TI128 *, float *, int);

extern int func_PAL_L23_0042B658(void *, void *, int, int, int, int, int, int, float, int, int, int, int, int);

/* func_PAL_L23_004211C8, the PAL copy of func_L23_0041C0E8: the same C, with every timer limit scaled to 50 Hz.
   The two wait extensions scale their sum, and D_L23_001B1694 is stored before D_L23_001B16A8 is cleared. */
void func_PAL_L23_004211C8(C0E8Moby *arg0) {
    C0E8State *state = *(C0E8State **)(g_mothership_boss_moby + 0x68);
    float v[4] __attribute__((aligned(16)));
    TI128 t;

    math_fast_float_d(&D_L23_001B371C);
    if (arg0->state == 0x10 && state->dist < D_L23_001B168C && state->level > state->limit &&
        math_fabs(state->level - state->limit) < D_L23_001B1690) {
        C0E8Hero *hero = (C0E8Hero *)g_hero_state;

        if (hero->charge >= 11 && D_L23_001B1694 == 0) {
            D_L23_001B16A4 = 1;
            D_L23_001B1694 = (D_L23_001B169C * 5 + 2) / 6;
            if (D_L23_001B16A8 != 0) {
                D_L23_001B1694 = (D_L23_001B1698 * 5 + 2) / 6;
                D_L23_001B16A8 = 0;
            }
        }
    }
    if (D_L23_001B1694 > 0) {
        if (D_L23_001B1694 == (D_L23_001B1698 * 5 + 2) / 6) {
            if (D_L23_001B16A4 != 0)
                D_L23_001B371C = 0;
            else
                D_L23_001B1694 = ((D_L23_001B1698 + 2) * 5 + 2) / 6;
        } else {
            C0E8Hero *hero = (C0E8Hero *)g_hero_state;

            if (hero->heat >= 11)
                D_L23_001B16A8 = 1;
        }
    }
    if (D_L23_001B16A8 != 0 && D_L23_001B1694 > (D_L23_001B1698 * 5 + 2) / 6) {
        C0E8Hero *hero = (C0E8Hero *)g_hero_state;

        if (hero->charge >= 11)
            D_L23_001B1694 = (D_L23_001B1698 * 5 + 2) / 6;
    }
    {
        C0E8Hero *hero = (C0E8Hero *)g_hero_state;

        if (hero->charge != 0 && hero->armed == 0)
            D_L23_001B16A8 = 0;
    }
    {
        C0E8Hero *hero = (C0E8Hero *)g_hero_state;

        if (hero->charge >= 11 && D_L23_001B16A4 == 0 && D_L23_001B1694 > 0 &&
            D_L23_001B1694 <= (D_L23_001B1698 * 5 + 2) / 6)
            D_L23_001B1694 = ((D_L23_001B1698 + 5) * 5 + 2) / 6;
    }
    if (D_L23_001B1694 == (D_L23_001B1698 * 5 + 2) / 6) {
        PlayMobySound(10, 0, (char *)arg0);
        PlayMobySound(0x11, 0, (char *)arg0);
    }
    if (D_L23_001B1694 < 0) {
        D_L23_001B1694++;
        if (D_L23_001B371C == 0) {
            C0E8Hero *hero = (C0E8Hero *)g_hero_state;

            if (hero->charge != 0 && state->range < 10.0f && state->level > state->limit) {
                FastVecSub(v, hero->pos, (float *)&arg0->pos);
                vec_scale_to_length(v, v, 3.0f);
                t = arg0->pos;
                v[3] = 5627.9248046875f;
                func_PAL_L23_00423898((void *)state->handle, 0x10007, 0x46, &t, v, 0);
                D_L23_001B371C = (D_L23_001B141C * 5 + 2) / 6;
                func_PAL_L00_003FB330((char *)D_L23_001B36D0, 1, 5, 0x46, 3, 15, 20, 1, 3.0f, 20.0f, 0, 1, 0, 0);
            }
        }
    } else if (D_L23_001B1694 > 0) {
        math_fast_float_d(&D_L23_001B1694);
        if (D_L23_001B1694 == 0) {
            state->handle = func_PAL_L23_0042B658(&arg0->pos, arg0, 1, 0x19, 0x14, 0x14, 0x14, 0x2D, 1.0f, 1, 1, 0, 0, 0x40);
            D_L23_001B1694 = -((D_L23_001B16AC * 5 + 2) / 6);
            PlayMobySound(7, 0, (char *)arg0);
            PlayMobySound(12, 0, (char *)arg0);
            if (state->range < 15.0f && state->level > state->limit) {
                C0E8Hero *hero = (C0E8Hero *)g_hero_state;

                if (hero->busy == 0) {
                    FastVecSub(v, hero->pos, (float *)&arg0->pos);
                    vec_scale_to_length(v, v, D_L23_001B16B0);
                    t = arg0->pos;
                    v[3] = 5627.9248046875f;
                    func_PAL_L23_00423898(arg0, 0x10007, 0x46, &t, v, 0);
                    func_PAL_L00_003FB330((char *)D_L23_001B36D0, 1, 5, 0x46, 3, 15, 20, 1, 3.0f, 20.0f, 0, 1, 0, 0);
                }
            }
        }
    }
}

/* Builds the measured vector when the state's first word names the argument, and lays out the call. */
void func_PAL_L23_004217B0(char *arg0) {
    union {
        TI128 q;
        float f[4];
    } vec;
    char *base = g_hero_state;

    if (*(char **)(base + 0x2290) == arg0) {
        vec.q = 0;
        vec.f[0] = 1.3f;
        vec.f[2] = 4.5f;
        vec.f[3] = 1.0f;
        matrix_mul_vec3((char *)&vec, (char *)&vec, arg0 + 0xC0);
        FastVecAdd((char *)&vec, (char *)&vec, base + 0x80);
        SpawnExplosion((char *)&vec, 0, 10, 10, 10, 25, 30, 0, 3.0f, 20.0f, 0, 1, 0, 0);
    } else {
        SpawnExplosion(arg0 + 0x10, 0, 25, 20, 20, 15, 25, 1, 1.5f, 20.0f, 0, 0, 0, 0);
    }
    if (*(short *)(arg0 + 0xAA) != 0x118F)
        PlayMobySound(3, 0, g_mothership_boss_moby);
}
