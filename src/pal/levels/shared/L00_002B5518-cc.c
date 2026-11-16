/* func_PAL_L00_002B5518, the PAL copy of func_L00_002B55F0: the same C. */
#include "common.h"

typedef int Quad __attribute__((mode(TI)));
typedef struct { float x, y, z, w; } Vec __attribute__((aligned(16)));

/* Collision query output; the push-out loop reads position, normal and point. */
typedef struct {
    unsigned char pad_0[0x8];
    void *moby;
    unsigned char pad_c[0x4];
    Quad point;
    Quad position;
    Quad normal;
} CollisionView;

extern unsigned char g_collision_view[];

/* Field names follow RAC1's hero collision step (hero_collision.c). */
typedef struct {
    unsigned char pad_0[0x20];
    Vec basis;
    unsigned char pad_30[0x50];
    Quad position;
    unsigned char pad_90[0x156];
    short locked;
    unsigned char pad_1e8[0x8];
    short collision_off_frames;
    unsigned char pad_1f2[0x26];
    short timer;
    unsigned char pad_21a[0x16];
    Quad wall_contact_normal;
    Quad wall_contact_point;
    float capsule_top;
    float capsule_bottom;
    unsigned char pad_258[0xc];
    float capsule_radius;
    unsigned char pad_268[0x4];
    void *coll_hit_moby;
    unsigned char pad_270[0x17];
    unsigned char wall_hit;
    unsigned char pad_288[0x38];
    Vec up;
    unsigned char pad_2d0[0x1fc0];
    char *moby;
    unsigned char pad_2294[0x8];
    int control_mode;
    unsigned char pad_22a0[0x14];
    unsigned char state;
    unsigned char pad_22b5[0xe];
    unsigned char gravity_mode;
    unsigned char pad_22c4[0x23a];
    short path_constrain_pending;
} PlayerView;

extern PlayerView D_00189E20_view __asm__("D_00189E20");   /* the player record, as func_PAL_L00_002B5518 reads it */
extern int g_hero_l16_block_flag __attribute__((sda));

extern void vec_clear_128(void *);
extern void hero_check_timed_condition(void);
extern float FastVecDot(void *, void *);
extern void matrix_mul_vec3(void *, void *, void *);
extern void cam_offset_point_in_view_space(Quad *, Quad *, float);
extern void hero_build_relative_point(float *, int, float, float, float);
extern void FastVecAdd(void *, void *, void *);
extern int coll_test_point(float, void *, int, void *);
extern int func_L00_002E0200(float, void *, int, void *, float);
extern int coll_process_triangles(void *, float);
extern void FastVecSub(void *, void *, void *);
extern float FastVecLength(void *);
extern void vec_scale_to_length(void *, void *, float);

typedef int Quadword __attribute__((mode(TI)));
typedef union { Quadword word; float f[4]; } Vector;
/* Partial resident view. Field offsets and widths follow the retail accesses. */
typedef struct {
    u8 prefix[0x80];
    Vector position;
    u8 pad90[0xf0 - 0x90];
    Vector velocity, pad100, motion;
    u8 pad120[0x1dc - 0x120];
    short timer, inputLock;
    u8 pad1e0[0x21c - 0x1e0];
    short soundTimer;
    u8 pad21e[0x31c - 0x21e];
    float elapsed;
    u8 pad320[0x334 - 0x320];
    float jumpTime;
    u8 pad338[8];
    int busy;
    u8 pad344[4];
    short pendingJump;
    u8 pad34a[2];
    short jumpCount;
    u8 pad34e[0x49e - 0x34e];
    u8 animationDone;
    u8 pad49f[0x1490 - 0x49f];
    short command;
    u8 pad1492[3];
    u8 attack, jump, jumpPressed, pad1498[2], hover, cancel, pad149c, saved;
    u8 pad149e[0x1500 - 0x149e];
    int interrupted;
    u8 pad1504[0x2290 - 0x1504];
    u8 *object;
    int state, phase, movement;
    u8 pad22a0[0x22b4 - 0x22a0];
    u8 mode;
    u8 pad22b5[0x22b9 - 0x22b5];
    u8 request;
    u8 pad22ba[3];
    u8 disabled;
    u8 pad22be[0x249c - 0x22be];
    u8 *contact;
    u8 pad24a0[0x24cc - 0x24a0];
    int health;
} PlayerInputView;

extern PlayerInputView g_hero_state;
/* Same body as func_L11_002C51D0, with this function's own callees. */

