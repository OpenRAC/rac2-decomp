#include "include_asm.h"

#include "common.h"
extern unsigned char g_hero_state[];
typedef int HitWord128 __attribute__((mode(TI)));
typedef union { HitWord128 word; float values[4]; } HitVector;
typedef struct {
    char prefix[4];
    unsigned char enabled;
    char middle[0x74 - 5];
    float scale;
    char suffix[0xE0 - 0x78];
} HitTuning;
typedef struct {
    HitVector direction;
    void *owner;
    int flags;
    unsigned char enabled, kind;
    unsigned short classId;
    float scale;
    int active;
    char suffix[12];
} HitRequest;
extern unsigned char g_item_slot_to_record[];
extern HitTuning g_weapon_l00_table[] __attribute__((nosda));
extern int g_active_tether_object;
extern char *g_area_hit_targets[] __attribute__((nosda));
extern void *SpawnExplosion_pal(void *, float, float, int, int, int, int, int, int, int, int, int, int, int);
extern void vec_scale_to_length(void *, void *, float);
extern int coll_process_hit(void *, int, void *, void *, float);
extern int func_PAL_00335DD0(char *, int, int);
extern int math_random_int_range(int, int);
extern int math_random_int_below(int);
extern float math_random_signed_float_range(float, float);
extern char *part_spawn_ground_effect(void *, int, float, float, unsigned int, int, int, void *, float, int);

/* Apply the configured area hit, or emit eight pairs of particles around the impact.
 * The hit request and particle vectors share one scratch area. Integer and FP
 * arguments retain the measured order within their independent EE register banks. */
void ApplyAreaHitOrEmitParticles_pal(char *object, HitVector *source)
{
    char *state = *(char **)(object + 0x68);
    struct {
        HitVector position;
        union { HitRequest request; struct { HitVector zero, jitter; } particles; } u;
    } scratch;
    int count, i;
    int particle;

    qcopy(&scratch.position, source);
    if (g_weapon_l00_table[g_item_slot_to_record[0x17]].enabled) {
        SpawnExplosion_pal(object + 0x10, 1.0f, 20.0f, 1, 0x28, 0x14, 0x1E, 0x28, 0x32, 1,
                      1, 1, 0, g_active_tether_object);
        scratch.u.request.flags = 0x810000;
        scratch.u.request.active = 1;
        scratch.u.request.owner = object;
        scratch.u.request.scale = g_weapon_l00_table[g_item_slot_to_record[0x17]].scale;
        qcopy(&scratch.u.request.direction, state);
        vec_scale_to_length(&scratch.u.request.direction, &scratch.u.request.direction, 1.0f);
        scratch.u.request.direction.values[3] = 5627.9248046875f;
        scratch.u.request.enabled = 3;
        scratch.u.request.kind = 2;
        scratch.u.request.classId = *(unsigned short *)(object + 0xAA);
        count = coll_process_hit(&scratch.position, 1, *(char **)(g_hero_state + 0x2290), &scratch.u.request, 2.0f);
        for (i = 0; i < count; i++)
            func_PAL_00335DD0(g_area_hit_targets[i], 0x42, *(int *)(object + 0xB8));
    } else {
        int negative;
        HitVector *jitter, *zero;
        scratch.u.particles.zero.word = 0;
        negative = -1;
        jitter = &scratch.u.particles.jitter;
        zero = &scratch.u.particles.zero;
        particle = 7;
        do {
            int lifetime = math_random_int_range(6, 16);
            int sign = math_random_int_below(2) ? negative : 1;
            scratch.u.particles.jitter.values[0] = scratch.position.values[0] + math_random_signed_float_range(0.0f, 0.5f);
            scratch.u.particles.jitter.values[1] = scratch.position.values[1] + math_random_signed_float_range(0.0f, 0.5f);
            scratch.u.particles.jitter.values[2] = scratch.position.values[2] + math_random_signed_float_range(0.0f, 0.5f);
            part_spawn_ground_effect(jitter, lifetime, 10.0f, 0.1f, 0x4010FF10, 2, sign, zero, 0.0f, 1);
            part_spawn_ground_effect(jitter, lifetime, 2.0f, 0.1f, (int)0xC0FFFFFF, 2, sign, zero, 0.0f, 1);
        } while (--particle >= 0);
    }
}
