/* functional: high. Same reads, writes and calls as retail (the D_L02_001A9048 read is the same word whether retail takes it by $gp or lui). SAME on 2 calls (level 16 copy); the unrun block (level 16 trigger: sets D_001A7A6B, func_002E5E58(1,0,0), func_002B0A18(0x1233,-1), D_L02_001A903C = 1) was read against retail. */
/* func_L02_00389F70 (152 bytes): a one-shot trigger: on first call marks itself set up (byte 0x20 = 1, 0x30 = 0xFF); when the level counter D_L02_001A9048 reaches 14 in level 16 and D_001A7A6B is clear, fires it once. */
/* GPT-6.1 Sol high, task v0862, 29 October 2026.
 * USA v1.01: 152/152 bytes, 0/7 placements; five instructions differ.
 * Reproduce in a separate unit with -O2 -G0 -ffunction-sections
 * -mno-split-addresses. The single SDA declaration of the level counter gives
 * the measured absolute load and speculative GP load of the same word.
 * This fixes the earlier frame-argument copy and missing branch-slot nop.
 * Remaining: the initial 1/255 loads are reversed, and a1 = 0 is scheduled
 * after the flag-store macro rather than before it. A typed state view and
 * argument-expression spelling tie. Disabling schedule-insns2 ties; disabling
 * schedule-insns changes the initial byte-store registers without matching.
 * No volatile accesses or altered helper interfaces were used.
 */

typedef unsigned char RouteU8;

extern int D_L02_001A9048 __attribute__((sda));
extern int D_001A79F0 __attribute__((sda));
extern RouteU8 D_001A7A6B __attribute__((nosda));
extern int D_L02_001A903C __attribute__((sda));

extern void func_002E5E58(int, int, int);
extern void func_002B0A18(int, int);

struct TriggerState { RouteU8 pad[0x20]; RouteU8 initialized; RouteU8 pad21[15]; RouteU8 state; };

void func_L02_00389F70(struct TriggerState *self) {
    int v;

    if (self->initialized == 0) {
        self->state = 0xFF;
        self->initialized = 1;
        v = D_L02_001A9048;
    } else {
        v = D_L02_001A9048;
    }
    if (v < 14)
        return;
    if (D_001A79F0 != 16)
        return;
    if (D_001A7A6B != 0)
        return;
    D_001A7A6B = 1;
    func_002E5E58(1, 0, 0);
    func_002B0A18(0x1233, -1);
    D_L02_001A903C = 1;
}
