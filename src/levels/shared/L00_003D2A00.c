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

extern void FastVecSub(void *, void *, void *);
extern void vec_scale_to_length(void *, void *, float);
extern int CollLine(void *,void *,int,void *,void *);
extern float fast_vec_dist(void *, void *);
extern char *large_spark_trail_create(char *, char *, char *, int);
extern void QueueMobyImpact(int, void *);
extern int StartAttachedEffect(int, int, char *);
extern int g_hero_moby;
extern unsigned char D_00139582;
extern L00AimState g_collision_result;
extern L00AimEntry g_weapon_l00_table[];

/* Fires a shot from the origin toward the target and, if it hits something, damages it. Damage drops with distance. */
int weapon_fire_damage_ray(char *source, char *origin, char *target, char *result)
{
    char offset[16];
    float distance;
    float saved;
    int hitObject;

    FastVecSub(result, target, origin);
    vec_scale_to_length(result, result, 1.5f);
    *(float *)(result + 0xC) = 5627.9248046875f;
    if (CollLine(origin, target, 0x10, g_hero_moby, 0) != 0) {
        FastVecSub(offset, target, origin);
        vec_scale_to_length(offset, offset, 1.0f);
        FastVecSub(offset, (char *)g_collision_result.vector_20, origin);
        large_spark_trail_create(origin, offset, (char *)g_collision_result.vector_20, 1);
        if (g_collision_result.object_18 != 0) {
            saved = (g_weapon_l00_table + D_00139582)->value_70;
            distance = fast_vec_dist((char *)g_collision_result.vector_20, origin);
            if (distance < 10.0f) {
                *(float *)(result + 0x1C) = saved;
            } else if (distance < 14.0f) {
                *(float *)(result + 0x1C) = saved * 0.75f;
            } else if (distance < 20.0f) {
                *(float *)(result + 0x1C) = saved * 0.5f;
            } else {
                *(float *)(result + 0x1C) = saved * 0.125f;
            }
            QueueMobyImpact(g_collision_result.object_18, result);
            StartAttachedEffect(g_collision_result.object_18, 0x44, source);
        }
        hitObject = g_collision_result.object_18;
    } else {
    FastVecSub(offset, target, origin);
    large_spark_trail_create(origin, offset, target, 0);
    hitObject = 0;
    }
    return hitObject;
}
