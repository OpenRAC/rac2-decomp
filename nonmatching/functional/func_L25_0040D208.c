/* functional: medium. Near-miss draft, not byte-compared in the latest sweep: paths the captured calls never take are unproven. */
/* Claude Opus 5.5 xhigh tier (opus-1), task v1897, 31 October 2026.
 * Best check.py, USA v1.01: 2752 bytes versus 2760 retail, 0 of 1 places match.
 * No linked build and no PAL/us2 check (not a match).
 * Compile as an isolated -g8.c unit: -O2 -G8 -ffunction-sections. Declarations follow.
 *
 * Closeness: on a private sequence alignment with relocated halves masked (not a check.py
 * result), 107 rows differ and 0040D368..0040DB44 has no difference left. What remains is the
 * two text blocks (0040D280..0040D360) and the last three sprites (0040DB44..0040DC74). The
 * 8 missing bytes are retail's two `daddu a0,vN` copies of x in the text blocks.
 *
 * Behaviour repaired over the sol-high draft, each measured against retail:
 * - Case 6 blends to 0x8000ff00, not 0x80000000. Case 12's first arm also draws CE4 in green,
 *   and case 14's first arm also draws CE4 in green. jump2 shares those tails, which explains
 *   every "switch-tail" difference in the old notes.
 * - Health above 0.3 stores 1 in state+0x28, through the same `sw` as the toggle.
 * - 0x1B0D20 "%s: %d" and 0x1B0D58 "%d/%d" are string literals. 0x1B0D28/38/48 are local
 *   initializers in a nested block: four RGBA corners, hence ldl/ldr. The rodata order agrees.
 * - sprintf's format and both table reads are nested in its call, so the format lands in s0
 *   first and the count pointer survives the second lookup.
 * - The first sprites' Y uses the scaled_screen_coord shape from src/game/002D3390.c. This also
 *   fixed the mtc1 f21 order and the place of `lui s1` / `daddu s4,s1` at 0040D46C..0040D4B4.
 *
 * Investigation: 21 check.py runs (about 15 wordings) and 3 tools/regalloc.py runs.
 *
 * Remaining blocker, the same as func_L22_003A5018 and func_L05_0041DF58: a block boundary
 * right after each rounding, with no instruction left and no tested value loaded.
 * - Evidence: x stays out of a0, fmt is `lui v1; addiu s1,v1` (not tied, so it spans a block),
 *   the last sprites have `lwc1 f1; add.s f12,f1,f20` and S in f2, and no argument setup rises
 *   into the rounding's free slots. Yet 0.5 stays in f20 and 1 in s2 across the text blocks.
 * - Diagnostic only, a placeholder test, not landable: after the float chain,
 *   `if (state != 0) { result = 0; color = 1; }` (`result` and `color` are written again before
 *   they are read). Unlike a one-statement arm it reaches allocation: tools/regalloc.py dumps show
 *   its branch through greg and gone by sched2. Inferred, not traced: the arm dies in flow, and
 *   a one-statement arm is lost earlier to jump's if-conversion.
 *   It gave retail's fmt registers and last-sprite FP registers (f1, f2, f21=0.8, f22=0.0),
 *   with no branch left. It did not give the barrier: arguments still fill the free slots, and
 *   x still lands in a0 (`addiu a0,v1,-0x3C`), with the test on tx or on state alike.
 *   110 aligned rows, so scheduling keeps it behind this draft.
 * - Inferred: only cross-jumping survives sched2, because an empty arm is gone by then and
 *   func_L22_003A5018's notes place cross-jumping after sched2. But cross-jumping needs a real
 *   join, and a real join stops cse. A probe of two `return`s with common float code, tested on
 *   tx and on the textures, kept branches and lost the shared 0.5 (2832 bytes).
 * - No effect: `y += adjust` with 0 (constant or local) gave the same differences as without it.
 *   A one-statement dead arm and a dead store to the helper's parameter likewise, and dumps show
 *   both tests gone before gcse. `do { } while (0)` around x and y gave the argument order, but
 *   blocked the 0.5 hoist, and x still folded into a0.
 * - Untested idea: 0.5 and 1 may be real locals rather than cse results. A local crosses a
 *   join without cse, which would remove the one-armed requirement argued in the sibling drafts.
 *   That still needs a real tested value for the join. tex1 being s3 rather than s2 is unexplained.
 *
 * closer D: the block boundary is a sched barrier, not a block. A loop note in the middle of a block makes the next
 * insn depend on everything before it (sched_analyze_insn), which is why do { } while (0) gave the argument order
 * here. A macro with do/while in retail would explain func_L22_003A5018 and func_L05_0041DF58 too; that spelling is
 * refused, so this stays open.
 */
