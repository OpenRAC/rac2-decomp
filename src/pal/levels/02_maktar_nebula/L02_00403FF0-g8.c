#include "include_asm.h"
#include "names.h"

extern void arena_draw_menu_help_prompts(char *, int);
extern char *GetLocalizedString(int);
extern long long GetEffectTextureDescriptor(int);
extern void FontPrintScaled(float, float, long long, char *, float, int, long long, char *);
extern void FontSetWindow(char *, int, int, int, int, int, int, int, int);
extern unsigned int func_001157AC(char *);
extern void text_draw_window_large(char *, long long, char *, int);
extern void text_draw_window_small(char *, long long, char *, int);
extern int sprintf(char *, char *, ...);
extern int arena_get_challenge_save_index(int);
extern unsigned char g_game_flag_table[0x100];
extern unsigned char g_pal_region_mode;
extern int g_text_l02_x_by_mode[2] __attribute__((sda));
extern float g_text_l02_print_scale __attribute__((sda));
extern int g_text_l02_print_color __attribute__((sda));
extern int g_text_l02_window_coord_a __attribute__((sda));
extern int g_text_l02_window_large_param __attribute__((sda));
extern int g_font_l02_window_flags_a __attribute__((sda));
extern int g_text_l02_window_coord_b __attribute__((sda));
extern int g_text_l02_window_small_param __attribute__((sda));
extern int g_font_l02_window_flags_b __attribute__((sda));
extern int g_text_l02_window_coord_c __attribute__((sda));
extern int g_text_l02_window_coord_d __attribute__((sda));
extern int g_font_l02_window_param_c __attribute__((sda));
extern int g_text_l02_window_coord_e;
extern int g_font_l02_window_param_a;
extern int g_font_l02_window_param_b;
extern float g_text_l02_layout_scale;
extern int g_text_l02_layout_mode;
extern char g_str_level_debug_format[];
extern char g_str_l02_effect_texture[];

static __inline__ int scaled_coord(int value, float scale, float half, int active)
{
    int mode = g_text_l02_layout_mode;
    float scaled = (float)value * scale + half;
    int result = (int)scaled;

    if (result != 0 && mode == active)
        scaled = 1.0f;
    return result;
}

/* func_PAL_L02_00403FF0, the PAL copy of func_L02_003FF6E8 (src/levels/02_maktar_nebula/
   L02_003FF6E8-g8.c) with this release's data and text ids; the first x is taken per language
   from D_PAL_L02_001B14D0. Its data is named D_PAL_L02_<PAL address>: several D_L02_ spellings
   of these addresses already name other data in functions linked into this level. */
void arena_draw_info_panel_pal(char *moby) {
    char buf1[0x20];
    char buf2[0x70];
    char *state;
    char *text;
    char *msg;
    float x, s, half;
    int r0, r1, r2, r3, one;

    arena_draw_menu_help_prompts(moby, 0);
    half = 0.5f;
    state = *(char **)(moby + 0x68);
    text = (char *)GetLocalizedString(0xE6A);
    one = 1;
    s = g_text_l02_layout_scale;
    x = (float)g_text_l02_x_by_mode[g_pal_region_mode];
    r0 = scaled_coord(g_text_l02_window_coord_a, s, half, one);
    FontPrintScaled(x, (float)r0, g_text_l02_print_color, text, g_text_l02_print_scale, -1,
                  GetEffectTextureDescriptor(1), g_str_l02_effect_texture);
    s = g_text_l02_layout_scale;
    r1 = scaled_coord(g_text_l02_window_coord_d, s, half, one);
    r2 = scaled_coord(g_text_l02_window_coord_e, s, half, one);
    r3 = scaled_coord(g_text_l02_window_coord_b, s, half, one);
    FontSetWindow(buf1, r1, r2, g_font_l02_window_param_a, g_font_l02_window_param_b, g_font_l02_window_flags_a, r3,
                  g_font_l02_window_param_c, 3);
    if (*(short *)(state + 0x118) == 0 && g_game_flag_table[arena_get_challenge_save_index(0)] < 2) {
        text = (char *)GetLocalizedString(0xE6B);
        text_draw_window_large(buf1, g_text_l02_window_large_param, text, func_001157AC(text));
    } else {
        text = (char *)GetLocalizedString(0xE87);
        msg = (char *)GetLocalizedString(0xE83);
        sprintf(buf2, g_str_level_debug_format, text, *(int *)(state + 0x110), msg);
        text_draw_window_large(buf1, g_text_l02_window_large_param, buf2, func_001157AC(buf2));
    }
    text = (char *)GetLocalizedString(0xE6C);
    {
        float half = 0.5f;
        int one = 1;

        s = g_text_l02_layout_scale;
        r1 = scaled_coord(g_text_l02_window_coord_d, s, half, one);
        r2 = scaled_coord(g_text_l02_window_coord_e, s, half, one);
        r3 = scaled_coord(g_text_l02_window_coord_c, s, half, one);
        FontSetWindow(buf1, r1, r2, g_font_l02_window_param_a, g_font_l02_window_param_b, g_font_l02_window_flags_b, r3,
                      g_font_l02_window_param_c, 3);
    }
    text_draw_window_small(buf1, g_text_l02_window_small_param, text, func_001157AC(text));
}

