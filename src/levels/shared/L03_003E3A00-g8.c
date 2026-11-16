#include "common.h"

/* func_L03_003E3A00 draws the node puzzle's overlay: the route walked so far, a marker from the
   current node towards each neighbour already in the visited list, two labels, a pulsing
   progress bar, a column of cells, then four lines of text.
   A unit of its own: -G8 for the $gp data, -g for the nop pair before div.s (+0x464), and
   -frac2-gcse-unsplit-edges, without which PRE's copy of the node table's %hi at the
   visited-list scan's entry counts at loop depth 3 (refs 14 instead of 12): the %hi then
   outranks the node index in global allocation and takes $a3 instead of $t0 (+0xF8). */

typedef struct { int x[4]; } Vec;
typedef struct { f32 x, y, z, w; } PuzzleNode;
typedef struct { f32 m[12]; } Matrix;

typedef struct {
    u8 route[16];
    u8 pad10[0x10];
    u8 path[16];
    u8 pad30[0x10];
    u8 visited[6];
    u8 pad46[0xA];
    s16 node;
    u8 pad52[6];
    float phase;
    s16 previous;
    s16 count;
    u8 pad60[2];
    s16 mode;
    u8 pad64[4];
    s16 amount;
} PuzzleState;

extern int g_path_puzzle_step_count __attribute__((sda));
extern int g_path_puzzle_timer_max __attribute__((sda));
extern u32 g_path_puzzle_color_a __attribute__((sda));
extern u32 g_path_puzzle_color_b __attribute__((sda));
extern u32 g_path_puzzle_link_color __attribute__((sda));
extern u32 g_path_puzzle_link_end_color __attribute__((sda));
extern int g_path_puzzle_rect_color __attribute__((sda));
extern int g_path_puzzle_label_left __attribute__((sda));
extern int g_path_puzzle_label_rect_x __attribute__((sda));
extern float g_path_puzzle_label_draw_x __attribute__((sda));
extern float g_path_puzzle_label_size __attribute__((sda));
extern float g_path_puzzle_label_scale_x __attribute__((sda));
extern float g_path_puzzle_label_scale_y __attribute__((sda));
extern float g_path_puzzle_label_corner_table[8] __attribute__((sda, section(".sdata")));
extern float g_screen_l03_scale[] __attribute__((sda));
extern float D_L03_001B3284_1 __attribute__((sda));
extern PuzzleNode g_puzzle_node_directions[14];
extern int g_path_puzzle_adjacency[14][6];
extern u8 *g_menu_data_base;
extern int g_frame_l03_counter;
extern int g_screen_l03_mode;
/* Absolute views of the cell colours, the bar box and the cell box, whose first words are read
   through $gp. */
extern int D_L03_001B0B98_1[] MACRO_ADDR;
extern int D_L03_001B0BA8_1[] MACRO_ADDR;
extern int D_L03_001B0BB8_1[] MACRO_ADDR;
extern Vec g_path_puzzle_label_ids, g_path_puzzle_label_offsets;
extern float g_path_puzzle_label_scale_table[] MACRO_ADDR;
extern char g_str_path_puzzle_label_format[];

extern void path_puzzle_draw_link_strip(u8 *, u32, u32, void *, void *, float, int);
extern void FastVecCross(void *, void *, void *);
extern void vec_set_direction_with_complement(void *, void *, float);
extern void quaternion_to_rotation_basis(void *, void *);
extern void matrix_mul_vec3(void *, void *, void *);
extern void vec_scale_to_length(void *, void *, float);
extern void *table_find_by_id(void *, int);
extern void gfx_draw_scaled_object_two_axes(char *, u32, float, float, float, float, float);
extern float IntToFloat(int);
extern float math_fast_sin_or_cos_b(float);
extern int FloatToInt(float);
extern u32 FastTweenColor(u32, u32, float);
extern void AppendScreenRectPacket(int, int, int, int, unsigned long, int);
extern char *GetLocalizedString(int);
extern int sprintf(char *, char *, ...);
extern int text_draw_centered_medium(int, int, u64, char *, int);

