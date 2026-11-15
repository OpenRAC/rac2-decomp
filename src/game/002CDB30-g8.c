#include "common.h"

typedef struct {
    char reserved00[0x14];
    char *source;
    int value;
    char reserved1c[0x118];
    int fallback;
} CallbackState;

/* 0x18-byte rows; the halfword at +0xA is shown for the selected row. */
typedef struct {
    char reserved00[0xA];
    short value;
    char reserved0c[0xC];
} TableRow;

typedef struct {
    char reserved00[0x58];
    int value;
} MenuCounter;

typedef struct {
    char reserved00[0x34];
    int value;
    int reserved38;
    int motion;
} MenuSelection;

extern int D_00138344 NOT_SDA;
extern CallbackState D_001F2840;
extern int D_001AB9B0 __attribute__((sda));
extern int D_001AB9B4 __attribute__((sda));
extern int D_001AB9B8 __attribute__((sda));
/* Two halfword counts per row (see func_002A6AE0). */
extern unsigned short D_00188510[][2];
extern TableRow D_00264630[];
extern MenuCounter D_0025ABC0;
extern MenuSelection D_0025AC28;
extern int func_002E5E58(int, unsigned int, void *);

/* Handles the left and right buttons on the item list menu and picks the nearest rows that have items. */
int func_002CDB30(void)
{
    int flags = D_00138344;
    int previousRow = D_001AB9B0;
    int result = 0;

    if (flags & 0x10) {
        int value = *(int *)(gPauseMenuState.source + 0xE0);
        if (value != 0)
            gPauseMenuState.value = value;
        else if (gPauseMenuState.fallback == 0) {
            value = -1;
            goto return_value;
        }
        value = 0;
return_value:
        return value;
    }
    if (flags & 0x900) {
        result = 1;
    } else if (flags & 0x8000) {
        if (previousRow != D_001AB9B4)
            PlaySoundFromGlobalBank(3, 0, 0);
        else
            PlaySoundFromGlobalBank(5, 0, 0);
        D_001AB9B0 = D_001AB9B4;
        if (D_001AB9B0 <= 0)
            D_001AB9B0 = 1;
    } else if (flags & 0x2000) {
        if (previousRow != D_001AB9B8)
            PlaySoundFromGlobalBank(3, 0, 0);
        else
            PlaySoundFromGlobalBank(5, 0, 0);
        D_001AB9B0 = D_001AB9B8;
        if (D_001AB9B0 >= 64)
            D_001AB9B0 = 63;
    }

    /* The nearest rows below and above the current one with a nonzero count;
       row 1 and the current row when there is none. */
    D_001AB9B8 = D_001AB9B0 + 1;
    D_001AB9B4 = D_001AB9B0 - 1;
    for (;;) {
        if (D_00188510[D_001AB9B4][0] != 0 || D_00188510[D_001AB9B4][1] != 0)
            break;
        if (--D_001AB9B4 <= 0) {
            D_001AB9B4 = 1;
            break;
        }
    }
    {
        int currentRow = D_001AB9B0;
        for (;;) {
            if (D_00188510[D_001AB9B8][0] != 0 || D_00188510[D_001AB9B8][1] != 0)
                break;
            if (++D_001AB9B8 >= 64) {
                D_001AB9B8 = currentRow;
                break;
            }
        }
    }

    if (D_00188510[D_001AB9B0][0] == 0 && D_00188510[D_001AB9B0][1] == 0) {
        D_0025ABC0.value = 63;
        D_0025AC28.value = 0;
    } else {
        D_0025ABC0.value = D_001AB9B0 - 1;
        D_0025AC28.value = D_00264630[D_001AB9B0].value;
    }
    if (D_001AB9B0 != previousRow)
        D_0025AC28.motion = -576;
    return result;
}
