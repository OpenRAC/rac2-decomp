#include "include_asm.h"
#include "names.h"

typedef unsigned char u8;

typedef int s32;

extern void F624a0727_FUN_00336A78(char *target);

#ifndef RAC2_T_ENTRY_F624A0727
#define RAC2_T_ENTRY_F624A0727
typedef struct { char pad[8]; short n; void (*fn)(char *); } ENTRY_F624a0727;
#endif

typedef float f32;

extern void *F8b17817c_FUN_003361A8(char *block);

extern char *F8b17817c_FUN_00336968(char *block);

extern void *F8b17817c_FUN_003366D0(char *block);

extern int Ffb202470_FUN_0033AB50(char *p);

/* Measured target: byte-identical across all 27 levels. */
/* Turns the extra labels of the button prompt bar on or off. */
void prompt_bar_set_extras_enabled(u8 *bar, s32 enabled) { *(s32 *)(bar + 0x294) = enabled; }

extern void object_set_first_float4(void *, float, float, float, float);
extern void object_set_value_float(void *, float);

/* Moves the icons and text of the button prompt bar to the bar position each frame. */
void prompt_bar_update(char *object) {
    char *slotRecord = object + 12;
    char *slotFlag = object + 0x188;
    int i;
    for (i = 4; i >= 0; i--) {
        if (*(short *)slotFlag != 0) {
            float *position = *(float **)object;
            object_set_first_float4(slotRecord, position[0], position[1], 0.0f, 0.0f);
            object_set_value_float(slotRecord, *(float *)(object + 0x274));
        }
        slotRecord += 76;
        slotFlag += 2;
    }
    if (*(int *)(object + 0x290) != 0) {
        object_set_first_float4(object + 0x198, (*(float **)object)[0] + *(float *)(object + 0x278), (*(float **)object)[1] + *(float *)(object + 0x27C), 0.0f, 0.0f);
        object_set_first_float4(object + 0x228, (*(float **)object)[0] + *(float *)(object + 0x288), (*(float **)object)[1] + *(float *)(object + 0x28C), 0.0f, 0.0f);
        object_set_first_float4(object + 0x1E0, (*(float **)object)[0] + *(float *)(object + 0x280), (*(float **)object)[1] + *(float *)(object + 0x284), 0.0f, 0.0f);
    }
}

/* Draws the icons and text of the button prompt bar. */
void prompt_bar_draw(char *object)
{
    char *slotRecord = object + 12;
    char *slotVtable = object + 60;
    char *slotFlag = object + 392;
    int i;

    for (i = 4; i >= 0; i--) {
        if (*(short *)slotFlag != 0) {
            ENTRY_F624a0727 *vtable = *(ENTRY_F624a0727 **)slotVtable;
            vtable->fn(slotRecord + vtable->n);
        }
        slotRecord += 76;
        slotVtable += 76;
        slotFlag += 2;
    }
    if (*(int *)(object + 656) != 0) {
        F624a0727_FUN_00336A78(object + 408);
        if (*(int *)(object + 660) != 0) {
            if (*(int *)(object + 668) != 0)
                F624a0727_FUN_00336A78(object + 552);
            if (*(int *)(object + 664) != 0)
                F624a0727_FUN_00336A78(object + 480);
        }
    }
}

/* Sets the x and y position of a menu. */
void menu_set_anchor_pos(float **position, float x, float y) {
    (*position)[0] = x;
    (*position)[1] = y;
}

/* Sets where the three text labels sit relative to the bar position. */
void prompt_bar_set_text_offsets(u8 *bar, f32 textAX, f32 textAY, f32 textBX, f32 textBY, f32 textCX, f32 textCY) {
    *(f32 *)(bar + 0x278) = textAX;
    *(f32 *)(bar + 0x27C) = textAY;
    *(f32 *)(bar + 0x288) = textBX;
    *(f32 *)(bar + 0x28C) = textBY;
    *(f32 *)(bar + 0x280) = textCX;
    *(f32 *)(bar + 0x284) = textCY;
}

/* Sets the three text strings shown on the button prompt bar. */
void prompt_bar_set_texts(int object, unsigned int textA, unsigned int textB, unsigned int textC)
{
    hud_set_widget_field_b(object + 0x198, textA);
    hud_set_widget_field_b(object + 0x228, textB);
    hud_set_widget_field_b(object + 0x1E0, textC);
}

/* Measured target: byte-identical across all 27 levels. */
/* Sets the spacing value used when the button prompt icons are placed. */
void prompt_bar_set_spacing(u8 *bar, f32 spacing) { *(f32 *)(bar + 0x274) = spacing; }


/* Cleans up all pictures and texts of the map screen and gives the screen back. */
char *map_screen_destroy(char *object)
{
    int index;
    char *block;

    F8b17817c_FUN_003361A8(object);
    F8b17817c_FUN_003361A8(object + 76);
    F8b17817c_FUN_003361A8(object + 152);
    block = object + 228;
    for (index = 2; index != -1; index--) {
        F8b17817c_FUN_003361A8(block);
        block += 76;
    }
    F8b17817c_FUN_00336968(object + 472);
    F8b17817c_FUN_00336968(object + 544);
    F8b17817c_FUN_00336968(object + 616);
    F8b17817c_FUN_003366D0(object + 688);
    F8b17817c_FUN_003366D0(object + 748);
    return object;
}


/* func_0033B170 is matched in 0033AE20-g8.c (-G8 small data). */

/* func_0033B540 is matched in 0033AE20-g8.c (-G8 small data). */


/* Cleans up the button prompt bar inside this menu and gives the menu back. */
char *map_screen_destroy_prompt_bar(char *object)
{
    Ffb202470_FUN_0033AB50(object + 8);
    return object;
}

