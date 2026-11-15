/* func_PAL_L00_0041F868, the PAL copy of func_L00_0041A5C0: the same C, where rename func_002BE278 becomes func_PAL_002BEF58; rename func_0032D758 becomes func_PAL_0032F0B8. */
#include "common.h"

/* func_PAL_L00_0041F868 reads its entry table through $gp, hence -G8. */

typedef unsigned int Q __attribute__((mode(TI)));
typedef union { Q q; float f[4]; } V;
typedef struct { V pos, vel, accel; int next, active, handle, pad; } Entry;
typedef struct {
    char pad[0x18];
    char *target;
    int count;
    V point;
    char gap[0x10];
    V normal;
} Collision;
typedef struct { char pad[0x70]; float direct, splash; char rest[0x68]; } ClassEntry;

extern Entry *g_lava_gun_ring_entries __attribute__((sda));
extern Collision g_collision_result;
extern char g_area_hit_targets[];
extern unsigned char g_item_slot_to_record[];
extern char g_hero_state[];
extern ClassEntry g_weapon_l00_table[] NOT_SDA;

extern void vec_transform_or_copy(void *, void *);
extern void part_steer_effect_direction(int, void *, void *);
extern void FastVecAdd(void *, void *, void *);
extern void vec_clear_128(void *);
extern void vec_scale_to_length(void *, void *, float);
extern void table_clear_entry_flag(int);
extern void euler_to_matrix(void *, void *);
extern void transform_vector(void *, void *, void *);
extern void func_PAL_002BEF58(void *, void *, int, float);
extern void FastVecSub(void *, void *, void *);
extern void make_hit_descriptor(void *, void *, int, void *, float);
extern void QueueMobyImpact(void *, void *);
extern void func_PAL_0032F0B8(void *, int, void *);
extern void PlayMobySound(int, int, void *);
extern void vec_add_object_direction_scaled(void *, void *, float);
extern void SpawnRandomTaperedQuadPair(void *, void *, void *, void *);
extern void part_spawn_debris_piece(void *, void *, void *);
extern int CollLine(void *, void *, int, void *, int);
extern int coll_process_hit(void *, int, void *, int, float);
extern int func_001163B0(void);
extern float math_random_float_range(float, float);

void func_PAL_L00_0041F868(char *object)
{
    V next, temp, small, angles, rot[4], direction;
    struct {
        V direction;
        char pad[8];
        unsigned char type, flag;
        unsigned short id;
        int pad2, enabled;
        char tail[12];
    } hit;
    char *state = *(char **)(object + 0x68);
    int i, index = *(int *)(state + 0x48);
    char *resident;
    Entry *e;
    char *target;
    int n, j, nextIndex;
    ClassEntry *c;

    for (i = 0; i < *(int *)(state + 0x44); i++) {
        resident = g_hero_state;
        e = g_lava_gun_ring_entries + index;
        if (i)
            vec_transform_or_copy(e, e);
        if (e->handle >= 0)
            part_steer_effect_direction(e->handle, &e->vel, e);
        FastVecAdd(&next, e, &e->vel);
        if (!e->active) {
            if (CollLine(e, &next, 0x10, object, 0)) {
                qcopy(e, &g_collision_result.point);
                vec_clear_128(&e->vel);
                vec_scale_to_length(&temp, &g_collision_result.normal, 0.1f);
                FastVecAdd(e, e, &temp);
                e->active = 1;
                table_clear_entry_flag(e->handle);
                e->handle = -1;
                qcopy_nc(&e->accel, &temp);
                vec_scale_to_length(&small, &temp, 0.01f);
                angles.f[0] = math_random_float_range(-0.7853981853f, 0.7853981853f);
                angles.f[1] = math_random_float_range(-0.7853981853f, 0.7853981853f);
                angles.f[2] = math_random_float_range(-0.7853981853f, 0.7853981853f);
                euler_to_matrix(rot, &angles);
                rot[3].f[0] = 0;
                rot[3].f[1] = 0;
                rot[3].f[2] = 0;
                transform_vector(&small, &small, rot);
                func_PAL_002BEF58(e, &small, 0, -1);
                vec_clear_128(&angles);
                target = g_collision_result.target;
                if (target && target != *(char **)(resident + 0x2290)
                    && ((*(unsigned short *)(target + 0x34) & 0x1000)
                        || *(short *)(*(char **)(target + 0x24) + 0x46) == 5)) {
                    nextIndex = index - 1;
                    FastVecSub(&direction, target + 0x10, object + 0x10);
                    vec_scale_to_length(&direction, &direction, 1);
                    vec_scale_to_length(&hit, &hit, 1);
                    c = &g_weapon_l00_table[g_item_slot_to_record[0x1d]];
                    make_hit_descriptor(&hit, object, 0x910000, &direction, c->direct);
                    hit.direction.q = direction.q;
                    hit.direction.f[3] = 5627.9248046875f;
                    hit.type = 9;
                    hit.enabled = 1;
                    hit.flag = 1;
                    hit.id = *(unsigned short *)(g_collision_result.target + 0xaa);
                    QueueMobyImpact(g_collision_result.target, &hit);
                    func_PAL_0032F0B8(g_collision_result.target, 0x1d, object);
                    PlayMobySound(1, 0, object);
                    n = coll_process_hit(g_collision_result.target + 0x10, 0x10, object, 0, 1.5f);
                    for (j = 0; j < n; j++) {
                        target = ((char **)g_area_hit_targets)[j];
                        if (target == *(char **)(resident + 0x2290))
                            continue;
                        FastVecSub(&direction, target + 0x10, object + 0x10);
                        vec_scale_to_length(&direction, &direction, 1);
                        vec_scale_to_length(&hit, &hit, 1);
                        c = &g_weapon_l00_table[g_item_slot_to_record[0x1d]];
                        make_hit_descriptor(&hit, object, 0x910000, &direction, c->splash);
                        hit.direction.q = direction.q;
                        hit.direction.f[3] = 5627.9248046875f;
                        hit.type = 9;
                        hit.enabled = 1;
                        hit.flag = 1;
                        hit.id = *(unsigned short *)(((char **)g_area_hit_targets)[j] + 0xaa);
                        QueueMobyImpact(((char **)g_area_hit_targets)[j], &hit);
                        func_PAL_0032F0B8(((char **)g_area_hit_targets)[j], 0x1d, object);
                        PlayMobySound(1, 0, object);
                        /* The block must not end in the call: flow would pad it with a
                         * (use 0) insn, which lengthens the inner pointers' live ranges
                         * and hands `object` the wrong saved register. */
                        target = 0;
                    }
                } else {
                    nextIndex = index - 1;
                    if (func_001163B0() % 11 == 0)
                        SpawnRandomTaperedQuadPair(object, &g_collision_result.point, &temp, &angles);
                }
            } else {
                vec_add_object_direction_scaled(e, &e->vel, 0.006f);
                nextIndex = index - 1;
            }
        } else {
            nextIndex = index - 1;
        }
        FastVecAdd(e, e, &e->vel);
        index = nextIndex;
        if (nextIndex < 0)
            index = 0x22;
        if (func_001163B0() % 7 == 0) {
            vec_scale_to_length(&temp, &e->vel, 0.05f);
            part_spawn_debris_piece(object, e, &e->vel);
        }
        if (func_001163B0() % 22 == 0) {
            vec_scale_to_length(&temp, &e->vel, 0.05f);
            func_PAL_002BEF58(e, &temp, 0, -1);
        }
    }
}
