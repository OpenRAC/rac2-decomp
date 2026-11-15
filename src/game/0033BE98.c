#include "include_asm.h"
#include "names.h"

extern void Fe524d931_FUN_0033AE28(char *p);

extern void Fe524d931_FUN_0033B018(char *p, float x, float y);

extern void Fe524d931_FUN_002E5E58(int a, int b, int c);

extern void Fe524d931_FUN_00284E40(void);

extern short Fe524d931_D_001A6480[];

extern void Ffb202470_FUN_0033AB50(char *p);

/* Updates the screen-adjust menu: moves the screen offset with the d-pad (within limits) and plays a sound when it changes. */
int screen_adjust_menu_update(char *object, int mask)
{
    char *prompt = object + 8;
    short oldX;
    short oldY;
    int *anchor;

    Fe524d931_FUN_0033AE28(prompt);
    anchor = *(int **)(object + 684);
    Fe524d931_FUN_0033B018(prompt, *(float *)anchor, *(float *)(anchor + 1));
    if ((mask & 0x40) != 0 && *(int *)(object + 680) == 0)
        Fe524d931_FUN_002E5E58(4, 0, 0);
    if ((mask & 0xf000) != 0) {
        short *offsets = Fe524d931_D_001A6480;
        oldX = offsets[180];
        oldY = offsets[181];
        if ((mask & 0x1000) != 0) {
            ((unsigned short *)offsets)[181] = ((unsigned short *)offsets)[181] - 1;
            if ((short)((unsigned short *)offsets)[181] < -32)
                offsets[181] = -32;
        }
        if ((mask & 0x4000) != 0) {
            unsigned short *offsets = (unsigned short *)Fe524d931_D_001A6480;
            offsets[181] = offsets[181] + 1;
            if ((short)offsets[181] > 32)
                ((short *)offsets)[181] = 32;
        }
        if ((mask & 0x8000) != 0) {
            unsigned short *offsets = (unsigned short *)Fe524d931_D_001A6480;
            offsets[180] = offsets[180] - 1;
            if ((short)offsets[180] < -40)
                ((short *)offsets)[180] = -40;
        }
        if ((mask & 0x2000) != 0) {
            unsigned short *offsets = (unsigned short *)Fe524d931_D_001A6480;
            offsets[180] = offsets[180] + 1;
            if ((short)offsets[180] > 40)
                ((short *)offsets)[180] = 40;
        }
        {
            short *offsets = Fe524d931_D_001A6480;
            if (oldX != offsets[180] || oldY != offsets[181])
                Fe524d931_FUN_002E5E58(4, 0, 0);
        }
        Fe524d931_FUN_00284E40();
    }
    return (mask >> 6) & 1;
}

/* func_0033C028 is matched in its own unit, src/game/0033C028-qcopy.c (-frac2-qcopy -frac2-qcopy-barrier). */

/* Cleans up the button prompt bar inside the screen-adjust menu and gives the menu back. */
char *screen_adjust_menu_destroy(char *object)
{
    Ffb202470_FUN_0033AB50(object + 8);
    return object;
}



typedef struct { int ids[2]; } SolTextPair;
extern SolTextPair D_L00_001AE110;
extern char D_L00_001AE118[];
/* Resident byte at 0x001A7BB1 is shared by all programs. */
extern void prompt_bar_draw(void *);
extern char *GetLocalizedString(int);
extern int sprintf(char *, const char *, ...);
extern void text_draw_centered_small(int, int, unsigned long, char *, int);

/* Draws the on/off option menu: its prompt bar and one line of text showing the current setting. */
void onoff_menu_draw(char *object)
{
    char buffer[128];
    SolTextPair pair;
    char *first;
    char *second;
    char *format;
    prompt_bar_draw(object + 8);
    pair = D_L00_001AE110;
    format = D_L00_001AE118;
    first = GetLocalizedString(0x31E4);
    second = GetLocalizedString(pair.ids[*(unsigned char *)0x001A7BB1 != 0]);
    sprintf(buffer, format, first, second);
    text_draw_centered_small(0x100, 0xAA, 0x80F0F0F0UL, buffer, -1);
}

/* Cleans up the button prompt bar inside the on/off option menu and gives the menu back. */
char *onoff_menu_destroy(char *object)
{
    Ffb202470_FUN_0033AB50(object + 8);
    return object;
}

