/* Nonmatching C reconstruction.
 * Profile: -O2 -G0 -ffunction-sections -frac2-qcopy.
 * Compiled 580 bytes; retail 596 bytes.
 * Carrying checks: 0/27 in us, pal and us2. No strict linked qualification.
 * A complete 64-byte matrix/vector workspace and final vector are represented with genuine lifetime reuse. Branch-specific position lifetimes changed 584 to 580 bytes. Saved-register priorities, branches and vector/camera-address scheduling differ. Reopen with allocator data; do not add padding or zero unassigned lanes.
 */
#include "common.h"
extern int func_00282978(short *);
extern void func_002B9180(void *);
extern void func_0029FC20(char *, int, char *);
extern void func_002830C0(void *, void *, void *);
extern void func_00282CC0(void *, void *, void *);
extern void func_00283098(void *, void *, void *);
extern void func_00282CF0(void *, void *, void *);
extern float func_00282DB0(void *, void *);
extern int func_00283CF0(float);
extern void func_00282F20(void *, void *, float);
extern float func_00283CE0(int);
extern char D_L00_001B8DC0[];

typedef union {
    float matrix[16];
    struct { float offset[4], direction[4], displacement[4], origin[4]; } v;
} EffectWorkspace;

void func_L00_0033E3B8(unsigned char *particle)
{
    EffectWorkspace temp __attribute__((aligned(16)));
    float transformed[4] __attribute__((aligned(16)));
    char *data = (char *)particle + 0x20;
    char *owner;
    float *position;
    float *ownerPosition;
    float cosine;
    if (*(short *)(particle + 0xA) >= 0 && func_00282978((short *)(particle + 0xA))) {
        func_002B9180(particle);
        return;
    }
    owner = *(char **)data;
    if (owner && *(signed char *)(owner + 0x20) < 0) {
        func_002B9180(particle);
        return;
    }
    if (owner) {
        ownerPosition = (float *)(owner + 0x10);
        if (*(int *)(data + 4) >= 0) {
            position = (float *)(particle + 0x10);
            func_0029FC20(owner, *(int *)(data + 4), (char *)temp.matrix);
            temp.matrix[15] = 0;
            func_002830C0(transformed, data + 0x10, temp.matrix);
            func_00282CC0(position, temp.v.origin, transformed);
        } else {
            position = (float *)(particle + 0x10);
            qcopy(position, ownerPosition);
            func_00283098(temp.v.offset, data + 0x10, owner + 0xC0);
            func_00282CC0(position, position, temp.v.offset);
        }
        if (*(short *)(data + 0xE)) {
            func_00282CF0(temp.v.direction, position, D_L00_001B8DC0);
            particle[8] = func_00283CF0(func_00282DB0(temp.v.direction, D_L00_001B8DC0 + 0x230) * 6.0f);
        }
        if (*(short *)(data + 0xC)) {
            func_00282CF0(temp.v.displacement, position, ownerPosition);
            func_00282F20(temp.v.direction, temp.v.direction, 1.0f);
            func_00282F20(temp.v.displacement, temp.v.displacement, 1.0f);
            cosine = -func_00282DB0(temp.v.direction, temp.v.displacement);
            if (cosine < 0.0f)
                *(unsigned int *)(particle + 4) &= 0x05FFFFFF;
            else
                *(unsigned int *)(particle + 4) = (*(unsigned int *)(particle + 4) & 0x00FFFFFF) |
                    (func_00283CF0(func_00283CE0(particle[7]) * cosine) << 24);
        }
    } else {
        position = (float *)(particle + 0x10);
        qcopy(position, data + 0x10);
    }
    func_00282CF0(temp.v.offset, D_L00_001B8DC0, position);
    func_00282F20(temp.v.offset, temp.v.offset, *(float *)(data + 8));
    func_00282CC0(position, position, temp.v.offset);
}
