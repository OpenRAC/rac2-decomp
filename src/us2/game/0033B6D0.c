#include "include_asm.h"
#include "names.h"

typedef float f32;
typedef unsigned char u8;

/* func_0033A688 is matched in 003399B0-g8.c (-G8 small data). */

/* func_0033A6D8 is matched in 003399B0-g8.c (-G8 small data). */

/* Measured target: byte-identical across all 27 levels. */
void circle_menu_set_radius_us2(u8 *a0, f32 a1) { *(f32 *)(a0 + 0x214) = a1; }

typedef int s32;

/* lot6 -- measured bodies with sizes recorded in the catalogue. */
void circle_menu_set_entry_mode_us2(u8 *a0, s32 a1, s32 a2) { a0 += a1 * 4; *(s32 *)(a0 + 0x1C8) = a2; }

/* writes the value if it is below the maximum; byte-identical across all 27 levels. */
void circle_menu_set_selection_us2(u8 *a0, s32 a1) { if (a1 < *(s32 *)(a0 + 0x208)) *(s32 *)(a0 + 0x218) = a1; }

/* Measured target: byte-identical across all 27 levels. */
void circle_menu_set_enabled_us2(u8 *a0, s32 a1) { *(s32 *)(a0 + 0x21C) = a1; }

extern int prompt_bar_destroy(int);
extern void *F7d9c8805_FUN_003361A8(int);
extern char *F7d9c8805_FUN_00336968(int);

/* Destroys the prompt bar: its five text widgets and three sprites. */
void *prompt_bar_destroy_us2(int object)
{
	char *slot = (char *)object + 12;
	int i;

	for (i = 4; i != -1; i--) {
		F7d9c8805_FUN_003361A8(slot);
		slot += 76;
	}
	F7d9c8805_FUN_00336968(object + 408);
	F7d9c8805_FUN_00336968(object + 496);
	F7d9c8805_FUN_00336968(object + 584);
	return object;
}


extern void prompt_bar_set_texts_enabled(unsigned char *owner, int value);

/* func_0033ABD8 is matched in 003399B0-g8.c (-G8 small data). */

/* Measured target: byte-identical across all 27 levels. */
void prompt_bar_set_texts_enabled_us2(u8 *a0, s32 a1) { *(s32 *)(a0 + 0x2C0) = a1; }

/* Measured target: byte-identical across all 27 levels. */
void prompt_bar_set_extras_enabled_us2(u8 *a0, s32 a1) { *(s32 *)(a0 + 0x2C4) = a1; }

extern void object_set_first_float4(void *, float, float, float, float);
extern void object_set_value_float(void *, float);

/* Updates the prompt bar each frame: moves its widgets to the anchor position. */
void prompt_bar_update_us2(char *object) {
    char *r = object + 12;
    char *q = object + 0x188;
    int i;
    for (i = 4; i >= 0; i--) {
        if (*(short *)q != 0) {
            float *position = *(float **)object;
            object_set_first_float4(r, position[0], position[1], 0.0f, 0.0f);
            object_set_value_float(r, *(float *)(object + 0x2A4));
        }
        r += 76;
        q += 2;
    }
    if (*(int *)(object + 0x2C0) != 0) {
        object_set_first_float4(object + 0x198, (*(float **)object)[0] + *(float *)(object + 0x2A8), (*(float **)object)[1] + *(float *)(object + 0x2AC), 0.0f, 0.0f);
        object_set_first_float4(object + 0x248, (*(float **)object)[0] + *(float *)(object + 0x2B8), (*(float **)object)[1] + *(float *)(object + 0x2BC), 0.0f, 0.0f);
        object_set_first_float4(object + 0x1F0, (*(float **)object)[0] + *(float *)(object + 0x2B0), (*(float **)object)[1] + *(float *)(object + 0x2B4), 0.0f, 0.0f);
    }
}

extern void F624a0727_FUN_00336A78(char *target);
typedef struct { char pad[8]; short n; void (*fn)(char *); } ENTRY_F624a0727;

/* Draws the prompt bar: its sprites and the button prompt texts. */
void prompt_bar_draw_us2(char *object)
{
    char *r = object + 12;
    char *q = object + 60;
    char *p = object + 392;
    int i;

    for (i = 4; i >= 0; i--) {
        if (*(short *)p != 0) {
            ENTRY_F624a0727 *t = *(ENTRY_F624a0727 **)q;
            t->fn(r + t->n);
        }
        r += 76;
        q += 76;
        p += 2;
    }
    if (*(int *)(object + 704) != 0) {
        F624a0727_FUN_00336A78(object + 408);
        if (*(int *)(object + 708) != 0) {
            if (*(int *)(object + 716) != 0)
                F624a0727_FUN_00336A78(object + 584);
            if (*(int *)(object + 712) != 0)
                F624a0727_FUN_00336A78(object + 496);
        }
    }
}

