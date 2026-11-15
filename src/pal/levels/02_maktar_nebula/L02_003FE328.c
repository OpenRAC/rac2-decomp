#include "include_asm.h"
#include "names.h"


typedef unsigned char u8;
typedef unsigned short u16;
extern int math_fast_float_d(void *);
extern void gfx_add_draw_callback_third(char *, char *);
extern void module_l00_call_handler_2(void);
extern char D_L02_004004D8[];
extern u8 D_001395B8[];

void func_PAL_L02_003FF640(char *a0) {
    char *s0 = a0;
    char *obj = *(char **)(s0 + 0x68);
    u16 timer = *(u16 *)(s0 + 0x96);

    if (timer <= 0xFFFE)
        *(u16 *)(s0 + 0x96) = timer + 1;
    math_fast_float_d(obj + 0xE4);
    if (*(u8 *)(s0 + 0x20) > 1)
        gfx_add_draw_callback_third(D_L02_004004D8, s0);
    module_l00_call_handler_2();
}

