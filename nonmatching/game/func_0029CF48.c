/*
 * Not a callable function. The 12-byte extent follows a completed return and
 * alignment nop, contains a GP-relative store and an unmatched 0x50-byte stack
 * restore, and has no direct or measured data reference in any placement. See
 * docs/LEVELS.md for the retained catalogue-boundary evidence.
 */
