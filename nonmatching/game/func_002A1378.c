/*
 * No C attempt: this 280-byte routine uses $at as a working register, several
 * trapping `addi` instructions and COP2/VU0 operations including qmtc2/qmfc2,
 * vector arithmetic and vsqrt. Keep INCLUDE_ASM pending maintainer agreement
 * for ASM_FUNC.
 */
