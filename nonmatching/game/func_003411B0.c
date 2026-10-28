/*
 * Not an independently callable function. The two stores follow a completed
 * return and alignment nop, then fall through into the next function's prologue.
 * No direct code, aligned data-pointer or straight-line address-construction
 * reference reaches this extent in any placement. See docs/LEVELS.md for the
 * retained catalogue-boundary evidence.
 */
