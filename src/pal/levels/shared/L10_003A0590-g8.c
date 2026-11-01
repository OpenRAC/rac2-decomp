#include "include_asm.h"

#include "common.h"
extern void *func_0029EFD0(s32);
extern short D_L10_001B2DB8[4];
extern u8 D_L10_0039D9C0[];

/* Creates a strip-effect object with its supplied vectors and rendering parameters. */
void *func_PAL_L10_003A0590(void *position, void *direction, s32 duration, s32 kind,
                       s32 first, s32 second, float jitter, s32 third, s32 texture,
                       float width, float height, float fade) {
    u8 *object = func_0029EFD0(0x133E);
    char *state;
    int i;
    if (object) {
        state = *(char **)(object + 0x68);
        object[0x30] = 255;
        *(u16 *)(object + 0x32) = 255;
        object[0x31] = 1;
        object[0x20] = 0;
        *(s32 *)(state + 0x2C) = kind;
        *(s32 *)(state + 0x10) = ((s32)(duration) * 5 + 2) / 6;
        *(s32 *)(state + 0x14) = first;
        *(s32 *)(state + 0x18) = second;
        *(s32 *)(state + 0x1C) = third;
        *(float *)(state + 0x20) = width;
        *(float *)(state + 0x24) = height;
        *(float *)(state + 0x28) = fade;
        *(s32 *)(state + 0x30) = texture;
        *(float *)(state + 0x34) = jitter;
        qcopy(state, direction);
        qcopy((object + 0x10), position);
        for (i = 2; i >= 0; i--) D_L10_001B2DB8[i] = -1;
    }
    return object;
}
