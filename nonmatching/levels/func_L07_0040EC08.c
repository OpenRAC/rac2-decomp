/* func_L07_0040EC08: retained near miss, 30 October 2026.
   Profile: -O2 -G8 -ffunction-sections.
   Local checks: 940/952 bytes, 0/1 in each of USA v1.01 and v2.00.
   No strict linked match is claimed.

   Typed five-member chain fields, following matched func_L07_0040E980,
   improved the first 912-byte draft to 940 bytes. Spilled pointer slots,
   scheduling and global address formation still differ. The retail stale
   a2 load near the func_L07_0040F0D0 call is not manufactured with a false
   extra argument.
*/

#include "common.h"

typedef struct { u8 prefix[0xE0]; f32 times[5]; u8 *members[5]; } ChainState;
typedef union { s32 q __attribute__((mode(TI))); f32 f[4]; } Vector;
extern u8 *D_L07_001FDEC0[];
extern u8 D_00188660[];
extern u8 D_00189E20[];
extern u8 D_L07_001B9200[];
extern u8 *D_L07_001ADAAC MACRO_ADDR;
extern f32 D_L07_001B1784 __attribute__((sda));
extern f32 D_L07_001B1788 __attribute__((sda));
extern f32 D_L07_001B1708 __attribute__((sda));
extern f32 func_002AA2E8(f32 *, f32, f32);
extern s32 func_002E5CF8(s32, s32, void *);
extern void func_002C9828(void *, s32, void *, void *, s32, f32);
extern void func_L07_0040EFC8(void *, void *, f32, f32);
extern void func_002A0F48(void *);
extern f32 func_00283B98(f32, f32);
extern void func_00282CF0(void *, void *, void *);
extern void func_002AD6F0(void *, void *, void *, void *);
extern void func_L07_00379180(f32);
extern void func_L00_00426478(void *);
extern void func_L07_0040F760(void *);
extern void func_L07_0040FA90(void *, s32);
extern void func_L07_004106B8(void *);
extern void func_L07_0040F0D0(void *);
extern void func_002AFDD8(void *, void *, void *, s32);
extern void func_L00_002B30E8(void);

/* Advance every member of the five-object chain and its rider attachments. */
void func_L07_0040EC08(u8 *object)
{
    Vector oldPosition, oldRotation, delta, relative;
    u8 *state = *(u8 **)(object + 0x68);
    u8 *path = D_L07_001FDEC0[*(s32 *)(state + 0x90)];
    ChainState *chain = (ChainState *)state;
    u8 *sound, *member, *memberState;
    s32 i, j, kind;
    f32 rate;

    D_L07_001ADAAC = 0;
    func_002AA2E8((f32 *)(state + 0x11C), *(f32 *)(state + 0x1A0), *(f32 *)(state + 0x1A4));
    sound = D_00188660 + *(s32 *)(state + 0x1AC) * 0x70;
    if (*(u8 **)(sound + 0x88) != object || sound[0x74] == 0)
        *(s32 *)(state + 0x1AC) = func_002E5CF8(2, 12, object);
    if (*(s32 *)(state + 0x1AC) != -1)
        qcopy(D_00188660 + *(s32 *)(state + 0x1AC) * 0x70 + 0x90, D_L07_001B9200);

    for (i = 0; i < 5; i++) {
        member = chain->members[i];
        memberState = *(u8 **)(member + 0x68);
        qcopy(&oldPosition, member + 0x10);
        qcopy(&oldRotation, member + 0xF0);
        func_002C9828(path, 1, member + 0x10, member + 0xF0, 0, chain->times[i]);
        *(f32 *)(member + 0x18) += D_L07_001B1784;
        func_L07_0040EFC8(path, member + 0xF0, chain->times[i], D_L07_001B1708);
        func_002A0F48(member);
        chain->times[i] += *(f32 *)(state + 0x11C);
        if (chain->times[i] >= (f32)*(s32 *)path)
            chain->times[i] -= (f32)*(s32 *)path;
        rate = D_L07_001B1788 * 0.00029088825f;
        for (j = 7; j >= 0; j--)
            *(f32 *)(memberState + 0x15B4 + (7 - j) * 0x20) =
                func_00283B98(*(f32 *)(memberState + 0x15B4 + (7 - j) * 0x20), rate);
        func_00282CF0(&delta, member + 0x10, &oldPosition);
        func_002AD6F0(memberState + 0x20, &delta, &oldRotation, member + 0xF0);
        if (*(u8 **)(D_00189E20 + 0x3A0) == member ||
            (*(u8 **)(memberState + 0x108) != 0 &&
             *(u8 **)(D_00189E20 + 0x3A0) == *(u8 **)(memberState + 0x108)) ||
            (*(u8 **)(memberState + 0x10C) != 0 &&
             *(u8 **)(D_00189E20 + 0x3A0) == *(u8 **)(memberState + 0x10C))) {
            D_L07_001ADAAC = member;
            func_L07_00379180(chain->times[i]);
        }
        func_L00_00426478(member);
        func_L07_0040F760(member);
        func_L07_0040FA90(member, i);
        func_L07_004106B8(member);
        kind = *(s16 *)(member + 0xAA);
        if (kind == 0x11D9 || kind == 0x11DB)
            func_L07_0040F0D0(member);
        if (D_L07_001ADAAC != 0) {
            func_00282CF0(&relative, D_00189E20 + 0x80, D_L07_001ADAAC + 0x10);
            func_002AFDD8(D_L07_001ADAAC, &relative, &relative, 0);
            if (relative.f[2] < -3.0f) {
                if (*(s32 *)(D_00189E20 + 0x33C) == 0)
                    func_L00_002B30E8();
                if (*(s32 *)(D_00189E20 + 0x33C) == 0 && *(f32 *)(D_00189E20 + 0x31C) < 1.0f)
                    func_L00_002B30E8();
            }
        }
    }
}
