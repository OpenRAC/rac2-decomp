#include "common.h"

extern s32 linked_moby_is_finished(u8 *);
extern void linked_moby_trigger_burst(u8 *);
extern s32 math_fast_float_d(s32 *);
extern void moby_set_state(u8 *, u8, s32);
extern void moby_mark_spawned(void *);
extern u8 *SpawnExplosion(void *, s32, s32, s32, s32, s32, s32, s32,
                          f32, f32, s32, s32, s32, void *);
extern void vec_scale_to_length(f32 *, void *, f32);
extern void part_spawn_masked_debris(f32, f32, f32, f32, char *, s32, f32 *, u8);

/* level 12 data reached through $gp (small-data) */
extern int g_current_map_index __attribute__((sda));
extern u8 *D_L12_001B2E9C MACRO_ADDR;
extern u8 *D_L12_001B2E9C;
extern int D_L12_001B18F0 __attribute__((sda));

/* level 12 data reached absolutely: out of the $gp window */
extern struct { u8 pad[0x464]; u8 flags[0]; } D_L12_0021EDF0;
extern u8 D_0019B4A8[];

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

/* Waits for its linked moby to finish, rises with it, then blows both up and counts the break as saved progress. */
void single_child_rise_controller_update(Actor *self)
{
    Node *vars = self->f68;

    switch (self->f20) {

    case 0: {
        u16 rawId;

        self->f20 = 1;
        vars->f8 = self->f18;
        rawId = self->fB2;
        if (D_L12_0021EDF0.flags[(s16)rawId] != 0)
            goto Destroy;
        {
            s32 savedBits = D_0019B4A8[((s16)rawId >> 1) + (g_current_map_index << 10)];
            if (rawId & 1) {
                if (((savedBits >> 4) & 7) != 0)
                    goto Destroy;
                return;
            } else {
                if ((savedBits & 7) == 0)
                    return;
                goto Destroy;
            }
        }

    }
    case 1:
        if (vars->f0 != -1) {
            if (linked_moby_is_finished(D_L12_001B2E9C + (vars->f0 << 8)) == 0)
                return;
        }
        self->f20 = 2;
        vars->fC = 0x50;
        return;

    case 4: {
        s32 index;
        vars->f4 = vars->f4 + 0.0013888889f;
        self->f18 = self->f18 + vars->f4;
        index = vars->f0;
        if (index != -1) {
            u8 *base = D_L12_001B2E9C;
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
        vars->fC = D_L12_001B18F0;
        return;

    case 3: {
        u16 rawId;

        if (math_fast_float_d(&vars->fC) != 0) {
            u8 *child = (u8 *)D_L12_001B2E9C + (vars->f0 << 8);
            f32 offset[4];

            SpawnExplosion(child + 0x10, 1, 0xE, 0xA, 0xF, 0xA, 0x14, 1,
                          2.0f, 20.0f, 1, 1, 0, 0);
            self->f98 = 0;
            self->f34 = (self->f34 | 0x41) & 0xEFFF;
            linked_moby_trigger_burst(child);
            vec_scale_to_length(offset, self->fC0, -0.10000000894069672f);
            part_spawn_masked_debris(3.0f, 6.0f, 3.0f, 6.0f, (char *)self, 0x3F, offset, 0xFF);
            if (vars->f0 != -1) {
                ((Actor *)D_L12_001B2E9C)[vars->f0].f34 &= 0xEFFF;
                moby_mark_spawned(D_L12_001B2E9C + (vars->f0 << 8));
            }
        rawId = self->fB2;
        if (rawId & 1) {
            u8 *cell = D_0019B4A8 + (((s16)rawId >> 1) + (g_current_map_index << 10));
            if (((*cell >> 4) & 7) != 7)
                *cell += 0x10;
        } else {
            u8 *cell = D_0019B4A8 + (((s16)rawId >> 1) + (g_current_map_index << 10));
            if ((*cell & 7) != 7)
                *cell += 1;
        }
Destroy:
        moby_mark_spawned(self);
        } else if (vars->fC == D_L12_001B18F0 / 2) {
            if (vars->f0 != -1)
                ((Actor *)D_L12_001B2E9C)[vars->f0].f20 = 4;
        }
        return;

    }
    case 5: {
        u16 rawId;

        rawId = self->fB2;
        if (rawId & 1) {
            u8 *cell = D_0019B4A8 + (((s16)rawId >> 1) + (g_current_map_index << 10));
            if (((*cell >> 4) & 7) != 7)
                *cell += 0x10;
        } else {
            u8 *cell = D_0019B4A8 + (((s16)rawId >> 1) + (g_current_map_index << 10));
            if ((*cell & 7) != 7)
                *cell += 1;
        }
        moby_mark_spawned(self);
        return;
    }
    }

}
