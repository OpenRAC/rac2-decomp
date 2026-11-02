/* functional: medium. Near-miss draft of retail size with the same frame: differences are allocation and scheduling, with some block order; paths the captured calls never take are unproven. */
/* opus-1 worker (Claude Opus 5.5, xhigh), task v1872, USA v1.01.
 * Closest draft: 3620 bytes / 3620 retail, 0 of 1 places; 80 of 905 rows differ, first at +0x208.
 * Compile as a dedicated -g8.c unit with default game flags (-O2 -G8 -ffunction-sections).
 * All required declarations are below. No linked build was run.
 *
 * NOT LANDABLE AS WRITTEN: text_row tests `data` only as a placeholder, to create the block
 * boundary. Its real condition is unknown; its arms compile alike.
 *
 * Established against retail (each moved the bytes toward retail):
 * - `idx=1` at entry is one pseudo with the later `idx=func_002ED8A0(6)`: gives `addiu s2,1`, `beq v1,s2`.
 * - `if(x) score=...; else score=0;` puts the zero in the branch delay slot.
 * - textX shares a local with the 0xF85 object: the copy preference for v0 gives `daddu a0,v0`.
 *   Case 2 has its own pseudo, which gets a0 directly (`addiu a0,v0,-0x46`).
 * - func_00300968 is declared (void *,f32,f32,s32,f32,f32): the bank-preserving interleaving
 *   reproduces every draw's argument order. This differs from the (ptr,int,float...) form in
 *   other units; each bank keeps its order, count and widths, as AGENTS.md allows.
 * - screen_coord is scaled_screen_coord from src/game/002D3390.c, with its real mode load.
 * - Corrections to earlier drafts: case 6 tweens to 0x8000FF00; case 14's top branch also
 *   draws D_L10_001B13DC; the blink is `if(>0.3) f38=1; else if(timer) {...}`; colors[1] is
 *   stored before colors[0]; the bar endpoint is computed before its test.
 * - sprite1 reuses the `data` local, which gives s3.
 *
 * Remaining differences:
 * 1. +0x208 and +0x318: print argument order. Retail always sets a1 first. In this draft's second
 *    scheduling pass, a0 outranks a1 at +0x318, where a0 is set again later in the same block.
 *    Inference, not proven: retail also sets a1 again in that block, so `mfc1 a1` lies BEFORE the
 *    block boundary rather than in the arms as in text_row.
 *    +0x3FC (case 3's first draw, a3 before a0) is still unexplained.
 * 2. +0xC98 to the epilogue: the three final sprite draws. Retail evaluates x, y and (f32)y, then
 *    loads 0.8f, 0.0f and the remaining arguments (y integer in v1, x through f1 to f12). This
 *    looks like the same boundary, later in the expression. The direct arguments here have none.
 * (+0x8CC differs only by how the D_L10_00221CD0 relocation displays, so 80 rows really differ.)
 *
 * The missing construct: a real block boundary after the integer conversion that survives to the
 * second scheduling pass and leaves no word. Measured, all failing:
 * - identical copy arms: the jump count falls from 61 to 43 in the cse2 dump and the arms are gone;
 * - a one-instruction dead arm: also gone by the cse2 dump (conditional-move if-conversion is a
 *   guess at the cause);
 * - a two-instruction dead arm: the text draws show no boundary at the first scheduling pass;
 * - `row+=adjust` with a zero held in a function-scope local: folds, no boundary;
 * - draw calls in identical arms: size 3748, not merged. A (use (const_int 0)) follows the
 *   fall-through arm's call in the dump, probably what stops cross-jumping. Case 0's order inside
 *   the block is right in this form;
 * - testing the converted row itself: the else arm becomes `a1=0`, so the branch stays;
 * - `do { } while (0)` after the conversion: forbidden, and measured worse (x goes to a0).
 * Next: find a real condition and arm shape meeting those constraints. The tested value must be in
 * a register at every site (no load of D_L10_001B2D80 appears at the text or sprite draws). The
 * explicit half and fmt locals may prove unnecessary: a boundary CSE can skip over would make those
 * values common without them.
 */
