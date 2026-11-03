/*
 * Claude Opus 5.5 (xhigh effort), task v1843, USA v1.01, 31 October 2026.
 * Best check.py: 3304 bytes / 3308 retail, 0 of 1 places match.
 * Profile: -O2 -G8 -ffunction-sections -g, in a dedicated -g8.c unit
 * (src/levels/19_grelbin/L19_00412140-g8.c plus its config/cflags.txt line).
 * All required declarations follow below. No match or linked build claimed.
 *
 * DrawGrelbinStatusHud (existing include/names.h name). Its entry is 00412148.
 *
 * Recovered over v1555's 3284-byte draft; these rows now agree up to register names:
 * - hud_coord/hud_size are the shape of scaled_screen_coord/scaled_screen_size in
 *   src/game/002D3390.c. A real inline (not a statement expression) makes H load
 *   after the coordinate. hud_bar_bottom's mode local gives retail's t0 and the
 *   f5/t1 PRE copies; its hud_size test on live mode vanishes at jump2.
 * - func_L08_004207D0(obj) belongs inside the D_001A79F0 == 8/19 test (that gives
 *   the branch delay slot `addiu a0,2`).
 * - One `str` for all status strings gives retail's s1 (even where no call is crossed).
 * - D_00138320 is section(".data") (lui in delay slot); func_00282978 returns int
 *   (load of D_L19_001A904C in v1); colors[0..3] are separate statements in order;
 *   delta is staged; palette words load before F(s,0xA4) is stored.
 *
 * Blocker: both texture labels (0xA8, 0xA9). Retail has a block boundary between
 * `mfc1 a3` (y) and the H load, leaving no instruction: 1.0f/0.0f load after it,
 * str lives in a2 and y in a3 (both global pseudos: W takes v0, a0 stays unused).
 * Yet 0x8710, 0.5f and the int 1 stay shared across it, so CSE's path passes it:
 * two-return arms (which do survive to jump2) are out, they lose the sharing (they
 * give 3304 bytes with the right boundary but reload every constant). A then-only arm
 * fits, but every form tried folds before sched1: `r += adjust` with adjust 0,
 * `r = (int)scaled + adjust`, an arm setting a variable overwritten later. Int 1 in s1
 * is set before the boundary. Its s1 ahead of 0x8710 suggests (inferred, not measured)
 * about 4 refs, a compare in each label plus the bar, but no D_L19_001B3280 load stays
 * behind, so the compared value is unknown. `int one = 1` here is a stand-in for that.
 * The hero s0 / one s1 / 0x8710 s2 / state s3 / text s4 order, and delta in f20 and
 * 1.0f in f21, should follow once this boundary and those refs exist.
 *
 * Measured, 0/1: `do { F1; one = 1; F2; str; x; y; } while (0)` (forbidden wrapper,
 * never a landing form) reproduces retail's constant-load positions, 1.0f/0.0f after
 * the barrier and the sharing, probably through the loop notes; but str stays tied to
 * v0 and W goes to a0, so it is not retail's block boundary. 1-iteration for loops are not
 * removed here (3344-3348 bytes). hud_coord(0, ...) folds with no 1 left behind.
 *
 * Also remaining: GS OR scheduling (retail runs some of blend's `or t0` rows ahead of
 * test's rows where this draft runs them after; blend-first or a direct expression is
 * worse), and
 * `sw v0,0x10(sp)` is scheduled before the ratio div.s, retail after it (swapping the
 * palette stores flips c0/c1 registers; storing around ratio reloads the state).
 */
#include "common.h"

