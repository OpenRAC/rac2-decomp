#include "common.h"
typedef struct { s32 field00; u8 remainder[12]; } JobaPolygonHeaderView;
extern JobaPolygonHeaderView *D_L11_001FF580[];
extern u8 *func_L11_004417E8(u8 *);
extern s32 func_002A8AF0(float *, float *, s32);
extern s32 func_L00_003206B8(void *, s32);
extern u8 *D_0018C0B0;

/* Rejects a target using the state polygons and class-dependent height limits. */
s32 func_L11_00441FB8(u8 *a, u8 *b, s32 c) {
    float pos[4] __attribute__((aligned(16)));
    u8 *state = *(u8 **)(a + 0x68);
    s16 result = !func_L00_003206B8(b + 0x10, *(s32 *)(state + 0x1E4));
    if (*(s16 *)(b + 0xAA) != 0 && (*(u16 *)(b + 0x34) & 2)) return 0;
    if (result) return result;
    if (!c) {
        if (*(s16 *)(b + 0xAA) == 0xD4B) {
            qcopy(pos, b + 0x10);
            pos[2] -= 0.8f;
            result = (s16)func_L00_003206B8(pos, *(s32 *)(state + 0x160));
        } else result = (s16)func_L00_003206B8(b + 0x10, *(s32 *)(state + 0x160));
    }
    if (result) return result;
    if (*(s16 *)(state + 0x1FA) == 3) {
        float *height = (float *)func_L11_004417E8(a);
        result = (s16)(*(float *)(b + 0x18) < height[2] + (b == D_0018C0B0 ? 0.5f : 3.0f));
    }
    if (result) return result;
    if (*(s16 *)(state + 0x1FA) == 2 || *(s16 *)(state + 0x1FA) == 4) {
        u8 *poly = (u8 *)D_L11_001FF580[*(s32 *)(state + 0x1C8)];
        if (*(float *)(b + 0x18) < ((float *)func_L11_004417E8(a))[2] + 0.5f)
            result = !point_in_path_xy((float *)(b + 0x10), (float *)(poly + 0x10), *(s32 *)poly);
    }
    return result;
}

