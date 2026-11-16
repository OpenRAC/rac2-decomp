#include "include_asm.h"

#include "common.h"
extern void moby_set_state(char *, int, int);
extern void func_PAL_002A7E68(char *, int, int, int);
extern int math_random_int_range(int, int);
extern int PlayMobySound(int, int, char *);
extern int g_current_map_index;
extern unsigned char g_moby_group_flags[];
extern char *g_path_list[];
extern float path_l01_compute_segment_lengths(char *);
extern void mem_clear(char *, int, int);
extern int actor_choose_path_goal(char *);
extern int func_PAL_002B1A50(char *, char *, int);
extern void trigger_linked_object(char *);
extern void math_update_wrapped_angle_offset(char *, char *, char *, float, float, float);
extern void moby_scale_owner_words_by_angles(char *, char *, char *, float, float, float);

int func_PAL_L06_004245B0(unsigned char *obj)
{
    char *d = *(char **)(obj + 0x68);
    int hit, old;
    if (obj[0x20] == 0) {
        if ((g_moby_group_flags[obj[0xB0] + (g_current_map_index << 4)] & 0x80) && *(int *)(d + 0x33C)) return 1;
        *(int *)(d + 0x2AC) = 0;
        *(unsigned short *)(obj + 0x34) |= 0x800;
        *(int *)(d + 0x254) = -1;
        *(int *)(d + 0xA8) = 3;
        d[0x70] = 7; d[0x71] = 5; d[0x72] = 6; d[0x76] = 6; d[0x77] = 6;
        *(float *)(d + 0x7C) = 0.120000005f;
        *(int *)(d + 0x80) = 0;
        *(float *)(d + 0x84) = 0.006f;
        *(float *)(d + 0x88) = 0.012f;
        *(float *)(d + 0x8C) = 0.006f;
        *(float *)(d + 0x90) = 2.5f; *(int *)(d + 0x94) = 0;
        *(float *)(d + 0x9C) = .4f;
        d[0xCC] = 4; d[0xCD] = 8; d[0xCE] = 4; d[0xCF] = 8;
        d[0xD2] = 4; d[0xD3] = 8; d[0xD4] = 0; d[0xD6] = 1;
        *(float *)(d + 0x2A8) = *(unsigned char *)(d + 0x34);
        d[0x28] = 3;
        *(int *)(d + 0x30) = 0; *(int *)(d + 0x258) = 0; *(int *)(d + 0x26C) = 0;
        qzero(d + 0x230);
        qcopy(d + 0x220, g_path_list[*(int *)(d + 0x274)] + 0x10);
        moby_set_state((char *)obj, 1, 0);
        if (obj[0x43] != 1) func_PAL_002A7E68((char *)obj, 1, 0, 0);
        obj[0x30] = 0x80; *(short *)(obj + 0x32) = 0x80;
        path_l01_compute_segment_lengths(g_path_list[*(int *)(d + 0x274)]);
        path_l01_compute_segment_lengths(g_path_list[*(int *)(d + 0x270)]);
        mem_clear(d + 0x2B0, 0, 0x80);
    }
    *(int *)(d + 0x258) = actor_choose_path_goal((char *)obj);
    *(float *)(obj + 0x2C) = *(float *)(*(char **)(obj + 0x24) + 0x24);
    old = obj[0x95];
    hit = func_PAL_002B1A50((char *)obj, d + 0x60, 0);
    if (hit) {
        trigger_linked_object((char *)obj);
        if (hit < 4) PlayMobySound(2, 0, (char *)obj);
        if (old == 1) *(int *)(d + 0x24C) = ((s32)(math_random_int_range(300, 360)) * 5 + 2) / 6;
        if ((unsigned int)(hit - 4) < 2) moby_set_state((char *)obj, 8, -1);
    }
    if (*(unsigned short *)(d + 0x98) & 3) *(int *)(obj + 0x98) = 0;
    math_update_wrapped_angle_offset((char *)obj, d + 0x280, d + 0x284, .3f, 0.027925273f, -1);
    moby_scale_owner_words_by_angles((char *)obj, d + 0x288, d + 0x28C, .1047197655f, 0.0062831864f, 0.007330384f);
    return 0;
}