/* A size scaled for the display and rounded (hud_size, as in src/levels/08_tabora/
   L08_0041D808-g8.c): scaled_coord's test in its float form, on the display mode its caller
   reads, compared with the 1 of this function's own mode test. The test has no effect on the
   result: flow deletes it after allocation. */
static __inline__ int hud_size(int mode, float value, float scale, float half)
{
    float scaled = value * scale + half;
    int result = (int)scaled;

    if (result != 0 && mode == 1)
        scaled = 1.0f;
    return result;
}

/* A coordinate scaled for the display and rounded to a whole pixel (upstream's scaled_coord,
   src/levels/02_maktar_nebula/L02_003FF6E8-g8.c). The display-mode test has no effect on the
   result: flow deletes it after allocation. */
static __inline__ int scaled_coord(int value, float scale, float half, int active)
{
    int mode = g_screen_l03_mode;
    float scaled = (float)value * scale + half;
    int result = (int)scaled;

    if (result != 0 && mode == active)
        scaled = 1.0f;
    return result;
}

/* A label's y coordinate (a text line or a sprite) scaled for the display and rounded to a whole
   pixel (label_y, as in src/levels/08_tabora/L08_0041D808-g8.c). Its display-mode and handle tests
   do not change the result: flow deletes them after allocation. */