int hero_push_out_of_collisions_pal(int mode)
{
    Vec previous;
    Vec offset, displacement;
    float extent;
    int facingUp, iteration, hit;

    if ((&D_00189E20_view)->collision_off_frames) return 1;
    qcopy(&previous, &(&D_00189E20_view)->position);
    vec_clear_128(&offset);
    if ((&D_00189E20_view)->path_constrain_pending) {
        hero_check_timed_condition();
        (&D_00189E20_view)->path_constrain_pending = 0;
    }
    facingUp = 0;
    if (FastVecDot(&(&D_00189E20_view)->basis, &(&D_00189E20_view)->up) > -0.92f) facingUp = 1;
    switch ((&D_00189E20_view)->control_mode) {
    case 17:
        break;
    case 15:
        vec_clear_128(&offset);
        offset.z = 0.8f;
        matrix_mul_vec3(&offset, &offset, (&D_00189E20_view)->moby + 0xc0);
        break;
    default:
        if ((&D_00189E20_view)->gravity_mode || (&D_00189E20_view)->timer || facingUp) {
            if ((&D_00189E20_view)->state == 2) {
                cam_offset_point_in_view_space((Quad *)&offset, (Quad *)&offset, 5.0f);
            } else if ((&D_00189E20_view)->gravity_mode == 1 || (&D_00189E20_view)->timer) {
                hero_build_relative_point(&offset.x, 0, 0.0f, 0.0f, 0.6f);
            } else if (g_hero_l16_block_flag) {
                cam_offset_point_in_view_space((Quad *)&offset, (Quad *)&offset, 0.77f);
            } else {
                hero_build_relative_point(&offset.x, 0, 0.0f, 0.0f, (&D_00189E20_view)->capsule_bottom);
            }
        } else {
            offset.z = (&D_00189E20_view)->capsule_bottom;
        }
        break;
    }
    FastVecAdd(&(&D_00189E20_view)->position, &(&D_00189E20_view)->position, &offset);
    for (iteration = 0; iteration < 8; ++iteration) {
        if ((&D_00189E20_view)->control_mode == 17) {
            if (!coll_test_point(0.6f, &(&D_00189E20_view)->position, 0x24, (&D_00189E20_view)->moby)) break;
        } else if ((&D_00189E20_view)->control_mode == 15) {
            if (!coll_test_point(0.54f, &(&D_00189E20_view)->position, 0x24, (&D_00189E20_view)->moby)) break;
        } else {
            PlayerView *player = (&D_00189E20_view);
            if (player->gravity_mode || facingUp) {
                hit = coll_test_point(player->capsule_radius, &player->position, 0x24, player->moby);
                if (!player->locked)
                    hit |= coll_process_triangles(&player->position, player->capsule_radius);
                if (!hit) break;
            } else {
                extent = player->capsule_top - player->capsule_bottom;
                if (extent < 0.05f) extent = 0.05f;
                hit = func_L00_002E0200(player->capsule_radius, &player->position, 0x24,
                                        player->moby, extent);
                if (!player->locked)
                    hit |= coll_process_triangles(&player->position, player->capsule_radius);
                if (!hit) break;
            }
        }
        qcopy(&(&D_00189E20_view)->position, &((CollisionView *)g_collision_view)->position);
        qcopy(&(&D_00189E20_view)->wall_contact_normal, &((CollisionView *)g_collision_view)->normal);
        qcopy(&(&D_00189E20_view)->wall_contact_point, &((CollisionView *)g_collision_view)->point);
        (&D_00189E20_view)->wall_hit = 1;
        (&D_00189E20_view)->coll_hit_moby = ((CollisionView *)g_collision_view)->moby;
    }
    FastVecSub(&(&D_00189E20_view)->position, &(&D_00189E20_view)->position, &offset);
    FastVecSub(&displacement, &(&D_00189E20_view)->position, &previous);
    if (FastVecLength(&displacement) > (&D_00189E20_view)->capsule_radius * 1.5f) {
        if (mode == 15) {
            if (displacement.x > 512.0f) displacement.x = 512.0f;
            else if (displacement.x < -512.0f) displacement.x = -512.0f;
            if (displacement.y > 512.0f) displacement.y = 512.0f;
            else if (displacement.y < -512.0f) displacement.y = -512.0f;
            if (displacement.z > 512.0f) displacement.z = 512.0f;
            else if (displacement.z < -512.0f) displacement.z = -512.0f;
            vec_scale_to_length(&displacement, &displacement, (&D_00189E20_view)->capsule_radius);
            FastVecAdd(&(&D_00189E20_view)->position, &previous, &displacement);
        }
        return -1;
    }
    return 1;
}

