/* func_002A677C, 296 bytes, 28 placements. USA v1.01 retail body traced
 * at 0x002A677C; no C candidate or checker run yet.
 *
 * The function saves the incoming return address in t9 and calls
 * func_002A6640(object + 0x10, stackValue, stackValue + 4). A false result
 * returns immediately through t9. Otherwise the second stack word indexes
 * D_001C1740 in 0x80-byte records; if bit 0 of record +0x50 is clear, it also
 * returns. The first stack float is multiplied by 255 and converted to an
 * integer. MMI operations expand the record's word at +0x40 and the inverted
 * converted alpha into halfwords, multiply the channels, add with saturation,
 * shift, and pack the resulting color into object+0x3C. Finally it combines
 * record words +0x44 and +0x48 with the converted alpha and stores the packed
 * value at object+0x38, then jumps to the shared return label.
 *
 * This is an ordinary function with a dense MMI packed-channel sequence,
 * including pextlb/pextlh, pcpyh, pmulth, paddub, psrlh, ppach and ppacb.
 * A separate compiler probe using standard 16-byte C vector types and lane
 * addition, multiplication and shift lowered to scalar GPR operations; it
 * emitted none of the packed instructions listed above. The compiler survey
 * in docs/contributing/matching-blockers.md establishes that game C emits only por and the
 * SPECIAL2 mult1/madd forms in the MMI space; the packed operations here fall
 * outside that set. This is evidence for handwritten assembly under
 * AGENTS.md, but ASM_FUNC still needs maintainer agreement. Marker remains;
 * no match is claimed. */
