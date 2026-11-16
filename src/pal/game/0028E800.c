#include "include_asm.h"
#include "names.h"

typedef unsigned char u8;
typedef unsigned short u16;
typedef int s32;
typedef struct Anim28DF80_Frame {
    u16 f0;
    u16 f2;
    u16 f4;
    u8 pad6;
    u8 f7;
} Anim28DF80_Frame;
typedef struct Anim28DF80_State {
    short f0;
    u8 f2;
    s32 f4;
    char pad8[4];
    s32 fC;
} Anim28DF80_State;
extern Anim28DF80_Frame *g_hud_element_table __attribute__((sda));
extern s32 g_game_time __attribute__((sda));
extern s32 math_random_int_below(s32);

/* Picks the frame of an animation record: clamp, loop, ping-pong or one-shot. */
s32 func_PAL_0028E800(Anim28DF80_State *a0) {
    s32 r = 0;
    Anim28DF80_Frame *t = g_hud_element_table + a0->f0;

    if (t->f0 != 0xFFFF) {
        switch (a0->f2) {
        case 0:
            r = t->f4;
            break;
        case 1:
            r = t->f4 + (g_game_time - a0->fC) / t->f7 % t->f2;
            break;
        case 2:
            r = (g_game_time - a0->fC) / t->f7 % (t->f2 * 2 - 2);
            if (r >= t->f2) {
                s32 k = r + 2;
                r = t->f2 * 2 - k;
            }
            r += t->f4;
            break;
        case 3:
            if (a0->fC < g_game_time) {
                r = (g_game_time - a0->fC) / t->f7;
                if (r < t->f2 * 2 - 2) {
                    if (r >= t->f2) {
                        s32 k = r + 2;
                        r = t->f2 * 2 - k;
                    }
                    r += t->f4;
                } else {
                    r = t->f4;
                    {
                        s32 k = math_random_int_below(25) + 8;
                        a0->fC = t->f2 * 2 + k;
                    }
                }
            } else {
                r = a0->f4;
            }
            break;
        }
    }
    a0->f4 = r;
    return r;
}


extern char g_hud_elements[];
extern int g_hud_record_timer_flag __attribute__((sda));
extern void hud_finish_element_setup(char *);
extern void weapon_menu_update_entry(void);

/* Walks the records, caps their timers, moves their positions on, and lets a
   record run its own handler. */
int hud_update_record_timers_pal(int arg)
{
    char *rec;
    char *end;
    int count = 0;

    weapon_menu_update_entry();
    rec = (char *)g_hud_elements;
    end = (char *)g_hud_elements + 0x750;
    do {
        int v;

        if ((*(int *)(rec + 4) & 0x10) || g_hud_record_timer_flag) {
            v = *(int *)(rec + 0x7C);
            if (v < 8) {
                *(int *)(rec + 0x7C) = 8;
            }
            v = *(int *)(rec + 0x7C);
        } else {
            v = *(int *)(rec + 0x7C);
        }

        if (v > 0) {
            v = v - 1;
            *(int *)(rec + 0x7C) = v;
            if (v > 0) {
                count++;
                if (*(int *)(rec + 0x6C) < 30) {
                    *(int *)(rec + 0x6C) = *(int *)(rec + 0x6C) + 1;
                }
            } else if (*(int *)(rec + 0x6C) >= -5) {
                *(int *)(rec + 0x6C) = *(int *)(rec + 0x6C) - 1;
            }
        } else if (*(int *)(rec + 0x6C) >= -5) {
            *(int *)(rec + 0x6C) = *(int *)(rec + 0x6C) - 1;
        }

        if (*(int *)(rec + 0x68) != 0) {
            if (*(int *)(rec + 0x6C) == -6) {
                hud_finish_element_setup(rec);
            }
        }

        if (arg != 0) {
            void (*handler)(char *) = *(void (**)(char *))(rec + 0x14);
            if (handler) {
                handler(rec);
            }
        }
        rec += 0x90;
    } while ((int)rec < (int)end);
    return count;
}

