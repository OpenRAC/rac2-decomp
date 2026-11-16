#include "include_asm.h"

#include "common.h"
extern void moby_set_state(char *, int, int);
extern void anim_start_blended_pal(char *, int, int, int);
extern int math_random_int_range(int, int);
extern int PlayMobySound(int, int, char *);
extern int g_current_map_index;
extern unsigned char g_moby_group_flags[];
extern char *g_path_list[];
extern float path_l01_compute_segment_lengths(char *);
extern void mem_clear(char *, int, int);
extern int actor_choose_path_goal(char *);
extern int moby_apply_damage_to_object_pal(char *, char *, int);
extern void trigger_linked_object(char *);
extern void math_update_wrapped_angle_offset(char *, char *, char *, float, float, float);
extern void moby_scale_owner_words_by_angles(char *, char *, char *, float, float, float);

/* Sets up the path follower the first time, then handles its hits and keeps its turning in step (PAL: 50 Hz timings). */
int follower_init_and_check_hits_pal(unsigned char *obj)
{
    char *state = *(char **)(obj + 0x68);
    int hit, old_alert_state;
    if (obj[0x20] == 0) {
        if ((g_moby_group_flags[obj[0xB0] + (g_current_map_index << 4)] & 0x80) && *(int *)(state + 0x33C)) return 1;
        *(int *)(state + 0x2AC) = 0;
        *(unsigned short *)(obj + 0x34) |= 0x800;
        *(int *)(state + 0x254) = -1;
        *(int *)(state + 0xA8) = 3;
        state[0x70] = 7; state[0x71] = 5; state[0x72] = 6; state[0x76] = 6; state[0x77] = 6;
        *(float *)(state + 0x7C) = 0.120000005f;
        *(int *)(state + 0x80) = 0;
        *(float *)(state + 0x84) = 0.006f;
        *(float *)(state + 0x88) = 0.012f;
        *(float *)(state + 0x8C) = 0.006f;
        *(float *)(state + 0x90) = 2.5f; *(int *)(state + 0x94) = 0;
        *(float *)(state + 0x9C) = .4f;
        state[0xCC] = 4; state[0xCD] = 8; state[0xCE] = 4; state[0xCF] = 8;
        state[0xD2] = 4; state[0xD3] = 8; state[0xD4] = 0; state[0xD6] = 1;
        *(float *)(state + 0x2A8) = *(unsigned char *)(state + 0x34);
        state[0x28] = 3;
        *(int *)(state + 0x30) = 0; *(int *)(state + 0x258) = 0; *(int *)(state + 0x26C) = 0;
        qzero(state + 0x230);
        qcopy(state + 0x220, g_path_list[*(int *)(state + 0x274)] + 0x10);
        moby_set_state((char *)obj, 1, 0);
        if (obj[0x43] != 1) anim_start_blended_pal((char *)obj, 1, 0, 0);
        obj[0x30] = 0x80; *(short *)(obj + 0x32) = 0x80;
        path_l01_compute_segment_lengths(g_path_list[*(int *)(state + 0x274)]);
        path_l01_compute_segment_lengths(g_path_list[*(int *)(state + 0x270)]);
        mem_clear(state + 0x2B0, 0, 0x80);
    }
    *(int *)(state + 0x258) = actor_choose_path_goal((char *)obj);
    *(float *)(obj + 0x2C) = *(float *)(*(char **)(obj + 0x24) + 0x24);
    old_alert_state = obj[0x95];
    hit = moby_apply_damage_to_object_pal((char *)obj, state + 0x60, 0);
    if (hit) {
        trigger_linked_object((char *)obj);
        if (hit < 4) PlayMobySound(2, 0, (char *)obj);
        if (old_alert_state == 1) *(int *)(state + 0x24C) = ((s32)(math_random_int_range(300, 360)) * 5 + 2) / 6;
        if ((unsigned int)(hit - 4) < 2) moby_set_state((char *)obj, 8, -1);
    }
    if (*(unsigned short *)(state + 0x98) & 3) *(int *)(obj + 0x98) = 0;
    math_update_wrapped_angle_offset((char *)obj, state + 0x280, state + 0x284, .3f, 0.027925273f, -1);
    moby_scale_owner_words_by_angles((char *)obj, state + 0x288, state + 0x28C, .1047197655f, 0.0062831864f, 0.007330384f);
    return 0;
}
