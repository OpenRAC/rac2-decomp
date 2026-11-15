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

extern void FastVecSub(void *, void *, void *);
extern void vec_scale_to_length(void *, void *, float);
extern int CollLine(void *,void *,int,void *,void *);
extern float fast_vec_dist(void *, void *);
extern char *spark_trail_create(char *, char *, char *, int);
extern void QueueMobyImpact(int, void *);
extern void StartAttachedEffect(int, int, char *);
extern int g_hero_moby;
extern unsigned char D_00139582;
extern L00AimState g_collision_result;
extern L00AimEntry g_weapon_l00_table[];

/* Shoots a beam from start to end. Whatever it hits takes less damage the farther the hit is from the start. */
int beam_trace_and_apply_damage(char *source, char *start, char *end, char *impactInfo)
{
    char ray[16];
    float distance;
    float baseDamage;
    int hitObject;

    FastVecSub(impactInfo, end, start);
    vec_scale_to_length(impactInfo, impactInfo, 1.5f);
    *(float *)(impactInfo + 0xC) = 5627.9248046875f;
    if (CollLine(start, end, 0x10, g_hero_moby, 0) != 0) {
        FastVecSub(ray, end, start);
        vec_scale_to_length(ray, ray, 1.0f);
        FastVecSub(ray, (char *)g_collision_result.vector_20, start);
        spark_trail_create(start, ray, (char *)g_collision_result.vector_20, 1);
        if (g_collision_result.object_18 != 0) {
            baseDamage = (g_weapon_l00_table + D_00139582)->value_70;
            distance = fast_vec_dist((char *)g_collision_result.vector_20, start);
            if (distance < 10.0f) {
                *(float *)(impactInfo + 0x1C) = baseDamage;
            } else if (distance < 14.0f) {
                *(float *)(impactInfo + 0x1C) = baseDamage * 0.75f;
            } else if (distance < 20.0f) {
                *(float *)(impactInfo + 0x1C) = baseDamage * 0.5f;
            } else {
                *(float *)(impactInfo + 0x1C) = baseDamage * 0.125f;
            }
            QueueMobyImpact(g_collision_result.object_18, impactInfo);
            StartAttachedEffect(g_collision_result.object_18, 26, source);
        }
        hitObject = g_collision_result.object_18;
    } else {
    FastVecSub(ray, end, start);
    spark_trail_create(start, ray, end, 0);
    hitObject = 0;
    }
    return hitObject;
}
