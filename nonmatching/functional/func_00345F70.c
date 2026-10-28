/* functional: medium. Same reads, writes and calls in retail order, checked on one captured state (one mode only); the offset table is read through one array declaration where retail reads some entries gp-relative and some absolute, which reaches the same words. */
#include "include_asm.h"

extern int func_002A9588(unsigned int, unsigned int, int, int, int);
extern int *func_00335E20(void *);
extern void func_00335E38(void *, float, float, float, float);
extern void func_003458F8(void *, int);
extern void func_00345B78(void *, int);
extern void func_00345D58(void *, int);
extern int D_00138344;
extern int D_001ADB10;
extern float D_001AE2A8[2];
extern float D_001AE3F0[];

#define OFS(base, o) ((float *)((char *)(base) + (o)))

int func_00345F70(char *obj, int buttons, int *out)
{
    float tmp[2];
    int mode;
    int *p;
    float *pos;

    *out = *(int *)(obj + 0x498);
    *(int *)(obj + 0x494) = 0;
    mode = *(int *)(obj + 0x498);
    D_001ADB10 = -1;
    tmp[0] = D_001AE2A8[0];
    tmp[1] = D_001AE2A8[1];
    if (mode == 1) {
        *out = mode;
        func_00345D58(obj, buttons);
    } else if (mode < 2) {
        if (mode == 0) {
            *out = 0;
            func_003458F8(obj, buttons);
        }
    } else if (mode == 3) {
        *out = mode;
        func_00345B78(obj, buttons);
    }
    if (D_00138344 & 0xF000)
        func_002A9588(0, 0, 1, 0, 1);
    p = func_00335E20(obj + 0x17C);
    *p = func_002A9588(0x60442D00, 0x70FFFEED, 0x14, 0, 0);

    pos = *(float **)(obj + 0x400);
    func_00335E38(obj, D_001AE3F0[0] + pos[0], D_001AE3F0[1] + pos[1], 0.0f, 0.0f);
    pos = *(float **)(obj + 0x400);
    func_00335E38(obj + 0x4C, D_001AE3F0[8] + pos[0], D_001AE3F0[9] + pos[1], 0.0f, 0.0f);
    pos = *(float **)(obj + 0x400);
    func_00335E38(obj + 0x98, D_001AE3F0[2] + pos[0], D_001AE3F0[3] + pos[1], 0.0f, 0.0f);
    pos = *(float **)(obj + 0x400);
    func_00335E38(obj + 0xE4, D_001AE3F0[4] + pos[0], D_001AE3F0[5] + pos[1], 0.0f, 0.0f);
    pos = *(float **)(obj + 0x400);
    func_00335E38(obj + 0x130, D_001AE3F0[6] + pos[0], D_001AE3F0[7] + pos[1], 0.0f, 0.0f);
    pos = *(float **)(obj + 0x400);
    func_00335E38(obj + 0x1C8, tmp[0] + pos[0], tmp[1] + pos[1], 0.0f, 0.0f);
    pos = *(float **)(obj + 0x400);
    func_00335E38(obj + 0x2E0, D_001AE3F0[12] + pos[0], D_001AE3F0[13] + pos[1], 0.0f, 0.0f);
    pos = *(float **)(obj + 0x400);
    func_00335E38(obj + 0x298, D_001AE3F0[10] + pos[0], D_001AE3F0[11] + pos[1], 0.0f, 0.0f);
    pos = *(float **)(obj + 0x400);
    func_00335E38(obj + 0x328, D_001AE3F0[14] + pos[0], D_001AE3F0[15] + pos[1], 0.0f, 0.0f);
    pos = *(float **)(obj + 0x400);
    func_00335E38(obj + 0x370, D_001AE3F0[16] + pos[0], D_001AE3F0[17] + pos[1], 0.0f, 0.0f);
    pos = *(float **)(obj + 0x400);
    func_00335E38(obj + 0x3B8, D_001AE3F0[18] + pos[0], D_001AE3F0[19] + pos[1], 0.0f, 0.0f);
    return 0;
}
