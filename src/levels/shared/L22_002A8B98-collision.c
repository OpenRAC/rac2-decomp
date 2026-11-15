#include "common.h"
extern char D_00189E20[];
extern void func_L00_002D36E0(void *, float, float, float, int);
extern float func_L00_002D3A58(void *);
extern float func_00282E20(void *);
extern void func_00282F20(void *, void *, float);
extern void func_L00_002D3B58(void *, void *, float);
extern void func_00282D30(void *, void *, float);
extern void func_00282CC0(void *, void *, void *);
extern int func_002761F8(void *, void *, int, void *, int);
extern int func_00278E78(void);
extern float func_L00_002D3EA8(void *);
extern float func_00282DB0(void *, void *);
typedef struct {
    char pad0[0x18]; void *object; int count;
    char pad20[0x20]; float normal[4];
} CollisionResult;
extern CollisionResult D_L22_001C00C0;

/* Checks ahead of the hero for walls and slides the hero's speed along them so it does not run into the wall. */
void func_L22_002B8E10(int force) {
    float start[4], end[4], extended_start[4], extended_end[4];
    float reach, scale, zero, angle;
    int hit;
    char *velocity = gHeroState + 0xF0;
    if (GetViewSpaceVectorLength(velocity) < 0.0016666668f) return;
    {
        char *hero = velocity - 0xF0;
        reach = 0.37f;
        scale = 0.5f;
        if ((unsigned)(*(int *)(hero + 0x229C) - 17) < 2) {
            reach = 0;
            scale = 0.7f;
        } else if (*(u8 *)(hero + 0x22B4) == 1) {
            reach = 0.35f;
            scale = 0.27f;
        } else if (*(u8 *)(hero + 0x22B4) == 2) {
            reach = 1;
            scale = 5;
        }
        zero = 0;
        BuildHeroRelativePoint(start, zero, zero, reach, 1);
        BuildHeroRelativePoint(extended_start, zero, zero, reach * 0.3f, 1);
    }
    if (force != 0 || vec_length_xy(gHeroState + 0xF0) < 0.01f) {
        vec_scale_to_length(end, gHeroState, scale);
        vec_scale_to_length(extended_end, gHeroState, scale * 1.4f);
    } else {
        SetViewSpaceHeight(end, gHeroState + 0xF0, 0);
        vec_scale_to_length(end, end, scale);
        FastVecScale(extended_end, end, 1.4f);
    }
    FastVecAdd(end, end, start);
    hit = -1;
    FastVecAdd(extended_end, extended_end, extended_start);
    {
        char *hero = gHeroState;
        if (CollLine(extended_start, extended_end, 2, *(void **)(hero + 0x2290), 0) && D_L22_001C00C0.count > 0)
            hit = GetCollHitMaterial();
    }
    angle = 0;
    {
        char *hero = gHeroState;
        if (CollLine(start, end, 2, *(void **)(hero + 0x2290), 0) && D_L22_001C00C0.count > 0)
            angle = GetViewSpaceAngle(D_L22_001C00C0.normal);
    }
    if (angle >= 0.8726647f || hit == 8 || hit == 12) {
        char *hero = gHeroState;
        CollisionResult *contact = &D_L22_001C00C0;
        float *normal = contact->normal;
        float dot;
        *(void **)(hero + 0x270) = contact->object;
        SetViewSpaceHeight(normal, normal, 0);
        vec_scale_to_length(normal, normal, 1);
        dot = FastVecDot(normal, hero + 0xF0);
        if (dot < 0) {
            FastVecScale(normal, normal, -dot);
            FastVecAdd(hero + 0xF0, hero + 0xF0, normal);
        }
    }
}
