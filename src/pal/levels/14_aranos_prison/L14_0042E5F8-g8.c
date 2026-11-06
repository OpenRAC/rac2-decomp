#include "include_asm.h"

/* func_PAL_L14_0042E5F8, the PAL copy of func_L14_00428E68: the same C, with the timers at 50 Hz. */
#include "common.h"

#define W(p, o) (*(int *)((char *)(p) + (o)))
#define B(p, o) (*(u8 *)((char *)(p) + (o)))
#define F(p, o) (*(float *)((char *)(p) + (o)))

typedef struct {
    char pad[0x80];
    float position[4];
} Hero;

extern int func_PAL_L14_0042ED80(void *);
extern int func_002B3890(void *);
extern int func_002B1C20(void *, void *);
extern int func_002B3868(void *);
extern int func_PAL_L01_00323068(void *, void *);
extern int func_L00_00329520(void *, int);
extern int func_L01_00322288(void *, float);
extern int func_002A7820(int, int);
extern int func_002A77E0(int);
/* Integer and FP arguments retain their respective EE register-bank order. */
extern int func_002A8C28(void *, void *, float, float, int, float, int, int, int);
extern float func_00282E80(void *, void *);
extern float func_00283248(float, float);
extern float func_00283C80(float, float);
extern float func_0029F530(void *);
extern void func_002B60B0(void *, float, float, float, float);
extern void func_PAL_L14_0042F200(void *);
extern void func_0029F338(void *);
extern void func_002A7750(void *, int, int);
extern void func_PAL_002A7E68(void *, int, int, int);
extern void func_PAL_002B5E10(void *);
extern void func_L14_003DF690(void *, int);
extern void func_0029FCC0(void *, int, void *);
extern void func_PAL_L14_0042F0D8(void *);

extern float D_L14_001B1924 __attribute__((sda));
extern float D_L14_001B1928 __attribute__((sda));
extern float D_L14_001B192C __attribute__((sda));
extern float D_L14_001B1930 __attribute__((sda));
extern int D_L14_001B20C8;
extern u8 D_00189E20[];
extern u8 *D_L14_001B259C;
extern int D_L14_001B1938[4];
extern char *D_L14_001C39C0[];


