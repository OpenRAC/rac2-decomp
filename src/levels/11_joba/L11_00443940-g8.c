#include "names.h"
/* func_L11_00443940: the help-prompt HUD lines (labels 0x49/0x48, then a pulsing colour
 * from func_00283D38, the 0x4b line when the selection is nonzero and the first available
 * 0x4a entry after it). Twin of func_L02_003FDDE8.
 * one/k3 are set-once label_y actives (k3 only in the 0x4b draw, which local-alloc keeps beside
 * the label copy); x3 is that draw's own x. The label_y dead-test helper, set-once constant
 * locals and func_00300A00's bank-preserving argument order (x before colour) are allowed by
 * owner rulings (2026-11-08/09). */
#include "common.h"

typedef struct {
    u8 pad[0x1a0];
    int field1a0;
} InputView;
typedef struct {
    u8 pad[4];
    u8 enabled;
    u8 rest[0xdb];
} MenuRecord;
extern u8 *g_help_prompt_table;
extern float g_hud_label_y_param;
extern int g_arena_progress_level;
extern unsigned char g_pad_state[];
extern unsigned char g_item_slot_to_record[], g_game_flag_table[];
extern unsigned char g_item_l11_record_table[];
/* The class pointer table is addressed through gp. */
extern int *g_arena_challenge_table[] SDATA(D_L11_001B14F8);
extern void gfx_append_draw_list_packet_c(void);
extern void *table_find_by_id(u8 *, int);
extern void gfx_draw_scaled_object_two_axes(char *, float, int, float, float, float, float);
extern unsigned int FastTweenColor(unsigned int, unsigned int, float);
extern int arena_get_challenge_flag_index(unsigned int);
extern int flag_is_byte_set(void);
extern void VU1_addGSregister(unsigned int, unsigned long long);
extern float g_help_prompt_label_scale __attribute__((sda));
extern int g_help_prompt_label_x __attribute__((sda));
extern int g_help_prompt_label_y __attribute__((sda));
extern int g_help_prompt_confirm_x __attribute__((sda));
extern int g_help_prompt_confirm_y __attribute__((sda));
extern int g_help_l11_prompt_next_x __attribute__((sda));
extern int g_help_l11_prompt_next_y __attribute__((sda));
extern unsigned int g_help_l11_prompt_color_a __attribute__((sda));
extern unsigned int g_help_l11_prompt_color_b __attribute__((sda));
extern unsigned int g_help_prompt_pressed_color_a __attribute__((sda));
extern unsigned int g_help_prompt_pressed_color_b __attribute__((sda));

extern int g_hud_coord_mode;

/* label_y: dead-test HUD helper allowed by owner ruling (7 November 2026; precedent
   src/levels/15_gorn/L15_00431590-g8.c); `one` as active per the func_L01_002F1588 ruling. */
static __inline__ int label_y(void *handle, float value, float scale, float half, int active)
{
    int mode = g_hud_coord_mode;
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

/* Draws the help prompts of the Joba menu: the two button labels and the arrows for the previous and next entry. */
void joba_menu_draw_help_prompts(u8 *moby, int enabled)
{
    u8 *state;
    int label, phase, i, one, k3, entry;
    unsigned int color, label_color;
    float confirm_x, next_x, label_x, labelY, pulse, half, scale, zero;
    if (g_help_prompt_table == 0) return;
    gfx_append_draw_list_packet_c();
    entry = 0x8710;
    state = *(u8 **)(moby + 0x68);
    half = 0.5f;

    label = table_find_by_id(g_help_prompt_table + entry, 0x49);
    label_x = (float)g_help_prompt_label_x;
    one = 1;
    labelY = (float)label_y((void *)label, (float)g_help_prompt_label_y, g_hud_label_y_param, half, one);
    scale = 1.0f;
    zero = 0.0f;
    gfx_draw_scaled_object_two_axes((char *)label, label_x, g_help_l11_prompt_color_b, labelY, g_help_prompt_label_scale, scale, zero);
    label = table_find_by_id(g_help_prompt_table + entry, 0x48);
    label_x = (float)g_help_prompt_label_x;
    labelY = (float)label_y((void *)label, (float)g_help_prompt_label_y, g_hud_label_y_param, half, 1);
    gfx_draw_scaled_object_two_axes((char *)label, label_x, g_help_l11_prompt_color_a, labelY, g_help_prompt_label_scale, scale, zero);
    phase = g_arena_progress_level % 50;
    if (phase >= 25) pulse = scale - (float)(phase - 25) * 0.04f;
    else pulse = (float)phase * 0.04f;
    color = FastTweenColor(g_help_l11_prompt_color_a, g_help_l11_prompt_color_b, pulse);
    if (enabled) {
        if (*(short *)(state + 0x1e8) != 0) {
            label = table_find_by_id(g_help_prompt_table + 0x8710, 0x4b);
            k3 = 1;
            confirm_x = (float)g_help_prompt_confirm_x;
            label_color = (((InputView *)g_pad_state)->field1a0 & 0x8000) ? g_help_prompt_pressed_color_a : color;
            labelY = (float)label_y((void *)label, (float)g_help_prompt_confirm_y, g_hud_label_y_param, 0.5f, k3);
            gfx_draw_scaled_object_two_axes((char *)label, confirm_x, label_color, labelY, g_help_prompt_label_scale, 1.0f, 0.0f);
        }
        for (i = *(short *)(state + 0x1e8) + 1; i < 13; i++) {
            if (!g_game_flag_table[arena_get_challenge_flag_index(g_arena_challenge_table[i][2])]) continue;
            if (i >= 11 && !flag_is_byte_set()) continue;
            if (i == 8) {
                MenuRecord *choice = (MenuRecord *)(g_item_l11_record_table + g_item_slot_to_record[0x1e] * 0xe0);
                if (!choice->enabled) continue;
            }
            label = table_find_by_id(g_help_prompt_table + 0x8710, 0x4a);
            one = 1;
            label_color = (((InputView *)g_pad_state)->field1a0 & 0x2000) ? g_help_prompt_pressed_color_b : color;
            next_x = (float)g_help_l11_prompt_next_x;
            labelY = (float)label_y((void *)label, (float)g_help_l11_prompt_next_y, g_hud_label_y_param, 0.5f, one);
            gfx_draw_scaled_object_two_axes((char *)label, next_x, label_color, labelY, g_help_prompt_label_scale, 1.0f, 0.0f);
            break;
        }
    }
    VU1_addGSregister(0x47, 0x5360b);
}
