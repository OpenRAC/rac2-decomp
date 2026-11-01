#include "include_asm.h"

#include "common.h"
typedef int TI __attribute__((mode(TI)));
typedef struct {
    s32 busy;
} Vars43FB08;
typedef struct {
    u8 pad00[0x20];
    u8 state;
    u8 pad21[0x68 - 0x21];
    Vars43FB08 *vars;
    u8 pad6C[0xA8 - 0x6C];
    u8 alpha;
    u8 padA9;
    s16 uid;
    u8 padAC[0xD0 - 0xAC];
    f32 dir[4];
} Moby43FB08;
extern s32 D_L18_001B1CB0[2] __attribute__((sda));
extern s32 D_L18_001B1CB8[2] __attribute__((sda));
extern s32 D_L18_001B1CE0 __attribute__((sda));
extern s32 D_L18_001B1CE4 __attribute__((sda));
extern s32 D_L18_001B1CE8 __attribute__((sda));
extern void func_00282CC0(void *, void *, void *);
extern void func_00282CF0(void *, void *, void *);
extern void func_00282D30(void *, void *, float);
extern void func_0029F338(void *);
extern void func_002A7750(void *, int, int);
extern float func_002A7878(float, float);
extern void *func_002A9640(void *, u32, s32);
extern int func_002E5DA0(int, int, void *, int);
extern void func_PAL_L00_0032C328(void *, void *, void *, void *, int, int, int, int, int, int, int);

void func_PAL_L18_00444F60(Moby43FB08 *self) {
    f32 lo[4] __attribute__((aligned(16)));
    f32 hi[4] __attribute__((aligned(16)));
    f32 ext[4] __attribute__((aligned(16)));
    Vars43FB08 *vars = self->vars;

    switch (self->state) {
    case 0:
        func_002A7750(self, 1, -1);
        break;
    case 1:
        if (func_002A9640(self, 0x4010000, 0) != 0 && vars->busy == 0) {
            *(TI *)ext = 0;
            ext[0] = 3.0f;
            ext[1] = 3.0f;
            func_00282D30(lo, self->dir, -func_002A7878(6.0f, 8.0f));
            qcopy(hi, lo);
            func_00282CF0(lo, lo, ext);
            func_00282CC0(hi, hi, ext);
            func_PAL_L00_0032C328(self, lo, D_L18_001B1CB8, D_L18_001B1CB0, D_L18_001B1CE4, -1,
                              D_L18_001B1CE0, 9, D_L18_001B1CE8, 0xFF, 0);
            func_002E5DA0(0, 0, self, self->uid);
            func_0029F338(self);
        } else {
            self->alpha = 0xFF;
        }
        break;
    case 2:
        break;
    }
}
