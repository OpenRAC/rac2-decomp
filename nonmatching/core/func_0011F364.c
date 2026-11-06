/* 6 November 2026: entry corrected to 0x0011F380 (608 bytes, fill skipped) and marked ASM_FUNC in src/ (original assembly: CP0, eret, $at working register). */
/* Retail classification, 2 November 2026; no C candidate or match.
 *
 * USA v1.01's 636-byte catalogue extent begins with seven 0xCDCDCDCD
 * linker-fill words (28 bytes). The code at 0x0011F380 saves the complete
 * EE general-register context through k0, including the assembler temporary, both
 * HI/LO banks and the shift-amount register. It reads and writes CP0 state,
 * uses sync.p and eret, and restores the context on a separate entry path.
 * The later callback/trap fragment also uses the assembler temporary and
 * establishes its own stack. This is privileged exception-handler assembly,
 * not a C function beginning at 0x0011F364.
 *
 * Read with the existing read_boot.py R5900 decoder through the permanent
 * workspace launcher in USA v1.01, PAL and USA v2.00. All three have the
 * 28-byte fill prefix, resolving the conflicting historical counts. Keep the catalogue row and
 * INCLUDE_ASM marker pending maintainer review of its entry boundaries and
 * handwritten classification; neither a C match nor ASM_FUNC credit is claimed.
 */
