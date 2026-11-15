#include "include_asm.h"


#include "common.h"
typedef int Quad __attribute__((mode(TI)));
typedef struct { float x, y, z, w; } Vec __attribute__((aligned(16)));
typedef struct {
    unsigned char pad_0[0x8];
    void *moby;
    unsigned char pad_c[0x4];
    Quad point;
    Quad position;
    Quad normal;
} CollisionView;
extern unsigned char D_L16_001BFF50[];
#define HIT ((CollisionView *)D_L16_001BFF50)
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
extern PlayerView D_00189E20_view __asm__("D_00189E20");
#define PLAYER (&D_00189E20_view)
extern int D_L16_001A8FF0 __attribute__((sda));
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

int func_PAL_L16_002B5848(int mode)
{
    Vec previous;
    Vec offset, displacement;
    float extent;
    int facingUp, iteration, hit;

    if (PLAYER->collision_off_frames) return 1;
    qcopy(&previous, &PLAYER->position);
    vec_clear_128(&offset);
    if (PLAYER->path_constrain_pending) {
        hero_check_timed_condition();
        PLAYER->path_constrain_pending = 0;
    }
    facingUp = 0;
    if (FastVecDot(&PLAYER->basis, &PLAYER->up) > -0.92f) facingUp = 1;
    switch (PLAYER->control_mode) {
    case 17:
        break;
    case 15:
        vec_clear_128(&offset);
        offset.z = 0.8f;
        matrix_mul_vec3(&offset, &offset, PLAYER->moby + 0xc0);
        break;
    default:
        if (PLAYER->gravity_mode || PLAYER->timer || facingUp) {
            if (PLAYER->state == 2) {
                cam_offset_point_in_view_space((Quad *)&offset, (Quad *)&offset, 5.0f);
            } else if (PLAYER->gravity_mode == 1 || PLAYER->timer) {
                hero_build_relative_point(&offset.x, 0, 0.0f, 0.0f, 0.6f);
            } else if (D_L16_001A8FF0) {
                cam_offset_point_in_view_space((Quad *)&offset, (Quad *)&offset, 0.77f);
            } else {
                hero_build_relative_point(&offset.x, 0, 0.0f, 0.0f, PLAYER->capsule_bottom);
            }
        } else {
            offset.z = PLAYER->capsule_bottom;
        }
        break;
    }
    FastVecAdd(&PLAYER->position, &PLAYER->position, &offset);
    for (iteration = 0; iteration < 8; ++iteration) {
        if (PLAYER->control_mode == 15) {
            if (!coll_test_point(0.54f, &PLAYER->position, 0x324, PLAYER->moby)) break;
        } else {
            PlayerView *player = PLAYER;
            if (player->gravity_mode || facingUp) {
                hit = coll_test_point(player->capsule_radius, &player->position, 0x324, player->moby);
                if (!player->locked)
                    hit |= coll_process_triangles(&player->position, player->capsule_radius);
                if (!hit) break;
            } else {
                extent = player->capsule_top - player->capsule_bottom;
                if (extent < 0.05f) extent = 0.05f;
                hit = func_L00_002E0200(player->capsule_radius, &player->position, 0x324,
                                        player->moby, extent);
                if (!player->locked)
                    hit |= coll_process_triangles(&player->position, player->capsule_radius);
                if (!hit) break;
            }
        }
        qcopy(&PLAYER->position, &HIT->position);
        qcopy(&PLAYER->wall_contact_normal, &HIT->normal);
        qcopy(&PLAYER->wall_contact_point, &HIT->point);
        PLAYER->wall_hit = 1;
        PLAYER->coll_hit_moby = HIT->moby;
    }
    FastVecSub(&PLAYER->position, &PLAYER->position, &offset);
    FastVecSub(&displacement, &PLAYER->position, &previous);
    if (FastVecLength(&displacement) > PLAYER->capsule_radius * 1.5f) {
        if (mode == 15) {
            if (displacement.x > 512.0f) displacement.x = 512.0f;
            else if (displacement.x < -512.0f) displacement.x = -512.0f;
            if (displacement.y > 512.0f) displacement.y = 512.0f;
            else if (displacement.y < -512.0f) displacement.y = -512.0f;
            if (displacement.z > 512.0f) displacement.z = 512.0f;
            else if (displacement.z < -512.0f) displacement.z = -512.0f;
            vec_scale_to_length(&displacement, &displacement, PLAYER->capsule_radius);
            FastVecAdd(&PLAYER->position, &previous, &displacement);
        }
        return -1;
    }
    return 1;
}

