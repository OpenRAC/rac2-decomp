/* 1 November 2026: still 6 words. 21 colour spellings tried (fresh temps, chain orders, the last OR in the call): none gives or $v1,$v1,$v0 then or $a2,$v1,$a0 with grey in $a0. Position first, a temp and a stride temp leave $a0 for the position load. */
/* Near miss, 26 October 2026 (M6): 1156/1156 bytes, 6 instructions off, register-only.
 * Unit src/levels/shared/L00_002E2C30.c, flags -O2 -G0 -ffunction-sections -g.
 * What closed the size: callee func_L00_002E30B8 takes (text, float, ...): the float is the
 * second parameter; the selected entry written out at each use (compute-then-copy);
 * the first loop as offset / ratio / fade statements and the second loop as fade / ratio
 * (the -g boundary nops before div.s); the colour built as lo, then (grey<<16)|lo, then |grey.
 * Left: the stride load lands in $a0 (retail $a1) and the colour intermediate in $a2
 * (retail $v1). Submitted to the permuter.
 */
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
extern void func_L00_002E30B8(int, float, int, int, int, int);
void func_L00_002E2C30(float progress, int item)
{
    int bank, index, text, position, i, grey;
    int colour;
    UIFadeEntry *entry;
    float ratio, offset;
    int hi, lo;
    float fade;
    if (!func_002798A0(item, &bank, &index))
        return;
    text = func_L00_002E36F8(D_L00_001BC588[bank].textBase + index);
    if (!text)
        return;
    position = D_L00_001BC588[D_L00_001BC200.selected].position + item * D_L00_001BC588[D_L00_001BC200.selected].stride;
    fade = D_L00_001BC200.fade;
    if (progress > 1.0f - fade) {
        fade = (progress - 1.0f + fade) / fade;
        if (fade > 1.0f) fade = 1.0f;
        else if (fade < 0.0f) fade = 0.0f;
        func_L00_002E30B8(text, fade, 3, -1, position, 1);
        for (i = D_L00_001BC200.repeats; i >= 0; i--) {
            offset = i * D_L00_001BC200.spacing;
            ratio = (float)(D_L00_001BC200.repeats - i) / (float)D_L00_001BC200.repeats;
            fade = (progress - 1.0f + D_L00_001BC200.fade) / D_L00_001BC200.fade + offset;
            grey = (int)(ratio * 255.0f);
            lo = (grey << 8) | 0x80000000;
            colour = (grey << 16) | lo;
            colour = grey | colour;
            if (fade > 1.0f) fade = 1.0f;
            else if (fade < 0.0f) fade = 0.0f;
            func_L00_002E30B8(text, fade, 3, colour, position, 0);
        }
    } else if (progress < fade) {
        fade = progress / fade;
        if (fade > 1.0f) fade = 1.0f;
        else if (fade < 0.0f) fade = 0.0f;
        func_L00_002E30B8(text, fade, 2, -1, position, 1);
        for (i = D_L00_001BC200.repeats; i >= 0; i--) {
            fade = progress / D_L00_001BC200.fade - i * D_L00_001BC200.spacing;
            ratio = (float)(D_L00_001BC200.repeats - i) / (float)D_L00_001BC200.repeats;
            grey = (int)(ratio * 255.0f);
            lo = (grey << 8) | 0x80000000;
            colour = (grey << 16) | lo;
            colour = grey | colour;
            if (fade > 1.0f) fade = 1.0f;
            else if (fade < 0.0f) fade = 0.0f;
            func_L00_002E30B8(text, fade, 2, colour, position, 0);
        }
    } else {
        func_L00_002E30B8(text, 1.0f, 0, -1, position, 1);
        func_L00_002E30B8(text, -2.2f, 1, 0x80000000, position - 2, 0);
        func_L00_002E30B8(text, 0.0f, 1, 0x80000000, position - 2, 0);
        func_L00_002E30B8(text, 2.2f, 1, 0x80000000, position - 2, 0);
        func_L00_002E30B8(text, -2.2f, 1, 0x80000000, position + 2, 0);
        func_L00_002E30B8(text, 0.0f, 1, 0x80000000, position + 2, 0);
        func_L00_002E30B8(text, 2.2f, 1, 0x80000000, position + 2, 0);
        func_L00_002E30B8(text, 1.0f, 0, -1, position, 0);
    }
}
