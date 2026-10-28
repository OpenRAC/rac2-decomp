/*
 * No C attempt: the 288-byte retail routine combines MMI pext/pmin/pmax
 * instructions, COP2/VU0 transfers and vector operations, working-register
 * use of $at, and multiple trapping `addi` instructions. Keep INCLUDE_ASM
 * pending maintainer agreement for ASM_FUNC.
 */
