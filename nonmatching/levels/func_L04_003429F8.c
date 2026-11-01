/* opus-1 (Claude Opus 5.5), USA v1.01: the sol-high orch/main draft recompiled on this
 * checkout in its own -G8 unit (src/levels/shared/L04_002CC748-search-g8.c, default
 * game profile -O2 -G8 -ffunction-sections). check.py: 920/920 bytes, 0/4 places
 * (04, 06, 08, 17); recorded differences confirmed unchanged:
 * 1. out (pseudo 85: 18 refs, live 154, priority 4*18/154 = 0.468) and the gcse PRE
 *    copy of m + 0x10 for the inner area loop (pseudo 190: 5 loop-weighted refs, live
 *    20, priority 0.5) swap $s4/$s5: global alloc takes the PRE copy first. Retail needs
 *    out first (e.g. the copy at loop weight 4 refs, or live >= 22).
 * 2. In the hero count>0 path, retail's sched2 order is i = 0, limit = count - 1, then
 *    the three out+0x10/0x20/0x30 spill computations (i = 0 fills the blez slot); here
 *    the spill computations come first. Writing the hero loop as
 *    for (i = 0; i < count - 1; i++) (pointer assignments first) is worse.
 * An inline area-test helper shared by the hero and moby checks gives 876 bytes (the
 * pointers are then computed once), so retail computes them per branch.
 * Needs: common.h (qcopy, qzero) and the declarations below.
 *
 * closer D, 1 November 2026: for/while/limit/pointer-local forms of the moby area loop do not
 * change out's priority: 25, 44, 74 and 153 words.
 */
#include "common.h"
#define WBYTE(p,o) (*(unsigned char *)((char *)(p)+(o)))
#define WSHORT(p,o) (*(short *)((char *)(p)+(o)))
#define WINT(p,o) (*(int *)((char *)(p)+(o)))
#define WFLOAT(p,o) (*(float *)((char *)(p)+(o)))
#define WPTR(p,o) (*(char **)((char *)(p)+(o)))
typedef struct { float pos[4], velocity[4], previous[4], next[4]; char *moby; int result; } SearchOutput;
typedef struct { char pad[0x2290]; char *moby; int state; int lastState; int mode; } SearchHero;
extern SearchHero D_00189E20;
extern short D_L04_001B2630[] MACRO_ADDR __attribute__((sda));
extern char *D_L04_001B24DC;
extern int func_002ACBC8(void *,int);
extern int func_002A8AF0(void *,void *,int);
extern float func_00282E80(void *,void *);
int func_L04_003429F8(char *source,SearchOutput *out,int *areas,int count,void *region,int regionCount,float distance) {
    char *best=D_00189E20.moby;
    int result=0;
    char *velocity,*previous,*next;
    int i,j,valid;
    char *m;
    float d;
    if(D_00189E20.mode==24 || D_00189E20.state==0x6F) {best=0;result=2;velocity=(char *)out->velocity;previous=(char *)out->previous;next=(char *)out->next;}
    else if(count>0) {
        int i, limit;
        i=0;
        limit=count-1;
        velocity=(char *)out->velocity;previous=(char *)out->previous;next=(char *)out->next;
        for(;i<limit;i++) if(func_002ACBC8((char *)&D_00189E20+0x80,areas[i])) {best=0;result=2;break;}
    } else {
        velocity=(char *)out->velocity;previous=(char *)out->previous;next=(char *)out->next;
        if(region && regionCount>0 && !func_002A8AF0((char *)&D_00189E20+0x80,region,regionCount)) {best=0;result=2;}
    }
    for(j=1;j<=D_L04_001B2630[0];j++) {
        m=D_L04_001B24DC+(D_L04_001B2630[j]<<8);
        if(m && (WSHORT(m,0xAA)==0xCB || WSHORT(m,0xAA)==0x76C) && WBYTE(m,0x20)!=0xFE && WBYTE(m,0x20)!=0xFD && WBYTE(m,0x20)==3) {
            valid=1;
            d=func_00282E80(source+0x10,m+0x10);
            if(distance<=d) valid=0;
            else if(count>0) {
                        for(i=0;i<count-1;i++) if(func_002ACBC8(m+0x10,areas[i])) {valid=0;break;}
            } else if(region && regionCount>0 && !func_002A8AF0(m+0x10,region,regionCount)) valid=0;
            if(valid) {result=1;best=m;distance=d;}
        }
    }
    if(best) {
        out->moby=best;
        qcopy(out,best+0x10);
        qcopy(velocity,best+0xF0);
        if(best==D_00189E20.moby) {qcopy(previous,(char *)&D_00189E20+0xD0);qcopy(next,(char *)&D_00189E20+0xE0);}
        else {qcopy(next,out);out->next[2]+=0.6f;qcopy(previous,next);}
    } else {out->moby=0;qzero(out);qzero(velocity);qzero(next);qzero(previous);}
    out->result=result;
    return result;
}
