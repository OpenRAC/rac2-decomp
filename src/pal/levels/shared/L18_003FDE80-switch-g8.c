/* func_PAL_L18_003FDE80, the PAL copy of func_L18_003F9DA0: the same C, where func_L00_002D70A0
   becomes func_PAL_L00_002D7850. */
#include "include_asm.h"
#include "common.h"

extern s32 D_L18_001C9D40 NOT_SDA;

extern const float D_L18_001B0430 __attribute__((sda));
extern const float D_L18_001B0434 __attribute__((sda));
extern const float D_L18_001B0438 __attribute__((sda));
extern const float D_L18_001B043C __attribute__((sda));
extern const float D_L18_001B0440 __attribute__((sda));
extern const float D_L18_001B0444 __attribute__((sda));
extern const float D_L18_001B0448 __attribute__((sda));
extern const float D_L18_001B044C __attribute__((sda));
extern const float D_L18_001B0450 __attribute__((sda));
extern void *func_PAL_L00_002D7850(s32);
extern void func_L00_002D7140(void *);

/* While D_L18_001C9D40 is clear: allocates the vector at +0x80 of the object's state block
   (func_PAL_L00_002D7850(5)) when it has none, else sets it to the constant triple of MODE (1, 2 or
   any other). Once D_L18_001C9D40 is set: frees the vector and clears the pointer. */
void func_PAL_L18_003FDE80(char *a0, s32 mode)
{
    char *state = *(char **)(a0 + 0x68);

    if (D_L18_001C9D40 == 0) {
        if (*(float **)(state + 0x80) == 0) {
            *(void **)(state + 0x80) = func_PAL_L00_002D7850(5);
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
        func_L00_002D7140(*(void **)(state + 0x80));
        *(int *)(state + 0x80) = 0;
    }
}
