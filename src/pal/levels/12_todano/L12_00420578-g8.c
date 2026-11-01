#include "include_asm.h"

#include "common.h"
typedef unsigned int u128 __attribute__((mode(TI), aligned(16)));
typedef struct {
    float axis0[4], axis1[4], axis2[4], position[4];
    u8 pad40[0x30];
    float rotation[4];
} BeamVolume;
typedef struct {
    int index;
    float phase;
    u8 *objects[2];
    float start[4], end[4];
    float f30;
    float heights[3];
    float width, length;
    int sound;
} BeamState;
extern struct { u8 pad[0x464]; u8 flags[0]; } D_L12_0021EDF0;
extern u8 D_0019B4A8[], D_00189EA0[], D_L12_001C0260[], D_00188660[];
extern BeamVolume *D_L12_001B2F8C MACRO_ADDR;
extern int D_001A79F0 MACRO_ADDR;
extern u8 *D_L12_001B090C MACRO_ADDR;
extern u8 *D_L12_001B1360 MACRO_ADDR;
extern float D_L12_001B1D00[] MACRO_ADDR;
extern float D_L12_001B1D00_gp[] SDATA(D_L12_001B1D00);
extern float D_L12_001B1D10_gp[] SDATA(D_L12_001B1D10);
extern u8 *D_0018C0B0 NOT_SDA;
extern u8 D_L12_0041BF88[];
extern void func_L12_0041BDA8(u8 *), func_L12_0041BDF8(u8 *), func_L12_0041BED8(u8 *);
extern void func_0029F338(void *);
extern float func_002A7878(float, float), func_00282DF0(void *), func_00282C48(float);
extern void func_00282CF0(void *, void *, void *), func_00282CC0(void *, void *, void *);
extern void func_00282F20(void *, void *, float);
extern int func_002761F8(void *, void *, int, void *, int);
extern u8 *func_0029EFD0(int);
extern void func_002B37E8(void *, void *), func_002833F0(void *, void *), func_00283698(void *, void *);
extern void func_002A0F48(void *), func_00283098(void *, void *, void *);
extern int func_002E5CF8(int, int, void *);
extern void func_002E59F8(int);
extern int func_002ACBC8(void *, int), func_L12_003DE4B0(void), func_L00_003DE260(void), func_L12_00404778(void);
extern void func_002A8C00(void *, void *, int, void *, float), func_002A8E20(void *, void *);
extern void func_PAL_L00_003E38E8(int, int), func_PAL_L00_004071F0(int, int), func_L00_002E6CF0(void *, void *);

