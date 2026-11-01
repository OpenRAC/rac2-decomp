/* functional: medium. Near-miss draft, not byte-compared in the latest sweep: paths the captured calls never take are unproven. */
/* from src/game/0029BCC8.c: 32-byte near miss; the candidate is 36 bytes and
   two instructions differ.  Retail materialises the register block in $at
   (lui $at,0x1000 ; ori $at,$at,0xD400) and keeps the constant 0x100 in $v0
   (ori $v0,$zero,0x100) until the last store, which sits in the jr $ra delay
   slot; this cc1 builds the address in $v0 (lui ; ori), materialises 0x100 as
   addiu $v1,$zero,0x100 before the address, and leaves a nop in the delay
   slot. The address is the PS2 SPR block (0x1000D400) and is the same in
   every program. 28 October 2026 current-master checker recheck of this
   volatile C form: 36 bytes, 0/28; the mismatch remains the base register,
   constant materialisation order, and final-store delay-slot placement.

   A direct absolute-address form for each SPR store measures 60 bytes, 0/28.
   It materializes a separate address for each store rather than sharing the
   base, so it is worse than the local-base form.

   29 October 2026 profile probes: `-ffixed-v0` moves the shared address from
   `$v0` to `$v1`, not retail `$at`, and still emits 36 bytes (0/28); it also
   puts the constant setup before the third store and leaves a `nop` after
   `jr`. Adding `-fno-schedule-insns` keeps the stores in source order but
   remains 36 bytes (0/28), uses `$v1`, materializes 0x100 with `addiu`, and
   leaves the final store before `jr`. Neither profile reproduces retail's
   base, constant instruction or delay-slot store. A 29 October typed volatile
   register-block probe with fields at offsets 0, 0x10, 0x20 and 0x80 also compiles
   to 36 bytes, 0/28. It emits the right three initial stores but keeps the base
   in $v0, uses addiu for 0x100, and leaves the final store before `jr`.

   A 29 October `-fno-schedule-insns2` probe remains 36/32 bytes and 0/28.
   The base moves to `$at`, matching retail, but the compiler emits `addiu`
   for 0x100 before the last input store, writes the final word before `jr`,
   and adds a trailing `nop`. Disabling the second scheduling pass does not
   recover the 32-byte retail sequence. A `-ffixed-v1` profile probe also
   remains 36/32 bytes and 0/28: reserving `$v1` leaves the shared base in
   `$v0`, rather than moving it to `$at`. */
void func_0029CF58(unsigned int a0, unsigned int a1, unsigned int a2) {
    volatile unsigned int *p = (volatile unsigned int *)0x1000D400;
    p[0x20] = a2;
    p[0x8] = a1;
    p[0x4] = a0;
    p[0] = 0x100u;
}
