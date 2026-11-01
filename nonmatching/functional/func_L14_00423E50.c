/* functional: medium. Near-miss draft of retail size with the same frame: differences are allocation and scheduling, with some block order; paths the captured calls never take are unproven. */
/* NEAR MISS — 136 bytes emitted, 144 expected (two instructions short).
 * last check.py line: "14_aranos_prison: 136 bytes, expected 144"
 *
 * Twin of func_L14_004286F8 (same table at D_L14_001FFB60, same record base, same walk); the
 * difference is that it reads the record base absolutely instead of through $gp, and it returns
 * 1 when the tagged record's word at 0xAA is 0xF91 rather than marking it.
 *
 * Residual wall is the entry block, not the loop. Retail:
 *   00423E50 daddu $a1,$a0,$zero      ; the parameter is copied into $a1 and read through it
 *   00423E58 lbu   $v0,0x21($a1)
 *   00423E5C bne   $v0,$v1 -> L2
 *   00423E64 addiu $a0,$a2,-0x4FA0    ; base (hi in $a2 keeps 0x00200000 for the reuse at L2)
 *   00423E68 sll   $v0,$v0,2          ; idx*4 recomputed, NOT folded even though idx == 0xFF
 *   00423E6C addu  $v0,$v0,$a0
 *   00423E70 lw    $v1,0x0($v0)
 *   00423E74 bnel  $v1,$zero -> L2
 *   00423E78 lbu   $v0,0x21($a1)      ; delay slot: idx RELOADED (the lw above may alias it)
 *   L2: 00423E8C addiu $v1,$a2,-0x4FA0   ; base recomputed from the saved %hi
 * This compiler instead folds `idx * 4` to the constant 0x3FC in the `idx == 0xFF` arm and
 * materialises the base without keeping the %hi, which costs both missing words. The loop
 * (c = *(short *)p; p++; while (c >= 0)) is otherwise identical to retail.
 */
extern char D_L14_001FFB60[];
extern int D_L14_001B259C;

int func_L14_00423E50(char *a0)
{
    unsigned char idx;
    unsigned short w;
    short c;
    unsigned short *p;
    char *q;

    idx = *(unsigned char *)(a0 + 0x21);
    if (idx == 0xFF && *(int *)(D_L14_001FFB60 + idx * 4) == 0)
        return 0;
    p = *(unsigned short **)(D_L14_001FFB60 + idx * 4);
    do {
        w = *p;
        q = (char *)(D_L14_001B259C + ((w & 0x7FFF) << 8));
        if (*(char *)(q + 0x20) >= 0 && *(short *)(q + 0xAA) != 0xF91)
            return 1;
        c = *(short *)p;
        p++;
    } while (c >= 0);
    return 0;
}

/* --- wave 24, worker 04 (2026-10-21) --------------------------------------------
   Re-measured: the walk itself matches word for word; the head does not.  With
   the goto spelling (the main path is the branch TARGET of both guards, which
   is retail's shape) the body is 160 bytes: retail copies the parameter into
   $a1, keeps the table's %hi in $a2 across the whole function and re-reads the
   table entry for the walk, while ours keeps the parameter in $a0, re-materialises
   the table's %hi in the walk block and reuses the first table load.
   What I added to the measurements:
   - the main path must be the branch target of both guards (retail's `bne` and
     `bnel` both jump to it): the plain if/else-if chain puts the main path in
     the fall-through and inverts both branches.
   - the table is read twice (the null check and the walk pointer) and the index
     is re-read from the object; the base D_001B259C is read absolutely here
     (lui %hi ; lw %lo) while func_L14_004286F8 reads the same global through
     $gp, so the two need different names in one unit.
   - with the index in a local the address folds to `lw $v1,0x3FC($v0)` and the
     index is lost (that is the 0x3FC of the earlier note).
   Last check.py line: "14_aranos_prison: 160 bytes, expected 144". */
