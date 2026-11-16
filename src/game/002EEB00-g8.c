#include "include_asm.h"
#include "names.h"

extern char *g_render_list_head;
extern char *g_render_list_tail;
extern int g_render_list_max_chain_size;
extern int g_vram_cursor __attribute__((sda));
extern char g_str_render_list_marker[];

extern void func_002F00A8(void);
extern int func_002F0218(int);
extern void gfx_append_vu1_preset_a(void);
extern void STUB_printf(const char *, ...);

/* Adds an empty marker to the render list, runs the main render passes, records how big the list got, and links the markers together. */
void gfx_build_render_list_markers(void)
{
    char *oldHead;
    char *oldTail;
    int chainSize;

    oldHead = g_render_list_head;
    oldTail = g_render_list_tail;
    g_render_list_tail = oldTail + 16;
    *(int *)(oldHead + 0) = 0x20000000;
    *(char **)(g_render_list_head + 4) = g_render_list_tail;
    *(int *)(g_render_list_head + 8) = 0;
    *(int *)(g_render_list_head + 12) = 0;
    func_002F00A8();
    chainSize = func_002F0218(g_vram_cursor);
    gfx_append_vu1_preset_a();
    if (0x400000 < chainSize) {
        STUB_printf(g_str_render_list_marker);
    }
    if (g_render_list_max_chain_size < chainSize) {
        g_render_list_max_chain_size = chainSize;
    }

    *(int *)(g_render_list_tail + 0) = 0x20000000;
    *(char **)(g_render_list_tail + 4) = g_render_list_head + 16;
    *(int *)(g_render_list_tail + 8) = 0;
    *(int *)(g_render_list_tail + 12) = 0;
    g_render_list_tail = g_render_list_tail + 16;
    *(int *)(oldTail + 0) = 0x20000000;
    *(char **)(oldTail + 4) = g_render_list_tail;
    *(int *)(oldTail + 8) = 0;
    *(int *)(oldTail + 12) = 0;
}
