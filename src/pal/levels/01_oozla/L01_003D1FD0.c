#include "include_asm.h"

#include "common.h"
extern void func_0029F338(void *a0);
extern u32 D_L01_001BF918[];
extern u32 g_pHeroMoby[];
extern s32 func_3120A8(void *a0, u32 a1, u32 a2, u32 a3, u32 a4, u32 a5,
                      u32 a6, f32 f12, f32 f13);
extern s32 func_355780(u32 a0, u32 a1, void *a2);
extern void func_002A7750(void *a0, s32 a1, s32 a2);
extern u8 *D_L01_001B255C_sda[] __attribute__((sda));
extern u8 *D_L01_001FE180[];
extern u8 *D_L01_001B255C __attribute__((sda));
extern u32 D_L01_001FFE80[];
extern u8 D_001A7B1C __attribute__((sda));
extern u8 D_0018C958[];
extern u8 D_L01_001BF6C0[];
extern u8 *D_L01_001B264C __attribute__((sda));
extern u32 D_001A7390 __attribute__((sda));
extern void func_PAL_002A7E68(void *a0, s32 a1, s32 a2, s32 a3);
extern s32 func_L01_00337A60(void *a0, void *a1, void *a2, s32 a3);
extern s32 func_00283CF0(f32 a0);
extern s32 D_L01_001B2578[] __attribute__((sda));
extern u16 *D_L01_001FB020[];
extern u8 D_00189EA0[];
extern void *func_002A9640(void *, s32, s32);
extern f32 func_PAL_002AA108(void *, void *);
extern u8 *func_002AB1F0(u8 *);
extern void func_00282CF0(void *, void *, void *);
extern void func_00282F20(void *, void *, f32);
extern f32 func_00283CE0(s32);
extern void func_L01_002F14E8(s32, s32, f32);

/* While the owner's kind (+0x95) is 5 or 6 and its timer (+0x20) is positive, finds the entity
   func_002A9640 names (only when the state's halfword at +0x26 is below 1) and its distance
   f20 from func_PAL_002AA108; when that is positive, walks the id list of the owner's group and
   sets the effect record each entity hands out (func_002AB1F0: class-dependent 60 or 0 at +6,
   the distance taken off its float at +0), otherwise takes the distance off the timer. Then
   it runs the timer out (releasing the entity at +0xCC and switching to state 5), or, below it,
   enters state 4 for a distance of 1.0 or more and scales the vector at +0x90. At the end the
   shared update runs and the timer ratio is handed to func_L01_002F14E8. The function keeps
   the second `p != 0` guard of the walk; func_L01_003CDB40 returns a word, and the retail
   copy of the 0.2 limit holds one ulp more than 0.2f. */
void func_PAL_L01_003D1FD0(u8 *a0)
{
    u8 *state = *(u8 **)(a0 + 0x68);
    u8 *ent;
    u8 *s0;
    u8 *e;
    u8 *r;
    u16 *p;
    f32 f20;
    f32 w;
    s32 s4;
    u16 cls;

    if (a0[0x95] >= 5 && a0[0x95] <= 6 && 0.0f < *(f32 *)(state + 0x20)) {
        ent = func_002A9640(a0, 0x10000, 0);
        s0 = ent;
        if (*(short *)(state + 0x26) >= 1)
            s0 = 0;
        f20 = func_PAL_002AA108(a0, s0);
        if (s0 != 0 && 0.0f < f20) {
            if (a0[0x21] != 0xFF && *(s32 *)(state + 0xA0) != -1) {
                cls = *(u16 *)(*(u8 **)(s0 + 0x20) + 0xAA);
                s4 = (cls == 0xCE4 || cls == 0xCE5) ? 50 : 0;
                for (p = D_L01_001FB020[a0[0x21]];
                     a0[0x21] != 0xFF && a0[0x21] <= D_L01_001B2578[0] && p != 0 &&
                     ((p != 0 && (short)p[-1] >= 0) || p == D_L01_001FB020[a0[0x21]]);
                     p++) {
                    e = D_L01_001B255C_sda[0] + ((*p & 0x7FFF) << 8);
                    if (e == 0)
                        break;
                    r = func_002AB1F0(e);
                    if (r != 0) {
                        *(u16 *)(r + 6) = s4;
                        *(f32 *)r = *(f32 *)r - f20;
                        r[0x17] = state[0x37];
                        *(s32 *)(r + 0x18) = *(s32 *)(state + 0x38);
                        *(u16 *)(r + 0x1C) = *(u16 *)(state + 0x3C);
                    }
                    e[0xA8] = 0xFF;
                }
            } else {
                *(f32 *)(state + 0x20) = *(f32 *)(state + 0x20) - f20;
            }
        }
        a0[0xA8] = 0xFF;
        if (*(f32 *)(state + 0x20) < 0.0f) {
            if (*(s32 *)(state + 0xCC) != -1)
                func_0029F338(D_L01_001B255C_sda[0] + (*(s32 *)(state + 0xCC) << 8));
            *(s32 *)(state + 0xCC) = -1;
            if (a0[0x43] != 5)
                func_PAL_002A7E68(a0, 5, 0, 10);
            *(f32 *)(state + 0x20) = 0.0f;
            func_002A7750(a0, 0, 6);
            *(u16 *)(a0 + 0x34) = *(u16 *)(a0 + 0x34) & 0xEFFF;
        } else {
            if (1.0f <= f20) {
                *(s32 *)(state + 0xBC) = 0xC8;
                if (a0[0x43] != 4)
                    func_PAL_002A7E68(a0, 4, 0, 3);
                *(u16 *)(a0 + 0x34) = *(u16 *)(a0 + 0x34) & 0xEFFF;
                func_002A7750(a0, 0, 6);
            }
            if (0.1f < f20) {
                func_00282CF0(state + 0x90, a0 + 0x10, D_00189EA0);
                w = (f20 + f20 + 3.0f) * 0.020000001f;
                if (0.24000001f < w)
                    w = 0.24000001f;
                func_00282F20(state + 0x90, state + 0x90, w);
                *(s32 *)(state + 0x98) = 0;
            }
        }
    } else {
        a0[0xA8] = 0xFF;
    }
    func_L01_003CDB40(a0);
    if (a0[0x95] >= 5 && a0[0x95] <= 6)
        func_L01_002F14E8(1, 0, *(f32 *)(state + 0x20) / func_00283CE0(*(short *)(state + 0x24)));
}



INCLUDE_ASM("asm/pal/levels", func_PAL_L01_003D2900);

