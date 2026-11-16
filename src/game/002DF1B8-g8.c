#include "include_asm.h"
#include "names.h"

/* -G8 sibling for src/game/002DF1B8.c: the two argument words go out through
   $gp, so this body needs the small-data addressing mode. */

extern int request_begin_slot(int, int, int, int, int);

extern void SetBackgroundColor(int, int, int);

extern int g_moby_hide_mode_a __attribute__((sda));
extern int g_moby_hide_mode_b __attribute__((sda));

extern int g_world_draw_callback_count[] __attribute__((sda));
extern char *g_moby_pool_start;
extern char *g_moby_context_aux;

extern char *g_dma_packet_cursor;
extern int g_shadow_pass_table[2] __attribute__((sda));
extern char g_shadow_packet_records[];
extern void shadow_draw_pass(int, int);

/* func_002DF380 is here for the compiler, not for $gp: the SDK compiler of
   src/game/002DF1B8.c does not rotate the loop the way retail does. The first
   call returns a word the original keeps in $v0, which is what puts the base
   pointer in $v1. */
extern int request_end_slot(int, int);

/* The globals this function reads are above the resident data: their addresses
   differ from program to program, so they have no address in their names. */
extern int ref_L00_002DF380_00[];
extern char *ref_L00_002DF380_01;
extern char *ref_L00_002DF380_02;

/* Shows every game object again by clearing the hidden mark on each one. */
void moby_show_all(void)
{
    char *start;
    char *end;
    char *p;

    request_end_slot(0, 0);
    SetBackgroundColor(ref_L00_002DF380_00[0x8F], ref_L00_002DF380_00[0x90], ref_L00_002DF380_00[0x91]);
    start = ref_L00_002DF380_02;
    end = ref_L00_002DF380_01;
    for (p = start; p < end; p += 0x100) {
        *(unsigned short *)(p + 0x34) &= 0xFF7F;
    }
}

/* Adds a shadow drawing step to the packet list and starts it. */
void gfx_shadow_submit_packet(int pass, int tableIndex, int recordIndex)
{
    *(int *)(*(char *volatile *)&g_dma_packet_cursor + 0x0) = 0x30000003;
    *(int *)(*(char *volatile *)&g_dma_packet_cursor + 0x4) = (int)(g_shadow_packet_records + recordIndex * 0x30);
    *(int *)(*(char *volatile *)&g_dma_packet_cursor + 0x8) = 0x13000000;
    *(int *)(*(char *volatile *)&g_dma_packet_cursor + 0xC) = 0x50000003;
    g_dma_packet_cursor = *(char *volatile *)&g_dma_packet_cursor + 0x10;
    shadow_draw_pass(pass, g_shadow_pass_table[tableIndex]);
}

/* Hides every game object by setting a hidden mark on each one, and remembers the two arguments. */
void moby_hide_all(int firstArg, int secondArg)
{
    char *start;
    char *end;
    char *p;

    request_begin_slot(7, 1, 0, 0, 0);
    g_moby_hide_mode_b = secondArg;
    g_moby_hide_mode_a = firstArg;
    g_world_draw_callback_count[0] = 0;
    SetBackgroundColor(0, 0, 0);
    start = g_moby_pool_start;
    end = g_moby_context_aux;
    for (p = start; p < end; p += 0x100) {
        *(unsigned short *)(p + 0x34) |= 0x80;
    }
}

extern char *g_dma_list_tail;
extern int g_dma_list_max_size __attribute__((section(".sdata")));
extern void *g_vram_cursor __attribute__((sda));
extern char g_str_display_list_size[];
extern int BuildShrubTextureDma(void *);
extern void gfx_append_vu1_preset_a(void);
extern void STUB_printf(const char *, ...);

/* Links the two graphics packet lists together, checks how big the frame got, warns if it is too large and keeps the biggest size seen. */
void gfx_link_display_lists_track_size(void)
{
    char *other = *(char *volatile *)&g_dma_list_tail;
    char *saved = *(char *volatile *)&g_dma_packet_cursor;
    char *next;
    int size;
    g_dma_packet_cursor = saved + 16;
    *(unsigned int *)other = 0x20000000;
    *(int *)(*(char *volatile *)&g_dma_list_tail + 4) = (int)*(char *volatile *)&g_dma_packet_cursor;
    *(int *)(*(char *volatile *)&g_dma_list_tail + 8) = 0;
    *(int *)(*(char *volatile *)&g_dma_list_tail + 12) = 0;
    size = BuildShrubTextureDma(g_vram_cursor);
    gfx_append_vu1_preset_a();
    if (size > 0x400000)
        STUB_printf(g_str_display_list_size);
    if (*(volatile int *)&g_dma_list_max_size < size)
        g_dma_list_max_size = size;
    *(unsigned int *)(*(char *volatile *)&g_dma_packet_cursor) = 0x20000000;
    next = *(char *volatile *)&g_dma_list_tail + 16;
    *(int *)(*(char *volatile *)&g_dma_packet_cursor + 4) = (int)next;
    *(int *)(*(char *volatile *)&g_dma_packet_cursor + 8) = 0;
    *(int *)(*(char *volatile *)&g_dma_packet_cursor + 12) = 0;
    *(char *volatile *)&g_dma_packet_cursor = *(char *volatile *)&g_dma_packet_cursor + 16;
    *(unsigned int *)saved = 0x20000000;
    *(int *)(saved + 4) = (int)*(char *volatile *)&g_dma_packet_cursor;
    *(int *)(saved + 8) = 0;
    *(int *)(saved + 12) = 0;
}

extern char *GetLocalizedString(int);
extern int sprintf(char *, const char *, ...);
extern const char g_str_two_string_fmt[];
extern const char g_str_localized_text_fmt[];
extern struct { int text; int pad; } g_menu_text_id_table[];

/* Builds the text for a location name into the buffer. Most locations get a prefix word first. */
char *text_format_location_name(char *buf, int kind) {
    int flag;

    switch (kind) {
    case 2:
    case 5:
    case 10:
    case 23:
    case 24:
    case 25:
    case 26:
        flag = 0;
        break;
    default:
        flag = 1;
        break;
    }
    if (flag) {
        sprintf(buf, g_str_two_string_fmt, GetLocalizedString(0xB44), GetLocalizedString(g_menu_text_id_table[kind].text));
    } else {
        sprintf(buf, g_str_localized_text_fmt, GetLocalizedString(g_menu_text_id_table[kind].text));
    }
    return buf;
}
