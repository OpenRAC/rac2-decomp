/*
 * Retained manual C reconstruction; not linked or counted.
 * Profile: -O2 -G8 -ffunction-sections (a *-g8.c sibling: the slot-name table is read through $gp).
 * Retail: 400 bytes; compiled: 400 bytes.
 * Coverage: us: 0/27 (tools/check.py, 2026-10-28, master 1243c8ea).
 * Residual: 85 of 100 words differ, all register allocation and scheduling; the control flow,
 * loads and stores follow retail. Retail keeps the block's full address in $s0 only for the
 * entry guards, saves its %hi in $s5 across the call and rebuilds %lo(D_00189E20) inside the
 * loop; this C keeps the full address live in $s1 for the whole function and loads the weapon
 * table's address into $s0 before the call instead of after it.
 * Tried without change (all 400 bytes, same 85 words): a local pointer for the guards only,
 * guards joined with ||, the whole body under one && condition, the weapon lookup split
 * through a temporary. A local pointer for the whole function gives 380 bytes; one set at
 * the top of the loop gives 388.
 * Reopen: a declaration or access form that leaves only D_00189E20's %hi live across the call.
 */
#include "include_asm.h"

/* The resident state block. */
extern unsigned char D_00189E20[];

/* The slot of each weapon, and the level's weapon table it indexes (0xE0 bytes a row). */
typedef struct { char head[0x2C]; int value; char tail[0xB0]; } WeaponEntry;
extern unsigned char D_00139568[];
extern WeaponEntry D_L00_00262570[];

/* A pair of 0x600-byte buffers per slot. */
typedef struct { char first[0x600]; char second[0x600]; } BufferPair;
extern BufferPair D_L00_001B7400[];

/* The two names the slots are created from, read through $gp. */
extern int D_L00_001A7D00[2] __attribute__((sda));

extern int func_L00_002ADEA0(int a0);
extern void *func_L00_00310BC8(int owner, int name);
extern void func_L00_00311080(int owner, void *slot, int value, int a3, int t0, int t1);

/* Fills the two slots of the block when the level is running and enabled: each empty slot
   is created from its name and set up with its buffer pair and the current weapon's value.
   The second slot is filled only when the mode byte at 0x22BB is two. */
void func_L00_002AF3D8(int a0, int a1)
{
    char *slot;
    int value;
    int i;

    if (D_00189E20[0x22B4] != 0)
        return;
    if (D_00189E20[0x22B8] == 0)
        return;
    if (D_00189E20[0x22BA] == 0)
        return;
    if (a0 != 0)
        return;
    if (a1 == 0)
        return;

    value = D_L00_00262570[D_00139568[func_L00_002ADEA0(0)]].value;
    if (value == -1)
        return;

    for (i = 0; i < 2; i++) {
        if (((char **)(D_00189E20 + 0xE98))[i] != 0)
            continue;
        if (i == 1 && D_00189E20[0x22BB] != 2)
            break;
        slot = func_L00_00310BC8(*(int *)(D_00189E20 + 0x2290), D_L00_001A7D00[i]);
        ((char **)(D_00189E20 + 0xE98))[i] = slot;
        if (slot == 0)
            continue;
        *(int *)(D_00189E20 + 0xEA4) = 0;
        *(int *)(slot + 0x8) = 0;
        *(char **)(slot + 0x3C) = D_L00_001B7400[i].second;
        *(char **)(slot + 0x38) = D_L00_001B7400[i].first;
        func_L00_00311080(*(int *)(D_00189E20 + 0x2290), slot, value, 0, 0xF, 1);
        *(float *)(slot + 0x28) = 1.0f;
    }
}
