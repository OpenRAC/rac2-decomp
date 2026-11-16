#include "names.h"
/* func_PAL_002CAEA0 (1,388 bytes), the PAL copy of func_002CA070 (src/game/002CA070-pause.c):
 * the same C, plus a 0x30-byte copy of D_001B5340 + 0x230 into the pause state (+0x200).
 * func_002CA070 notes: the pause and cinema state machine. Prototype symbols (pause.cpp,
 * loaders.cpp) identify D_001F2840 as the pause state and D_00210A40 as the cinema controller.
 * Own unit: -O2 -G16 -Wa,-G16 -ffunction-sections -frac2-la-funcref-weight (config/cflags.txt).
 * - qzero_nc at the two camera clears (the fresh lui for D_001C2AD0 + 0x10).
 * - The screen size and frame-buffer reads are sym+offset reads of sda pairs, D_001A7340[1] and
 *   D_001A72D8[1]: a (const (plus sym off)) address has length 2, so reorg leaves the bnez slot
 *   empty and gas expands the macro to lui/lw, as retail.
 * - The last loop: D_001A7398 as an sda incomplete array is one `la` insn, so the src giv has
 *   no %hi pseudo and dst takes $v1, the counter $a0, src $a1, as retail.
 * - Case 8 is written in its natural order (page, next, a, b, c, upd, init, init(0)). Its five
 *   block-local values (page, c, 0x18 and the two callbacks) get retail's registers with
 *   -frac2-la-funcref-weight, which counts one more reference in local-alloc for a quantity
 *   set from a function's address (docs/build/compiler-notes.md). The switch is a per-unit
 *   model, not retail's global rule: forced on for every USA v1.01 unit it changes 13 functions.
 *   Allowed by owner ruling, 12 November 2026.
 */
#include "common.h"

typedef struct {
    u8 pad0[0x8];
    int state;          /* 0x08 */
    u8 pad1[0x8];
    int *page;          /* 0x14 */
    int *next;          /* 0x18 */
    u8 pad2[0x4];
    int unk20;          /* 0x20 */
    u8 pad3[0x4];
    int unk28;          /* 0x28 */
    u8 pad4[0x4];
    int unk30[4];       /* 0x30 */
    int unk40[4];       /* 0x40 */
    u8 v50[0x10];       /* 0x50 */
    u8 v60[0x10];       /* 0x60 */
    u8 pad5[0x60];
    int unkD0;          /* 0xD0 */
    u8 pad6[0xC];
    int unkE0;          /* 0xE0 */
    u8 pad7[0x10];
    int unkF4;          /* 0xF4 */
    float unkF8;        /* 0xF8 */
    u8 pad8[0x4];
    int *queued;        /* 0x100 */
    int has_queued;      /* 0x104 */
    u8 pad9[0x4];
    int unk10C;         /* 0x10C */
    int unk110;         /* 0x110 */
    int unk114;         /* 0x114 */
    int unk118;         /* 0x118 */
    int unk11C;         /* 0x11C */
    u8 padA[0x14];
    int unk134;         /* 0x134 */
    u8 padB[0x8];
    int unk140;         /* 0x140 */
    u8 padC[0x200 - 0x144];
    u8 v200[0x30];      /* 0x200 */
} Menu;

typedef struct {
    u8 pad0[0xB0];
    float fB0;
    u8 pad1[0x218 - 0xB4];
    int i218;
    float f21C;
    u8 pad2[0x228 - 0x220];
    float f228;
    int i22C;
} View;

typedef struct {
    u8 pad0[0xC];
    int fC;
    int f10;
} Buffers;

typedef struct {
    u8 pad0[0x24C];
    int unk24C;
    int unk250;
    int bufs[4];
} Snd;

typedef struct {
    int a;
    int b;
    int *c;
    u8 pad[0x8C - 0xC];
    void (*init)(int);
    void (*upd)(void);
} Cutscene;

extern int g_collision_hit[];
extern Menu g_pause_menu_state;
extern View g_view_params;
extern Buffers g_loader_memory;
extern Snd g_map_overlay_state;
extern Cutscene g_pause_cinema_controller;
extern int g_pause_page_b[], g_pause_page_e[], g_pause_page_f[], g_menu_page_known_screen[], g_menu_page_options[], g_pause_page_d[], g_menu_page_pause[], g_menu_text_id_table[];
extern int g_menu_panel_flag[] __attribute__((sda));
extern int g_loader_state_word[] __attribute__((sda));
extern int g_packet_buffer_size[] __attribute__((sda));
extern int g_packet_buffer_offset __attribute__((sda));
extern int g_frame_counter_3[] __attribute__((sda));
extern int D_001B1598_sda __attribute__((sda));
extern int g_vram_frame_base[] __attribute__((sda));
extern int g_vram_fb_offset[] __attribute__((sda));   /* the two frame buffers */
extern int g_screen_width[] __attribute__((sda));   /* the screen size pair: [0] width, [1] height */
extern int g_menu_choice_table[] __attribute__((sda));
extern u8 g_pause_start_action_data[16] __attribute__((sda));
extern u8 g_pause_camera_scale_vec[16] __attribute__((sda));
extern u8 g_pause_camera_copy_vec[16] __attribute__((sda));
extern u8 g_pause_camera_state[];
extern u8 g_camera_eye_state[];

