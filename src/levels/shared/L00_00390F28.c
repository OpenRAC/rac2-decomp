#include "include_asm.h"
#include "names.h"
typedef struct {
    char pad0[0x30];
    float f30;
    float f34;
    float f38;
    float f3C;
    unsigned char b40;
    unsigned char b41;
    unsigned char b42;
} State_390F28;

typedef struct {
    char pad0[0x23C];
    int a;
    int b;
    int c;
} Cfg_390F28;

extern int g_lighting_saved_flag __attribute__((section(".sdata")));
extern float g_fog_near __attribute__((section(".sdata")));
extern float g_fog_far __attribute__((section(".sdata")));
extern float g_fog_near_intensity __attribute__((section(".sdata")));
extern float g_fog_far_intensity __attribute__((section(".sdata")));
extern unsigned char g_fog_color_r __attribute__((section(".sdata")));
extern unsigned char g_fog_color_g __attribute__((section(".sdata")));
extern unsigned char g_fog_color_b __attribute__((section(".sdata")));
extern float g_light_far_param __attribute__((section(".sdata")));
extern float g_light_falloff_param __attribute__((section(".sdata")));
extern int g_light_scale_first __attribute__((section(".sdata")));
extern int g_light_distance_param __attribute__((section(".sdata")));
extern int g_light_scale_second __attribute__((section(".sdata")));
extern Cfg_390F28 g_hud_float_params;
extern void SetBackgroundColor(int, int, int);

/* Restores the lighting and fog settings saved by func_L00_00390E10; when full is set it also resets the view range. */
void level_restore_lighting(char *object, int full)
{
    State_390F28 *st = *(State_390F28 **)(object + 0x68);

    g_lighting_saved_flag = 0;
    g_fog_near = st->f30;
    g_fog_far = st->f34;
    g_fog_near_intensity = st->f38;
    g_fog_far_intensity = st->f3C;
    g_fog_color_r = st->b40;
    g_fog_color_g = st->b41;
    g_fog_color_b = st->b42;
    if (full) {
        g_light_far_param = 983040.0f;
        g_light_falloff_param = 500.0f;
        g_light_scale_second = 0x3C0;
        g_light_scale_first = 0x3C0;
        g_light_distance_param = 0x1F4000;
    }
    SetBackgroundColor(g_hud_float_params.a, g_hud_float_params.b, g_hud_float_params.c);
}
