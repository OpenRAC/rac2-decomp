#include "include_asm.h"

#include "common.h"
extern int func_002E5CF8(int, int, char *);
extern float func_002A7878(float, float);
extern void func_PAL_002A7E68(void *, int, int, int);
extern void func_002A7750(void *, int, int);
extern void func_PAL_002A0F68(char *);
extern void func_PAL_L00_003FB330(char *, int, int, int, int, int, int, int, float, float, int, int, int, int);
extern void func_002E5DA0(int, int, void *, int);
extern void func_PAL_002A7E68(void *, int, int, int);
extern void func_PAL_002A0F68(char *);
extern void func_002A7750(void *, int, int);
extern void func_002A7A00(float *, float, float);
extern void func_L11_0043AB28(char *);
extern void func_002A7A00(float *out, float a, float b);
extern float func_002A7878(float a, float b);
extern void func_PAL_002B15D8(char *self, int mask, float *arg2, unsigned char arg3,
                           float f0, float f1, float f2, float f3);
extern int func_002E5CF8(int index, int a1, char *a2);
extern void func_0029F9F0(char *list, char *node);

/* Spawns the object's jitter effect while its flag byte is set, then retires the state. */
void func_PAL_L11_004400D0(char *obj)
{
    char *state;
    unsigned short flags;
    float v[3];

    if (*(unsigned char *)(obj + 0x20) == 0)
        return;

    if (*(unsigned char *)(obj + 0x31) != 0) {
        float s = 0.20000002f;

        func_002A7A00(v, s, 0.40000004f);
        v[2] = func_002A7878(0.10000001f, s);
        func_PAL_002B15D8(obj, 3, v, 0xFF, 3.0f, 6.0f, 3.0f, 6.0f);
        func_002E5CF8(1, 0, obj);
        func_PAL_L00_003FB330(obj + 0x10, 1, 0x19, 0xA, 0xA, 5, 0, 1, 1.0f, 20.0f, 0, 0, 0, 0);
        func_002E5DA0(0, 0, obj, 0xDF7);
    }

    func_002A7750(obj, 1, 0);
    func_PAL_002A7E68(obj, 0, 0, 3);
    func_PAL_002A0F68(obj);

    state = *(char **)(obj + 0x68);
    flags = *(unsigned short *)(obj + 0x34);
    *(unsigned char *)(obj + 0x31) = 0;
    *(int *)(obj + 0x98) = 0;
    *(unsigned short *)(obj + 0x34) = (flags & 0xEFFF) | 0x47;

    if (*(unsigned char *)(state + 0x221))
        func_0029F9F0(obj, state + 0x220);
    if (*(unsigned char *)(state + 0x261))
        func_0029F9F0(obj, state + 0x260);
}

