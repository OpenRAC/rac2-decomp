/* func_PAL_L00_002B3000, the PAL copy of func_L00_002B30E8: the same C. */

extern void func_L00_002B1F90(void);
extern int D_00138320[];
#ifndef RAC2_T_ROW_F3392E4BC
#define RAC2_T_ROW_F3392E4BC
#endif

#ifndef RAC2_T_V4_FA012328C
#define RAC2_T_V4_FA012328C
#endif

extern void func_L00_002B39D8(void);

typedef unsigned char u8;

typedef int s32;

typedef float f32;

extern u8 D_00189E20_1[];

#ifndef RAC2_T_V4_F6B9E759F
#define RAC2_T_V4_F6B9E759F
typedef struct {
    f32 x, y, z, w;
} V4_F6b9e759f;
#endif

#ifndef RAC2_T_M4_F6B9E759F
#define RAC2_T_M4_F6B9E759F
#endif

extern V4_F6b9e759f D_00189EA0_1[];

#ifndef RAC2_T_V4S_F31E44309
#define RAC2_T_V4S_F31E44309
typedef struct {
    f32 x, y, z, w;
} V4S_F31e44309;
#endif

extern V4S_F31e44309 D_00189E20_10[];

typedef struct {
    char pad0[6];
    unsigned char flag;
} HeroItemMobyClass;

typedef struct {
    char pad0[0x24];
    HeroItemMobyClass *cls;
    char pad28[9];
    unsigned char visible;
    short drawDistance;
    unsigned short flags;
    char pad36[2];
    long long spawnFrame;
    char pad40[0x23];
    unsigned char mode;
    void (*update)(char *);
} HeroItemMoby;

/* One of the hero's item slots, 0x50 bytes each. */
typedef struct {
    HeroItemMoby *moby;     /* 0x00 */
    HeroItemMoby *other;    /* 0x04 */
    HeroItemMoby *extra;    /* 0x08 */
    char pad0C[4];
    int buttonMask;         /* 0x10 */
    int respawnFrame;       /* 0x14 */
    unsigned char ammoFlag; /* 0x18 */
    char pad19[0x24 - 0x19];
    int state;              /* 0x24 */
    int id;                 /* 0x28 */
    char pad2C[0x50 - 0x2C];
} HeroItemSlot;

typedef struct {
    char pad0[0x1220];
    HeroItemSlot slots[5];      /* 0x1220 */
    char pad13B0[0x2290 - 0x13B0];
    HeroItemMoby *heroMoby;     /* 0x2290 */
    char pad2294[39];
    unsigned char itemFlag;     /* 0x22BB */
    char pad22BC[12];
    int pendingItem;            /* 0x22C8 */
    char pad22CC[24];
    int selectedItem0;          /* 0x22E4 */
    char pad22E8[8];
    int selectedItem3;          /* 0x22F0 */
    char pad22F4[520];
    short packDisabled;         /* 0x24FC */
} HeroItemsCreateState;
extern HeroItemsCreateState D_00189E20_items;
extern unsigned char D_00139568[];
extern int D_L00_001B18D8[] __attribute__((sda)), D_L00_001B19C8[] __attribute__((sda));
typedef struct {
    char pad0[0xA0];
    short joint;
    char padA2[14];
} HeroItemEase;
extern HeroItemEase D_0018B9A0[];
typedef struct {
    char pad0[0x14];
    int object;
    int other;
    unsigned char flag;
    char pad1[0x71];
    unsigned short ammo;
    char pad2[0x50];
} HeroItemDefinition;
extern HeroItemDefinition D_L00_00262570[];
extern HeroItemMoby *func_0029EFD0(int);
/* calls three measured no-argument functions in sequence */
#define ITEM_DEF(id) (&D_L00_00262570[D_00139568[id]])
#define HERO_ITEMS (&D_00189E20_items)

/* Spawns the mobys for the hero's equipped item slots, releasing disabled slots. */
#undef HERO_ITEMS
#undef ITEM_DEF

/* Nested 3x3 sweep over two rows-of-four arrays: sums the results of calling the same routine with the difference of each of the nine element pairs, returns the sum. */
/* func_L00_002B0528 is in L00_002B0528-g8.c. */

/* for one fixed 80-byte slot: stores a value, rewrites a state word, dispatches through a function pointer at entry+100 unless the entry is null or carries a 253/254 sentinel, then releases two stored entry pointers, skipping the second when the slot index is 3 */
typedef struct {
    u8 pad0[0x98];
    f32 f98;
    u8 pad1[0x1A0 - 0x9C];
    f32 f1A0;
    f32 f1A4;
    f32 f1A8;
    u8 pad2[0x1B0 - 0x1AC];
    f32 f1B0;
    f32 f1B4;
    u8 pad3[0x1FC - 0x1B8];
    short a;
    u8 pad4[0xA70 - 0x1FE];
    f32 fA70;
    f32 fA74;
    f32 fA78;
    u8 pad4b[0x1FB0 - 0xA7C];
    f32 f1FB0;
    f32 f1FB4;
    u8 pad5[0x22C3 - 0x1FB8];
    u8 flag;
    u8 pad6[0x24F4 - 0x22C4];
    short b;
} D00189E20_Overlay;

extern D00189E20_Overlay D_00189E20;

/* The level's own dispatch table: 31 absolute code addresses, five of them (the cases
 * 14, 26, 27, 43 and 44) pointing at the arm that writes the two shorts and the rest at
 * the return.  It lives in the level's data, so it is named by its address. */
