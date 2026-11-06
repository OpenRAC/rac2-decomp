/* 6 November 2026: best C below unchanged (732/732, 0/27, 2 rows). The RAC1 donor
 * spawn_decoy (rac1-decomp trespasser_and_throwing_gloves.c) has the same retire loop:
 * `while (list[0] >= 6)` and `for (i = 1; i <= list[0]; i++) (u8 *)(base + (list[i] << 8))`
 * with `s16 list[]` and `s32 base` MACRO_ADDR aliases of D_L00_001B1FF0/D_L00_001B1E9C.
 * Transcribed, it gets retail's zero-init order, but &D and the constant 5 swap s3/s4
 * (5 rows): priorities 3/82 (&D) against 3/80 (5) need retail's pre-header order
 * [5, &D, 1]. Tried with it: groups around each retire statement, the inner loop or the
 * whole scan (6-14 rows), `> 5`, struct count in the test or the bound, the call's list
 * pointer, `* 0x100` (all 5 or worse). Reopen on that pre-header order. */
/* Claude Opus 5.5 (opus-1), 29 October 2026: retained near miss, not linked.
 * Profile: -O2 -G0 -ffunction-sections (default; a unit of its own works the same).
 * USA v1.01: 732/732 bytes, 0/27 places, first difference +0x1EC; exactly two
 * instructions differ: at the outer-loop head retail has `daddu s0,zero,zero`
 * (oldest = 0) between sll/sra and `daddu a3,zero,zero` (oldestAge = 0) in the
 * blez delay slot; this body has them swapped.
 * What this draft fixed (previous best 9 rows): the retire loop indexes the
 * list (`D.index[i]`, 0-based for loop) so the list base is a loop-hoisted
 * register after the capacity guard, the s3/s4 roles, the t1/a1 order and the
 * 5/&D/1 pre-header order all match retail.
 * Why the swap remains (cse.c make_regs_eqv, verified by dump): the for loop's
 * duplicated first test `0 < count` uses whichever zero-valued pseudo lives
 * longest as its zero operand; that is `oldest` (used after the loop), so
 * combine moves `oldest = 0` next to the blez. Retail's order needs the zero
 * operand to be i or oldestAge, or no zero register at all.
 * The sibling list walkers (func_L00_002AE0C8, func_002B3BA8) use the 1-based
 * form `for (i = 1; i <= D[0]; i++) D_1E9C + (D[i] << 8)`. With it (D as
 * `short[]`, MACRO_ADDR or sda) the zero-init order matches, but cse_around_loop
 * and gcse PRE share &D between the inner test and the body, the outer loop has
 * 62 real insns at loop pass 1, so the constant 5 is "not desirable" there
 * (loop.c threshold 60-61, minus 3 per move) and the pre-header order becomes
 * [&D, 5, 1] (5 rows: s3/s4 traded). With a local `count = D[0]` bound it has
 * 55 insns, so 5 and 1 both move in pass 1: [5, 1, &D] (5 rows). Retail needs
 * 58-60 insns there (5 moves in pass 1, 1 and &D in pass 2). A 1-based form
 * with that count is the most likely reopening point. -fno-gcse breaks the
 * weapon predicates; -frac2-gcse-unsplit-edges and -g change nothing.
 */
