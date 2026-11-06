/* func_PAL_L08_003CA508, the PAL copy of func_L08_003C6AB0: the same C, where the frame counts (pvars+0x8B, pvars+0x7C,
 * pvars+0xAC, the pvars+0x88 limit) become (n * 5 + 2) / 6, loaded as words; the throttle rates are scaled by 1.2;
 * 1/60 becomes 1/50, 1/3600 becomes 1/2500, a degree per frame (pi/10800) becomes pi/9000, 1/6 becomes 1/5,
 * the animation rate's 60 frames become (n * 60 * 5 + 2) / 6, and the shake count 0x14 becomes 0x11.
 *
 * The update of a rideable moby (levels 8, 19 and 30): a pvars block at moby+0x68, a seven-entry
 * state switch on moby+0x20, then a byte state on pvars+0x8A when the level flag is 8.
 *
 * What fixes the bytes:
 * - moby and pvars are real structures: a fixed scalar load cannot alias a varying structure member, so the tuning
 *   floats issue ahead of the stores between them without being const.
 * - The six inputs are scalars with their address taken, so they get their slots after the arrays. fire stays a
 *   pseudo that reload spills to the slot after them.
 * - The 64-byte inverse and the two vectors have their own blocks, which share one stack slot.
 * - ground + blend is an expression at each use: PRE makes the copy that retail keeps in $f21.
 * - The products are separate statements because fold rebalances four or more factors.
 * - `else t = 0` is a dead store that keeps the arm from if-conversion (retail has no movn); flow deletes it.
 * - scale holds pvars+0x78 before speed is loaded and frame holds 1/50 before its uses. Each shifts a live length in
 *   sched1's order, which decides local-alloc's FP registers in this long block (calls do not end it).
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
typedef struct { u8 pad[0xA]; u16 index; u8 tail[4]; } Row16;
typedef union { u8 b[0x400]; u32 w[0x100]; } Pad;
typedef union { u8 b[0x2600]; s16 h[0x1300]; s32 i[0x980]; f32 f[0x980]; u8 *ptr[0x980]; TI128 q[0x260]; } Hero;

typedef struct {
    f32 x0;
    f32 x4;
    f32 x8;
    u8 padC[0x14];
    f32 x20;
    f32 x24;
    f32 x28;
    u8 pad2C[0x4];
    TI128 x30;
    u8 pad40[0x8];
    f32 x48;
    f32 x4C;
    u8 pad50[0x8];
    f32 x58;
    f32 x5C;
    f32 x60;
    s32 x64;
    f32 x68;
    u8 *x6C;
    u8 pad70[0x4];
    u8 *x74;
    f32 x78;
    s16 x7C;
    u16 x7E;
    u8 pad80[0x8];
    s16 x88;
    u8 x8A;
    u8 x8B;
    s16 x8C;
    u8 pad8E[0x9];
    u8 x97;
    u8 x98;
    u8 x99;
    u8 pad9A[0x6];
    u8 *xA0;
    s32 xA4;
    s32 xA8;
    s32 xAC;
} RideVars;
typedef struct {
    u8 pad0[0x10];
    RideVector pos;
    u8 x20;
    u8 pad21[0x3];
    u8 *x24;
    u8 pad28[0x4];
    f32 x2C;
    u8 pad30[0x1];
    u8 x31;
    u8 pad32[0x16];
    f32 x48;
    u8 pad4C[0x1C];
    u8 *x68;
    u8 pad6C[0x3];
    u8 x6F;
    u8 pad70[0x28];
    s32 x98;
    u8 pad9C[0xC];
    u8 xA8;
    u8 padA9[0x47];
    RideVector rot;
} RideMoby;

extern s32 func_002829A8(void *);
extern void *func_002A9640(void *, u32, s32);
extern void func_PAL_002AC290(void *, void *);
extern void func_PAL_002AC3C0(void *, void *);
extern f32 func_002A0558(void *, void *);
extern s32 func_002B0C28(s32, s32, s32);
extern s32 func_PAL_L08_002D3078(s32, s32);
extern void func_PAL_L00_002D2668(int, int, f32);
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
extern void func_002A8C00(f32, void *, void *, s32, void *);
extern void func_0029FCC0(void *, int, void *);
extern void func_00282CF0(void *, void *, void *);
extern s32 func_00278870(void *, f32);
extern s32 func_00277258(void *, s32, void *, f32);
extern f32 func_00282DB0(void *, void *);
extern void func_PAL_L08_003CA1C8(void *, void *, s32, f32, f32, f32, f32, f32, f32);
extern s32 func_00277F48(f32, void *, s32, void *, void *);
extern void func_0029F338(void *);
extern void func_PAL_002AC718(void *, void *, void *, float, float, int, int, int, float, float, float, float, int, float, int, int, int, int, int);
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
extern s32 D_001A79F0 MACRO_ADDR;
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
extern s32 D_L08_001AFACC __attribute__((sda));
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
extern s32 D_L08_001AFBB8 __attribute__((sda));
extern f32 D_L08_001B031C MACRO_ADDR;
extern u8 *D_L08_001B2484 MACRO_ADDR;
extern u8 D_L08_001B99C0[];
extern u8 D_L08_001B9B00[];
extern u8 D_L08_001BE700[];
extern u8 D_L08_001BFF40[];
extern u8 D_L08_001BFF60[];
extern u8 D_L08_001BFF80[];
extern Block400 D_L08_0023E6A0;
extern void func_L08_003C5940(void);

void func_PAL_L08_003CA508(RideMoby *moby)
{
    f32 dir[4] __attribute__((aligned(16)));
    f32 v30[4] __attribute__((aligned(16)));
    f32 v40[4] __attribute__((aligned(16)));
    union {
        f32 basis[4][4];
        struct { RideQuery request; RideVector position; } query;
    } work;
    f32 v90[4] __attribute__((aligned(16)));
    f32 turn;
    f32 speed;
    f32 pitch;
    f32 bank;
    f32 lift;
    f32 thrust;
    s32 fire;
    RideVars *vars;
    u8 *hit;
    u8 *other;

    vars = (RideVars *)moby->x68;
    if (func_002829A8((u8 *)vars + 0x8B) != 0) {
        vars->xA0 = 0;
    }
    if (moby->x20 != 0) {
        moby->pos.f[2] = vars->x58;
        hit = func_002A9640(moby, 1, 0);
        if (hit != 0 && (other = *(u8 **)(hit + 0x20)) != 0) {
            s16 kind = *(s16 *)(other + 0xAA);
            if (kind != 0x85C && kind != 0x942 && kind != 0xFFF) {
                if (other != vars->xA0 || vars->x8B == 0) {
                    vars->x97 = 0xD2;
                    vars->x98 = 0xD2;
                    vars->x99 = 0xD2;
                    func_PAL_002AC290(moby, (u8 *)vars + 0x90);
                    vars->x60 -= *(f32 *)(hit + 0x2C);
                    ((Hero *)D_00189E20)->f[0x183C / 4] = vars->x60;
                    if (vars->x60 <= 0.0f) {
                        moby->x20 = 5;
                    }
                    vars->xA0 = *(u8 **)(hit + 0x20);
                    vars->x8B = (D_L08_001AFBB8 * 5 + 2) / 6;
                }
            }
        }
        moby->xA8 = 0xFF;
    } else {
        vars->x58 = moby->pos.f[2];
    }
    func_PAL_002AC3C0(moby, (u8 *)vars + 0x90);
    moby->x2C = *(f32 *)(moby->x24 + 0x24) * D_L08_001AFA6C;
    if (((Hero *)D_00189E20)->ptr[0x1830 / 4] == (u8 *)moby) {
        ((Hero *)D_00189E20)->i[0x1848 / 4] = ((Hero *)D_00189E20)->f[0x183C / 4] / D_L08_001AFA80 * 200.0f;
    }
    fire = 0;
    switch (moby->x20) {
    case 0: {
        u8 *src = D_L08_001B2484 + ((Row16 *)D_L08_001BE700)[vars->x64 + D_L08_001AFA50].index * 16;
        s32 done = D_L08_001AFADC;
        D_L08_001AFAD8 = src;
        vars->xA8 = 0xFF;
        vars->xA4 = 0;
        if (done == 0) {
            D_L08_0023E6A0 = *(Block400 *)src;
        }
        D_L08_001AFADC = 1;
        vars->x30 = moby->pos.q;
        qzero_nc(vars);
        {
            f32 health = D_L08_001AFA80;
            vars->x60 = health;
            ((Hero *)D_00189E20)->f[0x183C / 4] = health;
            ((Hero *)D_00189E20)->f[0x1840 / 4] = health;
        }
        vars->x74 = 0;
        moby->x20 = 1;
        vars->x78 = 0.0f;
        vars->xAC = 0;
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
            s32 t = func_002B0C28(7, 0x12ea, 1) != 0;
            if (((Pad *)D_00138180)->w[0x1A4 / 4] & 0x10) {
                fire = t;
            } else {
                t = 0;
            }
        }
        if (fire != 0) {
            func_PAL_L08_002D3078(0x31, 0);
            func_PAL_L00_002D2668(D_L08_001AF9D4, 0, 15.0f);
            *(TI128 *)(D_00189E20 + 0x90) = moby->rot.q;
            *(TI128 *)(D_00189E20 + 0x80) = moby->pos.q;
            ((Hero *)D_00189E20)->ptr[0x1830 / 4] = (u8 *)moby;
            moby->x20 = 3;
            *(s32 *)(((Hero *)D_00189E20)->ptr[0x2290 / 4] + 0x9C) = -1;
        }
        /* fallthrough */
    case 3: {
        f32 sign;
        f32 blend;
        f32 cruise;
        f32 ground;
        s32 landed;
        s32 steer;
        f32 roll;
        f32 scale;

        moby->x98 = 0;
        func_00282978((u8 *)vars + 0x7C);
        func_00282948((u8 *)vars + 0xAC);
        {
            f32 zero = 0.0f;
            turn = zero;
            speed = zero;
            pitch = zero;
            bank = zero;
            lift = zero;
            thrust = zero;
        }
        if (moby->x20 == 3) {
            if ((((Pad *)D_00138180)->w[0x1A0 / 4] & 8) && vars->x7C == 0) {
                u8 **list = (u8 **)((u8 *)vars + 0x80);
                s32 wait;
                list += vars->x7E & 1;
                *(*list + 0xBC) = 1;
                wait = D_L08_001AFACC;
                vars->x7E ^= 1;
                vars->x7C = (wait * 5 + 2) / 6;
            }
            if (((Pad *)D_00138180)->w[0x1A0 / 4] & 4) {
                vars->x78 -= ((D_L08_001AFAB8) * 1.2f);
                if (func_002A77E0(9) == 0 || (((Pad *)D_00138180)->w[0x1A4 / 4] & 4)) {
                    func_L08_003C63F0((char *)moby);
                }
            } else {
                vars->x78 += ((D_L08_001AFABC) * 1.2f);
            }
            if (D_L08_001AF9D8 != D_L08_001AF9D4 && D_L08_001AF9D4 != -1) {
                func_PAL_L00_002D2668(D_L08_001AF9D4, 0, 15.0f);
            }
            func_L08_003C6528(&turn, &speed, &pitch, &bank, &lift, &thrust);
        } else {
            vars->x78 -= ((D_L08_001AFAB8) * 1.2f);
        }
        if (vars->x78 > 1.0f) {
            vars->x78 = 1.0f;
        } else if (vars->x78 < 0.0f) {
            vars->x78 = 0.0f;
        }
        scale = vars->x78;
        sign = 1.0f;
        speed *= scale;
        bank += 1.0f - vars->x78;
        lift *= vars->x78;
        thrust *= vars->x78;
        vars->x5C = speed;
        blend = D_L08_001AF9C8 * vars->x78 + D_L08_001AFAC0 * (1.0f - vars->x78);
        pitch = pitch * 0.017453294f;
        pitch *= D_L08_001AFA04;
        {
            f32 raw = func_00282DF0(vars);
            f32 frame = 0.020000001f;
            f32 cur = raw * vars->x78;
            f32 top = D_L08_001AFA0C * frame;
            f32 lim = cur < top ? cur : top;
            f32 rate, slew, target, gain, rad;

            rate = turn * (lim / top * D_L08_001AFA08 + (1.0f - D_L08_001AFA08)
                + D_L08_001AFAC4 * (1.0f - vars->x78));
            slew = rate * 0.0003490659f;
            cruise = D_L08_001AF9C4 * frame;
            vars->x28 = func_00283B98(vars->x28, D_L08_001AF9B4 * slew);
            gain = D_L08_001AF9F8 * speed + (1.0f - D_L08_001AF9F8);
            rad = turn * 0.017453294f;
            target = D_L08_001AF9EC * rad * vars->x78;
            vars->x20 += (target * gain - moby->rot.f[0]) * D_L08_001AF9E8;
            dir[0] = func_00283180(vars->x28);
            dir[1] = func_00283198(vars->x28);
            dir[2] = 0.0f;
            {
                f32 zero = dir[2];
                if (speed < zero) {
                    speed *= D_L08_001AF9F0;
                }
                if (speed < zero) {
                    sign = -1.0f;
                }
            }
            landed = 0;
            {
                f32 s = func_00282C48(turn), k = func_L08_003277C0(2, (cruise - cur) / cruise);
                {
                    f32 t = speed + D_L08_001AF9F4 * s * sign;
                    t *= 0.00040000002f;
                    moby->x48 += (speed * D_L08_001AFAB4 - moby->x48) * 0.02f;
                    t *= D_L08_001AF9C0;
                    roll = t * k;
                }
            }
        }
        func_00282CC0(v40, (u8 *)moby + 0x10, vars);
        ground = func_002A89A8(v40, 0, 0.5f);
        if (func_00278E78() == 1 || func_00278E78() == 0xB) {
            landed = 1;
        }
        if (moby->pos.f[2] < ground + blend + 0.3f) {
            if (landed) {
                moby->x20 = 5;
            }
        }
        if (D_L08_001AF994 - D_L08_001AF998 < vars->xAC) {
            vars->x8 += D_L08_001AF990 * 0.00040000002f;
        } else {
            vars->x8 -= D_L08_001AF9DC * 0.00040000002f;
        }
        if (ground != 0.0f) {
            steer = 1;
            if (ground + blend < v40[2]) {
                vars->x24 = func_00283B98(vars->x24,
                    func_00283BE0(pitch, vars->x24) * D_L08_001AFA00);
                if (D_001A79F0 == 8) {
                    steer = 0;
                }
            } else {
                if (vars->xAC == 0 && thrust > 0.2f) {
                    vars->xAC = (D_L08_001AF994 * 5 + 2) / 6;
                }
                if (v40[2] + 0.1f < ground || landed) {
                    v40[2] = ground;
                    func_00282D30(vars, vars, D_L08_001AF9E4);
                }
                vars->x8 += ((ground + blend - v40[2]) * D_L08_001AF9CC - vars->x8) * D_L08_001AF9CC;
                if (bank > 0.0f) {
                    f32 damp = 1.0f - D_L08_001AFA10 * bank;
                    vars->x0 *= damp;
                    vars->x4 *= damp;
                }
                func_00282F20(work.basis[2], D_L08_001BFF80, 1.0f);
                func_00282DD8(work.basis[1], (u8 *)moby + 0xC0, work.basis[2]);
                func_00282DD8(work.basis[0], work.basis[1], work.basis[2]);
                qzero_nc(work.basis[3]);
                func_002AB6D8(work.basis, v90);
                {
                    f32 half = pitch * 0.5f;
                    f32 rise = D_L08_001AFAC8 * (vars->x78 + 1.0f);
                    vars->x24 = func_00283B98(vars->x24,
                        func_00283BE0(func_00283B98(-v90[1], half * rise),
                            vars->x24) * D_L08_001AF9FC);
                }
                func_00282D30(vars, vars, D_L08_001AF9B8);
                {
                    f32 inverse[4][4] __attribute__((aligned(16)));

                    func_00283698(inverse, (u8 *)moby + 0xC0);
                    func_002830C0(vars, vars, inverse);
                }
                vars->x4 *= D_L08_001AF9BC;
                func_00283098(vars, vars, (u8 *)moby + 0xC0);
            }
            if (steer) {
                func_00282F20(v30, (u8 *)moby + 0xC0, roll);
                {
                    f32 climb = lift * 0.00040000002f;
                    func_00282F20(work.basis[0], (u8 *)moby + 0xD0, D_L08_001AFAD4 * climb * vars->x78);
                }
                func_00282CC0(v30, v30, work.basis[0]);
                func_00282CC0(vars, vars, v30);
            }
        }
        func_002A8C00(D_L08_001AFA70, &work.query.request, moby, 0x10000, vars);
        moby->pos.q = *(TI128 *)v40;
        func_0029FCC0(moby, 0, work.query.position.f);
        work.query.position.f[2] += D_L08_001AF9D0 - D_L08_001AFAC0;
        func_00282CF0(v90, (u8 *)moby + 0x10, work.query.position.f);
        moby->x98 = 0;
        {
            s32 found = func_00278870(work.query.position.f, D_L08_001AF9D0);
            if (found == 0) {
                found = func_00277258(work.query.position.f, 2, moby, D_L08_001AF9D0);
            }
            moby->x98 = *(s32 *)(moby->x24 + 0x10);
            if (found != 0) {
                u8 *col;
                if (func_00278E78() == 1 || func_00278E78() == 0xB) {
                    moby->x20 = 5;
                }
                col = D_L08_001BFF40;
                if (*(u8 **)(col + 0x18) != ((Hero *)D_00189E20)->ptr[0x2290 / 4]) {
                    f32 vA0[4] __attribute__((aligned(16)));
                    f32 vB0[4] __attribute__((aligned(16)));

                    *(f32 *)(col + 0x30) -= work.query.position.f[0];
                    *(f32 *)(col + 0x34) -= work.query.position.f[1];
                    *(f32 *)(col + 0x30) *= vars->x78;
                    *(f32 *)(col + 0x34) *= vars->x78;
                    *(f32 *)(col + 0x30) += work.query.position.f[0];
                    *(f32 *)(col + 0x34) += work.query.position.f[1];
                    func_00282CC0((u8 *)moby + 0x10, col + 0x30, v90);
                    func_00282DD8(vB0, col + 0x40, vars);
                    func_00282DD8(vA0, vB0, col + 0x40);
                    func_00282F20(vA0, vA0, 1.0f);
                    func_00282F20(vars, vA0, func_00282DB0(vars, vA0) * vars->x78);
                    func_00282D30(vars, vars, D_L08_001AF9E0);
                }
            }
        }
        if (moby->x20 == 3) {
            if (vars->x78 < 0.98f && (((Pad *)D_00138180)->w[0x1A0 / 4] & 4)) {
                if (vars->x68 < D_L08_001B031C) {
                    func_PAL_L08_003CA1C8(moby, D_L08_001BFF60, D_L08_001AFB94, D_L08_001AFB8C, D_L08_001AFB90,
                        D_L08_001AFB88, D_L08_001AFB88, D_L08_001AFB98, D_L08_001AFB9C);
                    if (func_002A77E0(9) == 0) {
                        f32 amount = (1.0f - vars->x78) * 0.1f;
                        u8 *shake = D_L08_001B99C0;
                        *(s32 *)(shake + 0x168) = 0x11;
                        *(s32 *)(shake + 0x16C) = 0;
                        *(f32 *)(shake + 0x160) = amount;
                    }
                } else {
                    func_PAL_L08_003CA1C8(moby, D_L08_001BFF60, D_L08_001AFBAC, D_L08_001AFBA4, D_L08_001AFBA8,
                        D_L08_001AFBA0, D_L08_001AFBA0, D_L08_001AFBB0, D_L08_001AFBB4);
                }
            }
            func_PAL_L08_003CA1C8(moby, D_L08_001BFF60, D_L08_001AFB7C, D_L08_001AFB74, D_L08_001AFB78,
                D_L08_001AFB70, D_L08_001AFB80, D_L08_001AFB84, 1.0f);
        }
        func_0029FCC0(moby, 0, work.query.position.f);
        work.query.position.f[2] += D_L08_001AFA78;
        func_00277F48(D_L08_001AFA14, work.query.position.f, 0, moby, &work.query.request);
        if (func_00282DF0(vars) > D_L08_001AFA7C * 0.020000001f) {
            f32 vA0[4] __attribute__((aligned(16)));

            func_0029FCC0(moby, 3, vA0);
            func_00277F48(D_L08_001AFA74, vA0, 0, moby, &work.query.request);
        }
        if (fire == 0 && ((Hero *)D_00189E20)->ptr[0x1830 / 4] == (u8 *)moby && (((Pad *)D_00138180)->w[0x1A4 / 4] & 0x10)) {
            moby->x20 = 4;
        }
        break;
    }
    case 4:
        moby->x98 = *(s32 *)(moby->x24 + 0x10);
        *(s32 *)(((Hero *)D_00189E20)->ptr[0x2290 / 4] + 0x9C) = 0;
        func_PAL_L08_002D3078(0, 1);
        ((Hero *)D_00189E20)->h[0x1834 / 2] = -1;
        ((Hero *)D_00189E20)->f[0x108 / 4] = 0.20000002f;
        ((Hero *)D_00189E20)->ptr[0x1830 / 4] = 0;
        ((Hero *)D_00189E20)->f[0x88 / 4] += 1.0f;
        if (vars->x74 != 0) {
            func_0029F338(vars->x74);
        }
        vars->x74 = 0;
        vars->x88 = 0;
        vars->x8A = 0;
        moby->x20 = 1;
        break;
    case 5:
        moby->x98 = *(s32 *)(moby->x24 + 0x10);
        *(s32 *)(((Hero *)D_00189E20)->ptr[0x2290 / 4] + 0x9C) = 0;
        func_PAL_L08_002D3078(0, 1);
        func_0029FCC0(moby, 0, dir);
        func_PAL_002AC718(moby, vars, dir, 0.0f, 0.0f, 10, 3, 16, 4.0f, 2.0f, 9.0f, 1.0f, -1, 15.0f, 1, 1, -1, 0, 0x810001);
        moby->pos.q = vars->x30;
        ((Hero *)D_00189E20)->h[0x1834 / 2] = -1;
        ((Hero *)D_00189E20)->ptr[0x1830 / 4] = 0;
        if (vars->x74 != 0) {
            func_0029F338(vars->x74);
        }
        vars->x74 = 0;
        vars->x88 = 0;
        vars->x8A = 0;
        moby->x20 = 0;
        break;
    case 6:
        break;
    }
    vars->x58 = moby->pos.f[2];
    {
        f32 t = vars->x78 * 0.0003490659f;
        vars->x48 = func_00283B98(vars->x48, D_L08_001AF9A4 * t);
    }
    {
        f32 t;
        vars->x4C = func_00283198(vars->x48) * D_L08_001AF9A0 * vars->x78;
        moby->pos.f[2] += vars->x4C * vars->x78;
        t = vars->x78 * 0.0003490659f;
        func_002AEF28(moby, (u8 *)vars + 0x50, (u8 *)vars + 0x54, D_L08_001AF9A8 * 0.017453294f,
            D_L08_001AF9AC * t, D_L08_001AF9B0 * t);
    }
    moby->rot.f[2] = vars->x28;
    moby->rot.f[0] = func_00283B98(moby->rot.f[0], vars->x20);
    moby->rot.f[1] = func_00283B98(moby->rot.f[1], vars->x24);
    if (moby->x20 == 3) {
        if (D_001A79F0 == 8) {
            switch (vars->x8A) {
            case 0:
                if (vars->x68 < D_L08_001B031C) {
                    vars->x8A = 1;
                    vars->x88 = 0;
                }
                break;
            case 1: {
                s32 limit = D_L08_001AFB14;
                vars->x88 += 1;
                if ((limit * 5 + 2) / 6 < vars->x88) {
                    vars->x88 = (D_L08_001AFB14 * 5 + 2) / 6;
                }
                if (vars->x68 > D_L08_001B031C) {
                    vars->x8A = 3;
                } else if (vars->x88 >= (D_L08_001AFB14 * 5 + 2) / 6) {
                    vars->x8A = 2;
                }
                break;
            }
            case 2:
                if (vars->x68 > D_L08_001B031C) {
                    vars->x8A = 3;
                }
                break;
            case 3:
                func_00282978((u8 *)vars + 0x88);
                if (vars->x68 < D_L08_001B031C) {
                    vars->x8A = 1;
                } else if (vars->x88 == 0) {
                    vars->x8A = 0;
                }
                break;
            }
            if (vars->x8A != 0 && vars->x6C != 0) {
                u8 *anim = *(u8 **)(vars->x6C + 0x68);
                vars->x8C = func_00283CF0(func_00283CE0((D_L08_001AFB18 - 1) << 5)
                    * func_00283CE0(*(s32 *)(anim + 0x4)) / ((func_00283CE0(*(s32 *)(anim + 0x0)) * 60.0f * 5 + 2) / 6));
            } else {
                vars->x8C = 0x200;
            }
            if (vars->x6C != 0) {
                if (vars->x74 == 0) {
                    vars->x74 = func_L08_00435600(moby, vars->x6C + 0x10);
                } else {
                    func_L08_004356A0(vars->x74, vars->x6C + 0x10);
                }
            } else if (vars->x74 != 0) {
                func_0029F338(vars->x74);
                vars->x74 = 0;
            }
        }
        func_0029FCC0(moby, D_L08_001AFA84, D_00189E20 + 0x80);
        ((Hero *)D_00189E20)->f[0x88 / 4] += D_L08_001AFA88;
        *(TI128 *)(D_00189E20 + 0x90) = moby->rot.q;
        func_L00_002E6EF8(func_L08_003C5940, moby);
    }
    moby->x98 = *(s32 *)(moby->x24 + 0x10);
    if (moby->x31 != 0 && func_00282E48((u8 *)moby + 0x10, D_L08_001B9B00) < 64.0f) {
        func_002A93B0(moby);
        moby->x6F = 0x3C;
    }
    vars->x6C = 0;
    vars->x68 = 1000000.0f;
    func_L08_003C66F0(moby);
}
