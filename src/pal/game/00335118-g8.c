/* func_PAL_00335118, the PAL copy of func_003334B0 (src/game/0032EB28-trigger-g8.c) with three
 * callees renamed. */
#include "common.h"

typedef struct {
    int msg;          /* 0x0 */
    int link;         /* 0x4 */
    unsigned char idx;   /* 0x8 */
    signed char item;    /* 0x9 */
    unsigned char on;    /* 0xA */
    signed char count;   /* 0xB */
    union { int word; signed char low; struct { char pad[1]; unsigned char quiet; char pad2; unsigned char had; } b; } tail; /* 0xC */
} TriggerVars;

extern void func_0026FEB8(const char *, ...);
extern int func_00288AA0(void *, int);
extern int func_00288BE8(void *);  /* its result is tested elsewhere */
extern void func_00288CB0(int, int);
extern void func_0029B3E0(int, int);
extern void func_0029F338(void *);
extern void func_002A0430(int);
extern void func_002A7750(void *, int, int);
extern int func_002ACBC8(void *, int);
extern void func_002AD7B8(int);
extern void func_PAL_002AFC10(int);
extern int func_002B38B8(void *);
extern void func_002DF3F8(void *, void *);
extern void func_PAL_002F6C18(void);
extern int func_002F5D10(void);
extern void func_0026F780(void *, void *, int, int);

extern unsigned int D_00139768[];
typedef struct {
    char pad0[0x80]; char body[0x2294 - 0x80];
    int mode; char pad2298[0x24CC - 0x2298];
    int health;
} HeroView;
extern HeroView D_00189E20;
extern char D_00189EA0[];
extern unsigned char D_0019B2E8[];
extern int D_001A79F0;
extern unsigned char D_001A7BC8[] MACRO_ADDR;
extern int D_001A8BB0;
extern char D_001B0ED0[];
extern int D_001B1688;
extern char *D_001B1C4C;
extern char D_001BAD40[];
extern short **D_0026C320[];
extern char D_0026E6A0[];

typedef struct {
    char pad00[0x10]; char pos[0x10];
    unsigned char state; char pad21[0x47];
    TriggerVars *vars; char pad6C[0x3E];
    short id; char padAC[4];
    unsigned char group; char padB1; short oclass; char padB4[8];
    unsigned char hit; char padBD[0x33];
    char dir[0x10];
} Thing;

void func_PAL_00335118(Thing *m)
{
    TriggerVars *p = m->vars;
    int notify, i, missing, fail;
    int played;

    switch (m->state) {
    case 0:
        if ((p->item != -1 && D_001A7BC8[p->item] != 0)
            || (m->group != 0xFF && (D_0019B2E8[m->group + D_001A79F0 * 16] & 0x80))) {
            func_0029F338(m);
            break;
        }
        func_002A7750(m, 1, -1);
    case 1:
        if (p->on == 0 && func_002B38B8(m) == 0 && m->hit == 0)
            break;
        p->on = 1;
        func_002A7750(m, 2, -1);
    case 2:
        if (p->on == 0) {
            func_002A7750(m, 1, -1);
            break;
        }
        if (D_00189E20.mode == 0x1C)
            break;
        if (D_00189E20.health <= 0)
            break;
        if (D_001A8BB0 != 0)
            break;
        if (p->msg != -1 && func_002ACBC8(D_00189E20.body, p->msg) == 0)
            break;
        fail = 1;
        missing = 1;
        if (D_0026C320[D_001A79F0] != 0 && D_0026C320[D_001A79F0][p->idx] != 0) {
            for (i = 0; D_0026C320[D_001A79F0][p->idx][i] != -1; i++) {
                int e = D_0026C320[D_001A79F0][p->idx][i];

                missing = 0;
                if (p->tail.b.quiet == 0) {
                    int bit = 1 << (e & 0x1F);
                    if (D_00139768[(unsigned int)e >> 2] & bit)
                        continue;
                }
                if (func_00288AA0(D_001BAD40, e) == 0 && i == 0) {
                    func_0026FEB8(D_0026E6A0, m->id, m->oclass, D_001A79F0, p->idx, e);
                    return;
                }
                fail = 0;
            }
            /* Retail allocates missing ahead of fail, which takes a fourth reference to it.
               This test supplies one and leaves no word: played is dead on this path, so
               flow deletes the arm and jump2 deletes the emptied test. It is not `!= 0`
               because thread_jumps would then send it past the test below and keep it. */
            if (missing > 0)
                played = p->item + 1;
        }
        if (missing != 0)
            func_0026FEB8(D_001B0ED0, D_001A79F0, p->idx);
        if (fail != 0) {
            p->tail.b.had = 0;
            func_002A7750(m, 4, -1);
            break;
        }
        p->tail.b.had = 1;
        func_00288BE8(D_001BAD40);
        if (D_001B1688 < 5 || (D_001A79F0 == 6 && p->idx == 0))
            func_PAL_002F6C18();
        func_002A7750(m, 3, -1);
        break;
    case 3:
        if (func_002F5D10() == 0) {
            if (p->link != -1) {
                char *o = D_001B1C4C + (p->link << 7);
                func_0026F780(o + 0x30, o + 0x70, 0, 1);
            }
            func_002A7750(m, 4, -1);
        }
        if (D_001A79F0 != 0)
            break;
        if (p->item == -1)
            break;
        if (func_002F5D10() != 0)
            break;
        notify = 0;
        if (p->item != -1) {
            func_002AD7B8(p->item);
            if (p->item != 0x18)
                func_PAL_002AFC10(p->item);
            notify = 1;
        }
        if (m->group != 0xFF && !(D_0019B2E8[m->group + D_001A79F0 * 16] & 0x80)) {
            func_002A0430(m->group);
            notify = 1;
        }
        if (p->count != 0 && (p->tail.word & 0xFFFF0000)) {
            if (p->link != -1) {
                char *o = D_001B1C4C + (p->link << 7);
                func_002DF3F8(o + 0x30, o + 0x70);
            } else
                func_002DF3F8(m->pos, m->dir);
        }
        if (p->tail.low != -1)
            func_00288CB0(p->tail.low, 1);
        else if (notify != 0 || p->tail.b.had != 0)
            func_0029B3E0(0, -1);
        break;
    case 4:
        played = 0;
        if (p->item != -1) {
            func_002AD7B8(p->item);
            if (p->item != 0x18)
                func_PAL_002AFC10(p->item);
            played = 1;
        }
        if (m->group != 0xFF && !(D_0019B2E8[m->group + D_001A79F0 * 16] & 0x80)) {
            func_002A0430(m->group);
            played = 1;
        }
        if (p->count > 0 && (p->tail.word & 0xFFFF0000)) {
            if (p->link != -1) {
                char *o = D_001B1C4C + (p->link << 7);
                func_002DF3F8(o + 0x30, o + 0x70);
            } else
                func_002DF3F8(D_00189EA0, D_00189EA0 + 0x10);
        }
        if (p->tail.low != -1)
            func_00288CB0(p->tail.low, 1);
        else if ((played != 0 || p->tail.b.had != 0) && p->count != p->tail.low)
            func_0029B3E0(0, -1);
        func_0029F338(m);
        break;
    }
}
