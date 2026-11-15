#include "common.h"

/* State of the object preview (see 002FC8D0.c). */
typedef struct {
    short s00;
    short frames;
    float rate;
    char pad08[0x34 - 0x08];
    unsigned char phase;
    unsigned char spin;
} PreviewState;

extern PreviewState g_object_preview_state __attribute__((sda));
extern short g_screen_adjust_offsets[];
extern float IntToFloat(int);
extern int FloatToInt(float);
extern void VU1_addGSregister(int, long long);
extern void gfx_draw_colored_rectangle(int, int, int, int, u64);

/* Draws a black overlay on the screen whose strength follows the preview timer, to fade the screen. */
void shop_draw_preview_fade_overlay(void)
{
    int v;
    VU1_addGSregister(0x42, 0x44);
    v = FloatToInt((1.0f - IntToFloat(g_object_preview_state.frames) * g_object_preview_state.rate) * 255.0f);
    gfx_draw_colored_rectangle(0, g_screen_adjust_offsets[0xA9], 0, g_screen_adjust_offsets[0xA8], (u64)(v << 24));
}
