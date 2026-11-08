/* 8 November 2026, HUD-recipe rewrite (Claude Opus 5.5), USA v1.01, re-measured on master's
 * compiler: the 7 November body was 280 masked differences at 3360/3388 bytes; the body
 * below is 84 at 3384/3388 (same cc1 diff harness, relocations masked). Steps that paid:
 * - hud_coord (dead-test helper, owner ruling 8 November 2026) on every ROW and the name row:
 *   280 -> 211; label_y(str_) on every TEXT row: -> 150.
 * - time / 60 % 60 written in each sprintf call and the < 10 test (no minutes local): retail's
 *   three dead li 60 come back, 3356 -> 3380 bytes; per-arm times pointer: -> 126 / 90.
 * - per-draw string locals (label in each flags arm, fmt, str in both reward branches): -> 92.
 * - CENTER's handle: buffer is a constant address, so label_y(buffer) folds its tests and
 *   loses the block boundary (li.s 286.0 hoisted above the 0x2f72 call). Using sprintf's
 *   return as the handle puts 286.0 after the mfc1 as retail: -> 84 (it leaves one dead
 *   daddu $a0,$v0; a global handle gives 3388 bytes but an extra lw).
 * - Title select: lang loaded in both arms, then {first; second} / {second; first} order
 *   gives retail's beqz delay-slot lw and $a0/$v1; one 2-insn order difference left.
 * Still open: the first icon's 1.0 (retail: direct $f14, new 1.0 in $f20 at the second icon;
 * here one $f20 pseudo for both, width/rot locals no help); the 283 sprites' mfc1 $a1 vs $v1
 * and input/colour $s1/$s2 swap; table base $s2 / flags pointer $s3 / count $s2 in retail vs
 * $s0/$s0/$s3 here (cascades into the name row, count, reward); time vs 60 ($s2/$s1 swapped);
 * the time lookup's sll is cross-jumped into the join (retail keeps one sll per arm).
 * Profile: own unit src/levels/shared/L04_0040AD28-g8.c, -O2 -G8 -ffunction-sections -g. */
/* 7 November 2026, label_y sweep: the two icon ys use label_y(icon, 200.0f, ...) and CENTER uses label_y(str_, ...): 319 -> 281 differences, 3360/3388 bytes (TEXT and ROW with label_y: no gain). That body (since replaced by the 8 November one above) was the retained C with that change (label_y is
 * the accepted HUD label idiom, definition as in src/levels/15_gorn/L15_00431590-g8.c). Counts are
 * masked aligned instruction differences from a cc1 -S diff harness, not check.py rows. */
