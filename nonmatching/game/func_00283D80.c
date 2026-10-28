/*
 * Not expressible in C with the project compiler. The 56-byte called routine
 * uses VU0/COP2 vector operations and uses $at as a working register, including
 * a trapping addi $at,$zero,1 before its return. This is evidence for a
 * handwritten routine; keep INCLUDE_ASM until a maintainer agrees to ASM_FUNC.
 */
