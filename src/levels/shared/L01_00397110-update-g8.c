#include "common.h"
extern void pushable_moby_update(void *, void *, int, float, float, float);
extern float IntToFloat(int);
extern int PulseColor(int, int, float);
extern void FastVecSub(void *, void *, void *);
extern void mat_combine_and_store(void *, void *, void *, void *);
extern char *D_0018A3E0 NOT_SDA;
extern int g_current_map_index;
extern unsigned short D_0018CCB8 NOT_SDA;
extern int D_L01_001B2088 __attribute__((sda));
extern int D_L01_001B05C0 __attribute__((sda));
extern int D_L01_001B05C4;
/* Moves a path-following moby along its route and carries anything riding on it. */
void path_platform_update(unsigned char *moby) {
    float pos[4], rot[4], delta[4];
    char *vars = *(char **)(moby + 0x68);
    qcopy_nc(pos, moby + 0x10);
    qcopy_nc(rot, moby + 0xF0);
    switch ((unsigned char)moby[0x20]) {
    case 0:
    *(unsigned short *)(moby + 0x34) |= 0x1000;
    *(int *)(vars + 0xDC) |= 1;
    moby[0x20] = 1;
    if (*(short *)(moby + 0xAA) == 0xE2A /* moby class 3626 */) *(float *)(vars + 0x88) = 12.0f;
    break;
    case 1: {
    float scale = *(float *)(moby + 0x2C)/ *(float *)(*(char **)(moby + 0x24) + 0x24);
    pushable_moby_update(moby, vars + 0x50, *(int *)(vars + 0xE0), *(float *)(vars + 0xEC)*scale, *(float *)(vars + 0xE4)*scale, *(float *)(vars + 0xE8)*scale);
    if (D_0018A3E0 == moby && g_current_map_index == 2) D_0018CCB8 = 0xFFFF;
    break;
    }
    }
    if ((unsigned char)moby[0x31]) {
    float angle = IntToFloat(D_L01_001B2088%60);
    angle = angle*6.2831854820251465f/IntToFloat(60)-3.1415927410125732f;
    *(int *)(moby + 0x78) = PulseColor(D_L01_001B05C0, D_L01_001B05C4, angle);
    }
    FastVecSub(delta, moby + 0x10, pos);
    mat_combine_and_store(vars + 0xA0, delta, rot, moby + 0xF0);
}
