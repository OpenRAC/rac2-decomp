#include "include_asm.h"

#include "common.h"
extern char *D_L20_001B2F9C_1 __attribute__((sda));
extern float D_L20_001B2ACC __attribute__((sda));
extern char D_L20_001A8F20[];
extern char D_L20_001A8F20_1[];
extern int func_002A9640(char *, int, int);
extern void func_002A7750(char *, int, int);
extern void func_L00_00324F18(char *, char *, f32, f32, f32);
extern void func_PAL_002AC718(void *, void *, void *, float, float, int, int, int,
                         float, float, float, float, int, float, int, int, int, int, int);
extern void func_PAL_002B15D8(char *, int, float *, float, float, float, float, unsigned char);
extern void func_PAL_L00_003281C0(char *, int, f32);
extern void func_002E5CF8(int, int, char *);
extern int func_002B3868(char *);
extern int func_00282948(char *);
extern void func_0029F338(char *);

void func_PAL_L20_003A328C(char *arg0) {
    char *s0 = arg0;
    char *s1;
    f32 buf[4];
    f32 f20;
    f32 f21;
    int v0;

    s1 = *(char **)(s0 + 0x68);

    switch (*(u8 *)(s0 + 0x20)) {
    case 0:
        func_002A7750(s0, 1, -1);
        break;
    case 1:
        v0 = func_002A9640(s0, 0x04010000, 0);
        if (v0 == 0) {
            v0 = 0xFF;
        } else if (*(int *)s1 != 0) {
            v0 = 0xFF;
        } else {
            func_002A7750(s0, 2, -1);
            break;
        }
        *(u8 *)(s0 + 0xA8) = v0;
        v0 = *(int *)(s1 + 4);
        if (v0 <= 0) {
            break;
        }
        v0 = (int)((char *)D_L20_001B2F9C_1 + (v0 << 8));
        if (v0 == 0) {
            break;
        }
        {
            s32 mode = *(u8 *)(v0 + 0x20);
            if (mode == 0xFE) goto changeState;
            if (mode == 0xFD) goto changeState;
            if (mode != 3) break;
        changeState:
            func_002A7750(s0, 2, -1);
        }
        break;
    case 2:
        f20 = 0.0f;
        f21 = 3.0f;
        func_L00_00324F18(s0, (char *)buf, f20, f20, f21);
        if (*(u8 *)(s0 + 0x31) != 0 && D_L20_001B2ACC < 0.9f) {
            func_PAL_002AC718(s0, D_L20_001A8F20, buf, f20, f20, 10, 3, 16,
                          1.0f, 0.5f, 9.0f, *(f32 *)(s0 + 0x2C) * 1.3f, -1, 15.0f,
                          0, 1, -1, 0, 0);
            func_PAL_002B15D8(s0, 1, (float *)D_L20_001A8F20_1, f21, 6.0f, f21, 6.0f, 0xFF);
        } else {
            func_PAL_002B15D8(s0, 1, (float *)D_L20_001A8F20_1, 3.0f, 6.0f, 3.0f, 6.0f, 0xFF);
        }
        func_PAL_L00_003281C0(s0, 1, 0.0f);
        func_002E5CF8(0, 0, s0);
        func_002A7750(s0, 3, -1);
        break;
    case 3:
        if (func_002B3868(s0) != 0) {
            *(u16 *)(s0 + 0x34) |= 1;
            *(u32 *)(s0 + 0x98) = 0;
            *(u8 *)(s0 + 0x31) = 0;
            *(u32 *)(s1 + 8) = 0x64;
        }
        if (func_00282948(s1 + 8) != 0) {
            func_0029F338(s0);
        }
        break;
    }
}
