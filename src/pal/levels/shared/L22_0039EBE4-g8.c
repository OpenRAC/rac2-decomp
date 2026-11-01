#include "include_asm.h"

#include "common.h"
typedef int Quad __attribute__((mode(TI)));
typedef struct ProjectileData ProjectileData;
typedef struct ProjectileObject {
    u8 pad0[0x10];
    Quad position;
    u8 pad20[0xc];
    f32 scale;
    u8 pad30;
    u8 targetable;
    u16 pad32;
    u16 flags;
    u8 pad36[0x32];
    ProjectileData *data;
    u8 pad6c[0x50];
    u8 draw;
    u8 padbd[3];
    Quad basis[3];
} ProjectileObject;
struct ProjectileData {
    u8 pad0[0x10];
    ProjectileObject *owner;
    s32 timer;
    ProjectileObject *target;
    f32 turn;
    s32 age;
    s32 color;
    s32 mode;
    s32 player;
    Quad direction;
};
extern void ref_L22_0039D198_31(void *, void *, void *);
extern void ref_L22_0039D198_0(void *, void *, s32);
extern void ref_L22_0039D198_1(void *, f32, f32);
extern void ref_L22_0039D198_2(void *, void *, f32);
extern void ref_L22_0039D198_3(void *, void *, void *);
extern void ref_L22_0039D198_4(void *, void *, f32);
extern f32 ref_L22_0039D198_5(void *);
extern f32 ref_L22_0039D198_6(f32);
extern void ref_L22_0039D198_7(void *, void *);
extern void ref_L22_0039D198_8(void *, void *, void *);
extern void ref_L22_0039D198_9(void *, void *, void *);
extern f32 ref_L22_0039D198_10(void *, void *);
extern void ref_L22_0039D198_11(void *, void *, void *, void *, void *, void *, f32, f32, f32, f32);
extern f32 ref_L22_0039D198_12(f32, f32);
extern s32 ref_L22_0039D198_13(s32);
extern void ref_L22_0039D198_14(void *, f32, f32);
extern void *ref_L22_0039D198_15(void *, void *, s32, s32, s32, s32, s32, f32, f32, f32, s32);
extern s32 ref_L22_0039D198_16(void *, void *, s32, void *, void *);
extern s32 ref_L22_0039D198_17(s32, s32, void *);
extern s32 ref_L22_0039D198_18(void *);
extern void ref_L22_0039D198_19(void *);
extern void ref_L22_0039D198_20(void *, void *, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, f32, f32, f32, f32, f32, f32, f32);
extern void ref_L22_0039D198_21(void *, s32, void *, void *, f32);
extern f32 ref_L22_0039D198_22 __attribute__((sda));
extern f32 ref_L22_0039D198_23 __attribute__((sda));
extern f32 ref_L22_0039D198_24 __attribute__((sda));
extern f32 ref_L22_0039D198_25 __attribute__((sda));
extern f32 ref_L22_0039D198_26 __attribute__((sda));
extern f32 ref_L22_0039D198_27 __attribute__((sda));
extern f32 ref_L22_0039D198_28 __attribute__((sda));
extern u8 ref_L22_0039D198_29[] __attribute__((sda));
extern struct { u8 pad[0x18]; void *object; s32 count; Quad position; } ref_L22_0039D198_30;

/* Steers a projectile toward its target, emits its trail, moves it and tests the
 * swept path. A collision starts its impact effects; expiry or negative world
 * coordinates remove the projectile.
 */
