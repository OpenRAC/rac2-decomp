#include "common.h"

typedef struct { u8 pad[0x80]; u8 data[0x270]; u8 more[0xC]; f32 value; } HeroBDA8;
extern HeroBDA8 D_00189E20;
extern u8 *D_L13_001B2A0C __attribute__((sda));
extern s32 func_002ACBC8(u8 *, s32);
extern void func_00282F20(u8 *, u8 *, f32);

void func_L13_0041BDA8(u8 *a0) {
    s32 *ids = *(s32 **)(a0 + 0x68);
    s32 i;

    if (a0[0x20] == 0) {
        a0[0x30] = 0xFF;
        a0[0x20] = 1;
    }
    for (i = 0; i < 8; i++) {
        if (ids[i] != -1 && IsPointInCuboid(D_00189E20.data, ids[i]) != 0) {
            vec_scale_to_length(D_00189E20.data + 0x270, D_L13_001B2A0C + (ids[i] << 7), -1.0f);
            D_00189E20.value = 10.0f;
        }
    }
}
