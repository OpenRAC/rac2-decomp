#include "names.h"
/* func_L02_003FDDE8: the help-prompt HUD lines (labels 0x49/0x48, then a pulsing colour
 * from func_00283D38, the 0x4b line when the selection is nonzero and the first available
 * 0x4a entry after it). Twin of func_L11_00443940.
 * one/k3 are set-once label_y actives (k3 only in the 0x4b draw, which local-alloc keeps beside
 * the label copy); x3 is that draw's own x. The label_y dead-test helper, set-once constant
 * locals and func_00300A00's bank-preserving argument order (x before colour) are allowed by
 * owner rulings (2026-11-08/09). */
#include "common.h"

typedef struct {
    u8 pad[0x1a0];
    int buttons;
} HelpInput;
typedef struct {
    u8 pad[4];
    u8 available;
    u8 rest[0xdb];
} HelpEntry;

extern u8 *g_arena_menu_base;
extern float g_hud_label_scale;
extern int g_frame_l02_counter;
extern HelpInput g_pad_state;
extern u8 g_item_slot_to_record[], g_game_flag_table[];
extern HelpEntry g_material_l02_table[];
extern u8 *g_arena_challenge_table_2[] SDATA(D_L02_001B1190);

extern void gfx_append_draw_list_packet_c(void);
extern void *table_find_by_id(u8 *, int);
extern void gfx_draw_scaled_object_two_axes(char *, float, int, float, float, float, float);
extern unsigned int FastTweenColor(unsigned int, unsigned int, float);
extern int arena_get_challenge_save_index(int);
extern int flag_is_byte_set(void);
extern void VU1_addGSregister(unsigned int, unsigned long long);

extern float g_help_prompt_scale __attribute__((sda));
extern int g_help_prompt_x __attribute__((sda));
extern int g_help_prompt_y __attribute__((sda));
extern int g_help_prompt_button_x __attribute__((sda));
extern int g_help_prompt_button_y __attribute__((sda));
extern int g_help_l02_prompt_next_x __attribute__((sda));
extern int g_help_l02_prompt_next_y __attribute__((sda));
extern unsigned int g_help_l02_prompt_color_a __attribute__((sda));
extern unsigned int g_help_l02_prompt_color_b __attribute__((sda));
extern unsigned int g_help_prompt_pressed_color __attribute__((sda));
extern unsigned int g_help_prompt_alt_color __attribute__((sda));

extern int g_hud_l02_mode;

/* label_y: dead-test HUD helper allowed by owner ruling (7 November 2026; precedent
   src/levels/15_gorn/L15_00431590-g8.c); `one` as active per the func_L01_002F1588 ruling. */
static __inline__ int label_y(void *handle, float value, float scale, float half, int active)
{
    int mode = g_hud_l02_mode;
    float scaled = value * scale + half;
    int result = (int)scaled;
    void *copy;

    if (mode == active)
        scaled = scale;
    if (handle != 0)
        scaled = scale;
    copy = handle;
    if (copy != 0)
        scaled = half;
    return result;
}

/* Draws the button help lines at the bottom of the challenge menu. */
void arena_draw_menu_help_prompts(u8 *object, int enabled)
{
    u8 *state;
    char *label;
    int phase, i, one, k3, entry;
    unsigned int color, button_color;
    float x3, next_x, x, fy, pulse, half, sc, z;
    HelpEntry *entry_record;

    if (g_arena_menu_base == 0) return;
    gfx_append_draw_list_packet_c();
    entry = 0x8710;
    state = *(u8 **)(object + 0x68);
    half = 0.5f;
    label = (char *)table_find_by_id(g_arena_menu_base + entry, 0x49);
    x = (float)g_help_prompt_x;
    one = 1;
    fy = (float)label_y(label, (float)g_help_prompt_y, g_hud_label_scale, half, one);
    sc = 1.0f;
    z = 0.0f;
    gfx_draw_scaled_object_two_axes(label, x, g_help_l02_prompt_color_b, fy, g_help_prompt_scale, sc, z);
    label = (char *)table_find_by_id(g_arena_menu_base + entry, 0x48);
    x = (float)g_help_prompt_x;
    fy = (float)label_y(label, (float)g_help_prompt_y, g_hud_label_scale, half, 1);
    gfx_draw_scaled_object_two_axes(label, x, g_help_l02_prompt_color_a, fy, g_help_prompt_scale, sc, z);
    phase = g_frame_l02_counter % 50;
    if (phase >= 25) pulse = sc - (float)(phase - 25) * 0.04f;
    else pulse = (float)phase * 0.04f;
    color = FastTweenColor(g_help_l02_prompt_color_a, g_help_l02_prompt_color_b, pulse);
    if (enabled) {
        if (*(short *)(state + 0x118) != 0) {
            label = (char *)table_find_by_id(g_arena_menu_base + 0x8710, 0x4b);
            k3 = 1;
            x3 = (float)g_help_prompt_button_x;
            if (g_pad_state.buttons & 0x8000) button_color = g_help_prompt_pressed_color; else button_color = color;
            fy = (float)label_y(label, (float)g_help_prompt_button_y, g_hud_label_scale, 0.5f, k3);
            gfx_draw_scaled_object_two_axes(label, x3, button_color, fy, g_help_prompt_scale, 1.0f, 0.0f);
        }
        for (i = *(short *)(state + 0x118) + 1; i < 14; i++) {
            if (g_game_flag_table[arena_get_challenge_save_index(*(int *)(g_arena_challenge_table_2[i] + 8))] == 0) continue;
            if (i >= 12 && !flag_is_byte_set()) continue;
            if (i == 7) {
                entry_record = &g_material_l02_table[g_item_slot_to_record[0x1e]];
                if (entry_record->available == 0) continue;
            }
            if (i == 8) {
                entry_record = &g_material_l02_table[g_item_slot_to_record[0x2a]];
                if (entry_record->available == 0) continue;
            }
            label = (char *)table_find_by_id(g_arena_menu_base + 0x8710, 0x4a);
            one = 1;
            button_color = (g_pad_state.buttons & 0x2000) ? g_help_prompt_alt_color : color;
            next_x = (float)g_help_l02_prompt_next_x;
            fy = (float)label_y(label, (float)g_help_l02_prompt_next_y, g_hud_label_scale, 0.5f, one);
            gfx_draw_scaled_object_two_axes(label, next_x, button_color, fy, g_help_prompt_scale, 1.0f, 0.0f);
            break;
        }
    }
    VU1_addGSregister(0x47, 0x5360b);
}
