/* functional: medium. Near-miss draft of retail size with the same frame: differences are allocation and scheduling, with some block order; paths the captured calls never take are unproven. */
/*
 * Tier: Claude Opus 5.5 (xhigh), task v1674, 30 October 2026.
 * Current US check.py: 984/984 bytes, 0/3 placements, 3 instructions differ; no linked match.
 * Profile: -O2 -G8 -ffunction-sections (the qcopy switches change nothing here; -g ties;
 * -fno-rerun-cse-after-loop and -fno-expensive-optimizations are much worse).
 * Corresponds to RAC1's src/game/effects.c draw_lens_flare (GPL-3.0); retail has 14 elements.
 *
 * Remaining, at +0x170..+0x178: retail `lui $v1; lw $v1,0x273C($v1); daddu $s0,$v0,$zero',
 * here `lui $a0; daddu $s0,$v0,$zero; lw $v1,0($a0)'. Declaring D_L00_001B273C as a plain array
 * makes gcse's PRE hoist its %hi, which is spilled and rebuilt by reload in a scratch register.
 * It cannot be $v1: reload may not use the load's own output. Declared as its sibling declares
 * it (`[] __attribute__((sda))') or as a scalar, the load is retail's single `lw' macro and every
 * instruction matches, but $s3/$s4/$s5 are permuted (12 lines); see the allocator notes below.
 *
 * Solved here: the 980-byte form folded the scale load into `lwc1 %lo'. Retail's
 * `lui; addiu; lwc1 0($v1)' is a pointer set before the loop and in no block with its use, so
 * cse and combine cannot fold it; it gets no register (all nine saved GPRs are taken) and reload
 * rebuilds it from its REG_EQUIV inside the loop. Volatile, const, and pointers set in the loop do
 * not give this shape (a pointer set in the loop is folded or hoisted past the last call).
 *
 * Allocator: retail's order is scale pointer ($s3), base copy ($s4), alpha pointer ($s5), i ($s6).
 * Priority is floor_log2(refs)*refs/live; refs are 9, 10, 5, 9. With live counted at 2 per insn
 * after sched1, this needs live(scale) <= 260, live(base) <= 293, live(i) >= 266, live(alpha) 98.
 * The pointer's position before center[0] gives 262/290/266; one more instruction in sched1's
 * free slot next to the second func_00283CE0 call gives retail's order: both a kept 5.0f local
 * (but it costs a save of $f27) and the hoisted %hi above do it. Between center[0] and center[1] gives 254/290/258, so `i' outranks the
 * base. What would unblock it: a source of that one instruction that leaves no code in the loop.
 * D_L00_001AED00 is 64 in the `lit' section; D_L00_001B273C is .bss, written by func_L00_00382AE8.
 */
#include "common.h"

typedef int Quadword __attribute__((mode(TI)));
typedef union { Quadword bits; float f[4]; } Vector4;
#define FIELD(type, p, off) (*(type *)((char *)(p) + (off)))

extern float func_00282E48(void *, void *);
extern float func_00283CE0(int);
extern void func_00279BD8(void *, void *);
extern unsigned long func_0027C878(int);
extern float func_00282C48(float);
extern int func_00283CF0(float);
extern void func_002FC560(unsigned int, unsigned long long);
extern void func_0027E018(int, int, int, int, int, int, int, int,
                         unsigned long, unsigned long);

typedef struct {
    char *target;
    int active;
    float intensity;
    int pad;
    short alpha[16];
    short texture[16];
    unsigned int color[16];
    float offset[16];
    float scale[16];
} FlareState;
extern FlareState D_L00_001B90C0;
extern Vector4 D_L00_001B8DC0;
extern int D_001A7348[] __attribute__((sda));
extern int D_L00_001B273C[];
extern int D_L00_001AED00[];

void func_L00_00382F28(char *object)
{
    char *work=FIELD(char *,object,0x68);
    Vector4 screen;
    float center[4],delta[4],offset[4],location[4];
    float distance,fade,horizontal,vertical;
    unsigned long texture;
    int color;
    int i,size,left,top;
    int *baseSize;
    if(D_L00_001B90C0.active!=1 || (FIELD(unsigned char,D_L00_001B90C0.target,0x20)&0x80)) {D_L00_001B90C0.active=0;return;}
    if(D_L00_001B90C0.intensity<=0)return;
    distance=func_00282E48(&D_L00_001B8DC0,work);
    baseSize=D_L00_001AED00;
    center[0]=func_00283CE0(D_001A7348[0]);center[1]=func_00283CE0(D_001A7348[1]);
    func_00279BD8(&screen,work);
    screen.f[0]=(screen.f[0]-func_00283CE0(D_001A7348[2]))*0.0625f;
    screen.f[1]=(screen.f[1]-func_00283CE0(D_001A7348[3]))*0.0625f;
    delta[0]=center[0]-screen.f[0];delta[1]=center[1]-screen.f[1];
    for(i=0;i<14;++i) {
        texture=func_0027C878(D_L00_001B273C[0]+D_L00_001B90C0.texture[i]);
        offset[0]=delta[0]*D_L00_001B90C0.offset[i];offset[1]=delta[1]*D_L00_001B90C0.offset[i];
        location[0]=center[0]+offset[0];location[1]=center[1]+offset[1];
        fade=distance-5;if(fade>1)fade=1;else if(fade<0)fade=0;
        horizontal=(func_00282C48(delta[0])/center[0])*-5+5.5f;
        if(horizontal>1)horizontal=1;else if(horizontal<0)horizontal=0;
        vertical=(func_00282C48(delta[1])/center[1])*-5+5.5f;
        if(vertical>1)vertical=1;else if(vertical<0)vertical=0;
        fade*=((horizontal*vertical)*D_L00_001B90C0.intensity);
        color=(int)(((unsigned int)func_00283CF0(fade*(float)D_L00_001B90C0.alpha[i])<<24)|(D_L00_001B90C0.color[i]&0xFFFFFF));
        size=func_00283CF0((float)*baseSize*D_L00_001B90C0.scale[i]);
        func_002FC560(66,0x8000000048ULL);
        left=func_00283CF0(location[0]-(float)(size>>1));top=func_00283CF0(location[1]-(float)(size>>1));
        func_0027E018(left,top,size,size,0,0,64,64,color,texture);
    }
    D_L00_001B90C0.intensity=0;
}