extern void moby_set_state(char *, int, int);
extern char *g_arena_challenge_table_2[] __attribute__((sda));
typedef unsigned char u8;
typedef short s16;
typedef int s32;
extern char *g_arena_challenge_table_2[2] __attribute__((sda));
extern s32 g_group_max_index[] __attribute__((sda));
extern s32 moby_is_state_six(char *);
extern s32 moby_is_state_one_cleared_vars(char *);
extern s32 math_random_int_below(s32);
extern s32 moby_has_free_child_slot_state2(char *);
extern s32 arena_is_entity_far_from_hero(char *);
extern unsigned char g_game_flag_table[0x100];
extern int arena_get_challenge_save_index(int);
extern int arena_start_announcer_message(char *, int);
extern s32 g_frame_l02_counter;
extern s32 math_random_int_range(s32, s32);
extern s32 g_request_enabled_flag __attribute__((nosda));
extern s32 arena_start_announcer_message(char *, s32);
extern s32 g_game_mode __attribute__((nosda));
extern u8 g_game_flag_table[];
extern u8 g_item_slot_to_record[];
typedef struct {
    char pad0[4];
    u8 f4;
    char pad1[0xDB];
} L02_003FF9A0_Rec;
extern L02_003FF9A0_Rec g_material_l02_table[];
extern s32 hero_l00_set_move_state_pal(s32, s32);
extern s32 PadPressedWithin(s32, s32, s32 *);
extern s32 arena_get_challenge_save_index(s32);
extern s32 flag_is_byte_set(void);
extern void arena_cancel_challenge_menu_pal(char *);
extern void arena_draw_info_panel_pal(char *);
extern void gfx_add_draw_callback_first(void *, void *);
extern const s32 g_actor_idle_message_count_limit __attribute__((sda));
extern s32 g_actor_message_delay_base __attribute__((sda));
extern s32 g_player_stats;
extern s32 math_fast_float_d(void *);

/* Calls func_PAL_L00_002C4480(0x6F, 1) unless D_0018C0B4 already is 0x6F.  When the input test
   func_L00_0032EF10(0x40, 0x3C, 0) holds, the object changes state to 7 and its selection (state
   half-word 0x118) moves to the next entry of the table at D_L02_001B1190 that is usable: the flag
   of D_001395B8 at the index func_L02_003F9B70 gives for the entry's word at +8 is set, entries from
   12 on also pass func_00288D58, and entries 7 and 8 need the byte at +4 of the record of
   D_L02_00264A70 that D_00139568[0x1E] (0x2A) names.  The pick is kept in the state and in
   D_001395B8[0x3C].  Otherwise, when func_L00_0032EF10(0x10, 0x3C, 0) holds, func_PAL_L02_004011D8
   runs; if neither test holds the callback func_PAL_L02_00403FF0 is registered for the object. */
void menu_select_next_usable_pal(char *moby) {
    char *state = *(char **)(moby + 0x68);
    s32 i;
    L02_003FF9A0_Rec *r;

    if (g_game_mode != 0x6F)
        hero_l00_set_move_state_pal(0x6F, 1);
    if (PadPressedWithin(0x40, 0x32, 0) != 0) {
        moby_set_state(moby, 7, -1);
        for (i = *(s16 *)(state + 0x118) + 1; i < 0xE; i++) {
            if (g_game_flag_table[arena_get_challenge_save_index(*(s32 *)(g_arena_challenge_table_2[i] + 8))] == 0)
                continue;
            if (i >= 0xC && flag_is_byte_set() == 0)
                continue;
            if (i == 7) {
                r = &g_material_l02_table[g_item_slot_to_record[0x1E]];
                if (r->f4 == 0)
                    continue;
            }
            if (i == 8) {
                r = &g_material_l02_table[g_item_slot_to_record[0x2A]];
                if (r->f4 == 0)
                    continue;
            }
            *(s16 *)(state + 0x118) = i;
            g_game_flag_table[0x3C] = *(u8 *)(state + 0x118);
            return;
        }
    } else if (PadPressedWithin(0x10, 0x32, 0) != 0) {
        arena_cancel_challenge_menu_pal(moby);
    } else {
        gfx_add_draw_callback_first(arena_draw_info_panel_pal, moby);
    }
}