void func_PAL_L22_003A0498(ProjectileObject *obj)
{
    struct {
        Quad offset, velocity, matrix[3], rotation, turn, previous, position;
        union {
            struct { Quad step, extra; } vectors;
            struct {
                ProjectileObject *owner;
                s32 flags;
                u8 kind, mode;
                u16 objectClass;
                f32 radius;
                s32 enabled;
            } hit;
        } collision;
    } local;
    ProjectileData *data = obj->data;
    Quad *basis = obj->basis;
    f32 scale, size;
    s32 color;
    obj->flags &= 0xffbe;
    ref_L22_0039D198_0(&obj->position, &local.offset, 0);
    ref_L22_0039D198_1(&data->turn, 2.8000002f, 0.080000006f);
    ref_L22_0039D198_2(&local.velocity, basis, data->turn);
    ref_L22_0039D198_2(&local.turn, &local.offset, 1.0f);
    ref_L22_0039D198_3(&local.rotation, &obj->basis[2], &local.turn);
    ref_L22_0039D198_4(&local.rotation, &local.rotation, ref_L22_0039D198_22 * 0.5f);
    scale = ref_L22_0039D198_5(&local.rotation);
    ((f32 *)&local.rotation)[3] = -ref_L22_0039D198_6(1.0f - scale * scale);
    ref_L22_0039D198_7(&local.rotation, local.matrix);
    ref_L22_0039D198_8(basis, local.matrix, basis);
    if (data->target) {
        if (data->mode) {
            ref_L22_0039D198_4(&local.collision.vectors.step, &data->target->basis[2], ref_L22_0039D198_23);
            ref_L22_0039D198_9(&local.position, &data->target->position, &local.collision.vectors.step);
            ref_L22_0039D198_11(&obj->position, basis, &local.position, &data->age, &local.offset, &local.previous,
                ref_L22_0039D198_24, ref_L22_0039D198_25, 0.0f, ref_L22_0039D198_26);
            ref_L22_0039D198_2(basis, basis, 1.0f);
            ref_L22_0039D198_4(&local.velocity, basis, data->turn);
        } else if (data->player) {
            if (data->timer < 121) {
                ref_L22_0039D198_31(&local.previous, &obj->position, &data->target->position);
                if (ref_L22_0039D198_10(&local.previous, &local.velocity) < 0.0f) {
                    ref_L22_0039D198_4(&local.collision.vectors.extra, &data->target->basis[2], ref_L22_0039D198_23);
                    ref_L22_0039D198_9(&local.collision.vectors.step, &data->target->position, &local.collision.vectors.extra);
                    ref_L22_0039D198_11(&obj->position, basis, &local.collision.vectors.step, &data->age, &local.offset, &local.position,
                        ref_L22_0039D198_24, ref_L22_0039D198_25, 0.0f, ref_L22_0039D198_27);
                    ref_L22_0039D198_2(basis, basis, 1.0f);
                    ref_L22_0039D198_4(&local.velocity, basis, data->turn);
                }
            }
        } else {
            ref_L22_0039D198_4(&local.velocity, &data->direction, data->turn);
            ref_L22_0039D198_2(&local.previous, &local.velocity, 1.0f);
            qcopy(basis, &local.previous);
        }
    }
    qcopy(&local.position, &obj->position);
    ref_L22_0039D198_4(&local.collision.vectors.step, &local.velocity, 0.7f);
    size = ref_L22_0039D198_12(0.1f, 0.3f);
    color = ref_L22_0039D198_13(255);
    ref_L22_0039D198_14(&local.previous, 0.0f, 0.1f);
    ref_L22_0039D198_9(&local.previous, &local.previous, &local.position);
    ref_L22_0039D198_15(&local.previous, ref_L22_0039D198_29, 12, 0x808080, color, 32, 0,
        size * 210000.0f, size * 42000.0f, 0.0f, 0);
    ref_L22_0039D198_9(&local.position, &local.position, &local.collision.vectors.step);
    qcopy(&local.previous, &obj->position);
    ref_L22_0039D198_9(&obj->position, &obj->position, &local.velocity);
    if (((f32 *)&obj->position)[0] < 0.0f || ((f32 *)&obj->position)[1] < 0.0f
        || ((f32 *)&obj->position)[2] < 0.0f) {
        ref_L22_0039D198_19(obj);
        return;
    }
    {
        local.collision.hit.owner = obj;
        local.collision.hit.flags = 0x8b0003;
        local.collision.hit.radius = ref_L22_0039D198_28;
        local.collision.hit.enabled = 1;
        qcopy(&local.position, &local.velocity);
        ref_L22_0039D198_2(&local.position, &local.position, 1.0f);
        ((f32 *)&local.position)[3] = 5627.925f;
        local.collision.hit.kind = 3;
        local.collision.hit.mode = 3;
        local.collision.hit.objectClass = *(u16 *)((u8 *)obj + 0xaa);
        if (!obj->draw && ref_L22_0039D198_16(&local.previous, &obj->position, 0, data->owner, &local.position)) {
            if (ref_L22_0039D198_30.object) {
                if (ref_L22_0039D198_30.object != *(void **)((u8 *)obj + 0xb8)) {
                    obj->draw = 2;
                    qcopy(&obj->position, &ref_L22_0039D198_30.position);
                }
            } else if (ref_L22_0039D198_30.count > 0) {
                obj->draw = 1;
                qcopy(&obj->position, &ref_L22_0039D198_30.position);
            }
            ref_L22_0039D198_17(0, 0, obj);
        } else if (ref_L22_0039D198_18(&data->timer)) {
            ref_L22_0039D198_19(obj);
            return;
        }
    }
    if (obj->draw) {
        ref_L22_0039D198_20(obj, ref_L22_0039D198_29, 0, 2, 1, 4, -1, 0, 0, -1, 0, 0x810001,
            0.0f, 0.0f, 1.5f, 1.0f, 9.0f, 1.0f, 15.0f);
        ref_L22_0039D198_21(&obj->position, 0, data->owner, &local.position, 2.0f);
        ref_L22_0039D198_19(obj);
    }
}

