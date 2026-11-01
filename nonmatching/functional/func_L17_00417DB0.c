/* functional: medium. Near-miss draft of retail size with the same frame: differences are allocation and scheduling, with some block order; paths the captured calls never take are unproven. */
/* 30 October 2026 retained ordinary C; no linked match or semantic proof.
 * Profile: -O2 -G8 -ffunction-sections.
 * us: 17_smolg: 1520 bytes, expected 1540.
 * us2: func_L17_00417DB0 is in neither catalogue of us2.
 * pal: func_L17_00417DB0 is in neither catalogue of pal.
 * Complete prerequisite-list/message gate and both progress-action paths. Corrected root is
 * incomplete array of short** entries, not a short*** pointer object. Preserve actual bit-
 * index >>2, all nested list lookups and debug call arguments.1520/1540 bytes; frame0x60
 * instead of0x50 and traversal/saved-value allocation differ. Current corrected entry00417DB8;
 * USA only.
 */
#include "common.h"
typedef int Q __attribute__((mode(TI)));
typedef union { Q q; float f[4]; } Vec;
#define I(p,o) (*(int *)((char *)(p)+(o)))
#define F(p,o) (*(float *)((char *)(p)+(o)))
#define P(p,o) (*(char **)((char *)(p)+(o)))
#define H(p,o) (*(short *)((char *)(p)+(o)))
#define U(p,o) (*(u8 *)((char *)(p)+(o)))
#define S(p,o) (*(signed char *)((char *)(p)+(o)))
extern u8 D_001A7BC8[],D_0019B2E8[],D_00189E20[];
extern u32 D_00139768[];
extern int D_001A79F0 __attribute__((sda));
extern int D_L17_001A8F00 __attribute__((sda)),D_L17_001B2748;
extern short **D_L17_002A0E60[];
extern char *D_L17_001B2D0C __attribute__((sda));
extern char D_L17_001BFDC0[],D_L17_001B1D80[],D_L17_002A4140[];
extern void func_0029F338(void *),func_002A7750(void *,int,int);
extern int func_002B38B8(void *),func_002ACBC8(void *,int),func_00288AA0(void *,int),func_00288BE8(void *);
extern void func_0026FEB8(const char *,...);
extern void func_002F5CC8(void);
extern int func_002F5D10(void);
extern void func_L00_002B9D60(void *,void *,int,int);
extern void func_002AD7B8(int),func_002AF0A8(int),func_002A0430(unsigned int),func_002DF3F8(void *,void *),func_00288CB0(int,int);
extern int func_0029B3E0(int,int);
/* Runs a prerequisite-message gate and commits the associated scene/progress action. */
void func_L17_00417DB0(char *object)
{
    char *state=P(object,0x68),*record;
    short *items;
    int complete,none,i,id=-1,changed,phase=U(object,0x20),level,group,index;
    switch(phase) {
    case 0:
        if((S(state,9)!=-1 && D_001A7BC8[S(state,9)]) || (U(object,0xb0)!=255 && (D_0019B2E8[U(object,0xb0)+(D_001A79F0<<4)]&128))) {func_0029F338(object);return;}
        func_002A7750(object,1,-1);
        /* fall through */
    case 1:
        if(!U(state,0xa) && !func_002B38B8(object) && !U(object,0xbc)) break;
        U(state,0xa)=1;func_002A7750(object,2,-1);break;
    case 2:
        if(!U(state,0xa)) {func_002A7750(object,1,-1);break;}
        if(I(D_00189E20,0x2294)==28 || I(D_00189E20,0x24cc)<=0 || D_L17_001A8F00) break;
        if(I(state,0)!=-1 && !func_002ACBC8(D_00189E20+0x80,I(state,0))) break;
        level=D_001A79F0;group=U(state,8);complete=1;none=1;
        if(D_L17_002A0E60[level] && D_L17_002A0E60[level][group] && D_L17_002A0E60[level][group][0]!=-1) {
            none=0;
            for(i=0;D_L17_002A0E60[D_001A79F0][U(state,8)][i]!=-1;i++) {
                id=D_L17_002A0E60[D_001A79F0][U(state,8)][i];
                if(!U(state,0xd) && (D_00139768[(unsigned)id>>2]&(1u<<(id&31)))) continue;
                if(!func_00288AA0(D_L17_001BFDC0,id)) {
                    if(!i) {func_0026FEB8(D_L17_002A4140,H(object,0xaa),H(object,0xb2),D_001A79F0,U(state,8),id);return;}
                    complete=0;
                }
            }
        }
        if(none) func_0026FEB8(D_L17_001B1D80,D_001A79F0,U(state,8));
        if(complete) {U(state,0xf)=0;func_002A7750(object,4,-1);}
        else {
            U(state,0xf)=1;func_00288BE8(D_L17_001BFDC0);
            if(D_L17_001B2748>=5 && D_001A79F0==6 && !U(state,8)) func_002F5CC8();
            func_002A7750(object,3,-1);
        }
        break;
    case 3:
        if(!func_002F5D10()) {
            if(I(state,4)!=-1) {record=D_L17_001B2D0C+I(state,4)*128;func_L00_002B9D60(record+0x30,record+0x70,0,1);}
            func_002A7750(object,4,-1);
        }
        if(D_001A79F0 || S(state,9)==-1 || func_002F5D10()) break;
        changed=0;
        if(S(state,9)!=-1) {func_002AD7B8(S(state,9));changed=1;if(S(state,9)!=24) func_002AF0A8(S(state,9));}
        if(U(object,0xb0)!=255 && !(D_0019B2E8[U(object,0xb0)+(D_001A79F0<<4)]&128)) {changed=1;func_002A0430(U(object,0xb0));}
        if(S(state,0xb)) {
            if(I(state,0xc)&0xffff0000) {
                if(I(state,4)!=-1) {record=D_L17_001B2D0C+I(state,4)*128;func_002DF3F8(record+0x30,record+0x70);}
                else func_002DF3F8(object+16,object+0xf0);
            }
        }
        if(S(state,0xc)!=-1) func_00288CB0(S(state,0xc),1);
        else if(changed || U(state,0xf)) func_0029B3E0(0,-1);
        break;
    case 4:
        changed=0;
        if(S(state,9)!=-1) {func_002AD7B8(S(state,9));changed=1;if(S(state,9)!=24) func_002AF0A8(S(state,9));}
        if(U(object,0xb0)!=255 && !(D_0019B2E8[U(object,0xb0)+(D_001A79F0<<4)]&128)) {changed=1;func_002A0430(U(object,0xb0));}
        if(S(state,0xb)>0 && (I(state,0xc)&0xffff0000)) {
            if(I(state,4)!=-1) {record=D_L17_001B2D0C+I(state,4)*128;func_002DF3F8(record+0x30,record+0x70);}
            else func_002DF3F8(D_00189E20+0x80,D_00189E20+0x90);
        }
        if(S(state,0xc)!=-1) func_00288CB0(S(state,0xc),1);
        else if((changed || U(state,0xf)) && S(state,0xb)!=-1) func_0029B3E0(0,-1);
        func_0029F338(object);break;
    }
}
