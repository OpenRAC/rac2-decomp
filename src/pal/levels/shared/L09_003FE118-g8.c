#include "common.h"

/* func_PAL_L09_003FE118, the PAL copy of func_L09_003F9708: the same C, with the timer
   period scaled to 50 Hz and the per-frame steps at 0.02 and 0.04. */

extern float g_trooper_arm_shot_speed __attribute__((sda));
extern float g_trooper_attack_range __attribute__((sda));
extern int g_trooper_anim_period __attribute__((sda));
extern float vec_distance_xy(void *, void *);
extern int FastDecTimer(void *);
extern int enemy_check_line_of_sight(void *, int, int, int);
extern void moby_transform_joint_to_world(void *, int, void *);
extern void FastVecSub(float *, const float *, const float *);
extern void vec_scale_to_length(float *, float *, float);
extern int PlayMobySound(int, int, void *);
extern char *moby_spawn_aimed_effect(void *, float, void *, void *);

typedef struct { char gap[0x2F0]; char *parts[2]; } Parts9708;

/* Fire from a valid linked part after its timer and parent flags permit it. */
void trooper_fire_arm_shot_pal(char *moby)
{
    float pos[4] __attribute__((aligned(16)));
    float dir[4] __attribute__((aligned(16)));
    char *state = *(char **)(moby + 0x68);
    char *parent;
    int close = 1;
    int side, shift;
    if (!(vec_distance_xy(moby + 0x10, *(char **)(state + 0x200)+0x10) < g_trooper_attack_range))
        close = 0;
    if (!*(int *)(state + 0x2F8) || !FastDecTimer(state + 0x2E4))
        return;
    side = (*(unsigned short *)(moby + 0x96) / (((s32)(g_trooper_anim_period) * 5 + 2) / 6)) & 1;
    shift = side ? 5 : 4;
    if (!((*(unsigned short *)(*(char **)(state + 0x2F8)+0x7C) >> shift) & 1))
        goto invalid;
    if (!enemy_check_line_of_sight(moby, 1, 0, *(u8 *)(state + 0x30D) != 0))
        return;
    parent = ((Parts9708 *)state)->parts[side];
    if (!parent || *(short *)(parent + 0xAA) != 0xD66)
        return;
    if (*(u8 *)(parent + 0x20) == 0xFE)
        return;
    if (*(u8 *)(parent + 0x20) == 0xFD)
        return;
    {
        *(short *)(state + 0x2E4) = ((s32)(g_trooper_anim_period) * 5 + 2) / 6;
        moby_transform_joint_to_world(((Parts9708 *)state)->parts[side], 0, pos);
        FastVecSub(dir, (float *)(state + 0x1F0), pos);
        vec_scale_to_length(dir, dir, g_trooper_arm_shot_speed * 0.020000001f);
        if (!close && !*(u8 *)(state + 0x30D)) {
            if (dir[2] > 0.040000003f)
                dir[2] = 0.040000003f;
            else if (dir[2] < -0.040000003f)
                dir[2] = -0.040000003f;
        }
        vec_scale_to_length(dir, dir, g_trooper_arm_shot_speed * 0.020000001f);
        PlayMobySound(1, 0, *(void **)(state + 0x2F8));
        moby_spawn_aimed_effect(moby, (float)*(u8 *)(state + 0x34), dir, pos);
    }
    return;
invalid:
    *(short *)(state + 0x2E4) = ((s32)(g_trooper_anim_period) * 5 + 2) / 6;
}