extern s32 func_2F4BE0(f32);
extern u16 D_L22_001AA5EC __attribute__((sda));
typedef struct {
    u8 pad0[0x188c];
    void *aim;
    u8 pad1890[0xa00];
    ProjectileObject *moby;
    s32 state;
} Hero;
extern ProjectileObject *ref_L22_0039CDC0_0(s32);
extern void ref_L22_0039CDC0_1(void *, void *);
extern void ref_L22_0039CDC0_2(void *, void *, f32);
extern void ref_L22_0039CDC0_3(void *, void *, void *);
extern void ref_L22_0039CDC0_4(void *, void *, void *);
extern void ref_L22_0039CDC0_5(void *, f32);
extern void ref_L22_0039CDC0_6(void *, void *, f32);
extern f32 ref_L22_0039CDC0_7(void *);
extern f32 ref_L22_0039CDC0_8(void *, void *);
extern f32 ref_L22_0039CDC0_9(f32);
extern f32 ref_L22_0039CDC0_10(void *, void *);
extern s32 ref_L22_0039CDC0_11(s32, s32, void *);
extern f32 D_L22_001AF2B0 __attribute__((sda));
extern f32 D_L22_001AF2C8 __attribute__((sda));
extern ProjectileObject *ref_L22_0039CDC0_12[] __attribute__((sda));
extern Hero D_00189E20;
extern Quad D_L22_001B1930 __attribute__((sda));

/* Spawns a class-0x100 moby at `position` with the owner's orientation and a 150-frame
   timer, picks its target (the argument, else the level's fallback), then drops the
   target when it is out of range or behind, and points the hero's aim at the shot. */
ProjectileObject *func_PAL_L22_003A00C0(ProjectileObject *owner, Quad *position,
                                    ProjectileObject *target, s32 a3, s32 a4)
{
    Quad offset, targetpos, start, direction, facing;
    s32 reject;
    ProjectileObject *obj;
    ProjectileData *data;
    f32 ownerangle, targetangle, distance, dot;

    obj = ref_L22_0039CDC0_0(0x100);
    if (obj) {
        data = obj->data;
        ref_L22_0039CDC0_1(obj, owner);
        obj->scale *= D_L22_001AF2B0;
        obj->flags |= 0x100;
        data->turn = 0.40000004f;
        obj->basis[0] = owner->basis[0];
        obj->basis[1] = owner->basis[1];
        obj->basis[2] = owner->basis[2];
        data->owner = owner;
        qcopy(&obj->position, position);
        {
            ProjectileObject *fallback = ref_L22_0039CDC0_12[0];

            data->timer = 125;
            obj->scale += obj->scale;
            data->mode = a3;
            data->player = a4;
            if (target) {
                data->target = target;
                data->color = 0x890000;
            } else if (fallback) {
                data->target = fallback;
                data->color = 0x890000;
            } else {
                data->target = 0;
                data->color = 0x890000;
                data->player = 0;
                data->mode = 0;
            }
        }
        if (owner == D_00189E20.moby)
            data->player = 1;
        if (!data->mode && data->target) {
            ref_L22_0039CDC0_2(&offset, &data->target->basis[2], 5.0f);
            ref_L22_0039CDC0_3(&offset, &data->target->position, &offset);
            qcopy(&targetpos, &data->target->position);
            ref_L22_0039CDC0_5(&targetpos, 0.0f);
            ref_L22_0039CDC0_4(&data->direction, &offset, &obj->position);
            qcopy(&start, &obj->position);
            ref_L22_0039CDC0_5(&start, 0.0f);
            reject = 0;
            ref_L22_0039CDC0_4(&direction, &targetpos, &start);
            ref_L22_0039CDC0_6(&direction, &direction, 1.0f);
            ref_L22_0039CDC0_6(&data->direction, &data->direction, 1.0f);
            ownerangle = ref_L22_0039CDC0_7(&owner->position);
            targetangle = ref_L22_0039CDC0_7(&data->target->position);
            distance = ref_L22_0039CDC0_8(&targetpos, &start);
            if (distance < 5.0f && ref_L22_0039CDC0_9(ownerangle - targetangle) > 10.0f)
                reject = 1;
            qcopy(&facing, &obj->basis[0]);
            dot = ref_L22_0039CDC0_10(&direction, &facing);
            if ((owner == D_00189E20.moby && !data->target->targetable)
                || dot < D_L22_001AF2C8 || distance > 50.0f || reject)
                data->target = 0;
            if (owner == D_00189E20.moby) {
                if (data->target) {
                    D_00189E20.aim = &data->direction;
                } else if (D_00189E20.state == 0x5b) {
                    qcopy(&D_L22_001B1930, &owner->basis[2]);
                    ref_L22_0039CDC0_2(&D_L22_001B1930, &D_L22_001B1930, -1.0f);
                    D_00189E20.aim = &D_L22_001B1930;
                    qcopy(&data->direction, &D_L22_001B1930);
                    data->mode = 0;
                    data->target = (ProjectileObject *)1;
                    data->player = 0;
                }
            }
        }
        data->age = 0;
        ref_L22_0039CDC0_11(1, 0, obj);
        obj->draw = 0;
        obj->flags |= 0x41;
    }
    return obj;
}
