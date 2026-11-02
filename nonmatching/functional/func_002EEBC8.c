/* functional: medium. Near-miss draft of retail size with the same frame: differences are allocation and scheduling, with some block order; paths the captured calls never take are unproven. */
/* GPT-6.1 Sol (high), 29 October 2026: 320/320 bytes, 0/1 places.
 * Default -O2 -G0 -ffunction-sections, current pinned compiler.
 * Carry from orch/main: first difference +0x64, one excess polling-loop nop;
 * branch and subsequent words shift until retry-loop padding rejoins at +0x88.
 * -g ties; -fno-schedule-insns2 and -mno-split-addresses keep the excess nop
 * and worsen allocation. Direct polling-client symbol hoists an address into
 * s0 (332 bytes); sda stops hoisting but keeps the excess nop.
 * Likely loop-padding instruction-count issue; needs independent compiler
 * evidence rather than artificial source barriers. No linked build run.
 */
extern void func_0011CF78(int);
extern int func_0011D450(void *, int, int);
extern int func_0011D810(void *);
extern int func_0011D620(void *, int, int, void *, int, void *, int, void *, void *);
typedef struct {
    int base, size, cd[10], cursor, count, extra;
} StashState;
extern StashState D_001A7240_s __asm__("D_001A7240") __attribute__((sda));
extern int D_L00_00215050[][4];

void func_002EEBC8(void) {
    int reply[4];
    int i;
    func_0011CF78(0);
    for (;;) {
        if (func_0011D450(D_001A7240_s.cd, 0x11, 1) < 0) {
            for (;;) {
            }
        }
        while (func_0011D810(D_001A7240_s.cd) != 0) {
        }
        if (D_001A7240_s.cd[9] != 0) {
            goto bound;
        }
        i = 0xFFFF;
        while (i--) {
        }
    }
bound:
    func_0011D620(D_001A7240_s.cd, 2, 0, 0, 0, reply, 16, 0, 0);
    D_001A7240_s.base = reply[0];
    D_001A7240_s.size = reply[1];
    D_001A7240_s.cursor = reply[0];
    D_001A7240_s.extra = reply[2];
    D_001A7240_s.count = 0;
    for (i = 0; i < 64; i++) {
        D_L00_00215050[i][0] = 0;
        D_L00_00215050[i][1] = 0;
    }
}
