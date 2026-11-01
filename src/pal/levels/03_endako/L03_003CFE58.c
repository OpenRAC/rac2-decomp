#include "include_asm.h"

#include "common.h"
extern s32  func_32AB10(char *a0);
extern s32  func_002E5CF8(s32 a0, s32 a1, char *a2);
extern void func_002A7750(char *a0, s32 a1, s32 a2);
extern f32  func_002A78D8(f32 a0, f32 a1);
extern f32  func_00283B98(f32 a0, f32 a1);
extern char D_L03_00188660[];
extern s32  func_312898(s32 a0, s32 a1, void *a2);
extern u8  *D_L03_001B2A1C;
extern f32  D_00189E20_19;
extern u8   D_001395BF;
extern u8   D_001395C0;
extern u8   D_001A7AFA;
extern u8   D_001A7B32;
extern u8   D_001A7AFB;
extern u8   D_001A7B33;
extern u8   D_001A7AFC;
extern u8   D_001A7B34;
extern u8 *D_L03_001B2A1C_tbl[] __asm__("D_L03_001B2A1C") __attribute__((sda));

/* func_L03_003C8660 is matched in its own unit, src/levels/03_endako/L03_003C8660-qcopy.c (-frac2-qcopy). */

/* func_L03_003C8698 is defined in L03_003C8698.c. */

/* func_L03_003CA938 lives in the -G8 sibling L03_00399230-g8.c. */


/* func_L03_003CAD78 is defined in L03_003CAD78-g8.c. */

/* func_L03_003CB398 is defined in L03_003CB398-g8.c. */

/* func_L03_003CBC40 is defined in L03_003CBC40-g8.c. */

/* Picks the actor's next motion slot: case 0 draws a random turn rate, case 1
   re-checks the 0x70-stride table entry before refreshing the aim. */
void func_PAL_L03_003CFE58(char *a0)
{
    char *s0 = a0;
    char *s1 = *(char **)(s0 + 0x68);

    switch (*(u8 *)(s0 + 0x20)) {
    case 0:
        func_002A7750(s0, 1, -1);
        *(f32 *)(s1 + 4) = func_002A78D8(60.0f, 90.0f) * 0.0003490659f;
        *(s32 *)(s1 + 8) = -1;
        break;
    case 1: {
        s32 v = *(s32 *)s1;

        if (v != 0) {
            char *p = D_L03_00188660 + *(s32 *)(s1 + 8) * 0x70;

            if (*(char **)(p + 0x88) != s0 || *(u8 *)(p + 0x74) == 0)
                *(s32 *)(s1 + 8) = func_002E5CF8(0, 4, s0);
        }
        *(f32 *)(s0 + 0xF8) = func_00283B98(*(f32 *)(s0 + 0xF8),
            *(f32 *)(s1 + 4));
        break;
    }
    }
}


INCLUDE_ASM("asm/pal/levels", func_PAL_L03_003CFF40);
