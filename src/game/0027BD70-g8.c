#include "common.h"

/* Incomplete-array views: the macro form (lui plus low half in ordinary flow, one $gp
   instruction in a delay slot), which is how retail reaches these resident words. */
extern int g_render_layer_flags[] MACRO_ADDR;
extern int g_gfx_pass_mode[] MACRO_ADDR;
extern int g_current_game_mode[] MACRO_ADDR;
extern float g_screen_fade[] MACRO_ADDR;
extern float g_screen_flash_alpha[] MACRO_ADDR;

extern char *ref_0027BD70_00[] MACRO_ADDR;
extern int g_world_draw_callback_count[] MACRO_ADDR, g_overlay_draw_callback_count[] MACRO_ADDR, g_early_draw_callback_count[] MACRO_ADDR;
extern int g_late_draw_callback_count[] MACRO_ADDR, g_final_draw_callback_count[] MACRO_ADDR;
extern int g_screen_tint_params[] SDATA(D_001A8770);
extern char g_water_vu_program[];
extern unsigned short g_water_vu_data_size NOT_SDA;
extern int ref_0027BD70_01 NOT_SDA;
extern unsigned long ref_0027BD70_02 NOT_SDA;
extern float g_hero_state[];
extern float ref_0027BD70_03[];
extern char ref_0027BD70_04[], ref_0027BD70_05[];
extern int g_screen_height[] MACRO_ADDR;
extern int ref_0027BD70_06 NOT_SDA;
extern unsigned char g_clear_color_r[] MACRO_ADDR, g_clear_color_g[] MACRO_ADDR;
extern unsigned char g_clear_color_b[] MACRO_ADDR, g_clear_color_a[] MACRO_ADDR;
extern int g_screen_tint_flag_a __attribute__((sda)), g_screen_tint_flag_b __attribute__((sda));
extern char g_gfx_dma_chain_buffer[];
extern int g_is_pal_video[] MACRO_ADDR;
extern float g_tick_time_scale[] MACRO_ADDR;
extern char ref_0027BD70_07[], ref_0027BD70_08[];
extern int g_vis_fallback_mode[] MACRO_ADDR;

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
extern void DrawLightQuads(void);
extern void part_draw_all(void);
extern void gfx_run_overlay_draw_callbacks(void);
extern void DrawGlowSprites(void);
extern void gfx_run_final_draw_callbacks(void);
extern void hud_draw_reticle_and_markers(void);
extern void gfx_queue_first_strip_packet(void);
extern void DrawLetterboxBars(void);
extern void level_run_callbacks_and_draw(void);
extern void hud_update_record_handlers(void);
extern void DrawSubtitleBox(void);
extern void DrawSubtitles(void);
extern void gfx_draw_screen_stripe_effect(void);
extern void PatchTfragGifs(void);
extern void func_002F3E78(void);
extern void gfx_apply_object_row_overrides(void);
extern void patch_shrub_gifs(void);
extern void PatchMobyGifs(void);
extern void gfx_apply_display_config(void);

