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
extern int D_001A7340 MACRO_ADDR;

extern int func_001157AC(char *);
extern int func_L00_002E9100(char *, int);
extern int func_L00_002E3A68(float, float, float);
extern void func_002802E0(void *, int, int, int, int, int, int, int, int);
extern void func_00280190(void *, unsigned long, char *, int);
extern void func_0027DE50(int, int, int, int, unsigned long);

/* Draws one banner line of TEXT at Y. MODE 0 centres it, 1 centres it shifted by T,
   2 slides it in and 3 slides it out with fraction T. Pass 0 draws the text box in
   COLOR, pass 1 a translucent black bar whose alpha follows the slide. */
void func_L00_002E30B8(char *text, float t, int mode, int color, int y, int pass)
{
    int box[8];
    int x = 0;
    float alpha = 0.0f;
    int width = func_L00_002E9100(text, func_001157AC(text));

    switch (mode) {
    case 1:
        x = (int)t;
    case 0:
        alpha = 1.0f;
        x += D_001A7340 / 2;
        break;
    case 2:
        x = func_L00_002E3A68(D_L00_001BC200.slide, (float)(D_001A7340 / 2) + (float)width, t) - width;
        alpha = t;
        break;
    case 3:
        x = width + D_001A7340
            - func_L00_002E3A68(D_L00_001BC200.slide, (float)(D_001A7340 / 2) + (float)width, 1.0f - t);
        alpha = 1.0f - t;
        break;
    }
    if (pass == 0) {
        func_002802E0(box, y, y + D_L00_001BC588[D_L00_001BC200.layout].height, -D_001A7340, D_001A7340 * 2,
                      x, y + D_L00_001BC588[D_L00_001BC200.layout].height / 2, D_L00_001BC200.style, 3);
        func_00280190(box, color, text, -1);
    } else if (pass == 1) {
        int shade = (int)(alpha * 96.0f) << 24;
        func_0027DE50(y + 2, y + D_L00_001BC588[D_L00_001BC200.layout].height - 2, -D_001A7340,
                      D_001A7340 * 2, shade);
    }
}
