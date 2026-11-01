#include "include_asm.h"

#include "common.h"
typedef struct {
    char pad0[0x30];
    int owner;
    short pad34;
    short x36;
    float x38;
    float x3C;
    char pad40[0x1C];
    int x5C;
    float x60;
    float x64;
    int x68;
    float x6C;
    float x70;
    int x74;
    int x78;
} Vars003158A8;
extern char *func_0029EFD0(int kind);
extern void func_00282C88(void *v);
extern float func_002A7878(float lo, float hi);
extern int D_001B1688;
extern void func_002A0F48(void *moby);

unsigned char *func_PAL_00316D98(int owner, void *pos) {
    unsigned char *obj = (unsigned char *)func_0029EFD0(0x81F);
    Vars003158A8 *data;

    if (obj) {
        *(float *)(obj + 0x2C) *= 0.5f;
        data = *(Vars003158A8 **)(obj + 0x68);
        obj[0x30] = 255;
        *(short *)(obj + 0x32) = 127;
        obj[0x31] = 1;
        obj[0x20] = 1;
        data->owner = owner;
        data->x36 = 0;
        data->x78 = 0;
        qcopy(obj + 0x10, pos);
        func_00282C88(data);
        data->x38 = func_002A7878(0.020943955f, 0.062831864f);
        data->x3C = func_002A7878(0.020943955f, 0.062831864f);
        data->x6C = data->x70 = data->x60 = data->x64 = 0.0f;
        data->x74 = 0;
        data->x5C = D_001B1688;
        data->x68 = -1;
        *(int *)(obj + 0x98) = 0;
        func_002A0F48(obj);
    }
    return obj;
}