#include "common.h"

extern char D_L25_00221850[] __attribute__((nosda));
extern char *D_L25_001B0CE0 __attribute__((sda));
extern int D_L25_001B0CD0 __attribute__((sda)), D_L25_001B0CD4 __attribute__((sda));
extern int D_L25_001B0CD8 __attribute__((sda));
extern char *D_L25_001A904C MACRO_ADDR;
extern float D_L25_001B2904 MACRO_ADDR;
extern int func_00282948(void *);
#define I(p,o) (*(int *)((char *)(p)+(o)))

extern int D_L25_001B0CE4 __attribute__((sda)), D_L25_001B0CE8 __attribute__((sda));
extern int D_L25_001B0CEC __attribute__((sda)), D_L25_001B0CF0 __attribute__((sda));
extern int D_L25_001B0D10 __attribute__((sda)), D_L25_001B0D18 __attribute__((sda));
extern int D_L25_001B0D14 MACRO_ADDR, D_L25_001B0D1C MACRO_ADDR;
extern int D_L25_001B2900 MACRO_ADDR;
extern float D_L25_001AC4E0 MACRO_ADDR, D_L25_001AC4E4 MACRO_ADDR;
extern int D_001A7340 MACRO_ADDR;
typedef struct { int active, pad1[2], capacity, maximum, count; short pad2[2], icon, pad3[5]; } InventoryEntry;
extern InventoryEntry D_L25_0029C320[] __attribute__((nosda));
typedef struct { u8 r, g, b, a; } Rgba;
extern void func_L25_0040DE40(int,int,int,int);
extern char *func_00288FB8(int);
extern int func_00115DA8(char *,char *,...);
extern void func_0027F5B8(int,int,u64,char *,int);
extern void func_0027F538(int,int,u64,char *,int);
extern int func_00336D50(void *,int);
extern float func_00283CE0(int);
extern void func_00300968(float,float,int,int,float,float);
extern int func_002ED8A0(int);
extern int func_00283D38(unsigned int,unsigned int,float);
extern void func_0027EAE8(int,int,int,int,int,void *);
extern void *func_0028E588(int,int);
extern void func_0028EA58(void *,int,int,int,int,void *);
extern void func_L05_003263F8(int);
extern int func_L05_00324DB8(void);
extern void func_L00_0030CF60(void);
extern void func_L05_0037A5F8(void);

typedef struct { char pad[0x10]; int count1, count2; char pad2[0x10]; int health; } HudState;

/* A screen coordinate scaled for the display; mode 1 also takes an offset in unscaled pixels
   (the same shape as scaled_screen_coord in src/game/002D3390.c). */
static __inline__ int hud_coord(int mode, float value, float offset)
{
    float scaled = value * D_L25_001B2904 + 0.5f;
    if (mode == 1)
        return (int)(scaled + offset);
    return (int)scaled;
}

