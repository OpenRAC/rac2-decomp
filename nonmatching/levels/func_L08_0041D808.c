/* 2 November 2026: retained nonmatching C; no linked matching credit.
 * Profile: -O2 -G8 -ffunction-sections -g.
 * USA v1.01 check: 3312/3308 bytes, 0/1 placements.
 * Remove all three forbidden do-while(0) wrappers and their overwritten dead locals; each real
 * rounded coordinate is assigned directly. Correct the int returns of 00300090, 003000C0 and
 * 002E5DA0 from their matched definitions. This meaningful natural draft is 3312/3308 bytes,
 * 0/1 US placement, with the complete 0xE0 frame. HUD coordinate/pack argument scheduling and
 * allocation remain; the earlier forbidden 3308-byte diagnostic is historical, not the current
 * source.
 */
/* Earlier notes below describe superseded diagnostic variants. */
/* Claude Opus 5.5 (xhigh effort), task v1821, USA v1.01, 31 October 2026.
 * Best check: 3308 bytes, the retail size, 0/1 places; first difference at +0x1cc. A scratch
 * alignment masking non-sp memory offsets, lui immediates and jal targets counts 53 of 827 rows,
 * about 20 of them .word display artefacts; opus-1's draft counts 65 on the same counter, at 3316
 * bytes with two padding nops. This form has no padding.
 * NOT a match and NOT landable: sites A, B and the last sprite still use a forbidden do/while(0)
 * wrapper and placeholder `dead` locals. No match is claimed. No linked build or PAL/US2 check was
 * run. About 30 check.py compiles, plus -da and -fsched-verbose dumps.
 * Profile: dedicated unit L08_0041D808-g8.c, -O2 -G8 -ffunction-sections -g. On the dead-arm form,
 * -frac2-keep-block-order, -frac2-gcse-unsplit-edges, -frac2-no-null-pointer-checks and
 * -frac2-hazard-labels did not change the row count.
 *
 * The overseer's "vanished test" lead, site by site:
 * - WORKS at the height pair (0x41DBDC-0x41DC30): HudYM and HudSize share a `mode` local, as
 *   func_002D3D88 does, and HudSize tests `mode != 0`. Retail's t0/v1 and the v1 result follow with
 *   no extra word, and that wording is clean. `mode == 1` there leaves a stray `addiu v0,1` (3312).
 * - DOES NOT close A (0x41D98C), B (0x41DA30) or the last sprite (about 0x41E420): retail shows no
 *   mode value in a register there. HudSize(D_L08_001B3240, ...) leaves the lw and the constant
 *   behind: 3388 bytes absolute, 3376 through a $gp alias.
 *
 * What A and B seem to need (the helper is still unknown):
 * - Measured: with a real branch merged at jump2, the sprite A group from the lw to the jal comes out
 *   in retail's order. With a loop note, the sched2 table shows the lw issuing alone as the barrier,
 *   which is the remaining order difference in both sprites. Inferred: retail has a real block
 *   boundary there, with lw and li a1 in one tick.
 * - That diagnostic was `tex == 1` with both arms (int)scaled, a placeholder condition, so it is not
 *   landable; it was also not exact. It lost the sharing of s1=1, f22=0.5f, f21=1.0f and f20=0.0f
 *   across A and B, so retail is probably one-armed at cse. Explicit constant locals did not restore it.
 * - Measured: tex is a2 when a0 holds the test's load or constant during allocation, and a0 otherwise,
 *   so retail's a0 was probably occupied. A dead-arm test gives a2 and 3308 bytes with no wrapper, but
 *   flow2 deletes the jump, so no boundary is left and the count is 95. A referenced user label is
 *   in the greg dump and gone from the flow2 dump, so it does not help.
 * Next idea: a one-armed test on a value already in a register, whose arm survives flow2's block
 * tidy and is empty by jump2. Which real value that is remains open. From memory of GCC 2.95, not
 * checked in this tree: flow2 deletes no-op moves after its tidy, and delete_computation skips the
 * operands' setters after reload when sched2 is on, which would explain why the load stays.
 *
 * Remaining differences:
 * - Both sprites: H-group order, from the barrier described above.
 * - 0x41DB10: retail stores gradient.a after the div.s. Store order b,a swaps a0/a1 and v0/v1.
 * - 0x41DBD4-0x41DC34: h is v0 and the D_001A7344 copy a3; retail has a3 and t1. New with the real
 *   helper: the priority of h against gcse's copy flips. A shared `one` local swaps t0/v1 instead.
 * - 0x41DF40: arg order; retail is a1, a2, jal, a0 in the slot; here a1, a0, jal, a2. A local for the
 *   length argument swaps s0/s1 instead.
 * - 0x41E3E4: daddu s2,v0 comes earlier and lwc1 f12 later than retail.
 *
 * Kept from earlier drafts: func_L08_003277C0 takes (int, float), retail passing 3 at 0x0041DCCC;
 * func_L08_004207D0 belongs inside the level-8/19 guard, the branch at 0x0041DC68 reaching 0x0041E474
 * past that call with a0=2 in the slot; PackHudFlag plus the interleaved flag/mode construction gives
 * the initial packing order; the incomplete sda view plus SDATA alias gives the frame counter's
 * absolute/GP mix. All declarations needed are below.
 */
