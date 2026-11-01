#include "include_asm.h"

#include "common.h"
typedef struct { f32 x, y, z; } V3;
typedef struct { f32 x, y, z, w; } V4;
typedef struct { s8 b00[0x10]; V3 v10; s32 p1c; V4 v20; V4 v30; } Fr;
extern f32 ref_L11_0043A810_00 __attribute__((sda));
extern f32 ref_L11_0043A810_01 __attribute__((sda));
extern f32 ref_L11_0043A810_02 __attribute__((sda));
extern f32 ref_L11_0043A810_03 __attribute__((sda));
extern f32 ref_L11_0043A810_04 __attribute__((sda));
extern void ref_L11_0043A810_05(void *);
extern void ref_L11_0043A810_06(f32 *, s32, void *);
extern f32 ref_L11_0043A810_07(s32, void *);
extern f32 ref_L11_0043A810_08(f32, f32);
extern void ref_L11_0043A810_09(void *, void *, void *, f32);
extern f32 ref_L11_0043A810_10(f32, f32);
extern f32 ref_L11_0043A810_11(f32);
extern void ref_L11_0043A810_12(void *, s32, void *);
extern void ref_L11_0043A810_13(void *, void *);
extern void ref_L11_0043A810_14(s32, void *, f32);

void func_PAL_L11_0043FDB8(void *arg0) {
    Fr fr;
    s8 *s1;
    s8 *s0;
    f32 temp_f20;
    f32 t, t1, t2, t3, t5, var_f0, var_f1, vdc;
    s16 h;

    s1 = *(s8 **)((s8 *)arg0 + 0x68);
    ref_L11_0043A810_12(arg0, 3, fr.b00);
    s0 = s1 + 0x50;
    ref_L11_0043A810_06(&fr.v10.x, (s32)s0, fr.b00);
    temp_f20 = ref_L11_0043A810_07((s32)s0, fr.b00);
    ref_L11_0043A810_05(&fr.v20);
    t = ref_L11_0043A810_08(fr.v10.z, temp_f20) + -1.5707964f + ref_L11_0043A810_04;
    fr.v20.y = t;
    if (ref_L11_0043A810_01 < t) {
        fr.v20.y = ref_L11_0043A810_01;
    } else if (t < ref_L11_0043A810_02) {
        fr.v20.y = ref_L11_0043A810_02;
    }
    ref_L11_0043A810_13(&fr.v30, &fr.v20);
    ref_L11_0043A810_14((s32)(s1 + 0x270), &fr.v30, ref_L11_0043A810_03);
    ref_L11_0043A810_05(&fr.v20);
    t1 = ref_L11_0043A810_08(fr.v10.x, fr.v10.y);
    fr.v20.z = t1;
    t2 = ref_L11_0043A810_10(t1, *(f32 *)(arg0 + 0xF8));
    fr.v20.z = t2;
    t3 = ref_L11_0043A810_11(t2);
    fr.v20.z = t3;
    fr.v20.z = t3 + *(f32 *)(s1 + 0x2DC);
    t5 = *(f32 *)(s1 + 0x2E0) * 0.0003490659f;
    h = *(s16 *)(s1 + 0x2EE);
    vdc = *(f32 *)(s1 + 0x2DC);
    if (h == 0) {
        var_f0 = vdc - t5;
    } else {
        var_f0 = vdc + t5;
    }
    var_f1 = ref_L11_0043A810_00;
    *(f32 *)(s1 + 0x2DC) = var_f0;
    if ((var_f1 < var_f0) || (var_f1 = -var_f1, (var_f0 < var_f1))) {
        *(f32 *)(s1 + 0x2DC) = var_f1;
        *(s16 *)(s1 + 0x2EE) = (s16)((u16)*(s16 *)(s1 + 0x2EE) ^ 1);
    }
    ref_L11_0043A810_13(&fr.v30, &fr.v20);
    ref_L11_0043A810_09(s1 + 0x230, s1 + 0x230, &fr.v30, 0.0625f);
}
