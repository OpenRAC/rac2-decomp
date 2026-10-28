/*
 * Retained manual C reconstruction; not linked or counted.
 * Profile: -O2 -G8 -ffunction-sections (a sibling of src/game/0031F210-g8.c, which needs
 * `#include "common.h"` for qcopy and its declaration changed to func_00326EC0(char *)).
 * Retail: 376 bytes; compiled: 380 bytes.
 * Coverage: us: 0/1 (tools/check.py, 2026-10-28, master 1243c8ea).
 * Residual: the loop. Retail tests `i < 4` first in each iteration (the test is also
 * copied into the latch's `bnel` slot) and increments i after the second call; this C
 * computes the corner arguments before the test and increments early, one word longer;
 * the saved registers are rotated (retail: table in $s0, position in $s3).
 * Measured: the four extents as one Vec4[4] (two arrays cost two more saves); the push
 * vector D_L00_001B27B0 as an incomplete `sda` array keeps retail's per-iteration
 * `lui ; addiu` (an ordinary array is hoisted into $s5, 20 bytes long). The increment
 * moved after the if or a while loop changes nothing.
 * Reopen: a loop form that puts the `i < 4` test at the iteration's head.
 */
