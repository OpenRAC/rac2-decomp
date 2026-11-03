/*
 * Opus 5.5 (xhigh), task v2169, 2026-11-03: body below unchanged (944/964 bytes
 * recompiled in its own -G8 unit here). Measured probe (NOT acceptable
 * source): replacing each of the four y conversions with
 *   static __inline__ int hud_scaled(float v)
 *   { float y; if (D_L02_001B3E00 == 1) y = 1.0f;
 *     y = v * D_L02_001B3E04 + 0.5f; return (int)y; }
 * gives 964/964 bytes with retail's whole allocation (object s0, 0x8710 s1,
 * state s2, enabled s3, 0.5/1.0/0.0 in f22/f20/f21, label kept in a2); only
 * the four draw sections still schedule differently. The skipped arm keeps
 * cse's path running (constants stay shared from section 1 to 2) and the
 * test vanishes at flow2. Retail additionally has a sched2 block boundary
 * between each y fix (cvt.w/mfc1) and the 1.0/0.0 argument setup: the
 * f13 conversion is issued first there and 1.0 never fills a chain stall.
 * Retail never loads D_L02_001B3E00, so a real test there must compare live
 * registers. The 002D3D88 if/else form after the y chain (tested on a live
 * register) gives that boundary (968 bytes) but its join label ends cse's
 * path, so 0.5/1.0/0.0/0x8710 are rematerialised per section. Needed: a
 * construct that cse skips (no else) yet survives to sched2.
 */
/*
 * GPT-6.1 Sol high tier, task v0936, 2026-10-29.
 * USA v1.01, pinned game -O2 -G8 -ffunction-sections.
 * Retained check.py: 944/964 bytes, 0 of 1 places match; no linked check.
 * This improves the older 948-byte draft's addressing: SDATA preserves the
 * unknown pointer-table extent while emitting its GP address, and a shared
 * row pointer keeps +4 in the two record loads rather than the base address.
 * The 0xe0 stride and input buttons at +0x1a0 are measured record views.
 * Remaining: entry saved-register assignment, FP constant setup/allocation,
 * text-result lifetime (retail preserves it through a2), and loop-header nop.
 * Typed FP/GPR argument interleaving, pointer-valued labels, float coordinate
 * locals, integer row locals, nested lookup calls, and explicit one/zero
 * locals leave the same 944-byte core. Staging a reused float only changes
 * the FP scratch registers. -frac2-gcse-unsplit-edges has no effect.
 * Next: recover the original UI conversion expression or explain the retail
 * label/constant lifetimes with allocator evidence; do not repeat these ties.
 * All declarations are below. The function needs its own -g8.c unit.
 */
#include "common.h"

/* Draws the contextual selection help and locates the next available entry. */
extern u8 *D_L02_001A904C;
extern float D_L02_001B3E04;
extern int D_L02_001B30C8;
extern u8 D_001395B8[], D_00139568[];
typedef struct { u8 pad[0x1a0]; unsigned int buttons; } HelpInput;
extern HelpInput D_00138180;
typedef struct { u8 pad[4]; u8 available; u8 tail[0xdb]; } HelpEntry;
extern HelpEntry D_L02_00264A70[];
extern u8 *D_L02_001B1190[] SDATA(D_L02_001B1190);
extern void func_L00_0037B7B0(void);
extern char *func_00336D50(u8 *, int);
extern void func_00300A00(char *, int, float, float, float, float, float);
extern unsigned int func_00283D38(unsigned int, unsigned int, float);
extern int func_L02_003F9B70(int);
extern int func_00288D58(void);
extern void func_002FC560(unsigned int, unsigned long long);
extern float D_L02_001B1260 __attribute__((sda));
extern int D_L02_001B1264 __attribute__((sda));
extern int D_L02_001B1268 __attribute__((sda));
extern int D_L02_001B126C __attribute__((sda));
extern int D_L02_001B1270 __attribute__((sda));
extern int D_L02_001B1274 __attribute__((sda));
extern int D_L02_001B1278 __attribute__((sda));
extern unsigned int D_L02_001B127C __attribute__((sda));
extern unsigned int D_L02_001B1280 __attribute__((sda));
extern unsigned int D_L02_001B1288 __attribute__((sda));
extern unsigned int D_L02_001B128C __attribute__((sda));
void func_L02_003FDDE8(u8 *object, int enabled)
{
    u8 *state;
    char *label;
    int phase, i;
    unsigned int color;
    float pulse;
    HelpEntry *r;
    if (D_L02_001A904C == 0) return;
    func_L00_0037B7B0();
    state = *(u8 **)(object + 0x68);
    label = func_00336D50(D_L02_001A904C + 0x8710, 0x49);
    func_00300A00(label, D_L02_001B1280, (float)D_L02_001B1264,
        (float)(int)((float)D_L02_001B1268 * D_L02_001B3E04 + 0.5f), D_L02_001B1260, 1.0f, 0.0f);
    label = func_00336D50(D_L02_001A904C + 0x8710, 0x48);
    func_00300A00(label, D_L02_001B127C, (float)D_L02_001B1264,
        (float)(int)((float)D_L02_001B1268 * D_L02_001B3E04 + 0.5f), D_L02_001B1260, 1.0f, 0.0f);
    phase = D_L02_001B30C8 % 50;
    if (phase >= 25) pulse = 1.0f - (float)(phase - 25) * 0.04f;
    else pulse = (float)phase * 0.04f;
    color = func_00283D38(D_L02_001B127C, D_L02_001B1280, pulse);
    if (enabled) {
        if (*(short *)(state + 0x118) != 0) {
            label = func_00336D50(D_L02_001A904C + 0x8710, 0x4b);
            func_00300A00(label, (D_00138180.buttons & 0x8000) ? D_L02_001B1288 : color,
                (float)D_L02_001B126C, (float)(int)((float)D_L02_001B1270 * D_L02_001B3E04 + 0.5f), D_L02_001B1260, 1.0f, 0.0f);
        }
        for (i = *(short *)(state + 0x118) + 1; i < 14; i++) {
            if (D_001395B8[func_L02_003F9B70(*(int *)(D_L02_001B1190[i] + 8))] == 0) continue;
            if (i >= 12 && !func_00288D58()) continue;
            if (i == 7) {
                r = &D_L02_00264A70[D_00139568[0x1e]];
                if (r->available == 0) continue;
            }
            if (i == 8) {
                r = &D_L02_00264A70[D_00139568[0x2a]];
                if (r->available == 0) continue;
            }
            label = func_00336D50(D_L02_001A904C + 0x8710, 0x4a);
            func_00300A00(label, (D_00138180.buttons & 0x2000) ? D_L02_001B128C : color,
                (float)D_L02_001B1274, (float)(int)((float)D_L02_001B1278 * D_L02_001B3E04 + 0.5f), D_L02_001B1260, 1.0f, 0.0f);
            break;
        }
    }
    func_002FC560(0x47, 0x5360b);
}