void func_PAL_L14_0042E5F8(char *self)
{
    char *s = *(char **)(self + 0x68);
    int r, i;
    float angle, t;
    union {
        int choices[4];
        float pos[4];
    } scratch;

    if (func_PAL_L14_0042ED80(self)) {
        func_0029F338(self);
        return;
    }
    {
        switch (B(self, 0x95)) {
        case 0:
            if (W(s, 0x2F0) == 1 && B(self, 0x20) == 1)
                func_002A7750(self, 5, 1);
            break;
        case 1:
            if (func_002B3890(self))
                func_002B60B0(self,
                    D_L14_001B1924 * 0.00040000002f,
                    D_L14_001B1928 * 0.020000001f,
                    D_L14_001B192C * 6.981318e-06f,
                    D_L14_001B1930 * 0.0003490659f);
            if (W(s, 0x2F0) != 1) {
                func_002A7750(self, 1, 0);
                W(s, 0x30C) = (func_002A7820(580, 600) * 5 + 2) / 6;
            }
            break;
        case 2:
            r = func_002B1C20(self, s + 0x140);
            if (r & 1) {
                func_PAL_L14_0042F200(self);
                func_0029F338(self);
                return;
            }
            if (r & 2) {
                if (W(s, 0x2F0) == 1)
                    func_002A7750(self, 5, 1);
                else {
                    func_002A7750(self, 1, 0);
                    W(s, 0x30C) = (func_002A7820(580, 600) * 5 + 2) / 6;
                }
            }
            break;
        }
    }

    switch (B(self, 0x20)) {
    case 1:
        if (func_002B3868(self) && B(self, 0x43) != 6)
            func_PAL_002A7E68(self, 6, 0, 17);
        if (B(self, 0x60) & 2) {
            __builtin_memcpy(scratch.choices, D_L14_001B1938, 16);
            if (B(self, 0x43) != scratch.choices[func_002A77E0(4)])
                func_PAL_002A7E68(self, scratch.choices[func_002A77E0(4)], 0, 17);
        }
        if (W(s, 0x2B8) != -1)
            func_PAL_002B5E10(self);
        if ((D_L14_001B20C8 & 15) == (((int)self >> 8) & 15)) {
            if (W(s, 0x2B8) == -1)
                break;
            if (W(s, 0x31C) && ((Hero *)D_00189E20)->position[2] + 2.0f < F(self, 0x18) &&
                func_00282E80(self + 0x10, (((Hero *)D_00189E20)->position)) < 16.0f) {
                func_002A7750(self, 2, -1);
                break;
            }
            if (!W(s, 0x31C) && F(self, 0x18) < ((Hero *)D_00189E20)->position[2] - 2.0f &&
                func_00282E80(self + 0x10, (((Hero *)D_00189E20)->position)) < 8.0f)
                func_002A7750(self, 3, -1);
        } else {
            angle = func_00283248(((Hero *)D_00189E20)->position[0] - F(self, 0x10),
                                 ((Hero *)D_00189E20)->position[1] - F(self, 0x14));
            if (func_00283C80(F(self, 0xF8), angle) > 0.7853982449f)
                func_002A7750(self, 4, -1);
        }
        break;
    case 4:
        if (func_002B3868(self) && B(self, 0x43) != 8)
            func_PAL_002A7E68(self, 8, 0, 17);
        angle = func_00283248(((Hero *)D_00189E20)->position[0] - F(self, 0x10),
                             ((Hero *)D_00189E20)->position[1] - F(self, 0x14));
        func_L01_00322288(self, angle);
        if (func_00283C80(F(self, 0xF8), angle) < 0.05235988274f)
            func_002A7750(self, 1, -1);
        break;
    case 2:
        if (func_002B3868(self)) {
            if (B(self, 0x43) != 8)
                func_PAL_002A7E68(self, 8, 0, 17);
            func_L14_003DF690(D_L14_001B259C + W(s, 0x2B8) * 256, 0);
        }
        if (func_PAL_L01_00323068(self, D_L14_001B259C + W(s, 0x2B8) * 256 + 0x10) & 128) {
            func_L14_003DF690(D_L14_001B259C + W(s, 0x2B8) * 256, 1);
            W(s, 0x31C) = 0;
            func_002A7750(self, 1, -1);
        }
        break;
    case 3:
        if (func_002B3868(self)) {
            if (B(self, 0x43) != 8)
                func_PAL_002A7E68(self, 8, 0, 17);
            func_L14_003DF690(D_L14_001B259C + W(s, 0x2B8) * 256, 0);
        }
        if (func_PAL_L01_00323068(self, s + 0x2E0) & 128) {
            W(s, 0x31C) = 1;
            func_002A7750(self, 1, -1);
        }
        break;
    case 5:
        if (func_002B3868(self) && B(self, 0x43) != 16)
            func_PAL_002A7E68(self, 16, 7, 6);
        t = func_0029F530(self);
        if (t < 19.0f) {
            angle = func_00283248(F(s, 0x210) - F(self, 0x10),
                                 F(s, 0x214) - F(self, 0x14));
            func_L01_00322288(self, angle);
            W(s, 0x320) = 1;
        } else if (t <= 22.0f && W(s, 0x320)) {
            func_002A8C28(self, *(char **)(s + 0x300) + 0x10,
                          0.57f, 2.0f, 1, 1.5f, 0, 1, 0);
            func_002A8C28(self, *(char **)(s + 0x304) + 0x10,
                          0.57f, 2.0f, 1, 1.5f, 0, 1, 0);
            func_0029FCC0(self, 6, scratch.pos);
            r = func_002A8C28(self, scratch.pos, 0.57f, 2.0f, 1, 2.0f, 0, 1, 0);
            for (i = 0; i < r; i++)
                if (*(short *)(D_L14_001C39C0[i] + 0xAA) == 2404)
                    W(s, 0x320) = 0;
        }
        break;
    case 7:
        if (func_L00_00329520((((Hero *)D_00189E20)->position), W(s, 0x2BC)))
            func_002A7750(self, 8, -1);
        break;
    case 8:
        if (func_002B3868(self) && B(self, 0x43) != 1)
            func_PAL_002A7E68(self, 1, 0, 2);
        if (B(self, 0x60) & 2)
            func_002A7750(self, 1, 0);
        break;
    }
    func_PAL_L14_0042F0D8(self);
}
