#include "include_asm.h"

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
extern s32 D_001B1688 __attribute__((sda));
extern s32 func_002A77E0(s32);

/* Picks the frame of an animation record: clamp, loop, ping-pong or one-shot. */
s32 func_PAL_0028E800(Anim28DF80_State *a0) {
    s32 r = 0;
    Anim28DF80_Frame *t = D_001B188C + a0->f0;

    if (t->f0 != 0xFFFF) {
        switch (a0->f2) {
        case 0:
            r = t->f4;
            break;
        case 1:
            r = t->f4 + (D_001B1688 - a0->fC) / t->f7 % t->f2;
            break;
        case 2:
            r = (D_001B1688 - a0->fC) / t->f7 % (t->f2 * 2 - 2);
            if (r >= t->f2) {
                s32 k = r + 2;
                r = t->f2 * 2 - k;
            }
            r += t->f4;
            break;
        case 3:
            if (a0->fC < D_001B1688) {
                r = (D_001B1688 - a0->fC) / t->f7;
                if (r < t->f2 * 2 - 2) {
                    if (r >= t->f2) {
                        s32 k = r + 2;
                        r = t->f2 * 2 - k;
                    }
                    r += t->f4;
                } else {
                    r = t->f4;
                    {
                        s32 k = func_002A77E0(25) + 8;
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


extern char D_00255330[];
extern int D_001B1874 __attribute__((sda));
extern void func_0028B4D8(char *);
extern void func_0028E2A8(void);

/* Walks the records, caps their timers, moves their positions on, and lets a
   record run its own handler. */
int func_PAL_0028E9B8(int arg)
{
    char *rec;
    char *end;
    int count = 0;

    func_0028E2A8();
    rec = (char *)D_00255330;
    end = (char *)D_00255330 + 0x750;
    do {
        int v;

        if ((*(int *)(rec + 4) & 0x10) || D_001B1874) {
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
                func_0028B4D8(rec);
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

