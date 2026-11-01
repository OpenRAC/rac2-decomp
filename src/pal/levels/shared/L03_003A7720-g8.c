#include "include_asm.h"

extern float func_00283248(float, float);
extern float func_00283B98(float, float);
extern float func_00282DF0(float *);
extern float func_00283248(float, float);
extern float func_00283B98(float, float);
extern void ref_L03_003C4240_00(unsigned char *, float);
extern void ref_L03_003C4240_01(unsigned char *, void *, int, float, float, float);
extern int ref_L03_003C4240_02(void *, void *, void *);
extern void ref_L03_003C4240_03(void *, void *);
extern float ref_L03_003C4240_04 __attribute__((sda));
extern float ref_L03_003C4240_05 __attribute__((sda));

/* Turns the object with its state: it stops when the state has no time left, otherwise it
   spreads the turn over the frame and lets the state and the object react to it. */
void func_PAL_L03_003C8250(unsigned char *a0) {
    unsigned char *s1 = *(unsigned char **)(a0 + 0x68);
    unsigned char *v;
    float f;
    float g;

    f = func_00282DF0((float *)(s1 + 0x1B0));
    if (f <= 0.0f)
        return;
    g = func_00282DF0((float *)(s1 + 0x1B0));
    if (g > 0.020000001f) {
        f = func_00283248(*(float *)(s1 + 0x1B0), *(float *)(s1 + 0x1B4));
        f = func_00283B98(f, 3.14159274f);
        ref_L03_003C4240_00(a0, f);
    }
    ref_L03_003C4240_01(a0, a0 + 0x10, 0x10, *(float *)(a0 + 0xF8),
                        ref_L03_003C4240_05 * 0.020000001f,
                        ref_L03_003C4240_04 * 0.00040000002f);
    ref_L03_003C4240_02(*(void **)(s1 + 0x220), a0 + 0x10, s1 + 0x368);
    v = *(unsigned char **)(s1 + 0x194);
    if (v != 0) {
        if (*(short *)(v + 0xAA) == 0x940 || *(short *)(v + 0xAA) == 0x93C ||
            *(short *)(v + 0xAA) == 0x964)
            ref_L03_003C4240_03(*(unsigned char **)(s1 + 0x194), a0 + 0x10);
    }
}

#include "common.h"
extern int func_002AD0B0(u8 *);
extern float func_00282C48(float);
extern void func_00282CF0(void *, void *, void *);
extern void func_00282F20(void *, void *, float);
extern void func_00282CC0(void *, void *, void *);
extern void func_002AC9F8(float *, float);
extern float D_L03_001AFF08 __attribute__((sda));
extern float D_L03_001AFF04 __attribute__((sda));

void func_PAL_L03_003C8378(u8 *object, void *target)
{
    float delta[4];
    u8 *state;
    u8 *attachment;
    if (object[0x20] != 4 && object[0x20] != 2)
        return;
    state = *(u8 **)(object + 0x68);
    if (*(u8 **)(state + 0x198) != 0) {
        attachment = (u8 *)func_002AD0B0(*(u8 **)(state + 0x198));
        if (attachment != 0 && 0.002f < func_00282C48(*(float *)(attachment + 0x18)))
            return;
    }
    func_00282CF0(delta, object + 0x10, target);
    delta[2] = 0.0f;
    func_00282F20(delta, delta, (D_L03_001AFF08 + D_L03_001AFF08) * 0.00040000002f);
    func_00282CC0(state + 0x1B0, state + 0x1B0, delta);
    func_002AC9F8((float *)(state + 0x1B0), D_L03_001AFF04 * 0.020000001f);
}

