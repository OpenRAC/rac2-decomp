#include "common.h"
typedef int Quad __attribute__((mode(TI)));
/* Partial resident state, through the last byte read here. */
typedef struct {
    u8 unknown0000[0x2290];
    u8 *active;
    u8 unknown2294[0x20];
    u8 mode;
} ResidentState;
extern ResidentState D_00189E20;
extern u8 D_00189EA0[];
extern void *D_L00_001B8E14;
extern void func_00282F20(void *, void *, float);
extern void func_00282D30(void *, void *, float);
extern void func_00282CC0(void *, void *, void *);
extern void func_00282DD8(void *, void *, void *);

/* Builds a normalized direction and its mode-dependent scale, then updates the
 * owner's basis and keeps a full aligned copy of its resulting first row. */
/* Points the camera along the hero direction and rebuilds its three axes. */
void func_L00_00426560(u8 *owner)
{
    Quad direction;
    Quad scaled;
    u8 mode;
    void *basis;
    vec_scale_to_length(&direction, gHeroState.active + 0xE0, 1.0f);
    mode = gHeroState.mode;
    if (mode == 2)
        FastVecScale(&scaled, &direction, 9.5f);
    else if (mode == 1)
        FastVecScale(&scaled, &direction, 0.75f);
    else
        FastVecScale(&scaled, &direction, 1.6f);
    FastVecAdd(owner + 0x30, gHeroPosition, &scaled);
    basis = D_L00_001B8E14;
    qcopy(owner + 0x20, &direction);
    FastVecCross(owner + 0x10, basis, &direction);
    vec_scale_to_length(owner + 0x10, owner + 0x10, 1.0f);
    FastVecCross(owner, &direction, owner + 0x10);
    qcopy(owner + 0x40, owner);
}
