/* func_L00_00423038 - retained C reconstruction, not an exact match.
 * Profile: -O2 -G0 -ffunction-sections.
 * Measured in src/levels/shared/L00_00423038-g8.c: 592/596 bytes.
 * US: 0/27 local places; PAL: 0/27 local places; US2: 0/27 local places.
 * No strict linked build was run because no local placement matched.
 * Scratch vectors and the three-row matrix have measured extents; base lifetime, GPR allocation and surrounding copy scheduling differ. G0 and G8 tied. Reopen with allocator/copy evidence.
 */

#include "common.h"

typedef struct { float x, y, z, w; } Vector;
typedef struct { Vector row[3]; } Matrix;
typedef struct {
    Vector up, scaled, delta, endpoint, transformed, offset;
    Matrix basis;
    Vector difference;
} CameraScratch;
extern char *D_L00_001B8E10 MACRO_ADDR;
extern char D_00189E20[];
extern int D_L00_001B184C MACRO_ADDR;
extern Vector D_L00_001BF220;
extern Vector D_L00_001B8E50;
extern void func_00283678(void *, void *);
extern void func_00283098(void *, void *, void *);
extern void func_00282CC0(void *, void *, void *);
extern void func_00282D30(void *, void *, float);
extern int func_002761F8(void *, void *, unsigned int, void *, void *);
extern void func_00282CF0(void *, void *, void *);
extern float func_00282DF0(void *);
extern void func_00282F20(void *, void *, float);
extern void func_00282DD8(void *, void *, void *);

void func_L00_00423038(int reposition)
{
    CameraScratch scratch;
    char *object = D_L00_001B8E10;
    char *state = *(char **)(object + 0x70);
    char *transform = state + 0x60;
    char *movement = state + 0x160;
    char *position;
    float length;
    if (reposition) {
        scratch.offset.x = -*(float *)(movement + 0x2C);
        scratch.offset.y = 0.0f;
        scratch.offset.z = *(float *)(movement + 0x30);
        scratch.offset.w = 0.0f;
        func_00283678(&scratch.basis, D_00189E20);
        func_00283098(&scratch.transformed, &scratch.offset, *(char **)(transform + 0xC0) + 0xC0);
        position = object + 0x30;
        func_00282CC0(position, transform, &scratch.transformed);
        func_00282D30(&scratch.scaled, *(char **)(transform + 0xC0) + 0xE0, *(float *)(transform + 0xB0));
        func_00282CC0(&scratch.endpoint, transform, &scratch.scaled);
        if (func_002761F8(&scratch.endpoint, position, D_L00_001B184C, *(char **)(D_00189E20 + 0x2290), 0)) {
            func_00282CF0(&scratch.difference, &D_L00_001BF220, &scratch.endpoint);
            length = func_00282DF0(&scratch.difference);
            if (length == 0.0f) {
                qcopy(position, &scratch.endpoint);
            } else {
                func_00282D30(&scratch.difference, &scratch.difference, (length - 0.5f) / length);
                func_00282CC0(position, &scratch.endpoint, &scratch.difference);
            }
        }
    }
    position = object + 0x30;
    *(float *)(object + 0x64) = *(float *)position;
    *(float *)(object + 0x68) = *(float *)(position + 4);
    *(float *)(object + 0x6C) = *(float *)(position + 8);
    qcopy(&scratch.up, &D_L00_001B8E50);
    func_00282F20(&scratch.scaled, &scratch.up, *(float *)(transform + 0xB0));
    func_00282CC0(&scratch.endpoint, &scratch.scaled, transform);
    func_00282CF0(&scratch.delta, &scratch.endpoint, position);
    func_00282F20(object, &scratch.delta, 1.0f);
    qcopy(object + 0x20, &scratch.up);
    func_00282DD8(object + 0x10, object, object + 0x20);
    func_00282F20(object + 0x10, object + 0x10, 1.0f);
    func_00282DD8(object + 0x20, object + 0x10, object);
    qcopy(object + 0x40, object);
}