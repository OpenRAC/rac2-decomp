#include "include_asm.h"
#include "names.h"

typedef unsigned char u8;

typedef unsigned short u16;

typedef signed short s16;

typedef signed int s32;

/* func_L18_00427BE0 lives in L18_00427BE0-update-g8.c. */


/* Reports zero after handing the level's measured list to the shared test. */
extern void func_L00_003B9310(void *);

extern u8 D_L18_002571A0[];
extern void func_3DB8F8(void *, void *);
extern char ref_L18_002571A0_00[];

/* Only the tagged object starts the sequence; the answer is always false. */
s32 func_L18_00428100(char *moby) {
    if (*(s16 *)(moby + 0xAA) == 0xEE1 /* Receiver Bot */)
        func_3DB8F8(moby, ref_L18_002571A0_00);
    return 0;
}
/* func_L18_00428138 lives in L18_00428138-g8.c. */


/* Maps the class identifier this level tags an object with to its small integer. The unit is
   built with -frac2-keep-block-order (config/cflags.txt): the switch keeps its default last,
   behind the dispatch's `b`, as in retail. */
/* Gives each enemy kind a small number, or -1 for an unknown kind. */
s32 func_L18_004283F0(u8 *moby) {
    s32 result;

    switch (*(s16 *)(moby + 0xAA)) {
    case 0xEC0 /* moby class 3776 */: result = 3; break;
    case 0xEE1 /* Receiver Bot */: result = 10; break;
    default: result = -1; break;
    }
    return result;
}

/* func_L18_00428428 lives in L18_00427BE0-shot-g8.c. */

/* Stores the measured halfword control for the one class that carries it, leaving
   the two silent classes alone and renewing the shared slot for anything else. */
extern void func_0026FEB8(void *);

extern u16 D_L18_001B1240 __attribute__((sda));

extern u8 D_L18_001B1360[];

/* Resets the enemy's timer from a shared value for the first kind, and does nothing for two other kinds. */
void func_L18_004286D0(u8 *moby) {
    u8 *state = *(u8 **)(moby + 0x68);
    switch (*(s16 *)(moby + 0xAA)) {
        case 0xEC0 /* moby class 3776 */:
            *(u16 *)(state + 0x392) = D_L18_001B1240;
            break;
        case 0xED4 /* moby class 3796 */:
            break;
        case 0xEE1 /* Receiver Bot */:
            break;
        default:
            STUB_printf(D_L18_001B1360);
            break;
    }
}



/* func_L18_00428F08 lives in L18_00428F08-g8.c. */


/* func_L18_0043E938 lives in the sibling small-data unit (L18_00427BE0-g8.c): its controls are read through $gp. */

/* func_L18_0043E9B0 lives in the sibling small-data unit (L18_00427BE0-g8.c): its
   controls are read through $gp in ordinary flow. */

/* func_L18_0043EA90 lives in L18_00427BE0-g8.c. */

/* func_L18_0043EDE8 lives in the sibling small-data unit (L18_00427BE0-g8.c): its spin limits are read through $gp. */


/* func_L18_0043EF40 is written with its sibling func_L18_0043F040 above. */

/* rotates the two 0xA0 blocks of the state's local frame into the shared matrices */
typedef float f32;

typedef int TI128 __attribute__((mode(TI)));

extern s32 D_L18_001B2348;

extern u8 D_L18_002BD9B0[];

extern s32 func_002A77E0(s32);

extern void func_00283098(void *, const void *, const void *);

extern void func_00282CC0(void *, void *, void *);

extern f32 func_00283B98(f32, f32);

extern f32 func_00283180(f32);

extern f32 func_00283198(f32);

/* Updates the spinning angles of two groups of parts and works out the rotation values for each. */
void func_L18_0043F040(u8 *moby) {
    u8 *state = *(u8 **)(moby + 0x68);
    s32 i;
    for (i = 0; i < 2; i++) {
        u8 *partBlock = state + i * 0xA0;
        s32 j;
        for (j = 1; j >= 0; j--) {
            *(f32 *)(partBlock + 0x40) = FastAddRotations(*(f32 *)(partBlock + 0x40), *(f32 *)(partBlock + 0x60));
            *(f32 *)(partBlock + 0x44) = FastAddRotations(*(f32 *)(partBlock + 0x44), *(f32 *)(partBlock + 0x64));
            *(f32 *)(partBlock + 0x48) = FastAddRotations(*(f32 *)(partBlock + 0x48), *(f32 *)(partBlock + 0x68));
            *(f32 *)(partBlock + 0x20) = FastSinOrCosA(*(f32 *)(partBlock + 0x40)) * *(f32 *)(partBlock + 0x80);
            *(f32 *)(partBlock + 0x24) = FastSinOrCosB(*(f32 *)(partBlock + 0x44)) * *(f32 *)(partBlock + 0x84);
            *(f32 *)(partBlock + 0x28) = -FastSinOrCosB(*(f32 *)(partBlock + 0x48)) * *(f32 *)(partBlock + 0x88);
            partBlock += 0x10;
        }
    }
}

/* func_L18_0043EF40 is matched in its own unit, L18_0043EF40-g8.c. */

/* func_L18_0043FFF8 is in L18_0043FFF8-g8.c. */

/* func_L18_004401E0 is in L18_00427BE0-sparks.c. */

/* Store the supplied unsigned 32-bit word at owner byte offset 0xB 8. */
void func_L18_0046B1E0(int owner, unsigned int value)
{
  *(unsigned int *)(owner + 0xb8) = value;
  return;
}
