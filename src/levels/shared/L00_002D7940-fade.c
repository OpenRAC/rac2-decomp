#include "common.h"

/* Draws the selected item with its fade and repeated outline strokes. */
typedef struct UIFadeState {
    char pad00[0x20];
    short selected;
    char pad22[0x356];
    float fade;
    int repeats;
    float spacing;
} UIFadeState;
extern UIFadeState g_fading_text_style;
typedef struct UIFadeEntry {
    int key, textBase;
    char pad08[12];
    int position;
    char pad18[8];
    int stride;
    int tail;
} UIFadeEntry;
extern UIFadeEntry g_fading_text_layouts[];
extern int AdvanceGroupedTableOffset(int, int *, int *);
extern int text_find_level_by_key(int);
extern void DrawSlidingTextLine(char *text, float t, int mode, int color, int y, int pass);
/* Fades one line of text in or out as progress runs from 0 to 1, with a soft outline. */
void text_draw_fading_line(float progress, int item)
{
    int bank, index, text, position, i;
    int colour;
    float ratio, offset;
    float fade;
    float alpha;
    if (!AdvanceGroupedTableOffset(item, &bank, &index))
        return;
    text = text_find_level_by_key(g_fading_text_layouts[bank].textBase + index);
    if (!text)
        return;
    position = g_fading_text_layouts[g_fading_text_style.selected].position + item * g_fading_text_layouts[g_fading_text_style.selected].stride;
    if (progress > 1.0f - g_fading_text_style.fade) {
        fade = (progress - 1.0f + g_fading_text_style.fade) / g_fading_text_style.fade;
        if (fade > 1.0f) fade = 1.0f;
        else if (fade < 0.0f) fade = 0.0f;
        DrawSlidingTextLine((char *)text, fade, 3, -1, position, 1);
        for (i = g_fading_text_style.repeats; i >= 0; i--) {
            int grey, lo, hi;
            offset = i * g_fading_text_style.spacing;
            ratio = (float)(g_fading_text_style.repeats - i) / (float)g_fading_text_style.repeats;
            alpha = (progress - 1.0f + g_fading_text_style.fade) / g_fading_text_style.fade + offset;
            grey = (int)(ratio * 255.0f);
            lo = (grey << 8) | 0x80000000;
            hi = (grey << 16) | lo;
            colour = hi | grey;
            if (alpha > 1.0f) alpha = 1.0f;
            else if (alpha < 0.0f) alpha = 0.0f;
            DrawSlidingTextLine((char *)text, alpha, 3, colour, position, 0);
        }
    } else if (progress < g_fading_text_style.fade) {
        fade = progress / g_fading_text_style.fade;
        if (fade > 1.0f) fade = 1.0f;
        else if (fade < 0.0f) fade = 0.0f;
        DrawSlidingTextLine((char *)text, fade, 2, -1, position, 1);
        for (i = g_fading_text_style.repeats; i >= 0; i--) {
            int grey, lo, hi;
            alpha = progress / g_fading_text_style.fade - i * g_fading_text_style.spacing;
            ratio = (float)(g_fading_text_style.repeats - i) / (float)g_fading_text_style.repeats;
            grey = (int)(ratio * 255.0f);
            lo = (grey << 8) | 0x80000000;
            hi = (grey << 16) | lo;
            colour = hi | grey;
            if (alpha > 1.0f) alpha = 1.0f;
            else if (alpha < 0.0f) alpha = 0.0f;
            DrawSlidingTextLine((char *)text, alpha, 2, colour, position, 0);
        }
    } else {
        DrawSlidingTextLine((char *)text, 1.0f, 0, -1, position, 1);
        DrawSlidingTextLine((char *)text, -2.2f, 1, 0x80000000, position - 2, 0);
        DrawSlidingTextLine((char *)text, 0.0f, 1, 0x80000000, position - 2, 0);
        DrawSlidingTextLine((char *)text, 2.2f, 1, 0x80000000, position - 2, 0);
        DrawSlidingTextLine((char *)text, -2.2f, 1, 0x80000000, position + 2, 0);
        DrawSlidingTextLine((char *)text, 0.0f, 1, 0x80000000, position + 2, 0);
        DrawSlidingTextLine((char *)text, 2.2f, 1, 0x80000000, position + 2, 0);
        DrawSlidingTextLine((char *)text, 1.0f, 0, -1, position, 0);
    }
}
