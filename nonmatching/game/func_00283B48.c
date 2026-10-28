/*
 * No C attempt: this called 80-byte routine performs VU0/COP2 vector math
 * with vsubx, vmulaw and vmaddx, plus lqc2/sqc2 transfers. The project C
 * compiler cannot emit the routine. Keep INCLUDE_ASM pending maintainer
 * agreement to classify it as ASM_FUNC.
 */
