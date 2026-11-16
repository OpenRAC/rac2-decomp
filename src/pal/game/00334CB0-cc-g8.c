#include "names.h"
/* func_PAL_00334CB0, the PAL copy of func_00333048: the same C, where rename func_002BDBC0 becomes func_PAL_002BE880; rename func_002C7E28 becomes func_PAL_002C8BD0; rename func_0032C700 becomes func_PAL_0032DF28. */
/* func_PAL_00334CB0: an explosion's sparks, pushed particles, ring effect and area hit.
 * In the hit loop the packet's vector is normalized before func_002A8C00 fills it, as
 * retail does at +0x36C: nothing writes sp+0x40 before that call (the slot is not shared),
 * and func_002A8C00 overwrites the whole vector from `direction` without reading it, so the
 * normalize result is dead. Its own -G8 unit (default -O2 -G8 -ffunction-sections).
 */
#include "common.h"
extern void vec_scale_to_length(void *, void *, float);
typedef int TI128_333048 __attribute__((mode(TI)));

typedef struct {
    int model;
    unsigned char kind;
    unsigned char pad05[0x47];
    short f4C;
    unsigned char pad4E[0x92];
} ClassRecord333048;

/* The hit description func_002A8E20 applies to a moby. */
typedef struct {
    float vector[4];
    char pad10[8];
    unsigned char type;
    unsigned char source;
    short oclass;
    char pad1C[4];
    int flag;
    char pad24[0xC];
} HitInfo333048;

extern unsigned char g_item_slot_to_record[];
extern ClassRecord333048 g_weapon_table[];
extern char g_active_camera[];
extern short g_explosion_moby_index_list[] __attribute__((sda));
extern int g_turret_target_moby;
extern char *g_nearby_mobys[];
extern float g_explode_hurt_distance_a __attribute__((sda));
extern float g_explode_hurt_distance_b __attribute__((sda));
extern float math_random_float_range(float, float);
extern float math_random_angle(void);
extern int math_random_int_range(int, int);
extern float math_random_signed_float_range(float, float);
extern void vec_build_spherical_offset(void *, float, float, float);
extern void part_spawn_growing_puff_pal(void *, void *, int, int, int, float);
extern float mat_fast_helper_a(float, float);
extern int FloatToInt(float);
extern float FastAddRotations(float, float);
extern float math_fast_sin_or_cos_a(float);
extern float math_fast_sin_or_cos_b(float);
extern unsigned char *part_spawn_spinning_spark_pal_2(void *, void *, int);
extern void RemoveMobyFromIndexList(void *, short *);
extern void *part_spawn_explosion_pal(void *, float, float, int, int, int, int, int, int, int, int, int, int, int);
extern int coll_process_hit(void *, int, void *, int, float);
extern void FastVecSub(void *, void *, void *);
extern void make_hit_descriptor(void *, void *, int, void *, float);
extern void QueueMobyImpact(void *, void *);
extern void moby_mark_spawned(void *);

/* The class slot table: D_00139568 maps a slot to its class record. */
static inline int func_00333048_kind(int index)
{
    ClassRecord333048 *record = &g_weapon_table[g_item_slot_to_record[index]];
    return record->model != 0 && record->kind == 3;
}

/* func_PAL_00334CB0: thirty sparks around the moby, fifty particles pushed away from the
   point at D_001B5200+0x140, a ring effect, then a hit on every moby in range. The ring prototype is
   interleaved as (pointer, float, float, ints...): the EE passes the two floats in $f12/$f13
   either way, and this order gives retail's argument scheduling. */
void moby_explode_and_hurt_nearby_pal(char *object)
{
    float direction[4] __attribute__((aligned(16)));
    float spark[4] __attribute__((aligned(16)));
    HitInfo333048 hit __attribute__((aligned(16)));
    float distance;
    float yaw;
    float angle;
    int i;
    int j;
    int k;
    int count;
    char *camera;

    PlayMobySound(3, 0, (int *)object);
    for (i = 0; i < 30; i++) {
        distance = math_random_float_range(0.0f, 0.37f);
        yaw = math_random_angle();
        vec_build_spherical_offset(spark, distance, yaw, math_random_angle());
        spark[2] += math_random_float_range(0.35f, 0.6f);
        FastVecAdd(spark, spark, object + 0x10);
        distance = math_random_float_range(0.002f, 0.020000001f);
        yaw = math_random_angle();
        vec_build_spherical_offset(direction, distance, yaw, math_random_angle());
        part_spawn_growing_puff_pal(spark, direction, 0x4F20507F, 0x102F, math_random_int_range(25, 47), 150000.0f);
    }
    camera = g_active_camera;
    for (j = 0; j < 50; j++) {
        angle = mat_fast_helper_a(*(float *)(camera + 0x140) - *(float *)(object + 0x10),
                              *(float *)(camera + 0x144) - *(float *)(object + 0x14));
        FloatToInt(math_random_signed_float_range(1.0f, 2.0f));
        direction[0] = *(float *)(object + 0x10) + math_random_signed_float_range(0.0f, 0.15f);
        direction[1] = *(float *)(object + 0x14) + math_random_signed_float_range(0.0f, 0.15f);
        direction[2] = *(float *)(object + 0x18) + math_random_signed_float_range(0.0f, 0.15f);
        distance = g_explode_hurt_distance_a;
        angle = FastAddRotations(angle, math_random_signed_float_range(0.0f, -1.5707965f));
        spark[0] = math_fast_sin_or_cos_a(angle) * 0.020000001f * distance;
        spark[1] = math_fast_sin_or_cos_b(angle) * 0.020000001f * distance;
        distance = g_explode_hurt_distance_b;
        spark[2] = distance * 0.020000001f;
        part_spawn_spinning_spark_pal_2(direction, spark, 0x10b);
    }
    RemoveMobyFromIndexList(object, g_explosion_moby_index_list);
    part_spawn_explosion_pal(object + 0x10, 1.0f, 20.0f, 1, 25, 20, 20, 20, 45, 1, 1, 1, 0, g_turret_target_moby);
    count = coll_process_hit(object + 0x10, 0, object, 0, 3.0f);
    if (count > 0) {
        char **list = g_nearby_mobys;
        k = count;
        do {
            char *moby = *list;
            if (*(short *)(*(char **)(moby + 0x24) + 0x46) == 5
                || (*(unsigned short *)(moby + 0x34) & 0x4000)) {
                float radius;
                FastVecSub(direction, moby + 0x10, object + 0x10);
                vec_scale_to_length(direction, direction, 1.0f);
                vec_scale_to_length(hit.vector, hit.vector, 1.0f);
                radius = 10.0f;
                if (func_00333048_kind(0x10))
                    radius = 55.0f;
                make_hit_descriptor(hit.vector, object, 0x810000, direction, radius);
                *(TI128_333048 *)hit.vector = *(TI128_333048 *)direction;
                hit.vector[3] = 5627.9248f;
                hit.source = 3;
                hit.flag = 1;
                hit.type = 5;
                hit.oclass = *(short *)(moby + 0xAA);
                QueueMobyImpact(moby, &hit);
            }
            list++;
        } while (--k);
    }
    moby_mark_spawned(object);
}
