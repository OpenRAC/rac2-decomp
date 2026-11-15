#include "common.h"
typedef int Quad __attribute__((mode(TI)));
/* Partial resident state, through the last byte read here. */
typedef struct {
    u8 unknown0000[0x2290];
    u8 *active;
    u8 unknown2294[0x20];
    u8 mode;
} ResidentState;
extern ResidentState g_hero_state;
extern u8 g_hero_position[];
extern void *D_L00_001B8E14;
extern void vec_scale_to_length(void *, void *, float);
extern void FastVecScale(void *, void *, float);
extern void FastVecAdd(void *, void *, void *);
extern void FastVecCross(void *, void *, void *);

/* Builds a normalized direction and its mode-dependent scale, then updates the
 * owner's basis and keeps a full aligned copy of its resulting first row. */
/* Points the camera along the hero direction and rebuilds its three axes. */
void cam_build_basis_from_hero(u8 *owner)
{
    Quad direction;
    Quad scaled;
    u8 mode;
    void *basis;
    vec_scale_to_length(&direction, g_hero_state.active + 0xE0, 1.0f);
    mode = g_hero_state.mode;
    if (mode == 2)
        FastVecScale(&scaled, &direction, 9.5f);
    else if (mode == 1)
        FastVecScale(&scaled, &direction, 0.75f);
    else
        FastVecScale(&scaled, &direction, 1.6f);
    FastVecAdd(owner + 0x30, g_hero_position, &scaled);
    basis = D_L00_001B8E14;
    qcopy(owner + 0x20, &direction);
    FastVecCross(owner + 0x10, basis, &direction);
    vec_scale_to_length(owner + 0x10, owner + 0x10, 1.0f);
    FastVecCross(owner, &direction, owner + 0x10);
    qcopy(owner + 0x40, owner);
}
