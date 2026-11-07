/* func_PAL_L02_00417A48, the PAL copy of func_L02_00412D50: the same C, where rename func_002A7470 becomes func_PAL_002A7E68; rename func_L00_002C42E0 becomes func_PAL_L00_002C4480; rename func_L00_002B9D60 becomes func_PAL_L00_002B9CD8; rename func_L02_00413730 becomes func_PAL_L02_00418428. */
#include "common.h"

typedef int TI128 __attribute__((mode(TI)));
typedef union { TI128 quad; float f[4]; } LiftVector;
typedef struct {
    u8 pad0[0x80];
    float position[4];
    u8 pad90[0x33C - 0x90];
    u8 *lift;
    s32 active;
    u8 pad344[0x22B6 - 0x344];
    u8 boarding;
} LiftHero;
extern LiftHero D_00189E20;
typedef struct {
    u8 pad0[0x60];
    s32 launch_nodes[2];
    s32 cameras[2];
    u8 pad70[8];
    s32 flag;
    s32 stops[2];
    s32 sound;
    u8 pad88[8];
    LiftVector position;
    LiftVector rotation;
    u8 padB0[12];
    s32 side;
    u8 padC0[12];
    float speed;
} LiftState;
extern u8 D_0019B2E8[];
typedef struct { u8 bytes[0x70]; } LiftSoundStride;
extern LiftSoundStride D_00188660[];
extern u8 D_001A7B00[] __attribute__((sda));
extern s32 D_001A79F0[] MACRO_ADDR;
typedef struct {
    LiftVector axes[3];
    LiftVector position;
    u8 pad40[0x30];
    LiftVector rotation;
} LiftNode;
extern LiftNode *D_L02_001B368C MACRO_ADDR;
extern s32 D_L02_001B30C8[] MACRO_ADDR;
extern float D_L02_001B2FE0[] MACRO_ADDR;
extern float D_L02_001B1C50 __attribute__((sda));
extern float D_L02_001B1C54 __attribute__((sda));
extern LiftVector D_L02_001B1C60 __attribute__((sda));
extern float D_L02_001B1C6C[] MACRO_ADDR;
extern char D_L02_001B1C70[];
extern u8 D_L02_001BA500[];
extern void func_00282A28(void);
extern void func_002A7750(u8 *, s32, s32);
extern void func_PAL_002A7E68(void *, s32, s32, s32);
extern void func_00282D60(void *, void *, float);
extern s32 func_00283DB8(void *, float);
extern void func_0029F338(void *);
extern void func_00282CF0(void *, void *, void *);
extern void func_00283098(void *, void *, void *);
extern void func_00282CC0(void *, void *, void *);
extern float func_00282E20(void *);
extern void func_002AFDD8(char *, char *, char *, char *);
extern double func_001234F0(float);
extern void func_0026FEB8(const char *, ...);
extern int func_PAL_L00_002C4480(s32, s32);
extern float func_00282E80(void *, void *);
extern void func_003355A8(s32);
extern s32 func_002B3868(u8 *);
extern void func_00335438(void *, void *, s32, s32, s32);
extern void func_L00_002D40A0(void *, s32, float);
extern s32 func_002E5CF8(s32, s32, char *);
extern float func_002AA2E8(float *, float, float);
extern void func_00282F20(void *, void *, float);
extern s32 func_002A8C28(void *, void *, u32, float, float, float, s32, s32, s32);
extern float func_00283248(float, float);
extern float func_002AA800(float *, s32, float, float);
extern void func_00335370(void *);
extern void func_003353C8(void *);
extern void func_002E59F8(s32);
extern void func_002A7398(s8 *, s32, s32);
extern void func_002833F0(void *, void *);
extern void func_00282D30(void *, void *, float);
extern void func_PAL_L00_002B9CD8(void *, void *, s32, s32);
extern void func_L00_0042A500(s32);
extern void func_PAL_L02_00418428(u8 *);
extern void func_002AD6F0(void *, void *, void *, void *);

/*
 * Move between the two lift poses, coordinating the camera and boarding state.
 * -G16 and the qcopy flags are this unit's own; its gp-relative data does not fit -G8.
 * func_002AA800 returns a float (it ends by calling func_002AA738, like its sibling
 * func_002AA898): the ignored call_value is what orders the yaw loads.
 */
