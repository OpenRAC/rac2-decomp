#include "common.h"

extern float D_L09_001B0F28 __attribute__((sda));
extern float D_L09_001B0F2C __attribute__((sda));
extern int D_L09_001B0F40 __attribute__((sda));
extern float func_00282E80(void *, void *);
extern int func_00282978(void *);
extern int func_L09_003F9568(void *, int, int, int);
extern void func_0029FCC0(void *, int, void *);
extern void func_00282CF0(float *, const float *, const float *);
extern void func_00282F20(float *, float *, float);
extern int func_002E5CF8(int, int, void *);
extern char *func_L09_003A06B0(void *, float, void *, void *);

typedef struct { char gap[0x2F0]; char *parts[2]; } Parts9708;

/* Fire from a valid linked part after its timer and parent flags permit it. */
void func_L09_003F9708(char *obj)
{
    float pos[4] __attribute__((aligned(16)));
    float dir[4] __attribute__((aligned(16)));
    char *state = *(char **)(obj + 0x68);
    char *parent;
    int close = 1;
    int side, shift;
    if (!(vec_distance_xy(obj + 0x10, *(char **)(state + 0x200)+0x10) < D_L09_001B0F2C))
        close = 0;
    if (!*(int *)(state + 0x2F8) || !FastDecTimer(state + 0x2E4))
        return;
    side = (*(unsigned short *)(obj + 0x96) / D_L09_001B0F40) & 1;
    shift = side ? 5 : 4;
    if (!((*(unsigned short *)(*(char **)(state + 0x2F8)+0x7C) >> shift) & 1))
        goto invalid;
    if (!func_L09_003F9568(obj, 1, 0, *(u8 *)(state + 0x30D) != 0))
        return;
    parent = ((Parts9708 *)state)->parts[side];
    if (!parent || *(short *)(parent + 0xAA) != 0xD66)
        return;
    if (*(u8 *)(parent + 0x20) == 0xFE)
        return;
    if (*(u8 *)(parent + 0x20) == 0xFD)
        return;
    {
        *(short *)(state + 0x2E4) = D_L09_001B0F40;
        func_0029FCC0(((Parts9708 *)state)->parts[side], 0, pos);
        FastVecSub(dir, (float *)(state + 0x1F0), pos);
        vec_scale_to_length(dir, dir, D_L09_001B0F28 * 0.016666668f);
        if (!close && !*(u8 *)(state + 0x30D)) {
            if (dir[2] > 0.033333335f)
                dir[2] = 0.033333335f;
            else if (dir[2] < -0.033333335f)
                dir[2] = -0.033333335f;
        }
        vec_scale_to_length(dir, dir, D_L09_001B0F28 * 0.016666668f);
        PlayMobySound(1, 0, *(void **)(state + 0x2F8));
        func_L09_003A06B0(obj, (float)*(u8 *)(state + 0x34), dir, pos);
    }
    return;
invalid:
    *(short *)(state + 0x2E4) = D_L09_001B0F40;
}
