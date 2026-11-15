#include "include_asm.h"
#include "names.h"

/* -G8 siblings for src/game/0027F128.c: these need the small-data addressing
   mode (absolute lui forms and gp-relative loads). */

typedef float f32;
typedef int s32;
typedef signed char s8;
typedef unsigned char u8;

extern void mem_clear(void *, int, int);
extern char ref_L00_002EA630_00[];
extern int ref_L00_002EA630_01;
extern f32 IntToFloat(s32);
extern s32 FloatToInt(f32);

/* Clears a data buffer and resets a related counter. */
void text_clear_font_queue_buffer(void) {
    mem_clear(ref_L00_002EA630_00, 0, 0x600);
    ref_L00_002EA630_01 = 0;
}

/* Sum the scaled per-character widths. */
int text_measure_width_scaled(u8 *text, int length, u8 *table, float scale) {
    int i = 0;
    f32 total = 0.0f;
    u8 *p;
    u8 c;

    if (length != 0 && text[0] != 0) {
        p = text;
        do {
            c = *p;
            i++;
            p++;
            total += IntToFloat(*(s8 *)(table + c * 4 + 3)) * scale;
            if (i == length) break;
        } while (*p != 0);
    }
    return FloatToInt(total);
}

extern s32 g_widescreen_flag;
extern s32 g_is_pal_video;
extern s32 func_00124418(void);
extern s32 sceGsResetGraph(s32,s32,s32,s32);

/* Updates the display mode when the screen type changes. */
void gfx_update_display_mode_from_screen_type(void) {
    func_00124418();
    if (g_is_pal_video != 0) g_widescreen_flag = 0;
    if (g_widescreen_flag != 0) sceGsResetGraph(0,0,0x50,1);
    else sceGsResetGraph(0,1,g_is_pal_video != 0 ? 3 : 2,0);
}
