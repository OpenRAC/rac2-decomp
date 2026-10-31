/* Reconstruction retained 30 October 2026; not a local or linked match.
 * Profile: -O2 -G8 -ffunction-sections.
 * 1296/1340 bytes, retail 0x40 frame retained; notice-history base offsets and load/branch scheduling differ. No-split addressing worsens to1416.
 * Reopen with a measured global statistics record and source lifetime for shared high-half bases; do not repeat tied whole-file profile trials.
 * ABI/bounds: Full 16-byte local point. Counters retain unsigned16 widths; frame differences and notice masks retain unsigned32 semantics. The shared notice helper is genuinely inline C with all calls and updates present.
 * Semantic equivalence has not been validated by the functional gate.
 */
#include "common.h"
typedef float NoticeVector[4] __attribute__((aligned(16)));
typedef struct { u16 count, pad; u32 frame, levels; } NoticeHistory;
extern unsigned char D_00189E20[],D_0018C958[],D_00139572[],D_00139630[],D_0019B2E8[];
extern unsigned char D_L14_002686F0[];
extern unsigned char *D_L14_001B259C __attribute__((sda));
extern NoticeVector D_L14_001A8F20;
extern int D_L14_001A8F00;
extern short D_L14_001B22E4;
extern u32 D_001A7390 MACRO_ADDR;
extern int D_001A79F0 MACRO_ADDR;
extern int func_002ACBC8(void *,int),func_002B3868(void *);
extern void func_002A7750(void *,int,int);
extern void func_002B4090(void *,void *,float,float,float);
extern int func_00288D58(void),func_00287FF8(int,int),func_00288E18(int,int);
extern void func_L08_0030A8F8(int);

/* Records the first level using a notice and refreshes its frame stamp. */
static __inline__ void update_notice(NoticeHistory *n,u32 now,int text,int topic)
{
    if(n->count) {
        if(now-n->frame>=1081 || n->frame==0) func_00288E18(text,topic);
        else if(n->frame<now) n->frame=now;
    } else {
        ++n->count;
        if(n->frame<now) n->frame=now;
        n->levels|=(1U<<D_001A79F0)|0x80000000;
    }
}

/* Tutorial trigger and per-topic reminder history. */
void func_L14_003F4F98(unsigned char *m)
{
    NoticeVector point;
    unsigned char *p=*(unsigned char **)(m+0x68), *other;
    u32 frame,stamp;
    switch(m[0x20]) {
    case 0:
        *(short *)(m+0x96)=0; m[0x30]=255;
        if(*(int *)(p+0x20)>=0) *(void **)(p+0x24)=D_L14_001B259C+*(int *)(p+0x20)*256;
        else *(void **)(p+0x24)=0;
        other=*(unsigned char **)(p+0x24);
        if(D_L14_002686F0[D_00139572[0]*0xe0+4]<2 && other) *(int *)(p+0x28)=1;
        else {
            if(other) { *(u16 *)(other+0x34)|=1; other[0x31]=0; }
            *(int *)(p+0x28)=0;
        }
        func_002A7750(m,1,-1);
        break;
    case 1:
        if(func_002B3868(m)) *(int *)(p+0x18)=0;
        if(func_002ACBC8(D_00189E20+0x80,*(int *)p)
            && D_L14_002686F0[D_00139572[0]*0xe0+4]<2) func_002A7750(m,2,-1);
        if(*(int *)(p+0x28)) {
            qcopy(point,D_L14_001A8F20);
            point[1]-=0.1f;
            func_002B4090(*(void **)(p+0x24),point,0.05f,0,0);
        }
        break;
    case 2:
        if(func_002B3868(m)) *(int *)(p+0x18)=0;
        if(D_L14_001A8F00!=2 && *(int *)(p+0x18)>=6) {
            if(func_00288D58()) func_00287FF8(10,5);
            else func_00287FF8(10,2);
            func_L08_0030A8F8(2);
            other=*(unsigned char **)(p+0x24);
            if(other) { *(u16 *)(other+0x34)|=1; other[0x31]=0; }
            *(int *)(p+0x28)=0;
            func_002A7750(m,1,-1);
        }
        break;
    }
    if(func_002ACBC8(D_00189E20+0x80,*(int *)(p+4)) && !(D_00139630[0]&2)) {
        frame=D_001A7390; stamp=*(u32 *)(D_0018C958+0x628);
        if(frame-stamp>=1081 || !stamp) func_00288E18(0xa2c,0x83);
        else if(stamp<frame) *(u32 *)(D_0018C958+0x628)=frame;
    }
    if(func_002ACBC8(D_00189E20+0x80,*(int *)(p+8))) {
        update_notice((NoticeHistory *)(D_0018C958+0x480),D_001A7390,0xa09,0x60);
        *(u16 *)(D_0018C958+0x48c)=65535;
    }
    if(func_002ACBC8(D_00189E20+0x80,*(int *)(p+12)) && D_L14_001B22E4)
        update_notice((NoticeHistory *)(D_0018C958+0x48c),D_001A7390,0xa0a,0x61);
    if(func_002ACBC8(D_00189E20+0x80,*(int *)(p+0x14))
        && !(D_0019B2E8[D_001A79F0*16+*(int *)(p+0x10)]&128)
        && *(u16 *)(D_0018C958+0x468)<2)
        update_notice((NoticeHistory *)(D_0018C958+0x468),D_001A7390,0xa07,0x5e);
    ++*(int *)(p+0x18);
}
