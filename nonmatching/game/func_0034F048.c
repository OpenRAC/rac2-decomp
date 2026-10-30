/* func_0034F048 (880 bytes, 28 places: the boot and every level): the movie player's main
   loop, called from func_0034EF58 as func_0034F048(state + 0xD9048, state, state + 0xD9040).
   It reads the stream into the ring at ring + 0x50000 until fewer than 5 units are left or
   the decoder reports 3, feeds the decoder, starts playback once (func_0034F8C0), and polls
   pad 1 for a skip: once the pad has been released, either the 0x800 bit of the word at
   D_00138180 + 0x1A4 (unless D_001A7478 is 0 and D_001A79F0 > 0 with the high half of
   D_001A7A08 clear), or the 64-bit mask 0x8000000000F over the words at + 0x1A0/+ 0x1A4.
   Mode 3 disables skipping; mode 2 skips on any held button with nothing in + 0x1A4.
   It then drains the decoder and returns whether playback was skipped. Button names are not
   identified.

   Near miss, 30 October 2026, USA v1.01, in src/game/0034CEA0.c (-O2 -G0
   -ffunction-sections) with the declarations below in place of its INCLUDE_ASM line:
   218/220 words, 0/28 places; decomp-permuter (rac2/ntsc built natively) scores it 9
   (it started at 24). The branch layout of the skip test now matches retail, including
   the likely-branch and movn tails. Left: the %hi of D_001A7A08 is hoisted into the
   delay slot of the mode == 2 test (retail leaves a nop there), and its value, the %hi
   of D_001A7478 and the mask take other temporaries than retail's $v0/$v1.

   Measured steps, in order: the pad block as a struct global, so direct field accesses
   rematerialise the base from a shared %hi like retail (a char * local keeps it in one
   register); `skip = 0` before func_002B9000(); separate count variables with the
   subtraction before the ring call; a char * local for D_00188660; if/else skip
   assignments (retail's addiu/movn tail), not an || value. Then two reuse patterns,
   the decisive ones: a `long` copy of D_001A7478 taken before the != 3 test gives
   retail's daddu $a1,$v1 in that test's delay slot (an int copy is coalesced with the
   load, a short/char copy becomes a second load, a != 0 flag becomes sltu); and loading
   D_001A7A08 into an already-used local (w0 here; n or m do the same) keeps the two
   `skip = 1` tails apart as in retail, where a fresh local is folded away (score 17).
   The same habit, a reused scratch local, is what matched func_L00_003B69D8.

   Permuter runs (asm passes off): 9 is the best candidate that keeps the meaning; its
   score-7 candidates all move the D_001A7A08 load so the 0xFFFF0000 test reads the pad
   word instead, which changes behaviour. Earlier runs with asm passes reached lower
   scores only through inline asm barriers and register pins, which AGENTS.md forbids. */

typedef struct {
    char pad0[0x1A0];
    union {
        struct { int w0; int w1; } w;
        unsigned long long both;
    } u;
} PadState_34F048;

extern PadState_34F048 D_00138180;
extern int D_001A7478;
extern int D_001A7A08;
extern int D_001A79F0;
extern char D_00188660[];
extern char *D_001B23CC[] __attribute__((sda));
extern void func_002B9000(void);
extern int func_001261F0(int);
extern void func_003518C8(void *);
extern int func_003518D8(void *);
extern int func_00351960(void *);
extern int func_00351A38(void *);
extern int func_00351E58(void *);
extern int func_00351F28(void *);
extern s32 func_003505B0(u8 *, u8 **);
extern int func_003506B0(void *, void *, int, int);
extern void func_003505E0(char *, int);
extern s32 func_00350628(u8 *, s32 *);
extern int func_0012EB30(void *, s32, s32, void *, s32);
extern s32 func_00350670(u8 *, s32);
extern void func_0034F7A8(void);
extern void func_0034F3B8(void);
extern int func_0034F3D8(void);
extern void func_003501E0(int);
extern void func_0034F8C0(u8 *);
extern void func_0034F918(u8 *);
extern void func_00350230(void);
extern void func_00132888(int, int);
extern void func_00132028(void);

int func_0034F048(void *decoder, u8 *ring, s32 *stream)
{
    u8 *data;
    s32 count;
    int skipped;
    long notMode0;
    int released = 0;
    int started = 0;
    int left = stream[0];
    int unread;
    int skip;
    int n;
    int m;
    int k;
    int w0;

    func_0011AEA0(0);
    func_0011AEA0(2);
    skipped = 0;
    unread = left;
    func_001261F0(0);
    while (left >= 5 && func_003518D8(decoder) != 3) {
        skip = 0;
        func_002B9000();
        w0 = D_00138180.u.w.w0;
        if (w0 == 0)
            released = 1;
        if (released) {
            notMode0 = D_001A7478;
            if (D_001A7478 != 3) {
                if (D_001A7478 == 2 && w0 != 0 && D_00138180.u.w.w1 == 0)
                    skip = 1;
                else {
                    w0 = D_001A7A08;
                    if (((w0 & 0xFFFF0000) != 0 || notMode0 || D_001A79F0 <= 0)
                        && (D_00138180.u.w.w1 & 0x800))
                        skip = 1;
                    else if ((D_00138180.u.both & 0x8000000000FULL) == 0x8000000000FULL)
                        skip = 1;
                    else
                        skip = 0;
                }
            }
        }
        if (skip && !skipped) {
            skipped = 1;
            func_003518C8(D_001B23CC[0] + 0xD9048);
        }
        n = func_003505B0(ring, &data);
        if (unread > 0 && n > 0xFFFF) {
            k = func_003506B0(stream, data, 0x10000, 0);
            unread -= k;
            func_003505E0((char *)ring, k);
        }
        func_0034F7A8();
        func_0034F3B8();
        m = func_00350628(ring, &count);
        if (m > 0) {
            k = func_0012EB30(decoder, count, m, ring, *(s32 *)(ring + 0x50008));
            left -= k;
            func_00350670(ring, k);
        }
        func_0034F7A8();
        if (!started && func_00351E58(D_001B23CC[0] + 0xD9168) && func_0034F3D8()) {
            func_003501E0(1);
            started = 1;
            func_0034F8C0((u8 *)(D_001B23CC[0] + 0xD9100));
        }
    }
    func_00132888(5, 0);
    func_00132028();
    while (!func_00351960(decoder)) {
        func_0034F7A8();
        func_0034F3B8();
    }
    while (!func_00351A38(decoder) && func_003518D8(decoder) != 3
           && !func_00351F28(D_001B23CC[0] + 0xD9168)) {
        func_0034F3B8();
    }
    func_00350230();
    func_0034F918((u8 *)(D_001B23CC[0] + 0xD9100));
    {
        char *g = D_00188660;
        func_00132888(5, *(int *)(g + 0x5C));
    }
    func_00132028();
    return skipped;
}
