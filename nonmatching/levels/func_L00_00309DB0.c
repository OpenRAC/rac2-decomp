/* 4 November 2026: release qualification changes the boundary conclusion.
 * US and US2 each have 27 copies with the retained orphan sequence after
 * a completed return/delay/padding; no scanned direct, aligned-literal or
 * nearby LUI/low-half reference enters these extents. In every PAL copy,
 * however, the first stack adjustment is the preceding jr's delay slot.
 * PAL level 20 additionally contains an aligned loaded word at 0x0026A2B8
 * equal to the row's 0x00320200 address. Its role as a pointer is unproven;
 * no direct or nearby address-pair reference was found in any PAL copy.
 * Preserve every marker and row. Reopen with the PAL predecessor's real
 * extent and this loaded-word provenance, rather than applying a blanket
 * exclusion from the US-only observation below. No C compile was repeated.
 */
/* Current US catalogue-boundary review, 2026-11-03.
 * 27/27 US placements follow completed return/delay/padding, then two unmatched positive stack restores and orphan v0 moves. No external direct, aligned literal or nearby LUI-address pair reaches the extent.
 * Direct branch/jump scans cover EE text, excluding VU microcode.
 * Aligned loaded-word pointers and nearby LUI+low-half constructions were also inspected.
 * Arbitrary computed indirect entries are outside this scan.
 * A specifically reviewed residue repair; guessed retained caller was unrelated to the actual words.
 * The former guessed/dummy-buffer source is preserved privately and rejected.
 * No C candidate or exact-C credit is claimed for the current extent.
 */
