/* Claude Opus 5.5 (xhigh), 2 November 2026: retained, unlinked near miss.
 * USA v1.01, -O2 -G8 -ffunction-sections (compile as an L23_0041D398-g8.c
 * unit): 1432/1432 bytes, 0/1 places; first real difference +0x380, 99 of
 * 358 cdiff rows (the sol-high draft differed from +0x50). No linked build.
 *
 * Solved here: the opening flag branches. Each arm of the flag test has its
 * own func_002A6C58/func_L23_0041D9B0 kill sequence and return (no goto):
 * jump2 cross-jumps the identical call tails and reload_cse deletes the
 * redundant a0 copy on the true arm, giving retail's beqz/daddu a1 and b/nop
 * shapes. The second, re-read flag test is real (volatile byte, two lbu).
 *
 * Remaining, all after +0x37C: post-transfer constant order (retail sets 10
 * before 1); both exits `timer & 15` / `timer & 31` use bnez where retail has
 * bnel with the annulled ld s0; both effect phases differ in schedule (retail:
 * jal 77E0 [a0=5]; daddu s2,v0; addiu s1,s1,0x358; sll v0,s2,2; ...; addu
 * s1,s1,v0; lw s0,0(s1); jal rand [addiu s0,0xD0]; ... jal rand [andi
 * s2,s2,1]) and in stack-argument store order. Index and cursor are
 * call-crossing, so haifa sched1 gives their in-place updates no anti-dep on
 * the last call and hoists them.
 * Tried: per-phase block-scoped `int index, parity; char *old, **base;` with
 * `base = cursor.state->parts; cursor.parts = base + index; parity = index
 * & 1` gives exactly retail's effect-phase order (a0=5 slot, andi in the
 * second rand slot, tied to index), but local-alloc then takes s0/s1 for
 * old/index, so the cursor moves to s2 and s1/s2 swap function-wide (101
 * rows). Retail's s1 cursor / s2 index implies index is a global pseudo;
 * reopen by finding a global-index shape that keeps that schedule.
 * All required declarations follow; the original INCLUDE_ASM stays in src/.
 */
#include "common.h"
typedef int Quad __attribute__((mode(TI)));
/* Two five-part windows share this ten-pointer table. */
typedef struct { u8 prefix[0x358]; char *parts[10]; } PartState;
extern char *D_L23_001B1484 __attribute__((sda));
extern int D_L23_001B1468 __attribute__((sda));
extern int D_L23_001B1434 __attribute__((sda));
extern char *D_L23_001B13D0 __attribute__((sda));
extern float D_L23_001B16D0 __attribute__((sda));
extern int D_L23_001B3720;
/* Retail reads this byte again at 0041D43C on the entry-cleanup path. */
extern volatile unsigned char D_001A7AFD;
extern int func_002F5D10(void);
extern void func_002A6C58(char *, int, int);
extern void func_L23_0041D9B0(void);
extern void func_L00_003294F0(unsigned char *, int);
extern void func_0029F338(void *);
extern void *func_0032C700(void *, int, int, int, int, int, int, int, float, float, int, int, int, void *);
extern int func_002E5CF8(int, int, char *);
extern void func_0029FC20(char *, int, char *);
extern void func_00282D30(char *, char *, float);
extern float func_002A7878(float, float);
extern void func_00282CC0(char *, char *, char *);
extern char *func_00273730(char *, int, int, int, char *, char *, float *, int, float, float);
extern void func_00310C88(u8 *);
extern int func_002A77E0(int);

