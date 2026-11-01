#include "include_asm.h"

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef int s32;
typedef short s16;

extern u32 D_L15_001FB320[];
extern s32 func_002ED688(void *);
extern char *D_L15_001B261C_base[] __asm__("D_L15_001B261C") __attribute__((sda));

/* func_L15_00315428 is defined in L15_00315428-effects-g8.c. */

extern void *func_803804E8(int a0);

/* Stores the second argument into the record the lookup returned. */
void func_L15_003804B8(int a0, void *a1)
{
    void *p = func_803804E8(a0);

    if (p != 0) {
        *(void **)((char *)p + 0x158) = a1;
    }
}

/* Counts list entries with an active object, a linked record and positive value. */
s32 func_L15_00381CF0(char *arg0) {
    u16 *p;
    char *base;
    char *e;
    char *o;
    u32 slot;
    s32 v;
    s32 count = 0;
    float f;

    slot = D_L15_001FB320[(u8)arg0[0x21]];
    if (slot == 0)
        return 0;
    p = (u16 *)slot;
    f = 0.0f;
    do {
        base = D_L15_001B261C_base[0];
        e = (char *)(((*p & 0x7FFF) << 8) + (u32)base);
        if ((*(u16 *)(e + 0x34) & 0x20) != 0) {
            o = *(char **)(e + 0x68);
            v = func_002ED688(e);
            if (*(s32 *)o != 0 && *(s32 *)(v + 0x110) != 0 &&
                f < *(float *)(*(s32 *)o))
                count++;
        }
    } while (*(s16 *)p++ >= 0);
    return count;
}




INCLUDE_ASM("asm/levels", func_L15_0041F2F8);

INCLUDE_ASM("asm/levels", func_L15_0042DCE0);

INCLUDE_ASM("asm/levels", func_L15_0042E1B0);

INCLUDE_ASM("asm/levels", func_L15_0042EFE0);

/* func_L15_0042FD40: attempt kept in drafts (148 bytes, +0x4 differs). */
/* func_L15_0042FD40 is defined in L15_00315428-g8.c (this unit has no $gp access for it). */

/* func_L15_0042FFB8 is defined in L15_00315428-g8.c (it reaches a global through $gp). */

INCLUDE_ASM("asm/levels", func_L15_00430168);

/* func_L15_00430590 is defined in L15_00430590-g8.c. */

INCLUDE_ASM("asm/levels", func_L15_004307E0);

/* func_L15_00430B30 is defined in L15_00430B30-g8.c. */


/* func_L15_00430DF0 is defined in L15_00430DF0-g8.c. */

INCLUDE_ASM("asm/levels", func_L15_00431590);

/* func_L15_00432008: attempt kept in drafts (176 bytes, 4 instructions over). */
/* func_L15_00432008 is defined in L15_00315428-g8.c (this unit has no $gp access for it). */

/* func_L15_004320B0 is matched in its own unit, src/levels/shared/L15_004320B0-qcopy.c (-frac2-qcopy -frac2-qcopy-barrier). */

extern unsigned char D_L15_004328E8[];

extern void func_L15_00432210(void *a0);
extern void func_802FFC98(void *a0, void *a1);
extern int func_803068A0(void *a0);
extern void func_80329048(void *a0);

/* Runs the level's per-frame update once the record is in its armed state. */
void func_L15_004321A8(char *p)
{
    char *q = *(char **)(p + 0x68);

    if (*(unsigned char *)(p + 0x20) == 1) {
        func_L15_00432210(p);
        func_802FFC98(D_L15_004328E8, p);
        if (func_803068A0(q + 0x54) != 0) {
            func_80329048(p);
        }
    }
}

/* func_L15_00432210 is defined in L15_00432210-g8.c. */
