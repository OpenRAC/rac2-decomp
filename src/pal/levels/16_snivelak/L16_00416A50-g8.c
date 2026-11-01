#include "include_asm.h"

#include "common.h"
typedef float V4_F411d00[4] __attribute__((aligned(16)));
extern float D_L16_001B17A0 __attribute__((sda));
extern float D_L16_001B17B0 __attribute__((sda));
extern float D_L16_001B17B8 __attribute__((sda));
extern float D_L16_001B17BC[];
extern void func_002A7A00(void *, float, float);
extern void func_00283098(void *, void *, char *);
extern void func_00282CC0(void *, void *, void *);
extern void func_00282D30(void *, void *, float);
extern void func_00282CF0(void *, void *, void *);
extern void func_00282F20(void *, void *, float);
extern float func_002A7878(float, float);
extern float func_L00_0031CDD0(void *, void *, s32, float, float);
extern s32 func_PAL_L00_003FB330(void *, s32, s32, s32, float, float, s32, s32, s32, s32, s32, s32, s32, s32);
extern void func_L16_0041F1F0(s32, void *, void *, s32, float, float);

/* Fires the object's spark: builds a short ray from its frame, tilts it by the resident angle and hands it to the effect spawner. */
void func_PAL_L16_00416E50(char *obj)
{
    V4_F411d00 a, b, c, d;
    char *rec = *(char **)(obj + 0x68);
    float rate, angle;

    func_002A7A00(a, 0.0f, 1.0f);
    func_00283098(b, &D_L16_001B17A0, obj + 0xC0);
    func_00282CC0(b, b, obj + 0x10);
    func_00282CC0(b, b, a);
    func_00282D30(c, a, 3.0f);
    c[2] = 0.0f;
    func_00282CC0(c, c, *(char **)(rec + 0x24C) + 0x10);
    rate = D_L16_001B17B0 * 0.020000001f;
    angle = func_002A7878(D_L16_001B17B8, D_L16_001B17BC[0]) * 0.00040000002f;
    func_00282CF0(d, c, b);
    d[2] = 0.0f;
    func_00282F20(d, d, rate);
    d[2] = func_L00_0031CDD0(b, c, 0, D_L16_001B17B0 * 0.020000001f, -angle);
    func_PAL_L00_003FB330(b, 0, 0x19, 0x14, 1.0f, 20.0f, 0x14, 0x14, 0x2D, 1, 1, 0, 0, 0);
    func_L16_0041F1F0(*(s32 *)(rec + 0x1F0), b, d, 0, angle, (float)*(u8 *)(rec + 0x36));
}
