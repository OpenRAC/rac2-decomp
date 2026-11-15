/* func_0028DF80: the two globals are sda words, read with the lw macro as retail does.
 * The frame number and the result are one variable (retail keeps both in $s0), and the
 * ping-pong reflection and the re-arm time keep their sums in separate statements, so
 * fold does not reassociate them: retail adds the 2 and the 10 first. */
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

extern Anim28DF80_Frame *D_001B188C __attribute__((sda));
extern s32 g_game_time __attribute__((sda));
extern s32 math_random_int_below(s32);

/* Picks the frame of an animation record: clamp, loop, ping-pong or one-shot. */
s32 func_0028DF80(Anim28DF80_State *a0) {
    s32 r = 0;
    Anim28DF80_Frame *t = D_001B188C + a0->f0;

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
                        s32 k = math_random_int_below(30) + 10;
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
