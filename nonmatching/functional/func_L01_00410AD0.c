/* functional: medium. Near-miss draft, not byte-compared in the latest sweep: paths the captured calls never take are unproven. */
/* Reconstruction retained 30 October 2026; not a linked match.
 * Profile: -O2 -G8 -ffunction-sections.
 * 1508/1540 bytes; frame 0x60 instead of 0x50, switch table, diagnostic varargs and scripted-state allocation differ.
 * Reopen with a real trigger-variable record, reviewed switch-table placement and debug-printer stack argument lifetime.
 * ABI/bounds: Corrected entry is +8 (retail 0x410AD8), current extent 1540 bytes. Signed byte item fields, signed-short sentinels and exact observed bitset indexing retained. Diagnostic helper is variadic; message queue helper returns int.
 * Local checks and release presence are recorded in the shared NMC index.
 * Semantic equivalence has not been validated by the functional gate.
 */
#include "common.h"
extern unsigned char D_00189E20[], D_001A7BC8[], D_0019B2E8[];
extern int D_001A79F0 MACRO_ADDR;
extern int D_L01_001A8F40 __attribute__((sda));
extern short **D_L01_002A17A0[];
extern u32 D_00139768[];
extern unsigned char D_L01_001BF6C0[], D_L01_001B1830[], D_L01_002A50F0[];
extern unsigned char *D_L01_001B264C __attribute__((sda));
extern int D_L01_001B2088;
extern void func_0029F338(void *),func_002A7750(void *,int,int);
extern int func_002B38B8(void *),func_002ACBC8(void *,int);
extern int func_00288AA0(void *,int),func_00288BE8(void *);
extern void func_0026FEB8(void *,...);
extern void func_002F5CC8(void);
extern int func_002F5D10(void);
extern void func_L00_002B9D60(void *,void *,int,int);
extern void func_002AD7B8(int),func_002AF0A8(int),func_002A0430(int);
extern void func_002DF3F8(void *,void *),func_00288CB0(int,int);
extern int func_0029B3E0(int,int);

/* Script trigger: queues prerequisite messages, activates its event/camera,
 * then performs the requested item, checkpoint and save transitions. */
void func_L01_00410AD0(unsigned char *m)
{
    unsigned char *p=*(unsigned char **)(m+0x68), *pose;
    int all, missing, i, id, changed;
    switch(m[0x20]) {
    case 0:
        if(((signed char *)p)[9]!=-1 && D_001A7BC8[((signed char *)p)[9]]) { func_0029F338(m); break; }
        if(m[0xb0]!=255 && (D_0019B2E8[D_001A79F0*16+m[0xb0]]&128)) { func_0029F338(m); break; }
        func_002A7750(m,1,-1);
    case 1:
        if(p[10] || func_002B38B8(m) || m[0xbc]) { p[10]=1; func_002A7750(m,2,-1); }
        break;
    case 2:
        if(!p[10]) { func_002A7750(m,1,-1); break; }
        if(*(int *)(D_00189E20+0x2294)==28 || *(int *)(D_00189E20+0x24cc)<=0 || D_L01_001A8F40) break;
        if(*(int *)p!=-1 && !func_002ACBC8(D_00189E20+0x80,*(int *)p)) break;
        all=1; missing=1;
        if(D_L01_002A17A0[D_001A79F0] && D_L01_002A17A0[D_001A79F0][p[8]]
            && D_L01_002A17A0[D_001A79F0][p[8]][0]!=-1) {
            missing=0;
            for(i=0;(id=D_L01_002A17A0[D_001A79F0][p[8]][i])!=-1;++i) {
                if(!p[13] && (D_00139768[(u32)id>>2]&(1U<<(id&31)))) continue;
                if(!func_00288AA0(D_L01_001BF6C0,id)) {
                    if(i==0) {
                        func_0026FEB8(D_L01_002A50F0,*(short *)(m+0xaa),*(short *)(m+0xb2),D_001A79F0,p[8],id);
                        return;
                    }
                    all=0;
                }
            }
        }
        if(missing) func_0026FEB8(D_L01_001B1830,D_001A79F0,p[8]);
        if(all) { p[15]=0; func_002A7750(m,4,-1); }
        else {
            p[15]=1; func_00288BE8(D_L01_001BF6C0);
            if(D_L01_001B2088>=5 && D_001A79F0==6 && !p[8]) func_002F5CC8();
            func_002A7750(m,3,-1);
        }
        break;
    case 3:
        if(!func_002F5D10()) {
            if(*(int *)(p+4)!=-1) {
                pose=D_L01_001B264C+*(int *)(p+4)*128;
                func_L00_002B9D60(pose+0x30,pose+0x70,0,1);
            }
            func_002A7750(m,4,-1);
        }
        if(D_001A79F0 || ((signed char *)p)[9]==-1 || func_002F5D10()) break;
        changed=0;
        if(((signed char *)p)[9]!=-1) {
            func_002AD7B8(((signed char *)p)[9]); changed=1;
            if(((signed char *)p)[9]!=24) func_002AF0A8(((signed char *)p)[9]);
        }
        if(m[0xb0]!=255 && !(D_0019B2E8[D_001A79F0*16+m[0xb0]]&128)) {
            func_002A0430(m[0xb0]); changed=1;
        }
        if(((signed char *)p)[11]) {
            if(*(u32 *)(p+12)&0xffff0000) {
                if(*(int *)(p+4)!=-1) {
                    pose=D_L01_001B264C+*(int *)(p+4)*128; func_002DF3F8(pose+0x30,pose+0x70);
                }
            } else func_002DF3F8(m+0x10,m+0xf0);
        }
        if(((signed char *)p)[12]!=-1) func_00288CB0(((signed char *)p)[12],1);
        else if(changed || p[15]) func_0029B3E0(0,-1);
        break;
    case 4:
        changed=0;
        if(((signed char *)p)[9]!=-1) {
            func_002AD7B8(((signed char *)p)[9]); changed=1;
            if(((signed char *)p)[9]!=24) func_002AF0A8(((signed char *)p)[9]);
        }
        if(m[0xb0]!=255 && !(D_0019B2E8[D_001A79F0*16+m[0xb0]]&128)) {
            func_002A0430(m[0xb0]); changed=1;
        }
        if(((signed char *)p)[11]>0) {
            if(*(u32 *)(p+12)&0xffff0000) {
                if(*(int *)(p+4)!=-1) {
                    pose=D_L01_001B264C+*(int *)(p+4)*128; func_002DF3F8(pose+0x30,pose+0x70);
                }
            } else func_002DF3F8(D_00189E20+0x80,D_00189E20+0x90);
        }
        if(((signed char *)p)[12]!=-1) { func_00288CB0(((signed char *)p)[12],1); func_0029F338(m); break; }
        if((changed || p[15]) && ((signed char *)p)[11]!=-1) func_0029B3E0(0,-1);
        func_0029F338(m);
        break;
    }
}
