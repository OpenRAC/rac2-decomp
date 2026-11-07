/* func_US2_002DE768, the USA v2.00 copy of func_002DDA10 (src/game/002D5E98-g8.c): the same C, where
   the score line prints the plain number right aligned in a column through func_0027FA10 and then
   draws a separator string every three digits, a comma or, in languages 3 to 5, a full stop. The
   empty-slot text is 0x2DAA. The language byte is element 4 of the byte table at D_001A7BB0: the
   symbol-plus-offset form is the unsplit two-word load, which reorg keeps out of the delay slot of
   the digit-count loop's first test. */
#include "include_asm.h"
#include "common.h"
extern void func_0027C540(int);
extern void func_0027C660(void);
extern int func_0028E588(int, int);
extern void func_0028E868(int, int, int, int, int, int);
extern int D_001A7420;
extern char D_001F2840[];

/* One save-slot summary row of the save context at D_001393E0 (28 bytes). */
typedef struct {
    int state;              /* -1: empty slot */
    int score;
    int extra;
    int ticks;              /* play time, 60 per second */
    unsigned char pad[4];
    unsigned char date[4];
    int unknown;
} SaveRow;

typedef struct {
    int head[12];
    SaveRow records[4];     /* D_00139410 */
    unsigned char gap[0x15C - 0xA0];
    int mode;
    int unknown160;
    int selected;
} SaveData;

extern SaveRow D_00139410[];

/* GP-relative layout coefficients of the save-slot panel. */
extern int D_001ABBF0 __attribute__((sda)); /* line height */
extern int D_001ABBF4 __attribute__((sda)); /* slot gap */
extern int D_001ABBF8 __attribute__((sda));
extern int D_001ABBFC __attribute__((sda));
extern int D_001ABC00 __attribute__((sda));
extern int D_001ABC04 __attribute__((sda));
extern int D_001ABC08 __attribute__((sda));
extern int D_001ABC10 __attribute__((sda));
extern int D_001ABC14[] MACRO_ADDR;
extern int D_001ABC18 __attribute__((sda));
extern int D_001ABC1C[] MACRO_ADDR;
extern int D_001ABC20 __attribute__((sda));

/* Format strings. */
extern char D_001ABC28[] NOT_SDA;
extern char D_001ABAF0[] NOT_SDA;
extern char D_001ABB20[] NOT_SDA;
extern char D_001ABC48[] NOT_SDA;

extern void func_0027F5B8(int, int, long, char *, int);
extern int func_0027FB40(int, int, u64, char *, int);
extern char *func_00288FB8(int);
extern int func_00115DA8(char *, char *, ...);

extern unsigned char D_001A7BB0[] __attribute__((sda));
extern int D_US2_001ABC9C __attribute__((sda));     /* score column width */
extern int D_US2_001ABCA0 __attribute__((sda));     /* comma offset */
extern int D_US2_001ABCA4 __attribute__((sda));
extern int D_US2_001ABCA8 __attribute__((sda));     /* full stop offset */
extern int D_US2_001ABCAC __attribute__((sda));
extern float D_US2_001ABCB0 __attribute__((sda));   /* digit width */
extern char D_US2_001ABCB8[] NOT_SDA;               /* "," */
extern char D_US2_001ABCC0[] NOT_SDA;               /* "." */
extern void func_0027FA10(int, int, long, char *, int);

