/* functional: medium. Near-miss draft, not byte-compared in the latest sweep: paths the captured calls never take are unproven. */
/* func_L06_00455BC0: family F7, five level members with identical opcodes (L06, L10, L15,
   L18, L22, 1540 bytes each). Flags: -O2 -G8 -ffunction-sections. 1540/1540, 34 raw rows.
   Cases 3 and 4 now equal retail: notify = 1 goes after the 0x18 test, and case 4 has its own
   flag (s0 in retail, s2 in case 3).
   Not a landing form: `missing = 0` at the loop's end stands in for retail's preheader set, to
   give the 4 refs that fix the frame. It leaves missing in t2, not s5. Set at the loop's top it
   is hoisted as in retail, but has 3 refs and is spilled (1548 B, 300 rows).
   Retail's order is missing s5, fail s6, -1 s7, high fp, with the 1 unallocated, so missing must
   outrank fail (.0615): 4 refs across 118 insns gives .0678. Where the 4th ref comes from is open.
   Tried, all worse: a do/for wrapper with breaks, per-arm sets at the p->msg guard, a second
   test of missing, missing = fail = 1. */
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
extern void func_00288BE8(void *);
extern void func_00288CB0(int, int);
extern void func_0029B3E0(int, int);
extern void func_0029F338(void *);
extern void func_002A0430(int);
extern void func_002A7750(void *, int, int);
extern int func_002ACBC8(void *, int);
extern void func_002AD7B8(int);
extern void func_002AF0A8(int);
extern int func_002B38B8(void *);
extern void func_002DF3F8(void *, void *);
extern void func_002F5CC8(void);
extern int func_002F5D10(void);
extern void func_L00_002B9D60(void *, void *, int, int);

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
extern int D_L06_001A8F00;
extern char D_L06_001B1810[];
extern int D_L06_001B2348;
extern char *D_L06_001B290C;
extern char D_L06_001BFA40[];
extern short **D_L06_002AA490[];
extern char D_L06_002E2210[];

typedef struct {
    char pad00[0x10]; char pos[0x10];
    unsigned char state; char pad21[0x47];
    TriggerVars *vars; char pad6C[0x3E];
    short id; char padAC[4];
    unsigned char group; char padB1; short oclass; char padB4[8];
    unsigned char hit; char padBD[0x33];
    char dir[0x10];
} Thing;

void func_L06_00455BC0(Thing *m)
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
        if (D_L06_001A8F00 != 0)
            break;
        if (p->msg != -1 && func_002ACBC8(D_00189E20.body, p->msg) == 0)
            break;
        fail = 1;
        missing = 1;
        if (D_L06_002AA490[D_001A79F0] != 0 && D_L06_002AA490[D_001A79F0][p->idx] != 0) {
            for (i = 0; D_L06_002AA490[D_001A79F0][p->idx][i] != -1; i++) {
                int e = D_L06_002AA490[D_001A79F0][p->idx][i];
                if (p->tail.b.quiet == 0) {
                    int bit = 1 << (e & 0x1F);
                    if (D_00139768[(unsigned int)e >> 2] & bit)
                        continue;
                }
                if (func_00288AA0(D_L06_001BFA40, e) == 0 && i == 0) {
                    func_0026FEB8(D_L06_002E2210, m->id, m->oclass, D_001A79F0, p->idx, e);
                    return;
                }
                fail = 0;
                missing = 0;
            }
        }
        if (missing != 0)
            func_0026FEB8(D_L06_001B1810, D_001A79F0, p->idx);
        if (fail != 0) {
            p->tail.b.had = 0;
            func_002A7750(m, 4, -1);
            break;
        }
        p->tail.b.had = 1;
        func_00288BE8(D_L06_001BFA40);
        if (D_L06_001B2348 < 5 || (D_001A79F0 == 6 && p->idx == 0))
            func_002F5CC8();
        func_002A7750(m, 3, -1);
        break;
    case 3:
        if (func_002F5D10() == 0) {
            if (p->link != -1) {
                char *o = D_L06_001B290C + (p->link << 7);
                func_L00_002B9D60(o + 0x30, o + 0x70, 0, 1);
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
                func_002AF0A8(p->item);
            notify = 1;
        }
        if (m->group != 0xFF && !(D_0019B2E8[m->group + D_001A79F0 * 16] & 0x80)) {
            func_002A0430(m->group);
            notify = 1;
        }
        if (p->count != 0 && (p->tail.word & 0xFFFF0000)) {
            if (p->link != -1) {
                char *o = D_L06_001B290C + (p->link << 7);
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
                func_002AF0A8(p->item);
            played = 1;
        }
        if (m->group != 0xFF && !(D_0019B2E8[m->group + D_001A79F0 * 16] & 0x80)) {
            func_002A0430(m->group);
            played = 1;
        }
        if (p->count > 0 && (p->tail.word & 0xFFFF0000)) {
            if (p->link != -1) {
                char *o = D_L06_001B290C + (p->link << 7);
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
