/* 9 November 2026, lead round 2 (3 compiles): 652/652, 0/2, 29 real rows. With x, then the first
   label coordinate, then y, the coordinate's mul.s now interleaves with the width max and box
   arithmetic as in retail (its dead test ends the block after x). Left: y's (d >> 1) and (h >> 1)
   are recomputed after that boundary, where retail forms (d >> 1) - (h >> 1) before it and only
   subtracts off after; and so the coordinate stays in $a0/$a3, not retail's $v1 copy. Named
   left/right edges before x give 644 bytes (copy lost). Entry load pair and closing x1/y1
   registers unchanged. Next: a form that keeps the y difference in the first block without a
   dead or artificial use. */
/* 9 November 2026, lead (Opus) follow-up: now 652/652 bytes, 0 of 2 places, 30 real rows (from 648).
   Two source-order facts from the retail bytes: 263.0f (kx) is set after the first three corner
   coordinates, just before func_002802E0 (retail loads it in that call's setup); and the first
   label coordinate is a local read in $v1 and copied to $a0 for func_0027EB88. Left: the entry's
   scale/222.0f load pair is swapped; retail interleaves that coordinate's mul.s with the width
   max and box arithmetic, which needs it in the same block as them and ending before the 371.0f
   coordinate (menu_coord after y keeps the block but gives $a0 directly and 648 bytes; a plain
   rounding without the dead test gets the $v1 copy but pulls the 371.0f coordinate into the
   block, 54 rows); the closing x1/y1 take $s1/$s0 against retail's $s0/$s1. 7 compiles. */
/* 9 November 2026: func_PAL_L04_0041B5C0 (levels 04, 11), PAL. 648 bytes vs retail 652, 0 of 2 places.
   The menu box with its two labels, same shape as USA func_L04_00416E38 (menu_coord idiom, constants
   in 222/479/299 then 263/371/349). Differs: retail loads the 371.0f constant after the width call
   and interleaves the 263 conversion with the lui/lw of D_001A73C0 and the gp offset before the slt;
   mine hoists lwc1/constants differently (4 bytes, scheduling only). Tried: kx/ky as locals in
   several orders, ky via comma expression, max as if/ternary, preloading d/off locals. Needs -G8
   (lw 0x1AE4($gp)): lives in L04_0041A660-g8.c. */
typedef unsigned short u16;

extern float D_L04_001B2DE4;
extern int D_L04_001B2DE0;
extern int D_001A73C0;
extern int D_L04_001B1AE4 __attribute__((sda));
extern void func_002802E0(void *, int, int, int, int, int, int, int, int);
extern char *func_00288FB8(int);
extern void func_00280200(void *, unsigned long long, char *, int);
extern int func_L00_002E9120(char *, int);
extern void func_0027EB88(int, int, int, int, int, int);
extern void func_PAL_0029BFF0(float, float, float, float, int, int);
extern int func_0027FB40(int, int, unsigned long long, char *, int);

static __inline__ int menu_coord(float value, float scale, float half, int active)
{
    int mode = D_L04_001B2DE0;
    float scaled = scale * value + half;
    int result = (int)scaled;

    if (result != 0 && mode == active)
        scaled = 1.0f;
    return result;
}

void func_PAL_L04_0041B5C0(void) {
    char box[0x20] __attribute__((aligned(16)));
    float s, half, kx, ky;
    int d, off, x, y, w, h, x0, y0, z0, cx, x1, y1, on;

    half = 0.5f;
    on = 1;
    s = D_L04_001B2DE4;
    x0 = menu_coord(222.0f, s, half, on);
    y0 = menu_coord(479.0f, s, half, on);
    z0 = menu_coord(299.0f, s, half, on);
    kx = 263.0f;
    func_002802E0(box, x0, y0, 44, 468, 256, z0, 16, 3);
    *(unsigned short *)(box + 0x12) |= 4;
    func_00280200(box, (int)0x80F0F0F0, func_00288FB8(0xA41), -1);
    w = func_L00_002E9120(func_00288FB8(0xE51), -1);
    s = D_L04_001B2DE4;
    h = *(short *)(box + 0xC);
    d = D_001A73C0;
    off = D_L04_001B1AE4;
    h = (w < h) ? h : w;
    x = (d >> 1) + (h >> 1) + off;
    cx = menu_coord(kx, s, half, on);
    y = (d >> 1) - (h >> 1) - off;
    ky = 371.0f;
    func_0027EB88(cx, menu_coord(ky, s, half, on), y, x, 96, 0x60442D00);
    s = D_L04_001B2DE4;
    func_PAL_0029BFF0((float)menu_coord(kx, s, half, on), (float)menu_coord(ky, s, half, on), (float)y,
                      (float)x, 96, 0x55F0C070);
    *(unsigned short *)(box + 0x12) &= ~4;
    func_00280200(box, (int)0x80F0F0F0, func_00288FB8(0xA41), -1);
    x1 = D_001A73C0 / 2;
    y1 = menu_coord(349.0f, D_L04_001B2DE4, half, on);
    func_0027FB40(x1, y1, (int)0x80F0F0F0, func_00288FB8(0xE51), -1);
}