int func_US2_002DE768(char *menu)
{
    char text[80];
    SaveRow *record;
    SaveData *context;
    int y, hours, minutes, score, extra, color, i;
    int digits, rest, comma, language, offsetX, offsetY;
    float place;

    if (D_001A7420 == 10)
        return 2;

    y = *(int *)(menu + 0x1C);
    func_0027C540(0);
    func_0028E868(func_0028E588(0xEAA9, 0), D_001ABC10, D_001ABC14[0], D_001ABC18, D_001ABC1C[0], D_001ABC20);

    for (i = 0; i < 4; i++) {
        record = &D_00139410[i];
        context = (SaveData *)((char *)D_00139410 - 0x30);
        if (context->mode >= 3 || context->selected >= 0 || *(int *)(D_001F2840 + 0x164) <= 10 || context->head[2] != 2) {
            y += D_001ABBF0 * 3;
        } else if (record->state == -1) {
            y += D_001ABBF0;
            func_0027FB40(*(int *)(menu + 0x18) + *(int *)(menu + 0x20) / 2, y + D_001ABC08, 0x80F0F0F0UL,
                          func_00288FB8(0x2DAA), -1);
            y += D_001ABBF0;
            y += D_001ABBF0;
        } else {
            hours = record->ticks / 216000;
            minutes = record->ticks / 3600 - hours * 60;
            color = 0x80F0F0F0;
            if (*(int *)(menu + 0x40) == i)
                color = 0x70FFFEED;
            if (hours > 99) {
                hours = 99;
                minutes = 59;
            }
            func_00115DA8(text, D_001ABC28, hours, minutes);
            func_0028E868(func_0028E588(0xE99D, 3), D_001ABC04 + 4, y + D_001ABC08, D_001ABBF8, D_001ABBFC, 128);
            func_0027F5B8(D_001ABC04 + (long)(D_001ABBFC + 6), y + D_001ABC08, color, text, -1);

            if (record->extra) {
                int iconRight, extraX;

                func_0028E868(func_0028E588(0xE99D, 4), D_001ABC04 + D_001ABC00, y + D_001ABC08, D_001ABBF8,
                              D_001ABBFC, 128);
                extra = record->extra;
                if (extra > 99)
                    extra = 99;
                func_00115DA8(text, D_001ABAF0, extra);
                iconRight = D_001ABBFC + 2;
                extraX = D_001ABC04 + iconRight;
                func_0027F5B8((long)extraX + D_001ABC00, y + D_001ABC08, color, text, -1);
            }

            score = record->score;
            if (score > 9999999)
                score = 9999999;
            y += D_001ABBF0;
            func_00115DA8(text, D_001ABAF0, score);
            func_0028E868(func_0028E588(0x7567, 0), D_001ABC04 + 4, y + D_001ABC08, D_001ABBF8, D_001ABBFC, 128);
            {
                int iconRight, scoreX;

                iconRight = D_001ABBFC + 6;
                scoreX = D_001ABC04 + iconRight;
                func_0027FA10((long)scoreX + D_US2_001ABC9C, y + D_001ABC08, color, text, -1);
            }
            digits = 1;
            for (rest = score; rest >= 10; rest /= 10)
                digits++;
            language = D_001A7BB0[4];
            comma = language != 3 && language != 5 && language != 4;
            func_00115DA8(text, comma ? D_US2_001ABCB8 : D_US2_001ABCC0);
            offsetY = comma ? D_US2_001ABCA4 : D_US2_001ABCAC;
            offsetX = comma ? D_US2_001ABCA0 : D_US2_001ABCA8;
            for (place = 3.0f; place < (float)digits; place += 3.0f) {
                func_0027FA10(D_001ABC04 + offsetX + (long)(D_001ABBFC + 6) + D_US2_001ABC9C - (int)(D_US2_001ABCB0 * place),
                              y + D_001ABC08 + offsetY, color, text, -1);
            }
            y += D_001ABBF0;

            func_00115DA8(text, D_001ABC48, record->date[2], record->date[1], record->date[3]);
            func_0028E868(func_0028E588(0xE99D, 2), D_001ABC04 + 4, y + D_001ABC08, D_001ABBF8, D_001ABBFC, 128);
            func_0027F5B8(D_001ABC04 + (long)(D_001ABBFC + 6), y + D_001ABC08, color, text, -1);
            y += D_001ABBF0;
        }
        y += D_001ABBF4;
    }
    func_0027C660();
    return 2;
}
