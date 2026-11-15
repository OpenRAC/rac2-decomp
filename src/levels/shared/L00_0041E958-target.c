#include "common.h"

typedef int Quad __attribute__((mode(TI)));
typedef union { u8 b[0x2600]; s16 h[0x1300]; s32 i[0x980]; f32 f[0x980]; char *ptr[0x980]; Quad q[0x260]; } Hero;
extern u8 g_hero_state[];
extern void hero_resolve_stick_direction(int, float);
/* The EE assigns the integer and floating arguments in separate register banks. */
extern char *SelectBestTargetInCone(void *, void *, int *, int, int, int, float, float, float, float, float, int, void *);
extern float mat_fast_helper_a(float, float);
extern void FastVecSub(void *, void *, void *);
extern void cam_set_view_space_height(void *, void *, float);

#define HERO ((Hero *)D_00189E20)

/* Finds what the hero is aiming at (the locked-on target or the best one in range) and stores the aim direction. */
void UpdateHeroAimTarget(float range, float angle, float elevation)
{
    Quad position;
    float heading;
    char *target;
    char *candidate;
    int count;
    if (HERO->i[0xBE8 / 4] != 0)
        return;
    heading = HERO->f[0x98 / 4];
    qcopy(&position, &HERO->q[0]);
    if (HERO->f[0x24B8 / 4] > 0.5f && HERO->h[0x1454 / 2] == 0) {
        char *locked = HERO->ptr[0x1450 / 4];
        if (locked == 0 || (u8)locked[0x20] == 254 || (u8)locked[0x20] == 253) {
            hero_resolve_stick_direction(0, 1.0f);
            heading = HERO->f[0x1A0 / 4];
            qcopy(&position, &HERO->q[0x190 / 16]);
            HERO->i[0xBE4 / 4] = 0;
            HERO->i[0xBE8 / 4] = 1;
        }
    }
    candidate = HERO->ptr[0x1450 / 4];
    if (candidate == 0 || (u8)candidate[0x20] == 254 || (u8)candidate[0x20] == 253)
        target = SelectBestTargetInCone(g_hero_state + 0x80, &position, &count, 0, 0, 0, angle, elevation, range, 0.0f, 0.0f, 1, 0);
    else
        target = candidate;
    if (target && (HERO->i[0xBE4 / 4] == 0 || HERO->i[0xBE8 / 4] != 0)) {
        HERO->f[0xBEC / 4] = mat_fast_helper_a(*(float *)(target + 0x10) - HERO->f[0x80 / 4], *(float *)(target + 0x14) - HERO->f[0x84 / 4]);
        FastVecSub(&HERO->q[0xBC0 / 16], target + 0x10, &HERO->f[0x80 / 4]);
        HERO->ptr[0xBE4 / 4] = target;
    } else {
        HERO->f[0xBEC / 4] = heading;
        qcopy(&HERO->q[0xBC0 / 16], &position);
    }
    cam_set_view_space_height(g_hero_state + 0xBC0, g_hero_state + 0xBC0, 0.0f);
}
