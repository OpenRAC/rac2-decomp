/* func_L00_003D2A00: aim the object at the level target and fade its alpha by distance. */
#include "include_asm.h"
#include "names.h"

typedef struct {
    unsigned char pad_000[0x18];
    int object_18;
    unsigned char pad_01C[4];
    float vector_20[4];
} L00AimState;

typedef struct {
    unsigned char pad_000[0x70];
    float value_70;
    unsigned char pad_074[0x6C];
} L00AimEntry;

extern void func_00282CF0(void *, void *, void *);
extern void func_00282F20(void *, void *, float);
extern int func_002761F8(void *,void *,int,void *,void *);
extern float func_00282E48(void *, void *);
extern char *func_L00_003FCA40(char *, char *, char *, int);
extern void func_002A8E20(int, void *);
extern void func_0032D758(int, int, char *);
extern int D_0018C0B0;
extern unsigned char D_00139582;
extern L00AimState D_L00_001BF200;
extern L00AimEntry D_L00_00262570[];

/* Fires a shot from the origin toward the target and, if it hits something, damages it. Damage drops with distance. */
int func_L00_003D2A00(char *source, char *origin, char *target, char *result)
{
    char offset[16];
    float distance;
    float saved;
    int hitObject;

    FastVecSub(result, target, origin);
    vec_scale_to_length(result, result, 1.5f);
    *(float *)(result + 0xC) = 5627.9248046875f;
    if (CollLine(origin, target, 0x10, gHeroMoby_0018C0B0, 0) != 0) {
        FastVecSub(offset, target, origin);
        vec_scale_to_length(offset, offset, 1.0f);
        FastVecSub(offset, (char *)gCollisionResult.vector_20, origin);
        CreateLargeSparkTrailObject(origin, offset, (char *)gCollisionResult.vector_20, 1);
        if (gCollisionResult.object_18 != 0) {
            saved = (gWeaponTable_L00 + D_00139582)->value_70;
            distance = fast_vec_dist((char *)gCollisionResult.vector_20, origin);
            if (distance < 10.0f) {
                *(float *)(result + 0x1C) = saved;
            } else if (distance < 14.0f) {
                *(float *)(result + 0x1C) = saved * 0.75f;
            } else if (distance < 20.0f) {
                *(float *)(result + 0x1C) = saved * 0.5f;
            } else {
                *(float *)(result + 0x1C) = saved * 0.125f;
            }
            QueueMobyImpact(gCollisionResult.object_18, result);
            StartAttachedEffect(gCollisionResult.object_18, 0x44, source);
        }
        hitObject = gCollisionResult.object_18;
    } else {
    FastVecSub(offset, target, origin);
    CreateLargeSparkTrailObject(origin, offset, target, 0);
    hitObject = 0;
    }
    return hitObject;
}