extern unsigned char D_00189E20[];
extern int D_001A7340, D_001A7344;
extern int D_00138320 __attribute__((section(".data")));
extern int D_001A79F0;
extern int D_L19_001B2508;
extern unsigned char *D_L19_001A904C;
extern int D_L19_001B3280;
extern float D_L19_001B3284;
extern unsigned char D_L19_001B1A54 __attribute__((sda));
extern unsigned char D_L19_001B1A55 __attribute__((sda));
extern unsigned char D_L19_001B1A56 __attribute__((sda));
extern unsigned char D_L19_001B1A57 __attribute__((sda));
extern unsigned char D_L19_001B1A58 __attribute__((sda));
extern unsigned char D_L19_001B1A59 __attribute__((sda));
extern unsigned char D_L19_001B1A5A __attribute__((sda));
extern unsigned char D_L19_001B1A5B __attribute__((sda));
extern unsigned char D_L19_001B1A5C __attribute__((sda));
extern unsigned char D_L19_001B1A5D __attribute__((sda));
extern unsigned char D_L19_001B1A5E __attribute__((sda));
extern unsigned char D_L19_001B1A5F __attribute__((sda));
extern unsigned char D_L19_001B1A60 __attribute__((sda));
extern int D_L19_001B1A94 __attribute__((sda));
extern int D_L19_001B1A98 __attribute__((sda));
extern float D_L19_001B1AA0 __attribute__((sda));
extern float D_L19_001B1AA4 __attribute__((sda));
extern float D_L19_001B1AA8 __attribute__((sda));
extern float D_L19_001B1AAC __attribute__((sda));
extern int D_L19_001B1AB0 __attribute__((sda));
extern int D_L19_001B1AB4 __attribute__((sda));
extern int D_L19_001B1AB8 __attribute__((sda));
extern float D_L19_001B1ACC __attribute__((sda));
extern float D_L19_001B1AD0 __attribute__((sda));
extern float D_L19_001B1AD4 __attribute__((sda));
extern float D_L19_001B1AD8 __attribute__((sda));
extern float D_L19_001B1ADC __attribute__((sda));
extern float D_L19_001B1AE0 __attribute__((sda));
extern float D_L19_001B1AE4 __attribute__((sda));
extern float D_L19_001B1AE8 __attribute__((sda));
extern float D_L19_001B1AEC __attribute__((sda));
extern float D_L19_001B1AF0 __attribute__((sda));
extern unsigned int D_L19_001B1AF4 __attribute__((sda));
extern unsigned int D_L19_001B1AF8 __attribute__((sda));
extern float D_L19_001B19BC __attribute__((sda));
extern float D_L19_001B0120 __attribute__((sda));
extern void func_L08_00389B68(int,int,u64,int,u64);
extern int func_00282978(void *);
extern void func_L08_00300090(void);
extern void func_L08_00300100(void);
extern void func_L08_003000C0(void);
extern char *func_00336D50(void *,int);
extern void func_00300A00(char *,int,float,float,float,float,float);
extern float func_00282C48(float);
extern unsigned int func_00283D38(unsigned int,unsigned int,float);
extern void func_0027EAE8(int,int,int,int,int,void *);
extern void func_002E5DA0(int,int,void *,int);
extern float func_00283CE0(int);
extern int func_00283CF0(float);
extern float func_002A7798(float);
extern float func_002A7790(float);
extern float func_L08_003277C0(int,float);
extern unsigned char *func_00288FB8(int);
extern void func_L08_002F5CB8(int,int,u64,void *,int,float);
extern void func_L08_0033CD18(void *,void *,int);
extern int func_001157AC(void *);
extern void func_0027F5B8(int,int,u64,void *,int);
extern float func_002ABB18(float);
extern float func_00283198(float);
extern int func_0028E588(int,int);
extern int func_0028EA58(int,int,int,int,int,void *);
extern void func_L08_004207D0(void *);
#define F(p,o) (*(float *)((p)+(o)))
#define I(p,o) (*(int *)((p)+(o)))
#define H(p,o) (*(short *)((p)+(o)))
static __inline__ int hud_coord(int mode, int interlaced, float value, float offset)
{
    float scaled = value * D_L19_001B3284 + 0.5f;
    if (mode == interlaced)
        return (int)(scaled + offset);
    return (int)scaled;
}

static __inline__ int hud_size(int mode, float value, int adjust)
{
    if (mode != 0)
        return (int)(value * D_L19_001B3284 + 0.5f) + adjust;
    return (int)(value * D_L19_001B3284 + 0.5f);
}

static __inline__ int hud_bar_bottom(void)
{
    int mode = D_L19_001B3280;
    int y = hud_coord(mode, 1, D_L19_001B1AE8, -4.0f);
    return D_001A7344 - y + hud_size(mode, D_L19_001B1AF0, 0);
}

