#include "common.h"

extern char D_L00_0022F7C0[];
extern float D_L00_001B25E0[] __attribute__((sda));
extern int D_001A7B90[] __attribute__((sda));
extern int D_001A7340[] __attribute__((sda)), D_001A7344[] __attribute__((sda));
extern void func_002FC620(int, int, int, int);
extern int func_00282C30(int);
extern void func_00285548(int, int, int, int, int, int, unsigned int);
extern int func_0028E588(int, int);
extern double func_001234F0(float);
extern int func_00123028(double, double);
extern double func_00122A98(double, double);
extern int func_00123130(double);
extern void func_0028EA58(int, int, int, int, int, unsigned int *);

void func_L00_00376600(void) {
    unsigned int colors[4];
    char *model;
    int top;
    int bottom;
    int outer_top, outer_bottom, inner_top, inner_bottom;
    char *loop_model;
    int y;
    int start;
    int initial_y;
    char *scroll;
    int pulse;
    int relative;
    int x;
    int slot;
    int handle;
    int first_alpha;
    int second_alpha;
    unsigned int shade;
    double distance;
    unsigned int tint;
    initial_y = (int)(D_L00_001B25E0[0] * 185.0f + 0.5f);
    initial_y += D_001A7B90[0] ? 4 : 0;
    func_002FC620(48, 298, (int)(D_L00_001B25E0[0] * 120.0f + 0.5f), initial_y);
    scroll = D_L00_0022F7C0;
    if (*(int *)(scroll + 0x6C) < 0) *(int *)(scroll + 0x6C) += 4;
    else if (*(int *)(scroll + 0x6C) > 0) *(int *)(scroll + 0x6C) -= 4;
    model = D_L00_0022F7C0;
    pulse = func_00282C30(((*(int *)(model + 4) * 4) & 63) - 32) + 64;
    if (*(int *)(model + 0x144 + *(int *)(model + 0x80) * 12) > 0) {
        shade = pulse * 0x10202;
        outer_top = (int)(D_L00_001B25E0[0] * 123.0f + 0.5f);
        outer_bottom = (int)(D_L00_001B25E0[0] * 179.0f + 0.5f);
        outer_top += D_001A7B90[0] ? 4 : 0; outer_bottom += D_001A7B90[0] ? 4 : 0;
        func_00285548(101, outer_top, 157, outer_bottom, D_001A7340[0], D_001A7344[0],
                      shade | 0x80000000u);
        inner_top = (int)(D_L00_001B25E0[0] * 125.0f + 0.5f);
        inner_bottom = (int)(D_L00_001B25E0[0] * 177.0f + 0.5f);
        inner_top += D_001A7B90[0] ? 4 : 0; inner_bottom += D_001A7B90[0] ? 4 : 0;
        func_00285548(103, inner_top, 155, inner_bottom, D_001A7340[0], D_001A7344[0], 0x80442D00);
    }
    x = *(int *)(model + 0x6C) - 63;
    for (relative = -3; relative < 5; relative++, x += 56) {
        loop_model = D_L00_0022F7C0;
        slot = relative + *(int *)(loop_model + 0x80);
        if (slot < 0) continue;
        if (slot >= *(int *)(loop_model + 0x740)) continue;
        tint = 0xF0F0B0;
        handle = func_0028E588(*(int *)(D_L00_0022F7C0 + 0x140 + slot * 12), 0);
        distance = func_001234F0(150.0f - (float)(x + 2));
        if (func_00123028(distance, 0.0) < 0) distance = func_00122A98(0.0, distance);
        first_alpha = 128 - func_00123130(distance);
        distance = func_001234F0(150.0f - (float)(x + 40));
        if (func_00123028(distance, 0.0) < 0) distance = func_00122A98(0.0, distance);
        second_alpha = 128 - func_00123130(distance);
        if (first_alpha < 0) first_alpha = 0;
        if (second_alpha < 0) second_alpha = 0;
        first_alpha <<= 24;
        second_alpha <<= 24;
        colors[1] = second_alpha | tint;
        colors[0] = first_alpha | tint;
        colors[3] = second_alpha | tint;
        colors[2] = first_alpha | tint;
        y = (int)(D_L00_001B25E0[0] * 129.0f + 0.5f);
        y += D_001A7B90[0] ? 4 : 0;
        func_0028EA58(handle, x + 2, y, 40, (int)(D_L00_001B25E0[0] * 40.0f + 0.5f), colors);
    }
}
