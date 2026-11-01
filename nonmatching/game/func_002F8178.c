/* 1 November 2026 (closer a3): the v / 2 block is local-alloc's fake_birth/fake_death: a qty avoids the registers of
 * qtys in the adjacent insns. Retail's sum isn't tied to `visible` (combine_regs refused), so it avoids v0: count/sum v1,
 * sign a0. Here they tie. combine_regs refuses when the output already has a qty, so `visible` looks born earlier in the
 * block. Tried and tied or worse: block-local count, about a dozen orderings, an inline half, non-void callees before the block.
 * The mode store's a0: cse picks count's register for the constant 1. */
/* 1 November 2026: 8 words, 1520/1520 (was 128). Screen size as one 8-byte object (an int under -G8 fills a
 * branch slot from the target thread), store orders from a hill climb. Left: sw $a0 (retail's constant) against
 * $v1 for the mode store at +0x1B0, and the v / 2 block: retail has $v0 taken over the whole load-to-sra range,
 * so count, srl, slt and 0x28 sit one register up (v1, a0, a1, a2) with a block-local count. */
/* GPT-6.1 Sol (high), task v1149, USA v1.01, 29 October 2026.
 * Best retained: 1524/1520 bytes, 0/28 places, game -O2 -G8
 * -ffunction-sections. The 0x50 frame and much of the entry/control flow
 * now agree structurally; this is not a byte match. No linked build run.
 * All required declarations are below; compile as a standalone -G8 unit.
 *
 * Started from the earlier 1476-byte sol-low draft. Typed shop/resources/hero
 * objects and separate conditional qcopy/helper calls recover the saved-register
 * frame and the retail camera branches. SDATA views provide the four 16-byte
 * vectors without inventing small array extents. D_001AD1C0 is a word store.
 * gp+0x329C is D_001B228C (already present in the earlier C); the genuinely
 * missing zero was gp+0x25B4, D_001B15A4. func_00288EA0 has no arguments in its
 * current C definition, and func_0026F748 returns unsigned int.
 *
 * Remaining: FP/int initialization order and FPR allocation around +0x264;
 * quotient/predicate allocation around +0x360; speculative absolute/SDA load
 * around +0x3C8 and subsequent resource setup scheduling. qzero_nc recovers
 * the independent final vector-clear address reconstruction. Keeping the count
 * in v and the mutable quotient in visible improves the carousel allocation.
 * Direct ternaries, a precomputed predicate and moving the index store earlier
 * instead lose the saved constant 2 or introduce a reload; scalar versus paired
 * scale declarations and nested versus combined item guards do not close it.
 * An equal-size 1520-byte variant still had a wrong 0x40 frame and 0/28 places.
 * Stopped after 18 check.py runs plus one regalloc diagnostic; pursue a measured
 * source/alias/lifetime hypothesis rather than repeating these tied wordings.
 */
