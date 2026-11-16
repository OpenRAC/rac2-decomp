#include "include_asm.h"

#include "common.h"
extern s32 g_current_map_index __attribute__((sda));
extern u8 g_moby_group_flags[];
extern u8 *g_moby_l19_array[] __attribute__((sda));
extern int g_mover_var_index[];
extern void BuildObjectAttachmentTransforms(char *, char *, int, int, int, int, int, int);
extern void moby_update_attached_transforms(char *, char *);
extern void euler_rotation_basis(void *, void *);
extern void multiply_matrix3x3(void *, void *, void *);
extern u16 *g_group_ptr_table[];
extern u8 *g_moby_l19_array[] __attribute__((sda));
extern s32 g_max_l19_group_index[] __attribute__((sda));
extern s32 g_current_map_index __attribute__((sda));
extern u8 g_moby_group_flags[];
extern s32 flag_is_third_pending_set(u8 *);
extern void moby_mark_spawned(u8 *);
extern float g_group_release_speed_min_a[] SDATA(D_L19_001B1ECC);
extern float g_group_release_speed_max_a[] SDATA(D_L19_001B1ED0);
extern float g_group_release_speed_min_b[] SDATA(D_L19_001B1ED4);
extern float g_group_release_speed_max_b[] SDATA(D_L19_001B1ED8);
extern u8 g_group_release_glow_alpha[] SDATA(D_L19_001B1EDC);
extern int g_group_release_particle_type_a[] SDATA(D_L19_001B1EE0);
extern int g_group_release_particle_type_b[] SDATA(D_L19_001B1EE4);
extern float g_group_release_particle_scale_a[] SDATA(D_L19_001B1EE8);
extern float g_group_release_particle_scale_b[] SDATA(D_L19_001B1EEC);
extern u32 g_group_release_color_start[] SDATA(D_L19_001B1EF0);
extern u32 g_group_release_color_end[] SDATA(D_L19_001B1EF4);
extern int g_group_release_fade_param_a[] SDATA(D_L19_001B1EFC);
extern int g_group_release_fade_param_b[] SDATA(D_L19_001B1F00);

/* Arms the rig object once its data arrives, then, when the level word matches the rig's tag, applies the stored rotations to the object and to every joint record. */
void rotated_rig_update_pal(char *moby)
{
    char *rig = *(char **)(moby + 0x68);
    float turn[4] __attribute__((aligned(16)));
    char mat[0x30] __attribute__((aligned(16)));
    char *joint;
    int tag;

    switch (*(u8 *)(moby + 0x20)) {
    case 0:
        if (*(long *)rig != -1) {
            { u8 opacity = 0xFF; *(u8 *)(moby + 0x30) = opacity; }
            BuildObjectAttachmentTransforms(moby, rig + 0x30, 0x32, *(s32 *)(rig + 4), *(s32 *)rig, *(s32 *)(rig + 8), 7, 0);
            if (*(u8 *)(rig + 0x7A) == 0) {
                moby_mark_spawned((u8 *)moby);
            } else {
                *(u8 *)(rig + 0x7D) = 1;
                *(u16 *)(moby + 0x34) |= 0x104;
                euler_rotation_basis(moby + 0xC0, moby + 0xF0);
                *(u8 *)(moby + 0x20) = 1;
            }
        }
        return;
    case 1:
        if (g_mover_var_index[0] == *(s32 *)(rig + 0xC)) {
            turn[0] = *(float *)(rig + 0x10) * 0.0003490659f;
            turn[1] = *(float *)(rig + 0x14) * 0.0003490659f;
            turn[2] = *(float *)(rig + 0x18) * 0.0003490659f;
            euler_rotation_basis(mat, turn);
            multiply_matrix3x3(moby + 0xC0, moby + 0xC0, mat);
            joint = rig + 0x30;
            do {
                turn[0] = *(float *)(rig + 0x1C) * 0.0003490659f;
                turn[1] = *(float *)(rig + 0x20) * 0.0003490659f;
                turn[2] = *(float *)(rig + 0x24) * 0.0003490659f;
                euler_rotation_basis(mat, turn);
                multiply_matrix3x3(joint, joint, mat);
                tag = *(u8 *)(joint + 0x4A);
                joint += 0x50;
            } while (tag != 1);
            moby_update_attached_transforms(moby, rig + 0x30);
        }
        break;
    }
}
