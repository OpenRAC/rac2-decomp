/* functional: medium. Near-miss draft of retail size with the same frame: differences are allocation and scheduling, with some block order; paths the captured calls never take are unproven. */
/*
 * Tier: sol-high, task v1034. USA v1.01, 0/5 places.
 * Profile: -O2 -G8 -ffunction-sections -fno-cse-follow-jumps.
 * Retained candidate: 1436/1416 bytes. The default-profile earlier draft is
 * 1416/1416 bytes but has the wrong GPR/FPR allocation. Disabling CSE following
 * jumps restores the 0x120 frame, s4 object, s3 state and s2/s5 position and
 * s0/s6 next-position aliases. Independent particle-size values restore the
 * retail FPR roles. Remaining: duplicated query-call tails (retail shares the
 * last four operations), switch-case argument setup and call scheduling.
 * -fno-gcse did not remove the extra f28; -fno-cse-skip-blocks adds nothing to
 * -fno-cse-follow-jumps. A combined query call shrinks to 1392 bytes and loses
 * retail's duplicated argument setup. Copy-helper/profile variants did not
 * resolve allocation; repeating the real destroy/return tail improves the
 * query-argument setup, but does not merge the query calls. No linked claim.
 * All declarations required to retry are below. Next: query-tail block layout
 * and the genuine CSE boundary; do not repeat the measured flag probes.
 */
#include "common.h"
extern float func_00283B98(float,float);
extern void func_00282C88(void *);
extern void func_002833F0(void *,void *);
extern void func_00282CC0(void *,void *,void *);
extern void func_00282D30(void *,void *,float);
extern void func_002A8C00(void *,int,int,void *,float);
extern int func_002761F8(void *,void *,int,void *,void *);
extern int func_00277258(void *,int,void *,float);
extern int D_L00_001BF218 NOT_SDA;
extern int D_L00_001B0518 __attribute__((sda));
extern char D_L00_001A8F20[];
extern int func_002A8C28(int,float,void *,int,float,float,int,int,int);
extern void func_002A7750(void *,int,int);
extern void func_002AD330(void *,int,void *,void *);
extern float func_002A7878(float,float);
extern float func_002A78D8(float,float);
extern void *func_002C65A0(void *,void *,float,float,float,int,int,int,int,int,int);
extern void func_002AD0E0(void *,int,void *,void *,void *,void *);
extern void func_002AD250(void *,int,void *,void *);
extern void func_002ABBB8(void *,void *,void *,float,float,int,int,int,float,float,float,float,int,float,int,int,int,int,int);
extern void func_0029F338(void *);
extern void func_L00_002E6EF8(void *,void *);
extern void func_L00_003DFDC0(void *);
void func_L00_003DF710(char *m)
{
    float scale[4], next[4]; char hit[48];
    float velocity[4], zero[4], pos[4];
    char *d=*(char **)(m+0x68);
    float size0, size1, size2, spread;
    switch(*(unsigned char *)(m+0x20)) {
    case 0:
        *(float *)(d+0x18)=func_00283B98(*(float *)(d+0x18),*(float *)(d+0x1c));
        func_00282C88(scale);
        scale[1]=*(float *)(d+0x18)*0.25f;
        scale[0]=*(float *)(d+0x18)*0.5f;
        scale[2]=*(float *)(d+0x18);
        func_002833F0(m+0xc0,scale);
        func_00282CC0(next,m+0x10,d);
        func_002A8C00(hit,*(int *)(d+0x10),1,d,*(float *)(d+0x14));
        *(unsigned short *)(hit+0x1a)=*(unsigned short *)(m+0xaa);
        if(func_002761F8(m+0x10,next,0,m,hit) || func_00277258(m+0x10,0,m,0.3f)) {
            if (D_L00_001BF218) {
                if (D_L00_001BF218 != *(int *)(d+0x10))
                    func_002A8C28(*(int *)(d+0x10),0.3f,m+0x10,0x10001,*(float *)(d+0x14),0,0,1,0);
                func_002A7750(m,1,-1);
                return;
            } else {
                func_002A8C28(*(int *)(d+0x10),0.3f,m+0x10,0x10001,*(float *)(d+0x14),0,0,1,0);
            }
            func_002A7750(m,1,-1);
            return;
        }
        qcopy(m+0x10,next);
        func_00282D30(velocity,d,-0.5f);
        func_00282C88(zero);
        if(*(int *)(d+0x24)) {
            func_002AD330(m,*(int *)(d+0x24),m+0x10,pos);
            func_00282CC0(velocity,velocity,pos);
        }
        size0=func_002A7878(1,1.5f)*(*(float *)(d+0x20)*210000.0f);
        spread=func_002A7878(0.2f,0.4f);
        func_002C65A0(m+0x10,velocity,size0,spread*(*(float *)(d+0x20)*210000.0f),0,5,D_L00_001B0518,3,0x4f,0,0);
        qcopy(pos,m+0x10);
        pos[0]+=func_002A78D8(0,0.15f); pos[1]+=func_002A78D8(0,0.15f); pos[2]+=func_002A78D8(0,0.15f);
        size1=func_002A7878(1,1.5f)*(*(float *)(d+0x20)*210000.0f);
        spread=func_002A7878(0.1f,0.3f);
        func_002C65A0(pos,velocity,size1,spread*(*(float *)(d+0x20)*210000.0f),0,5,D_L00_001B0518,7,0x5f,0,0);
        pos[0]+=func_002A78D8(0,0.15f); pos[1]+=func_002A78D8(0,0.15f); pos[2]+=func_002A78D8(0,0.15f);
        size2=func_002A7878(1,1.5f)*(*(float *)(d+0x20)*210000.0f);
        spread=func_002A7878(0.2f,0.4f);
        func_002C65A0(pos,velocity,size2,spread*(*(float *)(d+0x20)*210000.0f),0,5,D_L00_001B0518,12,0x7f,0,0);
        if(*(int *)(d+0x24)) {
            func_002AD0E0(m,*(int *)(d+0x24),m+0x10,m+0xf0,m+0x10,m+0xf0);
            func_002AD250(m,*(int *)(d+0x24),d,d);
        }
        break;
    case 1:
        func_002ABBB8(m,D_L00_001A8F20,m+0x10,0,0,10,0,16,0,0,9,1,-1,15,0,9,-1,0,0x810001);
        func_0029F338(m);
        return;
    }
    if(*(float *)(d+0x20)<1) *(float *)(d+0x20)+=0.025f;
    *(float *)(m+0x2c)=func_002A7878(0.01f,0.0125f)* *(float *)(d+0x20);
    func_L00_002E6EF8(func_L00_003DFDC0,m);
}
