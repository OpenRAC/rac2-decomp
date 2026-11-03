/* Second-pass complete-object review, 2026-11-03; retained, not linked.
 * Profile: -O2 -G8 -ffunction-sections -g -ffast-math -frac2-qcopy -frac2-qcopy-barrier.
 * Current US check.py: 5292/5300 bytes,0/3 places. Frame0x180 and entry
 * owner/saved-register roles agree; copy/input/FP scheduling still differs.
 * 002AB6D8 reads all64 bytes of basis[4][4], including the cleared final row.
 * 00283698 writes64 bytes at the old A0 address: the C0/D0 span has a real
 * writer. The older no-writer/unused-local note below is superseded. No dummy
 * C0/D0 vectors are restored: a full inverse shares later A0/B0 vector views.
 * The query at the old v50 address requires40 bytes: 002A8C00 writes through
 * +0x20, and 00277F48 explicitly reads lq+0,lq+0x10,ld+0x20 from that request.
 * It shares the basis allocation with a later real position at+0x30. Target
 * compiler debug types verify query size48, position offset48 and both phase
 * unions size64. Its opaque+0x24 word is not artificially initialized.
 * Three final clear/query/position variants produce identical checker output;
 * stop this hypothesis. Reopen on independent input/copy/FP lifetime evidence,
 * not an unreferenced local, padding array or repeated register wording.
 * No native-port semantic gate or linked matching credit is claimed.
 * Earlier measurements follow as historical evidence.
 */
/* Current retained result, 1 November 2026: 5284/5300 bytes. Remove the two unreferenced vector
 * declarations previously used to shape the stack. The 32-byte gap has no evidenced C object; do not
 * restore dummy storage. The current compiler removes the old block-move loop padding, but allocation and
 * store order still differ.
 * Not a functional-port qualification or a complete matching-build result.
 * Profile: -O2 -G8 -ffunction-sections -g -ffast-math -frac2-qcopy -frac2-qcopy-barrier.
 * Earlier measurements below remain historical where superseded by this note.
 */
/* Opus handoff (big8, 2026-10-26): func_L08_003C6AB0, 5300 bytes, 3 places
 * (L08 0x003C6AB0, L19 0x003B63E0, L30 0x003B5B48). A rideable moby's update: a pvars
 * block at moby+0x68, a seven-entry state jump table jtbl_L08_002B5220 on moby+0x20
 * (case 6 present, empty), then a byte switch on pvars+0x8A when the level flag is 8.
 * Step 0: one function (one prologue addiu $sp,-0x180, one jr $ra). No matched twin
 * (best opcode ratio 0.64 to the open func_L08_0041EBF8).
 * Profile: -O2 -G8 -ffunction-sections -g -ffast-math -frac2-qcopy -frac2-qcopy-barrier
 * (-g: the nop pair before the first div.s; -ffast-math: the min.s; the barrier +7 aligned).
 * Measured in its own unit src/levels/shared/L08_003C6AB0.c: 5300 bytes (size only) with the
 * current compiler, 1237/1325 opcodes aligned, 843 with registers. With the block-move
 * padding fix (branch compiler/blkmove-loop-length) the four loop NOPs go (16 bytes).
 * What the retail shows and this draft reproduces:
 *  - the 0x400-byte table copy is a plain structure assignment (byte-aligned struct):
 *    the ldl/ldr loop plus the aligned ld/sd loop come from GCC's block move;
 *  - a frame of 0x180 needs two more unused-looking 16-byte locals (vC0, vD0) before the
 *    six input floats at sp+0xE0..0xF4; the fire flag at sp+0xF8 must live in memory
 *    (if-conversion turns `if (bit) fire = t;` into movz otherwise), hence the struct;
 *  - hero addresses: the union view for fields, but `D_00189E20 + 0x90/0x80` as plain
 *    char arithmetic for the quadword copies (retail forms D+0x90 and derives the rest);
 *  - D_L08_001B031C is the one mixed symbol (absolute lui $at/lwc1 in flow, $gp in a delay
 *    slot): MACRO_ADDR gives that form (+5 aligned).
 * Still off: the moby/pvars pointers sit one callee-saved register up (s5/s4 against
 * retail s4/s3) because the &v80 pseudo outranks them; the float block after the input
 * clamp (scheduling of the AFA04/AF9C8/AFAC0 loads), the 0xD2 byte stores (retail
 * 0x99, 0x97, 0x98) and the hero 0x183C/0x1840 store order; retail does not CSE the 1.0f
 * between func_00282F20's argument and `v78 + 1.0f`.
 * closer4 (2026-10-26): the 0xD2 byte stores in source order 0x97, 0x98, 0x99 give retail's
 * 0x99, 0x97, 0x98.  Measured in scratch only (the helper is pending): the v80 clear as
 * big16's qzero_nc (bare volatile asm, cse flushes its table) instead of the TI zero store
 * puts moby/pvars in retail's s4/s3 and moby+0xC0 is rebuilt after it as in retail:
 * 1262/1325 opcodes and 1109 with registers (from 1248 and 845), 5304 bytes (+4).  What is
 * left then is mostly float scheduling in the input/physics block (0x3C7000-0x3C7200).
 * F3 (2026-10-26, on 795143e6 with the block-move padding default): this draft with
 * qzero_nc(v80) at the v80 clear in its own unit (flags above) is 5288 bytes (1322/1325
 * instructions, 3 short) and 1073/1325 aligned counting registers. The differences start at
 * the head: the 0x400-byte table copy's registers (a1/a2 swapped), pvars still in $s4 for
 * the input block (retail $s3), the float block at 0x3C7000. Not a few-instruction miss.
 */
