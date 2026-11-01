#include "include_asm.h"

void func_PAL_002D6730(short param_1, int param_2, int *param_3);

void func_PAL_002D6A70(int param_1)
{
  int auStack_20[4];

  auStack_20[0] = 0;
  func_PAL_002D6730(*(short *)(param_1 + 2), *(int *)(param_1 + 4), &auStack_20[0]);
  return;
}

typedef struct { char pad[4]; short mode; } Mode2D6E78;
typedef struct { char pad[0x29C]; int flags[5]; int selected; } Map2D6E78;
typedef struct { char pad[0xDB]; unsigned char active; char padDC[0x118 - 0xDC]; char *loaded; unsigned int limit; } State2D6E78;
extern Mode2D6E78 D_001A63A8;
extern Map2D6E78 D_001C4FA0;
extern State2D6E78 D_001F2840;
extern unsigned char D_001F291B;
extern void func_002B7AD0(void);
extern void func_002B7AD0(void);

int func_PAL_002D7AA8(void)
{
    if (D_001A63A8.mode == 0) {
        Map2D6E78 *map = &D_001C4FA0;
        int index = map->selected;
        if (index != -1) {
            D_001F291B = 0;
            map->flags[index] ^= 0x1000;
            map->selected = -1;
        }
    }
    if (D_001A63A8.mode != 0) {
        State2D6E78 *state = &D_001F2840;
        if (state->active != 0) {
            Map2D6E78 *map;
            func_002B7AD0();
            state->active = 0;
            map = &D_001C4FA0;
            map->flags[map->selected] = -1;
            map->selected = -1;
        }
    }
    return 0;
}

extern void func_0029D830(int *);
extern int func_0029DB28(unsigned int, unsigned int, unsigned int, int);
extern int D_001C51D0;
typedef struct { char pad[0x34]; int f34; int f38; int f3C; } Base2D75E8;
extern Base2D75E8 D_0025A6E0;
extern int D_0025A620[];

int func_PAL_002D8228(int *arg0)
{
    func_0029D830(arg0);
    *(int *)((char *)arg0 + 0xA0) = func_0029DB28(0x70000000, 0, 0x70000100, 1);
    {
        char *base = (char *)arg0 + 0x30;
        int index = D_001C51D0;

        if (*(int *)(base + (index << 2)) != -1) {
            D_0025A6E0.f3C = -0x240;
            D_0025A6E0.f34 = *(int *)(0x70000000 + 4 * *(int *)(base + (index << 2)));
            *(int *)D_0025A620 = *(int *)(0x70000100 + 4 * *(int *)(base + (index << 2)));
        }
    }
    *(int *)((char *)arg0 + 0xA4) = 0;
    return 0;
}

unsigned int func_PAL_002D61B0(void)
{
    return 0;
}

unsigned int func_PAL_002D6540(void)
{
    return 0;
}

extern int D_00138344;
extern void func_PAL_0029CD38(int);
extern int D_00138344;
extern void func_PAL_0029CD38(int);

int func_PAL_002D64D0(void) {
    func_PAL_0029CD38(D_00138344);
    return 0;
}