/* opus-1 (Claude Opus 5.5, xhigh) retained attempt, 31 October 2026, USA v1.01.
 * Profile: -O2 -G8 -ffunction-sections -g, in a separate -g8.c unit.
 * check.py: 3356/3388 bytes, 0 of 2 places (Barlow and Joba). No linked build.
 * Kept over the sol-high draft (3368/3388) because more of it is right: with
 * relocations masked, 616 of 847 retail instructions align in order against
 * 547, and the code through 0x40AE00 is exact.
 *
 * Recovered here: per-draw scoped text locals (they keep the opening register
 * map), an inline helper so the coordinate constant loads before the scale, a
 * plain absolute scalar D_001A79F0 next to the $gp alias D_001A79F0_1, the format
 * pointer loaded before the localization call, column locals before the time
 * text, and a two-arm time lookup.
 *
 * What still differs: retail behaves as if a basic block ends right after every
 * coordinate's (int) conversion, yet no branch remains. Evidence: sprite Y uses
 * mfc1 $v1 with the D_001A7B90 load only after it; li.s 286.0 sits just after the
 * row's mfc1; the table high half first appears in the fourth ROW; shift's 5 and
 * the flags pointer appear at the 110 row. YS() marks the sprite coordinates.
 * Without that boundary those values hoist to the block start, and the table
 * lifetimes then rename most saved registers from 0x40B0C8 to the end.
 *
 * Measured, none landable:
 * - Single arm on the four sprite Ys, placeholder test and dead store:
 *     float y = v * S + 0.5f; int r = (int)y; if (center) y = 0.0f; return r;
 *   638 of 847 align. It restores the $f24/$f22/$s1 constants, $v1/$v0 and the
 *   empty delay slot, because cse skips the arm. But flow deletes the arm, so the
 *   test is gone by sched2 (the .sched dump has li.s $f15 in place, the sched2
 *   timeline has merged the block and fills a load stall with it).
 * - Two arms: if (center != 0) return (int)y + 0; return (int)y;
 *   Retail's order of conversion, D_001A7B90 load, float and li.s in the first
 *   sprite, and the value is written straight to its target, because the arms
 *   merge only after sched2. But the join label ends the cse table and every
 *   constant reloads: 3508 bytes with the helper on all coordinates.
 * - do { } while (0) forms (forbidden): 3360 and 3452 bytes, not exact either.
 * - A volatile asm conversion (forbidden): worse, it fills the delay slot retail
 *   leaves empty, so the boundary is a real branch and not a barrier.
 * - Testing center at the text rows moves it to $s3 (retail $s5): it is not the
 *   tested value. -frac2-keep-block-order and -frac2-gcse-unsplit-edges: no help.
 * Needed next: a real single-arm test on an already-live value whose arm survives
 * until after sched2 and then vanishes. No such wording was found.
 *
 * Also open: the first sprite loads 1.0 directly into $f14 while its 0.0 is a
 * pseudo shared with the second sprite ($f23), and retail's second sprite starts a
 * new 1.0 in $f20. Title selection is a tie: retail has movn $a0(second), $v1(first)
 * with the D_001A79F0_1 load in the branch delay slot; first == 11 / second != 11
 * overwrites and both ternaries give movz with the registers swapped. Data bindings
 * remain unqualified: no equal-size relocation check or linked build was reached.
 */
#include "common.h"
extern int D_001A7340, D_001A7B90;
extern int D_001A79F0;
extern int D_001A79F0_1 __attribute__((sda));
extern unsigned char D_00138180[];
extern unsigned char D_001A7A0A;
extern int D_L04_001B0904 __attribute__((sda));
extern unsigned char *D_L04_001B0914 __attribute__((sda));
extern unsigned char *D_L04_001A904C;
extern float D_L04_001B2D44;
extern int D_L04_001B2008;
extern float D_L04_001BDB80[];
extern int D_001A7368[], D_001A737C[];
typedef struct { int name, flags, rewards[3]; unsigned char reserved[44]; } RaceChallenge;
extern RaceChallenge D_L04_002C63C0[];
extern char D_L04_001B0940[], D_L04_001B0950[], D_L04_001B0958[], D_L04_001B0968[];
extern float func_00283198(float), func_00283180(float);
extern void func_0027AB40(void);
extern void *func_00336D50(void *, int);
extern void func_00300A00(void *, unsigned int, float, float, float, float, float);
extern unsigned int func_00283D38(unsigned int, unsigned int, float);
extern char *func_00288FB8(int);
extern int func_00115DA8(char *, const char *, ...);
extern int func_001157AC(const char *);
extern int func_0027FAA8(int, int, unsigned long, char *, int);
extern int func_0027FBD8(int, int, unsigned long, char *, int);
extern void func_0027F5B8(int, int, unsigned long, char *, int);
extern int func_L04_0040A1D0(int);
extern void func_002FC560(int, unsigned long);
extern int D_L04_001B2D40;
static __inline__ int label_y(void *handle, float value, float scale, float half, int active)
{
    int mode = D_L04_001B2D40;
    float scaled = value * scale + half;
    int result = (int)scaled;
    void *copy;

    if (mode == active)
        scaled = scale;
    if (handle != 0)
        scaled = scale;
    copy = handle;
    if (copy != 0)
        scaled = half;
    return result;
}

