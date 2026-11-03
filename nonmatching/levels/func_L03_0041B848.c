/* Current US catalogue-boundary review, 2026-11-03.
 * All5 US placements have data pointers to+8, the actual jr ra/nop stub. The+0x190 stackrestore/nop prefix follows the previous completed return/delay. The old dummy0x190 local buffer is not faithful C.
 * Direct branch/jump scans cover EE text, excluding VU microcode.
 * Aligned loaded-word pointers and nearby LUI+low-half constructions were also inspected.
 * Arbitrary computed indirect entries are outside this scan.
 * Repair entry by8 with original end preserved, then match a real empty void stub; no catalogue change in this slot.
 * The former guessed/dummy-buffer source is preserved privately and rejected.
 * No C candidate or exact-C credit is claimed for the current extent.
 */
