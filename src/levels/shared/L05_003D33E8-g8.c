#include "common.h"
#include "include_asm.h"

extern int D_L05_001B0F50 __attribute__((sda));

void func_L05_00417730(char *object)
{
    char *state = *(char **)(object + 0x68);

    D_L05_001B0F50 = 0;
    *(int *)(state + 0x1BC) = 0;
    *(int *)(state + 0x1B8) = 0;
}

extern void func_00282C88(void *target);

extern void func_00283098(void *a, void *b, void *c);

extern void func_00282CC0(void *a, void *b, void *c);

extern int func_L00_002FCF18(void *p, float, float, float, float, float);

extern int D_L05_001B0FA4 __attribute__((sda));

void func_L05_00418200(char *object)
{
    float local[4];
    float one = 1.0f;

    func_00282C88(local);
    local[0] = 4.0f;
    local[2] = one;
    func_00283098(local, local, object + 0xC0);
    func_00282CC0(local, local, object + 0x10);
    D_L05_001B0FA4 = func_L00_002FCF18(local, 0.0f, 0.0f, 0.0f, one, 0.0f);
}

typedef int TI128 __attribute__((mode(TI)));

extern int func_328508(int);

extern void func_3065F8(int);

extern float func_332C18(void);

extern int D_L05_001D1348 __attribute__((sda));

extern int D_L05_001B14FC __attribute__((sda));

extern int D_L05_001B1504 __attribute__((sda));

extern int D_L05_001B2528 __attribute__((nosda));

extern void func_41D728(int);

extern void func_426270(int);

extern void func_426D98(int);

extern int D_001A79F0;

extern float func_00282E48(void *, void *);

extern float func_002AA458(void *, void *, void *, float, float, float);

extern float func_00283B98(float, float);

extern void func_L05_0037AB88(int, int);

extern void func_0029CC50(int, int, int);

extern int func_002E5DA0(int, int, char *, int);

extern void func_0029F338(void *);

extern void func_L05_00426348(char *);

void func_L05_004260B8(char *object)
{
    char *state = *(char **)(object + 0x68);
    float scale;

    if (D_L05_001B14FC != 0) {
        scale = func_00282E48((void *)(D_L05_001B14FC + 0x10), object + 0x10);

        if (D_001A79F0 == 0x14) {
            func_002AA458(object + 0x10, (void *)(D_L05_001B14FC + 0x10), state + 0x40,
                         0.008888889104127884f, 0.0033333334140479565f, 1.0666667222976685f);
            goto check_scale;
        }
        if (scale < 60.0f) {
            float *p = *(float **)(object + 0x24);
            float v = p[9] * 0.02222222276031971f * scale;

            *(float *)(object + 0x2C) = v;
            {
                float cap = p[9] * 0.30000001192092896f;

                if (v < cap)
                    *(float *)(object + 0x2C) = cap;
            }
            func_002AA458(object + 0x10, (void *)(D_L05_001B14FC + 0x10), state + 0x40,
                         0.0055555556900799274f, 0.0016666667070239782f, 0.5f);
        }
check_scale:
        if (scale < 0.5f) {
            func_L05_0037AB88(2, 10);
            func_0029CC50(0x1288, 10, -1);
            func_002E5DA0(0xC, 0, object, 0xFBF);
            func_0029F338(object);
            return;
        }
    }
    *(float *)(object + 0xF8) = func_00283B98(*(float *)(object + 0xF8), 0.04f);
    func_L05_00426348(object);
}

extern int D_L05_001B1500 __attribute__((sda));

extern void func_L05_004268E8(char *);

extern int D_L05_001B1348 __attribute__((sda));

extern void func_L05_0041D800(char *);

void func_L05_0041D570(char *object)
{
    char *state = *(char **)(object + 0x68);
    float scale;

    if (D_L05_001B1348 != 0) {
        scale = func_00282E48((void *)(D_L05_001B1348 + 0x10), object + 0x10);

        if (D_001A79F0 == 0x14) {
            func_002AA458(object + 0x10, (void *)(D_L05_001B1348 + 0x10), state + 0x40,
                         0.008888889104127884f, 0.0033333334140479565f, 1.0666667222976685f);
            goto check_scale;
        }
        if (scale < 60.0f) {
            float *p = *(float **)(object + 0x24);
            float v = p[9] * 0.02222222276031971f * scale;

            *(float *)(object + 0x2C) = v;
            {
                float cap = p[9] * 0.30000001192092896f;

                if (v < cap)
                    *(float *)(object + 0x2C) = cap;
            }
            func_002AA458(object + 0x10, (void *)(D_L05_001B1348 + 0x10), state + 0x40,
                         0.0055555556900799274f, 0.0016666667070239782f, 0.5f);
        }
    check_scale:
        if (scale < 0.5f) {
            func_002E5DA0(0xC, 0, object, 0xFBF);
            func_L05_0037AB88(1, 10);
            func_0029CC50(0x1286, 10, -1);
            func_0029F338(object);
            return;
        }
    }
    *(float *)(object + 0xF8) = func_00283B98(*(float *)(object + 0xF8), 0.04f);
    func_L05_0041D800(object);
}

