#include "common.h"

/* func_PAL_L00_003D8AB8, the PAL copy of func_L00_003D4A20: the same C, with
 * two 50 Hz scales, the 10 > 8 and 20 > 17 frame counts, and the two floats
 * rescaled. The two stores above the first scale are indexed, so the global
 * read can move above them and ahead of the division guard, as in retail.
 * Kilonoid update. The four active slots require -G16. This unit also uses
 * the qualified copy, expression-order and unsplit-GCSE profiles. */
typedef unsigned int KilonoidQuad __attribute__((mode(TI)));

extern int D_L00_001A8F00 __attribute__((sda));
extern int D_001A79F0 __attribute__((sda));
extern int D_L00_001ADB2C __attribute__((sda));
extern int D_L00_001B0264 __attribute__((sda)), D_L00_001B0270 __attribute__((sda)), D_L00_001B0274 __attribute__((sda)), D_L00_001B0278 __attribute__((sda)), D_L00_001B0288 __attribute__((sda));
extern float D_L00_001B027C __attribute__((sda)), D_L00_001B0280 __attribute__((sda)), D_L00_001B0284 __attribute__((sda)), D_L00_001B028C __attribute__((sda));
/* The creator scans four pointer slots (003D3E54: index < 4). */
extern unsigned char *D_L00_001B02B0[4] __attribute__((sda));
typedef struct {
    unsigned char pad000[0x80];
    float position[4];
    unsigned char pad090[0x90];
    float displacement[4];
    unsigned char pad130[0x20];
    float velocity[4];
    unsigned char pad160[0x1dc];
    char *attached;
    unsigned char pad340[0x1f50];
    char *moby;
    int state;
    int pad2298;
    int mode;
    unsigned char pad22a0[0x14];
    unsigned char flag;
} KilonoidHeroView;
extern KilonoidHeroView D_00189E20 __attribute__((nosda));
extern unsigned char D_00188660[] __attribute__((nosda));
extern void func_PAL_002A7E68(char *, int, int, int);
extern int ref_L00_003D4A20_01(int, int, char *);
extern float ref_L00_003D4A20_02(void);
extern float ref_L00_003D4A20_03(void *, void *);
extern void ref_L00_003D4A20_04(void *, void *, void *);
extern void ref_L00_003D4A20_05(void *, void *, void *);
extern void ref_L00_003D4A20_06(int);
extern int ref_L00_003D4A20_07(int, int);
extern float ref_L00_003D4A20_08(float, float);
extern void ref_L00_003D4A20_09(char *, char *);
extern void func_PAL_L00_003D85E0(char *, char *);
extern void func_PAL_L00_003D8170(char *, char *);
extern int ref_L00_003D4A20_12(void *);
extern void ref_L00_003D4A20_13(char *);
extern void ref_L00_003D4A20_14(void *, float);
extern int func_001163B0(void);
extern void ref_L00_003D4A20_15(void *, int, int, int, int, void *, int, float, float, float);
extern float ref_L00_003D4A20_16(float, float);
extern void ref_L00_003D4A20_17(void *, void *, void *, float);
extern void ref_L00_003D4A20_18(void *, void *, void *, float);
extern void ref_L00_003D4A20_19(void *, void *);
extern void ref_L00_003D4A20_20(char *, float);
extern void func_PAL_L00_003D89F0(char *, char *);
extern void ref_L00_003D4A20_22(void *, void *, float);
extern float ref_L00_003D4A20_23(float);
extern void ref_L00_003D4A20_24(void *, void *, float);
extern void ref_L00_003D4A20_25(void *, void *, void *);

static __inline__ void ReleaseSound(int index, unsigned char *object)
{
    unsigned char *entry;
    if (index != -1) {
        entry = D_00188660 + index * 0x70;
        if (*(unsigned char **)(entry + 0x88) == object && entry[0x74])
            ref_L00_003D4A20_06(index);
    }
}

typedef struct {
    unsigned char pad000[0x34];
    unsigned short flags;
    unsigned char pad036[0x96];
    float w0;
    unsigned char pad0d0[0xc];
    float w1;
    unsigned char pad0e0[0xc];
    float w2;
} KilonoidObjectView;

