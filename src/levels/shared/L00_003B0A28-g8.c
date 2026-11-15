#include "names.h"
/* Advances the trailing node-ring cursor to a live slot or the insertion cursor. */
typedef struct { float pos[3]; int active; int pad; unsigned char links[8]; } CursorNode;
extern CursorNode D_L00_0023BB78[];
extern unsigned char D_L00_001AF810 __attribute__((sda));
extern unsigned char D_L00_001AF811 __attribute__((sda));
void AdvanceNodeRingCursor(void)
{
    if (D_L00_001AF811 != D_L00_001AF810) {
        D_L00_001AF811++;
        while (D_L00_0023BB78[D_L00_001AF811].active == 0 &&
               D_L00_001AF811 != D_L00_001AF810) {
            D_L00_001AF811++;
        }
    }
}
