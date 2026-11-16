#include "common.h"

/* func_US2_002D4ED8, the v2.00 copy of func_002D3FA0: draws the preview menu (four logo
   sprite layers, the frame rectangles and corners, the header text and the two rows of
   choice icons, func_US2_002D4D38 for each unlocked choice either side of D_001ABA74), then
   renders the preview model. v2.00 drops the display scaling of every coordinate, reads the
   logo layers' scale from D_001B2688 and uses text 0x30A8/0x30A9 and 0x2BE5.

   Each logo layer is drawn by the inline draw_logo: its inlined copies keep their own 1.0
   argument, rematerialised before each call as in retail, while the shared 0x8710 offset and
   the 0.0 local each stay in one saved register. The default profile (expensive
   optimizations on) gives the choice loops' pointer start its separate temporary. */

typedef struct { char pad[0x1CC]; unsigned char *entries; int count; int timer; } MenuEntryState;
typedef struct {
    int value, display_choice, selection_mask, required_bits, icon;
} PreviewChoice;
typedef struct { unsigned char bytes[16]; } MenuCorners;

extern MenuEntryState g_pause_menu_state;
extern PreviewChoice g_preview_choices[];
extern unsigned int g_equipment_bits[] __attribute__((sda));
extern int g_preview_selection __attribute__((sda));
extern int g_ui_screen_height_param __attribute__((sda));
extern int g_screen_width[] __attribute__((sda)), g_screen_height[] __attribute__((sda));
extern float g_ui_float_params[] __attribute__((sda));
extern MenuCorners g_options_menu_corners;
extern char g_str_scaled_object_format[];
extern char *g_resident_data_base[] __attribute__((sda));
extern int math_ping_pong_blend_values(int, int, int, int, int);
extern void *table_find_by_id(char *, int);
extern void gfx_draw_scaled_object_two_axes(int, int, float, float, float, float, float);
extern void AppendScreenRectPacket(int, int, int, int, unsigned long, int);
extern int GetIconFrame(int, int);
extern void hud_draw_sprite_gradient(int, int, int, int, int, MenuCorners *);
extern void hud_draw_sprite(int, int, int, int, int, int);
extern char *GetLocalizedString(int);
extern int text_draw_centered_medium(int, int, unsigned long long, char *, int);
extern int text_draw_centered_small(int, int, unsigned long long, char *, int);
extern int sprintf(char *, char *, ...);
extern void preview_choice_icon_draw_us2(int, int);
extern void gfx_set_scissor_clamped(int, int, int, int);
extern void DrawMobysSetup(void), mem_fill_scratch_area(void), mem_save_scratch_area(void);
extern void tex_upload_object_textures(char *, int), mem_restore_scratch_area(void);
extern int tex_run_upload_and_setup(void);
extern void render_environment_mapped_object(char *);
extern void SetupGifPaging(int), DoGifPaging(void);

static __inline__ void draw_logo(int id, int color, float zero)
{
    gfx_draw_scaled_object_two_axes(table_find_by_id(g_resident_data_base[0] + 0x8710, id), color, (float)(g_screen_width[0] / 2), (float)(g_ui_screen_height_param / 2), 1.0f, g_ui_float_params[0], zero);
}

int options_menu_draw_us2(void)
{
    MenuCorners corners = g_options_menu_corners;
    char text[32];
    int color = math_ping_pong_blend_values(0x60241700, 0x55F0C070, 30, 0, 0);
    int x, index, i;
    char *fmt;
    float z;

    z = 0.0f;
    SetupGifPaging(0);
    draw_logo(0xD0, 0x60442D00, z);
    draw_logo(0xD1, 0x60241700, z);
    draw_logo(0xD2, 0x55F0C070, z);
    draw_logo(0xD3, 0x55F0C070, z);
    AppendScreenRectPacket(228, 326, 230, 387, color, 0);
    AppendScreenRectPacket(286, 326, 288, 387, color, 0);
    AppendScreenRectPacket(228, 325, 288, 327, color, 0);
    AppendScreenRectPacket(228, 386, 288, 388, color, 0);
    hud_draw_sprite_gradient(GetIconFrame(0xEAA8, 0), 16, 36, 192, 96, &corners);
    hud_draw_sprite_gradient(GetIconFrame(0xEAA8, 0), 400, 36, -192, 96, &corners);
    hud_draw_sprite_gradient(GetIconFrame(0xEAA8, 0), 16, 228, 192, -96, &corners);
    hud_draw_sprite_gradient(GetIconFrame(0xEAA8, 0), 400, 228, -192, -96, &corners);
    hud_draw_sprite(GetIconFrame(0xEAA8, 1), 402, 50, 89, 115, 64);
    text_draw_centered_medium(445, 116, 0x80F0F0F0ULL, GetLocalizedString(0x30A8), -1);
    text_draw_centered_medium(445, 134, 0x80F0F0F0ULL, GetLocalizedString(0x30A9), -1);
    fmt = g_str_scaled_object_format;
    sprintf(text, fmt, GetLocalizedString(0x30A9));
    text_draw_centered_small(159, 18, 0x80F0F0F0ULL, text, -1);
    text_draw_centered_small(445, 187, 0x80F0F0F0ULL, GetLocalizedString(0x2BE5), -1);
    x = 235;
    for (i = 0; i < 12; i++) {
        index = g_preview_selection - i;
        if (index >= 0 && index < 12) {
            while (index >= 0) {
                if ((g_equipment_bits[0] & g_preview_choices[index].selection_mask) == g_preview_choices[index].required_bits)
                    break;
                index--;
                i++;
            }
            if (index < 0)
                continue;
            preview_choice_icon_draw_us2(index, x);
        }
        x -= 56;
    }
    x = 291;
    for (i = 1; i < 12; i++) {
        index = g_preview_selection + i;
        if (index >= 0 && index < 12) {
            while (index < 12) {
                if ((g_equipment_bits[0] & g_preview_choices[index].selection_mask) == g_preview_choices[index].required_bits)
                    break;
                index++;
                i++;
            }
            if (index >= 12)
                continue;
            preview_choice_icon_draw_us2(index, x);
        }
        x += 56;
    }
    DoGifPaging();
    gfx_set_scissor_clamped(30, 385, 50, 213);
    DrawMobysSetup();
    mem_fill_scratch_area();
    mem_save_scratch_area();
    tex_upload_object_textures(g_pause_menu_state.entries, g_pause_menu_state.count);
    mem_restore_scratch_area();
    tex_run_upload_and_setup();
    SetupGifPaging(0);
    render_environment_mapped_object(g_pause_menu_state.entries);
    DoGifPaging();
    gfx_set_scissor_clamped(0, g_screen_width[0] - 1, 0, g_screen_height[0] - 1);
    return 0;
}
