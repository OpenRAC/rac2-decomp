/* func_PAL_L02_003FF858, the PAL copy of func_L02_003FB120: the same C, where the timer reload is
   read as a word and scaled for 50 Hz at the store, and the callee is func_PAL_L02_00405040. */
#include "include_asm.h"

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;
typedef short s16;
typedef int s32;
typedef float f32;

extern unsigned char *D_L02_001B359C[3] __attribute__((sda));

extern u32 D_L02_001FC060[];

extern char D_00189E20[];

extern f32 D_L02_001B1218 __attribute__((sda));

extern f32 D_L02_001B121C __attribute__((sda));

extern f32 D_L02_001B1220 __attribute__((sda));

extern s32 D_L02_001B1214 __attribute__((sda));

extern void func_PAL_L02_00405040(char *, s32, f32, f32);

extern void func_L00_0035F5A0(s32, s32, s32);

extern s32 func_00282978(char *);

#define GROUP(off) (*(s32 *)(state + (off)))

/* Counts the entities of the object's group (state word 0x40) whose state byte (+0x20) is not 0xFE,
   0xFD or 1 and that are of one of six kinds, and sums a float of their private data (+0x20; for
   the first four kinds only when it is positive, and then it also counts them). The count, the sum
   and the hero's value at +0x24CC are kept at +0x60, +0x64 and +0x68; the amount each of them
   dropped by since the last call is handed to func_PAL_L02_00405040 (a drop of the hero's value also
   starts effect 0x17) and added to the int, float and float fields of the record that the index
   at +0x11C names in the four 16-byte records at the start of the state. A weighted sum over the
   four records (1 for the current one down to 1/4 for the oldest, the three fields scaled by
   D_L02_001B121C, 1218 and 1220) goes to +0x6C; when the timer at +0x11E has run out the index
   steps, the new record is cleared and the timer is reloaded from D_L02_001B1214.

   The unit is built with -g (config/cflags.txt) for the single `nop` retail has in front of the
   weight division: the assembler pads a `div.s` that follows a -g line label by two nops when
   the division is a statement of its own, and by one when the statement shares its source line
   with the two before it, as written here. */
void func_PAL_L02_003FF858(char *a0) {
    char *state = *(char **)(a0 + 0x68);
    u16 *q;

    if (GROUP(0x40) != 0xFF) {
        q = (u16 *)D_L02_001FC060[GROUP(0x40)];
        if (q != 0) {
            u16 *p = q;
            char *e;
            s32 count = 0;
            s32 kind;
            f32 sum = 0.0f;
            f32 f;

            do {
                e = (char *)D_L02_001B359C[0] + ((*p & 0x7FFF) << 8);
                if (e != 0 && *(u8 *)(e + 0x20) != 0xFE && *(u8 *)(e + 0x20) != 0xFD &&
                    *(u8 *)(e + 0x20) != 1) {
                    kind = *(s16 *)(e + 0xAA);
                    if (kind == 0x9CA || kind == 0xB22 || kind == 0xC3B || kind == 0xC3E) {
                        f = *(f32 *)(*(char **)(e + 0x68) + 0x20);
                        sum += f;
                        if (f > 0.0f)
                            count++;
                    } else if (kind == 0x9F8 || kind == 0xA44) {
                        count++;
                        sum += *(f32 *)(*(char **)(e + 0x68) + 0x20);
                    }
                }
            } while ((s16)*p++ >= 0);
            {
                char *hero = D_00189E20;
                s32 k;
                s32 r;
                s32 x;
                f32 w;
                f32 s0;
                f32 s1;
                f32 s2;

                func_PAL_L02_00405040(a0, *(s32 *)(state + 0x60) - count, *(f32 *)(state + 0x64) - sum,
                                  *(f32 *)(state + 0x68) - (f32) * (s32 *)(hero + 0x24CC));
                if (*(f32 *)(state + 0x68) - (f32) * (s32 *)(hero + 0x24CC) > 0.0f)
                    func_L00_0035F5A0(0x17, 0, 0);
                if (count < *(s32 *)(state + 0x60))
                    *(s32 *)(state + ((s16) * (s16 *)(state + 0x11C) << 4)) +=
                        *(s32 *)(state + 0x60) - count;
                if (sum < *(f32 *)(state + 0x64)) {
                    char *b4 = state + 4;
                    f32 *at = (f32 *)(b4 + ((s16) * (s16 *)(state + 0x11C) << 4));

                    *at += *(f32 *)(state + 0x64) - sum;
                }
                if ((f32) * (s32 *)(hero + 0x24CC) < *(f32 *)(state + 0x68)) {
                    char *b8 = state + 8;
                    f32 *at = (f32 *)(b8 + ((s16) * (s16 *)(state + 0x11C) << 4));

                    *at += *(f32 *)(state + 0x68) - (f32) * (s32 *)(hero + 0x24CC);
                }
                *(f32 *)(state + 0x64) = sum;
                *(s32 *)(state + 0x60) = count;
                *(f32 *)(state + 0x68) = (f32) * (s32 *)(hero + 0x24CC);
                s0 = 0.0f;
                s1 = 0.0f;
                s2 = 0.0f;
                for (k = 4; k > 0; k--) {
                    char *b4;
                    char *b8;

                    x = *(s16 *)(state + 0x11C) + k; r = x - x / 4 * 4; w = 1.0f / (5.0f - (f32)k);
                    b4 = state + 4;
                    b8 = state + 8;
                    s1 += w * *(f32 *)(b4 + (r << 4));
                    s0 += w * (f32) * (s32 *)(state + (r << 4));
                    s2 += w * *(f32 *)(b8 + (r << 4));
                }
                *(f32 *)(state + 0x6C) =
                    D_L02_001B1218 * s1 + D_L02_001B121C * s0 + D_L02_001B1220 * s2;
                {
                    char *timer = state + 0x11E;

                    if (func_00282978(timer)) {
                        char *b4 = state + 4;
                        char *b8 = state + 8;
                        s32 reload = D_L02_001B1214;
                        s32 t;
                        s32 idx;

                        t = (s16)(*(u16 *)(state + 0x11C) + 1);
                        idx = t - t / 4 * 4;
                        *(s16 *)(state + 0x11C) = idx;
                        *(s32 *)(state + ((s16)idx << 4)) = 0;
                        *(s32 *)(b4 + ((s16) * (s16 *)(state + 0x11C) << 4)) = 0;
                        *(s32 *)(b8 + ((s16) * (s16 *)(state + 0x11C) << 4)) = 0;
                        *(u16 *)(state + 0x11E) = ((s32)reload * 5 + 2) / 6;
                    }
                }
            }
        }
    }
}
