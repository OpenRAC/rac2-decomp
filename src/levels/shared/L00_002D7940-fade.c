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
extern UIFadeState D_L00_001BC200;
typedef struct UIFadeEntry {
    int key, textBase;
    char pad08[12];
    int position;
    char pad18[8];
    int stride;
    int tail;
} UIFadeEntry;
extern UIFadeEntry D_L00_001BC588[];
extern int func_002798A0(int, int *, int *);
extern int func_L00_002E36F8(int);
extern void func_L00_002E30B8(char *text, float t, int mode, int color, int y, int pass);
void func_L00_002E2C30(float progress, int item)
{
    int bank, index, text, position, i;
    int colour;
    float ratio, offset;
    float fade;
    float alpha;
    if (!func_002798A0(item, &bank, &index))
        return;
    text = func_L00_002E36F8(D_L00_001BC588[bank].textBase + index);
    if (!text)
        return;
    position = D_L00_001BC588[D_L00_001BC200.selected].position + item * D_L00_001BC588[D_L00_001BC200.selected].stride;
    if (progress > 1.0f - D_L00_001BC200.fade) {
        fade = (progress - 1.0f + D_L00_001BC200.fade) / D_L00_001BC200.fade;
        if (fade > 1.0f) fade = 1.0f;
        else if (fade < 0.0f) fade = 0.0f;
        func_L00_002E30B8((char *)text, fade, 3, -1, position, 1);
        for (i = D_L00_001BC200.repeats; i >= 0; i--) {
            int grey, lo, hi;
            offset = i * D_L00_001BC200.spacing;
            ratio = (float)(D_L00_001BC200.repeats - i) / (float)D_L00_001BC200.repeats;
            alpha = (progress - 1.0f + D_L00_001BC200.fade) / D_L00_001BC200.fade + offset;
            grey = (int)(ratio * 255.0f);
            lo = (grey << 8) | 0x80000000;
            hi = (grey << 16) | lo;
            colour = hi | grey;
            if (alpha > 1.0f) alpha = 1.0f;
            else if (alpha < 0.0f) alpha = 0.0f;
            func_L00_002E30B8((char *)text, alpha, 3, colour, position, 0);
        }
    } else if (progress < D_L00_001BC200.fade) {
        fade = progress / D_L00_001BC200.fade;
        if (fade > 1.0f) fade = 1.0f;
        else if (fade < 0.0f) fade = 0.0f;
        func_L00_002E30B8((char *)text, fade, 2, -1, position, 1);
        for (i = D_L00_001BC200.repeats; i >= 0; i--) {
            int grey, lo, hi;
            alpha = progress / D_L00_001BC200.fade - i * D_L00_001BC200.spacing;
            ratio = (float)(D_L00_001BC200.repeats - i) / (float)D_L00_001BC200.repeats;
            grey = (int)(ratio * 255.0f);
            lo = (grey << 8) | 0x80000000;
            hi = (grey << 16) | lo;
            colour = hi | grey;
            if (alpha > 1.0f) alpha = 1.0f;
            else if (alpha < 0.0f) alpha = 0.0f;
            func_L00_002E30B8((char *)text, alpha, 2, colour, position, 0);
        }
    } else {
        func_L00_002E30B8((char *)text, 1.0f, 0, -1, position, 1);
        func_L00_002E30B8((char *)text, -2.2f, 1, 0x80000000, position - 2, 0);
        func_L00_002E30B8((char *)text, 0.0f, 1, 0x80000000, position - 2, 0);
        func_L00_002E30B8((char *)text, 2.2f, 1, 0x80000000, position - 2, 0);
        func_L00_002E30B8((char *)text, -2.2f, 1, 0x80000000, position + 2, 0);
        func_L00_002E30B8((char *)text, 0.0f, 1, 0x80000000, position + 2, 0);
        func_L00_002E30B8((char *)text, 2.2f, 1, 0x80000000, position + 2, 0);
        func_L00_002E30B8((char *)text, 1.0f, 0, -1, position, 0);
    }
}
