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
extern int func_PAL_002DF328(int), release_menu_stream_buffer(int);
extern void compose_bitmap_from_mask(void *, void *, void *, void *);
extern void map_decode_occlusion(int, void *, void *), map_build_mask_bitmap(int, void *, void *);
extern long register_8bit_texture(int, int, void *, void *, int, int);
extern void func_0029D0E0(void), func_0029DEA8(int, int);
extern int map_select_first_usable_slot(void), PickNextMap(void);
extern s32 gfx_upload_records_to_buffer_slot(int, void *, int, int, int);
extern int load_start_disc_read(int, int, int);

int func_PAL_002D7B68(int arg)
{
    int prev, idx, id, slot, n, buf, pick, next, k;
    MapHeader *hdr;
    char *pix, *pal, *base, *a, *tex, *b, *c;
    int mapped;
    char *tbase;

    map_update_overlay_pan_zoom();
    if (g_pause_menu_state.current != (MapPage *)g_level_page_root) {
        prev = g_map_overlay_state.level;
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
                mapped = 21;
            else if (g_map_overlay_state.level == 24)
                mapped = 0;
            else
                mapped = g_map_overlay_state.level;
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
            req_push_queue(g_loader_movie, mapped);
            req_launch_queued(g_loader_movie);
            goto close_map;
        }
        idx = map_find_table_index(g_map_overlay_state.level);
        if (idx >= 0) {
            if ((g_pad_state[0x1C4 / 4] & 8) && idx < 27) {
                if (g_map_select_list[idx + 1] || !g_current_map_index) map_set_current_and_refresh(g_map_select_list[idx + 1]);
            }
            if ((g_pad_state[0x1C4 / 4] & 4) && idx) {
                if (g_map_select_list[idx - 1] || !g_current_map_index) map_set_current_and_refresh(g_map_select_list[idx - 1]);
            }
        }
        if (g_map_overlay_state.level != prev) {
            snd_play_from_global_bank(3, 0, 0);
            menu_update_entry_states();
        }
    }
    if (g_pause_menu_state.current == (MapPage *)g_level_page_root)
        g_map_overlay_state.stream = 1;
    id = g_map_overlay_state.level;
    if (g_map_overlay_flag) id += 256;
    slot = map_find_cache_slot_by_id(id);
    if (g_map_overlay_state.level != g_map_overlay_state.loaded && slot != -1) {
        n = map_choose_slot_to_reuse();
        if (g_map_overlay_state.slots[0] && n > 0) {
            map_move_cache_slot(n, 0);
            if (!slot) slot = n;
        }
        fast_decompress_pal(g_map_overlay_state.slots[slot], g_map_overlay_state.header);
        hdr = g_map_overlay_state.header;
        pix = (char *)hdr + hdr->pixels;
        pal = (char *)hdr + hdr->palette;
        buf = func_PAL_002DF328(0);
        if (buf) {
            base = (char *)g_map_overlay_state.header;
            a = base + hdr->mask + 8;
            if (g_map_overlay_state.level == g_current_map_index)
                compose_bitmap_from_mask(pal, pix, pal, g_map_overlay_state.mask);
            else {
                if (g_map_unlocked_flags[g_map_overlay_state.level])
                    map_decode_occlusion(buf, g_map_occlusion_data + (g_map_overlay_state.level << 11), base + hdr->chunks);
                else
                    map_build_mask_bitmap(buf, a, a);
                compose_bitmap_from_mask(pal, pix, pal, (void *)buf);
            }
        }
        tbase = (char *)g_map_overlay_state.header;
        tex = tbase + hdr->texture;
        b = tbase + hdr->layer1 + 0x420;
        c = tbase + hdr->layer2 + 0x420;
        g_map_overlay_state.texture[0] = register_8bit_texture(7, 7, tex + 32, tex + 0x420, g_map_overlay_state.clut_vram, g_map_overlay_state.texture_vram[0]);
        g_map_overlay_state.texture[1] = register_8bit_texture(7, 7, tex + 32, b, g_map_overlay_state.clut_vram, g_map_overlay_state.texture_vram[1]);
        g_map_overlay_state.texture[2] = register_8bit_texture(7, 7, tex + 32, c, g_map_overlay_state.clut_vram, g_map_overlay_state.texture_vram[2]);
        if (buf) register_8bit_texture(9, 9, pal, pal, 0x3FF000, g_map_overlay_state.image_vram);
        func_0029D0E0();
        if (buf) release_menu_stream_buffer(buf);
        g_map_overlay_state.slots[0] = (int)pix;
        g_map_overlay_state.loaded = g_map_overlay_state.level;
        func_0029DEA8(g_map_overlay_state.level, 0);
    }
    if (!g_music_state.mode && g_map_overlay_state.selected != -1) {
        g_pause_menu_state.pending = 0;
        g_map_overlay_state.ids[g_map_overlay_state.selected] ^= 0x1000;
        g_map_overlay_state.selected = -1;
    }
    pick = -1;
    if (g_map_overlay_state.stream && !g_music_state.mode) {
        pick = map_select_first_usable_slot();
        if (pick != -1) {
            next = PickNextMap();
            if (next != -1) {
                k = (g_current_map_index + g_map_overlay_state.source_level == 0) ? 0 : 256;
                if (k == next) {
                    gfx_upload_records_to_buffer_slot(g_map_overlay_state.slots[pick], g_map_overlay_state.source, 0, g_map_overlay_state.source_size, 0);
                    g_map_overlay_state.sizes[pick] = g_map_overlay_state.source_size;
                } else {
                    if (next & 256) {
                        int *size;
                        int sector, origin, read_buffer, sectors;
                        origin = g_copy_setup_data.base;
                        sector = g_copy_setup_data.alt_maps[next ^ 256].offset;
                        size = &g_copy_setup_data.alt_maps[next ^ 256].size;
                        read_buffer = g_map_overlay_state.slots[pick];
                        sectors = *size;
                        load_start_disc_read(read_buffer, sector + origin, sectors);
                        g_map_overlay_state.sizes[pick] = (*size << 11) >> 4;
                    } else {
                        int *size;
                        int sector, origin, read_buffer, sectors;
                        origin = g_copy_setup_data.base;
                        sector = g_copy_setup_data.maps[next].offset;
                        size = &g_copy_setup_data.maps[next].size;
                        read_buffer = g_map_overlay_state.slots[pick];
                        sectors = *size;
                        load_start_disc_read(read_buffer, sector + origin, sectors);
                        g_map_overlay_state.sizes[pick] = (*size << 11) >> 4;
                    }
                    g_pause_menu_state.pending = 1;
                }
                g_map_overlay_state.ids[pick] = next | 0x1000;
                g_map_overlay_state.selected = pick;
            }
        }
    }
    slot = map_find_cache_slot_by_id(id);
    if (g_map_overlay_state.level != g_map_overlay_state.loaded && !g_music_state.mode && slot == -1 && pick == slot)
        map_choose_slot_to_reuse();
    return 0;
}
