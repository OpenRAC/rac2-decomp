#include "include_asm.h"

#include "common.h"
extern float g_impact_spark_scale_b __attribute__((sda));
extern float g_impact_spark_scale_a __attribute__((sda));
extern float g_projectile_hit_radius_alt __attribute__((sda));
extern float g_projectile_hit_radius_normal __attribute__((sda));
extern char *g_hit_l05_result __attribute__((nosda));
extern void vec_scale_to_length(void *, void *, float);
extern int coll_process_hit(void *, float, int, char *, void *);
extern float math_random_signed_float_range(float, float);
extern float math_random_angle(void);
extern void vec_build_spherical_offset(void *, float, float, float);
extern int math_random_int_range(int, int);
extern char *part_spawn_spinning_spark_pal(void *, float, float, float, float, int, void *, u32, int);
extern int math_random_int_below(int);
typedef int ImpactTI __attribute__((mode(TI)));
typedef union { ImpactTI q; float f[4]; } ImpactVector;
typedef struct {
    ImpactVector pos;
    void *owner;
    int flags;
    unsigned char type, subtype;
    unsigned short id;
    float scale;
    int one;
} ImpactParams;

/* Queues an impact request (func_00277F48) from the object at pos, then, when the
   object in D_L05_001BFB18 has class 0x956, spawns twenty spark particles there. */
void projectile_l05_impact_spawn_pal(char *object, char *state, float *pos)
{
    ImpactParams params;
    ImpactVector origin, direction;
    int i;
    int spin;
    float angle_a, angle_b;
    float count, speed, spread;
    char *particle, *data;

    params.flags = 0x810000;
    params.owner = object;
    if (*(int *)(state + 0x24))
        params.scale = g_impact_spark_scale_b;
    else
        params.scale = g_impact_spark_scale_a;
    params.one = 1;
    qcopy(&params.pos, state);
    vec_scale_to_length(&params, &params, 1.0f);
    params.pos.f[3] = 5627.925f;
    params.type = 3;
    params.subtype = 2;
    params.id = *(unsigned short *)(object + 0xAA);
    coll_process_hit(pos, *(int *)(state + 0x24) ? g_projectile_hit_radius_alt : g_projectile_hit_radius_normal,
                  1, *(char **)(state + 0x20), &params);
    if (g_hit_l05_result && *(short *)(g_hit_l05_result + 0xAA) == 0x956) {
        count = 20.0f;
        speed = 3.0f;
        spread = 2.0f;
        qcopy(&origin, object + 0x10);
        for (i = 0; (float)i < count; i++) {
            pos[0] = origin.f[0] + math_random_signed_float_range(0.0f, spread);
            pos[1] = origin.f[1] + math_random_signed_float_range(0.0f, spread);
            pos[2] = origin.f[2] + math_random_signed_float_range(0.0f, spread);
            angle_a = math_random_angle();
            angle_b = math_random_angle();
            vec_build_spherical_offset(&direction, 0.060000002f, angle_a, angle_b);
            spin = math_random_int_range(-3, 3);
            particle = part_spawn_spinning_spark_pal(pos, 0.0f, 1.0f, 1.0f, speed * 210000.0f, spin,
                                     &direction, 0x7fffffff, 0);
            if (particle) {
                *(short *)(particle + 0xA) = 100;
                data = particle + 0x20;
                particle[8] = math_random_int_below(255);
                particle[3] = 0x44;
                *(int *)(data + 4) = 2;
                data[0xA] = 127;
                data[0xB] = *(unsigned char *)(particle + 0xA);
            }
        }
    }
}

typedef int TI128 __attribute__((mode(TI)));
extern float g_limited_blast_count __attribute__((sda));
extern s32 g_blast_slot_used[5] MACRO_ADDR;
extern u8 g_hero_l05_state[];
extern void *CreateMoby(s32);
extern s32 math_fast_helper_a(void *, float);
extern float fast_vec_dist(void *, void *);
extern void FastVecSub(void *, void *, void *);
extern float FastVecDot(void *, void *);
extern float math_fast_angle_helper(float);
extern void part_spawn_fire_explosion_pal(void *);

/* spawns object 0x1193 at pos with parent's orientation, when one of the five slots is free:
   fills its vars from the arguments and, if it is in view, grades it against the reference
   point at D_L05_001B9580 + 0x140 */