#include "common.h"

typedef int TI128 __attribute__((mode(TI)));
typedef union { TI128 q; f32 f[4]; } RideVector __attribute__((aligned(16)));
/* The initializer writes through +0x20; consumers also transport +0x24.
 * Its unknown final word remains opaque, with no invented initialization. */
typedef struct {
    RideVector direction;
    s32 owner, flags;
    u8 first, second;
    u16 objectId;
    f32 distance;
    s32 enabled;
    f32 opaque;
} RideQuery;
typedef struct { u8 b[0x400]; } Block400;
typedef union { u8 b[0x400]; u32 w[0x100]; } Pad;
typedef union { u8 b[0x2600]; s16 h[0x1300]; s32 i[0x980]; f32 f[0x980]; u8 *ptr[0x980]; TI128 q[0x260]; } Hero;

extern s32 func_002829A8(void *);
extern void *func_002A9640(void *, u32, s32);
extern void func_002AB800(void *, void *);
extern void func_002AB8C0(void *, void *);
extern f32 func_002A0558(void *, void *);
extern s32 func_002B0C28(s32, s32, s32);
extern s32 func_L08_002D2ED8(s32, s32);
extern void func_L00_002D2168(int, int, f32);
extern int func_00282978(void *);
extern int func_00282948(void *);
extern int func_002A77E0(int);
extern void func_L08_003C63F0(char *);
extern void func_L08_003C6528(f32 *, f32 *, f32 *, f32 *, f32 *, f32 *);
extern f32 func_00282DF0(void *);
extern f32 func_00283B98(f32, f32);
extern f32 func_00283180(f32);
extern f32 func_00283198(f32);
extern f32 func_00282C48(f32);
extern f32 func_L08_003277C0(s32, f32);
extern void func_00282CC0(void *, void *, void *);
extern f32 func_002A89A8(void *, int, f32);
extern int func_00278E78(void);
extern f32 func_00283BE0(f32, f32);
extern void func_00282D30(void *, void *, f32);
extern void func_00282F20(void *, void *, f32);
extern void func_00282DD8(void *, void *, void *);
extern void func_002AB6D8(void *, void *);
extern void func_00283698(void *, void *);
extern void func_002830C0(void *, void *, void *);
extern void func_00283098(void *, void *, void *);
extern void func_002A8C00(void *, void *, s32, void *, f32);
extern void func_0029FCC0(void *, int, void *);
extern void func_00282CF0(void *, void *, void *);
extern s32 func_00278870(void *, f32);
extern s32 func_00277258(void *, s32, void *, f32);
extern f32 func_00282DB0(void *, void *);
extern void func_L08_003C67B8(void *, void *, s32, f32, f32, f32, f32, f32, f32);
extern s32 func_00277F48(f32, void *, s32, void *, void *);
extern void func_0029F338(void *);
extern void func_002ABBB8(void *, void *, void *, float, float, int, int, int, float, float, float, float, int, float, int, int, int, int, int);
extern f32 func_00283CE0(s32);
extern s32 func_00283CF0(f32);
extern void *func_L08_00435600(void *, void *);
extern void func_L08_004356A0(void *, void *);
extern void func_L00_002E6EF8(void *, void *);
extern f32 func_00282E48(void *, void *);
extern void func_002A93B0(void *);
extern void func_L08_003C66F0(void *);
extern void func_002AEF28(void *, void *, void *, f32, f32, f32);

