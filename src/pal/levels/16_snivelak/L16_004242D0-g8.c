#include "include_asm.h"

#include "common.h"
typedef int quad __attribute__((mode(TI)));
extern char D_L16_001BFF60[];
extern f32 D_L16_001B1FF0 __attribute__((sda));
extern f32 D_L16_001B1FF4 __attribute__((sda));
extern void FastVecAdd(char *, char *, char *);
extern void func_PAL_L16_00424590(char *);
extern s32 CollLine(char *, char *, s32, s32, s32);
extern void moby_set_state(char *, s32, s32);
extern void func_PAL_L00_003FB330(char *, f32, f32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32);
extern void coll_sweep_from_object(char *, char *, f32, f32, u32, s32, s32, s32, f32);
extern s32 flag_set_first_pending(char *);
extern f32 ApproachValue(f32 *, f32, f32);
extern void moby_mark_spawned(char *);
extern void SweepAndDrawRibbonRing(char *);
extern void gfx_add_draw_callback_first(void (*)(char *), char *);

/* Moves a fragment until impact and runs its fading shock-wave effect. */
void func_PAL_L16_004242D0(char *self) {
    quad previous;
    char *st = *(char **)(self + 0x68);

    switch (*(u8 *)(self + 0x20)) {
    case 0: {
        char *old = (char *)&previous;
        char *position = self + 16;
        qcopy(old,position);
        FastVecAdd(position, position, st);
        *(f32 *)(st + 8) -= *(f32 *)(st + 0x24);
        func_PAL_L16_00424590(self);
        if (CollLine(old, position, 0, *(s32 *)(self + 0xB8), 0)) {
            qcopy(position ,D_L16_001BFF60);
            if (*(s32 *)(st + 0x20)) moby_set_state(self, 2, -1);
            else moby_set_state(self, 1, -1);
        }
        break;
    }
    case 1: {
        char *position = self + 16;
        func_PAL_L00_003FB330(position, 1.0f, 20.0f, 0, 25, 20, 20, 20, 45, 1, 1, 0, 0, 0);
        coll_sweep_from_object(self, position, 2.0f, 6.0f, 0x10001, 0, 1, 0, 1.0f);
        moby_mark_spawned(self);
        break;
    }
    case 2:
        if (flag_set_first_pending(self)) {
            func_PAL_L00_003FB330(self + 16, 0.6660000085830688f, 20.0f, 0, 20, 15, 15, 15, 35, 1, 1, 0, 0, 0);
            *(s32 *)(self + 0x98) = 0;
            *(u16 *)(self + 0x34) = (*(u16 *)(self + 0x34) | 0x41) & 0xEFFF;
            *(f32 *)(self + 0x18) += 0.5f;
            *(f32 *)(st + 0x30) = 1.0f;
        }
        *(f32 *)(st + 0x34) += 0.080000006f;
        if (*(f32 *)(st + 0x34) > 1.0f) *(f32 *)(st + 0x34) -= 1.0f;
        { f32 radius = *(f32 *)(st + 0x2C);
          f32 growth = D_L16_001B1FF0 * 0.020000001f;
          f32 limit = D_L16_001B1FF4;
          radius += growth;
          *(f32 *)(st + 0x2C) = radius;
        if (radius >= limit) ApproachValue((f32 *)(st + 0x30), 0.0f, 0.080000006f);
        }
        if (*(f32 *)(st + 0x30) <= 0.0f) moby_mark_spawned(self);
        else gfx_add_draw_callback_first(SweepAndDrawRibbonRing, self);
        break;
    }
}
