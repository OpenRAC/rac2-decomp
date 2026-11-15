#include "include_asm.h"
#include "names.h"
typedef int Quadword __attribute__((mode(TI)));
typedef struct { char pad[23]; unsigned char selected; } Selection;
extern Selection g_item_slot_to_record;
typedef struct { char pad[4]; unsigned char enabled; char body[111]; float scale; char tail[104]; } EffectConfig;
extern EffectConfig g_weapon_l00_table[];
extern void *g_hero_moby;
extern void cam_compute_view_direction(void *, void *, int);
extern void SpawnExplosionEffects(void *, void *, void *, float, float, int, int, int, float, float, float, float, int, float, int, int, int, int, int);
extern void vec_scale_to_length(void *, void *, float);
extern int coll_process_hit(void *, int, float, void *, void *);
extern int math_random_int_range(int, int);
extern int math_random_int_below(int);
extern float math_random_signed_float_range(float, float);
extern void *part_spawn_ground_effect(void *, int, float, float, int, int, int, void *, float, int);

/* Emits impact effects using the current selection's effect configuration. */
void SpawnConfiguredImpactEffects(char *object, void *point)
{
    float position[4];
    float normal[4];
    char query[48];
    char *state = *(char **)(object + 104);
    int i, effect, sign;
    *(Quadword *)position = *(Quadword *)point;
    if (g_weapon_l00_table[g_item_slot_to_record.selected].enabled) {
        cam_compute_view_direction(position, normal, 1);
        SpawnExplosionEffects(object, normal, position, 0.0f, 0.0f, 10, 3, 16, 4.0f, 2.0f, 9.0f, 1.0f, -1, 15.0f, 1, 1, -1, 0, 0x810001);
        *(int *)(query + 20) = 0x810000;
        *(int *)(query + 32) = 1;
        *(char **)(query + 16) = object;
        *(float *)(query + 28) = g_weapon_l00_table[g_item_slot_to_record.selected].scale;
        *(Quadword *)query = *(Quadword *)state;
        vec_scale_to_length(query, query, 1.0f);
        *(float *)(query + 12) = 5627.925f;
        query[24] = 3;
        query[25] = 2;
        *(unsigned short *)(query + 26) = *(unsigned short *)(object + 170);
        coll_process_hit(position, 1, 2.0f, g_hero_moby, query);
    } else {
        int negative;
        char *spark;
        float *velocity;
        *(Quadword *)normal = 0;
        negative = -1;
        spark = query;
        velocity = normal;
        i = 7;
        do {
            effect = math_random_int_range(6, 16);
            sign = 1;
            if (math_random_int_below(2))
                sign = negative;
            *(float *)(query + 0) = position[0] + math_random_signed_float_range(0.0f, 0.5f);
            *(float *)(query + 4) = position[1] + math_random_signed_float_range(0.0f, 0.5f);
            *(float *)(query + 8) = position[2] + math_random_signed_float_range(0.0f, 0.5f);
            part_spawn_ground_effect(spark, effect, 10.0f, 0.1f, 0x4010ff10, 2, sign, velocity, 0.0f, 1);
            part_spawn_ground_effect(spark, effect, 2.0f, 0.1f, 0xc0ffffff, 2, sign, velocity, 0.0f, 1);
        } while (--i >= 0);
    }
}
