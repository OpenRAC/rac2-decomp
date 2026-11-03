/*
 * No C attempt: this 80-byte routine is present in the boot and 27 levels.
 * Its USA v1.01 body loads three vector rows with lqc2, performs VU0 vector
 * additions/subtractions and writes four output rows: the identity row at
 * +0x30 as well as results at +0, +0x10 and +0x20. A fresh 2 November 2026
 * R5900 read confirms that the output buffer must cover 64 bytes, despite
 * the 48-byte input. It places the final `sqc2 $vf6,0x20($a0)` in the live
 * `jr $ra` delay slot. All 27 level
 * placements contain VU0 store instructions. The compiler does not emit
 * COP2/VU0 operations from C. This supports handwritten-assembly review,
 * but keep INCLUDE_ASM until a maintainer agrees to ASM_FUNC.
 */
