/* func_PAL_L11_00449550, the PAL copy of func_L11_00443CE0: the same C. */
#include "common.h"

/* Dispatches an indexed polygon query through the already integrated helper. */
typedef struct { s32 field00; u8 remainder[12]; } JobaPolygonHeaderView;

extern JobaPolygonHeaderView *D_L11_001FF580[];

/* Consumes one positive counter selected by the measured class identifier. */
/* bumps the 0xFFFF-saturated counter, then starts the state's timer and reports the object */
/* clears the state's six-word block and its counters, then restarts the object */
/* func_L11_00440238 lives in L11_00440238-g8.c (its source unit has the retail small-data view). */
/* func_L11_00440360 is in L11_0043E1A0-g.c. */

/* func_L11_00440790 lives in L11_00440238-g8.c (its source unit has the retail small-data view). */

/* Finds the class entry the identifier names and hands it to that class's handler. */
extern u8 *D_L11_001FC420[];

extern u8 *D_L11_001B359C __attribute__((section(".sdata")));

/* func_L11_00440970 lives in the sibling small-data unit (L11_0043E1A0-g8.c). */

/* Hands a target point to the first free class-0xD37 moby (state 1) in this moby's
   group: records the caller as its owner, places it at the target facing -pi/2, sets
   its heading toward the target from the caller and starts it; 0 when the group is
   empty or has no free member. */
/* Returns the state's 0x200 halfword. */
/* The weight word (+0x20) of OTHER's state. */
#define WEIGHT (*(f32 *)(*(u8 **)(other + 0x68) + 0x20))

/* Adds OTHER to the group in the state's current slot (+0x120, indexed by +0x18C) when that
   group exists and accepts it: the class of OTHER is counted (0xD98 +0x100, 0xDCF +0x104,
   0xDF4 +0x108, 0xDF7 +0x10C, 0xDF9 +0x110 unless the group refuses it, 0xD37 +0x114) and
   its state's weight set to 1.0. Returns 1 when added, else 0. */
#undef WEIGHT

/* func_L11_00440E18 lives in the sibling small-data unit (L11_0043E1A0-g8.c). */

/* Walks the state's 0x120 slots in order and renews each live entry through the two shared helpers. */
/* Clears the state's 0x120 slot table once every live entry has been accepted. */
/* hands every entry of the class list to its measured handler */
extern u8 *D_L11_001FC420[];

extern u8 *D_L11_001B359C;

/* The class table base read through an incomplete `sda` array: cc1 emits the one-instruction
   load, which the assembler expands absolute (`lui $r` / `lw $r,%lo($r)`) and which is not
   hoisted out of the loop, as retail has it (docs/build/compiler-notes.md). */
/* func_L11_00441350 lives below, after the id-list macros it uses. */

/* arms the one-shot flag block when it is idle and the state agrees */
typedef struct { u8 pad[0x284]; s32 field284; s32 field288; } JobaFlagBlockView;

extern JobaFlagBlockView D_L11_001BA780;

/* returns the 128-byte entry selected by the state index, at its 0x30-byte payload */
/* returns zero for a missing state polygon index or dispatches its point query to the integrated crossing-parity helper */
/* Returns the state's 0xC0 word. */
/* consumes one positive signed state counter selected by a measured class identifier and reports success */
/* increments one signed state counter selected by a measured class identifier */
/* Increments the state counter selected by the measured class identifier. */
/* Each group word of the object's state names an id list in D_L11_001FC420: halfwords whose low
   15 bits index the 256-byte records of D_L11_001B359C, the last one with its sign bit set. A
   walk stops when the group word (re-read after every callback) is 0xFF or above the limit
   kept at D_L11_001B35B8. */
/* Counts the entities of the object's group (state word 0xC8) for which func_L02_004024A0
   holds, then sets (func_L02_004024B0) or clears (func_L02_004024C0) entities until the count
   equals the second argument. */
/* Counts the entities of the object's group (state word 0xCC) for which func_L02_003D7300
   holds, then sets (func_L02_003D7310) or clears (func_L02_003D7320) entities until the count
   equals the second argument. */
/* Over the entities of the object's group (state word 0xC0): first resets the "armed" halfword
   (1 -> 0) of the state of every entity of the four measured classes and reports its class to
   func_L11_00441978. Then, twice: picks the entity of those classes (state byte not 0xFE or 0xFD
   and at least 4, halfword not 1) that func_L02_002F21C0 puts nearest to D_00189EA0, and arms
   its halfword when func_L11_00441868 consumes the class's counter. */
/* func_L11_00441FB8 lives in L11_00441FB8.c. */

/* Hands every entity of the object's group (state word 0xC0) that the shared test func_L11_00441FB8
   accepts, and whose state byte is not 0xFE, 0xFD or below 3, to the handler of its class (the
   halfword at +0xAA); then runs the test once more on the entity D_00189E20 holds at +0x2290. */
/* func_L11_004423F8 lives in the sibling small-data unit (L11_0043E1A0-g8.c). */

/* func_L11_004425C8 is defined in its dedicated source unit. */

/* func_L11_00442B60 is defined in its dedicated source unit. */

/* Runs func_L02_003A6F78 on every entity of the object's two groups (state words 0x178 and
   0x174); an empty group, or a group word of 0xFF, ends the function. */
/* func_L11_00442E38 lives in the sibling small-data unit (L11_0043E1A0-g8.c). */

/* func_L11_00443380 and func_L11_004433D8 live in the sibling small-data unit
   (L11_0043E1A0-g8.c): they reach the level's globals through $gp. */

/* func_L11_00443498 is in L11_00443498-g8.c. */

/* maps the class index to its measured identifier */
/* The level's own jump table: the address of each case body. */
extern void *jtbl_002BB0E0[13];

s32 func_PAL_L11_00449550(s32 a) {
    static void * tab[] = {
        &&c0, &&c1, &&c2, &&c3, &&c4, &&c5, &&c6, &&c7,
        &&c8, &&c9, &&c10, &&c11, &&c12
    };

    if ((u32)a >= 13) {
        goto def;
    }
    goto *jtbl_002BB0E0[a];
c0:
    return 0xe8b;
c1:
    return 0xe8c;
c2:
    return 0xe8d;
c3:
    return 0xe8e;
c4:
    return 0xe8f;
c5:
    return 0xe90;
c6:
    return 0xe91;
c7:
    return 0xe92;
c8:
    return 0xe95;
c9:
    return 0xe96;
c10:
    return 0x140c;
c11:
    return 0x140d;
c12:
    return 0x140e;
def:
    return 0xe8b;
}

/* func_L11_004456A0 is in L11_004456A0-g8.c. */

/* func_L11_00445990 is defined in L11_00445990-g8.c ($gp accesses). */

/* func_L11_00445B30 is defined in L11_00445B30-g-g8.c. */

/* Claims the shared call slot for the state entry the identifier names. */
/* Claims the shared call slot for the state entry the caller's class identifier
   selects, unless the slot is already busy or waiting. */

/* func_L11_00445DF8 is defined in L11_00445DF8-g8.c ($gp accesses). */

/* func_L11_00446020 lives in L11_00446020-g8.c. */

/* hands the state's 0x1C4 field to the shared helper, after the caller's argument */
