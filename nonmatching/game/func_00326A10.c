/* 6 November 2026: unchanged. A named `float x = 454.0f;` gives retail's rematerialized
 * 454.0 (no $f25 save) but cse folds x, so the frame is 0x90 and 436/444 bytes; the
 * ghost $s0 save needs a GPR-class pseudo (regclass gives the 454.0 pseudo FP_REGS).
 * Separate label/int y statements change nothing. */
/* 4 November 2026 source-contract/lifetime trials; retained, not linked.
 * Three actual call/source trials remain unmatched: FP-first bank ordering gives 460/444 bytes;
 * interleaved bank ordering and real rounded-coordinate groups give 444/444, 0/1 USA placements,
 * first +0x0. Integer/FP bank counts, widths and order are preserved. Neither restores the unused
 * s0 save or the two x rematerializations. The older best C below is retained; no fresh result is
 * claimed for the three timer siblings.
 */
/* 2026-11-03 w02 source-contract review (USA v1.01 only).
 * Profile: -O2 -G8 -ffunction-sections.
 * Current check.py: 444/444 bytes, 0/1 places, first mismatch +0x0.
 * Corrected func_002ED578 to its actual integer return. Extra retail s0 save, rematerialized 454.0 and FP allocation remain unresolved.
 * Reopen: Independent source evidence for the saved-but-unused register and coordinate lifetime.
 * No linked match or cross-release qualification is claimed. Earlier notes follow.
 */
/*
 * Retained manual C reconstruction; not linked or counted.
 * Profile: -O2 -G8 -ffunction-sections, as its own unit src/game/00326A10-g8.c
 * (the flag at 0x1B00FC is read through $gp; take the marker out of 0031F210.c).
 * Retail: 444 bytes; compiled: 444 bytes.
 * Coverage: us: 0/1 (tools/check.py, 28 October 2026, master 85614b41).
 *
 * Draws the HUD timer: two labels from the text table, then the time split into three
 * fields, formatted and drawn centred, scaled by the HUD scale at 0x1B23A4.
 *
 * Blocked on "A register saved and never used" (docs/MATCHING-BLOCKERS.md): retail
 * saves $s0 and never uses it (frame 0xA0, $s1 holds 0x8710). Here the frame is 0x90
 * and the constant gets $s0. The second difference is the 454.0 x position: retail
 * loads it into $f12 before each call, cc1 keeps it in a sixth callee-saved float
 * register. The table pointer at 0x1A8CFC, the time at 0x1B27C0 and the scale are
 * absolute assembler macro accesses (incomplete sda arrays), as retail reloads them.
 */

#include "common.h"

extern int D_001B00FC __attribute__((sda));
extern char *D_001A8CFC[] __attribute__((sda));
/* The HUD scale, read through absolute assembler macro accesses. */
extern float D_001B23A4[] __attribute__((sda));
extern int D_001B27C0[] __attribute__((sda));
extern char D_001B0110[];

extern int func_00336D50(int, int);
extern void func_00300A00(int, int, float, float, float, float, float);
extern int func_002ED578(int, int *, int *, int *);
extern int func_00115DA8(char *, const char *, ...);
extern int func_00283CF0(float);
extern void func_0027F5B8(int, int, unsigned long long, unsigned char *, int);

int func_00326A10(void)
{
    char text[64];
    int hours;
    int minutes;
    int seconds;

    if (D_001B00FC != 0) {
        func_00300A00(func_00336D50((int)(D_001A8CFC[0] + 0x8710), 0xC1), 0x60442D00, 454.0f,
                      (float)(int)(D_001B23A4[0] * 380.0f + 0.5f), -0.5f, 1.0f, 0.0f);
        func_00300A00(func_00336D50((int)(D_001A8CFC[0] + 0x8710), 0xC2), 0x55F0C070, 454.0f,
                      (float)(int)(D_001B23A4[0] * 380.0f + 0.5f), -0.5f, 1.0f, 0.0f);
        func_002ED578(D_001B27C0[0], &hours, &minutes, &seconds);
        func_00115DA8(text, D_001B0110, hours, minutes, seconds);
        func_0027F5B8(func_00283CF0(405.0f), (int)(D_001B23A4[0] * 372.0f + 0.5f),
                      0x80808080, (unsigned char *)text, 0x80);
    }
    return 1;
}
