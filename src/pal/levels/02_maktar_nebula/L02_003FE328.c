#include "include_asm.h"
#include "names.h"


typedef unsigned char u8;
typedef unsigned short u16;
extern int math_fast_float_d(void *);
extern void gfx_add_draw_callback_third(char *, char *);
extern void module_l00_call_handler_2(void);
extern char g_stage_draw_callback[];
extern u8 g_game_flag_table[];

/* Ticks the arena controller's frame counter and timer and, once it is past state 1, registers the stage draw callback (PAL). */
void arena_tick_controller_pal(char *moby) {
    char *self = moby;
    char *vars = *(char **)(self + 0x68);
    u16 timer = *(u16 *)(self + 0x96);

    if (timer <= 0xFFFE)
        *(u16 *)(self + 0x96) = timer + 1;
    math_fast_float_d(vars + 0xE4);
    if (*(u8 *)(self + 0x20) > 1)
        gfx_add_draw_callback_third(g_stage_draw_callback, self);
    module_l00_call_handler_2();
}

