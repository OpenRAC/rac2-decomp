#include "names.h"
/* func_PAL_L18_003FDE80, the PAL copy of func_L18_003F9DA0: the same C, where func_L00_002D70A0
   becomes func_PAL_L00_002D7850. */
#include "include_asm.h"
#include "common.h"

extern s32 g_color_effect_freed_flag NOT_SDA;

extern const float g_color_a_r __attribute__((sda));
extern const float g_color_a_g __attribute__((sda));
extern const float g_color_a_b __attribute__((sda));
extern const float g_color_b_r __attribute__((sda));
extern const float g_color_b_g __attribute__((sda));
extern const float g_color_b_b __attribute__((sda));
extern const float g_color_c_r __attribute__((sda));
extern const float g_color_c_g __attribute__((sda));
extern const float g_color_c_b __attribute__((sda));
extern void *cam_alloc_override_slot_pal(s32);
extern void cam_end_override(void *);

/* While D_L18_001C9D40 is clear: allocates the vector at +0x80 of the object's state block
   (func_PAL_L00_002D7850(5)) when it has none, else sets it to the constant triple of MODE (1, 2 or
   any other). Once D_L18_001C9D40 is set: frees the vector and clears the pointer. */
void moby_set_color_effect_pal(char *a0, s32 mode)
{
    char *state = *(char **)(a0 + 0x68);

    if (g_color_effect_freed_flag == 0) {
        if (*(float **)(state + 0x80) == 0) {
            *(void **)(state + 0x80) = cam_alloc_override_slot_pal(5);
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
