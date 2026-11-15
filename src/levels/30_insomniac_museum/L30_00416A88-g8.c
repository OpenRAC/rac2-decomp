#include "common.h"
extern float D_L30_001B1F04 __attribute__((sda));
extern char *D_L30_001C0218 NOT_SDA;
extern int coll_sweep_from_object(void *, float, void *, float, int, float, int, int, int);
extern void moby_set_state(void *, int, int);
extern void FastVecAdd(void *, void *, void *);
extern void make_hit_descriptor(void *, void *, int, float, void *);
extern int CollLine(void *, void *, int, void *, void *);
extern int coll_test_point(void *, int, void *, float);
extern void FastVecScale(void *, void *, float);
extern int coll_process_hit(void *, float, int, void *, void *);
extern void vec_clear_128(void *);
extern void part_create_flash(void *, int, int, int, int, int, int, int, int, float, int);
extern void moby_mark_spawned(void *);
extern void math_apply_axis_rotation_to_quat(void *, void *, void *, float);
extern void gfx_queue_draw_callback(void *, void *);
extern void func_L30_00416FB0(void);
typedef unsigned int Quad __attribute__((mode(TI)));
typedef union { Quad q; float f[4]; } Vec;
/* Moves the museum projectile each frame, explodes it on a hit or after 4 seconds, and spins its model. */
void UpdateMuseumProjectile(char *moby) {
    float pos[4];
    struct Packet { Vec v; void *owner; int mode; unsigned char kind, active; unsigned short id; float distance; int enabled; } packet;
    Vec velocity;
    struct Packet query;
    char *vars = *(char **)(moby + 0x68);
    if (!*(unsigned char *)(moby + 0xBC)) {
        if (++*(int *)(vars + 0x24) > 240) {
            if (!*(unsigned char *)(moby + 0xBC)) {
                coll_sweep_from_object(moby, 0.6f, moby + 0x10, *(float *)(vars + 0x14), 0x10003, 0.0f, 0, 1, 0);
                moby_set_state(moby, 1, -1);
            }
        }
        switch (*(unsigned char *)(moby + 0x20)) {
        case 0: {
            FastVecAdd(pos, moby + 0x10, vars);
            make_hit_descriptor(&packet, moby, 3, *(float *)(vars + 0x14), vars);
            packet.id = *(unsigned short *)(moby + 0xAA);
            if (CollLine(moby + 0x10, pos, 0, moby, &packet) || coll_test_point(moby + 0x10, 0, moby, 0.3f)) {
                /* Two full copies of the response: cross-jumping merges their tails after reload,
                   and each copy's velocity pointer stays local to its block, in $s0. */
                if (D_L30_001C0218) {
                    if (D_L30_001C0218 == *(char **)(vars + 0x10)) goto move; /* An owner hit continues normal movement. */
                    qcopy(&velocity, vars);
                    FastVecScale(&velocity, &velocity, 1.5f);
                    velocity.f[2] = 1.0f;
                    velocity.f[3] = 5627.9248046875f;
                    make_hit_descriptor(&query, moby, 0x10003, *(float *)(vars + 0x14), &velocity);
                    query.active = 1;
                    query.id = *(unsigned short *)(moby + 0xAA);
                    query.kind = 0;
                    coll_process_hit(moby + 0x10, 0.6f, 0, moby, &query);
                    if (!*(unsigned char *)(moby + 0xBC)) moby_set_state(moby, 1, -1);
                    return;
                }
                qcopy(&velocity, vars);
                FastVecScale(&velocity, &velocity, 3.0f);
                velocity.f[2] = 1.0f;
                velocity.f[3] = 5627.9248046875f;
                make_hit_descriptor(&query, moby, 0x10003, *(float *)(vars + 0x14), &velocity);
                query.active = 1;
                query.id = *(unsigned short *)(moby + 0xAA);
                query.kind = 0;
                coll_process_hit(moby + 0x10, 0.6f, 0, moby, &query);
                if (!*(unsigned char *)(moby + 0xBC)) moby_set_state(moby, 1, -1);
                return;
            }
move:
            if (!*(unsigned char *)(moby + 0xBC)) qcopy(moby + 0x10, pos);
            FastVecScale(&velocity, vars, -0.5f);
            vec_clear_128(&query);
            break;
        }
        case 1:
            part_create_flash(moby + 0x10, 0, 25, 20, 20, 20, 0, 0, 1, 0.25f, 0);
            moby_mark_spawned(moby);
            return;
        }
    }
    math_apply_axis_rotation_to_quat(moby + 0xE0, moby + 0xE0, moby + 0xD0, D_L30_001B1F04 * 0.01745329424738884f);
    math_apply_axis_rotation_to_quat(moby + 0xC0, moby + 0xC0, moby + 0xD0, D_L30_001B1F04 * 0.01745329424738884f);
    gfx_queue_draw_callback(func_L30_00416FB0, moby);
}
