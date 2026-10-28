/*
 * No C attempt: this called 96-byte routine uses VU0/COP2 vector operations,
 * including vdiv/vwaitq and COP2 register transfers. The project C compiler
 * cannot emit the observed routine. Keep INCLUDE_ASM pending maintainer
 * agreement to classify it as ASM_FUNC.
 */
