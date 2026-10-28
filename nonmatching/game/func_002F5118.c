/*
 * No C attempt: the 264-byte retail routine uses $at as a working register
 * in shifts/addition at +0x28/+0x30 and a trapping `addi` at +0x20. These are
 * handwritten-assembly indicators. Keep INCLUDE_ASM pending maintainer
 * agreement for ASM_FUNC.
 */
