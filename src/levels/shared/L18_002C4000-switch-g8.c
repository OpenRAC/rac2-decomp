#include "include_asm.h"
#include "common.h"

/* -G8 for the nine $gp constants; -frac2-keep-block-order (config/cflags.txt) keeps the default
   case after the numbered ones, as retail lays the compare chain out. */

/* Read absolutely (lui/lw) although it is a word. */
extern s32 g_color_effect_freed_flag NOT_SDA;

/* Three constant triples. Read-only, so sched1 may load them ahead of the stores through the
   object's vector; the stores' common tail then cross-jumps between the three cases. */
extern const float g_color_a_r __attribute__((sda));
extern const float g_color_a_g __attribute__((sda));
extern const float g_color_a_b __attribute__((sda));
extern const float g_color_b_r __attribute__((sda));
extern const float g_color_b_g __attribute__((sda));
extern const float g_color_b_b __attribute__((sda));
extern const float g_color_c_r __attribute__((sda));
extern const float g_color_c_g __attribute__((sda));
extern const float g_color_c_b __attribute__((sda));
extern void *cam_alloc_override_slot(s32);
extern void cam_end_override(void *);

/* While D_L18_001C9D40 is clear: allocates the vector at +0x80 of the object's state block
   (func_L00_002D70A0(5)) when it has none, else sets it to the constant triple of MODE (1, 2 or
   any other). Once D_L18_001C9D40 is set: frees the vector and clears the pointer. */
/* Turns a colour effect on the object on or off, and picks one of three colours for it. */
void moby_set_color_effect(char *object, s32 mode)
{
    char *state = *(char **)(object + 0x68);

    if (g_color_effect_freed_flag == 0) {
        if (*(float **)(state + 0x80) == 0) {
            *(void **)(state + 0x80) = cam_alloc_override_slot(5);
        } else {
            switch (mode) {
            case 1:
                (*(float **)(state + 0x80))[0] = g_color_b_r;
                (*(float **)(state + 0x80))[1] = g_color_b_g;
                (*(float **)(state + 0x80))[2] = g_color_b_b;
                break;
            case 2:
                (*(float **)(state + 0x80))[0] = g_color_c_r;
                (*(float **)(state + 0x80))[1] = g_color_c_g;
                (*(float **)(state + 0x80))[2] = g_color_c_b;
                break;
            default:
                (*(float **)(state + 0x80))[0] = g_color_a_r;
                (*(float **)(state + 0x80))[1] = g_color_a_g;
                (*(float **)(state + 0x80))[2] = g_color_a_b;
                break;
            }
        }
    } else {
        cam_end_override(*(void **)(state + 0x80));
        *(int *)(state + 0x80) = 0;
    }
}
