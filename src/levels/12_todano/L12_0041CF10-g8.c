#include "common.h"

extern int g_current_map_index __attribute__((sda));
extern u8 D_0019B4A8[];
extern struct { u8 pad[0x464]; u8 flags[0]; } D_L12_0021EDF0;
extern u8 *D_L12_001B2E9C MACRO_ADDR;
extern u8 *D_L12_001B2E9C_gp SDATA(D_L12_001B2E9C);
extern int D_L12_001B1DA0 __attribute__((sda));

extern int linked_moby_is_finished(void *);
extern void linked_moby_trigger_burst(void *);
extern void moby_set_state(void *, int, int);
extern int math_fast_float_d(void *);
extern void vec_scale_to_length(void *, void *, float);
extern void part_spawn_masked_debris(void *, int, void *, float, float, float, float, u8);
/* GPR and FP arguments retain their respective EE ABI order. */
extern void *SpawnExplosion(void *, int, int, int, int, int, int, int,
                         int, int, int, int, float, float);
extern void moby_mark_spawned(void *);

/* Waits for three linked mobys to be ready, lifts them all, then blows them up together and counts the break as saved progress. */
void three_child_break_controller_update(u8 *self)
{
    u8 *state = *(u8 **)(self + 0x68);
    float vec[4];
    int ready;

    switch (self[0x20]) {
    case 0: {
        u16 id;

        self[0x20] = 1;
        *(float *)(state + 0x10) = *(float *)(self + 0x18);
        id = *(u16 *)(self + 0xB2);
        if (D_L12_0021EDF0.flags[(s16)id])
            goto Destroy0;
        {
            int packed = D_0019B4A8[((s16)id >> 1) + (g_current_map_index << 10)];

            if (id & 1) {
                if ((packed >> 4) & 7)
                    goto Destroy0;
                return;
            } else if (!(packed & 7)) {
                return;
            }
        }
Destroy0:
        moby_mark_spawned(self);
        break;
    }
    case 1: {
        int i;

        ready = 1;
        for (i = 0; i < 3; i++, state += 4) {
            if (*(int *)state != -1) {
                if (!linked_moby_is_finished(D_L12_001B2E9C_gp + (*(int *)state << 8)))
                    ready = 0;
            }
        }
        if (ready)
            self[0x20] = 2;
        break;
    }
    case 4: {
        int i;
        int *child_ids;
        u8 *base = D_L12_001B2E9C;

        *(float *)(state + 0xC) += 0.0013888889225199819f;
        *(float *)(self + 0x18) += *(float *)(state + 0xC);
        child_ids = (int *)state;
        for (i = 0; i < 3; i++) {
            if (child_ids[i] != -1)
                *(float *)((child_ids[i] << 8) + (u32)base + 0x18) += *(float *)(state + 0xC);
        }
        if (*(float *)(state + 0x10) + 8.0f < *(float *)(self + 0x18))
            self[0x20] = 5;
        break;
    }
    case 2:
        moby_set_state(self, 3, -1);
        *(int *)(state + 0x14) = D_L12_001B1DA0;
        break;
    case 3: {
        int i;
        int *child_ids;
        u8 *child;
        u16 id;

        if (math_fast_float_d(state + 0x14)) {
            *(int *)(self + 0x98) = 0;
            *(u16 *)(self + 0x34) = (*(u16 *)(self + 0x34) | 0x41) & 0xEFFF;
            vec_scale_to_length(vec, self + 0xC0, -0.10000000894f);
            part_spawn_masked_debris(self, 63, vec, 3.0f, 6.0f, 3.0f, 6.0f, 255);
            child_ids = (int *)state;
            for (i = 0; i < 3; i++, child_ids++) {
                if (*child_ids != -1) {
                    child = D_L12_001B2E9C_gp + (*child_ids << 8);
                    linked_moby_trigger_burst(child);
                    SpawnExplosion(child + 0x10, 1, 14, 10, 15, 10, 20, 1,
                                  1, 1, 0, 0, 2.0f, 20.0f);
                    moby_mark_spawned(D_L12_001B2E9C + (*child_ids << 8));
                }
            }
            id = *(u16 *)(self + 0xB2);
            if (id & 1) {
                u8 *counter = (u8 *)(((s16)id >> 1) + (g_current_map_index << 10)) + (int)D_0019B4A8;
                u8 packed = *counter;

                if (((packed >> 4) & 7) != 7)
                    *counter = packed + 16;
            } else {
                u8 *counter = (u8 *)(((s16)id >> 1) + (g_current_map_index << 10)) + (int)D_0019B4A8;
                u8 packed = *counter;

                if ((packed & 7) != 7)
                    *counter = packed + 1;
            }
            moby_mark_spawned(self);
            break;
        }
        if (*(int *)(state + 0x14) == D_L12_001B1DA0 / 2) {
            int *child_ids2 = (int *)state;
            int j;

            for (j = 0; j < 3; j++, child_ids2++) {
                if (*child_ids2 != -1)
                    ((u8 *)((*child_ids2 << 8) + (u32)D_L12_001B2E9C_gp))[0x20] = 4;
            }
        }
        break;
    }
    case 5: {
        int i;
        u8 *child;
        u16 id;

        for (i = 0; i < 3; i++, state += 4) {
            if (*(int *)state != -1) {
                u8 *base = D_L12_001B2E9C_gp;

                child = (u8 *)((*(int *)state << 8) + (u32)base);
                *(u16 *)(child + 0x34) &= 0xEFFF;
                moby_mark_spawned(base + (*(int *)state << 8));
            }
        }
        id = *(u16 *)(self + 0xB2);
        if (id & 1) {
            u8 *counter = (u8 *)(((s16)id >> 1) + (g_current_map_index << 10)) + (int)D_0019B4A8;
            u8 packed = *counter;

            if (((packed >> 4) & 7) != 7)
                *counter = packed + 16;
        } else {
            u8 *counter = (u8 *)(((s16)id >> 1) + (g_current_map_index << 10)) + (int)D_0019B4A8;
            u8 packed = *counter;

            if ((packed & 7) != 7)
                *counter = packed + 1;
        }
        moby_mark_spawned(self);
        break;
    }
    }
}
