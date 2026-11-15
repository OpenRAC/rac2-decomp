/* func_L00_003A5DC0: trace a beam and apply distance-scaled damage at its contact point. */
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
extern char *func_L00_003FC108(char *, char *, char *, int);
extern void func_002A8E20(int, void *);
extern void func_0032D758(int, int, char *);
extern int D_0018C0B0;
extern unsigned char D_00139582;
extern L00AimState D_L00_001BF200;
extern L00AimEntry D_L00_00262570[];

/* Shoots a beam from start to end. Whatever it hits takes less damage the farther the hit is from the start. */
int func_L00_003A5DC0(char *source, char *start, char *end, char *impactInfo)
{
    char ray[16];
    float distance;
    float baseDamage;
    int hitObject;

    FastVecSub(impactInfo, end, start);
    vec_scale_to_length(impactInfo, impactInfo, 1.5f);
    *(float *)(impactInfo + 0xC) = 5627.9248046875f;
    if (CollLine(start, end, 0x10, gHeroMoby_0018C0B0, 0) != 0) {
        FastVecSub(ray, end, start);
        vec_scale_to_length(ray, ray, 1.0f);
        FastVecSub(ray, (char *)gCollisionResult.vector_20, start);
        CreateSparkTrailObject(start, ray, (char *)gCollisionResult.vector_20, 1);
        if (gCollisionResult.object_18 != 0) {
            baseDamage = (gWeaponTable_L00 + D_00139582)->value_70;
            distance = fast_vec_dist((char *)gCollisionResult.vector_20, start);
            if (distance < 10.0f) {
                *(float *)(impactInfo + 0x1C) = baseDamage;
            } else if (distance < 14.0f) {
                *(float *)(impactInfo + 0x1C) = baseDamage * 0.75f;
            } else if (distance < 20.0f) {
                *(float *)(impactInfo + 0x1C) = baseDamage * 0.5f;
            } else {
                *(float *)(impactInfo + 0x1C) = baseDamage * 0.125f;
            }
            QueueMobyImpact(gCollisionResult.object_18, impactInfo);
            StartAttachedEffect(gCollisionResult.object_18, 26, source);
        }
        hitObject = gCollisionResult.object_18;
    } else {
    FastVecSub(ray, end, start);
    CreateSparkTrailObject(start, ray, end, 0);
    hitObject = 0;
    }
    return hitObject;
}
