/*
 * Retained manual C reconstruction; not linked or counted.
 * Profile: -O2 -G0 -ffunction-sections (src/levels/18_damosel/L18_003F80A0.c).
 * Retail: 364 bytes; compiled: 364 bytes.
 * Coverage: us: 0/1 (tools/check.py, 2026-10-28, master 1243c8ea).
 * Residual: 4 words at +0x34..+0x40, the case-range test before the mode 6-7 body. Retail
 * tests `mode < 8` with `beqz` to the return and an unconditional `b` to the body; this C
 * emits `bnel` to the body with the 0x71C load in its slot, then `b` to the return. Every
 * other word, including the 0-5 range test and both bodies, is identical.
 * Tried without change (all 4 words): the 6-7 body after the switch with `break`; switching
 * on an s32 variable (declared before or after the state pointer) or an (s32) cast; `case
 * 7: case 6:`; `default: break`. Any order other than `default` first gives 356 bytes;
 * if/else chains on an s32 mode give 352.
 * Reopen: a case layout or compiler profile that emits the inverted range branch.
 */
typedef unsigned char u8;
typedef short s16;
typedef int s32;

extern void func_002B5278(void *, float);
extern void func_002B5258(void *);
extern void func_L02_0032E998(void *, void *, void *, void *, int, void *, void *, float, float);
extern int func_002B50E0(void *, void *, float);
extern int func_002B4FF0(void *, void *, float);
extern void func_002A7750(u8 *arg0, s32 arg1, s32 arg2);
extern void func_002ACB48(void *, float);

/* Moves the object by its mode byte at +0x42. Modes 0 to 5 use one of two simple movers
   (with the state's +0x724 rate when its +0x766 flag is set). Modes 6 and 7 steer along
   the state's path at +0x700, through the full steering call when the target at +0x71C
   is set and the +0x76A flag is on; then, unless the object's state byte is 9, 4 or 3,
   they trigger effect 3 when the state's +0x190 count is at least 6 and, whenever bits
   0-1 of +0x1A4 are set, jitter the position by 0.01 and trigger it again. */
void func_L18_003F8A98(u8 *object)
{
    u8 *vars = *(u8 **)(object + 0x68);

    switch (object[0x42]) {
    default:
        return;
    case 0: case 1: case 2: case 3: case 4: case 5:
        if (*(s16 *)(vars + 0x766) != 0)
            func_002B5278(object, *(float *)(vars + 0x724));
        else
            func_002B5258(object);
        return;
    case 6: case 7:
        if (*(s32 *)(vars + 0x71C) != -1 && *(s16 *)(vars + 0x76A) != 0) {
            func_L02_0032E998(object + 0x10, vars + 0x700, vars + 0x748, vars + 0x200,
                              *(s32 *)(vars + 0x730), vars + 0x73C, vars + 0x740, 0.0f, 0.4f);
            func_002B50E0(object, vars + 0x700, *(float *)(vars + 0x748));
        } else {
            func_002B4FF0(object, vars + 0x700, *(float *)(vars + 0x720));
        }
        if (object[0x20] == 9 || object[0x20] == 4 || object[0x20] == 3)
            return;
        if (*(s32 *)(vars + 0x190) >= 6)
            func_002A7750(object, 3, -1);
        if (*(s32 *)(vars + 0x1A4) & 3) {
            func_002ACB48(object + 0x10, 0.01f);
            func_002A7750(object, 3, -1);
        }
        return;
    }
}
