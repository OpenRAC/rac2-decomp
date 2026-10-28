/*
 * No C attempt: this called 192-byte routine contains a COP2/VU0 vector
 * transform, COP2/GPR transfers and an in-function branch with a live
 * COP2-transfer delay slot. The project C compiler cannot emit the observed
 * vector sequence. Keep INCLUDE_ASM pending maintainer agreement for ASM_FUNC.
 */
