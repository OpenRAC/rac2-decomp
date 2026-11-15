#include "common.h"

/* Text banner layout, 0x28 bytes per entry; selected by TextScreen.layout. */
typedef struct {
    int key, base, a08, a0c, width, top, mode, count;
    int height; /* +0x20: line height */
    int duration;
} TextLayout;

typedef struct {
    int buffers[7];
    short buffer, pad1e;
    short layout; /* +0x20: index into D_L00_001BC588 */
    short pad22, active;
    char pad26[0x36C - 0x26];
    int delay, fade;
    float slide; /* +0x374: slide-in start offset */
    char pad378[0x384 - 0x378];
    int style;
} TextScreen;

extern TextScreen D_L00_001BC200;
extern TextLayout D_L00_001BC588[];
/* Screen width: a .sdata global the compiler addresses through the assembler macro. */
extern int g_screen_width MACRO_ADDR;

extern int func_001157AC(char *);
extern int text_measure_width_first_set(char *, int);
extern int math_blend_quadratic_to_int(float, float, float);
extern void FontSetWindow(void *, int, int, int, int, int, int, int, int);
extern void text_draw_window_small(void *, unsigned long, char *, int);
extern void gfx_draw_colored_rectangle(int, int, int, int, unsigned long);

/* Draws one banner line of TEXT at Y. MODE 0 centres it, 1 centres it shifted by T,
   2 slides it in and 3 slides it out with fraction T. Pass 0 draws the text box in
   COLOR, pass 1 a translucent black bar whose alpha follows the slide. */
/* Draws or shades one line of banner text, centred or sliding in or out of the screen. */
void DrawSlidingTextLine(char *text, float t, int mode, int color, int y, int pass)
{
    int box[8];
    int x = 0;
    float alpha = 0.0f;
    int width = text_measure_width_first_set(text, func_001157AC(text));

    switch (mode) {
    case 1:
        x = (int)t;
    case 0:
        alpha = 1.0f;
        x += g_screen_width / 2;
        break;
    case 2:
        x = math_blend_quadratic_to_int(D_L00_001BC200.slide, (float)(g_screen_width / 2) + (float)width, t) - width;
        alpha = t;
        break;
    case 3:
        x = width + g_screen_width
            - math_blend_quadratic_to_int(D_L00_001BC200.slide, (float)(g_screen_width / 2) + (float)width, 1.0f - t);
        alpha = 1.0f - t;
        break;
    }
    if (pass == 0) {
        FontSetWindow(box, y, y + D_L00_001BC588[D_L00_001BC200.layout].height, -g_screen_width, g_screen_width * 2,
                      x, y + D_L00_001BC588[D_L00_001BC200.layout].height / 2, D_L00_001BC200.style, 3);
        text_draw_window_small(box, color, text, -1);
    } else if (pass == 1) {
        int shade = (int)(alpha * 96.0f) << 24;
        gfx_draw_colored_rectangle(y + 2, y + D_L00_001BC588[D_L00_001BC200.layout].height - 2, -g_screen_width,
                      g_screen_width * 2, shade);
    }
}
