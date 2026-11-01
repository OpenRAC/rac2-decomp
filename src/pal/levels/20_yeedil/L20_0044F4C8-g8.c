#include "include_asm.h"

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
extern int D_L20_001A8F00;
extern char *D_0018A3E0 __attribute__((nosda));
extern float D_L20_001B23E0 __attribute__((sda));
extern float D_L20_001B23E4 __attribute__((sda));
extern int D_L20_001B2AC8;
extern void func_L20_00449A78(char *);
extern void func_L20_00449AE8(char *);
extern void func_L20_00449BB0(char *);
extern void func_PAL_L01_0031C9C0(void *, void *, float, float, float, int);
extern float func_002A89A8(char *, int, float);
extern float func_00282C48(float);
extern int func_00282948(int *);
typedef struct {
    char pad0[0x20];
    float x20;
    u16 x24;
    char pad26[0x50 - 0x26];
    char x50[0x20];
    u32 x70;
    char pad74[0x84 - 0x74];
    float x84;
    float x88;
    char pad8C[0xA0 - 0x8C];
    int xA0;
    char padA4[0xA8 - 0xA4];
    int xA8;
    u32 xAC;
} State;

void func_PAL_L20_0044F4C8(char *arg0) {
    State *state = *(State **)(arg0 + 0x68);
    int mode;

    if (D_L20_001A8F00 == 2 && *(u8 *)(arg0 + 0x20) != 1) {
        func_L20_00449A78(arg0);
    }
    mode = *(u8 *)(arg0 + 0x20);
    switch (mode) {
    case 0:
        state->x20 = 1.0f;
        state->x24 = 1;
        state->x70 |= 6;
        state->x84 = D_L20_001B23E0;
        state->x88 = D_L20_001B23E4;
        func_L20_00449A78(arg0);
        return;
    case 1:
        return;
    case 2:
        func_PAL_L01_0031C9C0(arg0, state->x50, 0.0f, 0.5f, 0.6f, state->xA0);
        break;
    }
    if (D_0018A3E0 == arg0) {
        state->xAC = 1;
    }
    if (((D_L20_001B2AC8 & 0xF) == (((int)arg0 >> 8) & 0xF)
         && 5.0f < func_00282C48(*(float *)(arg0 + 0x18)
                                 - func_002A89A8(arg0 + 0x10, 0, 0.5f)))
        || (state->xAC != 0 && func_00282948(&state->xA8) != 0)) {
        func_L20_00449AE8(arg0);
    } else {
        func_L20_00449BB0(arg0);
    }
}
