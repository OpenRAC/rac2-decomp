#include "include_asm.h"
#include "names.h"

extern void object_set_first_float4(char *p, float x, float y, float zero, float zero2);
extern float g_info_panel_counter_x0 __attribute__((sda));
extern float g_info_panel_counter_x1 __attribute__((sda));
extern float g_info_panel_counter_x2 __attribute__((sda));
extern float g_info_panel_counter_offset_x __attribute__((sda));
extern float g_info_panel_counter_y0;
extern float g_info_panel_counter_y1;
extern float g_info_panel_counter_y2;
extern float g_info_panel_counter_offset_y;
struct pos {
    float x;
    float y;
};

/* Places the three counter texts and the counter shift text relative to the panel anchor. */
void info_panel_place_counters_us2(char *self)
{
    float zero = 0.0f;

    object_set_first_float4(self + 1400, g_info_panel_counter_offset_x + (*(struct pos **)(self + 728))->x,
            g_info_panel_counter_offset_y + (*(struct pos **)(self + 728))->y, zero, zero);
    object_set_first_float4(self + 1136, g_info_panel_counter_x0 + (*(struct pos **)(self + 728))->x,
            g_info_panel_counter_y0 + (*(struct pos **)(self + 728))->y, zero, zero);
    object_set_first_float4(self + 1224, g_info_panel_counter_x1 + (*(struct pos **)(self + 728))->x,
            g_info_panel_counter_y1 + (*(struct pos **)(self + 728))->y, zero, zero);
    object_set_first_float4(self + 1312, g_info_panel_counter_x2 + (*(struct pos **)(self + 728))->x,
            g_info_panel_counter_y2 + (*(struct pos **)(self + 728))->y, zero, zero);
}
