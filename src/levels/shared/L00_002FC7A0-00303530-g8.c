#include "names.h"
extern void music_Pause();
extern int request_is_current_slot();
extern void snd_start_music_stream_no_loop();
extern void level_update_object_visibility();
extern void ReloadSoundBank();
extern void tutorial_reset_record_values();
extern void gfx_reset_record_list();
extern void func_002F0468();
extern void level_relocate_header_blocks();
extern void initialize_tfrag_render_data();
extern void fast_decompress();
extern void FlushCache();
extern int load_read_disc_with_pause(char *, int, int);
extern void level_flush_table_entry_offsets();
extern void gfx_wait_for_dma_status_bits();
extern void snd_wait_for_music_idle();
extern void snd_clear_all_voices();
extern void gfx_configure_screen_effect();
#include "include_asm.h"
#include "names.h"
extern int D_L00_001C9340[];
extern int D_L00_001B2600[];
extern int D_L00_001B2614 __attribute__((section(".sdata")));
extern int D_L00_001B24D4 __attribute__((section(".sdata")));
typedef struct {
    unsigned char pad00[0x529C];
    int base;
    unsigned char pad52A0[0x28];
    struct { int sector, size; } entries[0];
} ChunkDiscTable;
extern ChunkDiscTable g_copy_setup_data;
extern int D_L00_001B2608 __attribute__((section(".sdata")));
extern unsigned char *D_L00_001B24D0 __attribute__((section(".sdata")));

/* Loads a scene chunk, initializes its geometry and batches tfrag lighting. */
void load_scene_chunk(int index, int argument)
{
    int *root = D_L00_001C9340;
    int *block, *first, *second;
    int i;
    if (root[0] == index)
        return;
    gfx_configure_screen_effect(0, 0, 0, 0, 0);
    snd_clear_all_voices();
    snd_wait_for_music_idle();
    gfx_wait_for_dma_status_bits(1);
    root[0] = index;
    block = (int *)D_L00_001B2600[0];
    D_L00_001B2608 = D_L00_001B2600[D_L00_001B2614];
    level_flush_table_entry_offsets();
    load_read_disc_with_pause((char *)block, g_copy_setup_data.entries[index].sector + g_copy_setup_data.base, g_copy_setup_data.entries[index].size);
    first = (int *)((char *)block + block[0]);
    second = (int *)((char *)block + block[1]);
    FlushCache(0);
    fast_decompress(first, root[2]);
    fast_decompress(second, root[1]);
    FlushCache(0);
    initialize_tfrag_render_data(root[2], root[4]);
    level_relocate_header_blocks(root[1]);
    {
        int count = D_L00_001B24D4;
        if (count > 0) {
            unsigned short *p = (unsigned short *)(D_L00_001B24D0 + 0x36);
            do {
                *p = 0xffff;
                p += 32;
            } while (--count);
        }
    }
    i = 0;
    while (i < D_L00_001B24D4) {
        unsigned short *p = (unsigned short *)0x70003000;
        int n = 0;
        while (n < 1023 && i < D_L00_001B24D4) {
            *p++ = i;
            n++;
            i++;
        }
        *p = 0xffff;
        func_002F0468((void *)0x70003000);
    }
    gfx_reset_record_list();
    tutorial_reset_record_values();
    ReloadSoundBank(index);
    level_update_object_visibility(index);
    snd_start_music_stream_no_loop(argument, 1, 1024);
    if (request_is_current_slot(2))
        music_Pause(0);
}