extern u8 D_00138180[];
extern u8 D_00189E20[];
extern s32 D_001A79F0 __attribute__((nosda));
extern s32 D_L08_001A8F00 __attribute__((sda));
extern f32 D_L08_001AF990 __attribute__((sda));
extern s32 D_L08_001AF994 __attribute__((sda));
extern s32 D_L08_001AF998 __attribute__((sda));
extern f32 D_L08_001AF99C __attribute__((sda));
extern f32 D_L08_001AF9A0 __attribute__((sda));
extern f32 D_L08_001AF9A4 __attribute__((sda));
extern f32 D_L08_001AF9A8 __attribute__((sda));
extern f32 D_L08_001AF9AC __attribute__((sda));
extern f32 D_L08_001AF9B0 __attribute__((sda));
extern f32 D_L08_001AF9B4 __attribute__((sda));
extern f32 D_L08_001AF9B8 __attribute__((sda));
extern f32 D_L08_001AF9BC __attribute__((sda));
extern f32 D_L08_001AF9C0 __attribute__((sda));
extern f32 D_L08_001AF9C4 __attribute__((sda));
extern f32 D_L08_001AF9C8 __attribute__((sda));
extern f32 D_L08_001AF9CC __attribute__((sda));
extern f32 D_L08_001AF9D0 __attribute__((sda));
extern s32 D_L08_001AF9D4 __attribute__((sda));
extern s32 D_L08_001AF9D8 __attribute__((sda));
extern f32 D_L08_001AF9DC __attribute__((sda));
extern f32 D_L08_001AF9E0 __attribute__((sda));
extern f32 D_L08_001AF9E4 __attribute__((sda));
extern f32 D_L08_001AF9E8 __attribute__((sda));
extern f32 D_L08_001AF9EC __attribute__((sda));
extern f32 D_L08_001AF9F0 __attribute__((sda));
extern f32 D_L08_001AF9F4 __attribute__((sda));
extern f32 D_L08_001AF9F8 __attribute__((sda));
extern f32 D_L08_001AF9FC __attribute__((sda));
extern f32 D_L08_001AFA00 __attribute__((sda));
extern f32 D_L08_001AFA04 __attribute__((sda));
extern f32 D_L08_001AFA08 __attribute__((sda));
extern f32 D_L08_001AFA0C __attribute__((sda));
extern f32 D_L08_001AFA10 __attribute__((sda));
extern f32 D_L08_001AFA14 __attribute__((sda));
extern s32 D_L08_001AFA50 __attribute__((sda));
extern f32 D_L08_001AFA6C __attribute__((sda));
extern f32 D_L08_001AFA70 __attribute__((sda));
extern f32 D_L08_001AFA74 __attribute__((sda));
extern f32 D_L08_001AFA78 __attribute__((sda));
extern f32 D_L08_001AFA7C __attribute__((sda));
extern f32 D_L08_001AFA80 __attribute__((sda));
extern s32 D_L08_001AFA84 __attribute__((sda));
extern f32 D_L08_001AFA88 __attribute__((sda));
extern f32 D_L08_001AFAB4 __attribute__((sda));
extern f32 D_L08_001AFAB8 __attribute__((sda));
extern f32 D_L08_001AFABC __attribute__((sda));
extern f32 D_L08_001AFAC0 __attribute__((sda));
extern f32 D_L08_001AFAC4 __attribute__((sda));
extern f32 D_L08_001AFAC8 __attribute__((sda));
extern s16 D_L08_001AFACC __attribute__((sda));
extern f32 D_L08_001AFAD4 __attribute__((sda));
extern u8 *D_L08_001AFAD8 __attribute__((sda));
extern s32 D_L08_001AFADC __attribute__((sda));
extern s32 D_L08_001AFB14 __attribute__((sda));
extern s32 D_L08_001AFB18 __attribute__((sda));
extern f32 D_L08_001AFB70 __attribute__((sda));
extern f32 D_L08_001AFB74 __attribute__((sda));
extern f32 D_L08_001AFB78 __attribute__((sda));
extern s32 D_L08_001AFB7C __attribute__((sda));
extern f32 D_L08_001AFB80 __attribute__((sda));
extern f32 D_L08_001AFB84 __attribute__((sda));
extern f32 D_L08_001AFB88 __attribute__((sda));
extern f32 D_L08_001AFB8C __attribute__((sda));
extern f32 D_L08_001AFB90 __attribute__((sda));
extern s32 D_L08_001AFB94 __attribute__((sda));
extern f32 D_L08_001AFB98 __attribute__((sda));
extern f32 D_L08_001AFB9C __attribute__((sda));
extern f32 D_L08_001AFBA0 __attribute__((sda));
extern f32 D_L08_001AFBA4 __attribute__((sda));
extern f32 D_L08_001AFBA8 __attribute__((sda));
extern s32 D_L08_001AFBAC __attribute__((sda));
extern f32 D_L08_001AFBB0 __attribute__((sda));
extern f32 D_L08_001AFBB4 __attribute__((sda));
extern u8 D_L08_001AFBB8 __attribute__((sda));
extern f32 D_L08_001B031C MACRO_ADDR;
extern u8 *D_L08_001B2484 __attribute__((nosda));
extern u8 D_L08_001B99C0[];
extern u8 D_L08_001B9B00[];
extern u8 D_L08_001BE700[];
extern u8 D_L08_001BFF40[];
extern u8 D_L08_001BFF60[];
extern u8 D_L08_001BFF80[];
extern Block400 D_L08_0023E6A0;
extern u8 D_L08_003C5940[];

