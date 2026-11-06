/* func_US2_L05_0041EFBC, the USA v2.00 copy of func_L05_0041DA20: the same C, without the loop that
   skipped unusable D_L05_002A1800 entries. D_L05_001B13DC now starts at 1, and D_L05_001B13E8 is set
   after the other flags. */
#include "common.h"

typedef struct {
    int id, pad4[4], count, pad18[3], enabled, pad28, pending;
    float radius;
    int pad34[6]; void *callbacks[3]; int pad58[8];
    char *object; int pad7C[5]; int mode; int pad94[2];
    int settings[4];
} Control05;
extern Control05 D_L05_00221D10;
typedef struct {
    int id, a4, a8, aC, a10;
    char pad14[0x28 - 0x14];
    int target; char pad2C[8]; int stage; char pad38[8];
    int warmup, delay, first, second, third, fourth, fifth, timeout;
} State05;
extern unsigned char D_001395B8[];
extern char D_00189E20[];
extern unsigned char D_L05_001B2000[] __attribute__((sda)), D_L05_001B2001[] __attribute__((sda)), D_L05_001B2002[] __attribute__((sda));
extern float D_L05_001B2004[] __attribute__((sda)), D_L05_001B2008[] __attribute__((sda)), D_L05_001B200C[] __attribute__((sda)), D_L05_001B2010[] __attribute__((sda));
extern int D_L05_001B2014[] __attribute__((sda));
extern unsigned char D_L05_001B3558[] __attribute__((sda)), D_L05_001B3559[] __attribute__((sda)), D_L05_001B355A[] __attribute__((sda));
extern float D_L05_001B355C[] __attribute__((sda)), D_L05_001B3560[] __attribute__((sda)), D_L05_001B3564[] __attribute__((sda)), D_L05_001B3568[] __attribute__((sda));
extern int D_L05_001B356C[] __attribute__((sda)), D_L05_001B3554[] __attribute__((sda));
extern int D_L05_001AA6A0[] __attribute__((sda)), D_L05_001AA6A8[] __attribute__((sda));
extern int D_L05_001B1354[] __attribute__((sda)), D_L05_001B1358[] __attribute__((sda)), D_L05_001B135C[] __attribute__((sda));
extern int D_L05_001A8F00[] __attribute__((sda));
extern int D_L05_001A904C MACRO_ADDR;
extern float D_L05_001B2D84[] __attribute__((sda));
extern char *D_L05_001B251C[] __attribute__((sda));
extern void func_L05_00379F18(int), func_L05_00379F28(int), func_L05_00379B60(void);
extern void func_L05_0030C930(int, int), func_L00_003294F0(void *, int);
extern int func_US2_L00_002C4560(int, int);
extern void func_L05_00379F48(int);
extern int func_US2_L05_00420238(void);
extern void func_L05_00445A98(void);
extern int func_US2_00289840(int, int);
extern int func_00282948(void *);
extern void func_US2_L05_00422838(void *), func_US2_L05_00422BB0(void *);
extern void func_US2_L05_00422D38(void *), func_US2_L05_00422E88(void *);
extern void func_US2_0029C548(int, void *);
extern int func_L05_00442860(void);
extern void func_L05_0041FD48(void), func_US2_L05_00421A98(void), func_US2_L05_0041F478(void);
extern int func_L05_0041FFF8(char *, int);
extern int D_L05_001B1360 __attribute__((sda));
extern int D_L05_001B13B0 __attribute__((sda));
extern int D_L05_001B13E8 __attribute__((sda));
extern int D_L05_001B13DC __attribute__((sda));
extern int D_L05_001B1364 __attribute__((sda));
extern int D_L05_001B13B4 __attribute__((sda));
extern int D_L05_001B13B8 __attribute__((sda));
extern int D_L05_001B13BC __attribute__((sda));
extern int D_L05_001B1390 __attribute__((sda));
extern int D_L05_001B1394 __attribute__((sda));
extern int D_L05_001B1398 __attribute__((sda));
extern int D_L05_001B13A8 __attribute__((sda));
extern int D_L05_001B13AC __attribute__((sda));
extern int D_L05_001B13D8 __attribute__((sda));
extern int D_L05_001B1350 __attribute__((sda));
extern int D_L05_001B13F4 __attribute__((sda));
extern int D_L05_001B13D4 __attribute__((sda));
extern int D_L05_001B13E0 __attribute__((sda));
extern int D_L05_001B2048 __attribute__((sda));
extern int D_L05_001B13F0 __attribute__((sda));
/* Per-frame update. The first frame resets the control record, the timers in the moby's state and
   the saved mode record and sets flags on the hero's moby; later frames run func_L05_00379B60 and,
   after five settled frames, put the hero in action 0x31 and dispatch on the mode in
   D_L05_001B1360. */
