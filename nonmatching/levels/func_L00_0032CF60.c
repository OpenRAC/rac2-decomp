/* 6 November 2026 (round 12): not matched; see func_002B6658 round-12 note. The same asm call statement (`object` for `t`) with both 0x34 tests read through `volatile unsigned short *`, on the body below in an own -O2 -G8 -ffunction-sections -g unit, gives tools/check.py 27 of 27. No linked build was run. Both forms are forbidden in linked C. */
/* 6 November 2026 (round 11, w-c5): not matched; see func_002B6658 round-11 note. The same control-flow forms (if/else arms each calling, goto to a shared call, do/while(0) group over call + 0x4 test) compiled with -g give the identical filled `jal v1; move a0` and a v0 callback; no C form puts a surviving label, jump or trap_if between the a0 move and the call. */
/* 6 November 2026 (round 10, w-c5): not matched; see func_002B6658 round-10 note. Retail (0x32D008) also tests v0 in the bnel, so the s0-vs-v0 sibling lead gives no source form; the jalr slot still needs a reorg stopper no C form here produces. */
/* 6 November 2026 (round 9, w-cc): not matched, no flag; see func_002B6658 round-9 note. A volatile callback member is ruled out by retail itself (the lw is stolen into bnel). Matched func_L00_002D5940 has the same pre-reorg shape with a v0 callback and a filled slot, so no reorg or allocation rule keyed on this shape can be landed. */
/* 6 November 2026 (round 6, w-c5): not matched; see func_002B6658 note (same blocker). Retail's `beqz; nop; daddu a0; jalr v1; nop` is exactly what gas emits when cc1 leaves both slots unfilled; no C form found that makes reorg refuse the adjacent a0 move, and the callback pseudo has no v0 conflict. */
/* 5 November 2026 (round 5, w-cc): not matched, no flag; see func_002B6658 note. Same result with the pointer form: a callback read before the 0x40 test plus a reload after func_002A05A8 keeps the callback live over the v0 flag test, so global-alloc gives v1; but reorg then backfills the first lw into a plain bne (retail bnel, stolen from target) and still fills the jalr slot. Census of `move aN; jal; nop` in boot+L00: the matched-C sites checked (func_0027A1D0, func_L00_003F5870) are unfilled because a real cross-jump label sits between the arg move and the jal; no source form here gives such a label, and no principled reorg rule covers only these two sites. */
/* 5 November 2026 (w-c6): same result as func_002B6658 (see its note): load/call/test groups and both-arm loads keep v0 and the filled slot; v1 needs a hard v0 conflict across lw..jalr, not a priority change. */
/* 5 November 2026: own -O2 -G8 -g unit with retained body: 256/260. Reading the two post-scan flag tests through `volatile unsigned short *` (0x34) gives retail's `beqz; nop` before the callback (260/260 except below); a volatile callback-pointer load instead blocks the bnel steal (wrong); int-returning callback is neutral. Left: callback pointer in v0 (retail v1) and retail's `daddu a0; jalr v1; nop` unfilled jalr slot (ours fills it with the a0 move). */
/* 5 November 2026 (wave 3): not matched. Only these two functions (all 28/27 places) have lw v1;beqz;nop;daddu a0;jalr v1;nop; the 27 FILLED lw v0,0x64(s2) sites are func_L00_002D5940 (C, plain `if (obj->update) obj->update(obj);`). Reorg (reorg.c fill_simple_delay_slots) can only refuse the a0 move if a stopper (label/asm/jump) sits between it and the call: an empty asm after a $4-pinned arg reproduces nop+daddu+jalr+nop exactly, and a $3 pin gives v1, but both are banned. int/ptr/double/long long/char/short returns, switch/goto/cross-jump forms, int-view test, local copy, inline helper with -mastra-sibcall/-mastra-cygnus-cfg, and -O1/-O3/-Os/-fno-* flags all keep v0 and the filled slot. */
/* 4 November 2026 bounded source-method review; retained, not linked.
 * Four new actual read/dispatch/address-word forms under O2/G8/g reach 260/260 bytes but 0/27 USA
 * places, first +0xA8. A complete measured flags-reload view removes speculative flag-load
 * motion, but callback v0/v1 allocation and the branch/jalr delay slots still differ. The older
 * plain 256-byte draft below is retained; no nonvoid callback return, invented argument or
 * instruction patch was used.
 */
/* 4 November 2026 actual-contract review; retained near miss, not linked.
 * USA v1.01 check.py: 256/260 bytes, 0/27 placements; first difference size mismatch.
 * Profile: -O2 -G8 -ffunction-sections -g.
 * The raw-pointer draft, a complete measured 0x100-byte state/next/flags/callback record and a
 * direct callback-member call produce identical checker output. This establishes a three-form
 * tie; neither layout nor callback-local removal resolves the allocation/delay-slot difference.
 * The original body is preserved.
 * Earlier measurements below are historical where superseded by this note.
 */
/* Retained plain-C attempt: 256/260 bytes; first difference +0x88.
 * us: 0/27, pal: 0/27, us2: 0/27.
 * Profile: -O2 -G8 -ffunction-sections -g.
 * The scan matches structurally, but callback-pointer allocation and delay-slot scheduling differ. -g and disabling the second scheduler did not resolve it. Next: callback ABI/lifetime evidence.
 */
extern int D_L00_001FACE0 __attribute__((nosda));
extern char *D_L00_001B1EA8;
extern char *D_L00_001B1EA8_1 __attribute__((sda));
extern char *D_L00_001B1E9C;
extern void func_002A05A8(void *object);
extern void func_002A0F48(void *object);
void func_L00_0032CF60(void)
{
    char *scan, *object, *last = 0;
    void (*update)(void *);
    D_L00_001FACE0 = 0;
    D_L00_001B1EA8 = 0;
    for (scan = D_L00_001B1E9C; *(unsigned char *)(scan + 0x20) != 255; scan += 0x100) {
        if ((*(unsigned char *)(scan + 0x20) & 0x80) == 0 &&
            (*(unsigned short *)(scan + 0x34) & 2) == 0) {
            if (last != 0)
                *(char **)(last + 0x28) = scan;
            else
                D_L00_001B1EA8_1 = scan;
            last = scan;
        }
    }
    if (last != 0)
        *(char **)(last + 0x28) = 0;
    object = D_L00_001B1EA8;
    while (object != 0) {
        if (*(signed char *)(object + 0x20) >= 0) {
            if ((*(unsigned short *)(object + 0x34) & 0x40) == 0)
                func_002A05A8(object);
            update = *(void (**)(void *))(object + 0x64);
            if (update != 0)
                update(object);
            if ((*(unsigned short *)(object + 0x34) & 4) == 0)
                func_002A0F48(object);
        }
        object = *(char **)(object + 0x28);
    }
}
