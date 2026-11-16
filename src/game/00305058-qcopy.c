#include "common.h"

typedef float V4_F305058[4] __attribute__((aligned(16)));

extern u8 g_item_slot_to_record[];
extern char g_weapon_table[];
extern s32 g_miniturret_shot_param __attribute__((sda));

extern void moby_transform_joint_to_world(char *, s32, void *);
extern void moby_get_facing_direction(char *, void *);
extern char *moby_get_private_value_0(char *);
extern void FastVecScale(void *, char *, float);
extern void FastVecAdd(void *, void *, void *);
extern void FastVecSub(void *, void *, void *);
extern void vec_scale_to_length(void *, void *, float);
extern void vec_add_transformed_or_copy(void *, void *, void *);
extern void part_add_trail_entry(char *, void *);
extern s32 PlayMobySound(s32, s32, char *);

#define ENTRY() (D_00239BA0 + D_00139568[0x29] * 0xE0)

/* One step of an object's launch routine: aims the pending hit and counts it down. */
/* Fires the Miniturret's shot at its target and uses up one round. */
void miniturret_fire_shot(char *moby)
{
    V4_F305058 up_dir, target_pos, shot_velocity, muzzle_pos, target_motion;
    char *vars = *(char **)(moby + 0x68);
    char *target_info;
    char *target;
    float speed;
    char *weapon_def;

    moby_transform_joint_to_world(moby, 1, muzzle_pos);
    moby_get_facing_direction(moby + 0x10, up_dir);
    if (*(float *)(vars + 0x5C) == 0.0f) {
        if (*(s32 *)(vars + 0x50) != 0) {
            if (*(char **)(vars + 0x68) != 0) {
                target_info = moby_get_private_value_0(*(char **)(vars + 0x68));
                target = *(char **)(vars + 0x68);
                qcopy(target_pos, target + 0x10);
                if (target_info != 0) {
                    FastVecScale(target_motion, target + 0xE0, *(float *)(target_info + 0x10));
                    FastVecAdd(target_pos, target_pos, target_motion);
                }
                weapon_def = ENTRY();
                speed = *(float *)(weapon_def + 0x50) * 0.016666668f;
                FastVecSub(shot_velocity, target_pos, muzzle_pos);
                vec_scale_to_length(shot_velocity, shot_velocity, speed);
                vec_add_transformed_or_copy(shot_velocity, shot_velocity, muzzle_pos);
                part_add_trail_entry(moby, shot_velocity);
                PlayMobySound(0, 0, moby);
                *(s32 *)(vars + 0x40) = g_miniturret_shot_param;
                *(s32 *)(vars + 0x44) = 6;
                if (--*(s32 *)(vars + 0x60) <= 0)
                    *(u8 *)(moby + 0x20) = 8;
                weapon_def = ENTRY();
                *(float *)(vars + 0x5C) = 1.0f / *(float *)(weapon_def + 0x54);
            }
        }
    }
}
