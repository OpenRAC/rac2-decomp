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
   218/220 words, 0/28 places. Everything outside the skip test aligns with retail (189 of
   220 instructions identical by difflib, the rest relocation fields and the shift).
   Left: retail loads D_001A7478 into $v1 for the == 3 and == 2 tests and keeps a plain copy
   in $a1 for the later != 0 test, leaving the delay slots of the mode/held tests as nops.
   This C computes the != 0 flag with sltu instead; a plain `int mode = D_001A7478` copy is
   coalesced into one register (then the two `skip = 1` tails cross-jump), and a short/char
   copy becomes a second, narrower load.

   What it took to get here (each measured): the pad block as a struct global, so direct
   field accesses rematerialise the base from a shared %hi like retail (a char * local keeps
   it in one register); `skip = 0` before func_002B9000(); separate count variables with the
   subtraction before the ring call (it fills the call's delay slot); a char * local for
   D_00188660 (retail materialises its base for the single + 0x5C load); and if/else skip
   assignments (the final one becomes retail's addiu/movn), not an || value.

   Two decomp-permuter runs (OpenRAC tools/permuter, profile rac2/ntsc built natively;
   170,818 + 174,244 candidates) went from 24 to 13 differing instructions, the notMode0
   flag being their main find. Lower scores (9-11) all used inline asm barriers or register
   pins, which AGENTS.md does not allow; the best clean candidates scored 12 with no
   source-level meaning (e.g. comparing D_001A7478 against a variable holding 3). */

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
    int notMode0;
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
            if (D_001A7478 != 3) {
                notMode0 = D_001A7478 != 0;
                if (D_001A7478 == 2 && w0 != 0 && D_00138180.u.w.w1 == 0)
                    skip = 1;
                else if (((D_001A7A08 & 0xFFFF0000) != 0 || notMode0 || D_001A79F0 <= 0)
                         && (D_00138180.u.w.w1 & 0x800))
                    skip = 1;
                else if ((D_00138180.u.both & 0x8000000000FULL) == 0x8000000000FULL)
                    skip = 1;
                else
                    skip = 0;
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