void func_PAL_L12_00420578(u8 *self)
{
    float start[4], end[4], delta[4], local[4];
    float matrix[12], inverse[16];
    u8 event[48];
    BeamState *state = *(BeamState **)(self + 0x68);

    func_L12_0041BDA8(self);
    switch (self[0x20]) {
    case 0: {
        u16 id = *(u16 *)(self + 0xB2);
        int i;

        if (D_L12_0021EDF0.flags[(s16)id])
            goto Destroy;
        {
            int packed = D_0019B4A8[((s16)id >> 1) + (D_001A79F0 << 10)];

            if (id & 1) {
                if ((packed >> 4) & 7)
                    goto Destroy;
            } else if (packed & 7) {
Destroy:
                func_0029F338(self);
                return;
            }
        }
        state->sound = -1;
        self[0x20] = 1;
        state->phase = func_002A7878(0.0f, 1.0f);
        state->f30 = -10.0f;
        {
            float length = func_00282DF0(D_L12_001B2F8C[state->index].axis1);

            state->width = length + length;
            length = func_00282DF0(D_L12_001B2F8C[state->index].axis2);
            state->length = length + length;
        }
        func_00282CF0(state->start, D_L12_001B2F8C[state->index].position, D_L12_001B2F8C[state->index].axis1);
        func_00282CC0(state->end, D_L12_001B2F8C[state->index].position, D_L12_001B2F8C[state->index].axis1);
        {
            BeamVolume *volumes = D_L12_001B2F8C;
            BeamVolume *volume = (BeamVolume *)((u32)(state->index << 7) + (u32)volumes);

            state->start[2] += 1.5f - volume->axis2[2];
            state->end[2] += 1.5f - volume->axis2[2];
            qcopy(end, volume->position);
            end[2] += 1.5f;
            func_00282F20(start, volumes[state->index].axis1, 0.1f);
        }
        while (func_002761F8(state->start, end, 2, 0, 0))
            func_00282CC0(state->start, state->start, start);
        while (func_002761F8(state->end, end, 2, 0, 0))
            func_00282CF0(state->end, state->end, start);
        for (i = 0; i < 2; i++) {
            u8 *obj;

            if (D_L12_001B2F8C[state->index].axis2[2] < 2.0f && i > 0)
                continue;
            obj = func_0029EFD0(0xFDF);
            if (obj) {
                func_002B37E8(obj, self);
                qcopy(obj + 0xF0, D_L12_001B2F8C[state->index].rotation);
                func_002833F0(obj + 0xC0, obj + 0xF0);
                obj[0x31] = 0;
                *(u16 *)(obj + 0x34) |= 0x105;
                *(u128 *)local = 0;
                local[1] = -1.0f;
                local[2] = -1.0f;
                func_00283098(delta, local, &D_L12_001B2F8C[state->index]);
                func_00282CC0(obj + 0x10, delta, D_L12_001B2F8C[state->index].position);
                *(float *)(obj + 0x18) += i * 3.0f;
                func_002A0F48(obj);
                {
                    float radius = *(float *)(*(u8 **)(obj + 0x24) + 0x3C);

                    *(float *)(obj + 0xC) = radius + radius;
                }
            }
            state->objects[i] = obj;
        }
        return;
    }
    case 1:
        break;
    default:
        return;
    }
    state->phase += 0.010000001f;
    if (state->phase > 1.0f)
        state->phase -= 1.0f;
    {
        float height = state->width * 0.5f;

        state->heights[0] = state->heights[1] = state->heights[2] = height;
        func_002833F0(matrix, D_L12_001B2F8C[state->index].rotation);
    }
    func_00283698(inverse, matrix);
    qcopy(start, state->start);
    qcopy(end, state->end);
    {
        int clear = 1;
        int j = 0;

        do {
            if (!func_002761F8(start, end, 2, 0, 0))
                break;
            func_00282CF0(delta, D_L12_001C0260, D_L12_001B2F8C[state->index].position);
            func_00283098(delta, delta, inverse);
            if (state->heights[j] - delta[1] > 1.5f) {
                u16 id = *(u16 *)(self + 0xB2);

                if (id & 1) {
                    u8 *counter = (u8 *)(((s16)id >> 1) + (D_001A79F0 << 10)) + (int)D_0019B4A8;
                    u8 packed = *counter;

                    if (((packed >> 4) & 7) != 7)
                        *counter = packed + 16;
                } else {
                    u8 *counter = (u8 *)(((s16)id >> 1) + (D_001A79F0 << 10)) + (int)D_0019B4A8;
                    u8 packed = *counter;

                    if ((packed & 7) != 7)
                        *counter = packed + 1;
                }
                clear = 0;
            }
            state->heights[j] = delta[1];
            start[2] += 2.0f;
            end[2] += 2.0f;
            j++;
        } while (j < 3);
        if (clear) {
            u8 *sound = D_00188660 + state->sound * 0x70;

            if (*(u8 **)(sound + 0x88) != self || !sound[0x74])
                state->sound = func_002E5CF8(1, 4, self);
        } else {
            int id = state->sound;

            if (id != -1) {
                u8 *sound = D_00188660 + id * 0x70;

                if (*(u8 **)(sound + 0x88) == self && sound[0x74])
                    func_002E59F8(id);
            }
            state->sound = -1;
        }
    }
    {
        u8 *query = D_00189EA0;
        float height, t;
        float *pos;

        if (func_002ACBC8(query, state->index)) {
            t = *(float *)(query + 8);
            if (state->start[2] + 4.0f <= t)
                height = state->heights[2];
            else if (state->start[2] + 1.0f <= t)
                height = state->heights[1];
            else
                height = state->heights[0];
            func_00282CF0(delta, D_00189EA0, D_L12_001B2F8C[state->index].position);
            func_00283098(delta, delta, inverse);
            if (delta[1] < height && delta[0] <= D_L12_001B1D10_gp[0]) {
                func_L12_0041BDF8(self);
                if (delta[0] >= 0.0f) {
                    func_00283098(local, D_L12_001B1D00_gp, matrix);
                    pos = local;
                } else {
                    D_L12_001B1D00_gp[0] = -0.5f;
                    D_L12_001B1D00[2] = -1.0f;
                    func_00283098(local, D_L12_001B1D00_gp, matrix);
                    pos = local;
                    D_L12_001B1D00_gp[0] = 3.0f;
                    D_L12_001B1D00[2] = -3.0f;
                }
                func_002A8C00(event, self, 0x10001, pos, 2.0f);
                func_002A8E20(D_0018C0B0, event);
            } else if (delta[1] < height) {
                func_L12_0041BDF8(self);
            }
        } else if (func_002ACBC8(query + 0x60, state->index)) {
            t = *(float *)(query + 0x68);
            if (state->start[2] + 4.0f <= t)
                height = state->heights[2];
            else if (state->start[2] + 1.0f <= t)
                height = state->heights[1];
            else
                height = state->heights[0];
            func_00282CF0(delta, D_00189EA0 + 0x60, D_L12_001B2F8C[state->index].position);
            func_00283098(delta, delta, inverse);
            if (delta[1] < height) {
                func_L12_0041BDF8(self);
                if (delta[0] >= 0.0f) {
                    func_00283098(local, D_L12_001B1D00_gp, matrix);
                    pos = local;
                } else {
                    D_L12_001B1D00_gp[0] = -0.5f;
                    D_L12_001B1D00[2] = -1.0f;
                    func_00283098(local, D_L12_001B1D00_gp, matrix);
                    pos = local;
                    D_L12_001B1D00_gp[0] = 3.0f;
                    D_L12_001B1D00[2] = -3.0f;
                }
                func_002A8C00(event, self, 0x10001, pos, 2.0f);
                func_002A8E20(D_0018C0B0, event);
            }
        }
    }
    if (func_L12_003DE4B0() && !func_L00_003DE260()) {
        u8 *candidate = D_L12_001B090C;

        qcopy(delta, candidate + 0x10);
        if (func_00282C48(*(float *)(candidate + 0x18) - D_L12_001B2F8C[state->index].position[2]) < 2.0f)
            delta[2] = D_L12_001B2F8C[state->index].position[2];
        if (func_002ACBC8(delta, state->index))
            func_PAL_L00_003E38E8(1, -1);
    }
    if (func_L12_00404778()) {
        u8 *candidate = D_L12_001B1360;

        qcopy(delta, candidate + 0x10);
        if (func_00282C48(*(float *)(candidate + 0x18) - D_L12_001B2F8C[state->index].position[2]) < 2.0f)
            delta[2] = D_L12_001B2F8C[state->index].position[2];
        if (func_002ACBC8(delta, state->index))
            func_PAL_L00_004071F0(1, -1);
    }
    func_L00_002E6CF0(D_L12_0041BF88, self);
    func_L12_0041BED8(self);
}
