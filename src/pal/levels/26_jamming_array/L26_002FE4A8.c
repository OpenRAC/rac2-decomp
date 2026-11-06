#include "include_asm.h"
#include "common.h"

typedef unsigned int Quad __attribute__((mode(TI)));
typedef union { Quad q; float f[4]; } Vec;
typedef struct {
    char pad[0x30];
    int mode, timer;
    char gap38[0x44 - 0x38];
    short count;
    char gap46[0x18C - 0x46];
    char *parts[0];
} Hero;
extern Hero D_L26_001BC880;
typedef struct { char pad[0x34]; unsigned short flags; char gap[0xAA - 0x36]; short id; } Object;
extern int D_001A79F0[] __attribute__((sda));
extern float D_L26_001A9450[][4] SDATA(D_L26_001A9450);
extern float D_L26_001A9420[] __attribute__((sda));
extern float D_L26_001A9420_gp SDATA(D_L26_001A9420);
extern unsigned int D_L26_001A9428[] __attribute__((sda));
extern unsigned int D_L26_001A9428_gp SDATA(D_L26_001A9428);
extern int D_L26_001A9430[] __attribute__((sda));
extern int D_L26_001A9430_gp SDATA(D_L26_001A9430);
extern void func_L00_002FC980(void);
extern void func_PAL_002E7270(void *);
extern void func_L00_00326048(char *, float *, int, int, float);
extern void func_0029FC20(char *, int, char *);
extern void func_002830C0(void *, void *, void *);
extern void func_00282F20(void *, void *, float);
extern unsigned int func_00283D38(unsigned int, unsigned int, float);
extern char *func_002BAA28(void *, void *, void *, unsigned int, unsigned int, int, int, int, int);
extern int func_00283CF0(float);
extern float func_002A7878(float, float);
extern int func_002A7820(int, int);

/* func_PAL_L26_002FE890, the PAL copy of func_L26_002FCCC0: the same C, where the id 4000 call also
   requires D_001A79F0 != 51, its angle and the particle velocity scale by 6/5, the timer limit is 217
   and kind, duration and size take the 50 Hz scale. func_002E64A0 becomes func_PAL_002E7270. The
   bounds after the first three are read at offsets from D_L26_001A9430 and -1 is passed directly:
   the offset form keeps those absolute macro loads out of call delay slots, and a local for -1 moves
   the stack argument's store after the register moves. */
void func_PAL_L26_002FE890(void) {
    Vec transform[4];
    Vec position;
    Vec velocity;
    Vec acceleration;
    Hero *hero;
    char **slot;
    char *object;
    char *effect;
    unsigned int color;
    int kind;
    int duration;
    int size;
    int i;
    int j;
    func_L00_002FC980();
    for (i = 0; i < D_L26_001BC880.count; i++) {
        hero = &D_L26_001BC880;
        slot = &hero->parts[i];
        object = *slot;
        if (object && ((Object *)object)->id == 0xE29) {
            ((Object *)object)->flags |= 0x800;
        }
        if (((Object *)object)->id == 0xD54) func_PAL_002E7270(object);
        if (object && *(short *)(object + 0xAA) == 4000 && D_001A79F0[0] != 51 && *(char **)(object + 0x68))
            func_L00_00326048(object, (float *)(*(char **)(object + 0x68) + 0xC),
                              (int)0x80AAAAD2, (int)0x80396464, 0.07330384f);
    }
    if (D_001A79F0[0] == 26 && D_L26_001BC880.mode == 0 && D_L26_001BC880.timer < 217) {
        object = D_L26_001BC880.parts[3];
        func_0029FC20(object, 0, (char *)transform);
        object += 0x10;
        qcopy((transform + 3), object);
        for (j = 0; j < 8; j++) {
            func_002830C0(&position, D_L26_001A9450[j & 1], transform);
            func_00282F20(&velocity, transform, 0.080000006f);
            velocity.f[3] = D_L26_001A9420_gp;
            qzero_nc(&acceleration);
            acceleration.f[3] = D_L26_001A9420[1];
            color = func_00283D38(D_L26_001A9428_gp, D_L26_001A9428[1], func_002A7878(0.0f, 1.0f));
            {
                unsigned int rgb = color & 0xFFFFFF;
                kind = (func_002A7820(D_L26_001A9430_gp, D_L26_001A9430[1]) * 5 + 2) / 6;
                duration = (func_002A7820(D_L26_001A9430[2], D_L26_001A9430[3]) * 5 + 2) / 6;
                size = (func_002A7820(D_L26_001A9430[4], D_L26_001A9430[5]) * 5 + 2) / 6;
                effect = func_002BAA28(&position, &velocity, &acceleration, color, rgb,
                                       kind, duration, size, -1);
                if (effect) effect[9] = func_00283CF0(2.0f) - 16;
            }
        }
    }
}
