#include "include_asm.h"

INCLUDE_ASM("asm/pal/levels", func_PAL_L00_003A6238);




#include "common.h"
extern void func_002829A8(void *);
extern void func_00282D30(void *, void *, float);
extern void func_00282CC0(void *, void *, void *);
extern int func_002A77E0(int);
extern char *func_PAL_002BE9A8(float, void *, float, float, int, void *, float, unsigned int, int);
extern int func_00283CF0(float);

/* func_L00_003A2C60 is defined in L00_003A2C60-g8.c. */

/* func_L00_003A2EE0 is defined in L00_003A2EE0-g8.c. */



/* Emit layered sparks while the object's effect timer remains active. */
void func_PAL_L00_003A77D8(char *moby)
{
    float position[4], offset[4], velocity[4];
    int count, rotation;
    int style;
    int firstStyle;
    int firstKind, firstAlpha, secondKind, secondAlpha;
    float size;
    if (!*(unsigned char *)(moby + 0xBC))
        return;
    func_002829A8(moby + 0xBC);
    firstStyle = 7;
    firstKind = 2;
    firstAlpha = 127;
    func_00282D30(position, moby + 0xD0, 0.1f);
    func_00282CC0(position, position, moby + 0x10);
    func_00282D30(offset, moby + 0xC0, 0.275f);
    func_00282CC0(position, position, offset);
    func_00282D30(velocity, moby + 0xD0, 0.120000005f);
    for (count = 3; count >= 0; count--) {
        char *particle;
        rotation = func_002A77E0(16);
        if (func_002A77E0(2))
            rotation = -rotation;
        particle = func_PAL_002BE9A8(0.04f, position, 1.0f, 0.9f, rotation, velocity, 52500.0f, 0x7F204080, 0);
        if (particle) {
            char *sub;
            sub = particle + 0x20;
            *(short *)(particle + 10) = firstStyle;
            *(unsigned char *)(particle + 9) = ((*(short *)(moby + 0x32) >> 5) << 4) + func_00283CF0(4.0f);
            *(int *)(sub + 4) = firstKind;
            *(unsigned char *)(sub + 10) = firstAlpha;
            *(unsigned char *)(sub + 11) = *(unsigned char *)(particle + 10);
        }
    }
    rotation = 16;
    style = 2;
    size = 15750.0009765625f;
    secondKind = 2;
    secondAlpha = 127;
    for (count = 2; count >= 0; count--) {
        char *particle = func_PAL_002BE9A8(0.02f, position, 1.0f, 1.0f, rotation, velocity, size, 0x7FFFFFFF, 0);
        if (particle) {
            char *sub;
            int brightness;
            sub = particle + 0x20;
            brightness = ((*(short *)(moby + 0x32) >> 5) << 4) + func_00283CF0(4.0f);
            *(short *)(particle + 10) = style;
            *(unsigned char *)(particle + 9) = brightness;
            *(unsigned char *)(particle + 8) = func_002A77E0(255);
            *(int *)(sub + 4) = secondKind;
            *(unsigned char *)(sub + 10) = secondAlpha;
            *(unsigned char *)(sub + 11) = *(unsigned char *)(particle + 10);
        }
        rotation = -rotation;
        style <<= 1;
        size -= 3150.0f;
    }
}


INCLUDE_ASM("asm/pal/levels", func_PAL_L00_003A7A68);

INCLUDE_ASM("asm/pal/levels", func_PAL_L00_003A7ED8);

extern char D_L00_001A8F20[] __attribute__((sda));
extern void func_0029FCC0_1(int a, int b, void *c);
extern int func_L00_003AB9C0(int a, void *b, int c, char *d, float e, float f, float g, float h);

/* Runs one helper over the object and a stack buffer, then builds a second call from the object's field 104 sub-object - its field 24 as a float, the constants 2.0f/5.0f/0.6f and a bound data address - and stores the object into field 184 of the returned pointer when it is non-null. */
void func_PAL_L00_003A8978(int a0)
{
    int buf[4];
    int s0;
    int v;

    s0 = *(int *)(a0 + 104);
    func_0029FCC0_1(a0, 0, buf);
    v = func_L00_003AB9C0(a0, buf, *(int *)(s0 + 16), D_L00_001A8F20, *(float *)(s0 + 24), 2.0f, 5.0f, 0.6f);
    if (v != 0) {
        *(int *)(v + 184) = a0;
    }
}

INCLUDE_ASM("asm/pal/levels", func_PAL_L00_003A89F0);

typedef struct {
    unsigned char pad_000[0x18];
    int object_18;
    unsigned char pad_01C[4];
    float vector_20[4];
} L00AimState;
typedef struct {
    unsigned char pad_000[0x70];
    float value_70;
    unsigned char pad_074[0x6C];
} L00AimEntry;
extern void func_00282CF0(void *, void *, void *);
extern void func_00282F20(void *, void *, float);
extern int func_002761F8(void *,void *,int,void *,void *);
extern float func_00282E48(void *, void *);
extern char *func_PAL_L00_00400968(char *, char *, char *, int);
extern void func_002A8E20(int, void *);
extern void func_PAL_0032F0B8(int, int, char *);
extern int D_0018C0B0;
extern unsigned char D_00139582;
extern L00AimState D_L00_001BF200;
extern L00AimEntry D_L00_00262570[];

int func_PAL_L00_003A9468(char *a0, char *a1, char *a2, char *a3)
{
    char local[16];
    float distance;
    float saved;
    int ret;

    func_00282CF0(a3, a2, a1);
    func_00282F20(a3, a3, 1.5f);
    *(float *)(a3 + 0xC) = 5627.9248046875f;
    if (func_002761F8(a1, a2, 0x10, D_0018C0B0, 0) != 0) {
        func_00282CF0(local, a2, a1);
        func_00282F20(local, local, 1.0f);
        func_00282CF0(local, (char *)D_L00_001BF200.vector_20, a1);
        func_PAL_L00_00400968(a1, local, (char *)D_L00_001BF200.vector_20, 1);
        if (D_L00_001BF200.object_18 != 0) {
            saved = (D_L00_00262570 + D_00139582)->value_70;
            distance = func_00282E48((char *)D_L00_001BF200.vector_20, a1);
            if (distance < 10.0f) {
                *(float *)(a3 + 0x1C) = saved;
            } else if (distance < 14.0f) {
                *(float *)(a3 + 0x1C) = saved * 0.75f;
            } else if (distance < 20.0f) {
                *(float *)(a3 + 0x1C) = saved * 0.5f;
            } else {
                *(float *)(a3 + 0x1C) = saved * 0.125f;
            }
            func_002A8E20(D_L00_001BF200.object_18, a3);
            func_PAL_0032F0B8(D_L00_001BF200.object_18, 26, a0);
        }
        ret = D_L00_001BF200.object_18;
    } else {
    func_00282CF0(local, a2, a1);
    func_PAL_L00_00400968(a1, local, a2, 0);
    ret = 0;
    }
    return ret;
}


