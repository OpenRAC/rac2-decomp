/* Current US catalogue-boundary review, 2026-11-03.
 * 27/27 US placements follow completed return/delay/padding, then two unmatched positive stack restores and orphan v0 moves. No external direct, aligned literal or nearby LUI-address pair reaches the extent.
 * Direct branch/jump scans cover EE text, excluding VU microcode.
 * Aligned loaded-word pointers and nearby LUI+low-half constructions were also inspected.
 * Arbitrary computed indirect entries are outside this scan.
 * A specifically reviewed residue repair; guessed retained caller was unrelated to the actual words.
 * The former guessed/dummy-buffer source is preserved privately and rejected.
 * No C candidate or exact-C credit is claimed for the current extent.
 */
