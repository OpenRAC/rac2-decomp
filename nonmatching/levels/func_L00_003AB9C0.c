/* Reconstruction retained 30 October 2026; not a linked match.
 * Profile: -O2 -G8 -ffunction-sections.
 * 1316/1276 bytes; orientation branches and pointer lifetime/register allocation differ.
 * Reopen with real projectile/weapon record types and helper-bank scheduling evidence.
 * ABI/bounds: Four GPR arguments and four FP arguments retained, with the final FP input unused. Allocation returns a pointer; effect-slot helper returns int. All three local vectors are complete quads.
 * Local checks and release presence are recorded in the shared NMC index.
 * Semantic equivalence has not been validated by the functional gate.
 */
#include "common.h"

typedef float LaunchVector[4] __attribute__((aligned(16)));
extern int D_L00_001AF7A0 __attribute__((sda));
extern u8 D_00139583[];
extern unsigned char D_L00_00262570[];
extern unsigned char D_00189E20[];
extern int D_L00_001A8FF0;
extern unsigned char D_L00_001BF220[];
extern unsigned char D_L00_0023B710[];
extern unsigned char D_L00_001B1FB0[];
extern unsigned char *func_0029EFD0(int);
extern void func_00282CC0(void *, void *, void *);
extern void func_00282CD8(void *, void *, void *);
extern void func_00282CF0(void *, void *, void *);
extern void func_00282D30(void *, void *, float);
extern void func_00282DD8(void *, void *, void *);
extern void func_00282F20(void *, void *, float);
extern float func_00282DB0(void *, void *);
extern float func_002A7878(float, float);
extern float func_002A78D8(float, float);
extern float func_002A7940(void);
extern void func_L00_0037FA90(void *, void *, float, float, float);
extern void func_002AFFD8(void *, void *, int);
extern unsigned char *func_002AB1F0(void *);
extern int func_00283CF0(float);
extern int func_002761F8(void *, void *, int, void *, int);
extern void func_L00_003ACC88(void *, void *);
extern void func_002A0F48(void *);
extern void func_002ACA50(void *, void *, int);
extern int func_002FED90(void *, void *, float, float, float);

/* Allocates and aims a projectile, preserving the independent integer and FP
 * argument banks (four pointers/integers and four floats, the last unused). */
unsigned char *func_L00_003AB9C0(unsigned char *owner, void *position,
    unsigned char *target, void *color, float reach, float low, float high, float unused)
{
    LaunchVector predicted, direction, projection;
    unsigned char *object = func_0029EFD0(0x5da);
    unsigned char *vars, *info, *hero = D_00189E20;
    float speed;
    if (!object) return 0;
    object[0x30] = 255;
    object[0x31] = 1;
    object[0x20] = 0;
    *(u16 *)(object + 0x32) = 255;
    *(u16 *)(object + 0x34) |= 0x100;
    vars = *(unsigned char **)(object + 0x68);
    if ((u32)D_L00_001AF7A0 >= 9) D_L00_001AF7A0 = 0;
    *(int *)(vars + 0x2c) = D_L00_001AF7A0;
    D_L00_001AF7A0 = (D_L00_001AF7A0 + 1) % 8;
    speed = *(float *)(D_L00_00262570 + D_00139583[0] * 0xe0 + 0x50) * 0.016666668f;
    qcopy(object + 0x10, position);
    if (target) {
        func_00282D30(direction, target + 0xe0, reach);
        func_00282CC0(predicted, target + 0x10, direction);
    } else qzero(predicted);
    if (*(short *)(hero + 0x24ec) == 1) {
        func_00282F20(object + 0xc0, owner + 0xd0, -1.0f);
        func_00282D30(object + 0xd0, owner + 0xc0, -1.0f);
        qcopy(object + 0xe0, owner + 0xe0);
    } else if (target) {
        func_00282CF0(object + 0xc0, predicted, object + 0x10);
        func_00282F20(object + 0xc0, object + 0xc0, 1.0f);
        func_00282DD8(object + 0xd0, object + 0xc0,
            *(unsigned char **)(hero + 0x2290) + 0xe0);
        func_00282F20(object + 0xd0, object + 0xd0, 1.0f);
        func_00282DD8(object + 0xe0, object + 0xd0, object + 0xc0);
    } else {
        qcopy(object + 0xc0, hero + 0x760);
        if (*(int *)(hero + 0x1500))
            func_L00_0037FA90(object + 0xc0, position, 1.0f, 75.0f, 0.52359885f);
        func_00282DD8(object + 0xd0, object + 0xc0, hero + 0x750);
        func_00282F20(object + 0xd0, object + 0xd0, 1.0f);
        func_00282DD8(object + 0xe0, object + 0xd0, object + 0xc0);
    }
    *(float *)(object + 0xec) = *(float *)(object + 0xdc) = *(float *)(object + 0xcc) = 0.0f;
    *(void **)(vars + 0xc) = owner;
    *(float *)(vars + 0x1c) = func_002A7878(low, high);
    if (target) *(float *)(vars + 0x1c) = 0;
    *(float *)(vars + 0x20) = func_002A78D8(6.0f, 10.0f);
    *(float *)(vars + 0x18) = speed;
    *(float *)(vars + 0x28) = func_002A7940();
    vars[0x26] = vars[0x27] = 1;
    *(void **)(vars + 0x10) = target;
    qcopy(vars + 0x30, object + 0xc0);
    qcopy(vars + 0x40, color);
    if (D_L00_001A8FF0) {
        func_002AFFD8(object + 0x10, direction, 1);
        func_00282D30(projection, direction, func_00282DB0(direction, vars + 0x30));
        func_00282CF0(vars + 0x30, vars + 0x30, projection);
    }
    if (target) {
        info = func_002AB1F0(target);
        if (info) {
            *(u16 *)(info + 0x1e) |= 0x80;
            if (info[0xb]) vars[0x26] = 0;
        }
    }
    *(short *)(vars + 0x24) = func_00283CF0(75.0f / speed);
    if (target) {
        func_00282D30(direction, target + 0xe0, reach);
        func_00282CC0(direction, target + 0x10, direction);
        *(float *)(vars + 0) = direction[0];
        *(float *)(vars + 4) = direction[1];
        *(float *)(vars + 8) = direction[2];
        *(float *)(vars + 0x14) = reach;
    }
    qcopy(direction, owner + 0x10);
    direction[2] = ((float *)position)[2];
    if (func_002761F8(direction, position, 0, *(void **)(hero + 0x2290), 0)) {
        object[0xbc] = 1;
        qcopy(object + 0x10, D_L00_001BF220);
    }
    func_L00_003ACC88(object, D_L00_0023B710 + *(int *)(vars + 0x2c) * 64);
    func_002A0F48(object);
    func_002ACA50(object, D_L00_001B1FB0, 0x1f);
    *(float *)(object + 0x2c) *= 2.5f;
    *(int *)(vars + 0x50) = func_002FED90(object, 0, 1.0f, 1.0f, 1.0f);
    return object;
}
