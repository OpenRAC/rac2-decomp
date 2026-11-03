/* 2 November 2026 retail recheck; this supersedes conflicting historical notes below.
 * Fresh R5900 decode corrects stale screening:700014A9=por zero and7C820010=sq, both supported source methods, not evidence of handwritten MMI. Real leadingCDCDCDCD is after completed previous return, and jals28575C,2CA010,2FC930 reach126470(+4). Body builds GS packet using integer bitfields and ends with sync. Reopen on reviewed4-byte entry correction and faithful SDK sync/bitfield source contract; do not classify ASM_FUNC from por/sq.
 * No matching credit, generator change or ASM_FUNC classification.
 */
/* Not C, and not a function row: not attempted.
 *
 * src/core/001261F0.c line 54. The 324-byte extent opens on the linker fill
 * word 0xCDCDCDCD (rabbitizer prints it `pref 0x0D,-0x3233($t6)`); a real
 * prologue `addiu $sp,$sp,-0x10` starts at 0x126470, which symbol_addrs
 * already carries as its own entry (`func_00126470 = 0x00126470`). The body
 * from there is hand-written MMI: `sll`/`sra` pairs on every halfword
 * argument, `dsll32`/`dsra32`, and opcode 0x1C/0x1F words that rabbitizer
 * prints as `.word # INVALID` (0x700014A9, 0x7C820010).
 *
 * What would unblock it: tools/levels.py splitting the 4-byte fill off, so
 * the row becomes func_00126470 - and then ASM_FUNC, since the body is
 * assembly. Spending C budget here cannot pay.
 */
