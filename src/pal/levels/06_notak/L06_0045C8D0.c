#include "include_asm.h"



#include "common.h"
extern void func_00282CC0(char *, char *, char *);
extern int func_00283CF0(float);
extern void func_002A0488(char *, int, int, int);
extern void func_00282F20(char *, char *, float);
extern int D_L06_001B375C __attribute__((sda));
extern int D_L06_001B3758 __attribute__((sda));
extern void func_PAL_003120C0();
extern void func_L06_004579C8(char *);
extern int func_00283CF0(float);

void func_PAL_L06_0045CAE8(char *a0)
{
    char *s2 = *(char **)(a0 + 0x68);
    int v;

    func_00282CC0(a0 + 0x10, a0 + 0x10, s2);
    v = func_00283CF0((float)D_L06_001B375C * 1.5f);
    func_002A0488(a0, v, func_00283CF0((float)D_L06_001B375C * 1.25f), D_L06_001B375C);
    if (D_L06_001B3758 != 0) {
        func_00282F20(s2, s2, 0.14000002f);
        *(float *)(s2 + 0x8) = *(float *)(s2 + 0x8) + 0.22000001f;
        *(unsigned int *)(a0 + 0x64) = (unsigned int)func_PAL_003120C0;
        *(float *)(a0 + 0x2C) = *(float *)(a0 + 0x2C) * 0.75f;
        func_002A0488(a0, 0x10, 0x10, 0x10);
    }
}


extern void func_002A7750(char *, int, int);
extern int func_002A9640(char *, int, int);
extern int func_002E5CF8(int, int, char *);
extern void func_PAL_L00_003281C0(char *, int, float);
extern void func_0029F338(char *);
extern void func_00282D30(char *, char *, float);
extern void func_PAL_L06_0045CD20(char *, int, void *, int, float, float, float, float);

void func_PAL_L06_0045CBF0(unsigned char *a0)
{
    char *o = *(char **)(a0 + 0x68);

    switch (a0[0x20]) {
    case 0:
        *(unsigned short *)(a0 + 0x34) |= 0x800;
        func_002A7750((char *)a0, 1, -1);
        break;
    case 1:
        if (func_002A9640((char *)a0, 0x4010000, 0) != 0) {
            if (*(int *)o == 0) {
                func_002A7750((char *)a0, 2, -1);
            }
        }
        a0[0xA8] = 0xFF;
        break;
    case 2: {
        char tmp[16];

        func_00282D30(tmp, (char *)(a0 + 0xD0), -0.040000003f);
        func_PAL_L06_0045CD20((char *)a0, 7, tmp, 0xFF, 3.0f, 6.0f, 3.0f, 6.0f);
        func_002E5CF8(0, 0, (char *)a0);
        func_PAL_L00_003281C0((char *)a0, 1, 0.0f);
        func_0029F338((char *)a0);
        break;
    }
    }
}



void func_PAL_L06_0045CEC0(unsigned char *a0)
{
    char *o = *(char **)(a0 + 0x68);

    switch (a0[0x20]) {
    case 0:
        *(unsigned short *)(a0 + 0x34) |= 0x800;
        func_002A7750((char *)a0, 1, -1);
        break;
    case 1:
        if (func_002A9640((char *)a0, 0x4010000, 0) != 0) {
            if (*(int *)o == 0) {
                func_002A7750((char *)a0, 2, -1);
            }
        }
        a0[0xA8] = 0xFF;
        break;
    case 2: {
        char tmp[16];

        func_00282D30(tmp, (char *)(a0 + 0xD0), -0.040000003f);
        func_PAL_L06_0045CD20((char *)a0, 7, tmp, 0xFF, 3.0f, 6.0f, 3.0f, 6.0f);
        func_002E5CF8(0, 0, (char *)a0);
        func_PAL_L00_003281C0((char *)a0, 1, 0.0f);
        func_0029F338((char *)a0);
        break;
    }
    }
}


extern short *D_L06_001FB3A0[];
extern char *D_L06_001B281C[] __attribute__((sda));
extern float func_002A7940(void);
extern void func_PAL_L06_0045D258(char *);
extern void func_PAL_002A7E68(char *, int, int, int);

void func_PAL_L06_0045CFF0(unsigned char *obj)
{
    char *data;
    char *hit;
    short *list, *cursor;
    char *target;
    char *state;
    if (obj[0x20] == 0) {
        *(unsigned short *)(obj + 0x34) |= 0x800;
        obj[0x20] = 1;
    }
    data = *(char **)(obj + 0x68);
    hit = (char *)func_002A9640((char *)obj, 0x10000, 0);
    if (hit && *(short *)(*(char **)(hit + 0x20) + 0xAA) != 0xFE5) {
        if (*(int *)data == 255) { func_PAL_L06_0045D258((char *)obj); return; }
        {
            list = D_L06_001FB3A0[*(int *)data];
            if (list == 0) { func_PAL_L06_0045D258((char *)obj); return; }
            {
                cursor = list;
                do {
                    target = D_L06_001B281C[0] + ((*cursor & 0x7FFF) << 8);
                    if (*(signed char *)(target + 0x20) >= 0 && *(short *)(target + 0xAA) == 0xBBA) {
                        state = *(char **)(target + 0x68);
                        if (*(float *)(state + 0x20) > 0.0f) {
                            *(float *)(state + 0x5A4) = func_002A7940();
                            qcopy(state + 0x5B0, state + 0x460);
                            *(short *)(state + 0x24C) = 0xE1;
                            target[0x20] = 4;
                            func_PAL_002A7E68(target, 6, 0, 8);
                            *(int *)(state + 0x5A0) = 0;
                            *(short *)(state + 0x492) = 0;
                            target[0x20] = 5;
                            target[0x95] = 1;
                        }
                    }
                } while (*cursor++ >= 0);
            }
        }
        if (*(int *)(data + 4) == 255) goto destroy;
        list = D_L06_001FB3A0[*(int *)(data + 4)];
        if (list == 0) {
 destroy:
            func_PAL_L06_0045D258((char *)obj); return;
        }
        {
            cursor = list;
            do {
                target = D_L06_001B281C[0] + ((*cursor & 0x7FFF) << 8);
                if (*(signed char *)(target + 0x20) >= 0 && *(short *)(target + 0xAA) == 0xBBA) {
                    state = *(char **)(target + 0x68);
                    *(float *)(state + 0x5A4) = func_002A7940();
                    qcopy(state + 0x5B0, state + 0x460);
                    *(short *)(state + 0x24C) = 0xE1;
                    target[0x20] = 4;
                    func_PAL_002A7E68(target, 6, 0, 8);
                    target[0x20] = 5;
                    target[0x95] = 1;
                }
            } while (*cursor++ >= 0);
        }
        func_PAL_L06_0045D258((char *)obj);
    }
    obj[0xA8] = 255;
}


