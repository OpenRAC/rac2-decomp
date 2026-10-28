/* func_0027A9F0 - 332 bytes, 28 places (src/game/00274128.c): sets up the
   screen size (D_001A7340..D_001A735C: w, h, w/2, h/2 and the four bounds
   around 0x800 in 12.4 fixed point) and the projection floats in D_001B9040.

   Near miss: 328 of 332 bytes.  Retail stores each word with its own
   `lui $at` (separate symbols, not a struct: a struct gives 308 bytes and
   base-relative stores) and puts the 0x800 constant in $a2, computing
   0x800-h/2, w/2+0x800, h/2+0x800, 0x800-w/2 in that order.  The store of w
   lands in the call's delay slot as a $gp store here; retail stores it
   before the call with `daddu a0,v0` in the slot.

   Tried: the four bound stores in three orders, w and h stored together,
   the halves stored early, D_001A7340 without sda (worse, 79 lines). */

extern short D_001A6480[];
extern int D_001A7340[] __attribute__((sda));
extern int D_001A7344[] __attribute__((sda));
extern int D_001A7348[] __attribute__((sda));
extern int D_001A734C[] __attribute__((sda));
extern int D_001A7350[] __attribute__((sda));
extern int D_001A7354[] __attribute__((sda));
extern int D_001A7358[] __attribute__((sda));
extern int D_001A735C[] __attribute__((sda));
extern float D_001B9040[];
extern float func_00283CE0(int);

void func_0027A9F0(void)
{
    int h = D_001A6480[0xA9];
    int w = D_001A6480[0xA8];
    int hh = h >> 1;
    int hw = w >> 1;

    D_001A7344[0] = h;
    D_001A7354[0] = (0x800 - hh) << 4;
    D_001A735C[0] = (hh + 0x800) << 4;
    D_001A7350[0] = (0x800 - hw) << 4;
    D_001A7358[0] = (hw + 0x800) << 4;
    D_001B9040[0x28] = 32.0f;
    D_001B9040[0x29] = 1048576.0f;
    D_001B9040[0x2C] = 0.62f;
    D_001A7340[0] = w;
    D_001A7348[0] = hw;
    D_001A734C[0] = hh;
    D_001B9040[0x80] = func_00283CE0(w) * 0.5f;
    D_001B9040[0x81] = func_00283CE0(D_001A6480[0xA9]) * 0.5f;
    D_001B9040[0x82] = D_001B9040[0x80] * 4.0f;
    D_001B9040[0x87] = 524288.0f;
    D_001B9040[0x8A] = 255.0f;
    D_001B9040[0x83] = D_001B9040[0x81] * 4.0f;
    D_001B9040[0x8B] = 0.0f;
    D_001B9040[0x86] = 0.0f;
}
