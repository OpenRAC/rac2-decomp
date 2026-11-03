/* functional: high. From the near-miss draft (nonmatching/game/func_00315E20.c, every word but case 2's store order), with the matching-only tricks dropped: plain 16-byte copies for retail's lq/sq (qcopy) and the stack vector clear, plain struct fields. Same reads, writes and calls with the same arguments, in retail's order (case 2's clear of hero+0xC20 sits in a branch delay slot in retail, so it comes before the statistics counter store here too). 5627.9248046875f is retail's 0x45AFDF66 exactly. */

#include "common.h"

/* One of the three 0xA0-byte effect slots of D_0022AA10, filled by func_00316400. */
typedef struct {
    char pad0[0x8C];
    int owner; /* 0x8C: 0 for a free slot */
    char pad90[0x10];
} PoolEffect_00315E20;

typedef struct { unsigned short count; unsigned short pad; unsigned int maximum; unsigned int levels; } Statistics_00315E20;

/* The launch record func_002A8E20 takes (0x24 bytes used). */
typedef struct {
    float dir[4];
    void *owner;
    int flags;
    unsigned char kind;
    unsigned char mode;
    unsigned short klass;
    float range;
    int count;
} Launch_00315E20;

/* The launcher's state (obj + 0x68). */
typedef struct { char pad0[0x18]; char *target; } State_00315E20;

/* One 0xE0-byte entry per weapon. */
typedef struct { char pad0[0x70]; float range; char pad74[0x6C]; } Level_00315E20;

extern PoolEffect_00315E20 D_0022AA10[3];
extern char D_00189E20[];
extern Statistics_00315E20 D_0018C360[];
extern char D_001B2510[];
extern char D_001B2520[];
extern char D_001B5340[];
extern int D_001AF548 __attribute__((sda));
extern int D_00138324 NOT_SDA;
extern unsigned int D_001A7390 NOT_SDA;
extern unsigned int D_001A79F0 NOT_SDA;
extern unsigned char D_0013958C NOT_SDA;
extern Level_00315E20 D_00239BA0[];

extern void func_0029FCC0(void *, int, void *);
extern unsigned int func_0026F748(int, int);
extern char *func_00315C78(void *);
extern float func_00282E48(void *, void *);
extern float func_00282C48(float);
extern void func_00273318(float, float, float, void *, unsigned int, void *, int, int, int);
extern void func_00282CF0(void *, void *, void *);
extern void func_0026F758(void);
extern int func_00282948(int *);
extern void func_00282F70(void *, void *, float);
extern void func_002A8E20(void *, void *);
extern void func_00316400(void *, char *, int);
extern void func_003166C8(void *);
extern void func_0027CFD0(void *, void *);
extern void func_00316248(void *);

/* Update of the lock-on launcher: state 0 clears the effect slots, 1 aims at the nearest target (draws the lock
   reticle) and waits for the fire button, 2 launches at it, counts the shot in the statistics row 36 and starts three
   effects, 3 and 4 time the cool-down on the timer D_001AF548. */
void func_00315E20(unsigned char *obj)
{
    float dir[4];
    float aim[4];
    float pos[4];
    Launch_00315E20 launch;
    State_00315E20 *st;
    char *p;
    float d;
    int i;

    dir[0] = 0;
    dir[1] = 0;
    dir[2] = 0;
    dir[3] = 0;
    st = *(State_00315E20 **)(obj + 0x68);
    if (obj[0x20] == 0) {
        for (i = 2; i >= 0; i--) {
            D_0022AA10[i].owner = 0;
        }
        obj[0x20] = 1;
    }
    func_0029FCC0(obj, 1, D_001B2510);
    func_0029FCC0(obj, 0, D_001B2520);
    p = D_00189E20;
    if (*(int *)(p + 0x2294) == 1) {
        func_0026F748(0x1D, 1);
    }
    func_0029FCC0(obj, 0, aim);

    switch (obj[0x20]) {
    case 0:
        obj[0x20] = 1;
        st->target = 0;
        /* fall through */
    case 1:
        if (*(unsigned char *)(p + 0x22BC) != 0) {
            break;
        }
        st->target = func_00315C78(obj);
        if (st->target != 0) {
            d = func_00282E48(D_001B5340, st->target + 0x10) * 0.02f;
            for (i = 0; i < 4; i++) {
                pos[i] = ((float *)(st->target + 0x10))[i];
            }
            func_00273318(func_00282C48(0.9f - d * 0.65f), 0.0f, 90.0f, obj, 0xFF0FFF0F, pos, 0x26, -1, 4);
            func_00282CF0(dir, st->target + 0x10, aim);
        }
        if ((D_00138324 & *(int *)(p + 0x1230)) == 0) {
            break;
        }
        if (st->target == 0) {
            break;
        }
        if (*(int *)(p + 0x340) != 0) {
            D_001AF548 = 12;
        } else {
            D_001AF548 = 4;
        }
        obj[0x20] = 2;
        func_0026F758();
        break;
    case 2:
        if (func_00282948(&D_001AF548) == 0) {
            break;
        }
        *(int *)(p + 0xC20) = 0;
        if (D_0018C360[36].count < 0xFFFF) {
            D_0018C360[36].count++;
        }
        if (D_0018C360[36].maximum < D_001A7390) {
            D_0018C360[36].maximum = D_001A7390;
        }
        D_0018C360[36].levels = D_0018C360[36].levels | (1 << D_001A79F0) | 0x80000000;
        launch.flags = 0x10000;
        launch.range = D_00239BA0[D_0013958C].range;
        launch.count = 1;
        launch.owner = obj;
        for (i = 0; i < 4; i++) {
            launch.dir[i] = dir[i];
        }
        func_00282F70(&launch, &launch, 1.0f);
        launch.mode = 2;
        launch.dir[2] = 1.0f;
        launch.dir[3] = 5627.9248046875f;
        launch.klass = *(unsigned short *)(obj + 0xAA);
        launch.kind = 3;
        func_002A8E20(st->target, &launch);
        obj[0x20] = 3;
        if (*(int *)(p + 0x340) != 0) {
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
    case 3:
        if (func_00282948(&D_001AF548) == 0) {
            break;
        }
        *(float *)(p + 0xC20) = 1.0f;
        D_001AF548 = 7;
        obj[0x20] = 4;
        break;
    case 4:
        if (func_00282948(&D_001AF548) != 0) {
            obj[0x20] = 1;
        }
        break;
    }
    func_003166C8(obj);
    func_0027CFD0(func_00316248, obj);
}