static __inline__ int hud_coord(float value, float scale, float half)
{
    int mode = D_L04_001B2D40;
    float scaled = value * scale + half;
    int result = (int)scaled;
    int copy;

    if (mode == 1)
        scaled = scale;
    if (result != 0)
        scaled = scale;
    copy = result;
    if (copy != 0)
        scaled = half;
    return result;
}
#define Y(v) hud_coord((float)(v), D_L04_001B2D44, 0.5f)
#define YS(v) Y(v)
#define TEXT(x,y,s) { char *str_ = (s); int row_ = label_y(str_, (float)(y), D_L04_001B2D44, 0.5f, 1); int len_ = func_001157AC(str_); func_0027FAA8(x,row_,0x80f0f0f0UL,str_,len_); }
#define CENTER(y,s) { char *str_ = (s); int row_ = label_y(str_, (float)(y), D_L04_001B2D44, 0.5f, 1); int len_ = func_001157AC(str_); func_0027FBD8(center,row_,0x80f0f0f0UL,str_,len_); }
#define ROW(x,id) { int row_ = Y(286); char *str_ = func_00288FB8(id); func_0027F5B8(x,row_,0x80f0f0f0UL,str_,-1); }
int func_L04_0040AD28(void)
{
    char buffer[128];
    unsigned char *m = D_L04_001B0914;
    unsigned char *p = *(unsigned char **)(m + 0x68);
    int center = (int)((float)D_001A7340 * 0.5f);
    float angle = 0.56217057f, tangent;
    unsigned int color, tint;
    unsigned char *input;
    int count, shift, reward, time, minutes, x, row;
    void *icon;
    float scale, centerf, py;
    tangent = func_00283198(angle);
    tangent /= func_00283180(angle);
    centerf = (float)center;
    D_L04_001BDB80[44] = tangent;
    func_0027AB40();
    icon = func_00336D50(D_L04_001A904C + 0x8710,0x45);
    py = (float)label_y(icon, 200.0f, D_L04_001B2D44, 0.5f, 1);
    scale = 0.92f;
    if (D_001A7B90) scale = 0.9f;
    func_00300A00(icon,0x60442d00,centerf,py,1.0f,scale,(float)0);
    icon = func_00336D50(D_L04_001A904C + 0x8710,0x44);
    py = (float)label_y(icon, 200.0f, D_L04_001B2D44, 0.5f, 1);
    scale = 0.92f;
    if (D_001A7B90) scale = 0.9f;
    func_00300A00(icon,0x55f0c070,centerf,py,1.0f,scale,0.0f);
    x = D_L04_001B2008 % 50;
    color = func_00283D38(0x80ffde8d,0x60442d00, x >= 25 ? 1.0f-(float)(x-25)*0.04f : (float)x*0.04f);
    input = D_00138180;
    tint = 0x80f0f0f0;
    if (!(*(int *)(input + 0x1a0) & 0x2000)) tint = color;
    icon = func_00336D50(D_L04_001A904C+0x8710,0x4a);
    func_00300A00(icon,tint,259.0f,(float)label_y(icon, 283.0f, D_L04_001B2D44, 0.5f, 1),1.0f,1.0f,0.0f);
    tint = 0x80f0f0f0;
    if (!(*(int *)(input + 0x1a0) & 0x8000)) tint = color;
    icon = func_00336D50(D_L04_001A904C+0x8710,0x4b);
    func_00300A00(icon,tint,251.0f,(float)label_y(icon, 283.0f, D_L04_001B2D44, 0.5f, 1),1.0f,1.0f,0.0f);
    if (m[0x20] != 3) {
        float projection_angle = *(float *)(p+0x28c)*0.008726647f;
        float sine = func_00283198(projection_angle);
        D_L04_001BDB80[44] = sine / func_00283180(projection_angle);
        func_0027AB40();
    }
    { int n_ = func_00115DA8(buffer,func_00288FB8(0x2f72),D_L04_001B0904+1); int row_ = label_y((void *)n_, 60.0f, D_L04_001B2D44, 0.5f, 1); int len_ = func_001157AC(buffer); func_0027FBD8(center,row_,0x80f0f0f0UL,buffer,len_); }
    ROW(119,0x2f40);
    ROW(356,0x2f41);
    ROW(181,0x2f3f);
    ROW(279,0x2f42);
    { char *str_ = func_00288FB8(D_L04_002C63C0[D_L04_001B0904].name); int row_ = Y(110); int len_ = func_001157AC(str_); func_0027FAA8(center,row_,0x80f0f0f0UL,str_,len_); }
    shift = D_001A79F0 == 11 ? 10 : 5;
    count = func_L04_0040A1D0(D_L04_001B0904);
    if ((D_L04_002C63C0[D_L04_001B0904].flags & 0x10000000) ||
        (D_L04_001B0904 > 0 && func_L04_0040A1D0(D_L04_001B0904-1)>0)) {
        int first, second, lang;
        if (D_L04_002C63C0[D_L04_001B0904].flags & 4) { lang = D_001A79F0_1; first=0x2f7a; second=0x2f9a; }
        else { lang = D_001A79F0_1; second=0x2f99; first=0x2f79; }
        if (lang != 11) second = first;
        TEXT(center,150-shift,func_00288FB8(second));
        { char *label; if (D_L04_002C63C0[D_L04_001B0904].flags&1) label=func_00288FB8(0x2f7c);
        else label=func_00288FB8(0x2f7b);
        TEXT(center,170-shift,label); }
        if (D_001A79F0==11) {
            { char *label; if (D_L04_002C63C0[D_L04_001B0904].flags&16) label=func_00288FB8(0x2f9b);
            else label=func_00288FB8(0x2f9c);
            TEXT(center,190-shift,label); }
            if(D_L04_002C63C0[D_L04_001B0904].flags&2) TEXT(center,210-shift,func_00288FB8(0x2fc5))
        } else if(D_L04_002C63C0[D_L04_001B0904].flags&2) TEXT(center,190-shift,func_00288FB8(0x2fc5))
        if(count>=3) count=2;
        if(D_L04_002C63C0[D_L04_001B0904].rewards[count]) {
            char *fmt = D_L04_001B0940;
            char *str = func_00288FB8(0x2f7d);
            { unsigned char boost = D_001A7A0A;
            reward = D_L04_002C63C0[D_L04_001B0904].rewards[count];
            if(boost) reward*=10; }
            func_00115DA8(buffer,fmt,str,reward,func_00288FB8(0x2f5e));
        } else { char *fmt = D_L04_001B0950; func_00115DA8(buffer,fmt,func_00288FB8(0x2f7d)); }
        TEXT(center,shift+210,buffer);
        { int *times; if (D_001A79F0==4) { times = D_001A7368; time = times[D_L04_001B0904]; } else { times = D_001A737C; time = times[D_L04_001B0904]; } }
        x = 0;
        if(time) {
            x = 110;
            if (time / 60 % 60 < 10) func_00115DA8(buffer,D_L04_001B0958,func_00288FB8(0x31c8),time/3600%60,time/60%60,time/6%10);
            else func_00115DA8(buffer,D_L04_001B0968,func_00288FB8(0x31c8),time/3600%60,time/60%60,time/6%10);
            { int col = center+46; TEXT(col,shift+230,buffer); }
        }
            { int col = center-x;
            char *fmt = func_00288FB8(0x2f7e);
            func_00115DA8(buffer,fmt,func_L04_0040A1D0(D_L04_001B0904));
            TEXT(col,shift+230,buffer); }
    } else {
            char *fmt;
            CENTER(150,func_00288FB8(0x2f73));
            fmt = D_L04_001B0940;
            { char *str = func_00288FB8(0x2f7d);
            reward = D_L04_002C63C0[D_L04_001B0904].rewards[count];
            if(D_001A7A0A) reward*=10;
            func_00115DA8(buffer,fmt,str,reward,func_00288FB8(0x2f5e)); }
            TEXT(center,shift+210,buffer);
    }
    func_002FC560(71,0x5360b);
    return 1;
}
