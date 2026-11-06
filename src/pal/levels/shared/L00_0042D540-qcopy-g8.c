#include "include_asm.h"
#include "common.h"

typedef int TI128 __attribute__((mode(TI)));
typedef union { TI128 q; float f[4]; s32 w[4]; } V4_F42D540;

extern float D_L00_001B1630[];
typedef struct { u8 pad[0x80]; V4_F42D540 pos; } HeroView_F42D540;
typedef struct { u8 pad[0x140]; V4_F42D540 pos; u8 pad150[8]; float yaw; } CamView_F42D540;
extern HeroView_F42D540 D_00189E20;
extern CamView_F42D540 D_L00_001B8C80;

extern void func_00283098(void *, void *, void *);
extern void func_00282CC0(void *, void *, void *);
extern void func_L00_002D7958(void *, void *, float);
extern void func_L00_00427BE8(char *, void *, float, void *);
extern float func_00283B98(float, float);
extern float func_00283248(float, float);
extern float func_00283C80(float, float);
extern float func_00282E80(void *, void *);
extern void func_00300190(void *, void *);

/* func_PAL_L00_0042D540, the PAL copy of func_L00_00428000: the same C, where the smaller of the
   hero's and partner's distances becomes the hero's distance alone. */

/* Camera follow step for a target object: aims at a point offset from the target and
   adjusts the orbit by the hero's distance; returns 0 on the easing path, else 1. */
int func_PAL_L00_0042D540(char *self, char *target)
{
    V4_F42D540 offset, pos;
    char *cam = *(char **)(self + 0x70);
    float *orbit = (float *)(cam + 0x64);
    char *info;
    float angle;
    float d;

    *(char **)(cam + 0xF4) = target;
    if (target != 0) {
        offset.q = 0;
        offset.f[0] = D_L00_001B1630[0];
        offset.f[2] = 0.12f;
        info = *(char **)(target + 0x68);
        func_00283098(&offset, &offset, target + 0xC0);
        func_00282CC0(&pos, target + 0x10, &offset);
        if (*(int *)(info + 0x10) == -1) {
            func_L00_002D7958(orbit, self + 0x50, 0.0f);
            orbit[2] = 6.0f;
            orbit[1] = orbit[3];
            orbit[3] = 0.0f;
            func_L00_00427BE8(self, orbit, 0.0f, &pos);
        }
        if (*(int *)(info + 0x10) <= 0) {
            *(float *)(cam + 0xAC) = func_00283B98(*(float *)(cam + 0xAC), *(float *)(info + 0x18));
            *(float *)(info + 0x18) *= 0.97f;
            angle = func_00283C80(func_00283248(D_L00_001B8C80.pos.f[0] - D_00189E20.pos.f[0],
                                                D_L00_001B8C80.pos.f[1] - D_00189E20.pos.f[1]),
                                  D_L00_001B8C80.yaw);
            d = func_00282E80(&D_00189E20.pos, &D_L00_001B8C80.pos);
            if (d < 0.77f) {
                if (angle < 1.5707965f) {
                    *(float *)(cam + 0x1C) -= 0.7f - d;
                    *(int *)(info + 4) = 0;
                } else {
                    *(float *)(cam + 0x1C) += 0.7f - d;
                }
            } else {
                *(float *)(cam + 0x1C) += *(float *)(info + 4);
                *(float *)(info + 4) *= 0.97f;
            }
            qcopy(cam + 0x80, &pos);
            func_00300190(cam + 0x80, cam + 0x80);
            return 0;
        }
        *(float *)(cam + 0xAC) = *(float *)(target + 0xF0) * 0.5f;
        *(float *)(cam + 0x20) += (*(float *)(target + 0xF4) - *(float *)(cam + 0x20)) * 0.05f;
        qcopy(cam + 0x80, &pos);
        qcopy(cam + 0xC0, target + 0xF0);
    }
    return 1;
}
