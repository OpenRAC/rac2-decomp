/* GPT-6.1 Sol high, task v0887; USA v1.01.
 * Best: 1108/1108 bytes, 0/1 places. Profile: -O2 -G8 -ffunction-sections -g
 * -mno-split-addresses. All required declarations follow.
 * The frame, saved GPRs, UV/following/flags spill slots and vector/corner body
 * agree. Remaining differences are flag iterator allocation/scheduling, loop
 * likely branches, hoisted UV-address registers and following's temporary.
 * Casting the shifted alpha byte to int removes an unsigned-to-float fallback
 * absent in retail. SDATA provides the GP UV base; an incomplete NOT_SDA alpha
 * array with -mno-split-addresses gives the retail absolute lwc1 through at.
 * Explicit UV pointer locals recover spills at 0x100/0x104, following at 0x108,
 * and flags at 0x10C. Initializing those pointers at the UV loop preserves the
 * retail order of saved address setup. The second scan needs an outer next<13
 * guard and flags+(next-1), rather than (flags+next)-1.
 * Separate cursor variables add a reload and nop (1116 bytes); one shared
 * cursor stays size-exact but uses a1 where retail uses v1.
 * Next: recover the original flag iterator source/lifetimes.
 * 2 November 2026 (Claude Opus 5.5), with the current compiler: this body is
 * still 1108/1108 with 20 differing rows, all in the two flag scans' registers
 * and order. Retail's second scan forms flags+(next-1) in v0, tests it, then
 * copies it to v1 for the loop: a separate loop pointer, as strength reduction
 * would make (-fno-strength-reduce moves 91 rows, so loop.c decides this).
 * No progress from: index scans `flags[next-1]` (not reduced; flags goes to s7,
 * 1068 bytes), an index second scan alone (142 rows), `cursor[i]` with a
 * separate counter (28), `*cursor++` (1100 bytes), pre-increment do/while (21),
 * a static __inline__ scan helper (1120 bytes), seven local declaration
 * orders (20-21), and keep-block-order, gcse-unsplit-edges, no-null-pointer-
 * checks, hazard-labels, qcopy (1156 bytes) as per-file options.
 * 3 November 2026, second attempt: the index form is not strength-reduced at
 * all (flags is reloaded every iteration and the -1 folds into the lbu
 * offset), so retail's explicit `addiu v0,next,-1; addu v0,flags,v0` points at
 * a pointer start value in its own variable, tested before being copied into
 * the loop cursor (v1). `if (next<13 && *(cursor=flags+(next-1))) do ...
 * while` ties the retained 20 rows; a break-inside while (1092 bytes) and a
 * post-increment break loop (1100) are worse.
 */
#include "common.h"
typedef int Quadword __attribute__((mode(TI)));
extern void func_00282CF0(void *, void *, void *);
extern void func_00282CC0(void *, void *, void *);
extern void func_00282DD8(void *, void *, void *);
extern void func_00282F20(void *, void *, float);
extern void func_00281DE8(void *, int, int, int);
extern void func_00280B90(void *, int, int);
extern float func_002A7878(float, float);
extern char D_L11_001BA8C0[];
extern float D_L11_001B12B0 __attribute__((sda));
extern float D_L11_001B12B8 __attribute__((sda));
extern float D_L11_001B12BC __attribute__((sda));
extern float D_L11_001B12C0 __attribute__((sda));
extern float D_L11_001B12A8 __attribute__((sda));
extern unsigned int D_L11_001B12A0 __attribute__((sda));
extern unsigned int D_L11_001B12A4 __attribute__((sda));
extern float D_L11_001B1280[] SDATA(D_L11_001B1280);
extern float D_L11_001B1284[];
extern float D_L11_001B12B4[] NOT_SDA;
/* The alpha range endpoint at 001B12B4 is read as float by retail. */
void func_L11_00438880(char *obj) {
    float end[4], start[4], span[4], a[4], b[4], inset[4];
    struct { Quadword pos[4]; unsigned int color[4]; float uv[4][2]; unsigned long words[4]; } quad;
    Quadword corner;
    float *uv0, *uv1;
    char *st=*(char **)(obj+0x68);
    int next, prev, following, i;
    unsigned char *cursor, *flags;
    unsigned int color;
    if (*(unsigned char *)(obj+0x20)<2) return;
    next=1; prev=0; flags=(unsigned char *)(st+0x380);
    for(cursor=flags; next<13 && *cursor; next++,cursor++);
    while (next<12) {
        qcopy(end,st+0x100+next*16);
        qcopy(start,st+0x100+prev*16);
        following=next+1;
        func_00282CF0(inset,start,end);
        func_00282F20(inset,inset,D_L11_001B12C0);
        func_00282CC0(end,end,inset);
        func_00282CF0(span,end,start);
        func_00282CF0(a,end,D_L11_001BA8C0);
        func_00282CF0(b,start,D_L11_001BA8C0);
        func_00282DD8(a,a,span);
        func_00282DD8(b,b,span);
        func_00282F20(a,a,D_L11_001B12B8);
        func_00282F20(b,b,D_L11_001B12B8);
        func_00281DE8(&quad,23,1,128);
        color=(D_L11_001B12A0 & 0xFFFFFF) | ((int)(func_002A7878(D_L11_001B12B0,D_L11_001B12B4[0])*(int)(D_L11_001B12A0>>24))<<24);
        quad.color[0]=quad.color[1]=quad.color[2]=quad.color[3]=color;
        uv0=&quad.uv[0][0]; uv1=&quad.uv[0][1];
        for(i=0;i<4;i++) { uv0[i*2]=D_L11_001B1280[i*2]+*(float *)(st+0x35C); uv1[i*2]=D_L11_001B1284[i*2]; }
        func_00282CF0(&corner,end,a); quad.pos[0]=corner;
        func_00282CC0(&corner,end,a); quad.pos[1]=corner;
        func_00282CF0(&corner,start,b); quad.pos[2]=corner;
        func_00282CC0(&corner,start,b); quad.pos[3]=corner;
        func_00280B90(&quad,0,0);
        func_00282F20(a,a,D_L11_001B12BC);
        func_00282F20(b,b,D_L11_001B12BC);
        func_00282CF0(&corner,end,a); quad.pos[0]=corner;
        func_00282CC0(&corner,end,a); quad.pos[1]=corner;
        func_00282CF0(&corner,start,b); quad.pos[2]=corner;
        func_00282CC0(&corner,start,b); quad.pos[3]=corner;
        func_00281DE8(&quad,43,1,128);
        quad.color[0]=quad.color[1]=quad.color[2]=quad.color[3]=D_L11_001B12A4;
        func_00280B90(&quad,0,0);
        prev=next; next=following;
        if(next<13) { for(cursor=flags+(next-1); next<13 && *cursor; next++,cursor++); }
    }
    *(float *)(st+0x35C)+=D_L11_001B12A8;
    if (*(float *)(st+0x35C)>1) *(float *)(st+0x35C)-=2;
    if (*(float *)(st+0x35C)<-1) *(float *)(st+0x35C)+=2;
}
