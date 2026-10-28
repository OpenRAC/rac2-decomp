/*
 * No C attempt: this called 152-byte routine reads a COP2 register with
 * qmfc2.ni and contains multiple trapping addi/add operations annotated as
 * handwritten in retail. The project C compiler cannot emit the sequence.
 * Keep INCLUDE_ASM pending maintainer agreement for ASM_FUNC.
 */
