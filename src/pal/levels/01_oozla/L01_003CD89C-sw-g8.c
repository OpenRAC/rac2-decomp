#include "include_asm.h"

#include "common.h"
extern void func_00282F20(void *, void *, float);
extern void func_00282CF0(void *, void *, void *);
extern void func_00282CC0(void *, void *, void *);
extern float func_00283180(float);
extern int func_00282948(void *);
extern void func_002A8598(int, int);
extern void func_00291450(int);
typedef struct { char pad[0x30]; float position[4]; char rest[0x40]; } L01_003C9D00_PATH;
extern L01_003C9D00_PATH *D_L01_001B264C;
extern char D_L01_001C7640[];
extern float func_00282E48(void *);
extern void func_002A7750(void *, int, int);
extern int func_00283DB8(void *, float);
extern int func_L00_002FCF18(void *, float, float, float, float, float);
extern void func_L00_002E6CF0(void *, void *);
extern void func_002AD6F0(void *, void *, void *, void *);
extern void func_L01_003C97D8(void *);

void func_PAL_L01_003CDDC8(char *obj)
{
    float vec[4];
    char *s = *(char **)(obj + 0x68);
    float blend = 0.0f;
    switch (*(unsigned char *)(obj + 0x20)) {
    case 0:
        *(int *)(s + 0x90) = -1;
        *(int *)(s + 0x5C) |= 4;
        *(float *)(s + 0x70) = 0.0f;
        *(int *)(s + 0x6C) = 0;
        *(float *)(s + 0x74) = 0.0f;
        *(int *)(obj + 0x98) = 0;
        qcopy(s + 0x80, obj + 0x10);
        *(float *)(s + 0x98) = func_00282E48(D_L01_001B264C[*(int *)(s + 0x94)].position);
        func_002A7750(obj, 1, -1);
        break;
    case 1:
        if (*(unsigned char *)(obj + 0xBC)) {
            *(int *)(obj + 0x98) = *(int *)(*(char **)(obj + 0x24) + 0x10);
            func_002A7750(obj, 2, -1);
        }
        break;
    case 2:
        *(float *)(s + 0x70) += 1.0f / *(float *)(s + 0x60);
        if (*(float *)(s + 0x70) > 1.0f) *(float *)(s + 0x70) = 1.0f;
        else if (*(float *)(s + 0x70) < 0.0f) *(float *)(s + 0x70) = 0.0f;
        blend = (1.0f - func_00283180(*(float *)(s + 0x70) * 3.1415927f)) * 0.5f;
        if (*(int *)(s + 0x94) == -1) {
            func_00282F20(vec, obj + 0xC0, blend * 10.0f);
            func_00282CF0(obj + 0x10, s + 0x80, vec);
        } else {
            func_00282CF0(vec, D_L01_001B264C[*(int *)(s + 0x94)].position, s + 0x80);
            func_00282F20(vec, vec, *(float *)(s + 0x98) * blend);
            func_00282CC0(obj + 0x10, s + 0x80, vec);
        }
        if (*(float *)(s + 0x70) >= 1.0f) {
            *(int *)(s + 0x6C) = *(int *)(s + 0x64);
            func_002A7750(obj, 3, -1);
        }
        break;
    case 3:
        blend = 1.0f;
        if (func_00282948(s + 0x6C)) func_002A7750(obj, 4, -1);
        break;
    case 4:
        *(float *)(s + 0x70) -= 1.0f / *(float *)(s + 0x60);
        if (*(float *)(s + 0x70) > 1.0f) *(float *)(s + 0x70) = 1.0f;
        else if (*(float *)(s + 0x70) < 0.0f) *(float *)(s + 0x70) = 0.0f;
        blend = (1.0f - func_00283180(*(float *)(s + 0x70) * 3.1415927f)) * 0.5f;
        if (*(int *)(s + 0x94) == -1) {
            func_00282F20(vec, obj + 0xC0, blend * 10.0f);
            func_00282CF0(obj + 0x10, s + 0x80, vec);
        } else {
            func_00282CF0(vec, D_L01_001B264C[*(int *)(s + 0x94)].position, s + 0x80);
            func_00282F20(vec, vec, *(float *)(s + 0x98) * blend);
            func_00282CC0(obj + 0x10, s + 0x80, vec);
        }
        if (*(float *)(s + 0x70) <= 0.0f) {
            *(int *)(obj + 0x98) = 0;
            func_002A8598(*(unsigned char *)(obj + 0x21), 0);
            func_002A7750(obj, 1, -1);
        }
        break;
    }
    *(unsigned char *)(obj + 0xBC) = 0;
    if ((unsigned int)(*(unsigned char *)(obj + 0x20) - 2) < 3) {
        func_L00_002E6CF0(func_L01_003C97D8, obj);
        func_00282F20(vec, obj + 0xC0, *(float *)(s + 0x68) * ((float)*(int *)(s + 0x7C) * 0.020000001f));
        func_002AD6F0(s + 0x20, vec, obj + 0xF0, obj + 0xF0);
    }
    qcopy(vec, obj + 0x10);
    vec[3] = 10.0f;
    if (*(unsigned char *)(obj + 0x20) >= 2 && (*(unsigned char *)(obj + 0x31) || func_00283DB8(vec, 255.0f) != -1)) {
        if (*(int *)(s + 0x90) == -1) {
            *(int *)(s + 0x90) = func_L00_002FCF18(s + 0x80, 10.0f, 0.0f, blend * 0.8f, blend * 0.9f, blend * 1.1f);
        } else {
            char *light = D_L01_001C7640 + *(int *)(s + 0x90) * 32;
            *(float *)(light + 0) = blend * 0.8f;
            *(float *)(light + 4) = blend * 0.9f;
            *(float *)(light + 8) = blend * 1.1f;
        }
    } else if (*(int *)(s + 0x90) != -1) {
        func_00291450(*(int *)(s + 0x90));
        *(int *)(s + 0x90) = -1;
    }
}
