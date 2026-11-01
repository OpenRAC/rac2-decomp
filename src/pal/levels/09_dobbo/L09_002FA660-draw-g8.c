#include "include_asm.h"

#include "common.h"
extern int D_001A79F0[3] __attribute__((sda));
typedef struct { char pad[0x34]; int frame; } DrawState;
extern DrawState D_L09_001BD700;
extern float D_L09_001A93E0 __attribute__((sda));
extern float D_L09_001A9420[4][4] MACRO_ADDR;
extern void func_002833F0(void *, void *);
extern void func_00282F20(void *, void *, float);
extern void func_00283098(void *, void *, void *);
extern void func_00282CC0(void *, void *, void *);
extern float func_00283CE0(int);
extern float func_00283198(float);
extern int func_00283CF0(float);
extern void func_L01_002E2608(void *, int, int, int, int);

/* Draws the pulsing quad that marks the object while the level is src state 9: its corners are
   rotated about Z, moved to the object and queued with a sine-modulated alpha. */
void func_PAL_L09_002FA660(char *moby)
{
    float mat[3][4];
    float rot[4];
    float corners[4][4];
    float offset[4];
    float *dest, *src, *first;
    int i, id, phase;
    unsigned int color;

    if (D_001A79F0[0] != 9)
        return;

    id = -1;
    if ((unsigned int)(D_L09_001BD700.frame - 2) <= 998)
        id = 0x47;
    if (id == -1)
        return;

    qzero_nc(rot);
    rot[2] = D_L09_001A93E0;
    func_002833F0(mat, rot);
    func_00282F20(offset, mat, 0.05f);
    first = corners[0];
    dest = first;
    src = D_L09_001A9420[0];
    for (i = 3; i >= 0; --i) {
        func_00283098(dest, src, mat);
        src -= 4;
        func_00282CC0(dest, dest, moby + 0x10);
        func_00282CC0(dest, dest, offset);
        dest += 4;
    }

    phase = D_L09_001BD700.frame % 100;
    {
        float denom = func_00283CE0(100);
        float angle = (float)phase * 6.283186f;
        angle /= denom;
        color = func_00283CF0((func_00283198(angle) * 0.5f + 0.5f) * 48.0f);
    }
    color = ((color + 80) << 24) | 0x808080;
    func_L01_002E2608(first, id, 0, color, 0);
}
