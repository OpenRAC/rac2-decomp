#include "names.h"
/* func_PAL_L11_0045EBA0, the PAL copy of func_L11_00458F90: the same C, where scale func_00283CF0(D_L11_001B1FDC / t). */


typedef unsigned char u8;
typedef int TI128 __attribute__((mode(TI)));
extern void *CreateMoby(int);
extern void vec_scale_to_length(void *, void *, float);
extern void FastVecCross(void *, void *, void *);
extern int FloatToInt(float);
extern float IntToFloat(int);
extern void moby_rebuild_frame_from_transform(u8 *);
extern char D_0018A0E0[];
extern float D_L11_001B1FD0 __attribute__((sda));
extern float D_L11_001B1FD8 __attribute__((sda));
extern float D_L11_001B1FDC __attribute__((sda));

/* Same body as func_L02_004216F0, minus the final call; this level's own data. */
u8 *func_PAL_L11_0045EBA0(u8 *a0, int a1, u8 *a2, float a3) {
    u8 *obj = CreateMoby(0xE2D);
    u8 *v;
    int n;
    float t;

    if (obj != 0) {
        *(u8 *)(obj + 0x20) = 0;
        *(u8 *)(obj + 0x30) = 0xFF;
        t = D_L11_001B1FD8 * 0.020000001f;
        v = *(u8 **)(obj + 0x68);
        *(float *)(v + 0x64) = a3;
        vec_scale_to_length(v + 0x40, a2, t);
        *(TI128 *)(obj + 0x10) = *(TI128 *)a0;
        *(TI128 *)(obj + 0xC0) = *(TI128 *)(v + 0x40);
        FastVecCross(obj + 0xD0, obj + 0xC0, D_0018A0E0);
        vec_scale_to_length(obj + 0xD0, obj + 0xD0, -1.0f);
        FastVecCross(obj + 0xE0, obj + 0xD0, obj + 0xC0);
        t = D_L11_001B1FD8 * 0.020000001f;
        n = (((int)(FloatToInt(D_L11_001B1FDC / t)) * 5 + 2) / 6);
        *(int *)(v + 0x58) = n;
        *(float *)(v + 0x5C) = 1.0f / IntToFloat(n);
        *(int *)(v + 0x50) = a1;
        *(u8 *)(obj + 0x20) = 0;
        *(float *)(v + 0x60) = D_L11_001B1FD0;
        moby_rebuild_frame_from_transform(obj);
    }
    return obj;
}
