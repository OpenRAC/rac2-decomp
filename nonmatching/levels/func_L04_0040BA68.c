/* 2026-11-03 w02 source-contract review (USA v1.01 only).
 * Profile: -O2 -G8 -ffunction-sections.
 * Current check.py: 740/740 bytes, 0/2 places, first mismatch +0x34.
 * Corrected func_00132028, func_L04_002E7C08 and func_002E5E58 to their actual integer returns, and the sound helper object argument to a pointer. Absolute stores, object-loop allocation and row-address association remain different.
 * Reopen: An evidenced store-address and object-loop lifetime shape, preserving the actual returns.
 * No linked match or cross-release qualification is claimed. Earlier notes follow.
 */
/* func_L04_0040BA68 (740 bytes, levels 04 and 11). Tier opus-1, 28 October 2026.
 * Unit: a -G8 file of its own (e.g. L04_00402D90-<topic>-g8.c, default -g8
 * flags). Not L04_00402D90-g8.c: its earlier plain declaration of
 * D_L04_001A8EE4 wins over NOT_SDA and lets the first store fill the jal slot.
 * Best check.py: 740/740 bytes, 0/2 places, 44 words differ after relocation
 * masking (the sol-high draft: 47 by the same count). Change from that draft:
 * D_L04_001B24DC is a plain extern, so cc1 emits `lw $r,SYM` and gas builds
 * retail's `lui $a0,0x1B; lw $a0,0x24DC($a0)` reusing the destination.
 * What differs:
 *  - D_L04_001A8EE4 / D_L04_001A8ED0 stores: NOT_SDA splits them through a
 *    GPR (lui $v0; sw 0($v0)); retail has the gas macro with $at. A plain
 *    extern gives the macro, but then sched2 orders s0=1, a0=0x5d, store and
 *    reorg puts the store in the jal slot (gp form), shifting everything;
 *    retail has s0=1, store, a0=0x5d (a0 in the slot). Both ALU sets are
 *    ready in the same cycle, so the C order cannot fix it.
 *  - object loop: retail a1 slot, a2 count, a3 base, t0 -1, v1 child;
 *    here a2, a3, t0, t1, a1 (and the second base load is scheduled earlier).
 *  - D_L04_001B0904 updates: retail keeps the loaded value in v1 and the
 *    constant/slt result in v0 (three places); here the reverse.
 *  - D_L04_002C63C0 row address: retail addu base,index (v1,a0); here
 *    addu index,base (a local pointer for the table changes nothing).
 * Declarations: below.
 */
#include "common.h"
#define I(p,o) (((struct { char pad[o]; int v; } *)(p))->v)
#define P(p,o) (((struct { char pad[o]; char *v; } *)(p))->v)
#define H(p,o) (((struct { char pad[o]; unsigned short v; } *)(p))->v)
extern int D_L04_001B0978 __attribute__((sda)), D_L04_001B0904 __attribute__((sda)), D_L04_001B090C __attribute__((sda));
extern int D_L04_001A8EE4 NOT_SDA, D_L04_001A8ED0 NOT_SDA;
extern char D_00189E20[] NOT_SDA, D_00138180[] NOT_SDA;
extern char *D_L04_001B24DC, *D_L04_001B08F4 __attribute__((sda));
extern char D_L04_002C63C0[] NOT_SDA;
extern void func_00132AF8(int), func_00132B28(int);
extern int func_00132028(void);
extern void func_002B72E8(int), func_002B7320(void);
extern void func_L04_0040A3B8(char *, int);
extern int func_L04_002E7C08(int,int);
extern void func_L04_0040E248(char *, char *), func_L04_0040AC30(char *,char *);
extern int func_002E5E58(int,int,void *);
extern int func_L04_0040A1D0(int);
void func_L04_0040BA68(char *m, char *p)
{
    int done = 0;
    int *slot, i;
    char *obj, *child, *base;
    if (!D_L04_001B0978) {
        D_L04_001A8EE4 = 1;
        func_00132AF8(0x5d); func_002B72E8(0); func_00132028();
        D_L04_001A8ED0 = 1;
        func_L04_0040A3B8(m,0);
        D_L04_001B0904 = D_L04_001B090C;
        D_L04_001B0978 = 1;
    }
    if (I(D_00189E20,0x2294) != 0x31) func_L04_002E7C08(0x31,1);
    H(m,0x34) |= 0x41;
    if (I(p,0x1dc) != -1) {
        obj = D_L04_001B24DC + (I(p,0x1dc) << 8);
        child = D_L04_001B08F4;
        H(obj,0x34) |= 0x41;
        if (child) H(child,0x34) |= 0x41;
    }
    base=D_L04_001B24DC;
    for (slot=(int *)(p+0x1e4),i=20;i>=0;i--,slot++) {
        if (*slot != -1) {
            obj=base+(*slot<<8);
            H(obj,0x34)|=0x41;
            child=P(P(obj,0x68),0x8c);
            if (child) H(child,0x34)|=0x41;
        }
    }
    func_L04_0040E248(m,p);
    I(D_00189E20,0x24a0)=26;
    D_00189E20[0x22b5]=1;
    I(P(D_00189E20,0x2290),0x98)=0;
    if (I(D_00138180,0x1c4)&0x8000) {
        func_002E5E58(3,0,0);
        D_L04_001B0904=D_L04_001B0904-1;
        if (D_L04_001B0904 < 0) D_L04_001B0904=4;
    } else if (I(D_00138180,0x1c4)&0x2000) {
        func_002E5E58(3,0,0);
        D_L04_001B0904=D_L04_001B0904+1;
        if (D_L04_001B0904 >= 5) D_L04_001B0904=0;
    }
    if (I(D_00138180,0x1c4)&0x840) {
        if ((I(D_L04_002C63C0+D_L04_001B0904*64,4)&0x10000000) || (D_L04_001B0904>0 && func_L04_0040A1D0(D_L04_001B0904-1)>0)) {
            func_002E5E58(4,0,0); done=1;
            D_L04_001B090C=D_L04_001B0904;
            m[0xbc]=2;
        } else func_002E5E58(5,0,0);
    } else if (I(D_00138180,0x1c4)&0x10) {
        func_002E5E58(4,0,0);done=1;
        func_L04_0040AC30(m,p);
        I(p,0x320)=-1;m[0x20]=4;
    }
    if (done) {
        func_00132B28(0x5d);func_002B7320();func_00132028();
        D_L04_001A8EE4=0;D_L04_001A8ED0=0;D_L04_001B0978=0;
    }
}
