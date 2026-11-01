#include "include_asm.h"

#include "common.h"
extern char *D_L01_001FE180[];
extern float func_002A7878(float, float);
extern int func_001163B0(void);
extern void func_PAL_002A7E68(void *, int, int, int);
extern void func_00282CC0(void *, void *, void *);
extern int D_L01_001B2088;
typedef struct {
    char pad[0x2C];
    float radius;
} L01RadiusRecord;
extern L01RadiusRecord *D_L01_001B21C0;
extern char D_L01_001AFE38[] SDATA(D_L01_001AFE38);
extern void func_L01_003BD5E8(void *);
extern int func_00283CF0(float);
extern void func_L01_003377C8(void *);
extern void func_002A7750(void *, int, int);

void func_PAL_L01_003C12C8(char *obj)
{
    char *state = *(char **)(obj + 0x68);
    float value;
    L01RadiusRecord *record;

    if (!D_L01_001B2088) **(int **)(state + 0x250) = 0;
    qcopy(state + 0x1D0, obj + 0x10);
    func_L01_003BD5E8(obj);
    value = 0.0f;
    *(unsigned char *)(state + 0x48) = func_00283CF0(10.0f);
    *(unsigned char *)(state + 0x4A) = func_00283CF0(4.0f);
    *(unsigned char *)(state + 0x200) = *(unsigned char *)(obj + 0x30);
    if (*(int *)(state + 0x294) != -1) {
        record = D_L01_001B21C0;
        record += *(int *)(state + 0x294);
        value = record->radius;
    }
    if (value > 0.0f) *(unsigned char *)(obj + 0x30) = func_00283CF0(value + 2.0f);
    *(unsigned char *)(state + 0x200) = *(unsigned char *)(state + 0x201) = *(unsigned char *)(obj + 0x30);
    if (*(int *)(state + 0x298) != -1) {
        record = D_L01_001B21C0;
        record += *(int *)(state + 0x298);
        value = record->radius;
    }
    if (value > 0.0f) *(unsigned char *)(state + 0x200) = func_00283CF0(value + 2.0f);
    if (*(int *)(state + 0x210) != -1) func_L01_003377C8(D_L01_001FE180[*(int *)(state + 0x210)]);
    if (*(int *)(state + 0x214) != -1) func_L01_003377C8(D_L01_001FE180[*(int *)(state + 0x214)]);
    *(char **)(state + 0x10) = state + 0x50;
    *(unsigned char *)(state + 0x60) = 9;
    *(float *)(state + 0x80) = 0.3f;
    *(float *)(state + 0x8C) = 0.4f;
    *(unsigned char *)(state + 0xC6) = 1;
    *(unsigned char *)(state + 0x69) = 1;
    *(short *)(state + 0x88) = 0;
    *(unsigned char *)(state + 0x6A) = 0;
    *(int *)(state + 0x98) = 0;
    *(float *)(state + 0x84) = 0.0f;
    *(int *)(state + 0x220) = 0;
    *(unsigned char *)(state + 0x28) = 0;
    *(float *)(state + 0x30) = 0.0f;
    qcopy(state + 0x1E0, obj + 0x10);
    *(float *)(state + 0x240) = 0.0f;
    *(float *)(state + 0x24C) = func_002A7878(0.0f, 1.0f);
    *(float *)(state + 0x26C) = func_002A7878(-3.1415927f, 3.1415927f);
    *(float *)(state + 0x270) = func_002A7878(-3.1415927f, 3.1415927f);
    *(float *)(state + 0x274) = func_002A7878(-3.1415927f, 3.1415927f);
    *(float *)(state + 0x260) = func_002A7878(-3.1415927f, 3.1415927f) * 0.0003490659f;
    *(float *)(state + 0x264) = func_002A7878(-3.1415927f, 3.1415927f) * 0.0003490659f;
    *(float *)(state + 0x268) = func_002A7878(-3.1415927f, 3.1415927f) * 0.0003490659f;
    *(void **)(state + 0x190) = D_L01_001AFE38;
    *(float *)(state + 0x1C0) = *(float *)(*(char **)(obj + 0x24) + 0x24);
    *(float *)(state + 0x1B0) = *(float *)(state + 0x30);
    *(short *)(state + 0x202) = -1;
    *(float *)(state + 0x204) = 0.0f;
    *(int *)(state + 0x290) = 0;
    *(unsigned short *)(obj + 0x34) = *(unsigned short *)(obj + 0x34) | (func_001163B0() & -0x8000);
    *(float *)(state + 0x22C) = 0.0f;
    *(int *)(state + 0xCC) = *(int *)(state + 0x214);
    *(int *)(state + 0x29C) = *(int *)(state + 0x294);
    switch (*(int *)(state + 0x208)) {
    case 0:
        *(float *)(obj + 0x18) = *(float *)(state + 0x224) - 1.7f;
        qcopy(state + 0x1D0, obj + 0x10);
        qzero_nc(state + 0x1F0);
        *(unsigned short *)(obj + 0x34) &= 0xEFFF;
        if (*(unsigned char *)(obj + 0x43) != 1) func_PAL_002A7E68(obj, 1, 0, 3);
        func_002A7750(obj, 1, -1);
        break;
    case 1:
        *(float *)(obj + 0x18) = *(float *)(state + 0x224);
        *(float *)(obj + 0x18) += *(float *)(state + 0x24C) + 1.7f;
        qcopy(state + 0x1D0, obj + 0x10);
        qzero_nc(state + 0x1F0);
        *(unsigned short *)(obj + 0x34) |= 0x1000;
        if (*(unsigned char *)(obj + 0x43) != 1) func_PAL_002A7E68(obj, 1, 0, 3);
        func_002A7750(obj, 6, 0);
        break;
    case 2:
        qcopy(state + 0x1F0, state + 0xD0);
        func_00282CC0(obj + 0x10, obj + 0x10, state + 0x1F0);
        qcopy(state + 0x1D0, obj + 0x10);
        if (*(unsigned char *)(obj + 0x43) != 5) func_PAL_002A7E68(obj, 5, 0, 3);
        *(unsigned short *)(obj + 0x34) |= 0x1000;
        func_002A7750(obj, 4, -1);
        break;
    }
}