/* Dispatches on the argument through the level's table: the five listed cases write
 * 0x46 at +0x1FC and 3 at +0x24F4 of the resident block, the other twenty-six and every
 * argument out of the range only return. */
/* Read through its macro symbol: the copy reorg puts in a branch delay slot assembles
 * $gp-relative, the one in ordinary flow as lui/lw. */
extern int D_L00_001B18D8[] __attribute__((sda));

/* Per-frame pass over the seven 80-byte slots at +0x1220: an empty slot is released; in
 * state 2 a slot counts a tick, is released and, for a flagged entry whose animation set
 * allows it, starts animation 1; in state 3 it counts a byte tick and slots 0 and 1 (or a
 * flagged entry) are reinstalled with the shared value plus 2.  The entry's update
 * callback then runs, except for slot 6, a 253/254 sentinel entry, or slot 0 while the
 * block's word at +0x1500 is set and its mode at +0x1248 is not 10. */
void func_L00_002B1F90(void);

/* func_L00_002B2200 is in L00_002B2200-g8.c. */

/* Reset the hero update state, install the requested mode and object, and update the mode-one counters. */
/* Zeroes a 16-byte global block, calls a setup helper, runs a per-slot reset helper over seven 16-byte units of a global table, then clears three word fields of a block 256 bytes below the table base. */
/* dispatch on the second integer argument: each arm runs a pair of sub-calls passing the first argument twice, the second call also forwarding the float argument */
/* func_L00_002B2CC8 is in L00_002B2CC8-interact.c. */

typedef struct {
    u8 pad0[0x2294];
    int mode;
    u8 pad2298[0x22C1 - 0x2298];
    u8 visited;
    u8 pad22C2[0x22C6 - 0x22C2];
    u8 slot;
} HeroSlotState;

extern int D_001A79F0[] __attribute__((sda));
extern int D_001A73D8[] __attribute__((sda));
extern int D_001A73E0[] __attribute__((sda));
extern int D_0013A148[];
extern unsigned char D_0019B2E8[][16];
extern int D_001A24A8[][16];
extern void func_L00_002F45B8(void);
extern void func_0027D330(int);

/* Bumps the current level's counter and a global total, runs a helper, then for a valid slot at 0x22C6 bumps a
 * per-level per-slot counter (only once the counter at D_L00_001B19C8 reaches 900, or 1800 in modes 0x74 and 0x79,
 * and while the slot's 0x80 flag is clear) and a 16-entry counter; always bumps the per-slot counter, calls
 * func_0027D330(0x10) and sets the byte at 0x22C1. */
void func_PAL_L00_002B3000(void)
{
    int threshold;
    int mode;

    D_0013A148[D_001A79F0[0]]++;
    D_001A73D8[0]++;
    func_L00_002F45B8();
    if (((HeroSlotState *)D_00189E20_1)->slot != 0xFF) {
        mode = ((HeroSlotState *)D_00189E20_1)->mode;
        if (mode == 0x74 || mode == 0x79)
            threshold = 0x5dc;
        else
            threshold = 0x2ee;
        if (D_L00_001B19C8[0] >= threshold) {
            int level = D_001A79F0[0];
            int slot = ((HeroSlotState *)D_00189E20_1)->slot;
            if ((D_0019B2E8[level][slot] & 0x80) == 0)
                D_001A24A8[level][slot & 0xF]++;
        }
        D_001A73E0[((HeroSlotState *)D_00189E20_1)->slot & 0xF]++;
    }
    D_001A73E0[((HeroSlotState *)D_00189E20_1)->slot]++;
    func_0027D330(0xd);
    ((HeroSlotState *)D_00189E20_1)->visited = 1;
}

/* tests the signed short identifier at offset 0xaa of a nonnull object against 71 */
extern int D_00138320[];

/* func_L00_002B32F8 is in L00_002B32F8-hero.c. */

/* func_L00_002B35A0 is in L00_002B35A0.c. */

/* func_L00_002B36E0 is in L00_002B36E0-hero.c. */

/* Test whether a scalar lies below a plane within its configured depth, rejecting unordered values */
/* clears the two floats at the head of the window block; the second store is the one the
   scheduler parks in the jr delay slot, so it is written second */
void func_L00_002B39D8(void);

/* builds one 64-byte block from a 3-float vector of the incoming scalars and another from a static table record one element in, combines them, then scales the result again from that record */
/* Fills a two-float scratch buffer from one region of a fixed global, passes it with three forwarded floats and an out-parameter to another callee, stores the returned float back into the global, then feeds that out value to a final callee. */
/* func_L00_002B3F68 is in L00_002B3F68.c. */

/* func_L00_002B4308 is in L00_002B4308.c. */

/* func_L00_002B4458 is in L00_002AFBC0-surface.c. */

/* func_L00_002B47A8 is in L00_002AFBC0-vectors.c. */

/* func_L00_002B5250 is in L00_002AFBC0-snap.c. */

/* func_L00_002B5B60 is in L00_002B5B60-motion.c. */

/* scales four 16-byte records of a static table in place by a scalar, then multiplies one float field of a later record by the same scalar */
/* func_L00_002B6198 is in L00_002AFBC0-velocity.c. */

/* func_L00_002B6560 is in L00_002B6560.c. */

/* func_L00_002B75A0 is in L00_002AFBC0-target.c. */

/* func_L00_002B7718 is in L00_002B7718-g8.c. */
