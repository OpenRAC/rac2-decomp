/* func_PAL_L00_00431AA0, the PAL copy of func_L00_0042C4B8: the same C. */
#include "common.h"

typedef int InitQuad __attribute__((mode(TI)));
typedef struct { u8 pad[0xB0]; float scale; } PathView;
extern PathView D_L00_001BD2C0;
typedef struct { u8 pad[0x194]; InitQuad *transform; } PathCamera;
extern PathCamera D_L00_001B8C80;
/* Partial records follow only the fields used by the two path walks.
 * Retail reserves eight weight/index slots and assumes at most eight accepted
 * entries; it does not add a bounds check to the path scan. */
/* Measured child block reached at owner->sub + 0x40. */
/* Measured partial layouts; original type and game roles are unknown. */
extern void func_L00_004276E8(char *);

extern void func_L00_00426680(char *);

#define SDA_OBJ __attribute__((section(".sdata")))

extern char *D_L00_001B1844 SDA_OBJ;

extern char D_L00_001ADD98[] SDA_OBJ;

extern char D_L00_001ADD38[] SDA_OBJ;

extern char D_L00_001ADD78[] SDA_OBJ;

extern char D_L00_001ADD58[] SDA_OBJ;

typedef struct Rac2Native_6af85cabb56d3b41_SmallConditional52Global {
    unsigned char unknown_00[0x2290];
    char *ptr_2290;
    int mode_2294;
    unsigned char unknown_2298[0x208];
    int identity_24a0;
} Rac2Native_6af85cabb56d3b41_SmallConditional52Global;

extern Rac2Native_6af85cabb56d3b41_SmallConditional52Global D_00189E20_20;

/* runs a fixed sequence of seven callees on one object handle, passing the address of two stack floats to the third callee and then their values to the fourth */
/* selects one of three scale factors from a flag byte in a fixed global table, builds two 16-byte stack values through two callees, then applies two transforms rooted at object+48 against two fixed global tables */
/* func_L00_00426560 is defined in L00_00426560-helpers.c. */

/* clears the seven words of the sub-object at +0x70 (the last after a refresh call), then
   clears the flag word and the identity word-16 of the table entry and the owner's +0x7E. */
void func_L00_00426680(char *self);

/* when the mode halfword at +0x86 is 4 or 0x51, raises the flag halfword of the table entry
   selected by the owner's index halfword at +0x84. */
/* Restores the owner's half-turn state: it measures the two world vectors of the table
   entry, compares the angle they make with a fixed threshold, and writes the owner's
   half-word at +0x7E and the entry's flag half-word at +0x290. The block at the end
   resets the entry's two small floats and the owner's state; the two tests jump to it,
   and it needs its own copy of the entry's address. */
/* Blends the saved camera position and orientation, then rebuilds its matrix. */
void func_L00_004276E8(char *object);

/* When the sub-object at +0x70 gains its flag word at +0x40, clears the byte at +0x89 and
   fades the block at +0x30 to a half-turn target. */
/* Refreshes a child sub-structure through a setup helper, folds four float pairs (one measured against a fixed half-turn constant) through a shared two-float helper, and hands the resulting four-field block to a second helper. */
/* 128-bit copies reach lq/sq only through TImode. */
/* func_L00_00427BE8 is defined in L00_00427BE8-helpers.c. */

/* resets a sub-object reached through field +112 of its argument: two int zeros through a pointer 176 bytes in, twelve float constants (0.3/0.04/0.07/1.0/0.99) and three int zeros over offsets 40..172, then four calls (sub-object, +80, +144, the argument) and a 16-bit zero at +126 */
/* func_L00_00427D50 is defined in L00_00427D50-g8.c. */

/* func_L00_004282F0 is defined in L00_004282F0-spawn.c. */

/* Reads two floats from a data block, differences them against two globals, calls a two-float helper with the difference pair, refines the returned float through a second helper, then selects one of two small state codes and clears a flag byte according to two float thresholds. */
/* func_L00_004284B0 is defined in L00_004284B0-helpers.c. */

/* func_L00_00428588 is in L00_00428588.c. */

/* runs a fixed pair of callees on the same object handle */
/* A method that does nothing and returns 0, reached through a data pointer in every
   level that has it. Its entry is 24 bytes into the catalogued row, after linker fill. */
/* When the global identity differs from the signed owner identity at offset 0x86 and the global mode is not 6, clear the owner byte at offset 0x7D and write signed short value 3 at offset 0x7E. */
#define MACRO_ADDR __attribute__((section(".sdata")))

extern char * r1_D_L10_0015F050 MACRO_ADDR;

extern char *r1_D_L10_0015F050 MACRO_ADDR;

/* rac1-decomp src/overlays/shared/vendor_00299AF0.c: func_L10_002F6E10 */
/* Adapted from Lombyte (MIT) for PAL by OpenRAC's tools/port.py: src/overlays/shared/gameplay_vendor_002e3de8.c, FUN_L10_002f5a50. */
/* rac1-decomp src/overlays/shared/rocket_and_path_camera.c: func_L00_004290C0 */
/* Adapted from Lombyte's project (GPL-3.0) for PAL by OpenRAC's tools/port.py: src/overlays/shared/gameplay_vendor_002e3de8.c, FUN_L10_002f5a78. */
int func_L00_004290C0(char *moby, char *unused);

extern int func_L00_004290C0(char *, char *);

/* func_L00_00429CE8 is defined in L00_00429CE8.c. */

/* func_L00_00429F68 is defined in L00_00429F68.c. */

/* Looks the owner's table entry up (index half-word at +0x84, 0x20 bytes per entry, the
   entry's own pointer at +0x1C) and clears its flag half-word at +0x26 and its word at
   +0x20, but only when the entry is still idle, the global gate allows it and the extra
   check accepts the owner. */
/* clears the word at +0x20 and the halfword at +0x26 of the table entry selected by the
   index argument. */
/* func_L00_0042A698 is defined in L00_00426340-g8.c. */

/* func_L00_0042A908 is defined in L00_0042A908-g8.c. */

/* The actor hook receives its owner even when this implementation returns no index. */
/* func_L00_0042AC18 is defined in L00_0042AC18.c. */

/* func_L00_0042AD98 is defined in L00_0042AD98.c. */

/* rac1-decomp src/overlays/shared/music_box_voices.c: func_L00_0042B038 */
/* reverb box sound update: starts or stops the sound as the listener enters or leaves the box */
/* refreshes the object, installs the block at +0x30 and returns the object. */
/* Store the supplied unsigned 32-bit word at owner byte offset 0x 44. */
/* Store the supplied unsigned 32-bit word at owner byte offset 0x 40. */
/* Store the supplied unsigned 32-bit word at owner byte offset 0x 40. */
void func_PAL_L00_00431AA0(int param_1, unsigned int param_2)
{
  *(unsigned int *)(param_1 + 0x40) = param_2;
  return;
}

/* Store the supplied unsigned 32-bit word at owner byte offset 0x 44. */
/* Return the complete supplied unsigned-long 64-bit value unchanged. */
/* Target: FUN_003427B0 â€” identity function returning its first argument */
/* Disassembly: jr ra; move v0,a0 (MIPS delay slot) */
/* Compiled with: -O2 -G0 -ffunction-sections */

