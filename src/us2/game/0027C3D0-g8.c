#include "include_asm.h"

#include "common.h"
extern int D_001B1594[] MACRO_ADDR;
extern int D_001B169C[] MACRO_ADDR;
extern int g_current_game_mode[] MACRO_ADDR;
extern float g_screen_fade[] MACRO_ADDR;
extern float D_001B15A4[] MACRO_ADDR;
extern char *ref_0027BD70_00[] MACRO_ADDR;
extern int D_001B1608[] MACRO_ADDR, D_001B160C[] MACRO_ADDR, D_001B1610[] MACRO_ADDR;
extern int D_001B1614[] MACRO_ADDR, D_001B1638[] MACRO_ADDR;
extern int D_001A8770[] SDATA(D_001A8770);
extern char D_0010FFC0[];
extern unsigned short D_0010FFB0 NOT_SDA;
extern int ref_0027BD70_01 NOT_SDA;
extern unsigned long ref_0027BD70_02 NOT_SDA;
extern float g_hero_state[];
extern float ref_0027BD70_03[];
extern char ref_0027BD70_04[], ref_0027BD70_05[];
extern int g_screen_height[] MACRO_ADDR;
extern int ref_0027BD70_06 NOT_SDA;
extern unsigned char D_001AD580[] MACRO_ADDR, D_001AD581[] MACRO_ADDR;
extern unsigned char D_001AD582[] MACRO_ADDR, D_001AD583[] MACRO_ADDR;
extern int D_001A86F4 __attribute__((sda)), D_001A8758 __attribute__((sda));
extern char D_00100AE0[];
extern int g_is_pal_video[] MACRO_ADDR;
extern float D_001B1690[] MACRO_ADDR;
extern char ref_0027BD70_07[], ref_0027BD70_08[];
extern int D_001B170C[] MACRO_ADDR;
extern void gfx_append_draw_list_buffer_tag(int);
extern void SetupGifPaging(int);
extern void append_dma_tag(int);
extern void VU1_addGSregister(int, unsigned long);
extern void gfx_draw_screen_tint_step(void *);
extern void VU1_addDataRef(void *, int);
extern void FlushCache(int);
extern int request_is_current_slot(int);
extern double __extendsfdf2(float);
extern int sprintf(char *, char *, ...);
extern void text_draw_medium(int, int, long, char *, int);
extern void gfx_set_clear_color_packet(int, int, int, int);
extern int FloatToInt(float);
extern void gfx_start_dma_channel0_and_wait(void *);
extern float IntToFloat(int);
extern void gfx_wait_for_dma_status_bits(int);
extern void func_002F0468(void *);
extern void shrub_process_render_data(void *);
extern void gfx_build_view_matrices(void);
extern void moby_update_watched_objects(void);
extern void vis_update_by_mode(void);
extern void gfx_write_clear_color_packets(void);
extern void level_init_rendering(void);
extern void gfx_begin_render_frame(void);
extern void gfx_draw_level_render_passes(void);
extern void gfx_append_vu1_preset_c(void);
extern void gfx_run_early_draw_callbacks(void);
extern void DoGifPaging(void);
extern void gfx_append_vu1_preset_b(void);
extern void gfx_begin_render_setup(void);
extern void gfx_run_late_draw_callbacks(void);
extern void gfx_render_object_preview_to_texture(void);
extern void tex_upload_main_textures(void);
extern void gfx_run_world_draw_callbacks(void);
extern void DrawLensFlare(void);
extern void func_US2_0027D7D0(void);
extern void part_draw_all(void);
extern void gfx_run_overlay_draw_callbacks(void);
extern void DrawGlowSprites(void);
extern void gfx_run_final_draw_callbacks(void);
extern void hud_draw_reticle_and_markers(void);
extern void gfx_queue_first_strip_packet(void);
extern void DrawLetterboxBars(void);
extern void func_US2_0029CD18(void);
extern void hud_update_record_handlers(void);
extern void func_US2_0028A4E8(void);
extern void DrawSubtitles(void);
extern void gfx_draw_screen_stripe_effect(void);
extern void PatchTfragGifs(void);
extern void func_002F3E78(void);
extern void gfx_apply_object_row_overrides(void);
extern void patch_shrub_gifs(void);
extern void PatchMobyGifs(void);
extern void gfx_apply_display_config(void);

