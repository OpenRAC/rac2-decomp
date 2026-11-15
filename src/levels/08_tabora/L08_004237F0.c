#include "include_asm.h"
#include "names.h"
typedef unsigned char u8;
typedef unsigned short u16;
typedef short s16;
typedef int s32;
typedef float f32;

typedef struct { u8 pad[0x100]; } Ent;

extern int func_2F9A90();
extern s32 func_327898(s32, s32);
extern void func_329EC0(Ent *, f32);

/* Counts down the creature's timers and ages it by one frame. */
void sandfly_tick_timers(char *moby) {
    char *self = moby;
    char *vars = *(char **)(self + 0x68);

    if (*(u8 *)(self + 0xBC) != 0) {
        *(u8 *)(self + 0xBC) = 0;
        if (*(s16 *)(vars + 0x1BA) < 0xC8) {
            *(s16 *)(vars + 0x1BA) = (s16)func_327898(0x12C, 0x168);
        }
    }
    if (*(s32 *)(vars + 0x144) == 2) {
        func_2F9A90(vars + 0x1BA);
    }
    if (*(u16 *)(self + 0x96) < 0x7FFD) {
        *(u16 *)(self + 0x96) += 1;
    }
    func_2F9A90(vars + 0x1B8);
    func_2F9A90(vars + 0x1BC);
    if (*(u8 *)(self + 0x20) >= 2) {
        func_329EC0((Ent *)self, *(f32 *)(vars + 0x1B0));
    }
}