/* Same shape as func_L05_004260B8, on its own data slot and with its own tail. */
void func_L05_00426658(char *object)
{
    char *state = *(char **)(object + 0x68);
    float scale;

    if (D_L05_001B1500 != 0) {
        scale = func_00282E48((void *)(D_L05_001B1500 + 0x10), object + 0x10);

        if (D_001A79F0 == 0x14) {
            func_002AA458(object + 0x10, (void *)(D_L05_001B1500 + 0x10), state + 0x40,
                         0.008888889104127884f, 0.0033333334140479565f, 1.0666667222976685f);
            goto check_scale;
        }
        if (scale < 60.0f) {
            float *p = *(float **)(object + 0x24);
            float v = p[9] * 0.02222222276031971f * scale;

            *(float *)(object + 0x2C) = v;
            {
                float cap = p[9] * 0.30000001192092896f;

                if (v < cap)
                    *(float *)(object + 0x2C) = cap;
            }
            func_002AA458(object + 0x10, (void *)(D_L05_001B1500 + 0x10), state + 0x40,
                         0.0055555556900799274f, 0.0016666667070239782f, 0.5f);
        }
check_scale:
        if (scale < 0.5f) {
            func_L05_0037AB88(3, 10);
            func_0029CC50(0x1287, 10, -1);
            func_002E5DA0(0xC, 0, object, 0xFBF);
            func_0029F338(object);
            return;
        }
    }
    *(float *)(object + 0xF8) = func_00283B98(*(float *)(object + 0xF8), 0.04f);
    func_L05_004268E8(object);
}

extern void func_L05_00426E70(void *);

/* Turns the object towards the global target and clamps its aim cone; a target within
   half a unit takes the fast path, the rest the slow one (an angle step and an update). */
void func_L05_00426BE0(char *object)
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
                          0.008888889f, 0.0033333333f, 1.0666667f);
        } else {
            if (distance < 60.0f) {
                aim = *(char **)(object + 0x24);
                scaled = *(float *)(aim + 0x24) * 0.022222222f * distance;
                *(float *)(object + 0x2C) = scaled;
                capped = *(float *)(aim + 0x24) * 0.3f;
                if (capped > scaled)
                    *(float *)(object + 0x2C) = capped;
                func_002AA458(pos, (char *)D_L05_001B1504 + 0x10, state + 0x40,
                              0.0055555556f, 0.0016666667f, 0.5f);
            }
        }
        if (distance < 0.5f) {
            func_L05_0037AB88(4, 1);
            func_0029CC50(0x1285, 1, -1);
            func_002E5DA0(0xC, 0, object, 0xFBF);
            func_0029F338(object);
            return;
        }
    }
    *(float *)(object + 0xF8) = func_00283B98(*(float *)(object + 0xF8), 0.04f);
    func_L05_00426E70(object);
}

typedef union { int q __attribute__((mode(TI))); float f[4]; } Vector;
typedef struct {
    float direction[4]; void *attacker; int flags; u8 kind, mode; u16 object_class;
    float damage; int enabled; float field24;
} Impact;
extern void func_L05_0041A218(void *);
extern int func_00282948(void *);
extern float func_00282E80(void *, void *);
extern void func_00282F20(void *, void *, float);
extern int func_002761F8(void *, void *, int, void *, void *);
extern int func_00278E78(void);
extern void func_L05_00419F10(void *, int, u32, void *);
extern float func_L00_0031BDC0(void *, void *, void *, void *);
extern void func_00282D08(void *, void *, void *, float);
extern void func_00282CF0(void *, void *, void *);
extern float func_00282DF0(void *);
extern int func_00277F48(void *, int, void *, void *, float);
extern void func_002A8E20(void *, Impact *);
extern void func_L05_00418440(void *);
extern void func_L00_002E6EF8(void *, void *);
extern void func_L05_0041A228(void *);
extern char D_L05_001BFB20[], D_L05_001B9580[];
extern u8 *D_L05_001C3B80[];
extern float D_L05_001B104C __attribute__((sda));

