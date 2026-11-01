#include "include_asm.h"

#include "common.h"
extern char *func_0029EFD0(int);
extern char D_L05_001B96C0[];
extern void func_002AFFD8(void *, void *, int);
extern void func_00282DD8(void *, void *, void *);
extern int func_00283DB8(void *, float);
extern float func_00282E48(void *, void *);
extern float func_00282DB0(void *, void *);
extern float func_002831B0(float);
extern void func_PAL_L05_0042A900(void *, void *);
extern void func_00282CF0(float *, void *, float *);
extern void func_00282F20(float *, float *, float);

/* Creates a camera-facing burst, sets its lifetime and colors, and shakes
   the camera when a visible burst is nearby. */
char *func_PAL_L05_0042A240(void *pos, int shake, int c20, int c24, int c28,
                         int c2c, int c30, int unused, int c34, int mode,
                         int c38, float scale)
{
    float toward[4], up[4], sphere[4], cameraDir[4];
    char *obj = func_0029EFD0(0x116A);
    char *st;

    if (obj) {
        st = *(char **)(obj + 0x68);
        *(unsigned char *)(obj + 0x30) = 255;
        *(unsigned short *)(obj + 0x32) = 255;
        obj[0x20] = 0;
        qcopy(obj + 0x10, pos);
        *(float *)(obj + 0x1C) = 1.0f;
        func_00282CF0(toward, D_L05_001B96C0, (float *)(obj + 0x10));
        func_00282F20(toward, toward, 1.0f);
        func_002AFFD8(obj + 0x10, up, 1);
        qcopy(obj + 0xC0, toward);
        func_00282DD8(obj + 0xD0, obj + 0xC0, up);
        func_00282F20((float *)(obj + 0xD0), (float *)(obj + 0xD0), 1.0f);
        func_00282DD8(obj + 0xE0, obj + 0xD0, obj + 0xC0);
        *(float *)(obj + 0xCC) = *(float *)(obj + 0xDC) = *(float *)(obj + 0xEC) = 0.0f;
        *(short *)st = 50;
        *(short *)(st + 2) = 50;
        *(float *)(st + 8) = scale + scale;
        *(float *)(st + 0xC) = scale * 4.0f;
        *(int *)(st + 0x20) = c20;
        *(int *)(st + 0x24) = c24;
        *(int *)(st + 0x28) = c28;
        *(int *)(st + 0x2C) = c2c;
        *(int *)(st + 0x30) = c30;
        *(int *)(st + 0x34) = c34;
        *(int *)(st + 0x1C) = mode;
        *(int *)(st + 0x38) = c38;
        *(float *)(st + 0x14) = scale;
        *(int *)(st + 0x18) = 0;
        qcopy(sphere, obj + 0x10);
        sphere[3] = scale * 3.0f;
        if (func_00283DB8(sphere, 128.0f) == 1) {
            *(short *)(st + 4) = 8;
            *(float *)(st + 0x10) = 0.125f;
            if (func_00282E48(pos, D_L05_001B96C0) < 48.0f && shake) {
                char *mgr = D_L05_001B96C0 - 0x140;

                *(int *)(mgr + 0x16C) = 0;
                *(int *)(mgr + 0x168) = 33;
                *(float *)(mgr + 0x160) = 0.075f;
            }
            if (*(int *)(st + 0x18)) {
                func_00282CF0(cameraDir, obj + 0x10, (float *)D_L05_001B96C0);
                func_00282F20(cameraDir, cameraDir, 1.0f);
                if (1.5707964f - func_002831B0(func_00282DB0(cameraDir, D_L05_001B96C0 + 0x230)) < 0.45378566f)
                    *(int *)(st + 0x18) = 1;
                else
                    *(int *)(st + 0x18) = 0;
            }
        } else {
            *(short *)(st + 4) = 0;
            *(int *)(st + 0x18) = 0;
        }
        func_PAL_L05_0042A900(obj, up);
    }
    return obj;
}

