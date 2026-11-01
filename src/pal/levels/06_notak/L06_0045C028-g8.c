#include "include_asm.h"

#include "common.h"
extern void func_L06_004576C8(char *);
extern void func_PAL_L06_0045CA40(char *);
extern void func_PAL_L06_0045C8D0(char *);
extern int func_002A9640(char *, int, int);
extern int func_002A8508(int, int);
extern void func_002A7750(char *, int, int);
extern int func_002B3868(char *);
extern void func_002A0488(char *, int, int, int);
extern int func_002E5CF8(int, int, char *);
extern int func_00282948(char *);
extern void func_002E5E58(int, int, int);
extern void func_PAL_002B1588(int, int);
extern void func_PAL_L05_0042A240(char *, int, int, int, int, int, int, int, int, int, int, float);
extern void func_PAL_L00_003281C0(char *, int, float);
extern void func_0029F338(char *);
extern int D_L06_001B375C;
extern int D_L06_001B3758[] __attribute__((sda));
extern int D_L06_001B3758_gp SDATA(D_L06_001B3758);
extern int D_L06_001A903C;
extern unsigned char D_001A7A60[32] __attribute__((sda));
typedef struct {
    char pad[0x160];
    float scale;
    int pad164;
    int duration;
    int timer;
    char pad170[0x10];
    float speed;
    int pad184;
    int limit;
} EffectState;
extern EffectState D_L06_001B9700;

void func_PAL_L06_0045C508(unsigned char *obj)
{
    char *d = *(char **)(obj + 0x68);
    switch (obj[0x20]) {
    case 0:
        func_L06_004576C8((char *)obj);
        D_L06_001B375C = 10;
        D_L06_001B3758_gp = 0;
        func_002A7750((char *)obj, 1, -1);
        break;
    case 1:
        if (func_002A9640((char *)obj, 0x4010000, 0) &&
            !func_002A8508(*(int *)(d + 0x64), -1) &&
            !func_002A8508(*(int *)(d + 0x68), -1) &&
            !func_002A8508(*(int *)(d + 0x6C), -1) &&
            !func_002A8508(*(int *)(d + 0x60), -1))
            func_002A7750((char *)obj, 3, -1);
        obj[0xA8] = 255;
        break;
    case 3:
        if (func_002B3868((char *)obj)) {
            func_PAL_L06_0045CA40((char *)obj);
            *(float *)(obj + 0x2C) *= .9f;
            func_002A0488((char *)obj, 255, 127, 127);
            *(unsigned short *)(obj + 0x34) |= 0x200;
            *(int *)(d + 0x130) = 150;
            D_L06_001B9700.speed = .02f;
            D_L06_001B9700.limit = 150;
            D_L06_001B9700.scale = .4f;
            D_L06_001B9700.duration = 100;
            D_L06_001B9700.timer = 0;
            func_002E5CF8(0, 0, (char *)obj);
        }
        func_PAL_L06_0045C8D0((char *)obj);
        if (D_L06_001B375C < 127) ++D_L06_001B375C;
        if (func_00282948(d + 0x130)) func_002A7750((char *)obj, 4, -1);
        break;
    case 4:
        if (func_002B3868((char *)obj)) {
            func_002E5CF8(1, 0, (char *)obj);
            if (!D_001A7A60[17]) {
                D_001A7A60[17] = 1;
                func_002E5E58(1, 0, 0);
                func_PAL_002B1588(0x1233, -1);
                D_L06_001A903C = 1;
            }
            func_PAL_L05_0042A240((char *)obj + 0x10, 1, 25, 20, 20, 20, 45, 1, 1, 1, 1, 7);
            func_PAL_L00_003281C0((char *)obj, 20, 0);
            D_L06_001B3758[0] = 1;
            D_L06_001B9700.speed = .05f;
            D_L06_001B9700.limit = 150;
            D_L06_001B9700.scale = .05f;
            D_L06_001B9700.duration = 100;
            D_L06_001B9700.timer = 0;
            func_0029F338((char *)obj);
        }
    }
}