#include "common.h"
typedef struct { int id, kind; char pad[0x10]; } ShopSlot_002F8178;
typedef struct {
    int state, unused4, field8, fieldC;
    int base10, base14, unused18, base1C;
    char pad20[8]; char *moby; char pad2C[0xC];
    int field38; char pad3C[8]; int field44;
    int unused48, field4C, mode; char pad54[0xC];
    int restore, field64, field68, field6C;
    char pad70[8]; int field78, field7C, index, field84, field88, field8C;
    char pad90[0x10]; int fieldA0, fieldA4; char padA8[0xC];
    int fieldB4, fieldB8; float fieldBC; char padC0[0x10];
    float position[4], rotation[4]; char padF0[0x50]; ShopSlot_002F8178 slots[64];
    int count, field744; char pad748[0x18];
} Shop_002F8178;
extern Shop_002F8178 D_0021F240;
typedef struct { char pad[0xC]; int baseC, base10; } Resources_002F8178;
extern Resources_002F8178 D_001BAEC0;
typedef struct { char pad[0x20]; short level; } Settings_002F8178;
extern Settings_002F8178 D_001A79F8 MACRO_ADDR;
extern char D_001B5340[];
extern unsigned char D_001A7BB4[] __attribute__((sda));
extern int D_001B2294, D_001B2298, D_001B2290, D_001B2284, D_001B2288, D_001B228C, D_001A7AF0 MACRO_ADDR;
extern int D_001AD1C0;
extern int func_002E5CF8(int, int, void *);
extern void func_00282A60(void *, int, int);
extern char *func_0029EFD0(int);
extern void func_00282CC0(void *, void *, void *), func_00282C88(void *), func_002A0F48(void *);
extern void func_002F9778(void), func_002F6608(int), func_002F71B8(void), func_002F73A8(void), func_002F7738(void);
extern void func_00132AF8(int), func_002B72E8(int), func_00132028(void), func_0028E408(void);
extern void func_0029B698(int), func_0029B6D0(int, int), func_00288EA0(void), func_0026F720(void);
extern unsigned int func_0026F748(int, int);
extern void func_00283098(void *, void *, void *), func_00335438(void *, void *, int, int, int), func_00335370(void *), func_003353C8(void *), func_00272368(void);
extern float func_00283B98(float, float);
extern int D_001A7B90;
extern int D_001AD1C4 __attribute__((sda)), D_001AD230 __attribute__((sda));
extern float D_001B2280, D_001B15A0;
extern unsigned char D_001A7BB1;
extern char D_001AD1E0[] SDATA(D_001AD1E0), D_001AD1F0[] SDATA(D_001AD1F0), D_001AD210[] SDATA(D_001AD210), D_001AD220[] SDATA(D_001AD220);
extern float D_001AD234 SDATA(D_001AD234), D_001AD238 SDATA(D_001AD238);
extern int D_001B2244, D_001B2248, D_001B2238, D_001B8BB0;
extern struct { int w, h; } D_001A7340;
typedef struct { char pad[0x1248]; int mode; char pad124C[0x1069]; char flag22B5; char pad22B6[6]; char flag22BC; } Hero_002F8178;
extern Hero_002F8178 D_00189E20;
extern char D_00152CE4[], D_001C2AC0[];
extern int D_001B15A4;
void func_002F8178(char *moby)
{
    int mode, v, n, visible;
    float vec[4];
    func_00282A60(&D_0021F240, 0, 0x760);
    if (D_001A7B90) D_001B2280 = 1.076923f; else D_001B2280 = 1.0f;
    D_0021F240.restore = 0;
    D_001AD1C0 = D_001A79F8.level;
    mode = (int)moby;
    if ((unsigned)moby < 4) {
        D_0021F240.restore = 1;
        moby = func_0029EFD0(11);
        *(short *)(moby + 0x32) = 64;
        if (D_001A7BB1) qcopy(vec, D_001AD1F0);
        else qcopy(vec, D_001AD1E0);
        vec[2] = -vec[2];
        func_00282CC0(moby + 0x10, D_001B5340, vec);
        func_00282C88(moby + 0xF0);
        *(float *)(moby + 0xF8) = 3.1415927f;
        func_002A0F48(moby);
        D_0021F240.restore = 1; D_0021F240.field744 = 0; moby[0x20] = 3;
        if (mode == 0) { D_0021F240.field744 = 0; D_0021F240.mode = 0; }
        else if (mode == 1) D_0021F240.mode = 1;
        else if (mode == 2) { D_0021F240.mode = 2; D_0021F240.fieldBC = -1.5707964f; D_0021F240.fieldB4 = 0; D_0021F240.fieldB8 = 0; D_0021F240.fieldA4 = 0; }
        else D_0021F240.mode = 3;
    } else if (*(short *)(moby + 0xAA) == 11) {
        D_0021F240.field744 = 0;
        v = *(int *)(*(char **)(moby + 0x68) + 0x94);
        if (v == 0) D_0021F240.mode = 0;
        else if (v == 1) { D_0021F240.mode = 1; func_002F9778(); }
        else if (v == 4) D_0021F240.mode = 2;
        else if (v == 2) D_0021F240.mode = 3;
        else if (v == 3) { D_0021F240.field744 = 1; D_0021F240.mode = 0; }
    } else if (*(short *)(moby + 0xAA) == 0x1309) { D_0021F240.moby = moby; D_0021F240.mode = 2; }
    else if (*(short *)(moby + 0xAA) == 0xDDC) { D_0021F240.moby = moby; D_0021F240.mode = 1; func_002F9778(); }
    if (D_001AD1C4 != -1) D_0021F240.mode = D_001AD1C4;
    D_0021F240.field88 = 0; D_0021F240.field8C = 0; D_0021F240.field38 = 0;
    D_0021F240.field44 = D_001A7BB4[0] - 1;
    if (D_0021F240.field44 < 0) D_0021F240.field44 = 0;
    D_0021F240.field78 = -1;
    D_0021F240.field7C = -1;
    D_0021F240.field64 = 0;
    D_0021F240.index = 0;
    D_001B2244 = 0;
    D_0021F240.field84 = 0;
    D_0021F240.field68 = -1;
    D_001AD234 = 0.8f;
    D_001AD238 = 1.0f;
    D_001B2290 = 96;
    D_001B2238 = 0;
    D_001B2248 = 0;
    D_001B2294 = 96;
    D_001AD230 = 0;
    D_001B2284 = 0;
    D_001B2288 = 0;
    D_001B2298 = 85;
    D_001B228C = 0;
        func_00132AF8(93); func_002B72E8(0); func_00132028();
    if (D_0021F240.mode == 0) func_002F6608(0);
    else if (D_0021F240.mode == 3) func_002F71B8();
    else if (D_0021F240.mode == 1) func_002F73A8();
    else if (D_0021F240.mode == 2) func_002F7738();
    v = D_0021F240.count;
    visible = v / 2;
    n = visible;
    if (v <= 2) visible = 1;
    D_0021F240.index = n;
    D_0021F240.field6C = (visible - n) * 40;
    func_0028E408();
    if (D_0021F240.mode != 2) func_0029B698(0x112A880);
    if (D_0021F240.mode == 0 && D_0021F240.slots[D_0021F240.index].kind == 1 && D_00189E20.mode != 10)
        func_0029B6D0(D_0021F240.slots[D_0021F240.index].id, 0x112A880);
    D_0021F240.state = 0;
    D_0021F240.base10 = D_001BAEC0.base10 + 0x60000;
    D_0021F240.base1C = D_0021F240.base10 + D_001A7340.w * D_001A7340.h * 4;
    D_0021F240.field8 = 0;
    D_0021F240.fieldC = 1;
    D_0021F240.moby = moby;
    D_0021F240.base14 = D_001BAEC0.baseC + 0x60000;
        func_002E5CF8(3, 17, moby);
    D_0021F240.field4C = D_001A7AF0; D_0021F240.fieldA0 = *(short *)D_00152CE4;
    func_00288EA0();
    D_001B8BB0 = 5; D_001B15A0 = 0.0f; D_001B15A4 = 0;
    func_0026F748(97, 1);
    D_00189E20.flag22BC = 1; D_00189E20.flag22B5 = 1; func_0026F720();
    if (!D_0021F240.restore) {
        if (D_001A7BB1) func_00283098(D_0021F240.position, D_001AD1F0, D_0021F240.moby + 0xC0);
        else func_00283098(D_0021F240.position, D_001AD1E0, D_0021F240.moby + 0xC0);
        func_00282CC0(D_0021F240.position, D_0021F240.position, D_0021F240.moby + 0x10);
        D_0021F240.rotation[2] = func_00283B98(*(float *)(D_0021F240.moby + 0xF8), 3.1415927f);
        func_00335438(D_0021F240.position, D_0021F240.rotation, 1, 0, 0);
        qcopy(vec, D_0021F240.position);
        if (D_0021F240.mode == 2) vec[1] += 5.0f;
        func_00335370(vec); func_003353C8(D_0021F240.rotation); func_00272368();
    }
    func_00283098(D_001C2AC0 + 0x10, D_001AD210, D_0021F240.moby + 0xC0);
    qcopy(D_001C2AC0, D_001AD220);
    qzero_nc(D_001C2AC0 + 0x30); qzero_nc(D_001C2AC0 + 0x20);
}
