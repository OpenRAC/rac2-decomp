#include "include_asm.h"

#include "common.h"
extern void pushable_moby_update_pal(void *, void *, int, float, float, float);
extern float IntToFloat(int);
extern int PulseColor(int, int, float);
extern void FastVecSub(void *, void *, void *);
extern void mat_combine_and_store(void *, void *, void *, void *);
extern char *g_target_moby NOT_SDA;
extern int g_current_map_index;
extern unsigned short g_path_platform_id NOT_SDA;
extern int g_oozla_intro_stage __attribute__((sda));
extern int g_platform_pulse_color_a __attribute__((sda));
extern int g_platform_pulse_color_b;

void func_PAL_L01_003D6ECC(unsigned char *m) {
    float pos[4], rot[4], delta[4];
    char *p = *(char **)(m + 0x68);
    qcopy_nc(pos, m + 0x10);
    qcopy_nc(rot, m + 0xF0);
    switch ((unsigned char)m[0x20]) {
    case 0:
    *(unsigned short *)(m + 0x34) |= 0x1000;
    *(int *)(p + 0xDC) |= 1;
    m[0x20] = 1;
    if (*(short *)(m + 0xAA) == 0xE2A) *(float *)(p + 0x88) = 12.0f;
    break;
    case 1: {
    float scale = *(float *)(m + 0x2C)/ *(float *)(*(char **)(m + 0x24) + 0x24);
    pushable_moby_update_pal(m, p + 0x50, *(int *)(p + 0xE0), *(float *)(p + 0xEC)*scale, *(float *)(p + 0xE4)*scale, *(float *)(p + 0xE8)*scale);
    if (g_target_moby == m && g_current_map_index == 2) g_path_platform_id = 0xFFFF;
    break;
    }
    }
    if ((unsigned char)m[0x31]) {
    float angle = IntToFloat(g_oozla_intro_stage%50);
    angle = angle*6.2831854820251465f/IntToFloat(50)-3.1415927410125732f;
    *(int *)(m + 0x78) = PulseColor(g_platform_pulse_color_a, g_platform_pulse_color_b, angle);
    }
    FastVecSub(delta, m + 0x10, pos);
    mat_combine_and_store(p + 0xA0, delta, rot, m + 0xF0);
}
