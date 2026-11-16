#include "common.h"

/* func_PAL_002D4EA0: the PAL copy of v2.00's func_US2_002D4ED8 (src/us2/game/002D4ED8-g8.c),
   itself the v2.00 copy of func_002D3FA0: draws the preview menu (four logo sprite layers, the
   frame rectangles and corners, the header text and the two rows of choice icons,
   func_PAL_002D4D00 for each unlocked choice either side of D_001ABA74), then renders the preview
   model. The same C, with PAL's text ids (0x13DB, 0x13DC and 0xB60); PAL draws the 0xB60 label
   centred, with func_0027FB40 (v2.00: func_0027FAA8).

   Each logo layer is drawn by the inline draw_logo: its inlined copies keep their own 1.0
   argument, rematerialised before each call as in retail, while the shared 0x8710 offset and
   the 0.0 local each stay in one saved register. The default profile (expensive
   optimizations on) gives the choice loops' pointer start its separate temporary. */

typedef struct { char pad[0x1CC]; unsigned char *entries; int count; int timer; } MenuEntryState;
typedef struct {
    int value, displayChoice, selectionMask, requiredBits, icon;
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
extern void func_PAL_002D4D00(int, int);
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

int func_PAL_002D4EA0(void)
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
    text_draw_centered_medium(445, 116, 0x80F0F0F0ULL, GetLocalizedString(0x13DB), -1);
    text_draw_centered_medium(445, 134, 0x80F0F0F0ULL, GetLocalizedString(0x13DC), -1);
    fmt = g_str_scaled_object_format;
    sprintf(text, fmt, GetLocalizedString(0x13DC));
    text_draw_centered_small(159, 18, 0x80F0F0F0ULL, text, -1);
    text_draw_centered_medium(445, 187, 0x80F0F0F0ULL, GetLocalizedString(0xB60), -1);
    x = 235;
    for (i = 0; i < 12; i++) {
        index = g_preview_selection - i;
        if (index >= 0 && index < 12) {
            while (index >= 0) {
                if ((g_equipment_bits[0] & g_preview_choices[index].selectionMask) == g_preview_choices[index].requiredBits)
                    break;
                index--;
                i++;
            }
            if (index < 0)
                continue;
            func_PAL_002D4D00(index, x);
        }
        x -= 56;
    }
    x = 291;
    for (i = 1; i < 12; i++) {
        index = g_preview_selection + i;
        if (index >= 0 && index < 12) {
            while (index < 12) {
                if ((g_equipment_bits[0] & g_preview_choices[index].selectionMask) == g_preview_choices[index].requiredBits)
                    break;
                index++;
                i++;
            }
            if (index >= 12)
                continue;
            func_PAL_002D4D00(index, x);
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
