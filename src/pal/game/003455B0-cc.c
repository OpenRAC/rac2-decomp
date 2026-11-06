/* func_PAL_003455B0, the PAL copy of func_00343538: the same C. */

typedef unsigned char u8;

/* Measured partial C views; original types and object ownership are unknown. */
typedef unsigned char QwenRecovery_a2544d80ec96_AbiByte22;

extern void func_00342F70(QwenRecovery_a2544d80ec96_AbiByte22 *owner, const QwenRecovery_a2544d80ec96_AbiByte22 *table);

typedef int s32;

typedef unsigned int u32;

/* initialises eight in-place sub-records of one object by four routines, then returns the object pointer */
/* sda in this -G0 unit gives the one-instruction (macro) load of D_001A8CFC that retail has; a plain
   declaration splits it into lui/lw with two registers and shifts the register allocation */
extern void func_003435B0(u8 *, u32);

/* constructor: stores the owner at +0x28C, allocates the 16-byte position at +0x288 and initialises the
   sub-objects at +0x0, +0x4C, +0x98, +0xE4, +0x1B0, +0x1F8, +0x240 and +0x298 */
void func_PAL_003455B0(QwenRecovery_a2544d80ec96_AbiByte22 *p1, const QwenRecovery_a2544d80ec96_AbiByte22 *table)
{
    func_00342F70(p1 + 0x2c8, table);
}

/* Measured target: byte-identical across all 27 levels. */
/* Measured target: byte-identical across all 27 levels. */
void func_003435B0(u8 *a0, u32 a1);

/* func_00343638 is matched in 00343200-g8.c (-G8 small data). */
