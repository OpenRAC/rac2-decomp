#include "include_asm.h"
#include "names.h"

/* The published pair lives in small data, so this file is built with -G8. */
extern int g_packet_buffer_index;
extern int g_packet_buffer_size;
extern int g_packet_buffer_table[];
extern int g_packet_buffer_offset;
extern int g_scratch_upload_ptr;
extern int ref_L00_002FC190_00 __attribute__((sda));

/* Rebuilds the viewport position from the indexed table and the two resident
   offsets, then publishes it and one lowered copy. */
void gfx_rebuild_packet_buffer_pointers(void)
{
    int value = g_packet_buffer_table[g_packet_buffer_index] + g_packet_buffer_size - g_packet_buffer_offset;

    g_scratch_upload_ptr = value;
    ref_L00_002FC190_00 = value - 0x2000;
}

extern char g_loader_memory[];
extern int g_dma_packet_cursor;
extern int ref_L00_002FC1D8_00 __attribute__((sda));

/* Seeds the viewport from the resident pair, clears the index and rebuilds. */
void gfx_reset_packet_buffer(void)
{
    char *base = g_loader_memory;
    int value = *(int *)(base + 0xC);

    g_packet_buffer_table[0] = value;
    g_packet_buffer_table[1] = *(int *)(base + 0x10);
    g_dma_packet_cursor = value;
    ref_L00_002FC1D8_00 = 0;
    gfx_rebuild_packet_buffer_pointers();
}

extern int g_current_map_index;
extern int g_packet_buffer_ref_table[];
extern int g_packet_buffer_value_table[];
extern int ref_L00_002FC138_00 __attribute__((sda));

/* Clamps the resident index, publishes the two selected values and rebuilds. */
void gfx_select_packet_buffer_setup(void)
{
    int index = g_current_map_index;

    if ((unsigned int)index >= 0x19)
        index = 0;
    g_packet_buffer_offset = g_packet_buffer_value_table[index];
    ref_L00_002FC138_00 = g_packet_buffer_ref_table[index];
    gfx_rebuild_packet_buffer_pointers();
}
