#include "include_asm.h"
#include "names.h"

/* -G8 sibling of src/game/0027F128.c. */

typedef unsigned char u8;
typedef struct { u8 pad[0x1c]; int flags; short x, y, w, h; u8 tail[8]; } CopyRegion;
extern CopyRegion g_screen_copy_regions[];
extern int g_screen_copy_countdown;
extern int g_packet_buffer_index;
extern u8 *g_packet_buffer_table[];
extern void gfx_capture_screen_rect(int, int, int, int, void *);
extern int gfx_wait_paths_idle(int, int);
extern void ComputeRegionThresholdRatio(void *, int);

/* Copies the marked screen regions into spare buffers, one at a time, and clears each mark when done. */
void gfx_process_screen_copy_regions(void) {
    u8 *buffers[2];
    int current, next, i, index;

    if (g_screen_copy_countdown == 0) return;
    buffers[0] = g_packet_buffer_table[1 - g_packet_buffer_index];
    buffers[1] = buffers[0] + 0x40000;
    current = 0;
    next = -1;
    /* Region flag 4 selects an entry; flag 1 retires it after its pass, dropping the active count. */
    for (i = 31; i >= 0; i--) {
        if (g_screen_copy_regions[i].flags & 4) {
            next = i;
            gfx_capture_screen_rect(g_screen_copy_regions[i].x, g_screen_copy_regions[i].y, g_screen_copy_regions[i].w, g_screen_copy_regions[i].h,
                          buffers[current]);
            gfx_wait_paths_idle(0, 0);
        }
    }
    if (next == -1) return;
    index = next;
    while (index >= 0) {
        current = 1 - current;
        next = -1;
        for (i = index - 1; i >= 0; i--) {
            if (g_screen_copy_regions[i].flags & 4) {
                next = i;
                gfx_capture_screen_rect(g_screen_copy_regions[i].x, g_screen_copy_regions[i].y, g_screen_copy_regions[i].w, g_screen_copy_regions[i].h,
                              buffers[current]);
            }
        }
        ComputeRegionThresholdRatio(buffers[1 - current], index);
        if ((g_screen_copy_regions + index)->flags & 1) {
            (g_screen_copy_regions + index)->flags &= ~5;
            g_screen_copy_countdown--;
        }
        if (next >= 0) gfx_wait_paths_idle(0, 0);
        index = next;
    }
}