#include "common.h"

extern u8 D_00189E20[];
extern int D_L08_001B2508_view[] __asm__("D_L08_001B2508") __attribute__((sda));
#define D_L08_001B2508 (D_L08_001B2508_view[0])
extern u8 * D_L08_001A904C_view[] __asm__("D_L08_001A904C") __attribute__((sda));
#define D_L08_001A904C (D_L08_001A904C_view[0])
extern float D_L08_001B3244_view[] __asm__("D_L08_001B3244") __attribute__((sda));
#define D_L08_001B3244 (D_L08_001B3244_view[0])
extern int D_L08_001B3240_view[] __asm__("D_L08_001B3240") __attribute__((sda));
#define D_L08_001B3240 (D_L08_001B3240_view[0])
extern int D_001A7340_view[] __asm__("D_001A7340") __attribute__((sda));
#define D_001A7340 (D_001A7340_view[0])
extern int D_001A7344_view[] __asm__("D_001A7344") __attribute__((sda));
#define D_001A7344 (D_001A7344_view[0])
extern int D_001A79F0_view[] __asm__("D_001A79F0") __attribute__((sda));
#define D_001A79F0 (D_001A79F0_view[0])
extern int D_00138320 NOT_SDA;
extern float D_L08_001B031C __attribute__((sda));
extern int D_L08_001B2508_gp SDATA(D_L08_001B2508);
extern int D_L08_001B3240_gp SDATA(D_L08_001B3240);
extern u8 D_L08_001B1A34 __attribute__((sda));
extern u8 D_L08_001B1A35 __attribute__((sda));
extern u8 D_L08_001B1A36 __attribute__((sda));
extern u8 D_L08_001B1A37 __attribute__((sda));
extern u8 D_L08_001B1A38 __attribute__((sda));
extern u8 D_L08_001B1A39 __attribute__((sda));
extern u8 D_L08_001B1A3A __attribute__((sda));
extern u8 D_L08_001B1A3B __attribute__((sda));
extern u8 D_L08_001B1A3C __attribute__((sda));
extern u8 D_L08_001B1A3D __attribute__((sda));
extern u8 D_L08_001B1A3E __attribute__((sda));
extern u8 D_L08_001B1A3F __attribute__((sda));
extern u8 D_L08_001B1A40 __attribute__((sda));
extern int D_L08_001B1A74 __attribute__((sda));
extern int D_L08_001B1A78 __attribute__((sda));
extern int D_L08_001B1A90 __attribute__((sda));
extern int D_L08_001B1A94 __attribute__((sda));
extern int D_L08_001B1A98 __attribute__((sda));
extern int D_L08_001B1AD4 __attribute__((sda));
extern int D_L08_001B1AD8 __attribute__((sda));
extern float D_L08_001B199C __attribute__((sda));
extern float D_L08_001B1A80 __attribute__((sda));
extern float D_L08_001B1A84 __attribute__((sda));
extern float D_L08_001B1A88 __attribute__((sda));
extern float D_L08_001B1A8C __attribute__((sda));
extern float D_L08_001B1AAC __attribute__((sda));
extern float D_L08_001B1AB0 __attribute__((sda));
extern float D_L08_001B1AB4 __attribute__((sda));
extern float D_L08_001B1AB8 __attribute__((sda));
extern float D_L08_001B1ABC __attribute__((sda));
extern float D_L08_001B1AC0 __attribute__((sda));
extern float D_L08_001B1AC4 __attribute__((sda));
extern float D_L08_001B1AC8 __attribute__((sda));
extern float D_L08_001B1ACC __attribute__((sda));
extern float D_L08_001B1AD0 __attribute__((sda));

