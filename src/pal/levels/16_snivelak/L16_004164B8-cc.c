/* func_PAL_L16_004164B8, the PAL copy of func_L16_00411368: the same C, where rename func_L16_00412F48 becomes func_PAL_L16_004180B0. */
#include "common.h"

extern void func_L16_00412C58(u8 *, s32, s32);
extern void func_L16_00412BA8(u8 *, s32);

/* func_L16_00403900 is in L16_00403900-update-g8.c. */

/* func_L16_00404A60 is in the sibling file L16_00403900-g8.c: its body
   reaches the level's small-data floats through $gp. */

/* Steers the object toward the next point of its path (the state's table and cursor at
   0x294/0x2A4); advances the cursor once within half a unit, and returns 1 when the path is done. */
/* func_L16_00404F50 is defined in L16_00404F50.c. */

/* func_L16_004050D8 is defined in L16_004050D8-helpers.c. */

/* func_L16_00405488 is in L16_00405488-g8.c. */

/* func_L16_0040C840 is in L16_0040C840-g8.c. */

extern s32 func_00283CF0(float);
extern s32 D_L16_001B2648 MACRO_ADDR;
extern float func_00283198(float);
extern void func_002AA548(void *, void *, float, float, float, float);
extern void func_PAL_L16_004180B0(u8 *);
extern void func_L16_0040D188(u8 *);
/* Object update: on the first frame (+0x20 still zero) sets the state's defaults and
   rates; then, with +0x31 set and the object within 32 units of D_L16_001B9B00, runs
   func_002A93B0 and sets +0x6F to 30; marks the group when func_002B0ED8 reports, and
   runs func_002B3BA8 on the state's two slots, keeping the object's +0x18 across them. */
/* func_L16_0040CF98 is defined in L16_00403900-g8.c. */

/* `sda` on an array of unknown size: cc1 emits the one-instruction load, which the assembler
   expands absolute (`lui $r` / `lw $r,%lo($r)`), as retail has it in this -G0 unit. */
/* Sets a flag word in the state record (+0x68) of every entity of the object's group, stopping
   at the first id with no entity: +0x244 for class 0xF35, +0x24C for class 0xEA3. */
void func_L16_0040D188(u8 *arg0);

/* func_L16_0040D4E8 is compiled from L16_0040D4E8-g16.c. */

/* func_L16_00410618 is in L16_00410618-g8.c. */

/* func_L16_00410B88 is defined in L16_00403900-g8.c (this unit has no $gp access for it). */

/* Copies the measured 32-bit field pair of the handle reached at 0x68 onto the second
   pair after the helper has prepared the object's second half. */
/* func_L16_00410CC0 is defined in L16_00410CC0.c. */

/* Picks the row of the level's table that is closest to the handle, then, from a random
   start, the first other usable row, and copies it into the state's slot at 0x200. */
/* func_L16_00410FA8 is in L16_00410CC0.c. */

/* func_L16_004110D0 is compiled from L16_004110D0-g8.c. */

void func_PAL_L16_004164B8(u8 *arg)
{
    u8 *s0;
    u8 *s1;
    float f20;
    float period = 1e+02f;

    s0 = arg;
    s1 = *(u8 **)(arg + 0x68);
    f20 = 10.0f;
    if (s0[0x20] == 0xD || s0[0x20] == 0xF || s0[0x20] == 0xE || s0[0x20] == 0x11)
        f20 = 25.0f;
    f20 = f20 + func_00283198((float)(D_L16_001B2648 % func_00283CF0(1e+02f)) / period * 6.2831855f - 3.1415927f);
    func_002AA548(s0 + 0x18, s1 + 0x268, *(float *)(s1 + 0x264) + f20,
                  0.012f, 0.004f, 0.20000002f);
    func_PAL_L16_004180B0(s0);
}

/* func_L16_00411480 is defined in L16_00403900-g8.c. */

/* func_L16_00411600 is in L16_00411600-qcopy.c. */

/* Routes one transition request to the handle itself or to its first child, depending on
   the state word and on which of the two animation slots is current. */
/* func_L16_004117A8 is defined in L16_004117A8.c. */

/* func_L16_00411900 is defined in L16_00411900-g8.c. */

/* func_L16_00411B40 is defined in L16_00411B40-g16.c. */

/* func_L16_00411D00 is defined in L16_00411D00-g8.c. */

/* func_L16_00411F80 is defined in L16_00411F80.c. */

/* func_L16_00412560 is defined in L16_00412560-g32.c. */

/* func_L16_00412AF0 is defined in L16_00403900-g8.c (this unit has no $gp access for it). */

/* The voice-load state the level shares with the engine (see L03VoiceState in L03_003F09C0.c). */
typedef struct {
    u8 pad[0x24];
    s32 key;
    s32 selection;
    u8 pad2[0x3C];
    s32 active;
} L16VoiceState;

extern L16VoiceState D_001A63A8;
/* Asks the engine to load voice line idx, from the first table below 20 and the second from 20 up,
   unless a load is active or pending or that line is already the current one. The arms are written
   out: cross-jump merges their stores after allocation, which leaves them before the shared tail. */
void func_L16_00412BA8(u8 *arg, s32 idx);

/* Walks a rotating candidate index over the measured byte table until a free slot
   is found, arms it, and clears the whole window when none is. */
void func_L16_00412C58(u8 *arg, s32 start, s32 end);

/* Finishes the pending entry (its two saved vectors are copied back), then resets the
   level's handles. */
/* Level teardown: releases the handles the level state holds. */
/* func_PAL_L16_004180B0 is in L16_00412F48-g8.c. */

/* func_L16_004130B0 is in L16_004130B0-qcopy.c. */

/* State 0: moves by the state's velocity and frees itself when the state's timer (+0x30)
   runs out, unless +0x31 is set. State 2: moves, lowers the velocity's third component by
   +0x34, turns its basis by the state's rotation and ages; on a collision record, or past
   90 frames when func_00277258 reports, it runs its impact effects toward D_L16_001B9B00,
   spawns six particles and frees itself. */
/* Prepares a 16-byte record from the handle and reports one when the queried value
   does not exceed zero. */
/* func_L16_00413700 is in L16_00413700-qcopy.c. */

/* func_L16_00413D10 is in L16_00413D10-g8.c. */
