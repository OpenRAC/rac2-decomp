#include "include_asm.h"

#include "common.h"
extern float D_L05_001B153C __attribute__((sda));
extern float D_L05_001B1538 __attribute__((sda));
extern float D_L05_001B1534 __attribute__((sda));
extern float D_L05_001B1530 __attribute__((sda));
extern char *D_L05_001BFB18 __attribute__((nosda));
extern void func_00282F20(void *, void *, float);
extern int func_00277F48(void *, float, int, char *, void *);
extern float func_002A78D8(float, float);
extern float func_002A7940(void);
extern void func_002AF000(void *, float, float, float);
extern int func_002A7820(int, int);
extern char *func_PAL_002BE9A8(void *, float, float, float, float, int, void *, u32, int);
extern int func_002A77E0(int);
typedef int ImpactTI __attribute__((mode(TI)));
typedef union { ImpactTI q; float f[4]; } ImpactVector;
typedef struct {
    ImpactVector pos;
    void *owner;
    int flags;
    unsigned char type, subtype;
    unsigned short id;
    float scale;
    int one;
} ImpactParams;

/* Queues an impact request (func_00277F48) from the object at pos, then, when the
   object in D_L05_001BFB18 has class 0x956, spawns twenty spark particles there. */
void func_PAL_L05_0042D118(char *object, char *state, float *pos)
{
    ImpactParams p;
    ImpactVector origin, direction;
    int i;
    int spin;
    float a, b;
    float count, speed, spread;
    char *particle, *data;

    p.flags = 0x810000;
    p.owner = object;
    if (*(int *)(state + 0x24))
        p.scale = D_L05_001B153C;
    else
        p.scale = D_L05_001B1538;
    p.one = 1;
    qcopy(&p.pos, state);
    func_00282F20(&p, &p, 1.0f);
    p.pos.f[3] = 5627.925f;
    p.type = 3;
    p.subtype = 2;
    p.id = *(unsigned short *)(object + 0xAA);
    func_00277F48(pos, *(int *)(state + 0x24) ? D_L05_001B1534 : D_L05_001B1530,
                  1, *(char **)(state + 0x20), &p);
    if (D_L05_001BFB18 && *(short *)(D_L05_001BFB18 + 0xAA) == 0x956) {
        count = 20.0f;
        speed = 3.0f;
        spread = 2.0f;
        qcopy(&origin, object + 0x10);
        for (i = 0; (float)i < count; i++) {
            pos[0] = origin.f[0] + func_002A78D8(0.0f, spread);
            pos[1] = origin.f[1] + func_002A78D8(0.0f, spread);
            pos[2] = origin.f[2] + func_002A78D8(0.0f, spread);
            a = func_002A7940();
            b = func_002A7940();
            func_002AF000(&direction, 0.060000002f, a, b);
            spin = func_002A7820(-3, 3);
            particle = func_PAL_002BE9A8(pos, 0.0f, 1.0f, 1.0f, speed * 210000.0f, spin,
                                     &direction, 0x7fffffff, 0);
            if (particle) {
                *(short *)(particle + 0xA) = 100;
                data = particle + 0x20;
                particle[8] = func_002A77E0(255);
                particle[3] = 0x44;
                *(int *)(data + 4) = 2;
                data[0xA] = 127;
                data[0xB] = *(unsigned char *)(particle + 0xA);
            }
        }
    }
}

typedef int TI128 __attribute__((mode(TI)));
extern float D_L05_001B157C __attribute__((sda));
extern s32 D_L05_001B35B0[5] MACRO_ADDR;
extern u8 D_L05_001B9580[];
extern void *func_0029EFD0(s32);
extern s32 func_00283DB8(void *, float);
extern float func_00282E48(void *, void *);
extern void func_00282CF0(void *, void *, void *);
extern float func_00282DB0(void *, void *);
extern float func_002831B0(float);
extern void func_PAL_L05_0042E518(void *);

/* spawns object 0x1193 at pos with parent's orientation, when one of the five slots is free:
   fills its vars from the arguments and, if it is in view, grades it against the reference
   point at D_L05_001B9580 + 0x140 */
