#include "include_asm.h"
#include "names.h"

typedef unsigned char u8;
typedef short s16;

extern void func_L02_003FDDE8(char *, int);
extern int func_00288FB8(int);
extern long long func_0027C878(int);
extern void func_0027F640(float, float, long long, char *, float, int, long long, char *);
extern void func_002802E0(char *, int, int, int, int, int, int, int, int);
extern int func_L02_003F9B70(int);
extern unsigned int func_001157AC(char *);
extern void func_00280270(char *, long long, char *, int);
extern void func_00280190(char *, long long, char *, int);
extern int func_00115DA8(char *, char *, ...);

extern float D_L02_001B1438 __attribute__((sda));
extern int D_L02_001B143C __attribute__((sda));
extern int D_L02_001B1440 __attribute__((sda));
extern int D_L02_001B1444 __attribute__((sda));
extern int D_L02_001B1448 __attribute__((sda));
extern int D_L02_001B144C __attribute__((sda));
extern int D_L02_001B1450 __attribute__((sda));
extern int D_L02_001B1454 __attribute__((sda));
extern int D_L02_001B1458 __attribute__((sda));
extern int D_L02_001B145C __attribute__((sda));
extern int D_L02_001B1460 __attribute__((sda));
extern int D_L02_001B1464;
extern int D_L02_001B1468;
extern int D_L02_001B146C;
extern int D_L02_001B1470 __attribute__((sda));
extern float D_L02_001B3E04;
extern char D_L02_001B1228[];
extern char D_L02_0028E990[];
extern u8 D_001395B8[0x100];

extern int D_L02_001B3E00;

/* A coordinate scaled for the display and rounded to a whole pixel. The display-mode test has no
   effect on the result, but it is real: its load and compare go at flow2, after allocation. */
static __inline__ int scaled_coord(int value, float scale, float half, int active)
{
    int mode = D_L02_001B3E00;
    float scaled = (float)value * scale + half;
    int result = (int)scaled;

    if (result != 0 && mode == active)
        scaled = 1.0f;
    return result;
}

/* Level 2 copy of func_L11_004456A0 (src/levels/11_joba/L11_004456A0-g8.c), transcribed
   with this level's data. */
/* Draws the info panel for the selected challenge: a title, a box and a line with the best result so far. */
void func_L02_003FF6E8(char *actor) {
    char rect[0x20];
    char lineBuf[0x70];
    char *state;
    char *text;
    char *msg;
    float x, scale, half;
    int titleY, boxX, boxY, boxHeight, one;

    DrawChallengeMenuHelpPrompts(actor, 0);
    half = 0.5f;
    state = *(char **)(actor + 0x68);
    text = (char *)GetLocalizedString(0x2F45);
    one = 1;
    scale = D_L02_001B3E04;
    x = (float)D_L02_001B1440;
    titleY = scaled_coord(D_L02_001B1444, scale, half, one);
    FontPrintScaled(x, (float)titleY, D_L02_001B143C, text, D_L02_001B1438, -1,
                  GetEffectTextureDescriptor(1), D_L02_0028E990);
    scale = D_L02_001B3E04;
    boxX = scaled_coord(D_L02_001B1460, scale, half, one);
    boxY = scaled_coord(D_L02_001B1464, scale, half, one);
    boxHeight = scaled_coord(D_L02_001B1450, scale, half, one);
    FontSetWindow(rect, boxX, boxY, D_L02_001B1468, D_L02_001B146C, D_L02_001B144C, boxHeight,
                  D_L02_001B1470, 3);
    if (*(s16 *)(state + 0x118) == 0 && D_001395B8[GetChallengeSaveIndex(0)] < 2) {
        text = (char *)GetLocalizedString(0x2F46);
        DrawTextWindowLargeFont(rect, D_L02_001B1448, text, strlen_001157AC(text));
    } else {
        text = (char *)GetLocalizedString(0x2F62);
        msg = (char *)GetLocalizedString(0x2F5E);
        Sprintf(lineBuf, D_L02_001B1228, text, *(int *)(state + 0x110), msg);
        DrawTextWindowLargeFont(rect, D_L02_001B1448, lineBuf, strlen_001157AC(lineBuf));
    }
    text = (char *)GetLocalizedString(0x2F47);
    {
        float half = 0.5f;
        int one = 1;

        scale = D_L02_001B3E04;
        boxX = scaled_coord(D_L02_001B1460, scale, half, one);
        boxY = scaled_coord(D_L02_001B1464, scale, half, one);
        boxHeight = scaled_coord(D_L02_001B145C, scale, half, one);
        FontSetWindow(rect, boxX, boxY, D_L02_001B1468, D_L02_001B146C, D_L02_001B1458, boxHeight,
                      D_L02_001B1470, 3);
    }
    DrawTextWindowSmallFont(rect, D_L02_001B1454, text, strlen_001157AC(text));
}