extern void func_L08_00389B68(int, int, u64, int, u64);
extern int func_00282978(void *);
extern int func_L08_00300090(void), func_L08_003000C0(void);
extern void func_L08_00300100(void);
extern int func_00336D50(void *, int);
extern void func_00300A00(int, int, float, float, float, float, float);
extern float func_00282C48(float);
extern int func_00283D38(int, int, float);
extern void func_0027EAE8(int, int, int, int, int, void *);
extern int func_002E5DA0(int, int, void *, int);
extern float func_00283CE0(int), func_002A7798(float), func_L08_003277C0(int, float);
extern int func_00283CF0(float);
extern u8 *func_00288FB8(int);
extern void func_L08_002F5CB8(int, int, u64, u8 *, int, float);
extern int func_L08_0033CD18(u8 *, u8 *, int);
extern int func_001157AC(void *);
extern void func_0027F5B8(int, int, u64, u8 *, int);
extern float func_002ABB18(float), func_00283198(float), func_002A7790(float);
extern int func_0028E588(int, int);
extern int func_0028EA58(int, int, int, int, int, void *);
extern void func_L08_004207D0(void *);
#define FL(p,o) (*(float *)((u8 *)(p)+(o)))
#define IN(p,o) (*(int *)((u8 *)(p)+(o)))
#define SH(p,o) (*(short *)((u8 *)(p)+(o)))
#define BY(p,o) (*((u8 *)(p)+(o)))
#define G(off) D_L08_##off

static __inline__ u64 PackHudFlag(u64 flags, u8 value, int shift)
{
    return flags | ((u64)value << shift);
}

static __inline__ int HudY(float value, float adjustment)
{
    float y = value * D_L08_001B3244 + 0.5f;
    if (D_L08_001B3240 == 1) return (int)(y + adjustment);
    return (int)y;
}

static __inline__ int HudSize(int mode, float value, int adjust)
{
    float scaled = value * D_L08_001B3244 + 0.5f;
    if (mode != 0)
        return (int)scaled + adjust;
    return (int)scaled;
}

static __inline__ int HudYM(int mode, float value, float adjustment)
{
    float y = value * D_L08_001B3244 + 0.5f;
    if (mode == 1) return (int)(y + adjustment);
    return (int)y;
}

