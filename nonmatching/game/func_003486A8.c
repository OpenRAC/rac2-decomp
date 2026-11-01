#include "include_asm.h"

typedef int s32;
typedef unsigned char u8;

extern void func_003361E0(void *, void *, void *);
extern void func_00336A38(void *, void *);
extern int func_003489E8(void *, int);
extern char D_001ADC10[];
extern char D_001ADC18[];
extern char D_001ADC28[];
extern char D_001ADFC0[];
extern char D_001ADFC8[];
extern char D_001AE5B0[];
extern char D_001AE5B8[];
extern char D_001AE5C8[];

/* Near miss for func_003486A8 (boot 0x003486A8, 824 bytes, 28 places: the boot
 * and every level).
 *
 * Current-master check: 804 bytes, 0 of 28 places match.  The shape is the
 * retail one - the same seven func_003361E0 calls with the same level data
 * addresses, the same seven-entry 0x48-byte slot loop, the same seven
 * func_00335E20 colour writes and the same seven func_00336390 calls - and
 * the matched sibling func_00345490 (src/game/00345358-init.c) is the same
 * code with other offsets, so the reconstruction is the game's.
 *
 * What still differs, measured on the boot (all of it register or frame
 * layout, no missing work):
 *
 *  - The frame is 0x70 here and 0x80 in retail.  Retail keeps the zero float
 *    of the slot loop in $f20, a callee-saved float register it saves in the
 *    prologue and restores in the epilogue; this compiler folds the float
 *    variable to the constant 0.0 and rematerialises it in the loop instead
 *    (mtc1 $zero, $f13 plus two copies).  Keeping the variable alive needs a
 *    source shape this cc1 does not propagate away.
 *  - The prologue saves the callee-saved registers in the order
 *    $s3, $s4, $s0, $s1, $s2, $s5, $s6, $s7; this build saves $s5 before
 *    $s0-$s2 and materialises the a1 = 0 of the first call in its delay slot
 *    instead of before the saves.
 *  - The five spilled pointers land in the stack slots 0x00, 0x04, 0x08,
 *    0x0C and 0x10 in the order self+0x130, self+0xE4, self+0x98, self+0x4C
 *    and self+0x17C; here they are ordered differently, so the stores and
 *    the later reloads differ.
 *  - The first reference to D_001A8CFC is assembled in the small-data form
 *    (lw $a1, 0($gp)) instead of retail's lui/addiu pair, because the symbol
 *    is declared with the .sdata attribute the file needs for the matched
 *    func_0034AD10.
 *
 * The level data addresses (0x1ADC10 to 0x1AE5C8) and the pointer at
 * 0x1A8CFC are the same address in every program, so they need no ref_
 * name; their %hi/%lo pairs are what retail assembles.
 */
void func_003486A8(u8 *self, void *owner)
{
    u8 *slot;
    int i;

    func_00348578(self, 0);
    *(int *)(self + 0x43C) = 0;
    *(void **)(self + 0x438) = owner;
    if (owner) {
        int *list = func_00336DA8(16, func_00336E40(owner));
        *(int **)(self + 0x434) = list;
        list[1] = 0;
        list[2] = 0;
        list[3] = 0;
        list[0] = 0;
    }
    *(int *)(self + 0x440) = 1;
    (*(float **)(self + 0x434))[0] = 250.0f;
    (*(float **)(self + 0x434))[1] = 190.0f;
    func_003361E0(self, D_001ADC10, owner);
    func_003361E0(self + 0x130, D_001ADC18, owner);
    func_003361E0(self + 0x4C, D_001ADC28, owner);
    func_003361E0(self + 0x98, D_001ADFC0, owner);
    func_003361E0(self + 0xE4, D_001ADFC8, owner);
    func_003361E0(self + 0x17C, D_001AE5B0, owner);
    func_003361E0(self + 0x1C8, D_001AE5B8, owner);
    *(int *)(self + 0x410) = 0;
    *(int *)(self + 0x444) = 0;
    slot = self + 0x218;
    {
        int *flags = (int *)(self + 0x418);
        float zero = 0.0f;
        for (i = 6; i >= 0; i--) {
            func_003369A8(slot, D_001AE5C8, owner);
            func_00336A38(slot, 0);
            func_00335F88(slot, 1.0f, zero, zero, zero);
            *(int *)func_00335E20(slot) = 0x80F0F0F0;
            *flags = 1;
            flags++;
            slot += 0x48;
        }
    }
    *(int *)func_00335E20(self) = 0x60442D00;
    *(int *)func_00335E20(self + 0x130) = 0x55F0C070;
    *(int *)func_00335E20(self + 0x4C) = 0x55F0C070;
    *(int *)func_00335E20(self + 0x98) = 0x55F0C070;
    *(int *)func_00335E20(self + 0xE4) = 0x80FFDE8D;
    *(int *)func_00335E20(self + 0x17C) = 0x70FFFEED;
    *(int *)func_00335E20(self + 0x1C8) = 0x60442D00;
    func_00336390(self, D_001A8CFC, 0x1C);
    func_00336390(self + 0x130, D_001A8CFC + 0x8710, 0x1D);
    func_00336390(self + 0x4C, D_001A8CFC + 0x8710, 0x1E);
    func_00336390(self + 0x98, D_001A8CFC + 0x8710, 0x1F);
    func_00336390(self + 0xE4, D_001A8CFC + 0x8710, 0x20);
    func_00336390(self + 0x17C, D_001A8CFC + 0x8710, 0x73);
    func_00336390(self + 0x1C8, D_001A8CFC + 0x8710, 0x74);
    func_003489E8(self, 0);
}