void func_PAL_L00_003D8AB8(unsigned char *object)
{
    float temp[4];
    KilonoidQuad zero;
    char *state, *heroMoby;
    int displaced, r, g, b, color, flip, n;
    float f;
    if (!object)
        return;
    state = *(char **)(object+0x68);
    if (!state)
        return;
    if (D_L00_001A8F00) {
        *(short *)(state+0x46) = 1;
        ((KilonoidObjectView *)object)->flags |= 0x41;
        return;
    }
    if (*(short *)(state+0x46) == 1) ((KilonoidObjectView *)object)->flags &= 0xffbe;
    *(float *)(object+0x2c) += (*(float *)(*(char **)(object+0x24)+0x24)-*(float *)(object+0x2c))*0.1f;
    switch (object[0x20]) {
    case 0:
        qzero_nc(state);
        qzero_nc(state+0x10);
        state[0x26] = 0;
        *(int *)(state+0x20) = 0;
        *(short *)(state+0x46) = 0;
        if (object[0x43]) func_PAL_002A7E68(object, 0, 0, 8);
        object[0x30] = 255;
        ((short *)object)[0x32/2] = 255;
        state[0x25] = 0;
        ((int *)state)[0x30/4] = 0;
        *(int *)(state+0x2c) = ((s32)(D_L00_001B0264) * 5 + 2) / 6;
        *(KilonoidQuad *)(state+0x60) = *(KilonoidQuad *)D_00189E20.position;
        {
            unsigned char *current = D_00188660 + (signed char)state[0x27] * 0x70;
            if (*(unsigned char **)(current+0x88) != object || !current[0x74]) {
                unsigned char *fallback = D_00188660 - 0x70;
                state[0x27] = -1;
                if (*(unsigned char **)(fallback+0x88) != object || !fallback[0x74])
                    state[0x27] = ref_L00_003D4A20_01(1, 4, object);
            }
        }
        qzero_nc(state+0x10);
        *(float *)(state+0x48) = ref_L00_003D4A20_02();
        *(float *)(state+0x4c) = ref_L00_003D4A20_02();
        *(float *)(state+0x54) = ref_L00_003D4A20_02();
        *(int *)(state+0x50) = 0;
        object[0x20] = 1;
        break;
    case 1:
        if ((object[0x60]&2) && object[0x43] != 1) func_PAL_002A7E68(object, 1, 0, 10);
        {
            unsigned char *current = D_00188660 + (signed char)state[0x27] * 0x70;
            if (*(unsigned char **)(current+0x88) != object || !current[0x74]) {
                unsigned char *fallback = D_00188660 - 0x70;
                state[0x27] = -1;
                if (*(unsigned char **)(fallback+0x88) != object || !fallback[0x74])
                    state[0x27] = ref_L00_003D4A20_01(1, 4, object);
            }
        }
        displaced = 0;
        if (D_00189E20.state != 129 && ref_L00_003D4A20_03(state+0x60, D_00189E20.position)>400.0f) displaced = 1;
        if (displaced) {
            if (D_001A79F0 == 7 && D_00189E20.attached && *(short *)(D_00189E20.attached+0xaa) == 0x11d9) {
                ref_L00_003D4A20_04(temp, D_00189E20.position, state+0x60);
                ref_L00_003D4A20_05(object+0x10, object+0x10, temp);
            } else {
                ReleaseSound((signed char)state[0x27], object);
                state[0x27] = -1;
                object[0x23] = 128;
                qzero_nc(state+0x10);
                goto destroy;
            }
        }
        *(KilonoidQuad *)(state+0x60) = *(KilonoidQuad *)D_00189E20.position;
        if (*(int *)(state+0x20)>17 && (object[0x60]&2)) {
            if (object[0x43] != 1) func_PAL_002A7E68(object, 1, 0, ((s32)(ref_L00_003D4A20_07(7, 12)) * 5 + 2) / 6);
            *(float *)(object+0x48) = ref_L00_003D4A20_08(0.95f, 1.05f);
        }
        if ((unsigned char)state[0x25]<*(int *)(state+0x40) && D_00189E20.mode != 22 && D_00189E20.mode != 20 && !D_00189E20.flag) {
            ref_L00_003D4A20_09(object, state);
            func_PAL_L00_003D85E0(object, state);
        } else {
            qzero_nc(state+0x10);
            *(int *)(state+0x20) = D_L00_001B0270;
            ReleaseSound((signed char)state[0x27], object);
            state[0x27] = -1;
            ref_L00_003D4A20_01(2, 0, object);
            object[0x20] = 2;
        }
        func_PAL_L00_003D8170(object, state);
        break;
    case 2:
        ReleaseSound((signed char)state[0x27], object);
        state[0x27] = -1;
        if (ref_L00_003D4A20_12(state+0x20)) {
            ReleaseSound((signed char)state[0x27], object);
            state[0x27] = -1;
            object[0x23] = 128;
            qzero_nc(state+0x10);
destroy:
            ((KilonoidObjectView *)object)->flags &= 0xfdff;
            if (*(int *)(state+0x38) != -1)
                D_L00_001B02B0[*(int *)(state+0x38)] = 0;
            ref_L00_003D4A20_13(object);
            return;
        }
        zero = 0;
        qcopy(temp, object+0x10);
        ref_L00_003D4A20_14(temp, D_L00_001B027C);
        r = (func_001163B0()+48)&63;
        g = (func_001163B0()+32)&63;
        b = func_001163B0()&47;
        r |= g << 8;
        r |= b << 16;
        color = r | (D_L00_001B0288 << 24);
        flip = func_001163B0()%2;
        if (*(int *)(state+0x20)&1) flip = -flip;
        n = ref_L00_003D4A20_07(D_L00_001B0274, D_L00_001B0278);
        f = ref_L00_003D4A20_08(D_L00_001B0280, D_L00_001B0284);
        ref_L00_003D4A20_15(temp, n, color, 2, flip, &zero, 0, f, 0.001f, D_L00_001B028C*0.00040000002f);
        ((KilonoidObjectView *)object)->flags |= 0x200;
        object[0x23] -= 128/D_L00_001B0270;
        *(float *)(object+0xf8) = ref_L00_003D4A20_16(*(float *)(object+0xf8), 0.5026549f);
        break;
    }
    if (!object[0x20]) goto basis;
    {
        unsigned char *position = object+0x10;
        if (!D_L00_001ADB2C) {
            if (D_00189E20.state == 39) ref_L00_003D4A20_05(position, position, D_00189E20.displacement);
            else {
                ref_L00_003D4A20_05(temp, position, D_00189E20.velocity);
                ref_L00_003D4A20_17(position, position, temp, 0.4f);
                ref_L00_003D4A20_18(position, position, temp, 0.625f);
            }
        }
        ref_L00_003D4A20_19(position, position);
        ref_L00_003D4A20_20(object, 0.3f);
        func_PAL_L00_003D89F0(object, state);
    }
basis:
    heroMoby = D_00189E20.moby;
    qcopy(object+0xc0, heroMoby+0xc0);
    qcopy(object+0xd0, heroMoby+0xd0);
    qcopy(object+0xe0, heroMoby+0xe0);
    if (D_00189E20.mode == 15) {
        qcopy(object+0xc0, heroMoby+0xd0);
        ref_L00_003D4A20_22(object+0xd0, heroMoby+0xc0, -1.0f);
    }
    f = *(float *)(object+0xf8);
    if (ref_L00_003D4A20_23(f)>0.00001f) {
        ref_L00_003D4A20_24(temp, object+0xe0, f);
        ref_L00_003D4A20_25(object+0xc0, object+0xc0, temp);
        ref_L00_003D4A20_25(object+0xd0, object+0xd0, temp);
    }
    f = *(float *)(object+0xf4);
    if (ref_L00_003D4A20_23(f)>0.00001f) {
        ref_L00_003D4A20_24(temp, object+0xd0, f);
        ref_L00_003D4A20_25(object+0xc0, object+0xc0, temp);
        ref_L00_003D4A20_25(object+0xe0, object+0xe0, temp);
    }
    f = *(float *)(object+0xf0);
    if (ref_L00_003D4A20_23(f)>0.00001f) {
        ref_L00_003D4A20_24(temp, object+0xc0, f);
        ref_L00_003D4A20_25(object+0xd0, object+0xd0, temp);
        ref_L00_003D4A20_25(object+0xe0, object+0xe0, temp);
    }
    ((KilonoidObjectView *)object)->w0 = ((KilonoidObjectView *)object)->w1 = ((KilonoidObjectView *)object)->w2 = 0.0f;
    return;
}