int func_L08_0041D808(void)
{
    u8 *player = D_00189E20;
    u8 *moby = *(u8 **)(player + 0x1830);
    u8 *state = *(u8 **)(moby + 0x68);
    int mask = -1;
    int colors[4];
    struct HudGradient { int a, b; } gradientBase;
    u8 buffer[64];

    if (FL(player,0x183C) < FL(player,0x1840)*0.25f) {
        if ((D_L08_001B2508 / 90) & 1) mask = 0xFF0F0FFF;
    }
    {
        u64 test, alpha;
        test = G(001B1A39);
        test = PackHudFlag(test, G(001B1A3A), 1);
        test = PackHudFlag(test, G(001B1A3B), 4);
        test = PackHudFlag(test, G(001B1A3C), 12);
        test = PackHudFlag(test, G(001B1A3D), 14);
        test = PackHudFlag(test, G(001B1A3E), 15);
        alpha = G(001B1A34);
        alpha = PackHudFlag(alpha, G(001B1A35), 2);
        test = PackHudFlag(test, G(001B1A3F), 16);
        alpha = PackHudFlag(alpha, G(001B1A36), 4);
        alpha = PackHudFlag(alpha, G(001B1A37), 6);
        func_L08_00389B68(2,0x47,test|((u64)G(001B1A40)<<17),0x42,
                         alpha|((u64)G(001B1A38)<<32));
    }
    func_00282978(state+0x8E);
    if (D_L08_001A904C) {
        int x, y, w, h, firstColor, secondColor, tex;
        float delta, fraction, scale, sx;
        int hz;
        func_L08_00300090();
        func_L08_00300100();
        tex = func_00336D50(D_L08_001A904C+0x8710,0xA8);
        sx = D_001A7340/2;
        { int off = (int)(G(001B199C)*D_L08_001B3244+0.5f);
          y = off; }
        func_00300A00(tex,mask&0x60442D00,sx,(D_001A7344/2)+y,1.0f,1.0f,0.0f);
        tex = func_00336D50(D_L08_001A904C+0x8710,0xA9);
        sx = D_001A7340/2;
        { int off = (int)(G(001B199C)*D_L08_001B3244+0.5f);
          y = off; }
        func_00300A00(tex,mask&0x55F0C070,sx,(D_001A7344/2)+y,1.0f,1.0f,0.0f);
        delta=FL(player,0x183C)-FL(state,0xA4);
        delta*=0.2f;
        scale=func_00282C48(delta);
        if (scale>1.0f) delta/=scale;
        secondColor=G(001B1AD4); firstColor=G(001B1AD8);
        FL(state,0xA4)+=delta;
        fraction=FL(state,0xA4)/FL(player,0x1840);
        gradientBase.a=secondColor; gradientBase.b=firstColor;
        *(struct HudGradient *)colors=gradientBase;
        colors[1]=func_00283D38(secondColor,firstColor,fraction);
        x=(int)G(001B1AC4);
        y=D_001A7344-HudY(G(001B1AC8),-4.0f);
        w=(int)(G(001B1AC4)+G(001B1ACC)*fraction);
        { int mode = D_L08_001B3240; h=HudYM(mode,G(001B1AC8),-4.0f);
        hz=HudSize(mode,G(001B1AD0),0); }
        h=D_001A7344-h+hz;
        func_0027EAE8(x,y,w,h,0xFFFFF1,colors);
        func_L08_003000C0();
    }
    if (D_001A79F0==8 || D_001A79F0==19) {
        if (SH(state,0x8E)) {
            int alpha;
            float fraction, scale, fade;
            u8 *text;
            if (SH(state,0x8E)==1) func_002E5DA0(3,0,moby,0x85C);
            fraction=func_00283CE0(180-SH(state,0x8E));
            fraction/=func_00283CE0(180);
            scale=G(001B1ABC)+(G(001B1AC0)-G(001B1AAC))*func_002A7798(fraction);
            fade=func_L08_003277C0(3, 1.0f-fraction)*127.0f;
            alpha=func_00283CF0(fade*0.5f)<<24;
            text=func_00288FB8(0x2F59);
            func_L08_002F5CB8(D_001A7340-G(001B1A94),D_001A7344-HudY(G(001B1A98),-6.0f),
                (alpha|0x80)&mask,text,0x11,scale*0.96f);
            alpha=func_00283CF0(fade*0.75f)<<24;
            func_L08_002F5CB8(D_001A7340-G(001B1A94),D_001A7344-HudY(G(001B1A98),-6.0f),
                (alpha|0x800000)&mask,text,0x11,scale*0.98f);
            alpha=func_00283CF0(fade)<<24;
            func_L08_002F5CB8(D_001A7340-G(001B1A94),D_001A7344-HudY(G(001B1A98),-6.0f),
                (alpha|0x808080)&mask,text,0x11,scale);
        } else if (IN(state,0x6C)) {
            int x, y;
            float fraction, scale;
            u8 *text;
            if (FL(state,0x68) > D_L08_001B031C) {
                text=func_00288FB8(0x31E0);
                func_L08_0033CD18(buffer,text,func_00283CF0(FL(state,0x68)));
                x=D_001A7340-G(001B1A90);
                y=D_001A7344-HudY(G(001B1A98),-6.0f);
                func_0027F5B8(x,y,(u32)(mask&0x80FFDE8D),buffer,func_001157AC(buffer));
            } else if (D_00138320&0x80) {
                text=func_00288FB8(0x2F57);
                func_L08_002F5CB8(D_001A7340-G(001B1A94),D_001A7344-HudY(G(001B1A98),-6.0f),
                    (u32)(mask&0x80F0F0F0),text,0xD,G(001B1AB0));
            } else {
                fraction=func_00283CE0(D_L08_001B2508_gp);
                fraction=func_002ABB18(fraction*0.1f);
                fraction=func_00283198(fraction);
                scale=G(001B1AB4)+G(001B1AB8)*fraction;
                text=func_00288FB8(0x2F58);
                func_L08_002F5CB8(D_001A7340-G(001B1A94),D_001A7344-HudY(G(001B1A98),-6.0f),
                    (u32)(mask&0x80F0F0F0),text,0x11,scale);
            }
        }
        if (BY(state,0x8A)) {
            int alpha, x, y, w, h, sprite;
            float fraction, width, height, dx, dy, rise;
            { float num=func_00283CE0(SH(state,0x88));
            fraction=num/func_00283CE0(G(001B1A78)); }
            width=func_002A7790(fraction)*32.0f;
            height=func_002A7790(fraction)*24.0f;
            dx=G(001B1A80)*func_002A7798(fraction);
            dy=G(001B1A84)*func_002A7798(fraction);
            alpha=func_00283CF0(fraction*128.0f)<<24;
            rise=16.0f-width*0.5f;
            if (D_L08_001A904C) {
                int a;
                func_L08_00300090(); func_L08_00300100();
                a=func_00283CF0(func_00283CE0(96)*fraction)<<24;
                func_00300A00(func_00336D50(D_L08_001A904C+0x8710,0xAA),(a|0x442D00)&mask,
                    (float)(D_001A7340/2+32)-dx,D_001A7344/2+G(001B1A74),1,1,0);
                a=func_00283CF0(func_00283CE0(85)*fraction)<<24;
                func_00300A00(func_00336D50(D_L08_001A904C+0x8710,0xAB),(a|0xF0C070)&mask,
                    (float)(D_001A7340/2+32)-dx,D_001A7344/2+G(001B1A74),1,1,0);
                func_L08_003000C0();
            }
            if (BY(state,0x8A)<3) {
                { int c=alpha|0xF0F0B0; colors[0]=c; colors[1]=c; colors[2]=c; colors[3]=c; }
                sprite=func_0028E588(0xEAA2,3);
                x=func_00283CF0((float)D_001A7340-G(001B1A8C)-dy);
                { int off = (int)((float)func_00283CF0(G(001B1A88)+(float)G(001B1A74)+(float)SH(state,0x8C)+rise)*D_L08_001B3244+0.5f);
          y = off; }
                w=func_00283CF0(height); h=func_00283CF0(height);
                func_0028EA58(sprite,x,y,w,h,colors);
            }
        }
        func_L08_004207D0(moby);
    }
    func_L08_00389B68(2,0x47,0x5340B,0x42,0x8000000044ULL);
    IN(state,0x6C)=0; FL(state,0x68)=1000000.0f;
    return 1;
}
