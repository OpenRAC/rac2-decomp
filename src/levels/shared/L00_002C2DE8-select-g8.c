/* func_L00_002C40C0 (544 bytes, 25 places), in its own -G8 unit: the list head
 * D_L00_001B1EA8 is read through $gp, and this function's view of D_00189E20 differs
 * from the HeroProbeState declared in L00_002C2DE8-g8.c. The byte and flag tests read
 * their fields into int locals first: a zero-extending load from memory is one RTL insn,
 * while a test shortened to QImode/HImode loads and extends separately. Those two insns
 * decide loop.c's hoisting (threshold * savings * lifetime >= loop insns): 0x99D moves in
 * the first loop pass, then the &D_00189E20 copy, 1 and 0x1D in the rerun, as in retail. */
#include "common.h"
typedef struct {
    unsigned char pad0[0x80]; float position[4];
    unsigned char pad1[8]; float heading;
    unsigned char pad2[0x64C - 0x9C]; float alternate_heading;
    unsigned char pad3[0xB10 - 0x650]; void *selected_b10; int ready_b14;
    unsigned char pad4[0x2294 - 0xB18]; int mode, field_2298, state;
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
            int flags, active;
            if (*(short *)(node + 0xAA) != 0x99D) continue;
            flags = *(unsigned short *)(node + 0x34);
            if (flags & 1) continue;
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
            active = node[0x31];
            if (active == 0) score += 10.0f;
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
