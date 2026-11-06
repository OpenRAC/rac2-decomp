/* func_US2_L09_003E46F8, the USA v2.00 copy of func_L09_003E3288: the same C, where rename func_002B0A18 becomes func_US2_002B1880; rename func_00288E18 becomes func_US2_00289840. */
#include "common.h"

/* func_L09_003FE3B0 and func_US2_L09_003E46F8 of L09_002F8BA0.c, in a unit of their own: retail's
   gcse ran on the unsplit flow graph here (-frac2-gcse-unsplit-edges, config/cflags.txt). With the
   critical edge from the peeled first comparison into the scan loop split, PRE puts the
   next-track-pointer add at the end of both peeled arms and the two successful-search exits no
   longer cross-jump. In func_US2_L09_003E46F8, without the split, PRE puts the moby's state-byte load
   at the end of the 0xD0F test, where the class is still live in $v0, so the byte takes $v1 as in
   retail; the split edge block would take it instead and leave the byte in $v0. */

extern unsigned char D_001395B8[];
typedef struct { char pad[0x1bc]; unsigned short flag; char pad2[2]; unsigned int time; } DobboClock;
extern DobboClock D_0018C750;
typedef struct { char pad[0x2c0]; int first; char pad2[0x11c]; int second; char pad3[0x20]; int third; char pad4[0x24]; unsigned short flag; } DobboDialogue;
extern DobboDialogue D_0018C958;
typedef struct { char pad[0x80]; char position[0x10]; char pad2[0x128]; int field1b8; char pad3[0x20d8]; int field2294; } DobboPlayer;
extern DobboPlayer D_00189E20;
extern int D_001397C4;
extern unsigned char D_001A7A60[] __attribute__((sda)), D_001A7B08[] __attribute__((sda));
extern short D_001A7A10[] __attribute__((sda));
extern unsigned int D_001A7390 MACRO_ADDR;
extern int D_L09_001A9040[] __attribute__((sda)), D_L09_001A903C[] __attribute__((sda));
typedef struct {
    int region[4];
    int entered;
    int hint14;
    int hint18;
    int hint1c;
    char pad20[0xc];
    int f2c;
    char pad30[0x28];
    int scan;
    int count;
} RegionState;
typedef struct { char pad[0x3d6]; short busy; } ScanVars;
typedef struct {
    char pad00[0x20];
    unsigned char state;
    char pad21[0xf];
    unsigned char alpha;
    char pad31[0x37];
    ScanVars *vars;
    char pad6c[0x3e];
    short oClass;
    char padac[0x54];
} ScanMoby;
extern ScanMoby *D_L09_001B285C MACRO_ADDR, *D_L09_001B2860 MACRO_ADDR;
extern int func_002ACBC8(void *, int);
extern int func_US2_00289840(int, int);
extern void func_US2_002B1880(int, int);
extern int func_002E5E58(int, int, void *);

/* Walks the record's track while its signed halfwords stay non-negative and returns the
   entry whose measured value is largest, skipping the entries whose field 0xB2 is in the
   twenty-value screen table. */
void func_US2_L09_003E46F8(unsigned char *object)
{
    RegionState *s = *(RegionState **)(object + 0x68);
    ScanMoby *m;
    int i;

    if (!object[0x20]) {
        object[0x20] = 1;
        object[0x30] = 255;
        s->entered = 0;
        if (D_001395B8[0x7a] >= 126)
            D_001395B8[0x7a] = 125;
        if (D_001395B8[0x79] >= 126)
            D_001395B8[0x79] = 125;
        s->f2c = 0;
    }
    if (object[0x20] != 1)
        return;

    /* Scan 40 mobys a frame, counting those of five classes whose state byte is non-negative
       (a busy 0xD30 or an 0xD0F in state 5 is skipped). A full pass that counts none sets the
       done flag once and makes the two calls. The regions below are point-in-cuboid tests on the
       player's position that play hint lines. */
    if (D_L09_001A9040[0] && !D_001A7A60[12]) {
        for (i = 0; i < 40; i++) {
            m = &D_L09_001B285C[s->scan];
            if (m->oClass == 0xd0f || m->oClass == 0xd57 || m->oClass == 0xd30 ||
                m->oClass == 0xcbc || m->oClass == 0xd90) {
                if (m->oClass == 0xd30 && m->vars->busy) {
                    s->scan++;
                    continue;
                }
                if (m->oClass == 0xd0f) {
                    int state = m->state;
                    if (state == 5) {
                        s->scan++;
                        continue;
                    }
                }
                {
                    int state = m->state;
                    if ((signed char)state >= 0)
                        s->count++;
                }
            }
            s->scan++;
            if (&D_L09_001B285C[s->scan] >= D_L09_001B2860) {
                if (!s->count && !D_001A7A60[12]) {
                    D_001A7A60[12] = 1;
                    func_002E5E58(1, 0, 0);
                    func_US2_002B1880(0x1233, -1);
                    D_L09_001A903C[0] = 1;
                }
                s->scan = 0;
                s->count = 0;
            }
        }
    }

    if (!D_0018C958.flag && D_001397C4 < 0 && !D_001A7B08[5]) {
        if (func_002ACBC8(D_00189E20.position, s->region[0]))
            func_US2_00289840(0xa02, 0x59);
    }
    if (func_002ACBC8(D_00189E20.position, s->region[1]))
        s->entered = 1;
    if (D_00189E20.field2294 == 0x39 && !D_00189E20.field1b8 && s->entered)
        D_001395B8[0x7a]++;
    if (D_001A7A10[4] <= 0 && func_002ACBC8(D_00189E20.position, s->region[1])) {
        if (D_001395B8[0x7a] % 5 == 4 && !s->hint1c && D_00189E20.field2294 != 0x39) {
            if (D_0018C958.second >= 0)
                func_US2_00289840(0x9fb, 0x52);
            s->hint1c = 1;
            D_001395B8[0x7a]++;
        }
    }
    if (func_002ACBC8(D_00189E20.position, s->region[2])) {
        if (D_00189E20.field2294 == 0x39 && !D_00189E20.field1b8)
            D_001395B8[0x79]++;
    }
    if (!D_001A7B08[7] && func_002ACBC8(D_00189E20.position, s->region[2])) {
        if (D_001395B8[0x79] % 5 == 4 && !s->hint18 && D_00189E20.field2294 != 0x39) {
            if (D_0018C958.third >= 0)
                func_US2_00289840(0x9fe, 0x55);
            s->hint18 = 1;
            D_001395B8[0x79]++;
        }
    }
    if (func_002ACBC8(D_00189E20.position, s->region[3])) {
        if ((!D_0018C750.flag || D_001A7390 - D_0018C750.time > 432000) &&
            D_001395B8[0x7d] < 3 && !s->hint14) {
            if (D_0018C958.first >= 0)
                func_US2_00289840(0x9e3, 0x3a);
            D_001395B8[0x7d]++;
            s->hint14 = 1;
        }
    }
}
