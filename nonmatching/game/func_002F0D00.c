/*
 * No C attempt: the 264-byte retail routine uses $at as a working register
 * and has a trapping `addi` at +0x28. Both are evidence of handwritten
 * assembly. Keep INCLUDE_ASM pending maintainer agreement for ASM_FUNC.
 */
