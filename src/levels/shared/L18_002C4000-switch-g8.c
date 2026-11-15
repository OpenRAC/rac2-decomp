#include "include_asm.h"
#include "common.h"

/* -G8 for the nine $gp constants; -frac2-keep-block-order (config/cflags.txt) keeps the default
   case after the numbered ones, as retail lays the compare chain out. */

/* Read absolutely (lui/lw) although it is a word. */
extern s32 D_L18_001C9D40 NOT_SDA;

/* Three constant triples. Read-only, so sched1 may load them ahead of the stores through the
   object's vector; the stores' common tail then cross-jumps between the three cases. */
extern const float D_L18_001B0430 __attribute__((sda));
extern const float D_L18_001B0434 __attribute__((sda));
extern const float D_L18_001B0438 __attribute__((sda));
extern const float D_L18_001B043C __attribute__((sda));
extern const float D_L18_001B0440 __attribute__((sda));
extern const float D_L18_001B0444 __attribute__((sda));
extern const float D_L18_001B0448 __attribute__((sda));
extern const float D_L18_001B044C __attribute__((sda));
extern const float D_L18_001B0450 __attribute__((sda));
extern void *cam_alloc_override_slot(s32);
extern void cam_end_override(void *);

/* While D_L18_001C9D40 is clear: allocates the vector at +0x80 of the object's state block
   (func_L00_002D70A0(5)) when it has none, else sets it to the constant triple of MODE (1, 2 or
   any other). Once D_L18_001C9D40 is set: frees the vector and clears the pointer. */
/* Turns a colour effect on the object on or off, and picks one of three colours for it. */
void moby_set_color_effect(char *object, s32 mode)
{
    char *state = *(char **)(object + 0x68);

    if (D_L18_001C9D40 == 0) {
        if (*(float **)(state + 0x80) == 0) {
            *(void **)(state + 0x80) = cam_alloc_override_slot(5);
        } else {
            switch (mode) {
            case 1:
                (*(float **)(state + 0x80))[0] = D_L18_001B043C;
                (*(float **)(state + 0x80))[1] = D_L18_001B0440;
                (*(float **)(state + 0x80))[2] = D_L18_001B0444;
                break;
            case 2:
                (*(float **)(state + 0x80))[0] = D_L18_001B0448;
                (*(float **)(state + 0x80))[1] = D_L18_001B044C;
                (*(float **)(state + 0x80))[2] = D_L18_001B0450;
                break;
            default:
                (*(float **)(state + 0x80))[0] = D_L18_001B0430;
                (*(float **)(state + 0x80))[1] = D_L18_001B0434;
                (*(float **)(state + 0x80))[2] = D_L18_001B0438;
                break;
            }
        }
    } else {
        cam_end_override(*(void **)(state + 0x80));
        *(int *)(state + 0x80) = 0;
    }
}