int func_L19_00412140(void)
{
    unsigned int colors[4];
    struct Palette { unsigned int a,b; } palette;
    char text[64];
    unsigned char *hero = D_00189E20;
    unsigned char *obj = *(unsigned char **)(hero + 0x1830);
    unsigned char *s = *(unsigned char **)(obj + 0x68);
    int mask = -1;

    if (F(hero,0x183C) < F(hero,0x1840) * 0.25f)
        if ((D_L19_001B2508 / 90) & 1) mask = 0xFF0F0FFF;
    {
        u64 test = (u64)D_L19_001B1A59;
        test |= (u64)D_L19_001B1A5A << 1;
        test |= (u64)D_L19_001B1A5B << 4;
        test |= (u64)D_L19_001B1A5C << 12;
        test |= (u64)D_L19_001B1A5D << 14;
        test |= (u64)D_L19_001B1A5E << 15;
        test |= (u64)D_L19_001B1A5F << 16;
        test |= (u64)D_L19_001B1A60 << 17;
        { u64 blend = (u64)D_L19_001B1A54;
        blend |= (u64)D_L19_001B1A55 << 2;
        blend |= (u64)D_L19_001B1A56 << 4;
        blend |= (u64)D_L19_001B1A57 << 6;
        blend |= (u64)D_L19_001B1A58 << 32;
        func_L08_00389B68(2,0x47,test,0x42,blend); }
    }
    func_00282978(s + 0x8E);
    if (D_L19_001A904C) {
        float delta, ratio;
        unsigned char *str;
        int y;
        float x;
        unsigned int c0, c1;
        int one;
        func_L08_00300090();
        one = 1;
        func_L08_00300100();
        str = (unsigned char *)func_00336D50(D_L19_001A904C + 0x8710,0xA8);
        x = (float)(D_001A7340 / 2);
        y = (int)(D_L19_001B19BC * D_L19_001B3284 + 0.5f);
        func_00300A00((char *)str, mask & 0x60442D00, x, (float)(D_001A7344 / 2 + y),1.0f,1.0f,0.0f);
        str = (unsigned char *)func_00336D50(D_L19_001A904C + 0x8710,0xA9);
        x = (float)(D_001A7340 / 2);
        y = (int)(D_L19_001B19BC * D_L19_001B3284 + 0.5f);
        func_00300A00((char *)str, mask & 0x55F0C070, x, (float)(D_001A7344 / 2 + y),1.0f,1.0f,0.0f);
        delta = F(hero,0x183C) - F(s,0xA4);
        delta *= 0.2f;
        {
            float magnitude = func_00282C48(delta);
            if (magnitude > 1.0f) delta /= magnitude;
        }
        c0 = D_L19_001B1AF4;
        c1 = D_L19_001B1AF8;
        F(s,0xA4) += delta;
        ratio = F(s,0xA4) / F(hero,0x1840);
        palette.a = c0;
        palette.b = c1;
        *(struct Palette *)colors = palette;
        colors[1] = func_00283D38(c0,c1,ratio);
        func_0027EAE8((int)D_L19_001B1AE4,
            D_001A7344 - hud_coord(D_L19_001B3280, one, D_L19_001B1AE8, -4.0f),
            (int)(D_L19_001B1AE4 + D_L19_001B1AEC * ratio),
            hud_bar_bottom(),
            0xFFFFF1, colors);
        func_L08_003000C0();
    }
    if (D_001A79F0 == 8 || D_001A79F0 == 19) {
        unsigned char *str;
        if (H(s,0x8E)) {
            float ratio, scale, alpha;
            int color;
            if (H(s,0x8E) == 1) func_002E5DA0(3,0,obj,0x85C);
            ratio = func_00283CE0(180-H(s,0x8E)) / func_00283CE0(180);
            scale = D_L19_001B1ADC + (D_L19_001B1AE0-D_L19_001B1ACC)*func_002A7798(ratio);
            alpha = func_L08_003277C0(3,1.0f-ratio)*127.0f;
            color = func_00283CF0(alpha*0.5f) << 24;
            str = func_00288FB8(0x2F59);
            func_L08_002F5CB8(D_001A7340-D_L19_001B1AB4,D_001A7344-hud_coord(D_L19_001B3280, 1, (float)D_L19_001B1AB8, -6.0f),
                (color|0x80)&mask,str,0x11,scale*0.96f);
            color = func_00283CF0(alpha*0.75f) << 24;
            func_L08_002F5CB8(D_001A7340-D_L19_001B1AB4,D_001A7344-hud_coord(D_L19_001B3280, 1, (float)D_L19_001B1AB8, -6.0f),
                (color|0x800000)&mask,str,0x11,scale*0.98f);
            color = func_00283CF0(alpha) << 24;
            func_L08_002F5CB8(D_001A7340-D_L19_001B1AB4,D_001A7344-hud_coord(D_L19_001B3280, 1, (float)D_L19_001B1AB8, -6.0f),
                (color|0x808080)&mask,str,0x11,scale);
        } else if (I(s,0x6C)) {
            if (F(s,0x68) > D_L19_001B0120) {
                int x, y, color;
                str = func_00288FB8(0x31E0);
                func_L08_0033CD18(text,str,func_00283CF0(F(s,0x68)));
                x = D_001A7340-D_L19_001B1AB0;
                y = D_001A7344-hud_coord(D_L19_001B3280, 1, (float)D_L19_001B1AB8, -6.0f);
                color = mask & 0x80FFDE8D;
                func_0027F5B8(x,y,(unsigned int)color,text,func_001157AC(text));
            } else if (D_00138320 & 0x80) {
                str = func_00288FB8(0x2F57);
                func_L08_002F5CB8(D_001A7340-D_L19_001B1AB4,D_001A7344-hud_coord(D_L19_001B3280, 1, (float)D_L19_001B1AB8, -6.0f),
                    (unsigned int)(mask&0x80F0F0F0),str,0xD,D_L19_001B1AD0);
            } else {
                float scale;
                scale = func_002ABB18(func_00283CE0(D_L19_001B2508)*0.1f);
                scale = func_00283198(scale);
                scale = D_L19_001B1AD4 + D_L19_001B1AD8*scale;
                str = func_00288FB8(0x2F58);
                func_L08_002F5CB8(D_001A7340-D_L19_001B1AB4,D_001A7344-hud_coord(D_L19_001B3280, 1, (float)D_L19_001B1AB8, -6.0f),
                    (unsigned int)(mask&0x80F0F0F0),str,0x11,scale);
            }
        }
        if (s[0x8A]) {
            float ratio, width, height, dx, dy, top;
            int color, tex, x, y, a, b;
            ratio = func_00283CE0(H(s,0x88))/func_00283CE0(D_L19_001B1A98);
            width = func_002A7790(ratio)*32.0f;
            height = func_002A7790(ratio)*24.0f;
            dx = D_L19_001B1AA0*func_002A7798(ratio);
            dy = D_L19_001B1AA4*func_002A7798(ratio);
            color = func_00283CF0(ratio*128.0f)<<24;
            top = 16.0f-width*0.5f;
            if (D_L19_001A904C) {
                func_L08_00300090();
                func_L08_00300100();
                a = func_00283CF0(func_00283CE0(96)*ratio)<<24;
                str = (unsigned char *)func_00336D50(D_L19_001A904C+0x8710,0xAA);
                func_00300A00((char *)str,
                    (a|0x442D00)&mask,
                    (float)(D_001A7340/2+32)-dx,(float)(D_001A7344/2+D_L19_001B1A94),1.0f,1.0f,0.0f);
                a = func_00283CF0(func_00283CE0(85)*ratio)<<24;
                str = (unsigned char *)func_00336D50(D_L19_001A904C+0x8710,0xAB);
                func_00300A00((char *)str,
                    (a|0xF0C070)&mask,
                    (float)(D_001A7340/2+32)-dx,(float)(D_001A7344/2+D_L19_001B1A94),1.0f,1.0f,0.0f);
                func_L08_003000C0();
            }
            if (s[0x8A] < 3) {
                int c=color|0xF0F0B0;
                colors[0]=c;
                colors[1]=c;
                colors[2]=c;
                colors[3]=c;
                tex=func_0028E588(0xEAA2,3);
                x=func_00283CF0((float)D_001A7340-D_L19_001B1AAC-dy);
                y=func_00283CF0(D_L19_001B1AA8+(float)D_L19_001B1A94+(float)H(s,0x8C)+top);
                y=(int)((float)y*D_L19_001B3284+0.5f);
                a=func_00283CF0(height);
                b=func_00283CF0(height);
                func_0028EA58(tex,x,y,a,b,colors);
            }
        }
        func_L08_004207D0(obj);
    }
    func_L08_00389B68(2,0x47,0x5340B,0x42,0x8000000044ULL);
    F(s,0x68)=1000000.0f;
    I(s,0x6C)=0;
    return 1;
}
