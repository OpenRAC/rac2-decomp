/* func_002F0FA0 - near miss: 112 bytes of the retail 108, 0/28 places
 * (opus-1, Claude Opus 5.5, 3 November 2026, task v2127).
 *
 * Clears the flags of every 0x20-byte record of a list, after copying one
 * value and clearing four globals. Belongs in src/game/002EEB00-g8.c (one
 * global is reached through $gp; -G8 is the unit's profile).
 *
 * Every retail word is reproduced, in retail's order and registers: the split
 * %hi/%lo load of the value (nosda), the tied lui+lw macro loads of the list
 * bounds (plain externs), the three `lui $at; sw` stores, the $gp store in the
 * beq delay slot, 0xFFFF in $a0 and 0xFF in $v1, the loop reload of the end
 * before the increment and the branch-likely loop with the byte store in its
 * delay slot. The only difference is one extra NOP before the bnel.
 *
 * Measured: assembling this C's own .s with that one NOP deleted gives 27
 * words equal to the boot's retail 0x002F0FA0..0x002F100B in every opcode,
 * register and immediate field (only the relocation fields are unresolved).
 *
 * Why the NOP: the post-DBR R5900 short-loop pad (mips_r5900_pad_loops,
 * tools/compiler/patches/0054 + transformers) counts one word per RTL insn,
 * with exceptions only for TRAP_IF, asm, block moves and rac2_qcopy. The loop
 * reload `lw $2,ref_..._01` is one RTL insn but the assembler expands it to
 * lui+lw (the compiler takes the 4-byte extern for small data and its
 * `.extern NAME,4` only comes at the end of the file). Retail's loop is
 * sh, sh, lui, lw, addiu, bnel, sb = 7 words, unpadded; the pass counts
 * 6 and adds one NOP. Retail's assembler counted words. A split %hi/%lo
 * reload (nosda) would count 2 but gcse/loop share and hoist its %hi, and
 * retail's two separate luis for the same bound show the reload is the macro
 * form. Needs a compiler/tooling fix (count a symbolic macro load or store
 * by the words the assembler emits); not reachable from the C here.
 *
 * Key wording points: the record fields as struct members (a fixed scalar
 * global and a varying struct member do not conflict, so the reload is
 * scheduled before the increment); the stores written 0x16, 0x14, 0x1F
 * (puts 0xFFFF first in $a0 and the byte store first in the loop).
 *
 * The bounds and globals differ per program (level 00: 0x1B2514/0x1B2518,
 * value 0x1BF154; levels 02/11: 0x1B3C14/0x1B3C18), hence the ref_ names:
 * 00 = list start (boot 0x1B21B4), 01 = list end (0x1B21B8), 02 = value
 * (0x1BAED4, nosda: split), 03/04/05 = 0x1B21C4/0x1B21E0/0x1B21E4 (plain:
 * lui $at stores), 06 = 0x1B21E8 (sda: $gp). The bindings were not checked by
 * check.py (it stops at the size difference).
 *
 * History: earlier drafts (char * casts) reached 108 bytes only with the
 * constants and cursor in the wrong registers; the struct-member form above
 * replaces them.
 */

typedef struct {
    char pad0[0x14];
    unsigned short unk14;
    unsigned short unk16;
    char pad18[7];
    unsigned char unk1F;
} Record002F0FA0;

extern Record002F0FA0 *ref_L00_002F0FA0_00;
extern Record002F0FA0 *ref_L00_002F0FA0_01;
extern int ref_L00_002F0FA0_02 __attribute__((nosda));
extern int ref_L00_002F0FA0_03;
extern int ref_L00_002F0FA0_04;
extern int ref_L00_002F0FA0_05;
extern int ref_L00_002F0FA0_06 __attribute__((sda));

void func_002F0FA0(void)
{
    Record002F0FA0 *p = ref_L00_002F0FA0_00;
    int v = ref_L00_002F0FA0_02;
    Record002F0FA0 *end = ref_L00_002F0FA0_01;

    ref_L00_002F0FA0_03 = v;
    ref_L00_002F0FA0_04 = 0;
    ref_L00_002F0FA0_05 = 0;
    ref_L00_002F0FA0_06 = 0;

    if (p == end)
        return;

    do {
        p->unk16 = 0;
        p->unk14 = 0xFFFF;
        p->unk1F = 0xFF;
        p++;
    } while (p != ref_L00_002F0FA0_01);
}