#include "common.h"
typedef struct { int active; unsigned char kind; char pad05[0xDB]; } WeaponRecord;
typedef struct { short count; short index[31]; } ProjectileList;
extern char *D_0018C0B0;
extern unsigned char D_00139568[];
extern WeaponRecord D_L00_00262570[];
extern ProjectileList D_L00_001B1FF0 MACRO_ADDR;
extern char *D_L00_001B1E9C MACRO_ADDR;
extern char *func_0029EFD0(int);
extern int func_002FED90(void *, int, float, float, float);
extern void func_002AB650(u8 *);
extern void func_002A0F48(char *);
extern void func_002ACAD0(int, unsigned short *), func_002ACA50(int, short *, short);
/* Separate predicates match the weapon pool's two active families. */
static __inline__ int projectile_standard_weapon(void) {
    unsigned char *game = D_00139568;
    WeaponRecord *entry = D_L00_00262570 + game[0x11];
    int result;
    if (!entry->active) goto no;
    if (entry->kind == 2) goto yes;
    if (entry->kind != 1) goto no;
yes:
    result = 1;
    goto done;
no:
    result = 0;
done:
    return result;
}
static __inline__ int projectile_upgraded_weapon(void) {
    unsigned char *game = D_00139568;
    WeaponRecord *entry = D_L00_00262570 + game[0x11];
    int result = 0;
    if (entry->active) result = entry->kind == 3;
    return result;
}
/* Creates a projectile and retires the oldest live entries when the shared list is full. */
char *func_L00_00398810(char *position, char *direction) {
    char *actor = func_0029EFD0(0xCB);
    char *state, *hero, *oldest;
    int i, count, age, oldestAge;
    if (actor) {
        *(unsigned char *)(actor + 0x30) = 0xFF;
        *(unsigned short *)(actor + 0x32) = 0x1FF;
        *(unsigned short *)(actor + 0x34) |= 0x100;
        state = *(char **)(actor + 0x68);
        qcopy(actor + 0x10, position);
        qcopy(state + 0x10, direction);
        *(unsigned char *)(actor + 0x20) = 0;
        hero = D_0018C0B0;
        qcopy(actor + 0xC0, hero + 0xC0);
        qcopy(actor + 0xD0, hero + 0xD0);
        qcopy(actor + 0xE0, hero + 0xE0);
        *(int *)(state + 0x30) = 0;
        *(int *)(state + 0x2C) = 0;
        *(int *)(state + 0x28) = 0;
        *(int *)(state + 0x20) = func_002FED90(actor, 0, 1.0f, 1.0f, 1.0f);
        func_002AB650((u8 *)actor);
        *(unsigned char *)(state + 7) = 250;
        *(short *)(state + 0xC) = 4;
        *(short *)(state + 0xE) = 15;
        *(short *)state = 0;
        *(unsigned char *)(state + 8) = 0;
        *(unsigned char *)(state + 9) = 0;
        *(int *)(state + 0x44) = 0;
        *(int *)(state + 0x48) = 0;
        *(int *)(state + 0x4C) = 0;
        *(int *)(state + 0x40) = 0;
        *(int *)(state + 0x3C) = 0;
        *(int *)(state + 0x38) = 0;
        if (projectile_standard_weapon() || projectile_upgraded_weapon()) *(float *)(state + 0x24) = 60.0f;
        else *(float *)(state + 0x24) = 6.0f;
        if (D_L00_001B1FF0.count > 5) {
            do {
                oldest = 0;
                oldestAge = 0;
                for (i = 0; i < D_L00_001B1FF0.count; i++) {
                    char *candidate = D_L00_001B1E9C + D_L00_001B1FF0.index[i] * 0x100;
                    if (candidate && *(short *)(candidate + 0xAA) == 0xCB && *(unsigned char *)(candidate + 0x20) < 4) {
                        age = *(int *)(*(char **)(candidate + 0x68) + 0x3C);
                        if (oldestAge <= age) { oldest = candidate; oldestAge = age; }
                    }
                }
                if (oldest) {
                    *(unsigned char *)(oldest + 0x20) = 5;
                    func_002ACAD0((int)oldest, (unsigned short *)&D_L00_001B1FF0);
                    *(int *)(*(char **)(oldest + 0x68) + 0x40) = 1;
                }
            } while (D_L00_001B1FF0.count > 5);
        }
        func_002ACA50((int)actor, (short *)&D_L00_001B1FF0, 31);
        func_002A0F48(actor);
    }
    return actor;
}