#include "common.h"
#define I(p,o) (*(s32 *)((u8 *)(p)+(o)))
typedef struct { u8 bytes[16]; } Block;
extern u8 *D_L10_001B13F0 __attribute__((sda));
extern s32 D_L10_001B13A0 __attribute__((sda));
extern s32 D_L10_001B13F4 __attribute__((sda));
extern s32 D_L10_001B13F8 __attribute__((sda));
extern s32 D_L10_001B13FC __attribute__((sda));
extern s32 D_L10_001B14C0 __attribute__((sda));
extern s32 D_L10_001B14B8 __attribute__((sda));
extern s32 D_L10_001B14A8 __attribute__((sda));
extern s32 D_L10_001B1428 __attribute__((sda));
extern s32 D_L10_001B141C __attribute__((sda));
extern void *D_L10_001B13D0 __attribute__((sda));
extern void *D_L10_001B13D4 __attribute__((sda));
extern void *D_L10_001B13D8 __attribute__((sda));
extern void *D_L10_001B13DC __attribute__((sda));
extern void *D_L10_001B13E0 __attribute__((sda));
extern void *D_L10_001B13E4 __attribute__((sda));
extern u8 *D_L10_001A904C MACRO_ADDR;
extern s32 D_L10_001B14C4 MACRO_ADDR;
extern s32 D_L10_001B14BC MACRO_ADDR;
extern s32 D_L10_001B14AC MACRO_ADDR;
extern f32 D_L10_001B2D84;
extern s32 D_L10_001B2D80 MACRO_ADDR;
extern s32 D_001A7340 MACRO_ADDR;
extern s32 D_L10_001B3550 MACRO_ADDR;
typedef struct { u8 pad00[0x28]; s32 health; } HudMissionState;
extern HudMissionState D_L10_00221CD0;
extern f32 D_L10_001AC5E0, D_L10_001AC5E4;
extern char D_L10_001B14C8[], D_L10_001B14D0[], D_L10_001B1518[];
extern Block D_L10_001B14E8, D_L10_001B14F8, D_L10_001B1508;
typedef struct {
 s32 active;
 u8 pad04[8];
 s32 maxLevel;
 s32 maxAmmo;
 s32 value;
 u8 pad18[4];
 s16 icon;
 u8 pad1E[10];
} HudWeapon;
extern HudWeapon D_L10_002A3C70[];
extern void func_L10_00424CD0(s32,s32,s32,s32);
extern void *func_L05_00379ED0(s32);
extern s32 func_L10_0037D200(void *);
extern s32 func_L05_0037B3A0(void *);
extern char *func_00288FB8(s32);
extern s32 func_00115DA8(char *,char *,...);
extern void func_0027F5B8(s32,s32,u64,char *,s32);
extern s32 func_L10_004176A0(void),func_L10_004176B0(void);
extern void func_L00_0030DD70(char *,s32);
extern s32 func_00282948(s32 *);
extern void func_002ED578(s32,s32 *,s32 *,s32 *);
extern void *func_00336D50(void *,s32);
extern f32 func_00283CE0(s32);
extern void func_00300968(void *,f32,f32,s32,f32,f32);
extern s32 func_002ED8A0(s32);
extern s32 func_00283D38(u32,u32,f32);
extern void func_0027EAE8(s32,s32,s32,s32,s32,u32 *);
extern void *func_0028E588(s32,s32);
extern void func_0028EA58(void *,s32,s32,s32,s32,Block *);
extern void func_0027F538(s32,s32,u64,char *,s32);
extern void func_L05_003263F8(s32);
extern s32 func_L05_00324DB8(void);
extern void func_L00_0030CF60(void),func_L05_0037A5F8(void);

static __inline__ s32 text_row(s32 mode, f32 scaled, s32 adjust)
{
 if(mode!=0) return (s32)scaled+adjust;
 return (s32)scaled;
}

static __inline__ s32 screen_coord(s32 mode, f32 value, f32 offset)
{
 f32 scaled=value*D_L10_001B2D84+0.5f;
 if(mode==1) return (s32)(scaled+offset);
 return (s32)scaled;
}

