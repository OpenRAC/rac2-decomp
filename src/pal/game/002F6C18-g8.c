#include "include_asm.h"
#include "names.h"
extern float D_001A8C7C __attribute__((sda));
extern float g_screen_fade;
extern void FadeToBlack(int);

/* Publishes the slow-down factor and, while the frame rate is below one, asks
   for the six-frame path. */
void func_PAL_002F6C18(void)
{
    D_001A8C7C = 1.2f;
    if (g_screen_fade < 1.0f)
        FadeToBlack(5);
}