int func_L25_0040D208(void)
{
    char text[128];
    int colors[2], colors2[2];
    char *state=*(char **)(D_L25_001B0CE0+0x68);
    char *row;
    float x,y,a,fill;
    int selection=1, color, result;
    char *message;
    float edge, ammoCount, ammoStart, ammoWidth;
    func_L25_0040DE40(0,selection,selection,selection);
    message=func_00288FB8(0x31d1);
    func_00115DA8(text,"%s: %d",message,((HudState *)D_L25_00221850)->count1);
    func_0027F5B8(D_L25_001B0D10-60,(int)((D_L25_001B0D14-8)*D_L25_001B2904+0.5f),0x80808080,text,128);
    message=func_00288FB8(0x31d2);
    func_00115DA8(text,"%s: %d",message,((HudState *)D_L25_00221850)->count2+1);
    func_0027F5B8(D_L25_001B0D18-60,(int)((D_L25_001B0D1C-8)*D_L25_001B2904+0.5f),0x80808080,text,128);
    if (D_L25_001A904C) {
        D_L25_001B0CD0=func_00336D50(D_L25_001A904C+0x8710,128);
        D_L25_001B0CD4=func_00336D50(D_L25_001A904C+0x8710,129);
        D_L25_001B0CD8=func_00336D50(D_L25_001A904C+0x8710,130);
        D_L25_001B0CE4=func_00336D50(D_L25_001A904C+0x8710,131);
        D_L25_001B0CE8=func_00336D50(D_L25_001A904C+0x8710,132);
        D_L25_001B0CEC=func_00336D50(D_L25_001A904C+0x8710,133);
        x=func_00283CE0(D_001A7340)*0.5f;
        y=(float)hud_coord(D_L25_001B2900,200.0f,4.0f);
        func_00300968(x,y,D_L25_001B0CD0,0x60442d00,1.0f,0.0f);
        func_00300968(x,y,D_L25_001B0CD4,0x55f0c070,1.0f,0.0f);
        selection=func_002ED8A0(6);
        a=func_00283CE0(D_L25_0029C320[selection].count);
        a/=func_00283CE0(D_L25_0029C320[selection].capacity);
        switch(selection) {
        case 6:
            if(a>0.0f) func_00300968(x,y,D_L25_001B0CE4,(int)(float)func_00283D38(0x800000ff,0x8000ff00,a),1.0f,0.0f);
            break;
        case 12:
            if(a>0.5f) {
                a-=0.5f;
                func_00300968(x,y,D_L25_001B0CE8,(int)(float)func_00283D38(0x800000ff,0x8000ff00,a+a),1.0f,0.0f);
                func_00300968(x,y,D_L25_001B0CE4,0x8000ff00,1.0f,0.0f);
            } else if(a>0.0f) {
                func_00300968(x,y,D_L25_001B0CE4,(int)(float)func_00283D38(0x800000ff,0x8000ff00,a+a),1.0f,0.0f);
            }
            break;
        case 14:
            if(a>0.666666687f) {
                a-=0.666666687f;
                func_00300968(x,y,D_L25_001B0CEC,(int)(float)func_00283D38(0x800000ff,0x8000ff00,a*3.0f),1.0f,0.0f);
                func_00300968(x,y,D_L25_001B0CE8,0x8000ff00,1.0f,0.0f);
                func_00300968(x,y,D_L25_001B0CE4,0x8000ff00,1.0f,0.0f);
            } else if(a>0.333333343f) {
                a-=0.333333343f;
                func_00300968(x,y,D_L25_001B0CE8,(int)(float)func_00283D38(0x800000ff,0x8000ff00,a*3.0f),1.0f,0.0f);
                func_00300968(x,y,D_L25_001B0CE4,0x8000ff00,1.0f,0.0f);
            } else if(a>0.0f) {
                func_00300968(x,y,D_L25_001B0CE4,(int)(float)func_00283D38(0x800000ff,0x8000ff00,a*3.0f),1.0f,0.0f);
            }
            break;
        }
        fill=(float)((HudState *)D_L25_00221850)->health*0.01f;
        if(fill>0.3f) {
            I(state,0x28)=1;
        } else if(func_00282948(state+0x24)) {
            I(state,0x24)=5; I(state,0x28)^=1;
        }
        colors[1]=func_00283D38(0x800000ff,0x8000ff00,fill);
        colors[0]=0x800000ff;
        edge=fill*200.0f+156.0f;
        if(I(state,0x28)) func_0027EAE8(156,14,(int)edge,27,1,colors);
        selection=func_002ED8A0(7);
        ammoCount=func_00283CE0(D_L25_0029C320[selection].count);
        fill=ammoCount/func_00283CE0(D_L25_0029C320[selection].maximum);
        color=func_00283D38(0x800000ff,0x8000ff00,fill);
        ammoStart=func_00283CE0(450);
        ammoWidth=func_00283CE0(386);
        ammoWidth-=func_00283CE0(450);
        colors2[0]=0x800000ff; colors2[1]=color;
        ammoWidth*=fill;
        edge=ammoStart+ammoWidth;
        if(fill>0.0f) func_0027EAE8(450,8,(int)edge,19,1,colors2);
        {
        Rgba rect[4]={{0x70,0xc0,0xf0,0x55},{0x70,0xc0,0xf0,0x55},{0x70,0xc0,0xf0,0x55},{0x70,0xc0,0xf0,0x55}};
        Rgba rect1[4]={{0x00,0x2d,0x44,0x60},{0x00,0x2d,0x44,0x60},{0x00,0x2d,0x44,0x60},{0x00,0x2d,0x44,0x60}};
        Rgba rect2[4]={{0x80,0x80,0x80,0x80},{0x80,0x80,0x80,0x80},{0x80,0x80,0x80,0x80},{0x80,0x80,0x80,0x80}};
        func_0028EA58(func_0028E588(0xea97,1),21,7,30,30,rect1);
        func_0028EA58(func_0028E588(0xea97,0),21,7,30,30,rect);
        row=(char *)&D_L25_0029C320[func_002ED8A0(D_L25_001B0CF0)];
        func_0028EA58(func_0028E588(0xea97,*(short *)(row+0x1c)),21,7,30,30,rect2);
        func_0028EA58(func_0028E588(0xea97,1),462,9,30,30,rect1);
        row=(char *)&D_L25_0029C320[func_002ED8A0(7)];
        func_0028EA58(func_0028E588(0xea97,*(short *)(row+0x1c)),462,9,30,30,rect2);
        }
        func_00115DA8(text,"%d/%d",D_L25_0029C320[func_002ED8A0(D_L25_001B0CF0)].count,D_L25_0029C320[func_002ED8A0(D_L25_001B0CF0)].maximum);
        func_0027F538(67,5,0x80808080,text,128);
        func_L05_003263F8(2);
        result=func_L05_00324DB8();
        if(result>=0) {
            D_L25_0029C320[func_002ED8A0(D_L25_001B0CF0)].active=0;
            D_L25_001B0CF0=result;
            D_L25_0029C320[func_002ED8A0(result)].active=1;
        }
        func_00300968(x,y,D_L25_001B0CD8,0x80f0f0f0,1.0f,0.0f);
    }
    func_L00_0030CF60();
    {
    int tex0=func_00336D50(D_L25_001A904C+0x8710,186);
    int tex1=func_00336D50(D_L25_001A904C+0x8710,187);
    int tex2=func_00336D50(D_L25_001A904C+0x8710,188);
    int iy;
    float px;
    px=D_L25_001AC4E0;
    iy=(int)((D_L25_001AC4E4+4.0f)*D_L25_001B2904+0.5f);
    func_00300968(px+4.0f,(float)iy,tex0,0x60442d00,0.8f,0.0f);
    px=D_L25_001AC4E0;
    iy=(int)((D_L25_001AC4E4+4.0f)*D_L25_001B2904+0.5f);
    func_00300968(px+4.0f,(float)iy,tex1,0x60241700,0.8f,0.0f);
    px=D_L25_001AC4E0;
    iy=(int)((D_L25_001AC4E4+4.0f)*D_L25_001B2904+0.5f);
    func_00300968(px+4.0f,(float)iy,tex2,0x55f0c070,0.8f,0.0f);
    }
    func_L05_0037A5F8();
    return 1;
}
