/* functional: medium. Near-miss draft of retail size with the same frame: differences are allocation and scheduling, with some block order; paths the captured calls never take are unproven. */
/* opus-1 (v1302, 2026-10-29). Best check.py: 864/864 bytes, 0/1 places (USA v1.01),
 * 8 non-relocation instructions differ. Built as a -G8 unit of its own
 * (e.g. src/levels/03_endako/L03_003C7AC0-g8.c, default -O2 -G8 -ffunction-sections).
 * New since the sol-high draft: each sound-slot test gets its own block-scoped entry
 * pointer; one shared `entry` variable crossed all three sites, conflicted with $v1/$a0
 * and went to $v0, changing the table adds and the bne/bnel choices (12 instructions).
 * What still differs: at the two join blocks before func_00282D30(a, a, f * (1/60)) and
 * func_002AC9F8(b, f * (1/3600)) retail moves $a0 before the li.s of the constant into
 * $f12; cc1 issues the li.s (memory unit, longest path) first in the same cycle. The
 * no-held-object path of the second call, whose block also loads the float, matches.
 * Selection wording (if/else, default-then-override, ?:, inverted test), -g and the
 * scheduling-pass switches do not change it. Needs evidence for what kept the constant
 * load behind the argument move. Declarations are below. */
#include "common.h"
typedef int TI128 __attribute__((mode(TI)));
extern float D_L03_001B01BC __attribute__((sda)),D_L03_001B01A4 __attribute__((sda)),D_L03_001B01B4 __attribute__((sda)),D_L03_001B01AC __attribute__((sda));
extern float D_L03_001B01A8 __attribute__((sda)),D_L03_001B01B8 __attribute__((sda)),D_L03_001B01B0 __attribute__((sda));
extern u8 D_L03_001B01D4 __attribute__((sda));
extern float D_L03_001B9998 NOT_SDA, D_L03_001BFDE8 NOT_SDA;
typedef struct { float vec[4]; char pad[0x2d4]; int mode; } PlayerState;
extern PlayerState D_0018BDD0;
typedef struct { char pad[0x74]; u8 active; char pad75[0x13]; char *owner; } L03ControlEntry;
extern u8 D_00188660[];
extern float func_00283B98(float,float);
extern void func_002833F0(void *,void *);
extern float func_00282DF0(void *);
extern int func_002E5CF8(int,int,void *);
extern void func_002E59F8(int);
extern void func_00283098(void *,void *,void *);
extern void func_00282D30(void *,void *,float);
extern void func_00282C88(void *);
extern void func_00282CF0(void *,void *,void *);
extern void func_002AC9F8(void *,float);
extern void func_00282CC0(void *,void *,void *);
extern void func_002C9218(int,void *,void *,float);
extern void func_0029FCC0(void *,int,void *);
extern int func_002761F8(void *,void *,int,void *,int);
extern void func_002A93B0(void *);
void func_L03_003C7AC0(char *obj)
{
    float a[4],b[4],c[4];
    union { float m[12]; struct { float pad[4], d[4]; } v; } scratch;
    char *state=*(char **)(obj+0x68);
    char *other;
    float f;
    int id;
    if(*(u8 *)(obj+0x20)==2) {
        *(TI128 *)c=0;
        c[2]=func_00283B98(D_L03_001B9998,D_L03_001B01BC*0.017453294f);
        *(TI128 *)(b)=*(TI128 *)(c);
        func_002833F0(scratch.m,b);
        qcopy(a,D_0018BDD0.vec);
        if(func_00282DF0(a)>0.0f && D_0018BDD0.mode==0x31) {
            L03ControlEntry *entry=(L03ControlEntry *)(D_00188660+*(int *)(state+0x108)*0x70);
            if(entry->owner!=obj || !entry->active)
                *(int *)(state+0x108)=func_002E5CF8(0,4,obj);
        } else {
            id=*(int *)(state+0x108);
            if(id!=-1) {
                L03ControlEntry *entry=(L03ControlEntry *)(D_00188660+id*0x70);
                if(entry->owner==obj && entry->active) func_002E59F8(id);
            }
            *(int *)(state+0x108)=-1;
        }
        a[0]=-a[0];
        func_00283098(a,a,scratch.m);
        other=*(char **)(state+0xf0);
        if(other) {
            if(*(short *)(other+0xaa)==0xb85) f=D_L03_001B01AC;
            else f=D_L03_001B01B4;
        } else f=D_L03_001B01A4;
        func_00282D30(a,a,f*(1.0f/60.0f));
    } else {
        id=*(int *)(state+0x108);
        if(id!=-1) {
            L03ControlEntry *entry=(L03ControlEntry *)(D_00188660+id*0x70);
            if(entry->owner==obj && entry->active) func_002E59F8(id);
        }
        *(int *)(state+0x108)=-1;
        func_00282C88(a);
    }
    func_00282CF0(b,a,state+0xe0);
    b[2]=0;
    other=*(char **)(state+0xf0);
    if(other) {
        if(*(short *)(other+0xaa)==0xb85) f=D_L03_001B01B0;
        else f=D_L03_001B01B8;
        func_002AC9F8(b,f*0.000277777785f);
    } else {
        func_002AC9F8(b,D_L03_001B01A8*0.000277777785f);
    }
    func_00282CC0(state+0xe0,state+0xe0,b);
    func_00282CC0(obj+0x10,obj+0x10,state+0xe0);
    func_002C9218(*(int *)state,obj+0x10,obj+0x10,1.25f);
    func_0029FCC0(obj,2,c);
    qcopy(scratch.m,c);
    scratch.m[2]+=20.0f;
    qcopy(scratch.v.d,c);
    scratch.v.d[2]+=0.5f;
    if(func_002761F8(scratch.v.d,scratch.m,2,obj,0)) *(float *)(state+0xf4)=D_L03_001BFDE8;
    func_002A93B0(obj);
    *(u8 *)(obj+0xbd)=D_L03_001B01D4;
}
