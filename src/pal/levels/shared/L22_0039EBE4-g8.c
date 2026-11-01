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