void *func_PAL_L05_0042DA18(u8 *pos, u8 *parent, s32 flag, float scale, s32 a3, s32 a4, s32 a5,
                        s32 a6, s32 a7, s32 a8, s32 a9, s32 a10, s32 a11, s32 a12) {
    TI128 sphere;
    TI128 dir;
    s32 i;
    u8 *obj;
    u8 *vars;
    float angle;

    if (D_L05_001B157C == -1.0f) {
        for (i = 0; i < 5; i++) {
            D_L05_001B35B0[i] = 0;
        }
        D_L05_001B157C = 0.0f;
    }
    if (D_L05_001B157C >= 5.0f) {
        return 0;
    }
    for (i = 0; i < 5; i++) {
        if (D_L05_001B35B0[i] == 0) {
            break;
        }
    }
    D_L05_001B157C += 1.0f;
    D_L05_001B35B0[i] = 1;
    obj = func_0029EFD0(0x1193);
    if (obj != 0) {
        vars = *(u8 **)(obj + 0x68);
        obj[0x30] = 0xFF;
        *(s16 *)(obj + 0x32) = 0xFF;
        obj[0x20] = 0;
        *(s32 *)(vars + 0x3C) = i;
        qcopy(obj + 0x10, pos);
        *(float *)(obj + 0x1C) = 1.0f;
        qcopy(obj + 0xC0, parent + 0xC0);
        qcopy(obj + 0xD0, parent + 0xD0);
        qcopy(obj + 0xE0, parent + 0xE0);
        *(float *)(obj + 0xCC) = *(float *)(obj + 0xDC) = *(float *)(obj + 0xEC) = 0.0f;
        *(s32 *)(vars + 0x20) = a3;
        *(s32 *)(vars + 0x24) = a4;
        *(s32 *)(vars + 0x28) = a5;
        *(s32 *)(vars + 0x2C) = a6;
        *(float *)(vars + 0x14) = scale;
        *(s32 *)(vars + 0x30) = a7;
        *(s32 *)(vars + 0x34) = a9;
        *(s32 *)(vars + 0x48) = a12;
        *(s16 *)vars = 0x32;
        *(s16 *)(vars + 2) = 0x32;
        *(float *)(vars + 8) = scale + scale;
        *(float *)(vars + 0xC) = scale * 4.0f;
        *(s32 *)(vars + 0x1C) = a10;
        *(s32 *)(vars + 0x38) = a11;
        *(s32 *)(vars + 0x18) = a8;
        *(float *)(vars + 0x44) = func_002A78D8(65.0f, 80.0f);
        qcopy(&sphere, obj + 0x10);
        ((float *)&sphere)[3] = scale * 3.0f;
        if (func_00283DB8(&sphere, 128.0f) == 1) {
            *(s16 *)(vars + 4) = 0x15;
            *(float *)(vars + 0x10) = 0.04761905f;
            if (func_00282E48(pos, D_L05_001B9580 + 0x140) < 48.0f && flag != 0) {
                u8 *ref = D_L05_001B9580;
                *(s32 *)(ref + 0x16C) = 0;
                *(s32 *)(ref + 0x168) = 0x21;
                *(float *)(ref + 0x160) = 0.075f;
            }
            if (*(s32 *)(vars + 0x18) != 0) {
                func_00282CF0(&dir, obj + 0x10, D_L05_001B9580 + 0x140);
                func_00282F20(&dir, &dir, 1.0f);
                angle = func_002831B0(func_00282DB0(&dir, D_L05_001B9580 + 0x370));
                if (1.5707964f - angle < 0.45378566f) {
                    *(s32 *)(vars + 0x18) = 1;
                } else {
                    *(s32 *)(vars + 0x18) = 0;
                }
            }
        } else {
            *(s16 *)(vars + 4) = 0;
            *(s32 *)(vars + 0x18) = 0;
        }
        func_PAL_L05_0042E518(obj);
    }
    return obj;
}

extern int D_L05_001B1504 __attribute__((sda));
extern int D_001A79F0;
extern float func_002AA458(void *, void *, void *, float, float, float);
extern float func_00283B98(float, float);
extern void func_L05_0037AB88(int, int);
extern void func_PAL_0029D5E8(int, int, int);
extern int func_002E5DA0(int, int, char *, int);
extern void func_0029F338(void *);
extern void func_PAL_L05_0042C880(void *);

/* Turns the object towards the global target and clamps its aim cone; a target within
   half a unit takes the fast path, the rest the slow one (an angle step and an update). */
void func_PAL_L05_0042C5DC(char *object)
{
    char *state = *(char **)(object + 0x68);
    float distance;

    if (D_L05_001B1504 != 0) {
        char *pos = object + 0x10;
        char *aim;
        float scaled;
        float capped;

        distance = func_00282E48((char *)D_L05_001B1504 + 0x10, pos);
        if (D_001A79F0 == 0x14) {
            func_002AA458(pos, (char *)D_L05_001B1504 + 0x10, state + 0x40,
                          0.012800001f, 0.0048f, 1.2800001f);
        } else {
            if (distance < 6e+01f) {
                aim = *(char **)(object + 0x24);
                scaled = *(float *)(aim + 0x24) * 0.022222222f * distance;
                *(float *)(object + 0x2C) = scaled;
                capped = *(float *)(aim + 0x24) * 0.3f;
                if (capped > scaled)
                    *(float *)(object + 0x2C) = capped;
                func_002AA458(pos, (char *)D_L05_001B1504 + 0x10, state + 0x40,
                              0.008f, 0.0024f, 0.6f);
            }
        }
        if (distance < 0.5f) {
            func_L05_0037AB88(4, 1);
            func_PAL_0029D5E8(0x1285, 1, -1);
            func_002E5DA0(0xC, 0, object, 0xFBF);
            func_0029F338(object);
            return;
        }
    }
    *(float *)(object + 0xF8) = func_00283B98(*(float *)(object + 0xF8), 0.04f);
    func_PAL_L05_0042C880(object);
}
