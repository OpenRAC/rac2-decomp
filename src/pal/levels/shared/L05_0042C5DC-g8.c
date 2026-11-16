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
extern char *func_PAL_002BE9A8(void *, float, float, float, float, int, void *, u32, int);
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
void func_PAL_L05_0042D118(char *object, char *state, float *pos)
{
    ImpactParams p;
    ImpactVector origin, direction;
    int i;
    int spin;
    float a, b;
    float count, speed, spread;
    char *particle, *data;

    p.flags = 0x810000;
    p.owner = object;
    if (*(int *)(state + 0x24))
        p.scale = g_impact_spark_scale_b;
    else
        p.scale = g_impact_spark_scale_a;
    p.one = 1;
    qcopy(&p.pos, state);
    vec_scale_to_length(&p, &p, 1.0f);
    p.pos.f[3] = 5627.925f;
    p.type = 3;
    p.subtype = 2;
    p.id = *(unsigned short *)(object + 0xAA);
    coll_process_hit(pos, *(int *)(state + 0x24) ? g_projectile_hit_radius_alt : g_projectile_hit_radius_normal,
                  1, *(char **)(state + 0x20), &p);
    if (g_hit_l05_result && *(short *)(g_hit_l05_result + 0xAA) == 0x956) {
        count = 20.0f;
        speed = 3.0f;
        spread = 2.0f;
        qcopy(&origin, object + 0x10);
        for (i = 0; (float)i < count; i++) {
            pos[0] = origin.f[0] + math_random_signed_float_range(0.0f, spread);
            pos[1] = origin.f[1] + math_random_signed_float_range(0.0f, spread);
            pos[2] = origin.f[2] + math_random_signed_float_range(0.0f, spread);
            a = math_random_angle();
            b = math_random_angle();
            vec_build_spherical_offset(&direction, 0.060000002f, a, b);
            spin = math_random_int_range(-3, 3);
            particle = func_PAL_002BE9A8(pos, 0.0f, 1.0f, 1.0f, speed * 210000.0f, spin,
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
extern void func_PAL_L05_0042E518(void *);

/* spawns object 0x1193 at pos with parent's orientation, when one of the five slots is free:
   fills its vars from the arguments and, if it is in view, grades it against the reference
   point at D_L05_001B9580 + 0x140 */
void *part_spawn_limited_blast_pal(u8 *pos, u8 *parent, s32 flag, float scale, s32 a3, s32 a4, s32 a5,
                        s32 a6, s32 a7, s32 a8, s32 a9, s32 a10, s32 a11, s32 a12) {
    TI128 sphere;
    TI128 dir;
    s32 i;
    u8 *obj;
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
    obj = CreateMoby(0x1193);
    if (obj != 0) {
        vars = *(u8 **)(obj + 0x68);
        obj[0x30] = 0xFF;
        *(s16 *)(obj + 0x32) = 0xFF;
        obj[0x20] = 0;
        *(s32 *)(vars + 0x3C) = i;
        qcopy(obj + 0x10, pos);
        *(float *)(obj + 0x1C) = 1.0f;
        qcopy(obj + 0xC0, parent + 0xC0);
        qcopy(obj + 0xD0, parent + 0xD0);
        qcopy(obj + 0xE0, parent + 0xE0);
        *(float *)(obj + 0xCC) = *(float *)(obj + 0xDC) = *(float *)(obj + 0xEC) = 0.0f;
        *(s32 *)(vars + 0x20) = a3;
        *(s32 *)(vars + 0x24) = a4;
        *(s32 *)(vars + 0x28) = a5;
        *(s32 *)(vars + 0x2C) = a6;
        *(float *)(vars + 0x14) = scale;
        *(s32 *)(vars + 0x30) = a7;
        *(s32 *)(vars + 0x34) = a9;
        *(s32 *)(vars + 0x48) = a12;
        *(s16 *)vars = 0x32;
        *(s16 *)(vars + 2) = 0x32;
        *(float *)(vars + 8) = scale + scale;
        *(float *)(vars + 0xC) = scale * 4.0f;
        *(s32 *)(vars + 0x1C) = a10;
        *(s32 *)(vars + 0x38) = a11;
        *(s32 *)(vars + 0x18) = a8;
        *(float *)(vars + 0x44) = math_random_signed_float_range(65.0f, 80.0f);
        qcopy(&sphere, obj + 0x10);
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
                FastVecSub(&dir, obj + 0x10, g_hero_l05_state + 0x140);
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
        func_PAL_L05_0042E518(obj);
    }
    return obj;
}

extern int g_glow_ring_draw_target_moby __attribute__((sda));
extern int g_current_map_index;
extern float vec_spring_to_target(void *, void *, void *, float, float, float);
extern float FastAddRotations(float, float);
extern void slot_add_value_clamped(int, int);
extern void func_PAL_0029D5E8(int, int, int);
extern int snd_play_from_class_bank(int, int, char *, int);
extern void moby_mark_spawned(void *);
extern void func_PAL_L05_0042C880(void *);

/* Turns the object towards the global target and clamps its aim cone; a target within
   half a unit takes the fast path, the rest the slow one (an angle step and an update). */
void func_PAL_L05_0042C5DC(char *object)
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
    func_PAL_L05_0042C880(object);
}
