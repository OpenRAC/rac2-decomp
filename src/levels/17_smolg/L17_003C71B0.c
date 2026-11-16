#include "include_asm.h"
#include "names.h"

typedef char *ptr;
typedef unsigned char u8;
typedef unsigned short u16;
typedef short s16;
typedef int s32;

extern void part_spawn_effect_burst(void *, s32, s32, s32, s32, s32, s32, void *);
extern s32 PlayMobySound(s32, s32, void *);
extern char g_effect_color_params[];

/* Wakes up the object when it is still idle: starts its effect and sound, turns off its
   collision and moves it to state 1. */
void falling_object_wake_up(char *moby)
{
    char *self = moby;

    if (*(s16 *)(self + 0xAA) == 0x929 /* moby class 2345 */ && *(u8 *)(self + 0x20) == 0) {
        part_spawn_effect_burst(self, 0x931, 0, 0x931, 4, 6, 0, g_effect_color_params);
        PlayMobySound(0, 0, self);
        *(u16 *)(self + 0x34) = *(u16 *)(self + 0x34) | 0x41;
        *(s32 *)(self + 0x98) = 0;
        if (self != 0) {
            if (*(u8 *)(self + 0x20) != 0xFE) {
                if (*(u8 *)(self + 0x20) != 0xFD)
                    *(u8 *)(self + 0x20) = 1;
            }
        }
    }
}
