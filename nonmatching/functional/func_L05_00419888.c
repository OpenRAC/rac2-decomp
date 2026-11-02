/* functional: medium. Near-miss draft, not byte-compared in the latest sweep: paths the captured calls never take are unproven. */
/* Complete C near miss; not linked and no matching credit.
 * 2026-10-30: game -O2 -G8 -ffunction-sections -frac2-qcopy -frac2-qcopy-barrier.
 * us: 0/4; us2: 0/4; pal: absent.
 * 1060/1068 bytes; frame 0xC0. The actual Impact record is 0x28 bytes, including the callee-read
 * final word retail leaves unwritten; all projection buffers are complete. The closest-segment
 * helper retains its canonical float return. Collision branches, packet/source and iteration
 * allocation differ.
 * Reopen: Independent collision CFG/packet-lifetime witness, preserving all query and effect arguments.
 */
#include "common.h"
typedef union { int q __attribute__((mode(TI))); float f[4]; } Vector;
typedef struct {
    float direction[4]; void *attacker; int flags; u8 kind, mode; u16 object_class;
    float damage; int enabled; float field24;
} Impact;
typedef char ImpactExtent[sizeof(Impact) == 0x28 ? 1 : -1];
extern void func_L05_0041A218(void *);
extern void func_00282CC0(void *, void *, void *);
extern int func_00282948(void *);
extern float func_00282E80(void *, void *);
extern void func_00282F20(void *, void *, float);
extern int func_002761F8(void *, void *, int, void *, void *);
extern int func_00278E78(void);
extern int func_002E5DA0(int, int, void *, int);
extern void func_L05_00419F10(void *, int, u32, void *);
extern float func_L00_0031BDC0(void *, void *, void *, void *);
extern float func_00282E48(void *, void *);
extern void func_00282D08(void *, void *, void *, float);
extern void func_00282CF0(void *, void *, void *);
extern float func_00282DF0(void *);
extern int func_00277F48(void *, int, void *, void *, float);
extern void func_002A8E20(void *, Impact *);
extern void func_L05_00418440(void *);
extern void func_L00_002E6EF8(void *, void *);
extern void func_L05_0041A228(void *);
extern void func_0029F338(void *);
extern char D_L05_001B96C0[], D_L05_001BFB20[], D_L05_001B9580[];
extern u8 *D_L05_001C3B80[];
extern float D_L05_001B104C __attribute__((sda));

void func_L05_00419888(u8 *actor)
{
    Vector previous, point, delta, closest;
    Impact impact __attribute__((aligned(16)));
    u8 *state = *(u8 **)(actor + 0x68);
    float *position = (float *)(actor + 0x10);
    int outside;
    int count, i;
    qcopy(&previous, position);
    func_L05_0041A218(actor);
    func_00282CC0(position, position, state + 0x10);
    if (func_00282948(state) != 0)
        goto destroy;
    outside = position[0] < 2.0f || position[0] > 1021.0f ||
              position[1] < 2.0f || position[1] > 1021.0f ||
              position[2] < 2.0f || position[2] > 1021.0f;
    if (outside && *(int *)(state + 0x38) == 0)
        goto destroy;
    if (*(int *)(state + 0x38) != 0) {
        if (func_00282E80(position, D_L05_001B96C0) < 2.0f)
            goto destroy;
        goto finish;
    }
    impact.attacker = actor;
    impact.flags = 0x110000;
    impact.damage = *(int *)(state + 0x30) != 0 ? 3.0f : 1.0f;
    impact.enabled = 1;
    qcopy(impact.direction, state + 0x10);
    func_00282F20(impact.direction, impact.direction, 1.0f);
    impact.mode = 1;
    impact.direction[3] = 5627.9248046875f;
    impact.object_class = *(u16 *)(actor + 0xAA);
    impact.kind = 1;
    /* The last Impact word is read by the receiver but not initialized by retail. */
    *(float *)(state + 0x3C) += *(float *)(state + 0x40);
    if (func_002761F8(&previous, position, 0, *(void **)(state + 4), &impact) != 0 &&
        func_00278E78() != 6) {
        func_002E5DA0(7, 0, actor, 0xFBF);
        func_L05_00419F10(D_L05_001BFB20, 20, *(u32 *)(state + 0x24), actor);
        goto destroy;
    }
    if (*(s16 *)(*(u8 **)(state + 4) + 0xAA) != 0xFBF) {
        func_L00_0031BDC0(&point, &previous, position, D_L05_001B96C0);
        if (func_00282E48(&point, D_L05_001B96C0) < D_L05_001B104C) {
            func_002E5DA0(7, 0, actor, 0xFBF);
            *(int *)(D_L05_001B9580 + 0x16C) = 0;
            *(float *)(D_L05_001B9580 + 0x160) = 0.05f;
            *(int *)(D_L05_001B9580 + 0x168) = 30;
            func_L05_00419F10(&point, 20, *(u32 *)(state + 0x24), actor);
            goto destroy;
        }
        goto finish;
    }
    func_00282D08(&point, &previous, position, 0.5f);
    func_00282CF0(&delta, position, &previous);
    count = func_00277F48(&point, 1, *(void **)(state + 4), 0, func_00282DF0(&delta));
    if (count > 0) {
        for (i = 0; i < count; i++) {
            func_L00_0031BDC0(&closest, &previous, position, D_L05_001C3B80[i] + 0x10);
            func_00282CF0(&delta, D_L05_001C3B80[i] + 0x10, &closest);
            if (func_00282DF0(&delta) < *(float *)(state + 0x3C)) {
                func_002E5DA0(7, 0, actor, 0xFBF);
                func_L05_00419F10(&closest, 20, *(u32 *)(state + 0x24), actor);
                func_002A8E20(D_L05_001C3B80[i], &impact);
                goto destroy;
            }
        }
    }
finish:
    func_L05_00418440(actor);
    func_L00_002E6EF8(func_L05_0041A228, actor);
    return;
destroy:
    func_0029F338(actor);
}
