/* functional: high. The near-miss draft (524/544 bytes; the difference is loop-invariant hoisting) with the qcopy helper written as plain quadword copies; level 00's callees mapped through functions.tsv (0x2AE388 func_L00_002AE388, 0x2DE4B0 func_002761F8, 0x2EE2E8 func_00282E80, 0x329510 func_002B38B8). Same reads, calls, compares (c.lt.s dist<4, c.lt.s score<best) and stores as retail. */
/* func_L00_002C40C0 (shared, 25 places): picks the hero's target among the moby list (0x1B1EA8 head,
 * +0x28 next): class 0x99D, not flagged (+0x34 bit 0), not func_002B38B8, in the view cone
 * (func_L00_002AE388 with the heading, 30 and the cone angles; narrow in modes 1/0x1D, the alternate
 * heading in state 0xF), at least 4 away; +10 when +0x31 is clear; lowest score wins. The winner goes
 * to hero+0xB10 and hero+0xB14 is set when the line from the hero (z + 0.5) to it is clear.
 * In hero state 0x21 it only returns hero+0xB14.
 * From the near-miss draft nonmatching/levels/func_L00_002C40C0.c. */
#include "common.h"

typedef int Vector __attribute__((mode(TI)));
typedef struct {
    unsigned char pad0[0x80]; Vector position;
    unsigned char pad1[8]; float heading;
    unsigned char pad2[0x64C - 0x9C]; float alternate_heading;
    unsigned char pad3[0xB10 - 0x650]; unsigned char *selected_b10; int ready_b14;
    unsigned char pad4[0x2294 - 0xB18]; int mode, field_2298, state;
} HeroSelectionState;
extern HeroSelectionState D_00189E20;

extern unsigned char *D_L00_001B1EA8 __attribute__((sda));
extern int func_002B38B8(void *);
extern float func_L00_002AE388(void *, int *, float, float, float, float);
extern float func_00282E80(void *, void *);
extern int func_002761F8(void *, void *, int, void *, int);

int func_L00_002C40C0(void)
{
    unsigned char *node, *best;
    float score, closest;
    Vector first, second;
    int blocked[4];

    node = D_L00_001B1EA8;
    if (D_00189E20.state == 0x21)
        return D_00189E20.ready_b14;
    best = 0;
    closest = 100000000.0f;
    D_00189E20.ready_b14 = 0;
    while (node != 0) {
        float horizontal, vertical, heading;
        if (*(short *)(node + 0xAA) != 0x99D) goto next;
        if (*(unsigned short *)(node + 0x34) & 1) goto next;
        if (func_002B38B8(node) != 0) goto next;
        horizontal = 0.5235988497734069824f; /* 0x3F060A93 */
        vertical = -1.0f;
        if (D_00189E20.mode == 1 || D_00189E20.mode == 0x1D) {
            vertical = 0.087266474962234497f; /* 0x3DB2B8C4 */
            horizontal = vertical;
        }
        heading = D_00189E20.heading;
        if (D_00189E20.state == 0xF)
            heading = D_00189E20.alternate_heading;
        score = func_L00_002AE388(node, blocked, heading, 30.0f, horizontal, vertical);
        if (blocked[0] != 0) goto next;
        if (func_00282E80(&D_00189E20.position, node + 0x10) < 4.0f) goto next;
        if (node[0x31] == 0)
            score = score + 10.0f;
        if (score < closest) {
            closest = score;
            best = node;
        }
    next:
        node = *(unsigned char **)(node + 0x28);
    }
    if (best != 0) {
        D_00189E20.selected_b10 = best;
        first = D_00189E20.position;
        ((float *)&first)[2] += 0.5f;
        second = *(Vector *)(best + 0x10);
        if (func_002761F8(&first, &second, 2, 0, 0) == 0)
            D_00189E20.ready_b14 = 1;
    }
    return D_00189E20.ready_b14;
}
