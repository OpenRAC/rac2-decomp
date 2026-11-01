/* v0893, GPT-6.1 Sol high, USA v1.01, current pinned compiler, 2026-10-29.
   Dedicated -O2 -G8 -ffunction-sections -frac2-qcopy -frac2-qcopy-barrier
   -frac2-zero-ti-por: 1168/1168 bytes, 0/4 places, first mismatch +0x1C.
   The absolute macro views remove cached scale/object-table high halves.
   Camera view is +0x230 from its position, as retail computes it. Corrected
   scale association to distance*(radius/128), and the clamps to ordered >/<.
   Reusing distance for marker size and y for scale/screen Y matches saved FP
   allocation; calculating radius/128 before the clear matches constant order.
   Remaining: entry saves/conversion scheduling, list-table base hoisted into
   s7 (retail rematerializes it), loop-next index s6 versus s7, clear register
   and scale multiply scheduling, and color assembly versus Y conversion.
   A separate rounded-Y integer/color staging grows to 1180; a macro list-table
   view with split color staging shrinks to 1148. Debug labels do not close it.
   Reopen with an evidenced list-base/color lifetime; no handwritten claim.
   Required declarations are included below.
   1 November 2026: both draw sites share alpha (retail's a0, set to 0x80 in the
   slot of the second site's first test) and c. In retail every integer insn of
   those sites and of the entry comes after "cvt.w.s; mfc1", though sll is ready
   at the top of the block and an ALU slot is free: mtc1/cvt.s.w, lw 0x150, sll
   and the texture argument behave as if in a later block. The conversion
   result's register (a1 at the entry, v1 at both sites) also looks global. A
   static inline drawing helper taking y as an int was tried: worse (115 rows).
*/

#include "common.h"
typedef int Quad __attribute__((mode(TI)));
extern float D_L05_001AC4E0 __attribute__((sda));
extern float D_L05_001AC4E4 __attribute__((sda));
extern float D_L05_001AC4E8 __attribute__((sda));
extern float D_L05_001AC4EC __attribute__((sda));
extern int D_L05_001AC4F0 __attribute__((sda));
extern int D_L05_001AC4F4 __attribute__((sda));
extern float D_L05_001AC4F8 __attribute__((sda));
extern int D_L05_001AC4FC __attribute__((sda));
extern float D_L05_001B2D84[] MACRO_ADDR;
extern u8 *D_L05_00225DD0[] NOT_SDA;
extern u16 *D_L05_001FB220[];
extern u8 *D_L05_001B251C[] MACRO_ADDR;
typedef struct { float position[4]; u8 pad[0x220]; float view[12]; } L05HudCamera;
extern L05HudCamera D_L05_001B96C0;
extern u64 func_0027C878(int);
extern void func_L05_003008C0(float,float,float,float,int,int,int,int,u64,u64);
extern int func_L00_004272A0(void);
extern s32 func_002ED688(u8 *);
extern float func_00282E48(void *,void *);
extern void func_002833F0(void *,void *);
extern void func_00282CF0(void *,void *,void *);
extern void func_00282F20(void *,void *,float);
extern void func_002836E8(void *,void *);
extern void func_00283098(void *,void *,void *);
extern float func_002A7798(float);
extern int func_00283CF0(float);
void func_L05_0037A5F8(void)
{
    float offset[4],rotation[4],rotate[12],view[12];
    float distance,x,y;
    u64 texture,color;
    u8 *object,*state;
    u16 *list,*nextList;
    int i,alpha,c;
    y = (float)(int)(D_L05_001AC4E4*D_L05_001B2D84[0]+0.5f);
    texture = func_0027C878(D_L05_001AC4FC);
    func_L05_003008C0(D_L05_001AC4E0,y,D_L05_001AC4E8,D_L05_001AC4EC,0,0,D_L05_001AC4F0,D_L05_001AC4F4,0x80808080ULL,texture);
    for (i=0;i<func_L00_004272A0();i++) {
        nextList = D_L05_001FB220[D_L05_00225DD0[i][0x21]];
        if (!nextList) continue;
        list = nextList;
        do {
            object = D_L05_001B251C[0]+((*list&0x7FFF)<<8);
            state = (u8 *)func_002ED688(object);
            if (*(int *)(state+0x110) && *(int *)(state+0x14C)) {
                distance = func_00282E48(D_L05_001B96C0.position,object+0x10);
                if (distance <= 128.0f) {
                    y = D_L05_001AC4F8*0.0078125f;
                    *(Quad *)rotation = 0;
                    rotation[2] = 1.5707964f;
                    y = distance*y;
                    func_002833F0(rotate,rotation);
                    func_00282CF0(offset,object+0x10,D_L05_001B96C0.position);
                    func_00282F20(offset,offset,y);
                    func_002836E8(view,D_L05_001B96C0.view);
                    func_00283098(offset,offset,view);
                    func_00283098(offset,offset,rotate);
                    alpha = func_00283CF0(func_002A7798(1.0f-distance*0.0078125f)*128.0f);
                    distance = offset[2]*0.125f+D_L05_001AC4E8*0.5f;
                    if (*(int *)(state+0x158)) { alpha=128; distance=D_L05_001AC4E8*0.5f; }
                    if (distance > D_L05_001AC4E8+D_L05_001AC4E8) distance=D_L05_001AC4E8+D_L05_001AC4E8;
                    else if (distance < 0.0f) distance=0.0f;
                    x = offset[0]+D_L05_001AC4E0;
                    y = (float)(int)((D_L05_001AC4E4-offset[1])*D_L05_001B2D84[0]+0.5f);
                    c = *(s32 *)(state+0x150) | (alpha<<24);
                    color = c;
                    texture = func_0027C878(D_L05_001AC4FC);
                    func_L05_003008C0(x,y,distance,distance,0,0,D_L05_001AC4F0,D_L05_001AC4F4,color,texture);
                } else if (*(int *)(state+0x158)) {
                    *(Quad *)rotation = 0;
                    rotation[2] = 1.5707964f;
                    y = D_L05_001AC4F8;
                    func_002833F0(rotate,rotation);
                    func_00282CF0(offset,object+0x10,D_L05_001B96C0.position);
                    func_00282F20(offset,offset,y);
                    func_002836E8(view,D_L05_001B96C0.view);
                    func_00283098(offset,offset,view);
                    func_00283098(offset,offset,rotate);
                    alpha=128;
                    distance = D_L05_001AC4E8;
                    if (distance > D_L05_001AC4E8+D_L05_001AC4E8) distance=D_L05_001AC4E8+D_L05_001AC4E8;
                    else if (distance < 0.0f) distance=0.0f;
                    x = offset[0]+D_L05_001AC4E0;
                    y = (float)(int)((D_L05_001AC4E4-offset[1])*D_L05_001B2D84[0]+0.5f);
                    c = *(s32 *)(state+0x150) | (alpha<<24);
                    color = c;
                    texture = func_0027C878(D_L05_001AC4FC);
                    func_L05_003008C0(x,y,distance,distance,0,0,D_L05_001AC4F0,D_L05_001AC4F4,color,texture);
                }
            }
        } while ((s16)*list++ >= 0);
    }
}