extern float func_00283198(float);
extern int func_00283D38(int, int, float);
extern void func_L00_002E6CF0(void *, void *);
extern void func_L03_003C4800(unsigned char *);
extern void *ref_L03_003C4578_00[];
extern int ref_L03_003C4578_01 __attribute__((sda));
extern int ref_L03_003C4578_02[3] __attribute__((sda));
extern float ref_L03_003C4578_03 __attribute__((sda));
extern int ref_L03_003C4578_04 __attribute__((sda));
extern int ref_L03_003C4578_05[3] __attribute__((sda));
extern float ref_L03_003C4578_06 __attribute__((sda));
extern float ref_L03_003C4578_07 __attribute__((sda));
extern int ref_L03_003C4578_08 __attribute__((sda));
extern int ref_L03_003C4578_09[3] __attribute__((sda));
extern int ref_L03_003C4578_10 __attribute__((sda));
extern int ref_L03_003C4578_11[3] __attribute__((sda));
extern int ref_L03_003C4578_12 __attribute__((sda));
extern int ref_L03_003C4578_13[3] __attribute__((sda));
extern int ref_L03_003C4578_14 __attribute__((sda));
extern int ref_L03_003C4578_15[3] __attribute__((sda));
extern int ref_L03_003C4578_16 __attribute__((sda));
extern int ref_L03_003C4578_17[3] __attribute__((sda));
extern float ref_L03_003C4578_18 __attribute__((sda));
extern int ref_L03_003C4578_19;
extern unsigned short *ref_L03_003C4578_20[];
extern int ref_L03_003C4578_21 __attribute__((sda));
extern unsigned char *ref_L03_003C4578_22[3] __attribute__((sda));
typedef struct {
    unsigned char pad0[0x35C];
    float phase;
    unsigned char pad1[0x378 - 0x360];
    int stamp;
} L03State;
typedef struct {
    unsigned char pad0[0x21];
    unsigned char group;
    unsigned char pad1[0x31 - 0x22];
    unsigned char live;
    unsigned char pad2[0x68 - 0x32];
    L03State *state;
    unsigned char pad3[0x78 - 0x6C];
    int tint;
    unsigned char pad4[0x95 - 0x7C];
    unsigned char kind;
} L03Obj;

/* Per object kind (a0->kind: 1 and 7, 8, 2..6, else) it picks a pair of ids and a scale, turns
   the object's phase (the float at 0x35C of its state) by that scale, stores the result of
   func_00283D38 on the pair in a0->tint, and, when the state's stamp is not the frame counter,
   stamps the counter into the state of every entity of its group and registers
   func_L03_003C4800 for the object with func_L00_002E6CF0. The kind selects its arm through the
   level's jump table; `cases` only keeps the labels alive, and the labels are named after the
   kind that reaches them. */
void func_PAL_L03_003C8588(L03Obj *a0) {
    static void *cases[9] = {&&c0, &&c1, &&c2, &&c3, &&c4, &&c5, &&c6, &&c1, &&c8};
    L03State *s1 = a0->state;
    int pair[2];
    float scale;
    float t;
    float r;
    unsigned short *q;
    L03Obj *e;
    unsigned int kind;

    if (a0->live != 0) {
        kind = a0->kind;
        if (kind < 9)
            goto *ref_L03_003C4578_00[kind];
        goto c0;
c1:
        pair[0] = ref_L03_003C4578_01;
        pair[1] = ref_L03_003C4578_02[0];
        scale = ref_L03_003C4578_03 * 0.0003490659f;
        goto join;
c8:
        pair[0] = ref_L03_003C4578_04;
        pair[1] = ref_L03_003C4578_05[0];
        scale = ref_L03_003C4578_06 * 0.0003490659f;
        goto join;
c2:
        pair[0] = ref_L03_003C4578_04;
        pair[1] = ref_L03_003C4578_05[0];
        scale = ref_L03_003C4578_07 * 0.0003490659f;
        goto join;
c3:
        pair[0] = ref_L03_003C4578_08;
        pair[1] = ref_L03_003C4578_09[0];
        scale = ref_L03_003C4578_07 * 0.0003490659f;
        goto join;
c4:
        pair[0] = ref_L03_003C4578_10;
        pair[1] = ref_L03_003C4578_11[0];
        scale = ref_L03_003C4578_07 * 0.0003490659f;
        goto join;
c5:
        pair[0] = ref_L03_003C4578_12;
        pair[1] = ref_L03_003C4578_13[0];
        scale = ref_L03_003C4578_07 * 0.0003490659f;
        goto join;
c6:
        pair[0] = ref_L03_003C4578_14;
        pair[1] = ref_L03_003C4578_15[0];
        scale = ref_L03_003C4578_07 * 0.0003490659f;
        goto join;
c0:
        pair[0] = ref_L03_003C4578_16;
        pair[1] = ref_L03_003C4578_17[0];
        scale = ref_L03_003C4578_18 * 0.0003490659f;
join:
        t = func_00283B98(s1->phase, scale);
        s1->phase = t;
        r = func_00283198(t);
        a0->tint = func_00283D38(pair[0], pair[1], r * 0.5f + 0.5f);
        if (s1->stamp != ref_L03_003C4578_19) {
            for (q = ref_L03_003C4578_20[a0->group];
                 a0->group != 0xFF && a0->group <= ref_L03_003C4578_21 && q != 0 &&
                 ((q != 0 && (short)q[-1] >= 0) || q == ref_L03_003C4578_20[a0->group]);
                 q++) {
                e = (L03Obj *)(ref_L03_003C4578_22[0] + ((*q & 0x7FFF) << 8));
                if (e == 0)
                    break;
                e->state->stamp = ref_L03_003C4578_19;
            }
            func_L00_002E6CF0(func_L03_003C4800, a0);
        }
    }
}
