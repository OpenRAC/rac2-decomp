/* functional: medium. Near-miss draft, not byte-compared in the latest sweep: paths the captured calls never take are unproven. */
/* Closer B, 2026-11-01: first draft from retail's control flow (no draft existed): 1608/1660 bytes, 0/27.
 * The body is a run of independent if statements over the Hero state; only the re-tests are missing:
 * retail re-derives (u8)state at each if (andi rN,a1,0xFF, 13 words) where cse and gcse keep one pseudo,
 * and a0 = masked state stands for the value inside the state 4 arm. int state plus (u8)state gives the
 * first andi. A u8 local gives none; a one-byte struct local gives none. -fno-gcse: 1616 bytes;
 * -fno-cse-skip-blocks -fno-cse-follow-jumps: 1652 bytes (same re-test signature as func_002CF5B0,
 * which is why no source form was found). Those flags are not landable. Profile: -O2 -G8
 * -ffunction-sections -g. Why the andi goes: the zero_extends survive to gcse (13 left), and combine drops
 * the rest because the byte load's upper bits are known; a second byte-load set of state changes nothing.
 * Retail's a1 behaves like an unpromoted QImode pseudo (lbu, andi at each use, sb raw). Next: a C form
 * that leaves one, not more spellings of the arms.
 */
#include "common.h"
typedef union { u8 b[0x2600]; s16 h[0x1300]; s32 i[0x980]; } Hero;
extern char D_00189E20[];
typedef struct {
    float a[4];
    float b[4];
    char pad20[0x10];
    char sound[0x94];
    u8 state, prev;
    short timer;
    float rate, rate2, level;
    short timer2;
    u8 pad[1];
    u8 flag;
} Anim;
extern float func_00283CE0(int);
extern int func_00282978(void *);
extern void func_003349E8(void *, int, float);
extern int D_L00_001B1588 __attribute__((sda));
extern u16 D_L00_001B1518 __attribute__((sda)), D_L00_001B152C __attribute__((sda)), D_L00_001B1530 __attribute__((sda)), D_L00_001B1534 __attribute__((sda));
extern u16 D_L00_001B1540 __attribute__((sda)), D_L00_001B1544 __attribute__((sda)), D_L00_001B1548 __attribute__((sda)), D_L00_001B1550 __attribute__((sda));
extern u16 D_L00_001B1554 __attribute__((sda)), D_L00_001B1558 __attribute__((sda)), D_L00_001B1560 __attribute__((sda)), D_L00_001B156C __attribute__((sda));
extern float D_L00_001B153C __attribute__((sda)), D_L00_001B154C __attribute__((sda)), D_L00_001B155C __attribute__((sda)), D_L00_001B1570 __attribute__((sda));
#define H_STATE ((Hero *)D_00189E20)->i[0x8A5]
#define H_CTRL ((Hero *)D_00189E20)->i[0x8A7]
#define GO(n, t) { s->prev = state; s->state = n; s->timer = t; s->rate = 1.0f / func_00283CE0(s->timer); return; }
#define AIM(n, t2, lv, fl, snd, from, to) { float one = 1.0f; \
    s->prev = state; s->state = n; \
    s->timer2 = t2; s->rate2 = one / func_00283CE0(s->timer2); \
    s->timer = D_L00_001B1544 ; s->rate = one / func_00283CE0(s->timer); \
    s->level = lv; s->flag = 0; \
    func_003349E8(snd, fl, lv); \
    qcopy(to, from); return; }
#define AIM5(n, t2, lv, fl, snd, from, to) { float one = 1.0f; \
    s->prev = state; s->state = n; \
    s->timer2 = t2; s->rate2 = one / func_00283CE0(s->timer2); \
    s->timer = D_L00_001B1554 ; s->rate = one / func_00283CE0(s->timer); \
    s->level = lv; s->flag = 0; \
    func_003349E8(snd, fl, lv); \
    qcopy(to, from); return; }