s32 func_L10_00421790(void) {
 char text[128];
 char *label;
 u32 colors[2],colors2[2];
 Block b0,b1,b2;
 s32 a,b,c,score,idx=1,newidx,color,textX,textY;
 f32 scaled;
 void *object;
 u8 *data=*(u8 **)(D_L10_001B13F0+0x68);
 f32 x,y,ratio,tmp,base,end,hudY,ammo,tweenColor;
 void *sprite0,*sprite1,*sprite2;
 switch(D_L10_001B13A0) {
 case 0:
 func_L10_00424CD0(0,1,0,1);
 textX=(s32)func_L05_00379ED0(0xf85); if(textX) score=func_L10_0037D200((void *)textX); else score=0;
 label=func_00288FB8(0x31d8);
 func_00115DA8(text,D_L10_001B14C8,label,score);
 scaled=(D_L10_001B14C4-8)*D_L10_001B2D84+0.5f; textX=D_L10_001B14C0-65; func_0027F5B8(textX,text_row((s32)data,scaled,0),0x80808080,text,128);
 if(func_L10_004176A0() && D_L10_001B13F4) { D_L10_001B13F4=0; D_L10_001B13F8=180; }
 if(func_L10_004176B0()) { D_L10_001B13F4=1; D_L10_001B13FC=180; }
 if(D_L10_001B13F8) func_L00_0030DD70(func_00288FB8(0x31d9),-1);
 if(D_L10_001B13FC) func_L00_0030DD70(func_00288FB8(0x31da),-1);
 func_00282948(&D_L10_001B13F8); func_00282948(&D_L10_001B13FC);
 break;
 case 1: {
 f32 half=0.5f;
 char *fmt;
 func_L10_00424CD0(0,1,1,1);
 label=func_00288FB8(0x31db); fmt=D_L10_001B14C8;
 func_00115DA8(text,fmt,label,func_L05_0037B3A0(func_L05_00379ED0(0xf93)));
 scaled=(D_L10_001B14BC-8)*D_L10_001B2D84+half; textX=D_L10_001B14B8-65; func_0027F5B8(textX,text_row((s32)data,scaled,0),0x80808080,text,128);
 label=func_00288FB8(0x31dc);
 func_00115DA8(text,fmt,label,func_L05_0037B3A0(func_L05_00379ED0(0xcbe)));
 scaled=(D_L10_001B14C4-8)*D_L10_001B2D84+half; textX=D_L10_001B14C0-65; func_0027F5B8(textX,text_row((s32)data,scaled,0),0x80808080,text,128);
 break;
 }
 case 2: {
 char *fmt;
 func_L10_00424CD0(0,1,0,1);
 label=func_00288FB8(0x31dd); fmt=D_L10_001B14C8;
 func_00115DA8(text,fmt,label,func_L05_0037B3A0(func_L05_00379ED0(0xf8e)));
 scaled=(D_L10_001B14C4-8)*D_L10_001B2D84+0.5f; func_0027F5B8(D_L10_001B14C0-70,text_row((s32)data,scaled,0),0x80808080,text,128);
 break;
 }
 case 3: {
 f32 half=0.5f;
 func_L10_00424CD0(1,1,0,1);
 label=func_00288FB8(0x31d7);
 func_00115DA8(text,D_L10_001B14C8,label,D_L10_001B141C);
 scaled=(D_L10_001B14C4-8)*D_L10_001B2D84+half; textX=D_L10_001B14C0-65; func_0027F5B8(textX,text_row((s32)data,scaled,0),0x80808080,text,128);
 func_002ED578(D_L10_001B3550,&a,&b,&c);
 label=func_00288FB8(0x2f83);
 func_00115DA8(text,D_L10_001B14D0,label,a,b,c);
 scaled=(D_L10_001B14AC-8)*D_L10_001B2D84+half; textX=D_L10_001B14A8-80; func_0027F5B8(textX,text_row((s32)data,scaled,0),0x80808080,text,128);
 break;
 }
 }
 if(D_L10_001A904C) {
 D_L10_001B13D0=func_00336D50(D_L10_001A904C+0x8710,128);
 D_L10_001B13D4=func_00336D50(D_L10_001A904C+0x8710,129);
 D_L10_001B13D8=func_00336D50(D_L10_001A904C+0x8710,130);
 D_L10_001B13DC=func_00336D50(D_L10_001A904C+0x8710,131);
 D_L10_001B13E0=func_00336D50(D_L10_001A904C+0x8710,132);
 D_L10_001B13E4=func_00336D50(D_L10_001A904C+0x8710,133);
 x=func_00283CE0(D_001A7340)*0.5f;
 y=screen_coord(D_L10_001B2D80,200.0f,4.0f);
 func_00300968(D_L10_001B13D0,x,y,0x60442d00,1.0f,0.0f);
 func_00300968(D_L10_001B13D4,x,y,0x55f0c070,1.0f,0.0f);
 idx=func_002ED8A0(6);
 ratio=func_00283CE0(D_L10_002A3C70[idx].value)/func_00283CE0(D_L10_002A3C70[idx].maxLevel);
 switch(idx) {
 case 6: if(ratio>0.0f) { tweenColor=func_00283D38(0x800000ff,0x8000ff00,ratio); func_00300968(D_L10_001B13DC,x,y,(s32)tweenColor,1.0f,0.0f); } break;
 case 12:
 if(ratio>0.5f) { ratio-=0.5f; tweenColor=func_00283D38(0x800000ff,0x8000ff00,ratio+ratio); func_00300968(D_L10_001B13E0,x,y,(s32)tweenColor,1.0f,0.0f); func_00300968(D_L10_001B13DC,x,y,0x8000ff00,1.0f,0.0f); }
 else if(ratio>0.0f) { tweenColor=func_00283D38(0x800000ff,0x8000ff00,ratio+ratio); func_00300968(D_L10_001B13DC,x,y,(s32)tweenColor,1.0f,0.0f); }
 break;
 case 14:
 if(ratio>0.6666667f) { ratio-=0.6666667f; tweenColor=func_00283D38(0x800000ff,0x8000ff00,ratio*3.0f); func_00300968(D_L10_001B13E4,x,y,(s32)tweenColor,1.0f,0.0f); func_00300968(D_L10_001B13E0,x,y,0x8000ff00,1.0f,0.0f); func_00300968(D_L10_001B13DC,x,y,0x8000ff00,1.0f,0.0f); }
 else if(ratio>0.33333334f) { ratio-=0.33333334f; tweenColor=func_00283D38(0x800000ff,0x8000ff00,ratio*3.0f); func_00300968(D_L10_001B13E0,x,y,(s32)tweenColor,1.0f,0.0f); func_00300968(D_L10_001B13DC,x,y,0x8000ff00,1.0f,0.0f); }
 else if(ratio>0.0f) { tweenColor=func_00283D38(0x800000ff,0x8000ff00,ratio*3.0f); func_00300968(D_L10_001B13DC,x,y,(s32)tweenColor,1.0f,0.0f); }
 break;
 }
 ammo=D_L10_00221CD0.health*0.01f;
 if(ammo>0.3f) I(data,0x38)=1;
 else if(func_00282948((s32 *)(data+0x34))) { I(data,0x34)=5; I(data,0x38)^=1; }
 colors[1]=func_00283D38(0x800000ff,0x8000ff00,ammo); colors[0]=0x800000ff;
 tmp=ammo*200.0f+156.0f;
 if(I(data,0x38)) func_0027EAE8(156,14,(s32)tmp,27,1,colors);
 idx=func_002ED8A0(7);
 ratio=func_00283CE0(D_L10_002A3C70[idx].value);
 ammo=ratio/func_00283CE0(D_L10_002A3C70[idx].maxAmmo);
 color=func_00283D38(0x800000ff,0x8000ff00,ammo);
 base=func_00283CE0(450); end=func_00283CE0(386); end-=func_00283CE0(450);
 colors2[0]=0x800000ff; colors2[1]=color;
 end=end*ammo; tmp=base+end;
 if(ammo>0.0f) func_0027EAE8(450,8,(s32)tmp,19,1,colors2);
 b0=D_L10_001B14E8; b1=D_L10_001B14F8; b2=D_L10_001B1508;
 func_0028EA58(func_0028E588(0xea97,1),21,7,30,30,&b1);
 func_0028EA58(func_0028E588(0xea97,0),21,7,30,30,&b0);
 func_0028EA58(func_0028E588(0xea97,D_L10_002A3C70[func_002ED8A0(D_L10_001B1428)].icon),21,7,30,30,&b2);
 func_0028EA58(func_0028E588(0xea97,1),462,9,30,30,&b1);
 func_0028EA58(func_0028E588(0xea97,D_L10_002A3C70[func_002ED8A0(7)].icon),462,9,30,30,&b2);
 func_00115DA8(text,D_L10_001B1518,D_L10_002A3C70[func_002ED8A0(D_L10_001B1428)].value,D_L10_002A3C70[func_002ED8A0(D_L10_001B1428)].maxAmmo);
 func_0027F538(67,5,0x80808080,text,128);
 func_L05_003263F8(2); newidx=func_L05_00324DB8();
 if(newidx>=0) { D_L10_002A3C70[func_002ED8A0(D_L10_001B1428)].active=0; D_L10_001B1428=newidx; D_L10_002A3C70[func_002ED8A0(newidx)].active=1; }
 func_00300968(D_L10_001B13D8,x,y,0x80f0f0f0,1.0f,0.0f);
 }
 func_L00_0030CF60();
 sprite0=func_00336D50(D_L10_001A904C+0x8710,186);
 data=func_00336D50(D_L10_001A904C+0x8710,187);
 sprite2=func_00336D50(D_L10_001A904C+0x8710,188);
 func_00300968(sprite0,D_L10_001AC5E0+4.0f,(s32)((D_L10_001AC5E4+4.0f)*D_L10_001B2D84+0.5f),0x60442d00,0.8f,0.0f);
 func_00300968(data,D_L10_001AC5E0+4.0f,(s32)((D_L10_001AC5E4+4.0f)*D_L10_001B2D84+0.5f),0x60241700,0.8f,0.0f);
 func_00300968(sprite2,D_L10_001AC5E0+4.0f,(s32)((D_L10_001AC5E4+4.0f)*D_L10_001B2D84+0.5f),0x55f0c070,0.8f,0.0f);
 func_L05_0037A5F8(); return 1;
}
