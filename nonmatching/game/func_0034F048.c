/* func_0034F048 - 880 bytes. The movie playback loop (called from func_0034EF58 with
   decoder = state + 0xD9048, ring = state, stream = state + 0xD9040); returns whether
   the player skipped the movie.

   Attempt, 30 October 2026: 876/880 bytes, 0/28 USA places (tools/check.py).
   Everything outside the skip test matches. In the skip test retail loads
   D_001A7478 once into v1 and copies it to a1 (`beq v1,s1` / `daddu a1,v1`),
   leaves the `bne v1,2` and `beqz held` delay slots empty, and reaches
   `skip = 1` through a `beql pressed,zero` and a `bnez 0x800` delay slot that
   fall through to the 64-bit combo test. cc1 here keeps the address of
   D_001A7478 instead (reloads it for the `!= 0` test) and shares one
   `skip = 1` block, one instruction shorter.
   Tried: a block-local `mode` copy (868), `mode` assigned in the condition (868),
   the three cases as one `||` expression (876, saved registers shift), the
   combo as a plain assignment (sltiu instead of movn). */

#include "include_asm.h"

typedef int s32;
typedef unsigned int u32;
typedef unsigned char u8;

extern s32 func_0011AEA0(s32);
extern int func_001261F0(int);

typedef struct { char pad000[0x1A0]; u32 held; u32 pressed; } MoviePad;
extern MoviePad D_00138180;
extern int D_001A7478;
extern int D_001A7A08;
extern int D_001A79F0;
extern char D_00188660[];
extern char *D_001B23CC[] __attribute__((sda));
extern void func_002B9000(void);
extern void func_003518C8(u8 *);
extern s32 func_003505B0(u8 *, u8 **);
extern s32 func_003506B0(u8 *, u8 *, s32, s32);
extern void func_003505E0(char *, int);
extern s32 func_00350628(u8 *, s32 *);
extern s32 func_0012EB30(u8 *, s32, s32, u8 *, s32);
extern s32 func_00350670(u8 *, s32);
extern int func_00351E58(unsigned char *);
extern s32 func_003518D8(u8 *);
extern void func_00132888(s32, s32);
extern void func_00132028(void);
extern s32 func_00351960(u8 *);
extern int func_00351A38(void *);
extern int func_00351F28(void *);
extern void func_003501E0(int);
extern void func_00350230(void);
void func_0034F3B8(void);
int func_0034F3D8(void);
void func_0034F7A8(void);
void func_0034F8C0(u8 *);
void func_0034F918(u8 *);

int func_0034F048(u8 *decoder, u8 *ring, u8 *stream)
{
    u8 *data;
    s32 src;
    int stopped;
    int left = *(s32 *)stream;
    int pending;
    int armed = 0;
    int started = 0;
    int skip;

    func_0011AEA0(0);
    stopped = 0;
    func_0011AEA0(2);
    pending = left;
    func_001261F0(0);
    while (left >= 5 && func_003518D8(decoder) != 3) {
        skip = 0;
        func_002B9000();
        if (D_00138180.held == 0)
            armed = 1;
        if (armed && D_001A7478 != 3) {
            if (D_001A7478 == 2 && D_00138180.held != 0 && D_00138180.pressed == 0)
                skip = 1;
            else if (((D_001A7A08 & 0xFFFF0000) || D_001A7478 != 0 || D_001A79F0 <= 0)
                     && (D_00138180.pressed & 0x800))
                skip = 1;
            else if ((*(unsigned long long *)&D_00138180.held & 0x8000000000FULL)
                     == 0x8000000000FULL)
                skip = 1;
        }
        if (skip && !stopped) {
            stopped = 1;
            func_003518C8((u8 *)D_001B23CC[0] + 0xD9048);
        }
        {
            s32 free = func_003505B0(ring, &data);
            if (pending > 0 && free >= 0x10000) {
                s32 sent = func_003506B0(stream, data, 0x10000, 0);
                func_003505E0((char *)ring, sent);
                pending -= sent;
            }
        }
        func_0034F7A8();
        func_0034F3B8();
        {
            s32 count = func_00350628(ring, &src);
            if (count > 0) {
                s32 used = func_0012EB30(decoder, src, count, ring, *(s32 *)(ring + 0x50008));
                func_00350670(ring, used);
                left -= used;
            }
        }
        func_0034F7A8();
        if (!started && func_00351E58((u8 *)D_001B23CC[0] + 0xD9168) && func_0034F3D8()) {
            func_003501E0(1);
            started = 1;
            func_0034F8C0((u8 *)D_001B23CC[0] + 0xD9100);
        }
    }
    func_00132888(5, 0);
    func_00132028();
    while (!func_00351960(decoder)) {
        func_0034F7A8();
        func_0034F3B8();
    }
    while (!func_00351A38(decoder) && func_003518D8(decoder) != 3
           && !func_00351F28(D_001B23CC[0] + 0xD9168))
        func_0034F3B8();
    func_00350230();
    func_0034F918((u8 *)D_001B23CC[0] + 0xD9100);
    func_00132888(5, *(s32 *)(D_00188660 + 0x5C));
    func_00132028();
    return stopped;
}
