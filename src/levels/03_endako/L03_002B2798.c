#include "include_asm.h"
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

extern unsigned char D_L03_001BFDD0[];
#define HIT ((CollisionView *)D_L03_001BFDD0)

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

extern PlayerView D_00189E20;
#define PLAYER (&D_00189E20)
extern int D_L03_001A8FF0 __attribute__((sda));

extern void func_00282C88(void *);
extern void func_L00_002D49F0(void);
extern float func_00282DB0(void *, void *);
extern void func_00283098(void *, void *, void *);
extern void func_L00_002D38A0(Quad *, Quad *, float);
extern void func_L00_002D36E0(float *, int, float, float, float);
extern void func_00282CC0(void *, void *, void *);
extern int func_00277258(float, void *, int, void *);
extern int func_L00_002E0200(float, void *, int, void *, float);
extern int func_00278870(void *, float);
extern void func_00282CF0(void *, void *, void *);
extern float func_00282DF0(void *);
extern void func_00282F20(void *, void *, float);



/* Pushes the hero out of walls and objects it overlaps, and returns -1 if it was moved a long way. */
int func_L03_002BAEA0(int mode)
{
    Vec previous;
    Vec offset, displacement;
    float extent;
    int facingUp, iteration, hit;

    if (PLAYER->collision_off_frames) return 1;
    qcopy(&previous, &PLAYER->position);
    ClearVector128(&offset);
    if (PLAYER->path_constrain_pending) {
        CheckHeroTimedCondition();
        PLAYER->path_constrain_pending = 0;
    }
    facingUp = 0;
    if (FastVecDot(&PLAYER->basis, &PLAYER->up) > -0.92f) facingUp = 1;
    switch (PLAYER->control_mode) {
    case 17:
        break;
    case 15:
        ClearVector128(&offset);
        offset.z = 0.8f;
        matrix_mul_vec3(&offset, &offset, PLAYER->moby + 0xc0);
        break;
    default:
        if (PLAYER->gravity_mode || PLAYER->timer || facingUp) {
            if (PLAYER->state == 2) {
                OffsetPointInViewSpace((Quad *)&offset, (Quad *)&offset, 5.0f);
            } else if (PLAYER->gravity_mode == 1 || PLAYER->timer) {
                BuildHeroRelativePoint(&offset.x, 0, 0.0f, 0.0f, 0.6f);
            } else if (D_L03_001A8FF0) {
                OffsetPointInViewSpace((Quad *)&offset, (Quad *)&offset, 0.77f);
            } else {
                BuildHeroRelativePoint(&offset.x, 0, 0.0f, 0.0f, PLAYER->capsule_bottom);
            }
        } else {
            offset.z = PLAYER->capsule_bottom;
        }
        break;
    }
    FastVecAdd(&PLAYER->position, &PLAYER->position, &offset);
    for (iteration = 0; iteration < 8; ++iteration) {
        if (PLAYER->control_mode == 15) {
            if (!TestPointAgainstCollision(0.45f, &PLAYER->position, 0xd24, PLAYER->moby)) break;
        } else {
            PlayerView *player = PLAYER;
            if (player->gravity_mode || facingUp) {
                hit = TestPointAgainstCollision(player->capsule_radius, &player->position, 0xd24, player->moby);
                if (!player->locked)
                    hit |= ProcessCollisionTriangles(&player->position, player->capsule_radius);
                if (!hit) break;
            } else {
                extent = player->capsule_top - player->capsule_bottom;
                if (extent < 0.05f) extent = 0.05f;
                hit = func_L00_002E0200(player->capsule_radius, &player->position, 0xd24,
                                        player->moby, extent);
                if (!player->locked)
                    hit |= ProcessCollisionTriangles(&player->position, player->capsule_radius);
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
