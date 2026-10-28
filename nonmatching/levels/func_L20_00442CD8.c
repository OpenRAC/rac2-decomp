/*
 * Retained manual C reconstruction; not linked or counted.
 * Profile: -O2 -G8 -ffunction-sections (a sibling of src/levels/20_yeedil/L20_0043ECB0-g8.c;
 * the count at $gp+0x30DC is read outside a delay slot).
 * Retail: 396 bytes; compiled: 396 bytes.
 * Coverage: us: 0/1 (tools/check.py, 2026-10-28, master 1243c8ea).
 * Residual: the queued-action array D_L20_001B20D8 (at $gp+0x30E8). Retail forms its address
 * with `addiu $a0,$gp,0x30E8`, then adds the scaled index and loads 0($v0). Declared as below
 * (incomplete, section .sdata) the assembler expands the indexed load absolutely (lui, addu,
 * lw: 6 differing lines, 3 of them relocations); `int [2]` with sda folds $gp into the
 * index (`addu $v1,$v0,$gp ; lw %gp_rel`); sizes 3, 4 and 8 with sda fall back to lui. A
 * pointer local to the array (assigned early or at the use) gives 9 or 50 lines. Reading
 * the count into a local before the 50.0 store is what puts that store in the branch's
 * delay slot, as retail; the rest of the body (both switches, the rotating bit loop) matches.
 * Reopen: a declaration that makes cc1 materialise the array address separately while the
 * assembler keeps the GP form (compare COMPILER-NOTES.md on sda/MACRO_ADDR).
 */
extern int D_L20_001B20CC __attribute__((sda));
extern int D_L20_001B20D8[] __attribute__((section(".sdata")));
extern int func_002A77E0(int);

/* Picks the object's next action into the state's +0x1834, with a 50.0 delay (+0x1838).
   A queued action (the last of D_L20_001B20D8, D_L20_001B20CC of them) wins, action 10
   with a 30.0 delay; a state at 0x12D3 takes action 11. Otherwise the state's phase
   (+0x182C) allows actions 1, 2|4 or all four, narrowed to those not yet used (+0x184C)
   when any remain; starting at a random one, the first allowed action is marked used and
   mapped 1 -> 7, 2 -> 10, 4 -> 9, 8 -> 8. */
void func_L20_00442CD8(char *object)
{
    char *state = *(char **)(object + 0x68);
    int allowed;
    int unused;
    int start;
    int bit;
    int i;
    int queued;

    queued = D_L20_001B20CC;
    *(float *)(state + 0x1838) = 50.0f;
    if (queued != 0) {
        *(int *)(state + 0x1834) = D_L20_001B20D8[queued - 1];
        if (*(int *)(state + 0x1834) == 10)
            *(float *)(state + 0x1838) = 30.0f;
        return;
    }
    if (*(int *)(state + 0x183C) == 0x12D3) {
        *(int *)(state + 0x1834) = 11;
        return;
    }
    allowed = 0;
    switch (*(int *)(state + 0x182C)) {
    case 0:
        allowed = 1;
        break;
    case 1:
        allowed = 6;
        break;
    case 2:
        allowed = 15;
        break;
    }
    unused = *(int *)(state + 0x184C) & allowed;
    if (unused != 0)
        allowed = unused;
    start = func_002A77E0(4);
    for (i = 0; i < 4; i++) {
        bit = 1 << ((start + i) % 4);
        if (bit & allowed) {
            *(int *)(state + 0x184C) &= ~bit;
            switch (bit) {
            case 1:
                *(int *)(state + 0x1834) = 7;
                break;
            case 2:
                *(int *)(state + 0x1834) = 10;
                break;
            case 4:
                *(int *)(state + 0x1834) = 9;
                break;
            case 8:
                *(int *)(state + 0x1834) = 8;
                break;
            }
            return;
        }
    }
}
