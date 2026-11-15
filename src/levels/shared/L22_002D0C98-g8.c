#include "include_asm.h"
#include "common.h"

typedef int TI128 __attribute__((mode(TI)));
typedef float Vector[4] __attribute__((aligned(16)));

extern void func_2F3A80(void *, void *, void *);
extern void func_2F3AB0(void *, void *, void *);
extern void func_2F3AF0(void *, void *, f32);
extern s32 func_2F4BE0(f32);
extern void *func_332F58(s32);

/* A halfword read through $gp. */
extern u16 D_L22_001AA5EC __attribute__((sda));

/* func_L22_0039CDC0 reads $gp data (the scale and facing-limit floats), hence -G8. */

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
/* func_002E5CF8 returns int (see src/game/0026EA00.c); the call_value is what keeps the
   final flags update off $v0. */
extern s32 ref_L22_0039CDC0_11(s32, s32, void *);

extern f32 D_L22_001AF2B0 __attribute__((sda));
extern f32 D_L22_001AF2C8 __attribute__((sda));
/* Incomplete: read here with retail's absolute lui/lw, not through $gp. */
extern ProjectileObject *ref_L22_0039CDC0_12[] __attribute__((sda));
extern Hero g_hero_state;
extern Quad D_L22_001B1930 __attribute__((sda));

/* Allocates a kind-0x1F record for a handle. Three vector helpers combine the given point
   with the handle's vector at +0x10, one step scaled by 0.25; the record takes the result,
   the point, the colour word and its low 24 bits, a helper's result plus 0x70, a 0x44 byte,
   a 2, a halfword and the handle. Does nothing when the allocation fails. */
void part_spawn_homing_trail(u32 colour, Vector point, u8 *handle)
{
    Vector target;
    Vector step;
    Vector offset;
    u8 *record;

    *(TI128 *)target = *(TI128 *)point;
    record = func_332F58(0x1F);
    if (record == 0)
        return;
    func_2F3AB0(offset, target, handle + 0x10);
    *(TI128 *)step = *(TI128 *)offset;
    func_2F3AF0(step, step, 0.25f);
    func_2F3A80(offset, handle + 0x10, step);
    *(TI128 *)(record + 0x10) = *(TI128 *)offset;
    *(TI128 *)(record + 0x20) = *(TI128 *)target;
    *(u32 *)(record + 0x4) = colour;
    *(u32 *)(record + 0xC) = colour & 0xFFFFFF;
    record[0x9] = func_2F4BE0(4.0f) + 0x70;
    record[0x3] = 0x44;
    record[0x1] = 2;
    *(u16 *)(record + 0xA) = D_L22_001AA5EC;
    *(u8 **)(record + 0x30) = handle;
}

/* Spawns a class-0x100 moby at `position` with the owner's orientation and a 150-frame
   timer, picks its target (the argument, else the level's fallback), then drops the
   target when it is out of range or behind, and points the hero's aim at the shot. */
ProjectileObject *homing_projectile_spawn(ProjectileObject *owner, Quad *position,
                                    ProjectileObject *target, s32 a3, s32 a4)
{
    Quad offset, targetpos, start, direction, facing;
    s32 reject;
    ProjectileObject *obj;
    ProjectileData *data;
    f32 ownerangle, targetangle, distance, dot;

    obj = ref_L22_0039CDC0_0(0x100 /* moby class 256 */);
    if (obj) {
        data = obj->data;
        ref_L22_0039CDC0_1(obj, owner);
        obj->scale *= D_L22_001AF2B0;
        obj->flags |= 0x100;
        data->turn = 1.0f / 3.0f;
        obj->basis[0] = owner->basis[0];
        obj->basis[1] = owner->basis[1];
        obj->basis[2] = owner->basis[2];
        data->owner = owner;
        qcopy(&obj->position, position);
        {
            ProjectileObject *fallback = ref_L22_0039CDC0_12[0];

            data->timer = 150;
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
        if (owner == g_hero_state.moby)
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
            if ((owner == g_hero_state.moby && !data->target->targetable)
                || dot < D_L22_001AF2C8 || distance > 50.0f || reject)
                data->target = 0;
            if (owner == g_hero_state.moby) {
                if (data->target) {
                    g_hero_state.aim = &data->direction;
                } else if (g_hero_state.state == 0x5b) {
                    qcopy(&D_L22_001B1930, &owner->basis[2]);
                    ref_L22_0039CDC0_2(&D_L22_001B1930, &D_L22_001B1930, -1.0f);
                    g_hero_state.aim = &D_L22_001B1930;
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
