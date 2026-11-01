#include "include_asm.h"


#include "common.h"

/* func_L15_00435E80 is in L15_00435E80.c. */

void func_PAL_L15_0043BD80(char *a0) {
    char *v1 = *(char **)(a0 + 0x68);

    *(int *)(v1 + 0x270) = 1;
    *(int *)(v1 + 0x274) = 0x190;
    *(char *)(a0 + 0x23) = 0x20;
    *(char *)(a0 + 0x20) = 2;
    *(unsigned short *)(a0 + 0x34) |= 8;
    *(float *)(v1 + 0x180) = 450.0f;
    *(int *)(a0 + 0x98) = 0;
}



INCLUDE_ASM("asm/pal/levels", func_PAL_L15_0043BF88);


extern void func_L06_00382608(char *, int, int, int, float, int);
extern int func_002EEB00(char *);
extern void func_002EE920(char *, char *);
extern void func_002EE678(char *, int);
extern void func_PAL_L05_0037E8E0(char *);
extern void func_L05_0037B538(char *, int, int, int);
typedef struct GornPathPoint {
    float position[3];
    float action;
} GornPathPoint;
typedef struct GornPath {
    int count;
    int pad[3];
    GornPathPoint points[1];
} GornPath;
extern char *D_L15_001FE480[];
extern void func_PAL_L15_0043C8B8(char *);
extern void func_PAL_L15_0043C978(void);
extern int func_002ED688(unsigned char *owner);
extern int func_00282948(void *);
extern int func_00283CF0(float);
extern float func_002A7878(float, float);
extern int func_L00_00367720(void);
extern void func_L05_00379E60(void *, void *, int, int);
extern int func_002A77E0(int);
extern s32 D_L15_001AEE20[] __attribute__((sda));
extern s32 D_L15_001B1780[] SDATA(D_L15_001B1780);
extern s32 D_L15_001B17B0[] SDATA(D_L15_001B17B0);
extern s32 func_002E5CF8(s32 a, s32 b, void *c);
extern s32 func_002A77E0(s32 a);
extern f32 func_002A7878(f32 a, f32 b);
extern s32 func_00283CF0(f32 a);
extern float func_002A7878(float, float);
extern int func_00283CF0(float);
extern int func_002E5CF8(int, int, void *);
extern int func_002A77E0(int);

/* func_L15_004363C8 is in L15_004363C8-g8.c. */

/* Advance through the path points, pausing when an odd encoded action supplies
   a duration in seconds. The path has a 16-byte header and 16-byte points. */
void func_PAL_L15_0043C6A0(char *object) {
    char *mover = object;
    char *state = *(char **)(mover + 0x68);

    switch (*(unsigned char *)(mover + 0x20)) {
    case 0:
        *(unsigned char *)(mover + 0x30) = 0xFF;
        if (func_L00_00367720() == 0) {
            return;
        }
        func_PAL_L15_0043C8B8(mover);
        if (*(int *)(state + 0x264) != 0) {
            func_L05_00379E60(mover, (void *)func_PAL_L15_0043C978, 0, 0);
        }
        func_L06_00382608(mover, *(int *)(state + 0x268), 0x8000FF00, 0x81, 0.75f, 1);
        break;
    case 1: {
        GornPath *path;
        char *owner;
        int index;

        func_L06_00382608(mover, *(int *)(state + 0x268), 0x8000FF00, 0x81, 0.75f, 1);
        owner = (char *)func_002ED688(mover);
        path = (GornPath *)D_L15_001FE480[*(int *)(state + 0x268)];
        if (func_002EEB00(mover) != 0) {
            index = *(int *)(state + 0x26C);
            *(int *)(state + 0x26C) = index + 1;
            if (index + 1 == path->count - 1) {
                *(unsigned char *)(mover + 0x20) = 3;
            } else {
                float action = path->points[index].action;

                if (action != -1.0f) {
                    if ((func_00283CF0(action) & 1) != 0) {
                        *(int *)(state + 0x274) = (func_00283CF0(action) >> 1) * 0x32;
                        *(unsigned char *)(mover + 0x20) = 2;
                    }
                }
                func_002EE920(mover, (char *)&path->points[*(int *)(state + 0x26C)]);
                *(int *)(owner + 0x130) = 0x196E6B;
            }
        }
        func_002EE678(mover, 0xC);
        func_PAL_L05_0037E8E0(mover);
        func_L05_0037B538(mover, 0, 1, 1);
        break;
    }
    case 2:
        if (func_00282948((int *)(state + 0x274)) != 0) {
            *(unsigned char *)(mover + 0x20) = 1;
        }
        break;
    }
}


extern void func_L15_00436BA8(char *);
extern void func_PAL_L05_0037D610(char *object, int flag);
extern void func_L05_00379C68(int arg0, int value);

void func_PAL_L15_0043C8B8(char *a0) {
    char *s0 = a0;
    char *s1 = *(char **)(s0 + 0x68);
    char *s2 = (char *)func_002ED688((unsigned char *)a0);

    *(int *)(s2 + 0x148) = 100;
    func_PAL_L05_0037D610(s0, 1);
    *(float *)(s1 + 0x180) = 100.0f;
    *(unsigned char *)(s0 + 0x20) = 1;
    *(unsigned char *)(s0 + 0x30) = 0xFF;
    *(unsigned short *)(s0 + 0x32) = 0x1FF;
    *(unsigned short *)(s0 + 0x34) |= 0x100;
    *(float *)(s0 + 0x2C) = 0.20000000298023224f;
    *(float *)(s1 + 0x278) = 12.0f;
    *(int *)(s1 + 0x26C) = 0;
    *(int *)(s1 + 0x270) = 0;
    *(int *)(s1 + 0x274) = 0;
    *(int *)(s2 + 0x154) = (int)(s1 + 0x278);
    func_L05_00379C68((int)s0, 0xFFFF);
}


