/* func_L12_003A6F48 - 304 bytes.  Worker attempt, 28 October 2026 (draft below).
   Diff-line counts below were measured with a masking that hid offset
   differences; treat them as optimistic.

   7 differing lines (all scheduling/regs of the colour pack), size 304 ok.
   mine: sra v1,s0,16; sra v0,s0,8 first (a0=byte2,a2=byte1), pack or-order
   alpha|r.. ; retail: sra v1,s0,8 first (a0=byte1), a2=byte2, sll a0,8; sll
   v1,a2,16; or v0,v0,v1; or v0,v0,a0; or v0,v0,a3.
   Tried: all 24 or-orders, byte-var assign orders, + instead of |, alpha
   before/after bytes, u8 call params. Key finds: switch (not if/else),
   alpha=0x38 default then ==0||==0x12 -> 0x20, -G8 sibling file, constants
   0.0174532942f / 0.00029088825f.
   Update: assignment order b,g,r + expression (alpha<<24)|(g<<8)|(b<<16)|r
   fixes registers/shift order; only or-chain association differs (retail
   ((alpha|b)|g)|r). Brute-forced 144 orders x 5 parenthesizations. NOTE old
   d.sh counts were unreliable; recheck with fixed d.sh. */

/* goes in a -g8 sibling file (L12_003A6F48-g8.c), D_001A79F0 plain extern */
#include "common.h"

extern s32 D_001A79F0;
extern f32 func_00283B98(f32, f32);
extern f32 func_00283198(f32);
extern s32 func_00283D38(f32, s32, s32);
extern void func_L12_003A6EF8(void *arg0);
extern void func_002A0488(void *, s32, s32, s32);
extern f32 D_L12_001AF694 __attribute__((sda));
extern s32 D_L12_001AF68C __attribute__((sda));
extern s32 D_L12_001AF690 __attribute__((sda));

void func_L12_003A6F48(u8 *arg0) {
    f32 *state = *(f32 **)(arg0 + 0x68);
    s32 color;
    s32 alpha, r, g, b;

    switch (arg0[0x20]) {
    case 0:
        state[0] *= 0.0174532942f;
        arg0[0x20] = 1;
        break;
    case 1:
        state[0] = func_00283B98(state[0], D_L12_001AF694 * 0.00029088825f);
        color = func_00283D38(func_00283198(state[0]) * 0.5f + 0.5f, D_L12_001AF68C, D_L12_001AF690);
        b = (color >> 16) & 0xFF;
        g = (color >> 8) & 0xFF;
        r = color & 0xFF;
        alpha = 0x38;
        if (D_001A79F0 == 0 || D_001A79F0 == 0x12) {
            alpha = 0x20;
        }
        ((s32 *)state)[1] = (alpha << 24) | (g << 8) | (b << 16) | r;
        func_L12_003A6EF8(arg0);
        func_002A0488(arg0, color & 0xFF, (color >> 16) & 0xFF, (u32)color >> 24);
        break;
    }
}
