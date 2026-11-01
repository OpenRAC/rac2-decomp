#include "include_asm.h"

#include "common.h"
typedef union { int q __attribute__((mode(TI))); float f[4]; } Vec;
typedef struct Object Object;
typedef struct State State;
typedef struct Anim {
    char pad_0[36];
    float scale;
} Anim;
struct State {
    Vec vector0;
    Vec velocity;
    int timer;
    char pad_24[1];
    u8 count;
    u8 flag;
    s8 slot;
    char pad_28[4];
    int value2c;
    int value30;
    char pad_34[4];
    int index;
    char pad_3c[4];
    int limit;
    char pad_44[2];
    s16 disabled;
    float random0;
    float random1;
    int value50;
    float random2;
    char pad_58[8];
    Vec last_position;
};
struct Object {
    char pad_0[16];
    Vec position;
    u8 mode;
    char pad_21[2];
    u8 alpha;
    Anim *animation;
    char pad_28[4];
    float scale;
    u8 color;
    char pad_31[1];
    u16 color2;
    u16 flags;
    char pad_36[13];
    u8 anim_id;
    char pad_44[4];
    float anim_speed;
    char pad_4c[20];
    u8 status;
    char pad_61[7];
    State *state;
    char pad_6c[62];
    s16 class_id;
    char pad_ac[20];
    Vec axis_x;
    Vec axis_y;
    Vec axis_z;
    float angle_x;
    float angle_y;
    float angle_z;
};
typedef struct Runtime {
    char pad_0[128];
    Vec player;
    char pad_90[144];
    Vec movement;
    char pad_130[32];
    Vec drift;
    char pad_160[476];
    Object *object;
    char pad_340[8016];
    Object *camera;
    int mode;
    char pad_2298[4];
    int phase;
    char pad_22a0[20];
    u8 flag;
} Runtime;
typedef struct { char pad[4]; u8 active; char rest[219]; } Material;
typedef struct { char pad[0x74]; u8 active; char gap[0x13]; Object *owner; } Slot;
extern int D_L00_001A8F00 __attribute__((sda));
extern int D_L00_001B0768 __attribute__((sda));
extern int D_L00_001B075C __attribute__((sda));
extern unsigned char D_00139587[];
extern Material D_L00_00262570[];
extern Runtime D_00189E20;
extern char D_00188660[];
extern void *D_0018C0B0 NOT_SDA;
extern int D_001A79F0 __attribute__((sda));
extern int D_L00_001A8FF0[] MACRO_ADDR;
extern int D_L00_001ADB2C __attribute__((sda));
extern int D_L00_001B0798[4] __attribute__((sda));
extern int D_L00_001B076C __attribute__((sda)), D_L00_001B0770 __attribute__((sda));
extern float D_L00_001B0774 __attribute__((sda)), D_L00_001B0778 __attribute__((sda));
extern float D_L00_001B077C __attribute__((sda)), D_L00_001B0784 __attribute__((sda));
extern int D_L00_001B0780 __attribute__((sda));
extern int func_L00_003D3DE0(void *, void *);
extern void func_002E59F8(int);
extern int func_002E5CF8(int, int, void *);
extern void func_PAL_002A7E68(void *, int, int,int);
extern float func_002A7940(void);
extern int func_002A7820(int, int);
extern float func_002A7878(float, float);
extern float func_00282EB0(void *, void *);
extern void func_00282CF0(void *, void *,void *);
extern void func_00282CC0(void *, void *,void *);
extern void func_00282D30(void *, void *, float);
extern void func_L00_003EB7C0(void *, void *);
extern void func_PAL_L00_003EFF80(void *, void *);
extern void func_PAL_L00_003EFC00(void *, void *);
extern void func_PAL_L00_003F0390(void *, void *);
extern int func_00282948(void *);
extern void func_0029F338(void *);
extern void func_00300190(void *, void *);
extern void func_002A9288(void *, float);
extern void func_L00_0031AC60(void *, void *,void *, float);
extern void func_00282D08(void *, void *,void *, float);
extern float func_00283B98(float, float);
extern float func_00282C48(float);
extern void func_002AB668(void *, void *, float);
extern void func_002ACDE8(void *, void *,void *);
extern int func_001163B0(void);
extern void func_002ACB48(void *, float);
extern void func_002C2210(void *, int, int,int, int, void *, int,float, float,float);

