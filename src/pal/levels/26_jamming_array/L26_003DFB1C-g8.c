/* func_PAL_L26_003DFB1C, the PAL copy of func_L26_003DB818: the same C, where the compare 300
 * becomes 250, all three func_002A7820 results stored at +0x220 are scaled to 50 Hz, the last
 * argument of func_PAL_002A7E68 goes 20 > 17 and 10 > 8, and func_00282F20's factor goes
 * 0.083333336f > 0.10000001f. */
#include "common.h"

typedef int Quad __attribute__((mode(TI)));
typedef union { Quad q; float f[4]; } Vector;
typedef struct { int action[4]; } ActionChoices;
extern int D_L26_001A8FF0;
extern ActionChoices D_L26_001B05C8;
extern float D_L26_001B05C0 __attribute__((sda));
extern float D_00189EA0[4];
extern int func_PAL_L26_003E0168(unsigned char *);
extern void func_002A7750(unsigned char *, int, int);
extern unsigned long func_002B1C20(void *, void *);
extern void func_00325D30(char *, char *);
extern void func_PAL_002A7650(void *, int, int);
extern void func_00283098(void *, void *, void *);
extern void func_00282CC0(void *, void *, void *);
extern int func_002E5CF8(int, int, char *);
extern void *func_PAL_L00_003FB330(void *, int, int, int, int, int, int, int, int, int, int, void *, float, float);
extern void func_002AB6D8(float *, float *);
extern void func_00282F20(void *, void *, float);
extern void func_PAL_002B15D8(char *, int, float *, float, float, float, float, unsigned char);
extern void func_0029F338(void *);
extern int func_002A7820(int, int);
extern int func_002B3868(unsigned char *);
extern int func_002A77E0(int);
extern void func_PAL_002A7E68(void *, int, int, int);
extern int func_L02_00332630(char *, void *);
extern void func_PAL_L02_00335630(char *, char *);
extern float func_L26_00324598(unsigned char *, void *, void *);
extern float func_00282C48(float);
extern float func_0029F530(char *);
extern int func_002A8C28(void *, void *, int, int, int, int, float, float, float);
extern void func_PAL_L26_003E03D0(void *);

void func_PAL_L26_003DFB1C(unsigned char *object) {
    /* Mutually exclusive uses of the same 16-byte retail workspace. */
    union { ActionChoices choices; Vector position; } workspace;
    Vector seed;
    Vector velocity;
    char *private;
    unsigned long flags;
    float time;
    int next;
    int i;
    if (!D_L26_001A8FF0) return;
    private = *(char **)(object + 0x68);
    if (func_PAL_L26_003E0168(object)) { func_0029F338(object); return; }
    switch (object[0x95]) {
    case 0:
        if (*(short *)(private + 0x224) == 1) {
            if (object[0x20] == 1) func_002A7750(object, 4, 2);
            else func_002A7750(object, 5, 2);
        } else if (*(short *)(private + 0x226)) {
            func_002A7750(object, 3, 1);
            *(short *)(private + 0x226) = 0;
            if (*(short *)(private + 0x220) < 250)
                *(short *)(private + 0x220) = ((s32)(func_002A7820(480, 600)) * 5 + 2) / 6;
        }
        break;
    case 1:
        if (*(short *)(private + 0x224) == 1)
            func_002A7750(object, 5, 2);
        else if (*(short *)(private + 0x220) == 0 && (object[0x60] & 2))
            func_002A7750(object, 2, 0);
        break;
    case 2:
        if (*(short *)(private + 0x224) != 1 && object[0x20] != 6) {
            func_002A7750(object, 3, 1);
            *(short *)(private + 0x220) = ((s32)(func_002A7820(580, 600)) * 5 + 2) / 6;
        }
        break;
    case 3:
        flags = func_002B1C20(object, private + 0x50);
        if (((flags & 1UL) == 1UL) || *(float *)(private + 0x20) <= 0.0f) {
            func_00325D30((char *)object, private + 0x270);
            func_PAL_002A7650(object, 0, 3);
            seed.q = 0;
            seed.f[2] = 1.0f;
            func_00283098(&workspace.position, &seed, object + 0xC0);
            func_00282CC0(&workspace.position, &workspace.position, object + 0x10);
            func_002E5CF8(13, 0, (char *)object);
            func_PAL_L00_003FB330(&workspace.position, 0, 25, 20, 20, 20, 45, 0, 0, 1, 0, 0, 0.8f, 20.0f);
            func_002AB6D8((float *)(object + 0xC0), (float *)(object + 0xF0));
            func_00282F20(&velocity, private + 0xD0, 0.10000001f);
            func_PAL_002B15D8((char *)object, 0x3F8, velocity.f, 3.0f, 6.0f, 3.0f, 6.0f, 0xFF);
            func_0029F338(object);
            return;
        }
        if (((flags & 2UL) == 2UL) || (unsigned char)private[0x6A] > 1) {
            func_002A7750(object, 6, 2);
            *(short *)(private + 0x220) = ((s32)(func_002A7820(580, 600)) * 5 + 2) / 6;
        }
        break;
    }
    switch (object[0x20]) {
    case 2:
        if (func_002B3868(object) && object[0x43] != 2)
            func_PAL_002A7E68(object, 2, 0, 17);
        break;
    case 3:
        workspace.choices = D_L26_001B05C8;
        if (func_002B3868(object) && object[0x43] != workspace.choices.action[func_002A77E0(4)])
            func_PAL_002A7E68(object, workspace.choices.action[func_002A77E0(4)], 0, 17);
        func_L02_00332630((char *)object, D_00189EA0);
        if (object[0x60] & 2) {
            next = workspace.choices.action[func_002A77E0(4)];
            if (next == object[0x43]) next = (next + func_002A77E0(3)) % 4;
            if (object[0x43] != next) func_PAL_002A7E68(object, next, 0, 17);
        }
        break;
    case 4:
        if (func_002B3868(object) && object[0x43] != 4)
            func_PAL_002A7E68(object, 4, 0, 8);
        if (object[0x60] & 2) func_002A7750(object, 5, -1);
        break;
    case 5:
        if (func_002B3868(object) && object[0x43] != 8)
            func_PAL_002A7E68(object, 8, 0, 17);
        func_PAL_L02_00335630((char *)object, private + 0x1F0);
        if ((*(float *)(private + 0x1CC) < D_L26_001B05C0) &&
            (func_00282C48(func_L26_00324598(object, private + 0x1F0, private + 0x230)) < 0.17453295f))
            func_002A7750(object, 6, -1);
        break;
    case 6:
        if (func_002B3868(object) && object[0x43] != 9)
            func_PAL_002A7E68(object, 9, 8, 17);
        if (object[0x60] & 2) func_002A7750(object, 5, -1);
        time = func_0029F530((char *)object);
        if (object[0x42] == object[0x43] && time >= 18.0f && time <= 24.0f) {
            for (i = 0; i < 2; i++)
                func_002A8C28(object, *(char **)(private + 0x270 + i * 4) + 0x10,
                              0x4000001, 0, 1, 0, 0.333f, (float)(unsigned char)private[0x34], 1.0f);
        }
        break;
    }
    func_PAL_L26_003E03D0(object);
    return;
}
