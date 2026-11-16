#include "include_asm.h"
#include "names.h"
extern int map_screen_update_layout(char *, int);
extern void object_set_first_float4(char *, float, float, float, float);
extern float *object_get_first_field(char *);
extern float g_map_screen_offset_x_first __attribute__((sda));
extern float g_map_screen_offset_y_first;
extern float g_map_screen_offset_x_second;
extern float g_map_screen_offset_y_second;
extern float g_map_screen_offset_x_third;
extern float g_map_screen_offset_y_third;
extern float g_map_screen_offset_x_fourth __attribute__((sda));
extern float g_map_screen_offset_y_fourth;
extern float g_map_screen_offset_x_fifth __attribute__((sda));
extern float g_map_screen_offset_y_fifth;
extern float g_map_screen_offset_x_sixth __attribute__((sda));
extern float g_map_screen_offset_y_sixth;
extern float g_map_screen_offset_x_seventh __attribute__((sda));
extern float g_map_screen_offset_y_seventh;
extern char g_map_overlay_state[];
typedef struct { int first, second, third; float scale; } Entry_0033B540;
extern Entry_0033B540 g_map_spot_table[];

/* Places the sprites of the object built by func_0033B170 around the anchor at +0x1C8 and returns
   0. While the word at D_001C4FA0 + 0x230 is below 0x15, the offset of the sprites at +0xE4 and
   +0x130 (horizontal, 5 at most per call) and of the one at +0x17C (vertical, 3 at most) is eased
   toward a cell of the 16-byte table D_00265140. g and g2 are two loads of the same base: the
   second branch rebuilds the address, as retail does. The second argument is not read. */
int map_screen_update_layout_pal(char *self, int unused)
{
    float dx, dy;
    float *anchor;
    char *g;

    anchor = *(float **)(self + 0x1C8);
    object_set_first_float4(self, anchor[0], anchor[1], 0.0f, 0.0f);
    anchor = *(float **)(self + 0x1C8);
    object_set_first_float4(self + 0x4C, anchor[0], anchor[1], 0.0f, 0.0f);
    anchor = *(float **)(self + 0x1C8);
    object_set_first_float4(self + 0x98, anchor[0], anchor[1], 0.0f, 0.0f);
    dx = dy = 0.0f;
    g = g_map_overlay_state;
    if (*(int *)(g + 0x230) < 0x15) {
        float t;

        dx = object_get_first_field(self + 0xE4)[0] - (g_map_screen_offset_x_first + (*(float **)(self + 0x1C8))[0]);
        if (object_get_first_field(self + 0xE4)[0] == 0.0f) {
            dx = 56.0f;
        } else {
            t = (float)g_map_spot_table[*(int *)(g + 0x230)].first + g_map_spot_table[*(int *)(g + 0x230)].scale * 0.5f - dx;
            if (t > 5.0f)
                t = 5.0f;
            else if (t < -5.0f)
                t = -5.0f;
            dx += t;
        }
        dy = object_get_first_field(self + 0x17C)[1] - (g_map_screen_offset_y_third + (*(float **)(self + 0x1C8))[1]);
        if (object_get_first_field(self + 0x17C)[1] == 0.0f) {
            dy = -50.0f;
        } else {
            char *g2 = g_map_overlay_state;
            t = (float)g_map_spot_table[*(int *)(g2 + 0x230)].second + g_map_spot_table[*(int *)(g2 + 0x230)].scale * 0.5f - dy;
            if (t > 3.0f)
                t = 3.0f;
            else if (t < -3.0f)
                t = -3.0f;
            dy += t;
        }
    }
    anchor = *(float **)(self + 0x1C8);
    object_set_first_float4(self + 0xE4, g_map_screen_offset_x_first + anchor[0] + dx, g_map_screen_offset_y_first + anchor[1], 0.0f, 0.0f);
    anchor = *(float **)(self + 0x1C8);
    object_set_first_float4(self + 0x130, g_map_screen_offset_x_second + anchor[0] + dx, g_map_screen_offset_y_second + anchor[1], 0.0f, 0.0f);
    object_set_first_float4(self + 0x17C, g_map_screen_offset_x_third + (*(float **)(self + 0x1C8))[0], g_map_screen_offset_y_third + (*(float **)(self + 0x1C8))[1] + dy, 0.0f, 0.0f);
    anchor = *(float **)(self + 0x1C8);
    object_set_first_float4(self + 0x1D8, g_map_screen_offset_x_fourth + anchor[0], g_map_screen_offset_y_fourth + anchor[1], 0.0f, 0.0f);
    anchor = *(float **)(self + 0x1C8);
    object_set_first_float4(self + 0x230, g_map_screen_offset_x_fifth + anchor[0], g_map_screen_offset_y_fifth + anchor[1], 0.0f, 0.0f);
    anchor = *(float **)(self + 0x1C8);
    object_set_first_float4(self + 0x288, g_map_screen_offset_x_sixth + anchor[0], g_map_screen_offset_y_sixth + anchor[1], 0.0f, 0.0f);
    anchor = *(float **)(self + 0x1C8);
    object_set_first_float4(self + 0x2E0, g_map_screen_offset_x_seventh + anchor[0], g_map_screen_offset_y_seventh + anchor[1], 0.0f, 0.0f);
    return 0;
}
