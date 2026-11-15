#include "names.h"
typedef int TI128 __attribute__((mode(TI)));

typedef struct {
    TI128 v0, v1, v2, v3;
    char pad[0x20];
} Local51C0;

extern char *func_0029EFD0(int);
extern void func_002833F0(void *, void *);
extern int func_002AFFD8(void *, void *, int);
extern void func_00282F20(void *, void *, float);
extern void func_00282DD8(void *, void *, void *);
extern float func_00282DB0(void *, void *);
extern float func_00283198(float);
extern void func_00282D30(void *, void *, float);
extern float func_00283180(float);
extern void func_00283958(void *, void *);
extern void func_00283738(void *, void *, void *);
extern void func_0029F338(void *);
extern char *D_L00_001B05DC __attribute__((sda));
extern char D_0018C0B0[];

/* Creates the Mini-Nuke blast object at a position, turns it to face along the given direction, and replaces any earlier blast. */
char *func_L00_003E51C0(TI128 *position, TI128 *direction)
{
    Local51C0 local;
    char *blast = CreateMoby(0xC06 /* moby class 3078 */);
    char *data = *(char **)(blast + 0x68);
    char *basis;
    char *axis;
    char *point;
    float half;
    short header;

    if (blast != 0) {
        header = 0xFF;
        *(short *)(blast + 0x32) = header;
        *(char *)(blast + 0x30) = header;
        *(unsigned short *)(blast + 0x34) |= 0x100;
        *(char *)(blast + 0x20) = 0;
        point = blast + 0x10;
        *(TI128 *)point = *position;
        *(TI128 *)data = *direction;
        basis = blast + 0xC0;
        axis = blast + 0xE0;
        euler_rotation_basis(basis, *(char **)gHeroMoby_0018C0B0 + 0xF0);
        ComputeViewDirection(point, &local.v2, 1);
        vec_scale_to_length(&local.v2, &local.v2, 1.0f);
        FastVecCross(&local.v1, axis, &local.v2);
        half = FastVecDot(axis, &local.v2) * 0.5f;
        FastVecScale(&local.v0, &local.v1, FastSinOrCosB(half));
        *(float *)((char *)&local.v0 + 12) = FastSinOrCosA(half);
        quaternion_to_rotation_basis(&local.v0, &local.v3);
        multiply_matrix3x3(basis, &local.v3, basis);
        if (D_L00_001B05DC != 0)
            MarkMobySpawned(D_L00_001B05DC);
        D_L00_001B05DC = blast;
    }
    return blast;
}
