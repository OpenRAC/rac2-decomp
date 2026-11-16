#include "names.h"
/* func_PAL_L05_0041E5C8, the PAL copy of func_L05_00419888: the same C, where rename func_L05_0041A218 becomes func_PAL_L05_0041EF70; rename func_L05_00419F10 becomes func_PAL_L05_0041EC50. */
#include "common.h"

extern void FastVecAdd(void *a, void *b, void *c);

extern float fast_vec_dist(void *, void *);

extern int snd_play_from_class_bank(int, int, char *, int);

extern void moby_mark_spawned(void *);

/* Same shape as func_L05_004260B8, on its own data slot and with its own tail. */
/* Turns the object towards the global target and clamps its aim cone; a target within
   half a unit takes the fast path, the rest the slow one (an angle step and an update). */
typedef union { int q __attribute__((mode(TI))); float f[4]; } Vector;
typedef struct {
    float direction[4]; void *attacker; int flags; u8 kind, mode; u16 object_class;
    float damage; int enabled; float field24;
} Impact;
extern void stub_l05_empty_pal(void *);
extern int math_fast_float_d(void *);
extern float vec_distance_xy(void *, void *);
extern void vec_scale_to_length(void *, void *, float);
extern int CollLine(void *, void *, int, void *, void *);
extern int GetCollHitMaterial(void);
extern void func_PAL_L05_0041EC50(void *, int, u32, void *);
extern float coll_project_point_on_segment(void *, void *, void *, void *);
extern void lerp_vector(void *, void *, void *, float);
extern void FastVecSub(void *, void *, void *);
extern float FastVecLength(void *);
extern int coll_process_hit(void *, int, void *, void *, float);
extern void QueueMobyImpact(void *, Impact *);
extern void light_spot_add_nearby_object(void *);
extern void gfx_add_draw_callback_third(void *, void *);
extern void gfx_draw_energy_blast(void *);
extern char g_projectile_target_pos[], g_hero_l05_state[];
extern u8 *g_nearby_l05_mobys[];
extern float g_equipment_trigger_radius __attribute__((sda));

void func_PAL_L05_0041E5C8(u8 *actor)
{
    Vector previous;
    Impact impact __attribute__((aligned(16)));
    Vector point, delta, closest;
    u8 *state = *(u8 **)(actor + 0x68);
    int count, i;

    qcopy(&previous, actor + 0x10);
    stub_l05_empty_pal(actor);
    FastVecAdd(actor + 0x10, actor + 0x10, state + 0x10);
    if (math_fast_float_d(state) != 0) {
        moby_mark_spawned(actor);
        return;
    }
    if (*(float *)(actor + 0x10) < 2.0f || *(float *)(actor + 0x10) > 1021.0f ||
        *(float *)(actor + 0x14) < 2.0f || *(float *)(actor + 0x14) > 1021.0f ||
        *(float *)(actor + 0x18) < 2.0f || *(float *)(actor + 0x18) > 1021.0f) {
        if (*(int *)(state + 0x38) == 0) {
            moby_mark_spawned(actor);
            return;
        }
    }
    if (*(int *)(state + 0x38) != 0) {
        if (vec_distance_xy(actor + 0x10, g_hero_l05_state + 0x140) < 2.0f) {
            moby_mark_spawned(actor);
            return;
        }
    }
    if (*(int *)(state + 0x38) != 0)
        goto finish;
    impact.attacker = actor;
    impact.flags = 0x110000;
    if (*(int *)(state + 0x30) != 0)
        impact.damage = 3.0f;
    else
        impact.damage = 1.0f;
    impact.enabled = 1;
    qcopy(impact.direction, state + 0x10);
    vec_scale_to_length(impact.direction, impact.direction, 1.0f);
    impact.kind = 1;
    impact.mode = 1;
    impact.direction[3] = 5627.9248046875f;
    impact.object_class = *(u16 *)(actor + 0xAA);
    /* The last Impact word is read by the receiver but not initialized by retail. */
    *(float *)(state + 0x3C) += *(float *)(state + 0x40);
    if (CollLine(&previous, actor + 0x10, 0, *(void **)(state + 4), &impact) != 0 &&
        GetCollHitMaterial() != 6) {
        snd_play_from_class_bank(7, 0, (char *)actor, 0xFBF);
        func_PAL_L05_0041EC50(g_projectile_target_pos, 20, *(u32 *)(state + 0x24), actor);
        moby_mark_spawned(actor);
        return;
    }
    if (*(s16 *)(*(u8 **)(state + 4) + 0xAA) != 0xFBF) {
        coll_project_point_on_segment(&point, &previous, actor + 0x10, g_hero_l05_state + 0x140);
        if (fast_vec_dist(&point, g_hero_l05_state + 0x140) < g_equipment_trigger_radius) {
            snd_play_from_class_bank(7, 0, (char *)actor, 0xFBF);
            {
                char *camera = g_hero_l05_state;
                *(int *)(camera + 0x16C) = 0;
                *(int *)(camera + 0x168) = 25;
                *(float *)(camera + 0x160) = 0.05f;
            }
            func_PAL_L05_0041EC50(&point, 20, *(u32 *)(state + 0x24), actor);
            moby_mark_spawned(actor);
            return;
        }
        goto finish;
destroy:
        moby_mark_spawned(actor);
        return;
    }
    lerp_vector(&point, &previous, actor + 0x10, 0.5f);
    FastVecSub(&delta, actor + 0x10, &previous);
    count = coll_process_hit(&point, 1, *(void **)(state + 4), 0, FastVecLength(&delta));
    if (count != 0) {
        for (i = 0; i < count; i++) {
            coll_project_point_on_segment(&closest, &previous, actor + 0x10, g_nearby_l05_mobys[i] + 0x10);
            FastVecSub(&delta, g_nearby_l05_mobys[i] + 0x10, &closest);
            if (FastVecLength(&delta) < *(float *)(state + 0x3C)) {
                snd_play_from_class_bank(7, 0, (char *)actor, 0xFBF);
                func_PAL_L05_0041EC50(&closest, 20, *(u32 *)(state + 0x24), actor);
                QueueMobyImpact(g_nearby_l05_mobys[i], &impact);
                goto destroy;
            }
        }
    }
finish:
    light_spot_add_nearby_object(actor);
    gfx_add_draw_callback_third(gfx_draw_energy_blast, actor);
}

/* End of a shot's flight: the optional burst, then the object is removed. */

/* Per-frame update of a shot: moves it, removes it when it leaves the 2..1021 world box or expires
 * (with a last collision test), and otherwise tests for a hit and leaves a three-step trail.
 * The end-of-flight code is expanded once per exit and jump2 cross-jumps the copies. The two
 * collision.point loads merge through their shared REG_EQUIV constant, which leaves a dead lui
 * before the impact code, so one shared label does not reproduce it.
 */
