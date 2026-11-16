#include "include_asm.h"
#include "common.h"

/* func_US2_L03_002FEB58, the USA v2.00 copy of func_L03_002FDE30: the same C, with quad_a
   level test (0x33) added around the 0xFA0 objects' update, and the moby list read
   through quad_a local base in byte offsets, which leaves no separate list-address add in
   the loop: loop.c then hoists 0xFA0 on its first pass and 0x33 on its second. */

typedef unsigned int Quad __attribute__((mode(TI)));

/* The level's runtime block: its mode word and timer, and quad_a counted list of objects. */
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
/* Four matrices of three quadwords, filled from twelve joints of one moby. */
extern Quad g_joint_world_matrices[][3];
extern void anim_start_startup_animations(void);
extern void UpdateEquipmentPieces_us2(void *);
extern void math_store_angle_update_result(void *, void *, u32, u32, f32);
extern void EmitScaledObjectParticles(void *);
extern void moby_transform_joint_to_world(void *, s32, void *);

/* Per-frame pass over the level's objects: starts the startup animations, updates special objects, and drives the Endako intro objects and particles. */
void level_update_objects_us2(void)
{
    EndakoState *level_state;
    u8 *moby;
    s32 i;
    Quad quad_a, quad_b;

    anim_start_startup_animations();
    for (i = 0; i < g_endako_state.count; i++) {
        u8 *base = (u8 *)&g_endako_state;
        moby = *(u8 **)(base + i * 4 + 0x18C);
        if (moby != 0 && *(s16 *)(moby + 0xAA) == 0xE29)
            *(u16 *)(moby + 0x34) |= 0x800;
        if (*(s16 *)(moby + 0xAA) == 0xD54)
            UpdateEquipmentPieces_us2(moby);
        if (moby != 0 && *(s16 *)(moby + 0xAA) == MOBY_CLASS_TV_SCREENS && g_current_map_index != 0x33) {
            u8 *vars = *(u8 **)(moby + 0x68);
            if (vars != 0)
                math_store_angle_update_result(moby, vars + 0xC, 0x80AAAAD2, 0x80396464, 0.061086535f);
        }
    }
    if (g_current_map_index != 3)
        return;
    level_state = &g_endako_state;
    if (level_state->mode < 3) {
        u8 *pose = level_state->objects[1];
        *(f32 *)(pose + 0x2C) = *(f32 *)(*(u8 **)(pose + 0x24) + 0x24) * g_object_scale;
    }
    if (level_state->mode == 6)
        EmitScaledObjectParticles(level_state->objects[1]);
    if (level_state->mode == 8)
        EmitScaledObjectParticles(level_state->objects[3]);
    if (level_state->mode == 7 && level_state->timer == 0x424) {
        u8 *target;
        s32 row_index, col_index, i;

        g_object_timer = level_state->timer;
        target = level_state->objects[2];
        for (row_index = 0; row_index < 4; row_index++)
            for (col_index = 0; col_index < 3; col_index++)
                moby_transform_joint_to_world(target, row_index * 3 + col_index, &g_joint_world_matrices[row_index][col_index]);
        for (i = 0; i < 4; i++) {
            Quad (*matrices)[3] = g_joint_world_matrices;
            qcopy(&quad_a, &matrices[i][0]);
            qcopy(&quad_b, &matrices[i][1]);
            qcopy(&quad_a, &matrices[i][0]);
            qcopy(&quad_b, &matrices[i][2]);
        }
    }
}
