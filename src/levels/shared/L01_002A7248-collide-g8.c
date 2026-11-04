#include "common.h"

/* func_L01_002B5EA0 needs -G8 (it reads D_L01_001A9030 through $gp), so it has this unit of its own.
   Its counterpart in RAC1 is Camera_ResolveBlockedView (src/overlays/l02_aridia/hero_movement.c). */

typedef struct {
    char pad0[0x20];
    float axis[4];
    char pad30[0x50];
    float pos[4];
    char pad90[0x156];
    short no_group_test;
    char pad1E8[8];
    short collision_off;
    char pad1F2[0x26];
    short mode;
    char pad21A[0x16];
    float wall_normal[4];
    float wall_point[4];
    float capsule_top;
    float capsule_bottom;
    char pad258[12];
    float capsule_radius;
    char pad268[4];
    int hit_moby;
    char pad270[0x17];
    u8 wall_hit;
    char pad288[0x38];
    float up[4];
    char pad2D0[0x1FC0];
    int moby;
    char pad2294[8];
    int control_mode;
    char pad22A0[0x14];
    u8 state;
    char pad22B5[14];
    u8 gravity_mode;
    char pad22C4[0x23A];
    short constrain_pending;
} CollideHero;

typedef struct {
    char pad0[0x18];
    int moby;
    char pad1C[4];
    float point[4];
    float pos[4];
    float normal[4];
} CollideHit;

extern CollideHero D_00189E20;
extern CollideHit D_L01_001BF900;
extern int D_L01_001A9030 MACRO_ADDR;

extern void func_002E3438(void *);
extern void func_002CA1C0(void);
extern float func_002E3560(void *, void *);
extern void func_002C8E60(void *, int, float, float, float);
extern void func_002C9020(void *, void *, float);
extern void func_002E3470(void *, void *, void *);
extern void func_002E34A0(void *, void *, void *);
extern float func_002E35A0(void *);
extern void func_002E3738(void *, void *, float);
extern int func_002D4CE0(float, void *, int, int);
extern int func_002D59D0(float, float, void *, int, int);
extern int func_002D71E0(float, void *);

/* Moves the hero by this frame's offset and resolves it against the collision up to eight
   times, taking each hit's position, normal and point. Returns 1 when the hero did not move
   much further than its radius, else -1; for mode 0xF the excess is clamped to 512 a side
   and put back along the offset. */
int func_L01_002B5EA0(int arg)
{
    float old[4] __attribute__((aligned(16)));
    float offset[4] __attribute__((aligned(16)));
    float delta[4] __attribute__((aligned(16)));
    int steep, i, hit;

    if (D_00189E20.collision_off)
        return 1;
    qcopy(old, D_00189E20.pos);
    func_002E3438(offset);
    if (D_00189E20.constrain_pending) {
        func_002CA1C0();
        D_00189E20.constrain_pending = 0;
    }
    steep = 0;
    if (func_002E3560(D_00189E20.axis, D_00189E20.up) > -0.92f)
        steep = 1;
    if (D_00189E20.control_mode != 0x11) {
        if (D_00189E20.gravity_mode || D_00189E20.mode || steep) {
            if (D_00189E20.state == 2)
                func_002C9020(offset, offset, 5.0f);
            else if (D_00189E20.gravity_mode == 1 || D_00189E20.mode)
                func_002C8E60(offset, 0, 0.0f, 0.0f, 0.6f);
            else if (D_L01_001A9030)
                func_002C9020(offset, offset, 0.77f);
            else
                func_002C8E60(offset, 0, 0.0f, 0.0f, D_00189E20.capsule_bottom);
        } else {
            offset[2] = D_00189E20.capsule_bottom;
        }
    }
    func_002E3470(D_00189E20.pos, D_00189E20.pos, offset);
    for (i = 0; i < 8; i++) {
        CollideHero *p = &D_00189E20;
        float *pos;

        if (p->gravity_mode || steep) {
            pos = p->pos;
            hit = func_002D4CE0(p->capsule_radius, pos, 0x324, p->moby);
            if (!p->no_group_test)
                hit |= func_002D71E0(p->capsule_radius, pos);
        } else {
            float h = p->capsule_top - p->capsule_bottom;

            if (h < 0.05f)
                h = 0.05f;
            pos = p->pos;
            hit = func_002D59D0(p->capsule_radius, h, pos, 0x324, p->moby);
            if (!p->no_group_test)
                hit |= func_002D71E0(p->capsule_radius, pos);
        }
        if (!hit)
            break;
        qcopy(D_00189E20.pos, D_L01_001BF900.pos);
        qcopy(D_00189E20.wall_normal, D_L01_001BF900.normal);
        qcopy(D_00189E20.wall_point, D_L01_001BF900.point);
        p->wall_hit = 1;
        p->hit_moby = D_L01_001BF900.moby;
    }
    func_002E34A0(D_00189E20.pos, D_00189E20.pos, offset);
    func_002E34A0(delta, D_00189E20.pos, old);
    {
        float length = func_002E35A0(delta);

        if (D_00189E20.capsule_radius * 1.5f < length) {
            if (arg == 0xF) {
                if (delta[0] > 512.0f)
                    delta[0] = 512.0f;
                else if (delta[0] < -512.0f)
                    delta[0] = -512.0f;
                if (delta[1] > 512.0f)
                    delta[1] = 512.0f;
                else if (delta[1] < -512.0f)
                    delta[1] = -512.0f;
                if (delta[2] > 512.0f)
                    delta[2] = 512.0f;
                else if (delta[2] < -512.0f)
                    delta[2] = -512.0f;
                func_002E3738(delta, delta, D_00189E20.capsule_radius);
                func_002E3470(D_00189E20.pos, old, delta);
            }
            return -1;
        }
    }
    return 1;
}
