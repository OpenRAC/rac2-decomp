/* func_PAL_L05_0041E5C8, the PAL copy of func_L05_00419888: the same C, where rename func_L05_0041A218 becomes func_PAL_L05_0041EF70; rename func_L05_00419F10 becomes func_PAL_L05_0041EC50. */
#include "common.h"

extern void func_00282CC0(void *a, void *b, void *c);

extern float func_00282E48(void *, void *);

extern int func_002E5DA0(int, int, char *, int);

extern void func_0029F338(void *);

/* Same shape as func_L05_004260B8, on its own data slot and with its own tail. */
/* Turns the object towards the global target and clamps its aim cone; a target within
   half a unit takes the fast path, the rest the slow one (an angle step and an update). */
typedef union { int q __attribute__((mode(TI))); float f[4]; } Vector;
typedef struct {
    float direction[4]; void *attacker; int flags; u8 kind, mode; u16 object_class;
    float damage; int enabled; float field24;
} Impact;
extern void func_PAL_L05_0041EF70(void *);
extern int func_00282948(void *);
extern float func_00282E80(void *, void *);
extern void func_00282F20(void *, void *, float);
extern int func_002761F8(void *, void *, int, void *, void *);
extern int func_00278E78(void);
extern void func_PAL_L05_0041EC50(void *, int, u32, void *);
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

void func_PAL_L05_0041E5C8(u8 *actor)
{
    Vector previous;
    Impact impact __attribute__((aligned(16)));
    Vector point, delta, closest;
    u8 *state = *(u8 **)(actor + 0x68);
    int count, i;

    qcopy(&previous, actor + 0x10);
    func_PAL_L05_0041EF70(actor);
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
        func_PAL_L05_0041EC50(D_L05_001BFB20, 20, *(u32 *)(state + 0x24), actor);
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
                *(int *)(camera + 0x168) = 25;
                *(float *)(camera + 0x160) = 0.05f;
            }
            func_PAL_L05_0041EC50(&point, 20, *(u32 *)(state + 0x24), actor);
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
                func_PAL_L05_0041EC50(&closest, 20, *(u32 *)(state + 0x24), actor);
                func_002A8E20(D_L05_001C3B80[i], &impact);
                goto destroy;
            }
        }
    }
finish:
    func_L05_00418440(actor);
    func_L00_002E6EF8(func_L05_0041A228, actor);
}

/* End of a shot's flight: the optional burst, then the object is removed. */

/* Per-frame update of a shot: moves it, removes it when it leaves the 2..1021 world box or expires
 * (with a last collision test), and otherwise tests for a hit and leaves a three-step trail.
 * The end-of-flight code is expanded once per exit and jump2 cross-jumps the copies. The two
 * collision.point loads merge through their shared REG_EQUIV constant, which leaves a dead lui
 * before the impact code, so one shared label does not reproduce it.
 */
