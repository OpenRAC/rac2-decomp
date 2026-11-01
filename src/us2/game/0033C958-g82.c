#include "include_asm.h"

typedef unsigned char u8_Ff4eb83c9;
typedef int s32_Ff4eb83c9;
extern int func_0033C590(u8_Ff4eb83c9 *, s32_Ff4eb83c9);
extern void func_US2_0033BE70(void *);
extern void func_0033B018(void *, float, float);
extern int func_002E5E58(int, int, void *);
extern void func_0027AB40(void);

int func_US2_0033D5D8(u8_Ff4eb83c9 *a0, int a1)
{
    u8_Ff4eb83c9 *p = a0 + 8;
    unsigned int *sfx = (unsigned int *)0x1A7BAC;
    unsigned int *music = (unsigned int *)0x1A7BB0;
    int *mode = (int *)0x1A7BB4;
    unsigned char *toggle = (unsigned char *)0x1A7BB9;
    float *q;
    int v;

    func_US2_0033BE70(p);
    q = *(float **)(a0 + 0x2DC);
    func_0033B018(p, q[0], q[1]);
    if (a1 & 0x1000) {
        func_002E5E58(3, 0, 0);
        v = *(int *)(a0 + 0x2D8);
        *(int *)(a0 + 0x2D8) = (v + 3) % 4;
    } else if (a1 & 0x4000) {
        func_002E5E58(3, 0, 0);
        v = *(int *)(a0 + 0x2D8);
        *(int *)(a0 + 0x2D8) = (v + 1) % 4;
    } else if (a1 & 0x40) {
        func_002E5E58(4, 0, 0);
        switch (*(int *)(a0 + 0x2D8)) {
        case 0:
            *sfx = *sfx < 1;
            break;
        case 1:
            *music = *music < 1;
            break;
        case 2:
            *mode = (*mode + 1) % 3;
            break;
        case 3:
            *toggle = *toggle < 1;
            func_0027AB40();
            break;
        }
    }
    return (a1 >> 6) & 1;
}

typedef struct { int ids[2]; } OptionPair;
typedef struct { int ids[3]; } OptionTriple;
extern OptionPair D_001ADE20 __attribute__((section(".data")));
extern OptionPair D_001ADDD0 __attribute__((section(".data")));
extern OptionTriple D_001ADE28 __attribute__((section(".data")));
extern char D_001ADDD8[];
extern int D_001ADE00 __attribute__((sda));
extern int D_001ADE04[] __attribute__((sda));
extern int D_001ADE08 __attribute__((sda));
extern int D_001ADE0C[] __attribute__((sda));
extern int D_001ADE10 __attribute__((sda));
extern int D_001ADE14[] __attribute__((sda));
extern int D_001ADE18 __attribute__((sda));
extern int D_001ADE1C[] __attribute__((sda));
extern int D_001A7BA4, D_001A7BA8, D_001A7BAC;
extern unsigned char D_001A7BB1;
extern void func_US2_0033BF90(void *);
extern char *func_00288FB8(int);
extern int func_00115DA8(char *, const char *, ...);
extern int func_0027FB40(int, int, unsigned long, char *, int);

void func_US2_0033D780(char *object)
{
    char buffer[128];
    OptionPair onoff;
    OptionTriple modes;
    OptionPair toggle;
    char *first, *second, *format;
    char *label2, *label3, *label4;
    int color;
    func_US2_0033BF90(object + 8);
    onoff = D_001ADE20;
    modes = D_001ADE28;
    toggle = D_001ADDD0;
    format = D_001ADDD8;
    color = *(int *)(object + 0x2D8) == 0 ? (int)0x80D0D0D0 : 0x70808080;
    first = func_00288FB8(0x2C78);
    second = func_00288FB8(onoff.ids[D_001A7BA4 != 0]);
    func_00115DA8(buffer, format, first, second);
    func_0027FB40(D_001ADE00, D_001ADE04[0], color, buffer, -1);
    color = *(int *)(object + 0x2D8) == 1 ? (int)0x80D0D0D0 : 0x70808080;
    label2 = func_00288FB8(0x2C77);
    second = func_00288FB8(onoff.ids[D_001A7BA8 != 0]);
    func_00115DA8(buffer, format, label2, second);
    func_0027FB40(D_001ADE08, D_001ADE0C[0], color, buffer, -1);
    color = *(int *)(object + 0x2D8) == 2 ? (int)0x80D0D0D0 : 0x70808080;
    {
        int mode = D_001A7BAC;
        label3 = func_00288FB8(0x2DAE);
        second = func_00288FB8(modes.ids[mode]);
    }
    func_00115DA8(buffer, format, label3, second);
    func_0027FB40(D_001ADE10, D_001ADE14[0], color, buffer, -1);
    color = *(int *)(object + 0x2D8) == 3 ? (int)0x80D0D0D0 : 0x70808080;
    label4 = func_00288FB8(0x307A);
    second = func_00288FB8(toggle.ids[D_001A7BB1 != 0]);
    func_00115DA8(buffer, format, label4, second);
    func_0027FB40(D_001ADE18, D_001ADE1C[0], color, buffer, -1);
}