void func_US2_0027C3D0(void)
{
    char text[64];
    float ticks;

    if (!ref_0027BD70_00[0] || *(short *)(ref_0027BD70_00[0] + 4) ||
        ((D_001B1594[0] ^ 1) & 1))
        gfx_append_draw_list_buffer_tag(0);
    gfx_build_view_matrices();
    moby_update_watched_objects();
    vis_update_by_mode();
    gfx_write_clear_color_packets();
    D_001B169C[0] = -1;
    if (ref_0027BD70_00[0] && (D_001B1594[0] & 1))
        level_init_rendering();
    if (D_001B1594[0] & 2)
        gfx_begin_render_frame();
    append_dma_tag(0x02010000);
    if (D_001B1594[0] & 4)
        gfx_draw_level_render_passes();
    append_dma_tag(0x02020000);
    if (D_001B1610[0]) {
        gfx_append_vu1_preset_c();
        SetupGifPaging(1);
        gfx_run_early_draw_callbacks();
        DoGifPaging();
        gfx_append_vu1_preset_b();
    }
    if (D_001B1594[0] & 8)
        gfx_begin_render_setup();
    append_dma_tag(0x02040000);
    if (D_001A8770[0])
        gfx_draw_screen_tint_step(D_001A8770);
    if (D_001B1614[0]) {
        gfx_append_vu1_preset_c();
        SetupGifPaging(1);
        gfx_run_late_draw_callbacks();
        DoGifPaging();
        gfx_append_vu1_preset_b();
    }
    if (D_001B1594[0] & 0x10) {
        if (g_current_game_mode[0] == 2)
            gfx_render_object_preview_to_texture();
        else
            tex_upload_main_textures();
    }
    append_dma_tag(0x02080000);
    SetupGifPaging(0);
    if ((D_001B1594[0] & 0x20) && D_001B169C[0] != 6) {
        VU1_addDataRef(D_0010FFC0, D_0010FFB0);
        D_001B169C[0] = 6;
    }
    if (D_001B1594[0] & 0x20) {
        gfx_append_vu1_preset_c();
        if (D_001B1608[0])
            gfx_run_world_draw_callbacks();
        VU1_addGSregister(0x42, 0x8000000048UL);
        DrawLensFlare();
        gfx_append_vu1_preset_c();
        func_US2_0027D7D0();
        VU1_addGSregister(8, 5);
        gfx_append_vu1_preset_c();
        FlushCache(0);
        part_draw_all();
        D_001B169C[0] = 9;
        if (D_001B160C[0]) {
            gfx_append_vu1_preset_c();
            gfx_run_overlay_draw_callbacks();
        }
        DrawGlowSprites();
        if (D_001B1638[0]) {
            gfx_append_vu1_preset_c();
            gfx_run_final_draw_callbacks();
        }
        VU1_addGSregister(0x42, 0x8000000044UL);
        hud_draw_reticle_and_markers();
    }
    gfx_queue_first_strip_packet();
    gfx_append_vu1_preset_c();
    if ((D_001B1594[0] & 0x180) && !request_is_current_slot(3)) {
        VU1_addGSregister(0x47, 0x33001);
        DrawLetterboxBars();
        if (D_001B1594[0] & 0x80) {
            func_US2_0029CD18();
            hud_update_record_handlers();
            func_US2_0028A4E8();
        }
    }
    if (g_current_game_mode[0] == 2)
        DrawSubtitles();
    if (ref_0027BD70_01 && (ref_0027BD70_02 & 5) == 5) {
        sprintf(text, ref_0027BD70_04,
            __extendsfdf2(g_hero_state[32]),
            __extendsfdf2(g_hero_state[33]),
            __extendsfdf2(g_hero_state[34]));
        text_draw_medium(24, g_screen_height[0] - 54, 0x80F0F0F0L, text, -1);
        sprintf(text, ref_0027BD70_05,
            __extendsfdf2(ref_0027BD70_03[80]),
            __extendsfdf2(ref_0027BD70_03[81]),
            __extendsfdf2(ref_0027BD70_03[82]));
        text_draw_medium(24, g_screen_height[0] - 40, 0x80F0F0F0L, text, -1);
    }
    DoGifPaging();
    if (D_001B1594[0] & 0x40) {
        VU1_addGSregister(0x42, 0x8000000044UL);
        if (ref_0027BD70_06)
            gfx_set_clear_color_packet(D_001AD580[0], D_001AD581[0], D_001AD582[0], D_001AD583[0]);
        if (g_screen_fade[0] > 0.0f) {
            if (g_screen_fade[0] > 1.0f)
                g_screen_fade[0] = 1.0f;
            gfx_set_clear_color_packet(0, 0, 0, FloatToInt(g_screen_fade[0] * 128.0f));
        }
        if (D_001B15A4[0] > 0.0f) {
            if (D_001B15A4[0] > 1.0f)
                D_001B15A4[0] = 1.0f;
            gfx_set_clear_color_packet(255, 255, 255, FloatToInt(D_001B15A4[0] * 128.0f));
        }
        if (D_001A86F4 && D_001A8758)
            gfx_draw_screen_stripe_effect();
    }
    gfx_start_dma_channel0_and_wait(D_00100AE0);
    FlushCache(0);
    ticks = IntToFloat(((int)T1_COUNT));
    D_001B1690[0] = ticks * (g_is_pal_video[0] ? (1.0f / 11520.0f) : (1.0f / 9600.0f));
    gfx_wait_for_dma_status_bits(2);
    if (D_001B1594[0] & 2) {
        func_002F0468(ref_0027BD70_07);
        PatchTfragGifs();
    }
    gfx_wait_for_dma_status_bits(4);
    if (D_001B1594[0] & 4) {
        func_002F3E78();
        gfx_apply_object_row_overrides();
    }
    gfx_wait_for_dma_status_bits(8);
    if (D_001B1594[0] & 8) {
        shrub_process_render_data(ref_0027BD70_08);
        patch_shrub_gifs();
    }
    gfx_wait_for_dma_status_bits(16);
    if (D_001B1594[0] & 16)
        PatchMobyGifs();
    gfx_apply_display_config();
    D_001B170C[0] = 0;
}
