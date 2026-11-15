#include "include_asm.h"
#include "names.h"

typedef int s32;

typedef unsigned char u8;

extern void prompt_bar_set_texts_enabled(unsigned char *owner, int value);

extern char *func_00288FB8_3(int);

extern void prompt_bar_set_texts(char *, int, int, int);

extern void prompt_bar_set_spacing(char *, float);

extern char *func_00288FB8_5(int);

extern void func_0033B050_1(void *, void *, void *, void *);

extern void func_0033B0A8_1(void *, float);

/* Turns on the pop-up's flag at offset 0x300. */
void popup_set_flag_on(u8 *popup) {s32 flagValue=1;*(s32 *)(popup+0x300)=flagValue;}

/* Passes a value on to the pop-up's inner box. */
void popup_set_box_value(unsigned char *popup, int value)
{
    prompt_bar_set_texts_enabled(popup + 8, value);
}

/* Measured target: byte-identical across all 27 levels. */
/* Sets which row the pop-up is on. */
void popup_set_row(u8 *popup, s32 row) { *(s32 *)(popup + 0x2f8) = row; }

/* Calls a one-argument helper three times with three fixed small integers, passes the three results and a pointer plus 8 to a four-argument helper, calls a two-argument helper with the same address and 0.0f, then clears the word at offset 764. */
/* Sets the pop-up's three texts and resets its scale, then clears its flag. */
void popup_init_texts_hidden(char *popup)
{
    int first = func_00288FB8_3(11678);
    int second = func_00288FB8_3(11676);

    prompt_bar_set_texts(popup + 8, first, second, func_00288FB8_3(11599));
    prompt_bar_set_spacing(popup + 8, 0.0f);
    *(int *)(popup + 764) = 0;
}

/* looks up three objects by numeric id, runs a four-argument routine and a (pointer,float) routine on a sub-object at self+8, then stores 1 at self+764 */
/* Sets the pop-up's three texts and resets its scale, then sets its flag. */
void popup_init_texts_shown(int *popup)
{
    void *firstText;
    void *secondText;
    void *thirdText;
    void *box = (void *)(popup + 2);

    firstText = func_00288FB8_5(11677);
    secondText = func_00288FB8_5(11676);
    thirdText = func_00288FB8_5(11599);

    func_0033B050_1(box, firstText, secondText, thirdText);
    func_0033B0A8_1(box, 0.0f);

    popup[191] = 1;
}