/* Move through the encounter's damage phases, detaching pieces and spawning debris. */
void func_L23_0041D398(char *object) {
    struct { Quad velocity, matrix[4], random; } local;
    /* The encounter state becomes a cursor into its part table in each phase. */
    union { PartState *state; char **parts; } cursor;
    char *old, *particle;
    int index;
    unsigned short timer;
    float scale;
    cursor.state = *(PartState **)(D_L23_001B1484 + 0x68);
    if (D_001A7AFD) {
        if (*(unsigned short *)(object + 0x96) > D_L23_001B1468 + 60) {
            func_002A6C58(object, 0, 3);
            func_L23_0041D9B0();
            return;
        }
    } else {
        if (*(unsigned short *)(object + 0x96) > D_L23_001B1468 + 200 && !func_002F5D10()) {
            func_002A6C58(object, 0, 3);
            func_L23_0041D9B0();
            return;
        }
        if (!D_001A7AFD && *(unsigned short *)(object + 0x96) > D_L23_001B1468 + 60) {
            char *entryState;
            if (!D_L23_001B13D0) return;
            entryState = *(char **)(D_L23_001B13D0 + 0x68);
            entryState[13] = 1;
            entryState[8] = 0;
            func_L00_003294F0((unsigned char *)D_L23_001B13D0, 1);
            D_L23_001B13D0 = 0;
            return;
        }
    }
    if (D_L23_001B1434) {
        int i;
        cursor.parts = cursor.state->parts + 5;
        for (i = 5; i < 10; i++, cursor.parts++) {
            if (!D_L23_001B3720) {
                func_0029F338(*cursor.parts);
                *cursor.parts = 0;
                *(unsigned short *)(object + 0x34) |= 0x41;
                func_0032C700(object + 16, 1, 135, 120, 120, 115, 125, 1, 6.5f, 20.0f, 1, 1, 1, 0);
                func_002E5CF8(12, 0, object);
            } else if (*cursor.parts) {
                int debrisIndex = 10 - D_L23_001B3720;
                func_0029FC20(object, i - 4, (char *)local.matrix);
                func_00282D30((char *)&local.velocity, (char *)&local.matrix[1], D_L23_001B16D0);
                scale = func_002A7878(0.0f, D_L23_001B16D0 * 0.5f);
                func_00282D30((char *)&local.random, object + 0xE0, scale);
                func_00282CC0((char *)&local.velocity, (char *)&local.velocity, (char *)&local.random);
                {
                    char *oldPart = *cursor.parts;
                    particle = func_00273730(oldPart, 1, *(short *)(oldPart + 0xAA), debrisIndex, oldPart + 16, oldPart + 0xF0, (float *)&local.velocity, 255, 140.0f, 25.0f);
                    if (particle) *(void (**)(u8 *))(particle + 0x64) = func_00310C88;
                }
            }
        }
        D_L23_001B3720--;
        return;
    }
    timer = *(unsigned short *)(object + 0x96);
    if ((D_L23_001B1468 << 1) / 3 < timer) {
        int i;
        cursor.parts = cursor.state->parts;
        func_0032C700(object + 16, 1, 45, 30, 40, 25, 85, 1, 4.5f, 20.0f, 1, 1, 1, 0);
        func_002E5CF8(11, 0, object);
        for (i = 4; i >= 0; i--, cursor.parts++) {
            char *replacement = cursor.parts[5];
            if (replacement) {
                char *old = *cursor.parts;
                if (!old) continue;
                qcopy(replacement + 0xC0, old + 0xC0);
                qcopy(replacement + 0xD0, old + 0xD0);
                qcopy(replacement + 0xE0, old + 0xE0);
                qcopy(replacement + 0x10, old + 0x10);
                *(unsigned short *)(replacement + 0x34) &= 0xFFF9;
                *(unsigned short *)(cursor.parts[5] + 0x34) |= 0x4000;
                *(unsigned short *)(cursor.parts[5] + 0x34) &= 0xFFBE;
                func_0029F338(*cursor.parts);
                *cursor.parts = 0;
            }
        }
        D_L23_001B1434 = 1;
        D_L23_001B3720 = 10;
        return;
    }
    if (D_L23_001B1468 / 3 < timer) {
        if (timer & 15) return;
        index = func_002A77E0(5);
        cursor.parts = cursor.state->parts;
        cursor.parts += index;
        old = *cursor.parts;
        scale = func_002A7878(4.0f, 12.0f);
        old += 0xD0;
        func_00282D30((char *)&local.velocity, old, scale);
        func_00282CC0((char *)&local.velocity, (char *)&local.velocity, *cursor.parts + 16);
        scale = func_002A7878(2.3f, 3.7f);
        index &= 1;
        func_0032C700(&local.velocity, index, 20, 10, 14, 15, 25, 0, scale, 20.0f, index, 0, 0, 0);
        func_002E5CF8(func_002A77E0(3) + 13, 0, object);
        return;
    }
    if (timer & 31) return;
    index = func_002A77E0(5);
    cursor.parts = cursor.state->parts;
    cursor.parts += index;
    old = *cursor.parts;
    scale = func_002A7878(4.0f, 12.0f);
    old += 0xD0;
    func_00282D30((char *)&local.velocity, old, scale);
    func_00282CC0((char *)&local.velocity, (char *)&local.velocity, *cursor.parts + 16);
    scale = func_002A7878(2.3f, 3.7f);
    index &= 1;
    func_0032C700(&local.velocity, index, 20, 10, 14, 15, 25, 0, scale, 20.0f, index, 0, 0, 0);
    func_002E5CF8(func_002A77E0(3) + 13, 0, object);
}