void func_L00_00420C38(char *moby)
{
    char *p = *(char **)(moby + 0x70);
    Anim *s = (Anim *)(p + 0x60);
    int state;
    if (D_L00_001B1588) { D_L00_001B1588 = 0; return; }
    state = s->state;
    if ((u8)state == 0) {
        if (H_CTRL == 2 || H_CTRL == 30) GO(1, D_L00_001B1530)
        if (H_STATE == 15) AIM(3, D_L00_001B1540, D_L00_001B154C, 1, p + 0x90, p + 0x70, p + 0x80)
        if (H_STATE == 12) GO(8, D_L00_001B1554)
        if (H_STATE == 11) AIM(6, D_L00_001B1534, D_L00_001B153C, 0, p + 0x90, p + 0x70, p + 0x80)
        if ((unsigned)(H_STATE - 13) < 2) {
            AIM5(5, D_L00_001B1550, D_L00_001B155C, 1, p + 0x90, p + 0x70, p + 0x80)
        }
        if (H_CTRL == 4) GO(2, D_L00_001B152C)
        return;
    }
    if ((u8)state == 2 && (H_STATE == 0x81 || H_STATE == 0x5B)) GO(1, D_L00_001B1530)
    if ((u8)state != 9 && (u8)state != 1 && H_STATE == 0x14) {
        s->prev = state; s->state = 9;
        s->timer2 = D_L00_001B1560;
        s->rate2 = 1.0f / func_00283CE0(s->timer2);
        s->flag = 0; s->timer = 0; s->rate = 1.0f; s->level = D_L00_001B1570;
        func_003349E8(s->sound, 1, D_L00_001B1570);
        qcopy(p + 0x80, p + 0x70);
        return;
    }
    if ((u8)(state - 1) < 2 && H_CTRL != 4 && H_CTRL != 2 && H_CTRL != 30 && H_STATE != 0x81) {
        s->state = 0; s->rate = 1.0f; s->timer = 0;
        return;
    }
    if ((u8)state == 7) {
        if (!((Hero *)D_00189E20)->b[0x49E]) AIM(6, D_L00_001B1534, D_L00_001B153C, 1, s->sound, p + 0x70, p + 0x80)
        if (H_CTRL == 2) GO(1, D_L00_001B1548)
    }
    if ((u8)state == 4 && H_CTRL != state) {
        s->prev = state;
        if (H_CTRL == 2) s->state = 1; else s->state = 0;
        s->timer = D_L00_001B1548; s->rate = 1.0f / func_00283CE0(s->timer);
        return;
    }
    if ((u8)state == 3 && H_STATE == 11) AIM(6, D_L00_001B1534, D_L00_001B153C, 1, s->sound, p + 0x70, p + 0x80)
    if ((u8)state == 5 && H_STATE == 12) GO(8, D_L00_001B1554)
    if ((u8)state == 8 && H_STATE != 12) GO(0, D_L00_001B1558)
    if ((u8)state == 6 && H_STATE != 11) GO(0, D_L00_001B1548)
    if (((u8)state == 3 || (u8)state == 5) && H_CTRL != 4) GO(0, D_L00_001B1548)
    if (((u8)state == 9 && (H_CTRL == 2 || ((Hero *)D_00189E20)->h[0x1A6] >= 0x37)) ||
        ((u8)state == 10 && (H_CTRL == 2 || ((Hero *)D_00189E20)->h[0x1A6] >= 0x37))) {
        float one = 1.0f;
        char *q;
        s->prev = state; s->state = 1;
        s->timer = D_L00_001B1548;
        s->rate = one / func_00283CE0(s->timer);
        q = *(char **)(moby + 0x70);
        *(short *)(q + 0x20) = D_L00_001B1518;
        q += 0x20;
        *(float *)(q + 0x24) = one / func_00283CE0(*(short *)q);
        qcopy(moby + 0x40, moby);
        return;
    }
    if ((u8)state == 9 && H_STATE != 0x14) GO(10, D_L00_001B156C)
    if ((u8)state == 10 && func_00282978(&s->timer2)) {
        s->prev = s->state; s->state = 0;
        s->timer = D_L00_001B1548; s->rate = 1.0f / func_00283CE0(s->timer);
    }
}
