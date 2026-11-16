#include "include_asm.h"
#include "names.h"

/* Small-data file: this body reaches its global through $gp, so it only
 * reproduces at -G8. */

extern int g_backdrop_grid_enabled __attribute__((sda));

extern void DrawScrollingGridLayers(int, int);

/* Draws the scrolling grid layers when the grid is switched on. */
void gfx_draw_scrolling_grid_if_enabled(int drawArg) {
    if (g_backdrop_grid_enabled != 0) {
        DrawScrollingGridLayers(drawArg, 1);
    }
}
