/* Opus 5.5 xhigh, task v1727, USA v1.01, one Tabora placement.
 * Best check.py: 812/812 bytes, 0/1 places; 15 instructions differ (all listed below).
 * Profile (dedicated unit): -O2 -G0 -ffunction-sections -fno-gcse -frac2-qcopy
 *   -frac2-qcopy-barrier -frac2-zero-ti-barrier. Declarations are included below.
 * Recovered: 0x110 frame, position spilled at sp+0x50, a/inherited/count in s6/s7/s5, in-loop
 * addiu a2,a+0xC0 (gcse's PRE hoists it, hence -fno-gcse), direct addiu a0,sp+0x30, the
 * hoisted fp = sp+0x30 for sq $zero (the nested inline gives its pseudo life 3; life 2 is "not
 * desirable" to the loop pass at 130 real insns), and daddu a1,s3 at the particle call (v2).
 * Remaining: e (extra's address, retail s4) is local to its block here, so local-alloc gives it
 * s2 and motion/vel rotate to s3/s4; its set also schedules after addiu a0/lw a2, not first.
 * Retail's order motion s2, vel s3, e s4, count s5 needs e global with REG_N_REFS 4 (one set and
 * one use in the loop, 8/life just under vel's 27/121, so life >= 36), yet not hoisted.
 * Evidence against the alternatives, all measured:
 * - a single set at the join with no other mention is hoisted and merges with the clear's fp;
 * - sets in both arms give refs 6 (12/35, ahead of motion, so s2), and in the if arm cse reuses
 *   the argument's pseudo (daddu) unless that pseudo is a pre-loop variable (x0), which then
 *   takes fp from the clear's pseudo;
 * - e = extra before the loop is reused as a copy source, whose REG_EQUIV doubles the clear
 *   pseudo's live length so position wins fp; e = 0 is dead at flow, which leaves e local;
 * - -g changes nothing; a helper inline holding the loop tail hoists pos and is further off.
 * e = 0 here is that dead initializer: it only keeps the loop pass from moving e's set.
 * Next: find a source shape that puts a real block boundary between e's set and the call, or
 * another use removed after flow. A surviving placeholder branch is forbidden for now; if (e)
 * folds away before the loop pass and if (remaining) x = 0 if-converts, so neither helped.
 * Forms measured and no closer: e[3] = tail (store through a register), named clear pointer.
 *
 * Differences (mine | retail), jal targets aside:
 *   004250A4 addiu s4,sp,0x20 | addiu s3,sp,0x20      004251A8 daddu a1,s4 | daddu a1,s3
 *   004250B0 addiu s3,sp,0x40 | addiu s2,sp,0x40      004251B0 daddu a2,s3 | daddu a2,s2
 *   0042514C daddu a0,s4 | daddu a0,s3                004251C8 daddu a1,s3 | daddu a1,s2
 *   00425184 sq v0,0(s3) | sq v0,0(s2)                004251D0 addiu a0,sp,0x10 | addiu s4,sp,0x30
 *   00425194 daddu a0,s3 | daddu a0,s2                004251D8 addiu a0,sp,0x10 | addiu s4,sp,0x30
 *   004251A4 daddu a0,s4 | daddu a0,s3                004251DC lw a2,0x50(sp) | addiu a0,sp,0x10
 *   004251E0 addiu s2,sp,0x30 | lw a2,0x50(sp)        00425278 daddu a2,s2 | daddu a2,s4
 *   00425288 daddu a1,s4 | daddu a1,s3

 *
 * Opus 5.5 xhigh, task v2176 (rechecked here: still 812/812 bytes, 0/1 places, 15 differ).
 * Overseer's lead (a vanished real test as the block boundary) partly works. Any test placed
 * right after `e = extra;` (join, before the func_00282CC0 argument setup), with `v2 = vel;`
 * moved after it, makes e global, unhoisted and scheduled first at the join. E.g. the forbidden
 * placeholder `if (remaining) {x=3;y=4;} else {x=5;y=6;}` (dead x/y; jump2 removes it) leaves
 * 812 bytes and 13 rows: a pure s2/s3/s4 rotation (e s2, motion s3, vel s4 | retail motion s2,
 * vel s3, e s4). Schedule, s5 count, s6 a, s7 inherited and fp all match.
 * The priority model says the vanished region needs 2 more flow1 insns on count (refs 9) to give
 * retail's order; two placeholder tests on remaining raise count's refs so it takes s2 (worse).
 * No mode global fits: retail loads nothing there; nearby Tabora code tests only a+0x20.
 * Tests on a, inherited, e or vel fold or misorder; e set inside both arms gives e s2 (worse).
 * Next: a real count-based condition (arms differing in source) right after e = extra.
 */
#include "common.h"
typedef unsigned int u128 __attribute__((mode(TI)));
static __inline__ void vzero(float *v) {
    qzero(v);
}
extern float func_002A7878(float,float);
extern float func_00283180(float);
extern float func_00283198(float);
extern float func_00282DF0(void *);
extern void func_00283098(void *,void *,void *);
extern void func_00282F20(void *,void *,float);
extern void func_00282D30(void *,void *,float);
extern void func_00282CC0(void *,void *,void *);
extern int func_00283CF0(float);
extern int func_001163B0(void);
extern char *func_002BAA28(void *,void *,void *,int,int,int,int,int,int);
void func_L08_00424FF8(char *a,float *position,int count,float speed,float lift,float maxradius,float minradius,float size,float tail) {
    float pos[4] __attribute__((aligned(16)));
    float vel[4] __attribute__((aligned(16)));
    float extra[4] __attribute__((aligned(16)));
    float motion[4] __attribute__((aligned(16)));
    char *q=*(char **)(a+0x68);
    float f,r;
    int x,y,z;
    int remaining;
    float *inherited;
    char *p;
    float *e = 0;
    float *v2;
    if(count<=0)return;
    inherited=(float *)(q+0xD0);
    remaining=count;
    do {
        f=func_00283180(func_002A7878(-3.1415927f,3.1415927f));
        f*=func_002A7878(minradius,maxradius);
        pos[0]=f;
        f=func_00283198(func_002A7878(-3.1415927f,3.1415927f));
        f*=func_002A7878(minradius,maxradius);
        pos[1]=f;
        pos[2]=0;
        func_00283098(pos,pos,a+0xC0);
        r=func_00282DF0(pos);
        r=speed*((maxradius-r)*0.016666668f)/maxradius;
        func_00282F20(vel,pos,func_002A7878(r*0.25f,r));
        vel[2]+=func_002A7878(lift*0.25f,lift)*0.016666668f;
        if(*(u8 *)(a+0x20)==5) {
            *(u128 *)motion=*(u128 *)inherited;
            motion[2]=0;
            func_00282D30(motion,inherited,0.8f);
            func_00282CC0(vel,vel,motion);
            func_00282D30(extra,motion,0.4f);
        } else vzero(extra);
        v2=vel;
        e=extra;
        func_00282CC0(pos,pos,position);
        pos[2]+=-0.75f;
        vel[3]=size;
        extra[3]=tail;
        x=func_00283CF0(func_002A7878(15.0f,25.0f));
        y=func_00283CF0(func_002A7878(20.0f,40.0f));
        z=func_00283CF0(func_002A7878(50.0f,70.0f));
        p=func_002BAA28(pos,v2,e,0x70204050,0x7F7F7F,x,y,z,-1);
        if(p && (func_001163B0()&1))p[3]=0x48;
    }while(--remaining);
}
