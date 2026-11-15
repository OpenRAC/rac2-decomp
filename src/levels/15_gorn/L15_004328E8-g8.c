#include "include_asm.h"
#include "names.h"

/* Small-data file: this body reaches its global through $gp, so it only
 * reproduces at -G8. */

extern int D_L15_001B187C __attribute__((sda));

extern void func_L15_00437B68(int, int);

/* Draws the scrolling grid layers when the grid is switched on. */
void func_L15_00438238(int drawArg) {
    if (D_L15_001B187C != 0) {
        DrawScrollingGridLayers(drawArg, 1);
    }
}
