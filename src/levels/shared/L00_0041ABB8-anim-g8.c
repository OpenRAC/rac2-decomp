/* func_L00_00420C38 in its own unit: it reads the level's tuning values through $gp and is built
   with -g. The state byte has no local: every test re-reads s->state, gcse's reaching register for
   those loads is what stays in $a1 unmasked, and each compare keeps its own andi. */
#include "common.h"

/* The parts of the hero this state machine reads. */
typedef struct {
    char pad0[0x34C];
    short h34C;                   /* 0x34C */
    char pad34E[0x49E - 0x34E];
    u8 b49E;                      /* 0x49E */
    char pad49F[0x2294 - 0x49F];
    int state;                    /* 0x2294 */
    char pad2298[4];
    int ctrl;                     /* 0x229C */
} HeroAnim;

/* The animation state at +0x60 of the object's state. */
typedef struct {
    char pad0[0x10];
    float a[4];                   /* 0x10 */
    float b[4];                   /* 0x20 */
    char sound[0x94];             /* 0x30 */
    u8 state, prev;               /* 0xC4 */
    short timer;                  /* 0xC6 */
    float rate, rate2, level;     /* 0xC8 */
    short timer2;                 /* 0xD4 */
    u8 pad[1];
    u8 flag;                      /* 0xD7 */
} Anim;

extern HeroAnim D_00189E20;
extern float func_00283CE0(int);
extern int func_00282978(void *);
extern void func_003349E8(void *, int, float);
extern int D_L00_001B1588 __attribute__((sda));
extern u16 D_L00_001B1518 __attribute__((sda)), D_L00_001B152C __attribute__((sda)), D_L00_001B1530 __attribute__((sda)), D_L00_001B1534 __attribute__((sda));
extern u16 D_L00_001B1540 __attribute__((sda)), D_L00_001B1544 __attribute__((sda)), D_L00_001B1548 __attribute__((sda)), D_L00_001B1550 __attribute__((sda));
extern u16 D_L00_001B1554 __attribute__((sda)), D_L00_001B1558 __attribute__((sda)), D_L00_001B1560 __attribute__((sda)), D_L00_001B156C __attribute__((sda));
extern float D_L00_001B153C __attribute__((sda)), D_L00_001B154C __attribute__((sda)), D_L00_001B155C __attribute__((sda)), D_L00_001B1570 __attribute__((sda));

/* Switch to state n, with t frames of blend. */
#define GO(n, t) { s->prev = s->state; s->state = n; s->timer = t; s->rate = 1.0f / func_00283CE0(s->timer); return; }

/* Switch to aiming state n: start both blends, play the sound and keep the current pose. */
#define AIM(n, t2, t, lv, fl, snd, from, to) { float one = 1.0f; \
    s->prev = s->state; s->state = n; \
    s->timer2 = t2; s->rate2 = one / func_00283CE0(s->timer2); \
    s->timer = t; s->rate = one / func_00283CE0(s->timer); \
    s->level = lv; s->flag = 0; \
    func_003349E8(snd, fl, lv); \
    qcopy(to, from); return; }

void func_L00_00420C38(char *moby)
{
    char *p = *(char **)(moby + 0x70);
    Anim *s = (Anim *)(p + 0x60);
    if (D_L00_001B1588) { D_L00_001B1588 = 0; return; }
    if (s->state == 0) {
        if (D_00189E20.ctrl == 2 || D_00189E20.ctrl == 30) GO(1, D_L00_001B1530)
        if (D_00189E20.state == 15) AIM(3, D_L00_001B1540, D_L00_001B1544, D_L00_001B154C, 1, p + 0x90, p + 0x70, p + 0x80)
        if (D_00189E20.state == 12) GO(8, D_L00_001B1554)
        if (D_00189E20.state == 11) AIM(6, D_L00_001B1534, D_L00_001B1544, D_L00_001B153C, 0, p + 0x90, p + 0x70, p + 0x80)
        if ((unsigned)(D_00189E20.state - 13) < 2) {
            AIM(5, D_L00_001B1550, D_L00_001B1554, D_L00_001B155C, 1, p + 0x90, p + 0x70, p + 0x80)
        }
        if (D_00189E20.ctrl == 4) GO(2, D_L00_001B152C)
        return;
    }
    if (s->state == 2 && (D_00189E20.state == 0x81 || D_00189E20.state == 0x5B)) GO(1, D_L00_001B1530)
    if (s->state != 9 && s->state != 1 && D_00189E20.state == 0x14) {
        s->prev = s->state; s->state = 9;
        s->timer2 = D_L00_001B1560;
        s->rate2 = 1.0f / func_00283CE0(s->timer2);
        s->timer = 0; s->rate = 1.0f; s->level = D_L00_001B1570; s->flag = 0;
        func_003349E8(s->sound, 1, D_L00_001B1570);
        qcopy(s->b, s->a);
        return;
    }
    if ((s->state == 1 || s->state == 2) && D_00189E20.ctrl != 4 && D_00189E20.ctrl != 2 && D_00189E20.ctrl != 30 && D_00189E20.state != 0x81) {
        s->timer = 0; s->rate = 1.0f; s->state = 0;
        return;
    }
    if (s->state == 7) {
        if (!D_00189E20.b49E) AIM(6, D_L00_001B1534, D_L00_001B1544, D_L00_001B153C, 1, s->sound, s->a, s->b)
        if (D_00189E20.ctrl == 2) GO(1, D_L00_001B1548)
    }
    if (s->state == 4 && D_00189E20.ctrl != 4) {
        if (D_00189E20.ctrl == 2) {
            s->prev = 4; s->state = 1;
            s->timer = D_L00_001B1548; s->rate = 1.0f / func_00283CE0(s->timer);
            return;
        } else {
            s->prev = 4; s->state = 0;
            s->timer = D_L00_001B1548; s->rate = 1.0f / func_00283CE0(s->timer);
            return;
        }
    }
    if (s->state == 3 && D_00189E20.state == 11) AIM(6, D_L00_001B1534, D_L00_001B1544, D_L00_001B153C, 1, s->sound, s->a, s->b)
    if (s->state == 5 && D_00189E20.state == 12) GO(8, D_L00_001B1554)
    if (s->state == 8 && D_00189E20.state != 12) GO(0, D_L00_001B1558)
    if (s->state == 6 && D_00189E20.state != 11) GO(0, D_L00_001B1548)
    if ((s->state == 3 || s->state == 5) && D_00189E20.ctrl != 4) GO(0, D_L00_001B1548)
    if ((s->state == 9 && (D_00189E20.ctrl == 2 || D_00189E20.h34C >= 0x37)) ||
        (s->state == 10 && (D_00189E20.ctrl == 2 || D_00189E20.h34C >= 0x37))) {
        float one = 1.0f;
        char *q;
        s->prev = s->state; s->state = 1;
        s->timer = D_L00_001B1548;
        s->rate = one / func_00283CE0(s->timer);
        q = *(char **)(moby + 0x70) + 0x20;
        *(short *)q = D_L00_001B1518;
        *(float *)(q + 0x24) = one / func_00283CE0(*(short *)q);
        qcopy(moby + 0x40, moby);
        return;
    }
    if (s->state == 9 && D_00189E20.state != 0x14) GO(10, D_L00_001B156C)
    if (s->state == 10 && func_00282978(&s->timer2)) {
        s->prev = s->state; s->state = 0;
        s->timer = D_L00_001B1548; s->rate = 1.0f / func_00283CE0(s->timer);
    }
}
