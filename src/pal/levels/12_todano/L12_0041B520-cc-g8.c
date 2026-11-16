#include "names.h"
/* func_PAL_L12_0041B520, the PAL copy of func_L12_004163E8: the same C, where rename func_0032C700 becomes func_PAL_L00_003FB330; rename func_L12_0041E8F8 becomes func_PAL_L12_00423C50; rename func_002B0A68 becomes func_PAL_002B15D8; scale D_L12_001B18F0; scale D_L12_001B18F0 / 2. */
#include "common.h"

extern s32 linked_moby_is_finished(u8 *);
extern void linked_moby_trigger_burst_pal(u8 *);
extern s32 math_fast_float_d(s32 *);
extern void moby_set_state(u8 *, u8, s32);
extern void moby_mark_spawned(void *);
extern u8 *SpawnExplosion_pal(void *, s32, s32, s32, s32, s32, s32, s32,
                          f32, f32, s32, s32, s32, void *);
extern void vec_scale_to_length(f32 *, void *, f32);
extern void part_spawn_masked_debris_pal(f32, f32, f32, f32, char *, s32, f32 *, u8);

/* level 12 data reached through $gp (small-data) */
extern int g_current_map_index __attribute__((sda));
extern u8 *g_moby_list_start MACRO_ADDR;
extern u8 *g_moby_list_start;
extern int g_rise_controller_duration __attribute__((sda));

/* level 12 data reached absolutely: out of the $gp window */
extern struct { u8 pad[0x464]; u8 flags[0]; } g_object_flags;
extern u8 g_moby_nibble_table[];

typedef struct Actor {
    char pad00[0x18];
    f32 f18;              /* 0x18 */
    char pad1c[0x04];
    u8 f20;               /* 0x20 */
    char pad21[0x13];
    u16 f34;              /* 0x34 */
    char pad36[0x32];
    void *f68;            /* 0x68 */
    char pad6c[0x2c];
    u32 f98;              /* 0x98 */
    char pad9c[0x16];
    u16 fB2;              /* 0xB2 */
    char padB4[0x0c];
    char fC0[0x40];       /* 0xC0 */
} Actor;

typedef struct Node {
    s32 f0;               /* 0x00 */
    f32 f4;               /* 0x04 */
    f32 f8;               /* 0x08 */
    s32 fC;               /* 0x0C */
} Node;

/* Waits for its linked moby to finish, rises with it, then blows both up and counts the break as saved progress (PAL: 50 Hz timings). */
void single_child_rise_controller_update_pal(Actor *self)
{
    Node *vars = self->f68;

    switch (self->f20) {

    case 0: {
        u16 object_id;

        self->f20 = 1;
        vars->f8 = self->f18;
        object_id = self->fB2;
        if (g_object_flags.flags[(s16)object_id] != 0)
            goto Destroy;
        {
            s32 bits = g_moby_nibble_table[((s16)object_id >> 1) + (g_current_map_index << 10)];
            if (object_id & 1) {
                if (((bits >> 4) & 7) != 0)
                    goto Destroy;
                return;
            } else {
                if ((bits & 7) == 0)
                    return;
                goto Destroy;
            }
        }

    }
    case 1:
        if (vars->f0 != -1) {
            if (linked_moby_is_finished(g_moby_list_start + (vars->f0 << 8)) == 0)
                return;
        }
        self->f20 = 2;
        vars->fC = 0x43;
        return;

    case 4: {
        s32 index;
        vars->f4 = vars->f4 + 0.002f;
        self->f18 = self->f18 + vars->f4;
        index = vars->f0;
        if (index != -1) {
            u8 *base = g_moby_list_start;
            ((Actor *)base)[index].f18 += vars->f4;
        }
        if (vars->f8 + 8.0f < self->f18)
            self->f20 = 5;
        return;

    }
    case 2:
        if (math_fast_float_d(&vars->fC) != 0)
            return;
        moby_set_state((u8 *)self, 3, -1);
        vars->fC = (((int)(g_rise_controller_duration) * 5 + 2) / 6);
        return;

    case 3: {
        u16 object_id;

        if (math_fast_float_d(&vars->fC) != 0) {
            u8 *child = (u8 *)g_moby_list_start + (vars->f0 << 8);
            f32 push_vec[4];

            SpawnExplosion_pal(child + 0x10, 1, 0xE, 0xA, 0xF, 0xA, 0x14, 1,
                          2.0f, 20.0f, 1, 1, 0, 0);
            self->f98 = 0;
            self->f34 = (self->f34 | 0x41) & 0xEFFF;
            linked_moby_trigger_burst_pal(child);
            vec_scale_to_length(push_vec, self->fC0, -0.120000005f);
            part_spawn_masked_debris_pal(3.0f, 6.0f, 3.0f, 6.0f, (char *)self, 0x3F, push_vec, 0xFF);
            if (vars->f0 != -1) {
                ((Actor *)g_moby_list_start)[vars->f0].f34 &= 0xEFFF;
                moby_mark_spawned(g_moby_list_start + (vars->f0 << 8));
            }
        object_id = self->fB2;
        if (object_id & 1) {
            u8 *cell = g_moby_nibble_table + (((s16)object_id >> 1) + (g_current_map_index << 10));
            if (((*cell >> 4) & 7) != 7)
                *cell += 0x10;
        } else {
            u8 *cell = g_moby_nibble_table + (((s16)object_id >> 1) + (g_current_map_index << 10));
            if ((*cell & 7) != 7)
                *cell += 1;
        }
Destroy:
        moby_mark_spawned(self);
        } else if (vars->fC == (((int)(g_rise_controller_duration / 2) * 5 + 2) / 6)) {
            if (vars->f0 != -1)
                ((Actor *)g_moby_list_start)[vars->f0].f20 = 4;
        }
        return;

    }
    case 5: {
        u16 object_id;

        object_id = self->fB2;
        if (object_id & 1) {
            u8 *cell = g_moby_nibble_table + (((s16)object_id >> 1) + (g_current_map_index << 10));
            if (((*cell >> 4) & 7) != 7)
                *cell += 0x10;
        } else {
            u8 *cell = g_moby_nibble_table + (((s16)object_id >> 1) + (g_current_map_index << 10));
            if ((*cell & 7) != 7)
                *cell += 1;
        }
        moby_mark_spawned(self);
        return;
    }
    }

}
