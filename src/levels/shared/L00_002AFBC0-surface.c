#include "common.h"

typedef struct {
    f32 x, y, z, w;
} Vec4458;

typedef struct {
    Vec4458 dir0;       /* 0x0: the ray direction while nearly still */
    u8 pad10[0xF0 - 0x10];
    Vec4458 velocity;   /* 0xF0 */
    u8 pad100[0x270 - 0x100];
    s32 x270;
    u8 pad274[0x2290 - 0x274];
    s32 moby;           /* 0x2290 */
    u8 pad2294[0x229C - 0x2294];
    s32 x229C;
    u8 pad22A0[0x22B4 - 0x22A0];
    u8 mode;            /* 0x22B4 */
} Hero4458;

typedef struct {
    u8 pad0[0x18];
    s32 x18;
    s32 hits;           /* 0x1C */
    u8 pad20[0x40 - 0x20];
    Vec4458 normal;     /* 0x40 */
} Hit4458;

extern Hero4458 D_00189E20;
extern Hit4458 D_L00_001BF200;

extern float func_L00_002D3A58(Vec4458 *);
/* Called as (vector, flag, x, y, z); declared with the flag last so the EE passes the
 * floats in f12-f14 and the flag in a1. */
extern void func_L00_002D36E0(Vec4458 *, float, float, float, int);
extern float func_00282E20(Vec4458 *);
extern void func_00282F20(Vec4458 *, Vec4458 *, float);
extern void func_L00_002D3B58(Vec4458 *, Vec4458 *, float);
extern void func_00282D30(Vec4458 *, Vec4458 *, float);
extern void func_00282CC0(Vec4458 *, Vec4458 *, Vec4458 *);
extern int func_002761F8(Vec4458 *, Vec4458 *, int, s32, int);
extern int func_00278E78(void);
extern float func_L00_002D3EA8(Vec4458 *);
extern float func_00282DB0(Vec4458 *, Vec4458 *);

/* While the hero moves, casts two short rays ahead of it (along its velocity, or along
 * the direction at +0x0 when nearly still or when forced): one from a point at the mode's
 * height, one from 0.3 of it reaching 1.4 times as far.  A slope of at least 50 degrees
 * under the first ray, or collision type 8 or 12 under the second, records the hit's word
 * at +0x18 in +0x270 and removes the part of the velocity at +0xF0 that runs into the
 * flattened surface normal. */
/* Looks ahead of the moving hero for a steep wall and removes the speed that would push into it. */
void func_L00_002B4458(int force)
{
    Vec4458 upper;
    Vec4458 upperEnd;
    Vec4458 lower;
    Vec4458 lowerEnd;
    float height;
    float reach;
    float slope;
    float dot;
    int type;

    if (GetViewSpaceVectorLength(&gHeroState.velocity) < 0.0016666668f)
        return;
    height = 0.37f;
    reach = 0.5f;
    if ((unsigned int)(gHeroState.x229C - 17) < 2) {
        height = 0.0f;
        reach = 0.7f;
    } else if (gHeroState.mode == 1) {
        height = 0.35f;
        reach = 0.27f;
    }
    BuildHeroRelativePoint(&upper, 0.0f, 0.0f, height, 1);
    BuildHeroRelativePoint(&lower, 0.0f, 0.0f, height * 0.3f, 1);
    if (force || vec_length_xy(&gHeroState.velocity) < 0.01f) {
        vec_scale_to_length(&upperEnd, &gHeroState.dir0, reach);
        vec_scale_to_length(&lowerEnd, &gHeroState.dir0, reach * 1.4f);
    } else {
        SetViewSpaceHeight(&upperEnd, &gHeroState.velocity, 0.0f);
        vec_scale_to_length(&upperEnd, &upperEnd, reach);
        FastVecScale(&lowerEnd, &upperEnd, 1.4f);
    }
    type = -1;
    FastVecAdd(&upperEnd, &upperEnd, &upper);
    FastVecAdd(&lowerEnd, &lowerEnd, &lower);
    if (CollLine(&lower, &lowerEnd, 2, gHeroState.moby, 0) && gCollisionResult.hits > 0)
        type = GetCollHitMaterial();
    slope = 0.0f;
    if (CollLine(&upper, &upperEnd, 2, gHeroState.moby, 0) && gCollisionResult.hits > 0)
        slope = GetViewSpaceAngle(&gCollisionResult.normal);
    if (slope >= 0.87266469f || type == 8 || type == 12) {
        gHeroState.x270 = gCollisionResult.x18;
        SetViewSpaceHeight(&gCollisionResult.normal, &gCollisionResult.normal, 0.0f);
        vec_scale_to_length(&gCollisionResult.normal, &gCollisionResult.normal, 1.0f);
        dot = FastVecDot(&gCollisionResult.normal, &gHeroState.velocity);
        if (dot < 0.0f) {
            FastVecScale(&gCollisionResult.normal, &gCollisionResult.normal, -dot);
            FastVecAdd(&gHeroState.velocity, &gHeroState.velocity, &gCollisionResult.normal);
        }
    }
}
