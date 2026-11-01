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

extern unsigned char D_L00_001BF210[];
#define HIT ((CollisionView *)D_L00_001BF210)

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

extern PlayerView D_00189E20_view __asm__("D_00189E20");   /* the player record, as func_L00_002B55F0 reads it */
#define PLAYER (&D_00189E20_view)
extern int D_L16_001A8FF0 __attribute__((sda));

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

extern PlayerInputView D_00189E20;
extern int D_001A79F0 __attribute__((sda));
extern int D_L11_001A9010 __attribute__((sda));
extern u8 D_001A7B0B __attribute__((sda));

/* Same body as func_L11_002C51D0, with this function's own callees. */

int func_L00_002B55F0(int mode)
{
    Vec previous;
    Vec offset, displacement;
    float extent;
    int facingUp, iteration, hit;

    if (PLAYER->collision_off_frames) return 1;
    qcopy(&previous, &PLAYER->position);
    func_00282C88(&offset);
    if (PLAYER->path_constrain_pending) {
        func_L00_002D49F0();
        PLAYER->path_constrain_pending = 0;
    }
    facingUp = 0;
    if (func_00282DB0(&PLAYER->basis, &PLAYER->up) > -0.92f) facingUp = 1;
    switch (PLAYER->control_mode) {
    case 17:
        break;
    case 15:
        func_00282C88(&offset);
        offset.z = 0.8f;
        func_00283098(&offset, &offset, PLAYER->moby + 0xc0);
        break;
    default:
        if (PLAYER->gravity_mode || PLAYER->timer || facingUp) {
            if (PLAYER->state == 2) {
                func_L00_002D38A0((Quad *)&offset, (Quad *)&offset, 5.0f);
            } else if (PLAYER->gravity_mode == 1 || PLAYER->timer) {
                func_L00_002D36E0(&offset.x, 0, 0.0f, 0.0f, 0.6f);
            } else if (D_L16_001A8FF0) {
                func_L00_002D38A0((Quad *)&offset, (Quad *)&offset, 0.77f);
            } else {
                func_L00_002D36E0(&offset.x, 0, 0.0f, 0.0f, PLAYER->capsule_bottom);
            }
        } else {
            offset.z = PLAYER->capsule_bottom;
        }
        break;
    }
    func_00282CC0(&PLAYER->position, &PLAYER->position, &offset);
    for (iteration = 0; iteration < 8; ++iteration) {
        if (PLAYER->control_mode == 17) {
            if (!func_00277258(0.6f, &PLAYER->position, 0x24, PLAYER->moby)) break;
        } else if (PLAYER->control_mode == 15) {
            if (!func_00277258(0.45f, &PLAYER->position, 0x24, PLAYER->moby)) break;
        } else {
            PlayerView *player = PLAYER;
            if (player->gravity_mode || facingUp) {
                hit = func_00277258(player->capsule_radius, &player->position, 0x24, player->moby);
                if (!player->locked)
                    hit |= func_00278870(&player->position, player->capsule_radius);
                if (!hit) break;
            } else {
                extent = player->capsule_top - player->capsule_bottom;
                if (extent < 0.05f) extent = 0.05f;
                hit = func_L00_002E0200(player->capsule_radius, &player->position, 0x24,
                                        player->moby, extent);
                if (!player->locked)
                    hit |= func_00278870(&player->position, player->capsule_radius);
                if (!hit) break;
            }
        }
        qcopy(&PLAYER->position, &HIT->position);
        qcopy(&PLAYER->wall_contact_normal, &HIT->normal);
        qcopy(&PLAYER->wall_contact_point, &HIT->point);
        PLAYER->wall_hit = 1;
        PLAYER->coll_hit_moby = HIT->moby;
    }
    func_00282CF0(&PLAYER->position, &PLAYER->position, &offset);
    func_00282CF0(&displacement, &PLAYER->position, &previous);
    if (func_00282DF0(&displacement) > PLAYER->capsule_radius * 1.5f) {
        if (mode == 15) {
            if (displacement.x > 512.0f) displacement.x = 512.0f;
            else if (displacement.x < -512.0f) displacement.x = -512.0f;
            if (displacement.y > 512.0f) displacement.y = 512.0f;
            else if (displacement.y < -512.0f) displacement.y = -512.0f;
            if (displacement.z > 512.0f) displacement.z = 512.0f;
            else if (displacement.z < -512.0f) displacement.z = -512.0f;
            func_00282F20(&displacement, &displacement, PLAYER->capsule_radius);
            func_00282CC0(&PLAYER->position, &previous, &displacement);
        }
        return -1;
    }
    return 1;
}