void *part_spawn_limited_blast_pal(u8 *pos, u8 *parent, s32 flag, float scale, s32 vars_20, s32 vars_24, s32 vars_28,
                        s32 vars_2c, s32 vars_30, s32 vars_18, s32 vars_34, s32 vars_1c, s32 vars_38, s32 vars_48) {
    TI128 sphere;
    TI128 dir;
    s32 i;
    u8 *moby;
    u8 *vars;
    float angle;

    if (g_limited_blast_count == -1.0f) {
        for (i = 0; i < 5; i++) {
            g_blast_slot_used[i] = 0;
        }
        g_limited_blast_count = 0.0f;
    }
    if (g_limited_blast_count >= 5.0f) {
        return 0;
    }
    for (i = 0; i < 5; i++) {
        if (g_blast_slot_used[i] == 0) {
            break;
        }
    }
    g_limited_blast_count += 1.0f;
    g_blast_slot_used[i] = 1;
    moby = CreateMoby(0x1193);
    if (moby != 0) {
        vars = *(u8 **)(moby + 0x68);
        moby[0x30] = 0xFF;
        *(s16 *)(moby + 0x32) = 0xFF;
        moby[0x20] = 0;
        *(s32 *)(vars + 0x3C) = i;
        qcopy(moby + 0x10, pos);
        *(float *)(moby + 0x1C) = 1.0f;
        qcopy(moby + 0xC0, parent + 0xC0);
        qcopy(moby + 0xD0, parent + 0xD0);
        qcopy(moby + 0xE0, parent + 0xE0);
        *(float *)(moby + 0xCC) = *(float *)(moby + 0xDC) = *(float *)(moby + 0xEC) = 0.0f;
        *(s32 *)(vars + 0x20) = vars_20;
        *(s32 *)(vars + 0x24) = vars_24;
        *(s32 *)(vars + 0x28) = vars_28;
        *(s32 *)(vars + 0x2C) = vars_2c;
        *(float *)(vars + 0x14) = scale;
        *(s32 *)(vars + 0x30) = vars_30;
        *(s32 *)(vars + 0x34) = vars_34;
        *(s32 *)(vars + 0x48) = vars_48;
        *(s16 *)vars = 0x32;
        *(s16 *)(vars + 2) = 0x32;
        *(float *)(vars + 8) = scale + scale;
        *(float *)(vars + 0xC) = scale * 4.0f;
        *(s32 *)(vars + 0x1C) = vars_1c;
        *(s32 *)(vars + 0x38) = vars_38;
        *(s32 *)(vars + 0x18) = vars_18;
        *(float *)(vars + 0x44) = math_random_signed_float_range(65.0f, 80.0f);
        qcopy(&sphere, moby + 0x10);
        ((float *)&sphere)[3] = scale * 3.0f;
        if (math_fast_helper_a(&sphere, 128.0f) == 1) {
            *(s16 *)(vars + 4) = 0x15;
            *(float *)(vars + 0x10) = 0.04761905f;
            if (fast_vec_dist(pos, g_hero_l05_state + 0x140) < 48.0f && flag != 0) {
                u8 *ref = g_hero_l05_state;
                *(s32 *)(ref + 0x16C) = 0;
                *(s32 *)(ref + 0x168) = 0x21;
                *(float *)(ref + 0x160) = 0.075f;
            }
            if (*(s32 *)(vars + 0x18) != 0) {
                FastVecSub(&dir, moby + 0x10, g_hero_l05_state + 0x140);
                vec_scale_to_length(&dir, &dir, 1.0f);
                angle = math_fast_angle_helper(FastVecDot(&dir, g_hero_l05_state + 0x370));
                if (1.5707964f - angle < 0.45378566f) {
                    *(s32 *)(vars + 0x18) = 1;
                } else {
                    *(s32 *)(vars + 0x18) = 0;
                }
            }
        } else {
            *(s16 *)(vars + 4) = 0;
            *(s32 *)(vars + 0x18) = 0;
        }
        part_spawn_fire_explosion_pal(moby);
    }
    return moby;
}

extern int g_glow_ring_draw_target_moby __attribute__((sda));
extern int g_current_map_index;
extern float vec_spring_to_target(void *, void *, void *, float, float, float);
extern float FastAddRotations(float, float);
extern void slot_add_value_clamped(int, int);
extern void func_PAL_0029D5E8(int, int, int);
extern int snd_play_from_class_bank(int, int, char *, int);
extern void moby_mark_spawned(void *);
extern void glow_l05_ring_draw_2_pal(void *);

/* Turns the object towards the global target and clamps its aim cone; a target within
   half a unit takes the fast path, the rest the slow one (an angle step and an update). */
void glow_l05_ring_update_2_pal(char *object)
{
    char *state = *(char **)(object + 0x68);
    float distance;

    if (g_glow_ring_draw_target_moby != 0) {
        char *pos = object + 0x10;
        char *aim;
        float scaled;
        float capped;

        distance = fast_vec_dist((char *)g_glow_ring_draw_target_moby + 0x10, pos);
        if (g_current_map_index == 0x14) {
            vec_spring_to_target(pos, (char *)g_glow_ring_draw_target_moby + 0x10, state + 0x40,
                          0.012800001f, 0.0048f, 1.2800001f);
        } else {
            if (distance < 6e+01f) {
                aim = *(char **)(object + 0x24);
                scaled = *(float *)(aim + 0x24) * 0.022222222f * distance;
                *(float *)(object + 0x2C) = scaled;
                capped = *(float *)(aim + 0x24) * 0.3f;
                if (capped > scaled)
                    *(float *)(object + 0x2C) = capped;
                vec_spring_to_target(pos, (char *)g_glow_ring_draw_target_moby + 0x10, state + 0x40,
                              0.008f, 0.0024f, 0.6f);
            }
        }
        if (distance < 0.5f) {
            slot_add_value_clamped(4, 1);
            func_PAL_0029D5E8(0x1285, 1, -1);
            snd_play_from_class_bank(0xC, 0, object, 0xFBF);
            moby_mark_spawned(object);
            return;
        }
    }
    *(float *)(object + 0xF8) = FastAddRotations(*(float *)(object + 0xF8), 0.04f);
    glow_l05_ring_draw_2_pal(object);
}
