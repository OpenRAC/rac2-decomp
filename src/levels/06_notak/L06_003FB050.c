#include "common.h"
typedef int VectorBits __attribute__((mode(TI)));
typedef float Vector[4] __attribute__((aligned(16)));
extern char D_00188660[];
typedef struct { unsigned char prefix[0x80]; Vector position; } PlayerPosition;
extern PlayerPosition D_00189E20;
extern char *D_L06_001BFC98;
extern int D_L06_001B2348 MACRO_ADDR;
extern void func_002E59F8(int);
extern int func_002E5CF8(int, int, void *);
extern int func_L00_00324120(void *);
extern void func_002A7750(void *, int, int);
extern int func_00277258(void *, int, void *, float);
extern void func_002AA548(void *, void *, float, float, float, float);
extern void func_00282CF0(void *, void *, void *);
extern void func_002AD6F0(void *, void *, void *, void *);

/* Raise and lower a platform while maintaining its motion sound. */
void func_L06_003FB050(char *moby)
{
    Vector oldPosition, oldRotation, delta;
    char *state = *(char **)(moby + 0x68);
    int handle, phase, brightness;
    float time, wave;
    unsigned int selection;
    qcopy(oldPosition, (moby + 0x10));
    qcopy(oldRotation, (moby + 0xF0));
    selection = *(unsigned char *)(moby + 0x20);
    switch (selection) {
    case 0:
    *(int *)(state + 0x7C) = *(int *)(state + 0x78);
    *(int *)(state + 0x5C) |= 1;
    qcopy((state + 0x90), (moby + 0x10));
    qcopy((state + 0x80), (state + 0x90));
    *(float *)(state + 0x88) = *(float *)(state + 0x98) - *(float *)(state + 0x68);
    *(int *)(state + 0x60) = *(int *)(state + 0x74);
    *(unsigned char *)(moby + 0x20) = 1;
    *(int *)(state + 0xB0) = -1;
    *(int *)(state + 0x64) = 0;
    goto done;
    case 1:
    handle = *(int *)(state + 0xB0);
    if (handle != -1) {
        char *sound = D_00188660 + handle * 0x70;
        if (*(char **)(sound + 0x88) == moby && *(unsigned char *)(sound + 0x74))
            func_002E59F8(handle);
    }
    *(int *)(state + 0xB0) = -1;
    if (func_L00_00324120(moby)) {
        if (*(float *)(moby + 0x18) == *(float *)(state + 0x98))
            func_002A7750(moby, 2, -1);
        else
            func_002A7750(moby, 3, -1);
    }
    if (*(float *)(moby + 0x18) - D_00189E20.position[2] > 3.0f &&
        *(float *)(moby + 0x18) == *(float *)(state + 0x98))
        func_002A7750(moby, 2, -1);
    else if (*(float *)(moby + 0x18) - D_00189E20.position[2] < -3.0f &&
             *(float *)(moby + 0x18) == *(float *)(state + 0x88))
        func_002A7750(moby, 3, -1);
    goto done;
    case 2:
    if (*(float *)(moby + 0x18) <= *(float *)(state + 0x88)) {
    handle = *(int *)(state + 0xB0);
    if (handle != -1) {
        char *sound = D_00188660 + handle * 0x70;
        if (*(char **)(sound + 0x88) == moby && *(unsigned char *)(sound + 0x74))
            func_002E59F8(handle);
    }
    *(int *)(state + 0xB0) = -1;
        if (!func_L00_00324120(moby))
            *(unsigned char *)(moby + 0x20) = 1;
        goto done;
    }
    if (func_00277258(moby + 0x10, 1, moby, 2.1f) &&
        !(*(float *)(moby + 0x18) <= D_00189E20.position[2]) &&
        (!D_L06_001BFC98 || *(short *)(D_L06_001BFC98 + 0xAA) != 0xEA3))
        goto stop;
    {
        char *sound = D_00188660 + *(int *)(state + 0xB0) * 0x70;
    if (*(char **)(sound + 0x88) != moby || !*(unsigned char *)(sound + 0x74))
        *(int *)(state + 0xB0) = func_002E5CF8(0, 4, moby);
    }
    func_002AA548(moby + 0x18, state + 0x64, *(float *)(state + 0x88),
                  0.001944444492f, 0.001666666707f, 0.1000000089f);
    goto done;
    case 3:
    func_002AA548(moby + 0x18, state + 0x64, *(float *)(state + 0x98),
                  0.001944444492f, 0.001666666707f, 0.1000000089f);
    if (*(float *)(moby + 0x18) >= *(float *)(state + 0x98)) {
    handle = *(int *)(state + 0xB0);
    if (handle != -1) {
        char *sound = D_00188660 + handle * 0x70;
        if (*(char **)(sound + 0x88) == moby && *(unsigned char *)(sound + 0x74))
            func_002E59F8(handle);
    }
    *(int *)(state + 0xB0) = -1;
        if (!func_L00_00324120(moby)) {
            *(int *)(state + 0x60) = *(int *)(state + 0x74);
            (*(int *)(state + 0x78))--;
            *(unsigned char *)(moby + 0x20) = 1;
        }
    } else {
        char *sound = D_00188660 + *(int *)(state + 0xB0) * 0x70;
        if (*(char **)(sound + 0x88) != moby || !*(unsigned char *)(sound + 0x74))
            *(int *)(state + 0xB0) = func_002E5CF8(0, 4, moby);
    }
    goto done;
stop:
    case 4:
    handle = *(int *)(state + 0xB0);
    if (handle != -1) {
        char *sound = D_00188660 + handle * 0x70;
        if (*(char **)(sound + 0x88) == moby && *(unsigned char *)(sound + 0x74))
            func_002E59F8(handle);
    }
    *(int *)(state + 0xB0) = -1;
    }
done:
    time = (float)D_L06_001B2348 * (1.0f / 60.0f);
    phase = (int)time;
    wave = time - (float)phase;
    if (!(phase & 1))
        wave = 1.0f - wave;
    brightness = (int)(wave * 255.0f);
    {
        int hi = (brightness << 8) | 0x7F000000;
        int mid = (brightness << 16) | hi;
        *(int *)(moby + 0x78) = mid | brightness;
    }
    func_00282CF0(delta, moby + 0x10, oldPosition);
    func_002AD6F0(state + 0x20, delta, oldRotation, moby + 0xF0);
}