void func_PAL_L02_00417A48(u8 *object)
{
    LiftVector old_position;
    LiftVector old_rotation;
    LiftVector delta;
    LiftVector point;
    LiftVector aim;
    LiftVector launch;
    LiftVector rotation;
    LiftState *state = *(LiftState **)(object + 0x68);
    s32 side;
    float distance;
    float target;
    s32 i;

    qcopy_nc(&old_position, (object + 0x10));
    qcopy_nc(&old_rotation, (object + 0xF0));
    switch (object[0x20]) {
    case 0: {
        s32 index;
        object[0x30] = 0xFF;
        state->sound = -1;
        if (state->stops[0] == -1 || state->stops[1] == -1) {
            func_0029F338(object);
            return;
        }
        if (state->launch_nodes[0] == -1 || state->launch_nodes[1] == -1)
            func_00282A28();
        if (state->cameras[0] == -1 || state->cameras[1] == -1)
            func_00282A28();
        if (state->flag != -1) {
            if (D_001A7B00[0x1E]) {
                func_0029F338(object);
                return;
            }
            *(s32 *)(object + 0x98) = 0;
            {
                s16 flags = (*(u16 *)(object + 0x34) | 0x41) & 0xEFFF;
                *(u16 *)(object + 0x34) = flags;
            }
            func_002A7750(object, 4, -1);
        } else
            func_002A7750(object, 1, -1);
        if (object[0x43] != 2)
            func_PAL_002A7E68(object, 2, 0, 1);
        index = state->stops[0];
        qcopy_nc(&state->position, &D_L02_001B368C[index].position);
        qcopy_nc(&state->rotation, &D_L02_001B368C[index].rotation);
        break;
    }
    case 4:
        if (D_0019B2E8[state->flag + (D_001A79F0[0] << 4)] & 0x80) {
            func_00282D60(&delta, object, 0.0009765625f);
            if (func_00283DB8(&delta, 64.0f) == -1) {
                s16 flags = (*(u16 *)(object + 0x34) & 0xFFBE) | 0x1000;
                *(u16 *)(object + 0x34) = flags;
                *(u32 *)(object + 0x98) = *(u32 *)(*(u8 **)(object + 0x24) + 0x10);
                func_002A7750(object, 1, -1);
            }
        }
        break;
    case 1: {
        LiftNode *record;
        if (state->flag != -1 && D_001A7B00[0x1E]) {
            func_0029F338(object);
            return;
        }
        if (D_00189E20.lift == object && D_00189E20.active) {
            func_00282CF0(&delta, D_00189E20.position, object + 0x10);
            point.quad = 0;
            point.f[0] = -1.2f;
            point.f[2] = -0.69f;
            func_00283098(&point, &point, object + 0xC0);
            func_00282CC0(&point, &point, object + 0x10);
            func_00282CF0(&aim, &point, D_00189E20.position);
            distance = func_00282E20(&aim);
            func_002AFDD8((char *)object, (char *)&delta, (char *)&delta, 0);
            if (delta.f[2] < -0.6f) {
                func_0026FEB8(D_L02_001B1C70, func_001234F0(distance));
                func_PAL_L00_002C4480(0x6F, 1);
                func_002A7750(object, 2, -1);
            }
        } else if ((D_L02_001B30C8[0] & 0x3F) == 0) {
            float current;
            side = (state->side + 1) & 1;
            record = &D_L02_001B368C[state->stops[side]];
            distance = func_00282E80(D_00189E20.position, &record->position);
            record = &D_L02_001B368C[state->stops[state->side]];
            current = func_00282E80(D_00189E20.position, &record->position);
            if (distance < current) {
                s32 index;
                state->side = side;
                index = state->stops[side];
                qcopy_nc(&state->position, &D_L02_001B368C[index].position);
                qcopy_nc(&state->rotation, &D_L02_001B368C[index].rotation);
                qcopy_nc((object + 0x10), (&state->position));
                qcopy_nc((object + 0xF0), (&state->rotation));
            }
        }
        break;
    }
    case 2: {
        LiftNode *record;
        s32 count;
        u32 layer;
        if (D_00189E20.active == 0) {
            func_003355A8(0);
            break;
        }
        if (func_002B3868(object)) {
            func_00335438(D_L02_001BA500, D_L02_001BA500 + 0x10, 1, 0, 0);
            delta.quad = 0;
            delta.f[0] = -1.2f;
            delta.f[2] = -0.69f;
            func_00283098(&delta, &delta, object + 0xC0);
            func_00282CC0(&delta, &delta, object + 0x10);
            func_L00_002D40A0(&delta, 0, *(float *)(object + 0xF8));
            D_00189E20.boarding = 1;
            func_002E5CF8(1, 0, (char *)object);
            if (object[0x43])
                func_PAL_002A7E68(object, 0, 0, 37);
        }
        func_002AA2E8(&state->speed, D_L02_001B1C50 * 0.020000001f, D_L02_001B1C54 * 0.00040000002f);
        func_00282F20(&delta, object + 0xC0, state->speed);
        delta.f[2] = 0.0f;
        func_00282CC0(&state->position, &state->position, &delta);
        i = 0;
        count = 2;
        layer = 0x10000;
        do {
            qcopy_nc(&point, &D_L02_001B1C60);
            if (i)
                point.f[1] = -point.f[1];
            func_00283098(&point, &point, object + 0xC0);
            func_00282CC0(&point, &point, object + 0x10);
            func_002A8C28(object, &point, layer, D_L02_001B1C6C[0], 1.0f, 1.0f, 0, 1, 0);
        } while (++i < count);
        qcopy_nc(&point, D_L02_001BA500);
        point.f[2] += 0.020000001f;
        qcopy_nc(&aim, (D_L02_001BA500 + 0x10));
        distance = func_00282E80(&point, D_00189E20.position);
        target = func_00283248(distance, D_00189E20.position[2] - point.f[2]);
        func_002AA800(aim.f + 1, 0, -target, 0.015707966f);
        target = func_00283248(D_00189E20.position[0] - point.f[0], D_00189E20.position[1] - point.f[1]);
        func_002AA800(aim.f + 2, 0, target, 0.031415932f);
        func_00335370(&point);
        func_003353C8(&aim);
        {
            u16 previous = *(u16 *)(object + 0x96);
            s32 ticks = previous + 1;
            {
                s16 stored = ticks;
                *(u16 *)(object + 0x96) = stored;
            }
            if (previous >= 101)
                func_002AA2E8(&D_L02_001B2FE0[0], 1.0f, 0.040000003f);
            else {
                s32 slot;
                u8 *sound_record;
                if ((u16)ticks == 37)
                    func_PAL_L00_002C4480(0x6F, 1);
                slot = state->sound;
                sound_record = (u8 *)&D_00188660[slot];
                if (*(u8 **)(sound_record + 0x88) != object || !sound_record[0x74])
                    state->sound = func_002E5CF8(0, 4, (char *)object);
            }
        }
        if (D_L02_001B2FE0[0] >= 1.0f) {
            s32 slot;
            func_PAL_L00_002C4480(0, 1);
            slot = state->sound;
            if (slot != -1) {
                u8 *sound_record = (u8 *)&D_00188660[slot];
                if (*(u8 **)(sound_record + 0x88) == object && sound_record[0x74])
                    func_002E59F8(slot);
            }
            state->sound = -1;
            func_002A7398((s8 *)object, 2, 0);
            func_002A7750(object, 3, -1);
            state->side = (state->side + 1) & 1;
            {
                s32 index = state->stops[state->side];
                qcopy_nc(&state->position, &D_L02_001B368C[index].position);
                qcopy_nc(&state->rotation, &D_L02_001B368C[index].rotation);
            }
            func_002833F0(object + 0xC0, &state->rotation);
            record = &D_L02_001B368C[state->launch_nodes[state->side]];
            func_00282D30(&launch, record, -0.9f);
            func_00282CC0(&launch, &launch, &record->position);
            qcopy_nc(&rotation, (&record->rotation));
            func_PAL_L00_002B9CD8(&launch, &rotation, 0, 1);
            func_L00_002D40A0(&record->position, 1, record->rotation.f[2]);
            func_003355A8(0);
            func_L00_0042A500(state->cameras[state->side]);
            func_PAL_L02_00418428(object);
        }
        break;
    }
    case 3:
        func_002AA2E8(&D_L02_001B2FE0[0], 0.0f, 0.040000003f);
        if (D_L02_001B2FE0[0] <= 0.0f) {
            state->speed = 0.0f;
            func_002A7750(object, 1, -1);
        }
        break;
    }
    if (object[0x31])
        func_PAL_L02_00418428(object);
    func_00282CF0(&delta, object + 0x10, &old_position);
    func_002AD6F0((u8 *)state + 0x20, &delta, &old_rotation, object + 0xF0);
}