extern void menu_set_pause_scale_inverse(float);
extern void menu_start_action(void *);
extern void menu_draw_level_select_list(void);
extern int RebuildLevelSelectAvailability(int);
extern void menu_ring_list_step_forward(void *);
extern void map_set_current_and_refresh(int);
extern int menu_update_entry_states(void);
extern void FastVecScale(void *, void *, float);
extern void UpdateViewContext(void);
extern void cam_reset_active_position(void);
extern void gfx_build_view_matrices(void);
extern void gfx_wait_for_dma_status_bits(int);
extern int sceGsSyncV(int);
extern void menu_stream_chunk_table_init(int);
extern void gfx_reset_packet_buffer(void);
extern void map_reset_cache_and_reload(void);
extern void hud_unlink_bank_group(int);
extern void LoadStashedHudBanks(int);
extern void gfx_copy_image_to_gs_blocks(int, int, int);
extern void menu_upload_pause_background_to_gs(void);
extern void select_moby_context(int);
extern void mem_copy_aligned(void *, void *, int);

void menu_enter_pause_state_pal(void)
{
    int queued = 0;
    int s, j, k, n, vram_base, vram_next;
    int *buf_ptr;
    void (*upd)(void);

    g_collision_hit[4] |= 0x80000000;
    g_pause_menu_state.unk134 = 0;
    g_pause_menu_state.unkE0 = 0;
    switch (g_pause_menu_state.state) {
    case 0:
    case 7:
    case 9:
        break;
    case 2:
        queued = 1;
        g_pause_menu_state.page = g_pause_page_b;
        g_pause_menu_state.next = g_pause_page_b;
        break;
    case 3:
        g_pause_menu_state.page = 0;
        g_pause_menu_state.next = 0;
        break;
    case 4:
        g_pause_menu_state.page = g_pause_page_e;
        g_pause_menu_state.next = g_pause_page_e;
        queued = 1;
        menu_set_pause_scale_inverse(6.0f);
        break;
    case 11:
        g_pause_menu_state.next = g_pause_menu_state.page = g_pause_page_f;
        g_menu_panel_flag[0] = g_pause_menu_state.unk134 = 1;
        g_pause_menu_state.state = 5;
        menu_start_action(g_pause_start_action_data);
        break;
    case 5:
        g_pause_menu_state.page = g_pause_page_f;
        g_pause_menu_state.next = g_pause_page_f;
        g_pause_menu_state.unk134 = 1;
        g_menu_panel_flag[0] = 1;
        break;
    case 6:
        g_pause_menu_state.page = g_menu_page_known_screen;
        g_pause_menu_state.next = g_menu_page_known_screen;
        break;
    case 1:
        g_pause_menu_state.page = g_menu_page_options;
        g_pause_menu_state.next = g_menu_page_options;
        break;
    case 10:
        g_pause_menu_state.page = g_pause_page_d;
        g_pause_menu_state.next = g_pause_page_d;
        break;
    case 8:
        g_pause_menu_state.page = g_menu_page_pause;
        g_pause_menu_state.next = g_menu_page_pause;
        g_pause_cinema_controller.a = 0x18;
        g_pause_cinema_controller.b = 0x18;
        g_pause_cinema_controller.c = g_menu_text_id_table;
        g_pause_cinema_controller.upd = menu_draw_level_select_list;
        g_pause_cinema_controller.init = RebuildLevelSelectAvailability;
        g_pause_cinema_controller.init(0);
        menu_ring_list_step_forward(&g_pause_cinema_controller);
        break;
    }

    if (g_pause_menu_state.has_queued != 0) {
        g_loader_state_word[0] = g_pause_menu_state.unk140;
        g_pause_menu_state.page = g_pause_menu_state.queued;
        g_pause_menu_state.next = g_pause_menu_state.queued;
        if (g_pause_menu_state.state == 2 || g_pause_menu_state.state == 4) {
            map_set_current_and_refresh(g_pause_menu_state.unkF4);
            queued = 1;
            menu_update_entry_states();
        }
        g_pause_menu_state.queued = 0;
        g_pause_menu_state.has_queued = 0;
    }

    {
        u8 *cam_ptr = g_pause_camera_state;
        FastVecScale(cam_ptr, g_pause_camera_scale_vec, 1.0f);
        qcopy(cam_ptr - 0x10, g_pause_camera_copy_vec);
        cam_ptr += 0x20;
        qzero_nc(cam_ptr);
    }
    qzero_nc(g_pause_camera_state + 0x10);
    qcopy(g_pause_menu_state.v50, g_camera_eye_state);
    qcopy(g_pause_menu_state.v60, g_camera_eye_state + 0x10);
    mem_copy_aligned(g_pause_menu_state.v200, g_camera_eye_state + 0x230, 0x30);
    {
        float zfar = 524288.0f;
        float fog = 255.0f;
        float scale = 0.62f;
        g_pause_menu_state.unkF8 = g_view_params.fB0;
        g_view_params.fB0 = scale;
        g_view_params.f21C = zfar;
        g_view_params.f228 = fog;
        g_view_params.i22C = 0;
        g_view_params.i218 = 0;
    }
    UpdateViewContext();
    cam_reset_active_position();
    gfx_build_view_matrices();
    gfx_wait_for_dma_status_bits(1);
    sceGsSyncV(0);
    D_001B1598_sda = g_frame_counter_3[0] + 1;

    if (queued) {
        int buf_a, buf_b, buf_c, buf_d;
        buf_a = g_loader_memory.fC + 0x30000;
        buf_b = g_loader_memory.f10 + 0x30000;
        buf_c = buf_a + 0x3C000;
        buf_d = buf_b + 0xE0000;
        g_pause_menu_state.unk10C = buf_c + 0x11800;
        g_packet_buffer_size[0] = 0x30000;
        g_pause_menu_state.unk114 = buf_a;
        g_pause_menu_state.unk20 = buf_b;
        g_pause_menu_state.unk118 = buf_c;
        g_pause_menu_state.unk11C = buf_d;
        g_pause_menu_state.unk110 = buf_d;
        menu_stream_chunk_table_init(0);
    } else {
        int buf_a, buf_b, buf_c, buf_d, buf_e, buf_f;
        buf_a = g_loader_memory.fC + 0x60000;
        buf_b = g_loader_memory.f10 + 0x60000;
        buf_b = buf_b + 0xC000;
        buf_a = buf_a + 0xC000;
        buf_c = buf_a + 0x30000;
        buf_d = buf_b + 0xE0000;
        buf_e = buf_c + 0xC1000;
        buf_f = buf_d + 0x60800;
        g_pause_menu_state.unk10C = buf_e;
        g_packet_buffer_size[0] = 0x60000;
        g_pause_menu_state.unk114 = buf_a;
        g_pause_menu_state.unk20 = buf_b;
        g_pause_menu_state.unk118 = buf_c;
        g_pause_menu_state.unk11C = buf_d;
        g_pause_menu_state.unk110 = buf_f;
        menu_stream_chunk_table_init(1);
    }
    g_packet_buffer_offset = 0x2000;
    gfx_reset_packet_buffer();
    if (queued) {
        map_reset_cache_and_reload();
    }
    hud_unlink_bank_group(0);
    if (queued) {
        LoadStashedHudBanks(1);
    } else {
        LoadStashedHudBanks(0);
    }
    if (g_pause_menu_state.unkD0 == 0) {
        gfx_copy_image_to_gs_blocks(g_pause_menu_state.unk20, g_vram_fb_offset[1], g_screen_width[1] << 11);
    } else {
        menu_upload_pause_background_to_gs();
    }
    vram_base = g_vram_frame_base[0];
    g_pause_menu_state.unk28 = vram_base;
    if (queued) {
        g_map_overlay_state.unk24C = vram_base;
        vram_next = vram_base + 0x40000;
        g_map_overlay_state.unk250 = vram_next;
        g_vram_frame_base[0] = vram_next + 0x400;
        for (j = 0; j < 4; j++) {
            int buf_addr = g_vram_frame_base[0];
            g_map_overlay_state.bufs[j] = buf_addr;
            g_vram_frame_base[0] = buf_addr + 0x4000;
        }
    } else {
        int z;
        g_map_overlay_state.unk24C = 0;
        g_map_overlay_state.unk250 = 0;
        buf_ptr = &g_map_overlay_state.bufs[3];
        for (z = 0; z < 4; z++) {
            *buf_ptr = 0;
            buf_ptr--;
        }
    }
    select_moby_context(1);
    for (k = 0; k < 4; k++) {
        g_pause_menu_state.unk40[k] = g_menu_choice_table[k];
        g_pause_menu_state.unk30[k] = g_menu_choice_table[k];
    }
}
