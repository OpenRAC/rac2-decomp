#include "include_asm.h"

#include "common.h"
typedef struct { int a, b, c, d; } __attribute__((aligned(16))) Quad16;
typedef struct {
    Quad16 vector;
    int owner, flags;
    unsigned char enabled, kind;
    unsigned short id;
    float distance;
    int active;
} CollisionRequest;
typedef struct { Quad16 next; CollisionRequest move; Quad16 direction; CollisionRequest area; } ProjectileWorkspace;
extern int coll_sweep_from_object(void *, float, float *, int, float, float, int, int, int);
extern void moby_set_state(void *, int, int);
extern void FastVecAdd(void *, void *, void *);
extern void make_hit_descriptor(char *, int, int, float, Quad16 *);
extern int CollLine(void *, void *, int, void *, void *);
extern int coll_test_point(void *, int, void *, float);
extern void FastVecScale(void *, void *, float);
extern int coll_process_hit(void *, int, void *, void *, float);
extern void vec_clear_128(void *);
extern char *SpawnExplosion_pal(void *, int, int, int, int, int, int, int, int, int, int, int, float, float);
extern void moby_mark_spawned(void *);
extern void math_apply_axis_rotation_to_quat(void *, void *, void *, float);
extern void gfx_add_draw_callback_third(void (*)(void *), void *);
extern void part_spawn_two_flare_effects(void *);
extern char g_hit_l12_result[];
extern float g_spin_rotation_degrees __attribute__((sda));

void UpdateSpinningBlastProjectile_pal(char *object)
{
    ProjectileWorkspace local;
    char *state = *(char **)(object + 0x68);
    if (!*(unsigned char *)(object + 0xBC)) {
        (*(int *)(state + 0x24))++;
        if (*(int *)(state + 0x24) > 240 && !*(unsigned char *)(object + 0xBC)) {
            coll_sweep_from_object(object, 0.6f, (float *)(object + 0x10), 0x10003, *(float *)(state + 0x14), 0.0f, 0, 1, 0);
            moby_set_state(object, 1, -1);
        }
        switch (*(unsigned char *)(object + 0x20)) {
        case 0:
            FastVecAdd(&local.next, object + 0x10, state);
            make_hit_descriptor((char *)&local.move, (int)object, 3, *(float *)(state + 0x14), (Quad16 *)state);
            local.move.id = *(unsigned short *)(object + 0xAA);
            if (CollLine(object + 0x10, &local.next, 0, object, &local.move) != 0 || coll_test_point(object + 0x10, 0, object, 0.3f) != 0) {
                if (*(char **)g_hit_l12_result != 0) {
                    if (*(char **)g_hit_l12_result != *(char **)(state + 0x10)) {
                        qcopy(&local.direction, state);
                        FastVecScale(&local.direction, &local.direction, 1.5f);
                        ((float *)&local.direction)[2] = 1.0f;
                        ((float *)&local.direction)[3] = 5627.9248f;
                        make_hit_descriptor((char *)&local.area, (int)object, 0x10003, *(float *)(state + 0x14), &local.direction);
                        local.area.kind = 1;
                        local.area.id = *(unsigned short *)(object + 0xAA);
                        local.area.enabled = 0;
                        coll_process_hit(object + 0x10, 0, object, &local.area, 0.6f);
                        if (!*(unsigned char *)(object + 0xBC))
                            moby_set_state(object, 1, -1);
                        return;
                    }
                } else {
                    qcopy(&local.direction, state);
                    FastVecScale(&local.direction, &local.direction, 3.0f);
                    ((float *)&local.direction)[2] = 1.0f;
                    ((float *)&local.direction)[3] = 5627.9248f;
                    make_hit_descriptor((char *)&local.area, (int)object, 0x10003, *(float *)(state + 0x14), &local.direction);
                    local.area.kind = 1;
                    local.area.id = *(unsigned short *)(object + 0xAA);
                    local.area.enabled = 0;
                    coll_process_hit(object + 0x10, 0, object, &local.area, 0.6f);
                    if (!*(unsigned char *)(object + 0xBC))
                        moby_set_state(object, 1, -1);
                    return;
                }
            }
            if (!*(unsigned char *)(object + 0xBC))
                qcopy(object + 0x10, &local.next);
            FastVecScale(&local.direction, state, -0.5f);
            vec_clear_128(&local.area);
            break;
        case 1:
            SpawnExplosion_pal(object + 0x10, 0, 25, 20, 20, 20, 0, 0, 1, 0, 0, 0, 0.25f, 20.0f);
            moby_mark_spawned(object);
            return;
        }
    }
    math_apply_axis_rotation_to_quat(object + 0xE0, object + 0xE0, object + 0xD0, g_spin_rotation_degrees * 0.017453294f);
    math_apply_axis_rotation_to_quat(object + 0xC0, object + 0xC0, object + 0xD0, g_spin_rotation_degrees * 0.017453294f);
    gfx_add_draw_callback_third(part_spawn_two_flare_effects, object);
}