void func_US2_L05_0041EFBC(char *object)
{
    State05 *sub = *(State05 **)(object + 0x68);
    int one;
    char *hero, *p;
    switch ((unsigned char)object[0x20]) {
    case 0:
        *(short *)(object + 0x32) = 0x1FF;
        *(unsigned char *)(object + 0x30) = 0xFF;
        object[0x20] = 1;
        D_L05_00221D10.id = sub->id;
        D_L05_00221D10.radius = 8.0f;
        D_L05_001B1360 = -2;
        D_L05_00221D10.enabled = 1;
        D_L05_001B13B0 = (int)object;
        D_L05_001B13DC = 1;
        D_L05_001B1364 = 0;
        D_L05_001B13B4 = 0;
        D_L05_001B13B8 = 0;
        D_L05_001B13BC = 0;
        D_L05_001B1390 = 0;
        D_L05_001B1394 = 0;
        D_L05_001B1398 = 0;
        D_L05_001B13A8 = 0;
        D_L05_001B13AC = 0;
        D_L05_001B13E8 = 1;
        *(short *)(object + 0x32) = 0x1FF;
        *(unsigned char *)(object + 0x30) = 0xFF;
        object[0x20] = 1;
        sub->stage = 0;
        D_L05_001B13D8 = 0;
        sub->warmup = 5400; sub->delay = 7200;
        sub->first = 150; sub->second = 180;
        sub->third = 300; sub->fourth = 480;
        sub->fifth = 120; sub->timeout = 108000;
        D_L05_001B3554[0] = 540;
        D_L05_00221D10.callbacks[0] = func_L05_0041FD48;
        D_L05_00221D10.callbacks[1] = func_US2_L05_00421A98;
        D_L05_00221D10.callbacks[2] = func_L05_0041FFF8;
        D_L05_00221D10.object = object;
        func_L05_00379F18(1);
        func_L05_00379F28(0);
        D_L05_001AA6A0[0] = (int)func_L05_0041FD48;
        D_L05_001AA6A8[0] = (int)func_US2_L05_00421A98;
        D_L05_001B1350 = D_001395B8[0x61];
        D_L05_001B1354[0] = D_001395B8[0x62];
        D_L05_001B1358[0] = D_001395B8[0x63];
        D_L05_001B135C[0] = D_001395B8[0x64];
        if (!D_L05_001B1350) D_L05_001B13F4 = 1;
        else D_L05_001B13F4 = 0;
        hero = D_00189E20;
        D_L05_001B3558[0] = D_L05_001B2000[0];
        D_L05_001B3559[0] = D_L05_001B2001[0];
        D_L05_001B355A[0] = D_L05_001B2002[0];
        D_L05_001B3560[0] = D_L05_001B2008[0];
        D_L05_001B3568[0] = D_L05_001B2010[0];
        D_L05_001B355C[0] = D_L05_001B2004[0];
        D_L05_001B3564[0] = D_L05_001B200C[0];
        D_L05_001B356C[0] = D_L05_001B2014[0];
        D_L05_00221D10.mode = 4;
        D_L05_00221D10.settings[0] = sub->a4;
        D_L05_00221D10.settings[1] = sub->a8;
        D_L05_00221D10.settings[2] = sub->aC;
        D_L05_00221D10.settings[3] = sub->a10;
        p = *(char **)(hero + 0x2290);
        if (p)
            *(short *)(p+0x34) |= 0x41;
        /* fall through */
    case 1:
        one = 1;
        func_L05_00379B60();
        func_L05_0030C930((int)(D_L05_001B2D84[0] * -230.0f + 0.5f), 2);
        if (!D_L05_001B13D4) {
            func_L00_003294F0(D_L05_001B251C[0] + sub->target*256,1);
            D_L05_001B13D4 = one;
            D_L05_001B13D8 = 0;
        }
        if (D_L05_001B13D8++ < 5 || D_L05_001A8F00[0] == 2) break;
        func_US2_L00_002C4560(0x31,0);
        if (D_L05_001B13E8) {
            func_L05_00379F48(1);
            D_L05_001B1360 = func_US2_L05_00420238();
            if (D_L05_001B1360 != -2) func_L05_00445A98();
            break;
        }
        if (!D_L05_001B13E0) {
            func_US2_00289840(0xA17,110);
            D_L05_001B13E0 = one;
        }
        if (func_00282948((char *)sub+0x54)) D_L05_00221D10.pending = 0;
        else D_L05_00221D10.pending = one;
        func_L05_00379F48(0);
        if (D_L05_001B1360 != -2 && D_L05_001B2048 >= 3) {
            switch (D_L05_001B1360) {
            case 0: func_US2_L05_00422838(object); break;
            case 1: func_US2_L05_00422BB0(object); break;
            case 2: func_US2_L05_00422D38(object); break;
            case 3: func_US2_L05_00422E88(object); break;
            }
        }
        if (D_L05_001A904C && !D_L05_001B13A8 && !D_L05_001B13F0) {
            func_US2_0029C548(0,func_US2_L05_0041F478);
            D_L05_001B13AC = 0;
            D_L05_001B13A8 = 1;
        }
        break;
    case 2: break;
    case 3:
        if (!func_L05_00442860()) {
            D_L05_00221D10.pending = 0;
            D_L05_00221D10.count++;
            object[0x20] = 1;
        }
        break;
    }
}