void func_L08_003C6AB0(u8 *moby)
{
    f32 dir[4] __attribute__((aligned(16)));
    f32 v30[4] __attribute__((aligned(16)));
    f32 v40[4] __attribute__((aligned(16)));
    union {
        f32 basis[4][4];
        struct { RideQuery request; RideVector position; } query_view;
    } basis_work;
#define basis basis_work.basis
#define request basis_work.query_view.request
#define v50 basis[0]
#define v60 basis[1]
#define v70 basis[2]
#define v80 basis_work.query_view.position.f
    f32 v90[4] __attribute__((aligned(16)));
    union {
        f32 inverse[4][4];
        struct { f32 first[4], second[4]; } vectors;
    } inverse_work __attribute__((aligned(16)));
#define vA0 inverse_work.vectors.first
#define vB0 inverse_work.vectors.second
    struct { f32 turn, speed, pitch, bank, lift, thrust; s32 fire; } in;
    u8 *vars;
    u8 *hit;
    u8 *other;

    vars = *(u8 **)(moby + 0x68);
    if (func_002829A8(vars + 0x8B) != 0) {
        *(u8 **)(vars + 0xA0) = 0;
    }
    if (*(u8 *)(moby + 0x20) != 0) {
        *(f32 *)(moby + 0x18) = *(f32 *)(vars + 0x58);
        hit = func_002A9640(moby, 1, 0);
        if (hit != 0 && (other = *(u8 **)(hit + 0x20)) != 0) {
            s16 kind = *(s16 *)(other + 0xAA);
            if (kind != 0x85C && kind != 0x942 && kind != 0xFFF) {
                if (other != *(u8 **)(vars + 0xA0) || *(u8 *)(vars + 0x8B) == 0) {
                    *(u8 *)(vars + 0x97) = 0xD2;
                    *(u8 *)(vars + 0x98) = 0xD2;
                    *(u8 *)(vars + 0x99) = 0xD2;
                    func_002AB800(moby, vars + 0x90);
                    *(f32 *)(vars + 0x60) -= *(f32 *)(hit + 0x2C);
                    ((Hero *)D_00189E20)->f[0x183C / 4] = *(f32 *)(vars + 0x60);
                    if (*(f32 *)(vars + 0x60) <= 0.0f) {
                        *(u8 *)(moby + 0x20) = 5;
                    }
                    *(u8 **)(vars + 0xA0) = *(u8 **)(hit + 0x20);
                    *(u8 *)(vars + 0x8B) = D_L08_001AFBB8;
                }
            }
        }
        *(u8 *)(moby + 0xA8) = 0xFF;
    } else {
        *(f32 *)(vars + 0x58) = *(f32 *)(moby + 0x18);
    }
    func_002AB8C0(moby, vars + 0x90);
    *(f32 *)(moby + 0x2C) = *(f32 *)(*(u8 **)(moby + 0x24) + 0x24) * D_L08_001AFA6C;
    if (((Hero *)D_00189E20)->ptr[0x1830 / 4] == moby) {
        ((Hero *)D_00189E20)->i[0x1848 / 4] = ((Hero *)D_00189E20)->f[0x183C / 4] / D_L08_001AFA80 * 200.0f;
    }
    in.fire = 0;
    switch (*(u8 *)(moby + 0x20)) {
    case 0: {
        u8 *src = D_L08_001B2484 + *(u16 *)(D_L08_001BE700 + (*(s32 *)(vars + 0x64) + D_L08_001AFA50) * 16 + 0xA) * 16;
        s32 done = D_L08_001AFADC;
        D_L08_001AFAD8 = src;
        *(s32 *)(vars + 0xA8) = 0xFF;
        *(s32 *)(vars + 0xA4) = 0;
        if (done == 0) {
            D_L08_0023E6A0 = *(Block400 *)src;
        }
        D_L08_001AFADC = 1;
        *(TI128 *)(vars + 0x30) = *(TI128 *)(moby + 0x10);
        *(TI128 *)(vars + 0x0) = 0;
        {
            f32 health = D_L08_001AFA80;
            *(f32 *)(vars + 0x60) = health;
            ((Hero *)D_00189E20)->f[0x183C / 4] = health;
            ((Hero *)D_00189E20)->f[0x1840 / 4] = health;
        }
        *(u8 **)(vars + 0x74) = 0;
        *(u8 *)(moby + 0x20) = 1;
        *(f32 *)(vars + 0x78) = 0.0f;
        *(s32 *)(vars + 0xAC) = 0;
        break;
    }
    case 1:
        if (((Hero *)D_00189E20)->i[0x2294 / 4] == 0x1C || ((Hero *)D_00189E20)->i[0x2294 / 4] == 0x16
            || ((Hero *)D_00189E20)->i[0x2294 / 4] == 0x39 || ((Hero *)D_00189E20)->i[0x2294 / 4] == 0x6F) {
            break;
        }
        if (((Hero *)D_00189E20)->i[0x229C / 4] == 2 || ((Hero *)D_00189E20)->i[0x229C / 4] == 4
            || ((Hero *)D_00189E20)->i[0x229C / 4] == 3 || ((Hero *)D_00189E20)->i[0x229C / 4] >= 0xD
            || ((Hero *)D_00189E20)->i[0x229C / 4] == 7 || ((Hero *)D_00189E20)->i[0x229C / 4] == 0xA
            || ((Hero *)D_00189E20)->i[0x229C / 4] == 0x10 || ((Hero *)D_00189E20)->i[0x229C / 4] == 5) {
            break;
        }
        if (((Hero *)D_00189E20)->i[0x2294 / 4] == 0x62) {
            break;
        }
        if (((Hero *)D_00189E20)->i[0x24CC / 4] <= 0) {
            break;
        }
        if (D_L08_001A8F00 != 0) {
            break;
        }
        if (((Hero *)D_00189E20)->i[0x340 / 4] == 0) {
            break;
        }
        if (((Hero *)D_00189E20)->ptr[0x33C / 4] != 0) {
            s16 kind = *(s16 *)(((Hero *)D_00189E20)->ptr[0x33C / 4] + 0xAA);
            if (kind == 0x13E || kind == 0x46F) {
                break;
            }
        }
        if (func_002A0558(moby, ((Hero *)D_00189E20)->ptr[0x2290 / 4]) < D_L08_001AF99C
            && ((Hero *)D_00189E20)->i[0x2294 / 4] != 0x31) {
            s32 t = func_002B0C28(7, 0x2798, 1) != 0;
            if (((Pad *)D_00138180)->w[0x1A4 / 4] & 0x10) {
                in.fire = t;
            }
        }
        if (in.fire != 0) {
            func_L08_002D2ED8(0x31, 0);
            func_L00_002D2168(D_L08_001AF9D4, 0, 15.0f);
            *(TI128 *)(D_00189E20 + 0x90) = *(TI128 *)(moby + 0xF0);
            *(TI128 *)(D_00189E20 + 0x80) = *(TI128 *)(moby + 0x10);
            ((Hero *)D_00189E20)->ptr[0x1830 / 4] = moby;
            *(u8 *)(moby + 0x20) = 3;
            *(s32 *)(((Hero *)D_00189E20)->ptr[0x2290 / 4] + 0x9C) = -1;
        }
        /* fallthrough */
    case 3: {
        f32 sign;
        f32 blend;
        f32 cruise;
        f32 ground;
        f32 floor;
        s32 landed;
        s32 steer;
        f32 roll;

        *(s32 *)(moby + 0x98) = 0;
        func_00282978(vars + 0x7C);
        func_00282948(vars + 0xAC);
        {
            f32 zero = 0.0f;
            in.thrust = zero;
            in.speed = zero;
            in.pitch = zero;
            in.bank = zero;
            in.lift = zero;
            in.turn = zero;
        }
        if (*(u8 *)(moby + 0x20) == 3) {
            if ((((Pad *)D_00138180)->w[0x1A0 / 4] & 8) && *(s16 *)(vars + 0x7C) == 0) {
                u8 **list = (u8 **)(vars + 0x80);
                *(list[*(u16 *)(vars + 0x7E) & 1] + 0xBC) = 1;
                *(u16 *)(vars + 0x7E) ^= 1;
                *(s16 *)(vars + 0x7C) = D_L08_001AFACC;
            }
            if (((Pad *)D_00138180)->w[0x1A0 / 4] & 4) {
                *(f32 *)(vars + 0x78) -= D_L08_001AFAB8;
                if (func_002A77E0(9) == 0 || (((Pad *)D_00138180)->w[0x1A4 / 4] & 4)) {
                    func_L08_003C63F0(moby);
                }
            } else {
                *(f32 *)(vars + 0x78) += D_L08_001AFABC;
            }
            if (D_L08_001AF9D8 != D_L08_001AF9D4 && D_L08_001AF9D4 != -1) {
                func_L00_002D2168(D_L08_001AF9D4, 0, 15.0f);
            }
            func_L08_003C6528(&in.turn, &in.speed, &in.pitch, &in.bank, &in.lift, &in.thrust);
        } else {
            *(f32 *)(vars + 0x78) -= D_L08_001AFAB8;
        }
        if (*(f32 *)(vars + 0x78) > 1.0f) {
            *(f32 *)(vars + 0x78) = 1.0f;
        } else if (*(f32 *)(vars + 0x78) < 0.0f) {
            *(f32 *)(vars + 0x78) = 0.0f;
        }
        sign = 1.0f;
        in.speed *= *(f32 *)(vars + 0x78);
        in.bank += 1.0f - *(f32 *)(vars + 0x78);
        in.lift *= *(f32 *)(vars + 0x78);
        in.thrust *= *(f32 *)(vars + 0x78);
        blend = D_L08_001AF9C8 * *(f32 *)(vars + 0x78) + D_L08_001AFAC0 * (1.0f - *(f32 *)(vars + 0x78));
        *(f32 *)(vars + 0x5C) = in.speed;
        in.pitch = in.pitch * 0.017453294f * D_L08_001AFA04;
        {
            f32 cur = func_00282DF0(vars) * *(f32 *)(vars + 0x78);
            f32 top = D_L08_001AFA0C * 0.016666668f;
            f32 lim = top < cur ? top : cur;

            cruise = D_L08_001AF9C4 * 0.016666668f;
            *(f32 *)(vars + 0x28) = func_00283B98(*(f32 *)(vars + 0x28),
                D_L08_001AF9B4 * (in.turn * (lim / top * D_L08_001AFA08 + (1.0f - D_L08_001AFA08)
                    + D_L08_001AFAC4 * (1.0f - *(f32 *)(vars + 0x78))) * 0.000290888245f));
            *(f32 *)(vars + 0x20) += (D_L08_001AF9EC * (in.turn * 0.017453294f) * *(f32 *)(vars + 0x78)
                * (D_L08_001AF9F8 * in.speed + (1.0f - D_L08_001AF9F8)) - *(f32 *)(moby + 0xF0)) * D_L08_001AF9E8;
            dir[0] = func_00283180(*(f32 *)(vars + 0x28));
            dir[1] = func_00283198(*(f32 *)(vars + 0x28));
            dir[2] = 0.0f;
            if (in.speed < dir[2]) {
                in.speed *= D_L08_001AF9F0;
            }
            if (in.speed < dir[2]) {
                sign = -1.0f;
            }
            landed = 0;
            {
                f32 s = func_00282C48(in.turn);
                f32 k = func_L08_003277C0(2, (cruise - cur) / cruise);
                *(f32 *)(moby + 0x48) += (in.speed * D_L08_001AFAB4 - *(f32 *)(moby + 0x48)) * 0.02f;
                roll = (in.speed + D_L08_001AF9F4 * s * sign) * 0.00027777778f * D_L08_001AF9C0 * k;
            }
        }
        func_00282CC0(v40, moby + 0x10, vars);
        ground = func_002A89A8(v40, 0, 0.5f);
        if (func_00278E78() == 1 || func_00278E78() == 0xB) {
            landed = 1;
        }
        floor = ground + blend;
        if (*(f32 *)(moby + 0x18) < floor + 0.3f) {
            if (landed) {
                *(u8 *)(moby + 0x20) = 5;
            }
        }
        if (D_L08_001AF994 - D_L08_001AF998 < *(s32 *)(vars + 0xAC)) {
            *(f32 *)(vars + 0x8) += D_L08_001AF990 * 0.00027777778f;
        } else {
            *(f32 *)(vars + 0x8) -= D_L08_001AF9DC * 0.00027777778f;
        }
        if (ground != 0.0f) {
            steer = 1;
            if (floor < v40[2]) {
                *(f32 *)(vars + 0x24) = func_00283B98(*(f32 *)(vars + 0x24),
                    func_00283BE0(in.pitch, *(f32 *)(vars + 0x24)) * D_L08_001AFA00);
                if (D_001A79F0 == 8) {
                    steer = 0;
                }
            } else {
                if (*(s32 *)(vars + 0xAC) == 0 && in.thrust > 0.2f) {
                    *(s32 *)(vars + 0xAC) = D_L08_001AF994;
                }
                if (v40[2] + 0.1f < ground || landed) {
                    v40[2] = ground;
                    func_00282D30(vars, vars, D_L08_001AF9E4);
                }
                *(f32 *)(vars + 0x8) += ((floor - v40[2]) * D_L08_001AF9CC - *(f32 *)(vars + 0x8)) * D_L08_001AF9CC;
                if (in.bank > 0.0f) {
                    f32 damp = 1.0f - D_L08_001AFA10 * in.bank;
                    *(f32 *)(vars + 0x0) *= damp;
                    *(f32 *)(vars + 0x4) *= damp;
                }
                func_00282F20(v70, D_L08_001BFF80, 1.0f);
                func_00282DD8(v60, moby + 0xC0, v70);
                func_00282DD8(v50, v60, v70);
                qzero_nc(basis[3]);
                func_002AB6D8(basis, v90);
                *(f32 *)(vars + 0x24) = func_00283B98(*(f32 *)(vars + 0x24),
                    func_00283BE0(func_00283B98(-v90[1], in.pitch * 0.5f * (D_L08_001AFAC8 * (*(f32 *)(vars + 0x78) + 1.0f))),
                        *(f32 *)(vars + 0x24)) * D_L08_001AF9FC);
                func_00282D30(vars, vars, D_L08_001AF9B8);
                func_00283698(inverse_work.inverse, moby + 0xC0);
                func_002830C0(vars, vars, inverse_work.inverse);
                *(f32 *)(vars + 0x4) *= D_L08_001AF9BC;
                func_00283098(vars, vars, moby + 0xC0);
            }
            if (steer) {
                func_00282F20(v30, moby + 0xC0, roll);
                func_00282F20(v50, moby + 0xD0, D_L08_001AFAD4 * (in.lift * 0.00027777778f) * *(f32 *)(vars + 0x78));
                func_00282CC0(v30, v30, v50);
                func_00282CC0(vars, vars, v30);
            }
        }
        func_002A8C00(&request, moby, 0x10000, vars, D_L08_001AFA70);
        *(TI128 *)(moby + 0x10) = *(TI128 *)v40;
        func_0029FCC0(moby, 0, v80);
        v80[2] += D_L08_001AF9D0 - D_L08_001AFAC0;
        func_00282CF0(v90, moby + 0x10, v80);
        *(s32 *)(moby + 0x98) = 0;
        {
            s32 found = func_00278870(v80, D_L08_001AF9D0);
            if (found == 0) {
                found = func_00277258(v80, 2, moby, D_L08_001AF9D0);
            }
            *(s32 *)(moby + 0x98) = *(s32 *)(*(u8 **)(moby + 0x24) + 0x10);
            if (found != 0) {
                u8 *col;
                if (func_00278E78() == 1 || func_00278E78() == 0xB) {
                    *(u8 *)(moby + 0x20) = 5;
                }
                col = D_L08_001BFF40;
                if (*(u8 **)(col + 0x18) != ((Hero *)D_00189E20)->ptr[0x2290 / 4]) {
                    *(f32 *)(col + 0x30) -= v80[0];
                    *(f32 *)(col + 0x34) -= v80[1];
                    *(f32 *)(col + 0x30) *= *(f32 *)(vars + 0x78);
                    *(f32 *)(col + 0x30) += v80[0];
                    *(f32 *)(col + 0x34) *= *(f32 *)(vars + 0x78);
                    *(f32 *)(col + 0x34) += v80[1];
                    func_00282CC0(moby + 0x10, col + 0x30, v90);
                    func_00282DD8(vB0, col + 0x40, vars);
                    func_00282DD8(vA0, vB0, col + 0x40);
                    func_00282F20(vA0, vA0, 1.0f);
                    func_00282F20(vars, vA0, func_00282DB0(vars, vA0) * *(f32 *)(vars + 0x78));
                    func_00282D30(vars, vars, D_L08_001AF9E0);
                }
            }
        }
        if (*(u8 *)(moby + 0x20) == 3) {
            if (*(f32 *)(vars + 0x78) < 0.98f && (((Pad *)D_00138180)->w[0x1A0 / 4] & 4)) {
                if (*(f32 *)(vars + 0x68) < D_L08_001B031C) {
                    func_L08_003C67B8(moby, D_L08_001BFF60, D_L08_001AFB94, D_L08_001AFB8C, D_L08_001AFB90,
                        D_L08_001AFB88, D_L08_001AFB88, D_L08_001AFB98, D_L08_001AFB9C);
                    if (func_002A77E0(9) == 0) {
                        *(s32 *)(D_L08_001B99C0 + 0x168) = 0x14;
                        *(s32 *)(D_L08_001B99C0 + 0x16C) = 0;
                        *(f32 *)(D_L08_001B99C0 + 0x160) = (1.0f - *(f32 *)(vars + 0x78)) * 0.1f;
                    }
                } else {
                    func_L08_003C67B8(moby, D_L08_001BFF60, D_L08_001AFBAC, D_L08_001AFBA4, D_L08_001AFBA8,
                        D_L08_001AFBA0, D_L08_001AFBA0, D_L08_001AFBB0, D_L08_001AFBB4);
                }
            }
            func_L08_003C67B8(moby, D_L08_001BFF60, D_L08_001AFB7C, D_L08_001AFB74, D_L08_001AFB78,
                D_L08_001AFB70, D_L08_001AFB80, D_L08_001AFB84, 1.0f);
        }
        func_0029FCC0(moby, 0, v80);
        v80[2] += D_L08_001AFA78;
        func_00277F48(D_L08_001AFA14, v80, 0, moby, &request);
        if (D_L08_001AFA7C * 0.016666668f < func_00282DF0(vars)) {
            func_0029FCC0(moby, 3, vA0);
            func_00277F48(D_L08_001AFA74, vA0, 0, moby, &request);
        }
        if (in.fire == 0 && ((Hero *)D_00189E20)->ptr[0x1830 / 4] == moby && (((Pad *)D_00138180)->w[0x1A4 / 4] & 0x10)) {
            *(u8 *)(moby + 0x20) = 4;
        }
        break;
    }
    case 4:
        *(s32 *)(moby + 0x98) = *(s32 *)(*(u8 **)(moby + 0x24) + 0x10);
        *(s32 *)(((Hero *)D_00189E20)->ptr[0x2290 / 4] + 0x9C) = 0;
        func_L08_002D2ED8(0, 1);
        ((Hero *)D_00189E20)->h[0x1834 / 2] = -1;
        ((Hero *)D_00189E20)->f[0x108 / 4] = 0.16666667f;
        ((Hero *)D_00189E20)->ptr[0x1830 / 4] = 0;
        ((Hero *)D_00189E20)->f[0x88 / 4] += 1.0f;
        if (*(u8 **)(vars + 0x74) != 0) {
            func_0029F338(*(u8 **)(vars + 0x74));
        }
        *(u8 **)(vars + 0x74) = 0;
        *(s16 *)(vars + 0x88) = 0;
        *(u8 *)(vars + 0x8A) = 0;
        *(u8 *)(moby + 0x20) = 1;
        break;
    case 5:
        *(s32 *)(moby + 0x98) = *(s32 *)(*(u8 **)(moby + 0x24) + 0x10);
        *(s32 *)(((Hero *)D_00189E20)->ptr[0x2290 / 4] + 0x9C) = 0;
        func_L08_002D2ED8(0, 1);
        func_0029FCC0(moby, 0, dir);
        func_002ABBB8(moby, vars, dir, 0.0f, 0.0f, 10, 3, 16, 4.0f, 2.0f, 9.0f, 1.0f, -1, 15.0f, 1, 1, -1, 0, 0x810001);
        *(TI128 *)(moby + 0x10) = *(TI128 *)(vars + 0x30);
        ((Hero *)D_00189E20)->h[0x1834 / 2] = -1;
        ((Hero *)D_00189E20)->ptr[0x1830 / 4] = 0;
        if (*(u8 **)(vars + 0x74) != 0) {
            func_0029F338(*(u8 **)(vars + 0x74));
        }
        *(u8 **)(vars + 0x74) = 0;
        *(s16 *)(vars + 0x88) = 0;
        *(u8 *)(vars + 0x8A) = 0;
        *(u8 *)(moby + 0x20) = 0;
        break;
    case 6:
        break;
    }
    *(f32 *)(vars + 0x58) = *(f32 *)(moby + 0x18);
    *(f32 *)(vars + 0x48) = func_00283B98(*(f32 *)(vars + 0x48), D_L08_001AF9A4 * (*(f32 *)(vars + 0x78) * 0.000290888245f));
    *(f32 *)(vars + 0x4C) = func_00283198(*(f32 *)(vars + 0x48)) * D_L08_001AF9A0 * *(f32 *)(vars + 0x78);
    *(f32 *)(moby + 0x18) += *(f32 *)(vars + 0x4C) * *(f32 *)(vars + 0x78);
    func_002AEF28(moby, vars + 0x50, vars + 0x54, D_L08_001AF9A8 * 0.017453294f,
        D_L08_001AF9AC * (*(f32 *)(vars + 0x78) * 0.000290888245f),
        D_L08_001AF9B0 * (*(f32 *)(vars + 0x78) * 0.000290888245f));
    *(f32 *)(moby + 0xF8) = *(f32 *)(vars + 0x28);
    *(f32 *)(moby + 0xF0) = func_00283B98(*(f32 *)(moby + 0xF0), *(f32 *)(vars + 0x20));
    *(f32 *)(moby + 0xF4) = func_00283B98(*(f32 *)(moby + 0xF4), *(f32 *)(vars + 0x24));
    if (*(u8 *)(moby + 0x20) == 3) {
        if (D_001A79F0 == 8) {
            switch (*(u8 *)(vars + 0x8A)) {
            case 0:
                if (*(f32 *)(vars + 0x68) < D_L08_001B031C) {
                    *(u8 *)(vars + 0x8A) = 1;
                    *(s16 *)(vars + 0x88) = 0;
                }
                break;
            case 1:
                *(s16 *)(vars + 0x88) += 1;
                if (D_L08_001AFB14 < *(s16 *)(vars + 0x88)) {
                    *(s16 *)(vars + 0x88) = D_L08_001AFB14;
                }
                if (D_L08_001B031C < *(f32 *)(vars + 0x68)) {
                    *(u8 *)(vars + 0x8A) = 3;
                } else if (*(s16 *)(vars + 0x88) >= D_L08_001AFB14) {
                    *(u8 *)(vars + 0x8A) = 2;
                }
                break;
            case 2:
                if (D_L08_001B031C < *(f32 *)(vars + 0x68)) {
                    *(u8 *)(vars + 0x8A) = 3;
                }
                break;
            case 3:
                func_00282978(vars + 0x88);
                if (*(f32 *)(vars + 0x68) < D_L08_001B031C) {
                    *(u8 *)(vars + 0x8A) = 1;
                } else if (*(s16 *)(vars + 0x88) == 0) {
                    *(u8 *)(vars + 0x8A) = 0;
                }
                break;
            }
            if (*(u8 *)(vars + 0x8A) != 0 && *(u8 **)(vars + 0x6C) != 0) {
                u8 *anim = *(u8 **)(*(u8 **)(vars + 0x6C) + 0x68);
                *(s16 *)(vars + 0x8C) = func_00283CF0(func_00283CE0((D_L08_001AFB18 - 1) << 5)
                    * func_00283CE0(*(s32 *)(anim + 0x4)) / (func_00283CE0(*(s32 *)(anim + 0x0)) * 60.0f));
            } else {
                *(s16 *)(vars + 0x8C) = 0x200;
            }
            if (*(u8 **)(vars + 0x6C) != 0) {
                if (*(u8 **)(vars + 0x74) == 0) {
                    *(u8 **)(vars + 0x74) = func_L08_00435600(moby, *(u8 **)(vars + 0x6C) + 0x10);
                } else {
                    func_L08_004356A0(*(u8 **)(vars + 0x74), *(u8 **)(vars + 0x6C) + 0x10);
                }
            } else if (*(u8 **)(vars + 0x74) != 0) {
                func_0029F338(*(u8 **)(vars + 0x74));
                *(u8 **)(vars + 0x74) = 0;
            }
        }
        func_0029FCC0(moby, D_L08_001AFA84, D_00189E20 + 0x80);
        ((Hero *)D_00189E20)->f[0x88 / 4] += D_L08_001AFA88;
        *(TI128 *)(D_00189E20 + 0x90) = *(TI128 *)(moby + 0xF0);
        func_L00_002E6EF8(D_L08_003C5940, moby);
    }
    *(s32 *)(moby + 0x98) = *(s32 *)(*(u8 **)(moby + 0x24) + 0x10);
    if (*(u8 *)(moby + 0x31) != 0 && func_00282E48(moby + 0x10, D_L08_001B9B00) < 64.0f) {
        func_002A93B0(moby);
        *(u8 *)(moby + 0x6F) = 0x3C;
    }
    *(u8 **)(vars + 0x6C) = 0;
    *(f32 *)(vars + 0x68) = 1000000.0f;
    func_L08_003C66F0(moby);
}