/* Update the three object states, emit fading particles, and orient the object
 * from the camera basis and its three stored angles. */
void func_PAL_L00_003F0458(Object *object)
{
    Vec vector, matrix;
    State *state;
    Slot *entry;
    Object *camera;
    float angle;

    if (!object)
        return;
    state = object->state;
    if (!state)
        return;
    if (D_L00_001A8F00) {
        state->disabled = 1;
        object->flags |= 0x41;
        return;
    }
    if (state->disabled == 1)
        object->flags &= 0xFFBE;
    if (((Material *)(D_00139587[0] * 224 + (char *)D_L00_00262570))->active &&
        object->mode != 2 && func_L00_003D3DE0(D_0018C0B0, &object->position)) {
        qzero(&state->velocity);
        state->timer = D_L00_001B0768;
        if (state->slot != -1) {
            entry = (Slot *)(D_00188660 + state->slot * 112);
            if (entry->owner == object && entry->active)
                func_002E59F8(state->slot);
        }
        state->slot = -1;
        func_002E5CF8(2, 0, object);
        object->mode = 2;
        return;
    }
    object->scale += (object->animation->scale - object->scale) * 0.1f;
    switch (object->mode) {
    case 0: {
        Slot *entry;

        qzero(&state->vector0);
        /* Velocity is disjoint from the scalar state fields written next. */
        qzero_nc(&state->velocity);
        state->flag = 0;
        state->timer = 0;
        if (object->anim_id)
            func_PAL_002A7E68(object, 0, 0, 8);
        object->color = 255;
        object->color2 = 255;
        state->count = 0;
        state->value30 = 0;
        state->value2c = ((s32)(D_L00_001B075C) * 5 + 2) / 6;
        qcopy(&state->last_position, &D_00189E20.player);
        entry = (Slot *)(D_00188660 + state->slot * 112);
        if (entry->owner != object || !entry->active) {
            state->slot = -1;
            if (((Slot *)(D_00188660 - 0x70))->owner != object ||
                !((Slot *)(D_00188660 - 0x70))->active)
                state->slot = func_002E5CF8(1, 4, object);
        }
        qzero(&state->velocity);
        state->random0 = func_002A7940();
        state->random1 = func_002A7940();
        state->random2 = func_002A7940();
        state->value50 = 0;
        object->mode = 1;
        break;
    }
    case 1: {
        Slot *entry;

        if ((object->status & 2) && object->anim_id != 1)
            func_PAL_002A7E68(object, 1, 0, 10);
        entry = (Slot *)(D_00188660 + state->slot * 112);
        if (entry->owner != object || !entry->active) {
            state->slot = -1;
            if (((Slot *)(D_00188660 - 0x70))->owner != object ||
                !((Slot *)(D_00188660 - 0x70))->active)
                state->slot = func_002E5CF8(1, 4, object);
        }
        if (D_00189E20.mode != 129 &&
            func_00282EB0(&state->last_position, &D_00189E20.player) > 400.0f) {
            if (D_001A79F0 == 7 && D_00189E20.object &&
                D_00189E20.object->class_id == 0x11D9) {
                func_00282CF0(&vector, &D_00189E20.player, &state->last_position);
                func_00282CC0(&object->position, &object->position, &vector);
            } else {
                if (state->slot != -1) {
                    Slot *entry = (Slot *)(D_00188660 + state->slot * 112);
                    if (entry->owner == object && entry->active)
                        func_002E59F8(state->slot);
                }
                state->slot = -1;
                object->alpha = 128;
                /* These scalar writes do not access the velocity vector. */
                qzero_nc(&state->velocity);
                object->flags &= 0xFDFF;
                if (state->index != -1)
                    D_L00_001B0798[state->index] = 0;
                func_0029F338(object);
                return;
            }
        }
        qcopy(&state->last_position, &D_00189E20.player);
        if (state->timer >= 18 && (object->status & 2)) {
            if (object->anim_id != 1)
                func_PAL_002A7E68(object, 1, 0, ((s32)(func_002A7820(7, 12)) * 5 + 2) / 6);
            object->anim_speed = func_002A7878(0.95f, 1.05f);
        }
        if (state->count < state->limit && D_00189E20.phase != 22 &&
            D_00189E20.phase != 20 && !D_00189E20.flag) {
            func_L00_003EB7C0(object, state);
            func_PAL_L00_003EFF80(object, state);
        } else {
            qzero(&state->velocity);
            state->timer = D_L00_001B0768;
            if (state->slot != -1) {
                Slot *entry = (Slot *)(D_00188660 + state->slot * 112);
                if (entry->owner == object && entry->active)
                    func_002E59F8(state->slot);
            }
            state->slot = -1;
            func_002E5CF8(2, 0, object);
            object->mode = 2;
        }
        func_PAL_L00_003EFC00(object, state);
        break;
    }
    case 2:
        if (state->slot != -1) {
            Slot *entry = (Slot *)(D_00188660 + state->slot * 112);
            if (entry->owner == object && entry->active)
                func_002E59F8(state->slot);
        }
        state->slot = -1;
        if (func_00282948(&state->timer)) {
            if (state->slot != -1) {
                Slot *entry = (Slot *)(D_00188660 + state->slot * 112);
                if (entry->owner == object && entry->active)
                    func_002E59F8(state->slot);
            }
            state->slot = -1;
            object->alpha = 128;
            qzero(&state->velocity);
            object->flags &= 0xFDFF;
            if (state->index != -1)
                D_L00_001B0798[state->index] = 0;
            func_0029F338(object);
            return;
        }
        matrix.q = 0;
        qcopy(&vector, &object->position);
        func_002ACB48(&vector, D_L00_001B0774);
        {
            int red = (func_001163B0() + 0x30) & 0x3F;
            int green = (func_001163B0() + 0x20) & 0x3F;
            int blue = func_001163B0() & 0x2F;
            int color;
            int direction;
            int id;
            float scale;

            red |= green << 8;
            red |= blue << 16;
            color = red | (D_L00_001B0780 << 24);
            direction = func_001163B0() % 2;
            if (state->timer & 1)
                direction = -direction;
            id = func_002A7820(D_L00_001B076C, D_L00_001B0770);
            scale = func_002A7878(D_L00_001B0778, D_L00_001B077C);
            func_002C2210(&vector, id, color, 2, direction, &matrix, 0,
                          scale, 0.001f, D_L00_001B0784 * 0.00040000002f);
        }
        object->flags |= 0x200;
        object->alpha -= 128 / D_L00_001B0768;
        object->angle_z = func_00283B98(object->angle_z, 0.5026549f);
        break;
    }
    if (object->mode) {
        if (!D_L00_001ADB2C) {
            if (D_00189E20.mode == 39) {
                func_00282CC0(&object->position, &object->position, &D_00189E20.movement);
            } else {
                func_00282CC0(&vector, &object->position, &D_00189E20.drift);
                func_L00_0031AC60(&object->position, &object->position, &vector, 0.4f);
                func_00282D08(&object->position, &object->position, &vector, 0.625f);
            }
        }
        func_00300190(&object->position, &object->position);
        if (!D_L00_001A8FF0[0])
            func_002A9288(object, 0.3f);
        func_PAL_L00_003F0390(object, state);
    }
    camera = D_00189E20.camera;
    qcopy(&object->axis_x, &camera->axis_x);
    qcopy(&object->axis_y, &camera->axis_y);
    qcopy(&object->axis_z, &camera->axis_z);
    if (D_00189E20.phase == 15) {
        qcopy(&object->axis_x, &camera->axis_y);
        func_00282D30(&object->axis_y, &camera->axis_x, -1.0f);
    }
    angle = object->angle_z;
    if (func_00282C48(angle) > 0.00001f) {
        func_002AB668(&vector, &object->axis_z, angle);
        func_002ACDE8(&object->axis_x, &object->axis_x, &vector);
        func_002ACDE8(&object->axis_y, &object->axis_y, &vector);
    }
    angle = object->angle_y;
    if (func_00282C48(angle) > 0.00001f) {
        func_002AB668(&vector, &object->axis_y, angle);
        func_002ACDE8(&object->axis_x, &object->axis_x, &vector);
        func_002ACDE8(&object->axis_z, &object->axis_z, &vector);
    }
    angle = object->angle_x;
    if (func_00282C48(angle) > 0.00001f) {
        func_002AB668(&vector, &object->axis_x, angle);
        func_002ACDE8(&object->axis_y, &object->axis_y, &vector);
        func_002ACDE8(&object->axis_z, &object->axis_z, &vector);
    }
    object->axis_x.f[3] = object->axis_y.f[3] = object->axis_z.f[3] = 0.0f;
}
