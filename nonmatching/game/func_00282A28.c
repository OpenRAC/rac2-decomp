/* 6 November 2026, round 6: marked ASM_FUNC in src/ (original assembly, pending maintainer review); see the src comment for the evidence. */
/* func_00282A28 - 16 bytes, 28 places (the boot and every level), retail at
   0x00282A28: teq $zero,$zero,0 ; nop ; jr $ra ; nop.
   the body starts with a trap (teq $zero,$zero,0), which no C emits.  Not matched in wave 12 (worker g1): no C source reproduces the body.
   28 October 2026 current-master probe: `__builtin_trap()` is rejected by the
   target compiler (`__builtin_trap not supported by this target`), so it does
   not provide a C spelling for the retail `teq`. */
