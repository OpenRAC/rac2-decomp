#include "include_asm.h"
#include "common.h"

/* func_PAL_L03_002FFA00, the PAL copy of func_L03_002FDE30: the USA v2.00 C (a level test
   of 0x33 around the 0xFA0 objects' update, the object list read through a local base),
   where the 0xFA0 update's float goes from 0.061086535f to 0.07330384f (x 6/5) and the
   mode 7 timer test from 0x424 to 0x373 (x 5/6). */

typedef unsigned int Quad __attribute__((mode(TI)));

/* The level's runtime block: its mode word and timer, and a counted list of objects. */
typedef struct {
    u8 pad00[0x30];
    u32 mode;
    s32 timer;
    u8 pad38[0xC];
    s16 count;
    u8 pad46[0x146];
    u8 *objects[0];
} EndakoState;

extern EndakoState g_endako_state;
extern s32 g_current_map_index __attribute__((sda));
extern f32 g_object_scale SDATA(D_L03_001A9420);
extern s32 g_object_timer SDATA(D_L03_001A9424);
/* Four rows of three quadwords, filled from twelve joints of one object. */
extern Quad g_joint_world_matrices[][3];
extern void anim_start_startup_animations(void);
extern void func_PAL_002E7270(void *);
extern void math_store_angle_update_result(void *, void *, u32, u32, f32);
extern void func_PAL_L03_00328558(void *);
extern void moby_transform_joint_to_world(void *, s32, void *);

void func_PAL_L03_002FFA00(void)
{
    EndakoState *state;
    u8 *object;
    s32 i;
    Quad a, b;

    anim_start_startup_animations();
    for (i = 0; i < g_endako_state.count; i++) {
        u8 *base = (u8 *)&g_endako_state;
        object = *(u8 **)(base + i * 4 + 0x18C);
        if (object != 0 && *(s16 *)(object + 0xAA) == 0xE29)
            *(u16 *)(object + 0x34) |= 0x800;
        if (*(s16 *)(object + 0xAA) == 0xD54)
            func_PAL_002E7270(object);
        if (object != 0 && *(s16 *)(object + 0xAA) == 0xFA0 && g_current_map_index != 0x33) {
            u8 *vars = *(u8 **)(object + 0x68);
            if (vars != 0)
                math_store_angle_update_result(object, vars + 0xC, 0x80AAAAD2, 0x80396464, 0.07330384f);
        }
    }
    if (g_current_map_index != 3)
        return;
    state = &g_endako_state;
    if (state->mode < 3) {
        u8 *p = state->objects[1];
        *(f32 *)(p + 0x2C) = *(f32 *)(*(u8 **)(p + 0x24) + 0x24) * g_object_scale;
    }
    if (state->mode == 6)
        func_PAL_L03_00328558(state->objects[1]);
    if (state->mode == 8)
        func_PAL_L03_00328558(state->objects[3]);
    if (state->mode == 7 && state->timer == 0x373) {
        u8 *target;
        s32 row, col, k;

        g_object_timer = state->timer;
        target = state->objects[2];
        for (row = 0; row < 4; row++)
            for (col = 0; col < 3; col++)
                moby_transform_joint_to_world(target, row * 3 + col, &g_joint_world_matrices[row][col]);
        for (k = 0; k < 4; k++) {
            Quad (*rows)[3] = g_joint_world_matrices;
            qcopy(&a, &rows[k][0]);
            qcopy(&b, &rows[k][1]);
            qcopy(&a, &rows[k][0]);
            qcopy(&b, &rows[k][2]);
        }
    }
}
