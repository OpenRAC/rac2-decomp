#include "include_asm.h"
#include "names.h"

extern void VU1_addGSregister(unsigned int reg, unsigned long long value);

extern int g_vram_zbuffer_address;

extern short g_screen_adjust_offsets[];

extern void gfx_draw_colored_rectangle(int a, int b, int c, int d, unsigned long e);

/* The argument is a structure: a word at +4 and a double word at +8. */
/* Draws a screen-sized fade or tint step using the values stored in the given packet. */
void gfx_draw_screen_tint_step(char *packet)
{
    if (*(unsigned long long *)(packet + 8) != 0) {
        VU1_addGSregister(0x42, *(unsigned long long *)(packet + 8) & 0xFF000000FFULL);
    }
    if (*(int *)(packet + 4) & 0xFF000000) {
        VU1_addGSregister(0x4E, (((long long)(g_vram_zbuffer_address >> 13) | 0x1000000) | (1LL << 32)));
        gfx_draw_colored_rectangle(0, g_screen_adjust_offsets[0xA9], 0, g_screen_adjust_offsets[0xA8], *(unsigned int *)(packet + 4));
        VU1_addGSregister(0x4E, (g_vram_zbuffer_address >> 13) | 0x1000000);
    }
    if (*(unsigned long long *)(packet + 8) != 0) {
        VU1_addGSregister(0x42, 0x8000000044ULL);
    }
}

extern char *ref_0027DDC0_00;

extern char g_gfx_clear_packet_a[];

/* Packs a colour into the GS register 1 and writes the matching packet. */
/* Sets the screen clear color and adds a matching draw packet. */
void gfx_set_clear_color_packet(int r, int g, int b, int a)
{
    unsigned long packed;

    packed = (unsigned long)r | ((unsigned long)g << 8);
    packed |= ((unsigned long)b << 16);
    packed |= ((unsigned long)a << 24);
    VU1_addGSregister(1, packed);
    *(int *)(ref_0027DDC0_00 + 0) = 0x30000014;
    *(char **)(ref_0027DDC0_00 + 4) = g_gfx_clear_packet_a;
    *(int *)(ref_0027DDC0_00 + 8) = 0;
    *(int *)(ref_0027DDC0_00 + 12) = 0x50000014;
    ref_0027DDC0_00 = ref_0027DDC0_00 + 16;
}

extern int *g_dma_packet_cursor __attribute__((section(".sdata")));
extern int *g_clear_color_packet __attribute__((section(".sdata")));
extern int g_vram_cursor __attribute__((section(".sdata")));
extern int g_vram_frame_base __attribute__((section(".sdata")));
extern int g_vram_display_address __attribute__((section(".sdata")));
extern int g_palette_upload_count __attribute__((section(".sdata")));
extern int g_gfx_entry_count __attribute__((section(".sdata")));
extern long g_clear_color_word_a __attribute__((sda));
extern long g_clear_color_word_b __attribute__((sda));
extern int g_clear_color_word_c __attribute__((section(".sdata")));
extern long g_texture_upload_params[];
extern char g_hud_state[] __attribute__((sda));

/* SetupGifPaging, after RAC1 draw.c (GPL-3.0): marks the packet cursor in
   D_001B15F4 and reserves 0x10 bytes, restarts the texture allocation cursor,
   clears the upload count and the first dword of the paging slots, then, when
   arg0 is 0, clears the +4 half of the arena's 8-byte list entries: the list
   at +0x24 (count at +0x44 of the record at +0x18) where it is at least
   D_001A72DC >> 8, and all of the list at +0x28 (count at +0x24).  The arena
   read at an offset is a two-word load, which keeps the second list's load out
   of the loop branch's delay slot. */
void SetupGifPaging(int keepEntries) {
    int *cursor = g_dma_packet_cursor;
    int i;

    g_clear_color_packet = cursor;
    cursor += 4;
    g_dma_packet_cursor = cursor;
    g_vram_cursor = g_vram_frame_base;
    g_palette_upload_count = 0;
    {
        int k;

        for (k = 0; k < g_gfx_entry_count; k++) {
            g_texture_upload_params[k * 2] = 0;
        }
    }
    g_clear_color_word_a = 0;
    g_clear_color_word_b = 0;
    g_clear_color_word_c = 0;
    if (keepEntries == 0) {
        for (i = 0; i < *(int *)(*(char **)(g_hud_state + 0x18) + 0x44); i++) {
            unsigned short *el = (unsigned short *)(i * 8 + *(int *)(g_hud_state + 0x24) + 4);

            if (*el >= (g_vram_display_address >> 8)) {
                *el = 0;
            }
        }
        {
            int j;

            for (j = 0; j < *(int *)(*(char **)(g_hud_state + 0x18) + 0x24); j++) {
                *(short *)(*(char **)(g_hud_state + 0x28) + j * 8 + 4) = 0;
            }
        }
    }
}
