#include "include_asm.h"

#include "common.h"
extern int D_001A79F0 __attribute__((sda));
extern char D_0019B4A8[];
extern char D_00189EA0[];
extern void func_00282CF0(f32 *, const f32 *, const f32 *);
extern void func_002AFEB8(char *, char *, char *, char *, f32);
extern void func_00282F20(f32 *, f32 *, f32);
extern void func_PAL_002B15D8(void *, s32, void *, f32, f32, f32, f32, s32);
extern s32 *D_L12_001FEAC0[];
extern s32 *D_L12_001FEAC0[];
extern s32 func_002761F8(void *from, void *to, s32 mode, void *self, s32 flags);
extern s32 *D_L12_001FEAC0[];
extern char D_00189EA0[];
extern f32 func_00282C48(f32);
extern f32 func_00282E80(void *, void *);
extern s32 func_002A7820(s32, s32);
extern s32 func_002E5CF8(s32, s32, void *);
extern s32 D_L12_001B20C0 __attribute__((sda));
extern u8 D_001395DB;
extern s32 func_002A77E0(s32);
extern s32 func_00283CF0(f32);
extern u8 *func_002BDCE8(void *, f32, f32, f32, s32, void *, f32, u32, s32);

void func_PAL_L12_00423C50(u8 *a0) {
    u8 *self = a0;
    f32 buf[4];
    u16 f;

    func_00282CF0(buf, (f32 *)(self + 0x10), (f32 *)D_00189EA0);
    func_002AFEB8((char *)self, (char *)buf, (char *)buf, 0, 0.0f);
    func_00282F20(buf, buf, 0.120000005f);
    func_PAL_002B15D8(self, 31, buf, 6.0f, 12.0f, 6.0f, 12.0f, 255);

    f = *(u16 *)(self + 0xB2);
    if (f & 1) {
        u8 *p = (u8 *)(((s16)f >> 1) + (D_001A79F0 << 10)) + (int)D_0019B4A8;
        u8 c = *p;

        if (((c >> 4) & 7) != 7)
            *p = c + 0x10;
    } else {
        u8 *p = (u8 *)(((s16)f >> 1) + (D_001A79F0 << 10)) + (int)D_0019B4A8;
        u8 c = *p;

        if ((c & 7) != 7)
            *p = c + 1;
    }
    func_002E5CF8(1, 0, self);
}





