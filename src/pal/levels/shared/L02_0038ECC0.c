#include "include_asm.h"

INCLUDE_ASM("asm/pal/levels", func_PAL_L02_0038ECC0);


typedef unsigned char u8;
typedef unsigned int u32;
extern int D_001A79F0 __attribute__((sda));
extern float D_00189EA8;
extern u8 D_00188660[];
extern float D_L02_001BA500[4];
extern int func_002E5CF8(int, int, char *);
extern int func_00282978(void *);
extern u32 func_00283D38(u32, u32, float);
extern float func_00282E48(void *, void *);
extern void *func_L00_0033E220(void *, void *, u32, int, int, float, float, int, int, int);

void func_PAL_L02_0038FDC0(char *object) {
    char *data = *(char **)(object + 0x68);
    short kind = *(short *)(object + 0xAA);
    float distance;
    if (kind == 0x9B7 || kind == 0x9B0 || kind == 0xD2C || kind == 0xD5C) {
        if (D_001A79F0 != 13) {
            char *event = (char *)D_00188660 + *(int *)(data + 0x18) * 0x70;
            if (*(char **)(event + 0x88) != object || !((u8 *)event)[0x74])
                *(int *)(data + 0x18) = func_002E5CF8(0, 4, object);
        }
    }
    if (*(short *)(object + 0xAA) == 0xD2C) {
        if (func_00282978(data + 0x74)) {
            *(short *)(data + 0x74) = 29;
            *(int *)(data + 0x8C) = *(int *)(data + 0x8C) == 0;
        }
        *(u32 *)(object + 0x78) = func_00283D38(*(u32 *)(object + 0x78), 0x50000046, 0.18f);
    }
    if (D_001A79F0 == 13 && D_00189EA8 > 89.0f)
        return;
    kind = *(short *)(object + 0xAA);
    switch (kind) {
    case 0x9B0:
        distance = func_00282E48(D_L02_001BA500, object + 0x10);
        if (distance < (float)*(int *)(data + 0x90)) {
            func_L00_0033E220(data + 0x30, object, 0x40804040, -1, 0, *(float *)(data + 0x78) * 756000.0f, 0.5f, 2, 0, *(int *)(data + 0x90));
            func_L00_0033E220(data + 0x40, object, 0x40804040, -1, 0, *(float *)(data + 0x78) * 756000.0f, 0.5f, 2, 0, *(int *)(data + 0x90));
            func_L00_0033E220(data + 0x50, object, 0x40804040, -1, 0, *(float *)(data + 0x78) * 756000.0f, 0.5f, 2, 0, *(int *)(data + 0x90));
        }
        if (distance < (float)*(int *)(data + 0x94)) {
            func_L00_0033E220(data + 0x30, object, 0x20804040, -1, 1, *(float *)(data + 0x78) * 777000.0f, 0.6f, 2, 0, *(int *)(data + 0x94));
            func_L00_0033E220(data + 0x40, object, 0x20804040, -1, 1, *(float *)(data + 0x78) * 777000.0f, 0.6f, 2, 0, *(int *)(data + 0x94));
            func_L00_0033E220(data + 0x50, object, 0x20804040, -1, 1, *(float *)(data + 0x78) * 777000.0f, 0.6f, 2, 0, *(int *)(data + 0x94));
        }
        break;
    case 0x9B7:
        distance = func_00282E48(D_L02_001BA500, object + 0x10);
        if (distance < (float)*(int *)(data + 0x90)) {
            func_L00_0033E220(data + 0x30, object, 0x405696FF, -1, 0, *(float *)(data + 0x78) * 756000.0f, 0.5f, 2, 0, *(int *)(data + 0x90));
            func_L00_0033E220(data + 0x40, object, 0x405696FF, -1, 0, *(float *)(data + 0x78) * 756000.0f, 0.5f, 2, 0, *(int *)(data + 0x90));
        }
        if (distance < (float)*(int *)(data + 0x94)) {
            func_L00_0033E220(data + 0x30, object, 0x205696FF, -1, 1, *(float *)(data + 0x78) * 777000.0f, 0.6f, 2, 0, *(int *)(data + 0x94));
            func_L00_0033E220(data + 0x40, object, 0x205696FF, -1, 1, *(float *)(data + 0x78) * 777000.0f, 0.6f, 2, 0, *(int *)(data + 0x94));
        }
        break;
    case 0xB15:
        distance = func_00282E48(D_L02_001BA500, object + 0x10);
        if (distance < (float)*(int *)(data + 0x90)) {
            func_L00_0033E220(data + 0x30, object, 0x405696FF, -1, 0, *(float *)(data + 0x78) * 756000.0f, 0.5f, 2, 0, *(int *)(data + 0x90));
            func_L00_0033E220(data + 0x40, object, 0x405696FF, -1, 0, *(float *)(data + 0x78) * 756000.0f, 0.5f, 2, 0, *(int *)(data + 0x90));
        }
        if (distance < (float)*(int *)(data + 0x94)) {
            func_L00_0033E220(data + 0x30, object, 0x205696FF, -1, 1, *(float *)(data + 0x78) * 777000.0f, 0.6f, 2, 0, *(int *)(data + 0x94));
            func_L00_0033E220(data + 0x40, object, 0x205696FF, -1, 1, *(float *)(data + 0x78) * 777000.0f, 0.6f, 2, 0, *(int *)(data + 0x94));
        }
        break;
    case 0x134B:
        distance = func_00282E48(D_L02_001BA500, object + 0x10);
        if (distance < (float)*(int *)(data + 0x90)) {
            func_L00_0033E220(data + 0x30, object, 0x40804040, -1, 0, *(float *)(data + 0x78) * 340200.0f, 0.5f, 2, 0, *(int *)(data + 0x90));
            func_L00_0033E220(data + 0x40, object, 0x40804040, -1, 0, *(float *)(data + 0x78) * 340200.0f, 0.5f, 2, 0, *(int *)(data + 0x90));
        }
        if (distance < (float)*(int *)(data + 0x94)) {
            func_L00_0033E220(data + 0x30, object, 0x20804040, -1, 1, *(float *)(data + 0x78) * 194250.0f, 0.6f, 2, 0, *(int *)(data + 0x94));
            func_L00_0033E220(data + 0x40, object, 0x20804040, -1, 1, *(float *)(data + 0x78) * 194250.0f, 0.6f, 2, 0, *(int *)(data + 0x94));
        }
        break;
    case 0xB13:
        distance = func_00282E48(D_L02_001BA500, object + 0x10);
        if (distance < (float)*(int *)(data + 0x90)) {
            func_L00_0033E220(data + 0x30, object, 0x40804040, -1, 0, *(float *)(data + 0x78) * 756000.0f, 0.5f, 2, 0, *(int *)(data + 0x90));
            func_L00_0033E220(data + 0x40, object, 0x40804040, -1, 0, *(float *)(data + 0x78) * 756000.0f, 0.5f, 2, 0, *(int *)(data + 0x90));
        }
        if (distance < (float)*(int *)(data + 0x94)) {
            func_L00_0033E220(data + 0x30, object, 0x20804040, -1, 1, *(float *)(data + 0x78) * 777000.0f, 0.6f, 2, 0, *(int *)(data + 0x94));
            func_L00_0033E220(data + 0x40, object, 0x20804040, -1, 1, *(float *)(data + 0x78) * 777000.0f, 0.6f, 2, 0, *(int *)(data + 0x94));
        }
        break;
    case 0xD5C:
        distance = func_00282E48(D_L02_001BA500, object + 0x10);
        if (distance < (float)*(int *)(data + 0x90)) {
            func_L00_0033E220(data + 0x30, object, 0x40804040, -1, 0, *(float *)(data + 0x78) * 756000.0f, 0.5f, 2, 0, *(int *)(data + 0x90));
            func_L00_0033E220(data + 0x40, object, 0x40804040, -1, 0, *(float *)(data + 0x78) * 756000.0f, 0.5f, 2, 0, *(int *)(data + 0x90));
        }
        if (distance < (float)*(int *)(data + 0x94)) {
            func_L00_0033E220(data + 0x30, object, 0x20804040, -1, 1, *(float *)(data + 0x78) * 777000.0f, 0.6f, 2, 0, *(int *)(data + 0x94));
            func_L00_0033E220(data + 0x40, object, 0x20804040, -1, 1, *(float *)(data + 0x78) * 777000.0f, 0.6f, 2, 0, *(int *)(data + 0x94));
        }
        break;
    case 0x127D:
        distance = func_00282E48(D_L02_001BA500, object + 0x10);
        if (distance < (float)*(int *)(data + 0x90)) {
            func_L00_0033E220(data + 0x30, object, 0x40202080, -1, 0, *(float *)(data + 0x78) * 294000.0f, 0.5f, 2, 0, *(int *)(data + 0x90));
            func_L00_0033E220(data + 0x40, object, 0x40202080, -1, 0, *(float *)(data + 0x78) * 294000.0f, 0.5f, 2, 0, *(int *)(data + 0x90));
        }
        if (distance < (float)*(int *)(data + 0x94)) {
            func_L00_0033E220(data + 0x30, object, 0x205696FF, -1, 1, *(float *)(data + 0x78) * 231000.0f, 0.6f, 2, 0, *(int *)(data + 0x94));
            func_L00_0033E220(data + 0x40, object, 0x205696FF, -1, 1, *(float *)(data + 0x78) * 231000.0f, 0.6f, 2, 0, *(int *)(data + 0x94));
        }
        break;
    case 0x1290:
        distance = func_00282E48(D_L02_001BA500, object + 0x10);
        if (distance < (float)*(int *)(data + 0x90)) {
            func_L00_0033E220(data + 0x30, object, 0x40804020, -1, 0, *(float *)(data + 0x78) * 210000.0f, 0.5f, 2, 0, *(int *)(data + 0x90));
            func_L00_0033E220(data + 0x40, object, 0x40804020, -1, 0, *(float *)(data + 0x78) * 210000.0f, 0.5f, 2, 0, *(int *)(data + 0x90));
            func_L00_0033E220(data + 0x50, object, 0x40804020, -1, 0, *(float *)(data + 0x78) * 210000.0f, 0.5f, 2, 0, *(int *)(data + 0x90));
        }
        if (distance < (float)*(int *)(data + 0x94)) {
            func_L00_0033E220(data + 0x30, object, 0x20905010, -1, 1, *(float *)(data + 0x78) * 210000.0f, 0.6f, 2, 0, *(int *)(data + 0x94));
            func_L00_0033E220(data + 0x40, object, 0x20905010, -1, 1, *(float *)(data + 0x78) * 210000.0f, 0.6f, 2, 0, *(int *)(data + 0x94));
            func_L00_0033E220(data + 0x50, object, 0x20905010, -1, 1, *(float *)(data + 0x78) * 210000.0f, 0.6f, 2, 0, *(int *)(data + 0x94));
        }
        break;
    }
}


