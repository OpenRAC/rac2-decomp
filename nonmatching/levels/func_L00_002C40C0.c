/* 3 November 2026; no linked match.
 * Actual scorer L00_002AE388 writes only one 32-bit blocked flag and has
 * two GPR/four FP inputs. Its canonical bank-preserving interleaving and
 * the real scalar output are retained below: 524/544 bytes, 0/25 US,
 * frame 0x80 versus retail 0x90. Capturing the complete hero owner gives
 * 508/544, also frame 0x80, and is not retained. Two grounded checks.
 * The diagnosed loop-hoist threshold remains; no diagnostic call-used
 * register flags, fake storage or altered register banks were used.
 * The older diagnostic comparison below is historical, not qualification.
 */
/* Claude Opus 5.5 (opus-1), v1321: USA v1.01 524/544 bytes, 0/25 places under the pinned
 * toolchain (-O2 -G8 -ffunction-sections, approved qcopy helper; sibling -g8 unit).
 * This plain form is retail's source shape: compiled with -fcall-used-hi1 -fcall-used-lo1
 * -fcall-used-accum1 (diagnostic only, not a permitted profile) it matches 25 of 25 places.
 * What differs: loop.c's movable threshold is (1 + n_non_fixed_regs) with a call in the loop;
 * compiler patch 0055 keeps the R5900 hi1/lo1/accum1 registers fixed, which lowers it from 64
 * to 61. With 61, pass 1 (63 insns) hoists nothing and pass 2 (58) hoists only 0x99D and the
 * mode address; retail (64) hoists 0x99D in pass 1, then the &D_00189E20 copy (s7), 1 and 0x1D
 * in pass 2, giving the 0x90 frame with s4-s7. No natural wording removes the two RTL insns
 * a threshold of 61 would need (class/flag/byte tests and call temporaries are minimal).
 * Older alternative (544/544, two instructions differ): declare `int *modes =
 * &D_00189E20.mode;` before the do-while and test `*modes`; it forms s7 = root+0x2294.
 * Declarations follow. No linked match claimed. */
#include "include_asm.h"
#include "common.h"
typedef int Vector __attribute__((mode(TI)));
typedef struct {
    unsigned char pad0[0x80]; float position[4];
    unsigned char pad1[8]; float heading;
    unsigned char pad2[0x64C - 0x9C]; float alternate_heading;
    unsigned char pad3[0xAA4 - 0x650]; void *selected_aa4; int ready_aa8;
    unsigned char pad4[12]; int value_ab8;
    unsigned char pad5[4]; int value_ac0; float score_ac4;
    unsigned char pad6[8]; void *selected_ad0;
    unsigned char pad7[4]; float score_ad8;
    unsigned char pad8[2]; short ready_ade;
    unsigned char pad9[0xB10 - 0xAE0]; void *selected_b10; int ready_b14;
    unsigned char pad10[0x2294 - 0xB18]; int mode, field_2298, state;
} HeroSelectionState;
extern HeroSelectionState D_00189E20;

extern unsigned char *D_L00_001B1EA8 __attribute__((sda));
extern int func_002B38B8(void *);
extern float func_L00_002AE388(char *, float, float, int *, float, float);
extern float func_00282E80(void *, void *);
extern int func_002761F8(void *, void *, int, void *, int);

int func_L00_002C40C0(void)
{
    unsigned char *node, *best;
    float score, closest;
    float first[4], second[4];
    int blocked;
    if (D_00189E20.state == 0x21) return D_00189E20.ready_b14;
    best = 0;
    closest = 100000000.0f;
    D_00189E20.ready_b14 = 0;
    node = D_L00_001B1EA8;
    if (node) {
        do {
            float horizontal, vertical, heading;
            if (*(short *)(node + 0xAA) != 0x99D) continue;
            if (*(unsigned short *)(node + 0x34) & 1) continue;
            if (func_002B38B8(node)) continue;
            horizontal = 0.5235988497734069824f;
            vertical = -1.0f;
            if (D_00189E20.mode == 1 || D_00189E20.mode == 0x1D)
                horizontal = vertical = 0.087266474962234497f;
            heading = D_00189E20.heading;
            if (D_00189E20.state == 0xF) heading = D_00189E20.alternate_heading;
            score = func_L00_002AE388((char *)node, heading, 30.0f, &blocked, horizontal, vertical);
            if (blocked != 0) continue;
            if (func_00282E80(D_00189E20.position, node + 0x10) < 4.0f) continue;
            if ((unsigned char)node[0x31] == 0) score += 10.0f;
            if (score < closest) { closest = score; best = node; }
        } while ((node = *(unsigned char **)(node + 0x28)) != 0);
    }
    if (best) {
        D_00189E20.selected_b10 = best;
        qcopy(first, D_00189E20.position);
        first[2] += 0.5f;
        qcopy(second, best + 0x10);
        if (!func_002761F8(first, second, 2, 0, 0)) D_00189E20.ready_b14 = 1;
    }
    return D_00189E20.ready_b14;
}
