#include "names.h"
/* func_00279FF0: copies one of two display configurations (the one at 0x1AD584 while
 * the flag at 0x1B5600 is set, else the one at 0x1B1640) into the settings block at
 * 0x1B9040, sets the mode word and applies it. The sources and the mode words are sda
 * objects: -G0 addresses them with the assembler macros, and the mode store in the
 * branch delay slot becomes the $gp form, as retail has it. */
typedef struct {
    unsigned char a, b, c, pad;
    float x, y, z, w;
} Config;

typedef struct {
    char pad000[0x218];
    float x;
    float y;
    char pad220[8];
    float z;
    float w;
    int a;
    int b;
    int c;
} Settings;

extern int g_underwater_flag;
extern Config g_display_config __attribute__((sda));
extern Config g_fog_color __attribute__((sda));
extern Settings g_view_params;
extern int g_display_buffer_size __attribute__((sda));
extern int g_display_config_flag __attribute__((sda));
extern void UpdateViewContext(void);

/* Loads one of two display settings into the live settings block and applies it. */
void gfx_apply_display_config(void)
{
    if (g_underwater_flag != 0) {
        g_view_params.a = g_display_config.a;
        g_view_params.b = g_display_config.b;
        g_view_params.c = g_display_config.c;
        g_view_params.x = g_display_config.x;
        g_view_params.y = g_display_config.y;
        g_view_params.z = g_display_config.z;
        g_view_params.w = g_display_config.w;
        g_display_buffer_size = 0x40000;
    } else {
        g_view_params.a = g_fog_color.a;
        g_view_params.b = g_fog_color.b;
        g_view_params.c = g_fog_color.c;
        g_view_params.x = g_fog_color.x;
        g_view_params.y = g_fog_color.y;
        g_view_params.z = g_fog_color.z;
        g_view_params.w = g_fog_color.w;
        g_display_buffer_size = 0x1F4000;
    }
    UpdateViewContext();
    g_display_config_flag = 0;
}