void func_L05_00419888(u8 *actor)
{
    Vector previous;
    Impact impact __attribute__((aligned(16)));
    Vector point, delta, closest;
    u8 *state = *(u8 **)(actor + 0x68);
    int count, i;

    qcopy(&previous, actor + 0x10);
    func_L05_0041A218(actor);
    func_00282CC0(actor + 0x10, actor + 0x10, state + 0x10);
    if (func_00282948(state) != 0) {
        func_0029F338(actor);
        return;
    }
    if (*(float *)(actor + 0x10) < 2.0f || *(float *)(actor + 0x10) > 1021.0f ||
        *(float *)(actor + 0x14) < 2.0f || *(float *)(actor + 0x14) > 1021.0f ||
        *(float *)(actor + 0x18) < 2.0f || *(float *)(actor + 0x18) > 1021.0f) {
        if (*(int *)(state + 0x38) == 0) {
            func_0029F338(actor);
            return;
        }
    }
    if (*(int *)(state + 0x38) != 0) {
        if (func_00282E80(actor + 0x10, D_L05_001B9580 + 0x140) < 2.0f) {
            func_0029F338(actor);
            return;
        }
    }
    if (*(int *)(state + 0x38) != 0)
        goto finish;
    impact.attacker = actor;
    impact.flags = 0x110000;
    if (*(int *)(state + 0x30) != 0)
        impact.damage = 3.0f;
    else
        impact.damage = 1.0f;
    impact.enabled = 1;
    qcopy(impact.direction, state + 0x10);
    func_00282F20(impact.direction, impact.direction, 1.0f);
    impact.kind = 1;
    impact.mode = 1;
    impact.direction[3] = 5627.9248046875f;
    impact.object_class = *(u16 *)(actor + 0xAA);
    /* The last Impact word is read by the receiver but not initialized by retail. */
    *(float *)(state + 0x3C) += *(float *)(state + 0x40);
    if (func_002761F8(&previous, actor + 0x10, 0, *(void **)(state + 4), &impact) != 0 &&
        func_00278E78() != 6) {
        func_002E5DA0(7, 0, (char *)actor, 0xFBF);
        func_L05_00419F10(D_L05_001BFB20, 20, *(u32 *)(state + 0x24), actor);
        func_0029F338(actor);
        return;
    }
    if (*(s16 *)(*(u8 **)(state + 4) + 0xAA) != 0xFBF) {
        func_L00_0031BDC0(&point, &previous, actor + 0x10, D_L05_001B9580 + 0x140);
        if (func_00282E48(&point, D_L05_001B9580 + 0x140) < D_L05_001B104C) {
            func_002E5DA0(7, 0, (char *)actor, 0xFBF);
            {
                char *camera = D_L05_001B9580;
                *(int *)(camera + 0x16C) = 0;
                *(int *)(camera + 0x168) = 30;
                *(float *)(camera + 0x160) = 0.05f;
            }
            func_L05_00419F10(&point, 20, *(u32 *)(state + 0x24), actor);
            func_0029F338(actor);
            return;
        }
        goto finish;
destroy:
        func_0029F338(actor);
        return;
    }
    func_00282D08(&point, &previous, actor + 0x10, 0.5f);
    func_00282CF0(&delta, actor + 0x10, &previous);
    count = func_00277F48(&point, 1, *(void **)(state + 4), 0, func_00282DF0(&delta));
    if (count != 0) {
        for (i = 0; i < count; i++) {
            func_L00_0031BDC0(&closest, &previous, actor + 0x10, D_L05_001C3B80[i] + 0x10);
            func_00282CF0(&delta, D_L05_001C3B80[i] + 0x10, &closest);
            if (func_00282DF0(&delta) < *(float *)(state + 0x3C)) {
                func_002E5DA0(7, 0, (char *)actor, 0xFBF);
                func_L05_00419F10(&closest, 20, *(u32 *)(state + 0x24), actor);
                func_002A8E20(D_L05_001C3B80[i], &impact);
                goto destroy;
            }
        }
    }
finish:
    func_L05_00418440(actor);
    func_L00_002E6EF8(func_L05_0041A228, actor);
}
