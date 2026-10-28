/* func_L11_003F2A30 - 504 bytes.  Worker attempt, 28 October 2026 (draft below).
   Diff-line counts below were measured with a masking that hid offset
   differences; treat them as optimistic.

   func_L11_003F2A30 (504 B), goes in L11_003D6270-g8.c ($gp floats
   D_L11_001B0540/0544/0550/0554/0558). Jump table: retail `sltiu 0xB` + table
   at 0x2BAA10, 11 entries, three targets (A: subtract, B: add, default). I do
   not know the case->label mapping (draft guesses even/odd), so the table
   will not match until it is read from the retail data.
   Draft is 500 B vs 504. Diffs: retail loads D_..0554 ($gp+0x1564) and the
   0.00029088825 constant inside each arm before the join (mine hoists
   differently), and the clamp: retail stores v first in the bc1t delay slot,
   `c.lt lim,v ; bc1t S ; swc1 v ; neg.s lim ; c.lt v,lim ; bc1fl ; ... S:
   swc1 lim` (one shared store of lim / -lim). Constants: 4.8481374e-06f
   (0x36A2AD2F), 0.00029088825f (0x3998825C). */

extern f32 D_L11_001B0540 __attribute__((sda));
extern f32 D_L11_001B0544 __attribute__((sda));
extern f32 D_L11_001B0550 __attribute__((sda));
extern f32 D_L11_001B0554 __attribute__((sda));
extern f32 D_L11_001B0558 __attribute__((sda));
extern f32 func_00283B98(f32, f32);
extern f32 func_00283180(f32);
extern f32 func_00283198(f32);
extern f32 *func_L11_004417E8(void *);
extern void func_002833F0(void *, void *);

void func_L11_003F2A30(u8 *a0) {
    u8 *s1 = *(u8 **)(a0 + 0x68);
    f32 v, lim, f20, t;
    f32 *p;

    switch (a0[0x42]) {
    case 0: case 2: case 4: case 6: case 8: case 10:
        t = D_L11_001B0550 * 4.8481374e-06f;
        v = *(f32 *)(s1 + 0x254);
        lim = D_L11_001B0554;
        v = v - t;
        goto limit;
    case 1: case 3: case 5: case 7: case 9:
        t = D_L11_001B0550 * 4.8481374e-06f;
        v = *(f32 *)(s1 + 0x254);
        lim = D_L11_001B0554;
        v = v + t;
    limit:
        lim = lim * 0.00029088825f;
        *(f32 *)(s1 + 0x254) = v;
        if (lim < *(f32 *)(s1 + 0x254)) {
            *(f32 *)(s1 + 0x254) = lim;
        } else if (*(f32 *)(s1 + 0x254) < -lim) {
            *(f32 *)(s1 + 0x254) = -lim;
        }
        break;
    default:
        break;
    }
    *(f32 *)(s1 + 0x250) = func_00283B98(*(f32 *)(s1 + 0x250), *(f32 *)(s1 + 0x254));
    if (a0[0x20] == 5 || a0[0x20] == 9) {
        return;
    }
    if (*(u8 **)(a0 + 0xB8) != 0) {
        f20 = func_00283180(*(f32 *)(s1 + 0x250));
        p = func_L11_004417E8(*(u8 **)(a0 + 0xB8));
        *(f32 *)(a0 + 0x10) = D_L11_001B0558 * f20 + p[0];
        f20 = func_00283198(*(f32 *)(s1 + 0x250));
        p = func_L11_004417E8(*(u8 **)(a0 + 0xB8));
        *(f32 *)(a0 + 0x14) = D_L11_001B0558 * f20 + p[1];
    }
    if (a0[0x95] == 2) {
        *(f32 *)(a0 + 0x18) = D_L11_001B0540;
        *(f32 *)(a0 + 0xF4) = -1.5707964f;
        *(int *)(a0 + 0xF0) = 0;
        *(f32 *)(a0 + 0xF8) = *(f32 *)(s1 + 0x250);
        func_002833F0(a0 + 0xC0, a0 + 0xF0);
    } else if (a0[0x95] == 1) {
        *(f32 *)(a0 + 0x18) = D_L11_001B0544;
        *(f32 *)(a0 + 0xF4) = 1.5707964f;
        *(int *)(a0 + 0xF0) = 0;
        *(f32 *)(a0 + 0xF8) = func_00283B98(3.1415927f, *(f32 *)(s1 + 0x250));
        func_002833F0(a0 + 0xC0, a0 + 0xF0);
    }
}
