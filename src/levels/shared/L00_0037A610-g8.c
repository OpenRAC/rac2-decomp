#include "common.h"

/* Partial layouts measured from this renderer and its neighboring menu functions. */
typedef unsigned int Quad __attribute__((mode(TI)));
typedef struct {
    char pad00[8];
    int state, initialize;
    int capture;
    char * buffer, *end;
    char pad1c[4];
    char * preview0, *preview1, *moby, *models;
    char pad30[4];
    int count;
    char pad38[4];
    char * text;
    char pad40[0x10];
    int mode, selected0, selected1;
    char pad5c[4];
    int use_camera;
    char pad64[0x24];
    int draw;
    char pad8c[4];
    int field90, field94;
    char pad98[0x48];
    Quad saved;
    char padf0[0x654];
    int auxiliary;
} MenuState;
extern char g_purchase_menu_model[];

#define menu ((MenuState *)D_L00_0022F7C0)
typedef struct {
    char pad00[0x370];
    float x;
    char pad374[0x10];
    float y;
    char pad388[0x10];
    float z, w;
} CameraState;
extern CameraState g_scalar_transition_state;
extern char g_hero_saved_vector[];
/* The incomplete array preserves the retail absolute address macro. */
extern Quad g_shop_quad_buffer[] __attribute__((sda));
extern char g_scratch_vec_pair[], g_scratch_vec_secondary[];
typedef struct {
    int words[2];
} Pair;
extern Pair g_shop_pair_table[];
extern int g_screen_width[] __attribute__((sda));
extern int g_screen_height[] __attribute__((sda));
extern int g_vram_display_address[] __attribute__((sda));
extern int g_shop_color_start_r[] __attribute__((sda));
extern int g_shop_color_start_g[] __attribute__((sda));
extern int g_shop_color_start_b[] __attribute__((sda));
extern int g_shop_color_end_r[] __attribute__((sda));
extern int g_shop_color_end_g[] __attribute__((sda));
extern int g_shop_color_end_b[] __attribute__((sda));
extern char * g_bolt_counter_base MACRO_ADDR;
extern float g_fast_math_ratio[];
extern float g_shop_blend_factor __attribute__((sda));
extern float g_shop_scale_start __attribute__((sda));
extern float g_shop_scale_end __attribute__((sda));
extern float g_menu_slide_scale __attribute__((sda));
extern int g_screen_overlay_color MACRO_ADDR;
extern int g_ring_animation_counter MACRO_ADDR;
extern int g_shop_scene_param __attribute__((sda));
extern int sceGsSyncV(int);
extern void level_init_record_from_object();
extern void gfx_build_view_matrices();
extern void UpdateViewContext(void);
extern void gfx_write_clear_color_packets();
extern void RenderFrame();
extern void SetupGifPaging();
extern void DoGifPaging();
extern void gfx_draw_item_with_pass();
extern void mem_fast_helper_b();
extern void copy_matrix3x4();
extern void gfx_append_draw_list_buffer_tag();
extern void hud_update_record_handlers();
extern void level_run_callbacks_and_draw();
extern void mat_transform_array();
extern void PatchMobyGifs();
extern void mem_fill_scratch_area();
extern void mem_save_scratch_area();
extern void mem_restore_scratch_area();
extern void DrawMobysSetup();
extern void tex_upload_object_textures();
extern int tex_run_upload_and_setup();
extern void gfx_pack_render_command_fields();
extern void func_002A0F48();
extern void func_002A10E8();
extern int math_ping_pong_blend_values();
extern void text_draw_scrolling_help();
extern void DrawVendorItemSelectList();
extern void DrawAmmoSelectList();
extern void shop_draw_item_icon_strip();
extern void shop_draw_vendor_item_list();
extern void DrawVendorPurchasePrompt();
extern void shop_draw_price_and_description();
extern void shop_draw_upgrade_price_lines();
extern void DrawSelectedItemInfoPanel();
extern void DrawPurchaseActionPrompts();
extern void DrawItemPurchaseButtonLabels();
extern void shop_draw_buy_back_labels();
extern void DrawSelectedItemPurchasePanel();
extern void DrawVendorPurchasePanel();
extern void DrawPurchaseAffordabilityPrompt();
extern void DrawSelectedItemLimitStatus();
extern void shop_draw_item_limit_text_box();
extern void shop_step_message_states();
extern void PrepareVendorSelectionPreview();
extern void ref_L00_0037A610_00();
extern void gfx_swap_packet_buffer();
extern void SubmitBufferedDmaChain(void);
extern void gfx_wait_for_dma_status_bits();
extern void VU1_addGSregister(int, unsigned long long);
extern void gfx_set_scissor_clamped();
extern void gfx_upload_image_to_gs_packets();
extern void gfx_draw_scaled_object_two_axes(int, int, float, float, float, float, float);
extern void *table_find_by_id();
/* Initialize the selected menu view, draw its layered background, then render its models. */
void shop_draw_purchase_menu_scene(void)
{
    int ids[4];
    Pair pair;
    unsigned char matrices[128] __attribute__((aligned(16)));
    int red, green, blue, color;
    float scale;
    int handle;
    gfx_append_draw_list_buffer_tag(0);
    g_fast_math_ratio[0] = 0.62f;
    UpdateViewContext();

    switch (menu->state) {
    case 0:
        if (menu->initialize)
            *(unsigned short *)(menu->moby + 0x34) |= 1;
        g_screen_overlay_color = 0x100ff;
        if (menu->initialize)
            g_screen_overlay_color = 127;
        RenderFrame();
        *(unsigned short *)(menu->moby + 0x34) &= 0xfffe;
        if (!menu->initialize)
            break;
        {
            menu->state = 1;
            menu->initialize = 0;
            gfx_wait_for_dma_status_bits(1);
            sceGsSyncV(0);
            g_ring_animation_counter = g_ring_animation_counter + 1;
            SubmitBufferedDmaChain();
            gfx_swap_packet_buffer();
            g_shop_scene_param = 0x60000;
            gfx_draw_item_with_pass(menu->capture);
            if (menu->use_camera) {
                qcopy(&menu->saved, g_hero_saved_vector);
                /* Save the three camera basis vectors before resetting the view. */
                {
                    Quad * src = (Quad *)(g_hero_saved_vector + 0x220);
                    Quad * dst = (Quad *)g_shop_quad_buffer;
                    dst[0] = src[0];
                    dst[1] = src[1];
                    dst[2] = src[2];
                }
                qzero(g_hero_saved_vector + 0x220);
                qzero(g_scratch_vec_pair);
                qzero(g_scratch_vec_secondary);
                g_scalar_transition_state.x = 1;
                g_scalar_transition_state.y = 1;
                g_scalar_transition_state.z = 1;
                g_scalar_transition_state.w = 1;
                gfx_build_view_matrices();
            }
            {
                char * base = menu->buffer;
                menu->preview1 = base + 0x800;
                menu->preview0 = base;
                menu->models = base + 0x1000;
                menu->text = base + 0x2400;
                mem_fast_helper_b(base + 0x2400, 0x400);
            }
            menu->field94 = 0;
            menu->field90 = 0;
            menu->end = menu->text + 0x400;
            PrepareVendorSelectionPreview();
        }
        /* Initialization falls through into the first rendered frame. */
    case 1:
        gfx_upload_image_to_gs_packets(menu->capture, g_vram_display_address[0], g_screen_height[0] << 11);
        SetupGifPaging(0);
        gfx_build_view_matrices();
        gfx_write_clear_color_packets();
        if (g_shop_blend_factor >= 1.0f && menu->draw) {
            DrawMobysSetup();
            mem_fill_scratch_area();
            mem_save_scratch_area();
        }
        VU1_addGSregister(0x42, 0x8000000044ULL);
        {
            float dr = (float)(g_shop_color_end_r[0] - g_shop_color_start_r[0]);
            float dg = (float)(g_shop_color_end_g[0] - g_shop_color_start_g[0]);
            float db = (float)(g_shop_color_end_b[0] - g_shop_color_start_b[0]);
            float fr = (float)g_shop_color_start_r[0] + dr * g_shop_blend_factor;
            float fb = (float)g_shop_color_start_b[0] + db * g_shop_blend_factor;
            float fg = (float)g_shop_color_start_g[0] + dg * g_shop_blend_factor;
            red = (int)fr;
            green = (int)fg;
            blue = (int)fb;
        }
        scale = g_shop_scale_start + (g_shop_scale_end - g_shop_scale_start) * g_shop_blend_factor;
        if (menu->mode == 0) {
            ids[0] = 0x67;
            ids[1] = 0x68;
            ids[2] = 0x69;
            ids[3] = 0x6a;
        } else if (menu->mode == 3) {
            ids[0] = 0x75;
            ids[1] = 0x76;
            ids[2] = 0x77;
            ids[3] = 0x78;
        } else if (menu->mode == 2) {
            ids[0] = 0x7c;
            ids[1] = 0x7d;
            ids[2] = 0x7e;
            ids[3] = 0x7f;
        } else if (menu->mode == 1) {
            ids[0] = 0x79;
            ids[1] = 0x7a;
            ids[2] = 0x7b;
        }
        handle = table_find_by_id(g_bolt_counter_base + 0x8710, ids[0]);
        gfx_draw_scaled_object_two_axes(handle, (red << 24) | 0x442d00, (float)(g_screen_width[0] >> 1), (float)(g_screen_height[0] >> 1), scale, scale, 0.0f);
        handle = table_find_by_id(g_bolt_counter_base + 0x8710, ids[1]);
        gfx_draw_scaled_object_two_axes(handle, (green << 24) | 0x241700, (float)(g_screen_width[0] >> 1), (float)(g_screen_height[0] >> 1), scale, scale, 0.0f);
        handle = table_find_by_id(g_bolt_counter_base + 0x8710, ids[2]);
        color = (blue << 24) | 0xf0c070;
        gfx_draw_scaled_object_two_axes(handle, color, (float)(g_screen_width[0] >> 1), (float)(g_screen_height[0] >> 1), scale, scale, 0.0f);
        if (menu->mode != 1) {
            handle = table_find_by_id(g_bolt_counter_base + 0x8710, ids[3]);
            gfx_draw_scaled_object_two_axes(handle, color, (float)(g_screen_width[0] >> 1), (float)(g_screen_height[0] >> 1), scale, scale, 0.0f);
        }
        hud_update_record_handlers();
        level_run_callbacks_and_draw();
        if (g_shop_blend_factor >= 1.0f) {
            ref_L00_0037A610_00();
            if (menu->mode == 0) {
                DrawVendorPurchasePrompt();
                DrawPurchaseActionPrompts();
                DrawVendorPurchasePanel();
                DrawVendorItemSelectList();
                text_draw_scrolling_help();
                if (menu->auxiliary)
                    shop_step_message_states();
                if (menu->draw) {
                    gfx_set_scissor_clamped(158, 360, 115, 206);
                    tex_upload_object_textures(menu->models, 1);
                    mem_restore_scratch_area();
                    tex_run_upload_and_setup();
                }
            } else if (menu->mode == 3) {
                shop_draw_price_and_description();
                DrawItemPurchaseButtonLabels();
                DrawPurchaseAffordabilityPrompt();
                shop_draw_item_icon_strip();
                text_draw_scrolling_help();
                if (menu->draw) {
                    gfx_set_scissor_clamped(0, g_screen_width[0] - 1, 0, g_screen_height[0] - 1);
                    level_init_record_from_object(menu->models, menu->models + 0x100);
                    pair = g_shop_pair_table[0];
                    mat_transform_array(menu->models, 2, &pair, matrices);
                    {
                        char * models = menu->models;
                        qcopy(models + 0x210, matrices + 0x30);
                        qcopy(models + 0x310, matrices + 0x70);
                        func_002A0F48(models + 0x200);
                    }
                    copy_matrix3x4(menu->models + 0x2c0, matrices);
                    copy_matrix3x4(menu->models + 0x3c0, matrices + 0x40);
                    func_002A10E8(menu->models + 0x200);
                    func_002A10E8(menu->models + 0x300);
                    tex_upload_object_textures(menu->models, menu->count + 2);
                    mem_restore_scratch_area();
                    tex_run_upload_and_setup();
                }
            } else if (menu->mode == 2) {
                DrawSelectedItemPurchasePanel();
                shop_draw_item_limit_text_box();
                shop_draw_vendor_item_list();
                text_draw_scrolling_help();
                if (menu->draw) {
                    gfx_set_scissor_clamped(32, 386, (int)(g_menu_slide_scale * 64.0f + 0.5f), (int)(g_menu_slide_scale * 229.0f + 0.5f));
                    handle = math_ping_pong_blend_values(0xffffff, 0x606060, 30, 1, 0);
                    if (menu->selected0 != -1)
                        gfx_pack_render_command_fields(menu->models + (menu->selected0 << 8), handle, 14, 14, 0);
                    if (menu->selected1 != -1)
                        gfx_pack_render_command_fields(menu->models + (menu->selected1 << 8), handle, 14, 14, 0);
                    tex_upload_object_textures(menu->models, menu->count);
                    mem_restore_scratch_area();
                    tex_run_upload_and_setup();
                    gfx_set_scissor_clamped(0, g_screen_width[0] - 1, 0, g_screen_height[0] - 1);
                    DrawSelectedItemInfoPanel();
                }
            } else if (menu->mode == 1) {
                shop_draw_upgrade_price_lines();
                shop_draw_buy_back_labels();
                DrawSelectedItemLimitStatus();
                DrawAmmoSelectList();
                text_draw_scrolling_help();
                if (menu->draw) {
                    gfx_set_scissor_clamped(158, 360, 115, 206);
                    tex_upload_object_textures(menu->models, 1);
                    mem_restore_scratch_area();
                    tex_run_upload_and_setup();
                }
            }
            gfx_set_scissor_clamped(0, g_screen_width[0] - 1, 0, g_screen_height[0] - 1);
        }
        DoGifPaging();
        gfx_wait_for_dma_status_bits(16);
        PatchMobyGifs();
        break;
    }
}
