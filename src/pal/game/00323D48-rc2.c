#include "include_asm.h"

#include "common.h"
struct Vec3 { f32 x; f32 y; f32 z; };
struct Vec4 { f32 x; f32 y; f32 z; f32 w; };
extern void *func_PAL_002735D0(void *, s32, s16, s32, void *, void *, void *, s32, f32, f32);
extern void func_00282CC0(struct Vec3 *, struct Vec3 *, struct Vec4 *);
extern void func_00282F20(struct Vec4 *, void *, f32);
extern void func_00283098(struct Vec3 *, struct Vec3 *, void *);
extern f32 func_00283180(f32);
extern f32 func_00283198(f32);
extern f32 func_002A7878(f32, f32);
extern f32 func_002A7940(void);
extern void func_PAL_003242C8(void);
extern s32 D_001A8CA0;

void func_PAL_003240E8(void *arg0) {
    struct Vec4 loc0;
    struct Vec3 sp10;
    void *obj;
    void *v1;
    f32 t20;
    f32 t21;
    f32 t;
    f32 t22;
    s32 i;

    obj = (*(void **)((s8 *)(arg0) + (0x68)));
    func_00282F20(&loc0, (s8 *)obj + 0xE0, 0.060000002f);
    for (i = 0; i < 0xF; i++) {
        if (!(((0x7F8 >> i) ^ 1) & 1)) {
            t20 = func_002A7940();
            t21 = func_002A7878(3.0f, 5.0f) * 0.020000001f;
            sp10.x = func_00283180(t20) * t21;
            t = func_00283198(t20) * t21;
            sp10.z = 0.0f;
            sp10.y = t;
            sp10.z = func_002A7878(3.0f, 5.0f) * 0.020000001f;
            if (D_001A8CA0 != 0) {
                func_00283098(&sp10, &sp10, (s8 *)arg0 + 0xC0);
            }
            func_00282CC0(&sp10, &sp10, &loc0);
            t22 = func_002A7878(90.0f, 270.0f);
            t = func_002A7878(10.0f, 20.0f);
            v1 = func_PAL_002735D0(arg0, 2, (*(s16 *)((s8 *)(arg0) + (0xAA))), i, (s8 *)arg0 + 0x10, (s8 *)arg0 + 0xF0, &sp10, 0xFF, t22, t);
            if ((*(s32 *)((s8 *)(obj) + (0x2B4))) != 0 && v1 != 0) {
                (*(s32 *)((s8 *)(v1) + (0x64))) = (s32)func_PAL_003242C8;
            }
        }
    }
}
