/* func_PAL_002D7B68, the PAL copy of func_002D6F38: the same C, except that both level-step
   calls to func_00295C50 also run with an empty entry while D_001A79F0 is 0. */
#include "common.h"

typedef struct {
    char reserved[0xE0];
    int back;
} MapPage;
typedef struct {
    char reserved[8];
    int state;
    char reservedC[8];
    MapPage *current;
    int next;
    char reserved1C[0x28 - 0x1C];
    int mode;
    char reserved2C[0xDB - 0x2C];
    unsigned char pending;
    char reservedDC[0xF4 - 0xDC];
    int warp;
    char reservedF8[8];
    MapPage *saved_page;
    int saved_state;
    char reserved108[0x134 - 0x108];
    int locked;
    char reserved138[8];
    int saved_mode;
} MapMenu;
typedef struct {
    char reserved[4];
    short mode;
    char reserved6[0x78 - 6];
} MapRead;
typedef struct {
    int mask, chunks, pixels, palette, texture, layer1, layer2;
} MapHeader;
typedef struct {
    char reserved[0xC];
    void *mask;
    char reserved10[0x28 - 0x10];
    int stream;
    char reserved2C[0x230 - 0x2C];
    int level, loaded;
    void *source;
    int source_level;
    int source_size;
    int reserved244;
    MapHeader *header;
    int image_vram, clut_vram, texture_vram[3];
    char reserved260[8];
    long texture[3];
    char reserved280[8];
    int slots[5], ids[5], selected, sizes[5];
} MapState;
typedef struct { int offset, size; } MapEntry;
typedef struct {
    char reserved[0x36C];
    int base;
    char reserved370[0x14F0 - 0x370];
    MapEntry maps[28];
    MapEntry alt_maps[28];
} MapDisc;
extern MapMenu g_pause_menu_state;
extern MapState g_map_overlay_state;
extern MapRead g_music_state;
extern MapDisc g_copy_setup_data;
extern int g_pad_state[];
extern char g_level_page_root[], g_pause_page_c[], g_loader_movie[];
extern int g_request_flag_table[];
extern int g_vram_frame_base __attribute__((sda));
extern int g_loader_state_word;
extern int D_001A7478_sda __attribute__((sda));
extern int *g_map_select_list __attribute__((sda));
extern int g_current_map_index;
extern unsigned char g_map_overlay_flag, g_map_unlocked_flags[];
extern char g_map_occlusion_data[];
extern int map_update_overlay_pan_zoom(void);
extern void map_set_current_and_refresh(int);
extern int menu_update_entry_states(void);
extern void menu_restore_saved_screen_image(int);
extern int snd_play_from_global_bank(int, int, int);
extern int req_push_queue(void *, int), req_launch_queued(void *);
extern int map_find_table_index(int), map_find_cache_slot_by_id(int), map_choose_slot_to_reuse(void);
extern void map_move_cache_slot(int, int);
extern int fast_decompress_pal(int, void *);
extern int menu_stream_chunk_claim_free_pal(int), release_menu_stream_buffer(int);
extern void compose_bitmap_from_mask(void *, void *, void *, void *);
extern void map_decode_occlusion(int, void *, void *), map_build_mask_bitmap(int, void *, void *);
extern long register_8bit_texture(int, int, void *, void *, int, int);
extern void func_0029D0E0(void), func_0029DEA8(int, int);
extern int map_select_first_usable_slot(void), PickNextMap(void);
extern s32 gfx_upload_records_to_buffer_slot(int, void *, int, int, int);
extern int load_start_disc_read(int, int, int);

