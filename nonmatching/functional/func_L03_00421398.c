/* functional: medium. Near-miss draft, not byte-compared in the latest sweep: paths the captured calls never take are unproven. */
/* sol-high worker, USA v1.01, current upstream toolchain.
 * Retained check.py result: 1424 bytes / 1420 retail, 0 of 1 places match.
 * Compile as a -g8.c unit: -O2 -G8 -ffunction-sections.
 * The frame (0x60), saved registers and the complete four-state behavior are
 * reconstructed. Explicit flag/high-nibble/low-nibble arms retain both counter
 * tests instead of merging their AND operations. The initial 16-record walk
 * still hoists table+0x148 rather than the retail table base, and branch setup
 * and register allocation differ. The subtitle-key store also folds its base
 * address into the relocation, omitting retail's separate base addiu.
 * A shared record pointer retains field offsets but reuses outer arithmetic
 * that retail repeats (1400/1384-byte variants). Incomplete-array sda,
 * -mno-split-addresses, -fno-gcse, -fno-rerun-loop-opt and
 * -fno-strength-reduce did not solve the family. A volatile count experiment
 * changed scheduling without fixing addressing; no volatile is retained.
 * Reopen with evidence for the actual table expression/address lifetimes.
 * All required declarations are below. No linked build was run; no match.
 */
#include "common.h"
extern void func_0029F338(void *);
extern void func_002A7750(void *, int, int);
extern u8 *func_002A9640(void *, int, int);
extern int func_002B3868(void *);
extern int func_00282948(void *);
extern void func_L00_00324F18(void *, void *, float, float, float);
extern void *func_0032C700(void *, int, int, int, int, int, int, int, float, float, int, int, int, int);
extern void func_L03_00421930(void);
extern void func_L00_0032A530(void *, void *, void *, void *, int, int, int, int, int, int, void *);
typedef struct { u8 pad[0x120]; int entries[10]; int count; int active; } EntryGroup;
extern u8 D_L03_00259A30[];
extern u8 D_L03_0021EA30[];
extern u8 D_0019B4A8[];
extern int D_001A79F0 __attribute__((sda));
extern u8 D_0018C958[];
extern int D_L03_001B2A38;
extern u8 *D_L03_001B2A1C;
extern u16 *D_L03_001FB5A0[];
extern float D_L03_001B1DA0[2] __attribute__((sda)), D_L03_001B1DA8[2] __attribute__((sda)), D_L03_001B1DB0[2] __attribute__((sda));
void func_L03_00421398(u8 *obj)
{
    u8 *state = *(u8 **)(obj + 0x68);
    u8 pos[16] __attribute__((aligned(16)));
    u8 *hit, *other;
    u16 *p;
    int i, j, index, bits;
    u8 *counter;
    if (!state) { func_0029F338(obj); return; }
    switch (obj[0x20]) {
    case 0:
        { int group;
        for (group = 0; group < 16; group++) {
            for (j = 0; j < ((EntryGroup *)(D_L03_00259A30 + group * 0x150))->count; j++)
                if (((EntryGroup *)(D_L03_00259A30 + group * 0x150))->entries[j])
                    ((EntryGroup *)(D_L03_00259A30 + group * 0x150))->entries[j] = 0;
            ((EntryGroup *)(D_L03_00259A30 + group * 0x150))->active = 0;
        }}
        index = *(s16 *)(obj + 0xB2);
        if (D_L03_0021EA30[index + 0x464]) {
            func_0029F338(obj);
        } else {
            bits = D_0019B4A8[(index >> 1) + (D_001A79F0 << 10)];
            if (index & 1) {
                if ((bits >> 4) & 7) func_0029F338(obj);
                else func_002A7750(obj, 1, -1);
            } else {
                if (bits & 7) func_0029F338(obj);
                else func_002A7750(obj, 1, -1);
            }
        }
        break;
    case 1:
        hit = func_002A9640(obj, 0x10000, 0);
        if (hit && (other = *(u8 **)(hit + 0x20)) && *(s16 *)(other + 0xAA) == 0xCFC &&
            *(float *)(obj + 0x18) <= *(float *)(other + 0x18) + 0.5f) {
            for (p = D_L03_001FB5A0[obj[0x21]];
                 obj[0x21] != 0xFF && obj[0x21] <= D_L03_001B2A38 && p != 0 &&
                 ((p != 0 && (s16)p[-1] >= 0) || p == D_L03_001FB5A0[obj[0x21]]); p++) {
                other = D_L03_001B2A1C + ((*p & 0x7FFF) << 8);
                if (!other) break;
                func_002A7750(other, 2, -1);
            }
        }
        obj[0xA8] = 0xFF;
        break;
    case 2:
        if (func_002B3868(obj)) {
            *(int *)(state + 4) = 230;
            for (i = -1; i < 2; i++) {
                func_L00_00324F18(obj, pos, (float)(i << 3), -6.0f, 5.0f);
                func_0032C700(pos, 0, 5, 5, 5, 5, 5, 0, .75f, 20.0f, 0, 0, 0, 0);
            }
            *(int *)(state + 4) = 10;
        } else if (func_00282948(state + 4)) {
            for (i = -1; i < 2; i++) {
                func_L00_00324F18(obj, pos, (float)(i << 3), -6.0f, 15.0f);
                func_0032C700(pos, 0, 5, 5, 5, 5, 5, 0, .75f, 20.0f, 0, 0, 0, 0);
            }
            *(int *)(state + 4) = 10;
            func_002A7750(obj, 3, -1);
        }
        break;
    case 3:
        if (!func_00282948(state + 4)) break;
        for (i = -1; i < 2; i++) {
            func_L00_00324F18(obj, pos, (float)(i << 3), -6.0f, 25.0f);
            func_0032C700(pos, 0, 5, 5, 5, 5, 5, 0, .75f, 20.0f, 0, 0, i == 0, 0);
        }
        if (*(u16 *)(obj + 0xB2) & 1) {
            counter = D_0019B4A8 + ((*(s16 *)(obj + 0xB2) >> 1) + (D_001A79F0 << 10));
            if (((*counter >> 4) & 7) != 7) *counter += 16;
        } else {
            counter = D_0019B4A8 + ((*(s16 *)(obj + 0xB2) >> 1) + (D_001A79F0 << 10));
            if ((*counter & 7) != 7) *counter += 1;
        }
        *(u16 *)(D_0018C958 + 0x2D0) = 0xFFFF;
        if (*(int *)state)
            func_L00_0032A530(obj, D_L03_001B1DB0, D_L03_001B1DA8, D_L03_001B1DA0,
                              0xFFFF, 0, -1, 1, 0xFFFF, 0xFF, func_L03_00421930);
        else
            func_L00_0032A530(obj, D_L03_001B1DB0, D_L03_001B1DA8, D_L03_001B1DA0,
                              0xFFFF, 0, -1, 1, 0xFFFF, 0xFF, 0);
        func_0029F338(obj);
        break;
    }
    return;

}
