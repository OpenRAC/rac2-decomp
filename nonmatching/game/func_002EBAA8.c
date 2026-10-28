/* func_002EBAA8 - 452 bytes.  Worker attempt, 27 October 2026 (draft below).

   Draft is 444 B vs 452 (8 bytes = loop-alignment nops before the
   func_00132028 loop; follows from loop 1 shape).
   Diff: retail's first loop (func_002E4AC8/func_001261F0) re-tests D_001A63A8
   at the bottom with `addiu v1,s3,0x63A8` (hi part in s3) and -1 in the bnez
   delay slot; mine tests through s0 and keeps -1 in s1. Rest of the function
   looked the same up to there (not compared after).
   Tried: `while (a==0 && b!=-1)` and `for(;;){if..break;}`; same result. */

/* append to src/game/002E7018-g8.c, after func_002EB598 (needs its Moby2EB598/State2EB598 structs and D_001B8840) */
typedef struct {
    u8 pad00[0x24];
    int f24;
    u8 pad28[0x40];
    int f68;
    u8 pad6C[6];
    unsigned short h72;
} Selector2EBAA8;

typedef struct {
    u8 pad00[0xB0];
    float fb0;
} Render2EBAA8;

typedef struct {
    u8 pad00[0x12C0];
    struct Moby2EB598 *held;
} Pool2EBAA8;

typedef struct {
    u8 pad00[0xFC];
    struct Moby2EB598 *held;
} Pending2EBAA8;

extern Selector2EBAA8 D_001A63A8;
extern Render2EBAA8 D_001BF040;
extern Pool2EBAA8 D_00189E20;
extern Pending2EBAA8 D_001F2840;
extern struct Moby2EB598 *D_001B1790;
extern int D_001B15A8;
extern int D_001B15AC;
extern int ref_L00_002EBAA8_00 __attribute__((sda));

extern void func_0027D330(int);
extern void func_002E4AC8(void);
extern void func_001261F0(int);
extern int func_00132028(void);
extern void func_0027AB40(void);
extern void func_0029F338(struct Moby2EB598 *);

void func_002EBAA8(void)
{
    int i;

    if ((unsigned short)(D_001A63A8.h72 - 6) >= 2) {
        D_001A63A8.h72 = 5;
    }
    func_0027D330(0xC);
    for (;;) {
        if (D_001A63A8.f68 != 0)
            break;
        if (D_001A63A8.f24 == -1)
            break;
        func_002E4AC8();
        func_001261F0(0);
    }
    while (func_00132028()) {
    }
    D_001BF040.fb0 = 0.63f;
    D_001B15A8 = 0;
    D_001B15AC = 0;
    ref_L00_002EBAA8_00 = 0;
    func_0027AB40();
    for (i = 0; i < D_001B8840.num_parts; i++) {
        struct Moby2EB598 *mob = D_001B8840.slots[i];

        if (mob != 0) {
            mob->parts->used--;
            mob->parts->entries[mob->parts->used] = 0;
            func_0029F338(mob);
        }
    }
    if (D_00189E20.held != 0) {
        func_0029F338(D_00189E20.held);
        D_00189E20.held = 0;
    }
    if (D_001B1790 != 0) {
        D_001B1790->unk34 &= ~1;
    }
    if (D_001F2840.held != 0) {
        D_001F2840.held->unk34 &= ~1;
        D_001F2840.held = 0;
    }
}
