#include "names.h"
/* func_PAL_L12_004221E8, the PAL copy of func_L12_0041CF10: the same C, where rename func_002B0A68 becomes func_PAL_002B15D8; rename func_L12_0041E8F8 becomes func_PAL_L12_00423C50; rename func_0032C700 becomes func_PAL_L00_003FB330; scale D_L12_001B1DA0 / 2; wrap D_L12_001B1DA0 (((int)({e}) * 5 + 2) / 6). */
#include "common.h"

extern int g_current_map_index __attribute__((sda));
extern u8 g_moby_nibble_table[];
extern struct { u8 pad[0x464]; u8 flags[0]; } g_object_flags;
extern u8 *g_moby_list_start MACRO_ADDR;
extern u8 *D_L12_001B2E9C_gp SDATA(D_L12_001B2E9C);
extern int g_break_controller_duration __attribute__((sda));

extern int linked_moby_is_finished(void *);
extern void linked_moby_trigger_burst_pal(void *);
extern void moby_set_state(void *, int, int);
extern int math_fast_float_d(void *);
extern void vec_scale_to_length(void *, void *, float);
extern void part_spawn_masked_debris_pal(void *, int, void *, float, float, float, float, u8);
/* GPR and FP arguments retain their respective EE ABI order. */
extern void *SpawnExplosion_pal(void *, int, int, int, int, int, int, int,
                         int, int, int, int, float, float);
extern void moby_mark_spawned(void *);

/* Waits for three linked mobys to be ready, lifts them all, then blows them up together and counts the break as saved progress (PAL: 50 Hz timings). */
void three_child_break_controller_update_pal(u8 *self)
{
    u8 *state = *(u8 **)(self + 0x68);
    float push_vec[4];
    int ready;

    switch (self[0x20]) {
    case 0: {
        u16 object_id;

        self[0x20] = 1;
        *(float *)(state + 0x10) = *(float *)(self + 0x18);
        object_id = *(u16 *)(self + 0xB2);
        if (g_object_flags.flags[(s16)object_id])
            goto Destroy0;
        {
            int packed = g_moby_nibble_table[((s16)object_id >> 1) + (g_current_map_index << 10)];

            if (object_id & 1) {
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
        int *links;
        u8 *base = g_moby_list_start;

        *(float *)(state + 0xC) += 0.002f;
        *(float *)(self + 0x18) += *(float *)(state + 0xC);
        links = (int *)state;
        for (i = 0; i < 3; i++) {
            if (links[i] != -1)
                *(float *)((links[i] << 8) + (u32)base + 0x18) += *(float *)(state + 0xC);
        }
        if (*(float *)(state + 0x10) + 8.0f < *(float *)(self + 0x18))
            self[0x20] = 5;
        break;
    }
    case 2:
        moby_set_state(self, 3, -1);
        *(int *)(state + 0x14) = (((int)(g_break_controller_duration) * 5 + 2) / 6);
        break;
    case 3: {
        int i;
        int *links;
        u8 *child;
        u16 object_id;

        if (math_fast_float_d(state + 0x14)) {
            *(int *)(self + 0x98) = 0;
            *(u16 *)(self + 0x34) = (*(u16 *)(self + 0x34) | 0x41) & 0xEFFF;
            vec_scale_to_length(push_vec, self + 0xC0, -0.120000005f);
            part_spawn_masked_debris_pal(self, 63, push_vec, 3.0f, 6.0f, 3.0f, 6.0f, 255);
            links = (int *)state;
            for (i = 0; i < 3; i++, links++) {
                if (*links != -1) {
                    child = D_L12_001B2E9C_gp + (*links << 8);
                    linked_moby_trigger_burst_pal(child);
                    SpawnExplosion_pal(child + 0x10, 1, 14, 10, 15, 10, 20, 1,
                                  1, 1, 0, 0, 2.0f, 20.0f);
                    moby_mark_spawned(g_moby_list_start + (*links << 8));
                }
            }
            object_id = *(u16 *)(self + 0xB2);
            if (object_id & 1) {
                u8 *counter = (u8 *)(((s16)object_id >> 1) + (g_current_map_index << 10)) + (int)g_moby_nibble_table;
                u8 packed = *counter;

                if (((packed >> 4) & 7) != 7)
                    *counter = packed + 16;
            } else {
                u8 *counter = (u8 *)(((s16)object_id >> 1) + (g_current_map_index << 10)) + (int)g_moby_nibble_table;
                u8 packed = *counter;

                if ((packed & 7) != 7)
                    *counter = packed + 1;
            }
            moby_mark_spawned(self);
            break;
        }
        if (*(int *)(state + 0x14) == (((int)(g_break_controller_duration / 2) * 5 + 2) / 6)) {
            int *links2 = (int *)state;
            int j;

            for (j = 0; j < 3; j++, links2++) {
                if (*links2 != -1)
                    ((u8 *)((*links2 << 8) + (u32)D_L12_001B2E9C_gp))[0x20] = 4;
            }
        }
        break;
    }
    case 5: {
        int i;
        u8 *child;
        u16 object_id;

        for (i = 0; i < 3; i++, state += 4) {
            if (*(int *)state != -1) {
                u8 *base = D_L12_001B2E9C_gp;

                child = (u8 *)((*(int *)state << 8) + (u32)base);
                *(u16 *)(child + 0x34) &= 0xEFFF;
                moby_mark_spawned(base + (*(int *)state << 8));
            }
        }
        object_id = *(u16 *)(self + 0xB2);
        if (object_id & 1) {
            u8 *counter = (u8 *)(((s16)object_id >> 1) + (g_current_map_index << 10)) + (int)g_moby_nibble_table;
            u8 packed = *counter;

            if (((packed >> 4) & 7) != 7)
                *counter = packed + 16;
        } else {
            u8 *counter = (u8 *)(((s16)object_id >> 1) + (g_current_map_index << 10)) + (int)g_moby_nibble_table;
            u8 packed = *counter;

            if ((packed & 7) != 7)
                *counter = packed + 1;
        }
        moby_mark_spawned(self);
        break;
    }
    }
}