/* Draws one whole frame: all the game layers, the overlays, the subtitles and the fade effects, in order. */
void RenderFrame(void)
{
    char text[64];
    float ticks;

    if (!ref_0027BD70_00[0] || *(short *)(ref_0027BD70_00[0] + 4) ||
        ((g_render_layer_flags[0] ^ 1) & 1))
        gfx_append_draw_list_buffer_tag(0);
    gfx_build_view_matrices();
    moby_update_watched_objects();
    vis_update_by_mode();
    gfx_write_clear_color_packets();
    g_gfx_pass_mode[0] = -1;
    if (ref_0027BD70_00[0] && (g_render_layer_flags[0] & 1))
        level_init_rendering();
    if (g_render_layer_flags[0] & 2)
        gfx_begin_render_frame();
    append_dma_tag(0x02010000);
    if (g_render_layer_flags[0] & 4)
        gfx_draw_level_render_passes();
    append_dma_tag(0x02020000);
    if (g_early_draw_callback_count[0]) {
        gfx_append_vu1_preset_c();
        SetupGifPaging(1);
        gfx_run_early_draw_callbacks();
        DoGifPaging();
        gfx_append_vu1_preset_b();
    }
    if (g_render_layer_flags[0] & 8)
        gfx_begin_render_setup();
    append_dma_tag(0x02040000);
    if (g_screen_tint_params[0])
        gfx_draw_screen_tint_step(g_screen_tint_params);
    if (g_late_draw_callback_count[0]) {
        gfx_append_vu1_preset_c();
        SetupGifPaging(1);
        gfx_run_late_draw_callbacks();
        DoGifPaging();
        gfx_append_vu1_preset_b();
    }
    if (g_render_layer_flags[0] & 0x10) {
        if (g_current_game_mode[0] == 2)
            gfx_render_object_preview_to_texture();
        else
            tex_upload_main_textures();
    }
    append_dma_tag(0x02080000);
    SetupGifPaging(0);
    if ((g_render_layer_flags[0] & 0x20) && g_gfx_pass_mode[0] != 6) {
        VU1_addDataRef(g_water_vu_program, g_water_vu_data_size);
        g_gfx_pass_mode[0] = 6;
    }
    if (g_render_layer_flags[0] & 0x20) {
        gfx_append_vu1_preset_c();
        if (g_world_draw_callback_count[0])
            gfx_run_world_draw_callbacks();
        VU1_addGSregister(0x42, 0x8000000048UL);
        DrawLensFlare();
        gfx_append_vu1_preset_c();
        DrawLightQuads();
        VU1_addGSregister(8, 5);
        gfx_append_vu1_preset_c();
        FlushCache(0);
        part_draw_all();
        g_gfx_pass_mode[0] = 9;
        if (g_overlay_draw_callback_count[0]) {
            gfx_append_vu1_preset_c();
            gfx_run_overlay_draw_callbacks();
        }
        DrawGlowSprites();
        if (g_final_draw_callback_count[0]) {
            gfx_append_vu1_preset_c();
            gfx_run_final_draw_callbacks();
        }
        VU1_addGSregister(0x42, 0x8000000044UL);
        hud_draw_reticle_and_markers();
    }
    gfx_queue_first_strip_packet();
    gfx_append_vu1_preset_c();
    if ((g_render_layer_flags[0] & 0x180) && !request_is_current_slot(3)) {
        VU1_addGSregister(0x47, 0x33001);
        DrawLetterboxBars();
        if (g_render_layer_flags[0] & 0x80) {
            level_run_callbacks_and_draw();
            hud_update_record_handlers();
            DrawSubtitleBox();
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
    if (g_render_layer_flags[0] & 0x40) {
        VU1_addGSregister(0x42, 0x8000000044UL);
        if (ref_0027BD70_06)
            gfx_set_clear_color_packet(g_clear_color_r[0], g_clear_color_g[0], g_clear_color_b[0], g_clear_color_a[0]);
        if (g_screen_fade[0] > 0.0f) {
            if (g_screen_fade[0] > 1.0f)
                g_screen_fade[0] = 1.0f;
            gfx_set_clear_color_packet(0, 0, 0, FloatToInt(g_screen_fade[0] * 128.0f));
        }
        if (g_screen_flash_alpha[0] > 0.0f) {
            if (g_screen_flash_alpha[0] > 1.0f)
                g_screen_flash_alpha[0] = 1.0f;
            gfx_set_clear_color_packet(255, 255, 255, FloatToInt(g_screen_flash_alpha[0] * 128.0f));
        }
        if (g_screen_tint_flag_a && g_screen_tint_flag_b)
            gfx_draw_screen_stripe_effect();
    }
    gfx_start_dma_channel0_and_wait(g_gfx_dma_chain_buffer);
    FlushCache(0);
    ticks = IntToFloat(((int)T1_COUNT));
    g_tick_time_scale[0] = ticks * (g_is_pal_video[0] ? (1.0f / 11520.0f) : (1.0f / 9600.0f));
    gfx_wait_for_dma_status_bits(2);
    if (g_render_layer_flags[0] & 2) {
        func_002F0468(ref_0027BD70_07);
        PatchTfragGifs();
    }
    gfx_wait_for_dma_status_bits(4);
    if (g_render_layer_flags[0] & 4) {
        func_002F3E78();
        gfx_apply_object_row_overrides();
    }
    gfx_wait_for_dma_status_bits(8);
    if (g_render_layer_flags[0] & 8) {
        shrub_process_render_data(ref_0027BD70_08);
        patch_shrub_gifs();
    }
    gfx_wait_for_dma_status_bits(16);
    if (g_render_layer_flags[0] & 16)
        PatchMobyGifs();
    gfx_apply_display_config();
    g_vis_fallback_mode[0] = 0;
}