static __inline__ int label_y(void *handle, float value, float scale, float half, int active)
{
    int mode = g_screen_l03_mode;
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

void DrawPathPuzzleHud(u8 *moby)
{
    PuzzleState *vars = *(PuzzleState **)(moby + 0x68);
    int color, i;
    float a, b, half, t;

    {
        int i, j;
        PuzzleNode tip, axis;
        Matrix rotation;

        if (vars->mode == g_path_puzzle_step_count)
            color = g_path_puzzle_color_b;
        else
            color = g_path_puzzle_color_a;
        i = 0;
        if (vars->route[1] != 255)
            do {
                j = i + 1;
                path_puzzle_draw_link_strip(moby, color, color, &g_puzzle_node_directions[vars->route[i]],
                                  &g_puzzle_node_directions[vars->route[j]], vars->phase, g_path_puzzle_link_end_color);
                i = j;
                if (i >= 15)
                    break;
            } while (vars->route[i + 1] != 255);

        {
            int i, j, k, found;

            for (i = 0; i < 6; i++) {
                k = g_path_puzzle_adjacency[vars->node][i];
                if (k == vars->previous || k == -1)
                    continue;
                if (vars->mode == g_path_puzzle_step_count && k == vars->path[1])
                    continue;
                found = 0;
                for (j = 0; j < 6 && vars->visited[j] != 255; j++)
                    if (vars->visited[j] == k) {
                        found = 1;
                        break;
                    }
                FastVecCross(&axis, &g_puzzle_node_directions[vars->node], &g_puzzle_node_directions[k]);
                vec_set_direction_with_complement(&axis, &axis, 0.17453294992446899f);
                quaternion_to_rotation_basis(&axis, &rotation);
                matrix_mul_vec3(&tip, &g_puzzle_node_directions[vars->node], &rotation);
                vec_scale_to_length(&tip, &tip, 1.0f);
                if (found)
                    path_puzzle_draw_link_strip(moby, g_path_puzzle_link_color & 0xFFFFFF, g_path_puzzle_link_color, &tip,
                                      &g_puzzle_node_directions[vars->node], -vars->phase, 0);
            }
        }
    }
    if (g_menu_data_base) {
        char *s;
        int y, entry = 0x8710;
        float z, half;

        half = 0.5f;
        s = table_find_by_id(g_menu_data_base + entry, 0xCB);
        y = label_y(s, g_path_puzzle_label_size, g_screen_l03_scale[0], half, 1);
        z = 0.0f;
        gfx_draw_scaled_object_two_axes(s, 0x60442D00, g_path_puzzle_label_draw_x, (float)y, g_path_puzzle_label_scale_x, g_path_puzzle_label_scale_y, z);
        s = table_find_by_id(g_menu_data_base + entry, 0xCC);
        y = label_y(s, g_path_puzzle_label_size, g_screen_l03_scale[0], half, 1);
        gfx_draw_scaled_object_two_axes(s, 0x55F0C070, g_path_puzzle_label_draw_x, (float)y, g_path_puzzle_label_scale_x, g_path_puzzle_label_scale_y, z);
    }
    half = 0.5f;
    {
        int x, left, top, right, bottom;
        int pulse;

        pulse = FastTweenColor(0x80F0C070, 0x40F0C070,
                          math_fast_sin_or_cos_b(IntToFloat(g_frame_l03_counter % 60) * 0.10471976548433304f
                                        - 3.14159274f) * half + half);
        a = IntToFloat(vars->amount);
        b = IntToFloat(g_path_puzzle_timer_max);
        left = g_path_puzzle_label_left + 2;
        x = FloatToInt((float)(D_L03_001B0BA8_1[1] - D_L03_001B0BA8_1[3] - 4) * a / b
                          + (float)(D_L03_001B0BA8_1[3] - 2));
        t = g_screen_l03_scale[0];
        top = scaled_coord(x, t, half, 1);
        right = D_L03_001B0BA8_1[2] - 2;
        bottom = scaled_coord(D_L03_001B0BA8_1[3] - 2, t, half, 1);
        AppendScreenRectPacket(left, top, right, bottom, pulse, 0);
    }
    {
        int x, end, top, bottom, left, right;
        float step, fx;

        a = IntToFloat(D_L03_001B0BB8_1[1] - D_L03_001B0BB8_1[3]);
        b = IntToFloat(g_path_puzzle_step_count);
        step = a / b;
        for (i = 0; i < g_path_puzzle_step_count; i++) {
            float scale;

            x = FloatToInt((float)D_L03_001B0BB8_1[3] + (float)i * step);
            fx = (float)x;
            end = FloatToInt(fx + step + 3.0f);
            scale = D_L03_001B3284_1;
            if (i >= vars->count) {
                bottom = scaled_coord(end, scale, half, 1);
                top = hud_size(g_screen_l03_mode, fx, scale, half);
                AppendScreenRectPacket(g_path_puzzle_label_rect_x, bottom, D_L03_001B0BB8_1[2], top, D_L03_001B0B98_1[2], 0);
                {
                    float t;

                    left = g_path_puzzle_label_rect_x + 2;
                    t = g_screen_l03_scale[0];
                    bottom = scaled_coord(end + 2, t, half, 1);
                    right = D_L03_001B0BB8_1[2] - 2;
                    top = scaled_coord(x - 2, t, half, 1);
                    AppendScreenRectPacket(left, bottom, right, top, g_path_puzzle_rect_color, 0);
                }
            } else {
                bottom = scaled_coord(end, scale, half, 1);
                top = hud_size(g_screen_l03_mode, fx, scale, half);
                AppendScreenRectPacket(g_path_puzzle_label_rect_x, bottom, D_L03_001B0BB8_1[2], top, D_L03_001B0B98_1[1], 0);
            }
        }
    }
    {
        int i, x, y;
        Vec ids, offs;
        char text[128];

        ids = g_path_puzzle_label_ids;
        offs = g_path_puzzle_label_offsets;
        for (i = 0; i < 4; i++) {
            float a, offset;

            sprintf(text, g_str_path_puzzle_label_format, GetLocalizedString(ids.x[i]));
            x = FloatToInt(g_path_puzzle_label_corner_table[i * 2]);
            offset = (float)offs.x[i];
            a = g_path_puzzle_label_scale_table[i * 2] * g_screen_l03_scale[0] + 0.5f;
            if (g_screen_l03_mode == 1)
                y = (int)(a + offset);
            else
                y = (int)a;
            y = FloatToInt((float)y);
            text_draw_centered_medium(x, y, 0x80808080, text, 128);
        }
    }
}
