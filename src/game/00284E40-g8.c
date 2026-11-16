#include "common.h"

/* A -G8 unit (the profile from the file's name): a plain extern of at most eight bytes is then
   one assembler operand, and with its .extern only at the end of the file the assembler
   expands it to the retail's absolute lui + load through the destination register. -G0
   splits the address into a high-part register of its own. */

extern u8 *g_fs_aa_buffer_table;
typedef struct { u8 before[0x158]; short a,b,c; u8 gap[10]; short d,e; } DisplayState;
extern DisplayState g_screen_adjust_offsets;
extern void sceGsSetDefDispEnv(u8 *,short,short,short,short,short);

/* Re-applies the current screen layout settings by passing them to the display setup routine. */
void gfx_reapply_display_layout(void) {
    sceGsSetDefDispEnv(g_fs_aa_buffer_table,g_screen_adjust_offsets.c,g_screen_adjust_offsets.a,g_screen_adjust_offsets.b,g_screen_adjust_offsets.d,g_screen_adjust_offsets.e);
}
