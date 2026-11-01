/* func_00315E20: near miss, 1064/1064 bytes, boot (USA v1.01, 1 November 2026).

   Profile: its own `-g8` unit, `-O2 -G8 -ffunction-sections -frac2-zero-ti-por` (the timer at
   0x1AF548 is $gp-relative, the stack vector clear stays `por` + `sq`). The jump table runs
   0..4 in order, case 0 falls into case 1. The two `D_00189E20` reads outside the cases go
   through their own locals so the offsets stay out of %lo and the hoisted `lui` is shared;
   the state is a struct so the timer stores do not wait for `st->target` (GCC's fixed
   scalar against varying struct rule); the two vector copies are qcopy.

   Everything matches but case 2's first block: retail puts the 0xC20 clear in the delay
   slot of the counter test (here it lands after the increment; written before the test it
   costs a branch-likely and 4 bytes), and retail stores launch.flags before the levels
   word while loading D_0013958C ahead of D_001A79F0. Tried: the clear before and after the
   counter, a typed player struct, the counters as fixed u16/u32 scalars, every order of the
   five launch/statistics statements and of the five launch tail stores, -fstrict-aliasing
   (fixes the clear, reorders the launch stores). */

#include "common.h"

typedef int Quad __attribute__((mode(TI)));

/* One of the three 0xA0-byte effect slots of D_0022AA10, filled by func_00316400. */
typedef struct {
    char pad0[0x8C];
    void *owner;                /* 0x8C: 0 for a free slot */
    char pad90[0x10];
} PoolEffect_00315E20;

typedef struct { u16 count; u16 pad; u32 maximum; u32 levels; } Statistics;

/* The launch record func_002A8E20 takes. */
typedef struct {
    float dir[4];
    void *owner;
    int flags;
    u8 kind;
    u8 mode;
    u16 klass;
    float range;
    int count;
} Launch_00315E20;

/* The launcher's state. */
typedef struct { char pad0[0x18]; char *target; } State_00315E20;

extern PoolEffect_00315E20 D_0022AA10[3];
extern char D_00189E20[];
extern Statistics D_0018C360[];
extern char D_001B2510[] __attribute__((sda));
extern char D_001B2520[] __attribute__((sda));
extern char D_001B5340[];
extern int D_001AF548 __attribute__((sda));
extern int D_00138324 __attribute__((nosda));
extern u32 D_001A7390 __attribute__((nosda));
extern u32 D_001A79F0 __attribute__((nosda));
extern u8 D_0013958C __attribute__((nosda));
/* One 0xE0-byte entry per weapon level. */
typedef struct { char pad0[0x70]; float range; char pad74[0x6C]; } Level_00315E20;

extern Level_00315E20 D_00239BA0[];

extern void func_0029FCC0(void *, int, void *);
extern unsigned int func_0026F748(int, int);
extern char *func_00315C78(void *);
extern float func_00282E48(void *, void *);
extern float func_00282C48(float);
extern void func_00273318(float, float, float, void *, u32, void *, int, int, int);
extern void func_00282CF0(void *, void *, void *);
extern void func_0026F758(void);
extern int func_00282948(void *);
extern void func_00282F70(void *, void *, float);
extern void func_002A8E20(void *, void *);
extern void func_00316400(void *, char *, int);
extern void func_003166C8(void *);
extern void func_0027CFD0(void *, void *);
extern void func_00316248(void *);

/* Update of the lock-on launcher: 0 clears the effect slots, 1 aims at the nearest target and
   waits for the fire button, 2 launches at it and starts three effects, 3 and 4 time the
   cool-down. */
void func_00315E20(u8 *obj)
{
    float dir[4];
    float aim[4];
    float pos[4];
    Launch_00315E20 launch;
    State_00315E20 *st = *(State_00315E20 **)(obj + 0x68);
    char *p;
    char *q;
    float d;
    int i;

    *(Quad *)dir = 0;
    if (obj[0x20] == 0) {
        for (i = 2; i >= 0; i--)
            D_0022AA10[i].owner = 0;
        obj[0x20] = 1;
    }
    func_0029FCC0(obj, 1, D_001B2510);
    func_0029FCC0(obj, 0, D_001B2520);
    q = D_00189E20;
    if (*(int *)(q + 0x2294) == 1)
        func_0026F748(0x1D, 1);
    func_0029FCC0(obj, 0, aim);

    switch (obj[0x20]) {
    case 0:
        obj[0x20] = 1;
        st->target = 0;
    case 1:
        p = D_00189E20;
        if (*(u8 *)(p + 0x22BC) != 0)
            break;
        st->target = func_00315C78(obj);
        if (st->target != 0) {
            d = func_00282E48(D_001B5340, st->target + 0x10) * 0.02f;
            qcopy(pos, st->target + 0x10);
            func_00273318(func_00282C48(0.9f - d * 0.65f), 0.0f, 90.0f, obj, 0xFF0FFF0F, pos, 0x26,
                          -1, 4);
            func_00282CF0(dir, st->target + 0x10, aim);
        }
        if (!(D_00138324 & *(int *)(p + 0x1230)))
            break;
        if (st->target == 0)
            break;
        if (*(int *)(p + 0x340) != 0)
            D_001AF548 = 12;
        else
            D_001AF548 = 4;
        obj[0x20] = 2;
        func_0026F758();
        break;
    case 2:
        if (!func_00282948(&D_001AF548))
            break;
        p = D_00189E20;
        if (D_0018C360[36].count < 0xFFFF)
            D_0018C360[36].count++;
        *(int *)(p + 0xC20) = 0;
        if (D_0018C360[36].maximum < D_001A7390)
            D_0018C360[36].maximum = D_001A7390;
        D_0018C360[36].levels = D_0018C360[36].levels | (1 << D_001A79F0) | 0x80000000;
        launch.flags = 0x10000;
        launch.range = D_00239BA0[D_0013958C].range;
        launch.count = 1;
        launch.owner = obj;
        qcopy(&launch, dir);
        func_00282F70(&launch, &launch, 1.0f);
        launch.mode = 2;
        launch.dir[2] = 1.0f;
        launch.dir[3] = 5627.925f;
        launch.klass = *(u16 *)(obj + 0xAA);
        launch.kind = 3;
        func_002A8E20(st->target, &launch);
        obj[0x20] = 3;
        if (*(int *)(p + 0x340)) {
            D_001AF548 = 15;
            func_00316400(obj, st->target, 7);
            func_00316400(obj, st->target, 7);
            func_00316400(obj, st->target, 7);
        } else {
            D_001AF548 = 3;
            func_00316400(obj, st->target, 3);
            func_00316400(obj, st->target, 3);
            func_00316400(obj, st->target, 3);
        }
        st->target = 0;
        break;
    case 3: {
        char *player;

        if (!func_00282948(&D_001AF548))
            break;
        player = D_00189E20;
        *(float *)(player + 0xC20) = 1.0f;
        D_001AF548 = 7;
        obj[0x20] = 4;
        break;
    }
    case 4:
        if (func_00282948(&D_001AF548))
            obj[0x20] = 1;
        break;
    }
    func_003166C8(obj);
    func_0027CFD0(func_00316248, obj);
}
