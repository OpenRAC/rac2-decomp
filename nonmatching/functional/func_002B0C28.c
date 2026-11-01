/* functional: high. Near-miss draft within a few instructions of retail: differences are register allocation, scheduling and instruction shape. */
/* func_002B0C28 (184 bytes, 28 placements): the retained candidate is close but does not
   match. A 28 October 2026 current USA v1.01 probe with -O2 -G8 -ffunction-sections
   -mno-split-addresses reports 0/28. The address relocations line up, but control-flow
   layout differs around the shared calls and tail stores. Reversing the outer condition as
   a source-shape experiment gives 188 bytes and also 0/28. Factoring the duplicated
   helper call into one shared call path gives 172 bytes, 0/28, and grows the frame
   from 0x20 to 0x30. A fresh `tools/check.py --diff` replay of the retained 184-byte
   candidate first differs at +0x8: cc1 starts materialising the first global address
   before saving `$s0`/`$s1`, while retail saves registers before loading the global.
   Moving the global read to immediately before the comparison in C does not change
   that schedule; it still reports 0/28 and the same +0x8 difference.

   The earlier near-miss hypothesis was that only the *address* form of the three globals
   differed, because this cc1 splits the %hi/%lo pair of a symbol address while retail keeps
   it together:
     retail: lui $v0,0x1B ; lw $v0,-0x739C($v0)
             lui $at,0x1B ; sw $s0,0x1D48($at)
     default profile: %hi may be hoisted and the low part materialised at the use.
   Two source facts still matter: globals read and written need separate names to prevent
   address CSE across calls, and D_001A8FB0 is small data at $gp-0x6040, so it needs the
   sda attribute. However, -mno-split-addresses alone is not sufficient for a match. The
   candidate remains unlinked until every placement passes. */
extern int D_001B8FB4;
extern int D_001B8FB4_b;
extern int D_001B8FB0;
extern int D_001C2088;
extern int D_001C2088_b;
extern int D_001A8FB0 __attribute__((sda));
extern int func_00288FB8(int);
extern void func_L00_0030DDB0(int, int);

int func_002B0C28(int a0, int a1, int a2)
{
    int current = D_001B8FB4;

    if (current == a0) {
        if (a1 != 0)
            func_L00_0030DDB0(func_00288FB8(a1), a2);
        D_001C2088 = a1;
        D_001A8FB0 = 2;
    } else {
        if (current != 0)
            return 0;
        if (a1 != 0)
            func_L00_0030DDB0(func_00288FB8(a1), a2);
    }
    D_001B8FB4_b = a0;
    D_001B8FB0 = 2;
    D_001C2088_b = a1;
    return 1;
}
