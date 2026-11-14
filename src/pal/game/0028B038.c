/* func_PAL_0028B038 (1,192 bytes): the PAL copy of func_0028A670 (src/game/00288D88.c), the
 * counters panel, with its frame counts for 50 Hz: the fade-in ends after 12 frames instead of
 * 14 and the fade-out starts after 6 instead of 7. Built with the v1.01 unit's flags
 * (-frac2-reload-lone-class-no-rotate -frac2-reload-reuse-pseudo-reg, config/cflags.txt). The
 * hud_coord dead-test helper is allowed by owner ruling (7 November 2026). */
#include "common.h"

typedef struct {
    int value;
    int timer;
    int age;
    short reserved;
    short state;
} CounterRow;
typedef struct {
    CounterRow rows[2];
    int shown;
    int base;
    int pending;
    int active;
    int falling;
} CounterState;
extern CounterState D_001B1928 __attribute__((sda));

typedef struct { float value[7]; } CounterWidths;
extern float D_001A8DE0[];
extern char D_001A8E00[];
extern unsigned char *D_001A8CFC __attribute__((sda));
extern float D_001B23A4 __attribute__((sda));
extern int func_00283D38(int, int, float);
extern int func_00115DA8(char *, char *, ...);
extern int func_001157AC(char *);
extern int func_00336D50(unsigned char *, int);
extern void func_00300A00(char *, int, float, float, float, float, float);
extern void func_0027F980(int, int, unsigned long long, unsigned char *, int);

/* The display mode word beside the HUD scale. */
extern int D_001B23A0 __attribute__((sda));

/* A HUD coordinate scaled for the display and rounded to a whole pixel; the display-mode test
   has no effect on the result (as func_00326A10). */
static __inline__ int hud_coord(float value, float scale, float half, int active)
{
    float scaled = value * scale + half;
    int result = (int)scaled;

    if (result != 0 && D_001B23A0 == active)
        scaled = 1.0f;
    return result;
}

void func_PAL_0028B038(void)
{
    char text[16];
    unsigned char active;
    CounterWidths widths;
    int firstX, y, secondY, x, firstY, secondX;
    unsigned int color;
    CounterRow *row;
    int i;
    unsigned int first, second;
    float fade, scale, width;
    int len;
    int one, id;

    secondX = 0;
    color = 0;
    y = 0;
    secondY = 0;
    x = 0;
    firstY = 0;
    widths = *(CounterWidths *)D_001A8DE0;
    scale = 0.0f;
    first = 0;
    second = 0;
    for (i = 0; i < 2; i++) {
        row = &D_001B1928.rows[i];
        firstX = 0;
        one = 1;
        switch (row->state) {
        case 1:
            fade = (float)row->age * 0.0714285746f;
            first = func_00283D38(0x00F0C070, 0x55F0C070, fade);
            second = func_00283D38(0x00442D00, 0x60442D00, fade);
            if (row->value < 0)
                color = func_00283D38(0x001010F0, 0x801010F0, fade);
            else
                color = func_00283D38(0x0029A1FF, 0x6029A1FF, fade);
            firstX = 499;
            firstY = 2;
            secondX = 499;
            secondY = 2;
            x = 442;
            scale = 1.0f;
            y = 36;
            break;
        case 2:
            if (row->timer < 12)
                fade = (float)row->timer * 0.0714285746f;
            else
                fade = 1.0f;
            first = 0x55F0C070;
            second = 0x60442D00;
            if (row->value < 0)
                color = func_00283D38(0x001010F0, 0x801010F0, fade);
            else
                color = func_00283D38(0x8000FFFF, 0x6029A1FF, fade);
            firstX = 499;
            firstY = 2;
            secondX = 499;
            secondY = 2;
            x = 442;
            scale = 1.0f;
            y = 36;
            break;
        case 3:
            if (row->timer < 6)
                fade = 1.0f;
            else
                fade = 1.0f - ((float)row->timer - 7.0f) * 0.142857149f;
            first = func_00283D38(0x00F0C070, 0x55F0C070, fade);
            second = func_00283D38(0x00442D00, 0x60442D00, fade);
            if (row->value < 0)
                color = func_00283D38(0x001010F0, 0x801010F0, fade);
            else
                color = func_00283D38(0x0029A1FF, 0x6029A1FF, fade);
            x = 442;
            scale = 1.0f;
            y = 36;
            firstX = 499;
            firstY = 2;
            secondX = 499;
            secondY = 2;
            break;
        }
        if (firstX) {
            func_00115DA8(text, D_001A8E00, D_001B1928.rows[i].value);
            len = func_001157AC(text);
            if (len > 0) {
                width = widths.value[len - 1];
                active = one;
                id = func_00336D50(D_001A8CFC + 0x8710, 178);
                func_00300A00((char *)id, first,
                    (float)firstX, (float)hud_coord((float)firstY, D_001B23A4, 0.5f, active), scale, scale, width);
                id = func_00336D50(D_001A8CFC + 0x8710, 179);
                func_00300A00((char *)id, second,
                    (float)secondX, (float)hud_coord((float)secondY, D_001B23A4, 0.5f, active), scale, scale, width);
                func_0027F980(x, hud_coord((float)y, D_001B23A4, 0.5f, one), (int)color, (unsigned char *)text, func_001157AC(text));
            }
        }
    }
}