/* Runs the map screen: handles buttons, loads the map picture for the chosen page and streams the next one from disc (PAL version). */
int DrawMapScreen_pal(int unused)
{
    int previous_level, table_index, cache_id, slot, reuse_slot, mask_buffer, free_slot, next_map, map_key;
    MapHeader *header;
    char *pixels, *palette_data, *data_base, *mask_data, *texture_data, *layer1_data, *layer2_data;
    int movie_index;
    char *texture_base;

    map_update_overlay_pan_zoom();
    if (g_pause_menu_state.current != (MapPage *)g_level_page_root) {
        previous_level = g_map_overlay_state.level;
        if ((g_pad_state[0x1C4 / 4] & 0xD00) && !g_pause_menu_state.locked) {
close_map:
            return 1;
        }
        if (g_pad_state[0x1C4 / 4] & 0x10) {
            int result;
            if (g_pause_menu_state.current->back)
                g_pause_menu_state.next = g_pause_menu_state.current->back;
            else if (!g_pause_menu_state.locked) {
                result = -1;
                goto back_done;
            }
            result = 0;
back_done:
            return result;
        }
        if (g_pad_state[0x1C4 / 4] & 0x40)
            g_pause_menu_state.next = (int)g_pause_page_c;
        if ((g_pad_state[0x1C4 / 4] & 0x20) && g_map_overlay_state.level >= 0 && !g_pause_menu_state.pending) {
            if (g_map_overlay_state.level == 0)
                movie_index = 21;
            else if (g_map_overlay_state.level == 24)
                movie_index = 0;
            else
                movie_index = g_map_overlay_state.level;
            if (g_map_overlay_state.level < 0) goto close_map;
            {
                unsigned int word = (unsigned)g_map_overlay_state.level >> 2;
                int bit = 1 << (g_map_overlay_state.level & 0x1F);
                if (!(g_request_flag_table[word] & bit)) goto close_map;
            }
            g_vram_frame_base = g_pause_menu_state.mode;
            menu_restore_saved_screen_image(0);
            {
                int saved_mode = g_loader_state_word;
                g_pause_menu_state.saved_page = g_pause_menu_state.current;
                g_pause_menu_state.saved_state = g_pause_menu_state.state;
                g_pause_menu_state.warp = g_map_overlay_state.level;
                g_pause_menu_state.saved_mode = saved_mode;
            }
            D_001A7478_sda = 2;
            req_push_queue(g_loader_movie, movie_index);
            req_launch_queued(g_loader_movie);
            goto close_map;
        }
        table_index = map_find_table_index(g_map_overlay_state.level);
        if (table_index >= 0) {
            if ((g_pad_state[0x1C4 / 4] & 8) && table_index < 27) {
                if (g_map_select_list[table_index + 1] || !g_current_map_index) map_set_current_and_refresh(g_map_select_list[table_index + 1]);
            }
            if ((g_pad_state[0x1C4 / 4] & 4) && table_index) {
                if (g_map_select_list[table_index - 1] || !g_current_map_index) map_set_current_and_refresh(g_map_select_list[table_index - 1]);
            }
        }
        if (g_map_overlay_state.level != previous_level) {
            snd_play_from_global_bank(3, 0, 0);
            menu_update_entry_states();
        }
    }
    if (g_pause_menu_state.current == (MapPage *)g_level_page_root)
        g_map_overlay_state.stream = 1;
    cache_id = g_map_overlay_state.level;
    if (g_map_overlay_flag) cache_id += 256;
    slot = map_find_cache_slot_by_id(cache_id);
    if (g_map_overlay_state.level != g_map_overlay_state.loaded && slot != -1) {
        reuse_slot = map_choose_slot_to_reuse();
        if (g_map_overlay_state.slots[0] && reuse_slot > 0) {
            map_move_cache_slot(reuse_slot, 0);
            if (!slot) slot = reuse_slot;
        }
        fast_decompress_pal(g_map_overlay_state.slots[slot], g_map_overlay_state.header);
        header = g_map_overlay_state.header;
        pixels = (char *)header + header->pixels;
        palette_data = (char *)header + header->palette;
        mask_buffer = menu_stream_chunk_claim_free_pal(0);
        if (mask_buffer) {
            data_base = (char *)g_map_overlay_state.header;
            mask_data = data_base + header->mask + 8;
            if (g_map_overlay_state.level == g_current_map_index)
                compose_bitmap_from_mask(palette_data, pixels, palette_data, g_map_overlay_state.mask);
            else {
                if (g_map_unlocked_flags[g_map_overlay_state.level])
                    map_decode_occlusion(mask_buffer, g_map_occlusion_data + (g_map_overlay_state.level << 11), data_base + header->chunks);
                else
                    map_build_mask_bitmap(mask_buffer, mask_data, mask_data);
                compose_bitmap_from_mask(palette_data, pixels, palette_data, (void *)mask_buffer);
            }
        }
        texture_base = (char *)g_map_overlay_state.header;
        texture_data = texture_base + header->texture;
        layer1_data = texture_base + header->layer1 + 0x420;
        layer2_data = texture_base + header->layer2 + 0x420;
        g_map_overlay_state.texture[0] = register_8bit_texture(7, 7, texture_data + 32, texture_data + 0x420, g_map_overlay_state.clut_vram, g_map_overlay_state.texture_vram[0]);
        g_map_overlay_state.texture[1] = register_8bit_texture(7, 7, texture_data + 32, layer1_data, g_map_overlay_state.clut_vram, g_map_overlay_state.texture_vram[1]);
        g_map_overlay_state.texture[2] = register_8bit_texture(7, 7, texture_data + 32, layer2_data, g_map_overlay_state.clut_vram, g_map_overlay_state.texture_vram[2]);
        if (mask_buffer) register_8bit_texture(9, 9, palette_data, palette_data, 0x3FF000, g_map_overlay_state.image_vram);
        func_0029D0E0();
        if (mask_buffer) release_menu_stream_buffer(mask_buffer);
        g_map_overlay_state.slots[0] = (int)pixels;
        g_map_overlay_state.loaded = g_map_overlay_state.level;
        func_0029DEA8(g_map_overlay_state.level, 0);
    }
    if (!g_music_state.mode && g_map_overlay_state.selected != -1) {
        g_pause_menu_state.pending = 0;
        g_map_overlay_state.ids[g_map_overlay_state.selected] ^= 0x1000;
        g_map_overlay_state.selected = -1;
    }
    free_slot = -1;
    if (g_map_overlay_state.stream && !g_music_state.mode) {
        free_slot = map_select_first_usable_slot();
        if (free_slot != -1) {
            next_map = PickNextMap();
            if (next_map != -1) {
                map_key = (g_current_map_index + g_map_overlay_state.source_level == 0) ? 0 : 256;
                if (map_key == next_map) {
                    gfx_upload_records_to_buffer_slot(g_map_overlay_state.slots[free_slot], g_map_overlay_state.source, 0, g_map_overlay_state.source_size, 0);
                    g_map_overlay_state.sizes[free_slot] = g_map_overlay_state.source_size;
                } else {
                    if (next_map & 256) {
                        int *size;
                        int sector, origin, read_buffer, sectors;
                        origin = g_copy_setup_data.base;
                        sector = g_copy_setup_data.alt_maps[next_map ^ 256].offset;
                        size = &g_copy_setup_data.alt_maps[next_map ^ 256].size;
                        read_buffer = g_map_overlay_state.slots[free_slot];
                        sectors = *size;
                        load_start_disc_read(read_buffer, sector + origin, sectors);
                        g_map_overlay_state.sizes[free_slot] = (*size << 11) >> 4;
                    } else {
                        int *size;
                        int sector, origin, read_buffer, sectors;
                        origin = g_copy_setup_data.base;
                        sector = g_copy_setup_data.maps[next_map].offset;
                        size = &g_copy_setup_data.maps[next_map].size;
                        read_buffer = g_map_overlay_state.slots[free_slot];
                        sectors = *size;
                        load_start_disc_read(read_buffer, sector + origin, sectors);
                        g_map_overlay_state.sizes[free_slot] = (*size << 11) >> 4;
                    }
                    g_pause_menu_state.pending = 1;
                }
                g_map_overlay_state.ids[free_slot] = next_map | 0x1000;
                g_map_overlay_state.selected = free_slot;
            }
        }
    }
    slot = map_find_cache_slot_by_id(cache_id);
    if (g_map_overlay_state.level != g_map_overlay_state.loaded && !g_music_state.mode && slot == -1 && free_slot == slot)
        map_choose_slot_to_reuse();
    return 0;
}
