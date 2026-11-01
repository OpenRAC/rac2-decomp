#include "include_asm.h"

#include "common.h"
typedef int Quad __attribute__((mode(TI)));
#define V(offset) ((char *)&D_00189E20+(offset))
typedef struct {
char pad0[268];
float field10c;
char pad110[8];
float field118;
char pad11c[64];
float field15c;
char pad160[16];
float field170;
float field174;
float field178;
float field17c;
float field180;
float field184;
char pad188[104];
s16 field1f0;
char pad1f2[114];
float field264;
char pad268[4];
int field26c;
char pad270[23];
u8 field287;
char pad288[148];
float field31c;
char pad320[616];
int field588;
char pad58c[7432];
int field2294;
char pad2298[4];
int field229c;
} Resident;
extern Resident D_00189E20;
extern void func_PAL_L00_002D4668(int,void *,void *);
extern float func_L00_002D3A58(char *);
extern float func_L00_002D3B00(char *);
extern void func_L00_002D3BD8(char *,char *,float);
extern void func_L00_002D3B58(Quad *,Quad *,float);
extern float func_00282E20(void *);
extern void func_00282F70(void *,void *,float);
extern float func_00282DF0(void *);
extern void func_00282F20(void *,void *,float);
extern void func_00282CC0(void *,void *,void *);
extern void func_00282CF0(void *,void *,void *);
extern void func_00282C88(Quad *);
extern float func_00282DB0(void *,void *);
extern void func_00282D30(void *,void *,float);
extern void func_L00_002B5A88(void);
extern void func_L09_002B7238(void);
extern void func_PAL_L00_002B5178(void);
extern void func_L00_002D3960(char *,char *);
extern float func_L00_002B5590(void *);

void func_PAL_L16_002B5D88(void)
{
    float oldPosition[4],horizontal[4],vertical[4];
    float limit,saved;
    qcopy(oldPosition,V(0x80));
    func_PAL_L00_002D4668(D_00189E20.field588,V(0x100),V(0x90));
    if (D_00189E20.field2294==0x14 || D_00189E20.field2294==0x5B || D_00189E20.field2294==0x58 || D_00189E20.field2294==0x81) {
        if (D_00189E20.field1f0==0 && func_L00_002D3A58(V(0xF0))>D_00189E20.field264-0.02f)
            func_L00_002D3BD8(V(0xF0),V(0xF0),D_00189E20.field264-0.02f);
        if (func_L00_002D3B00(V(0xF0)) < -D_00189E20.field31c) {
            limit=-D_00189E20.field31c-0.02f;
            if (limit>0.0f) limit=0.0f;
            func_L00_002D3B58((Quad *)V(0xF0),(Quad *)V(0xF0),limit);
        }
    } else if (D_00189E20.field229c==15) {
        if (D_00189E20.field1f0==0 && func_00282E20(V(0xF0))>D_00189E20.field264-0.02f)
            func_00282F70(V(0xF0),V(0xF0),D_00189E20.field264-0.02f);
    } else {
        if (D_00189E20.field229c==13) goto moved;
        if (D_00189E20.field229c==14) goto moved;
        if (D_00189E20.field1f0==0 && func_00282DF0(V(0xF0))>D_00189E20.field264-0.02f)
            func_00282F20(V(0xF0),V(0xF0),D_00189E20.field264-0.02f);
    }
moved:
    func_00282CC0(V(0x80),V(0x80),V(0xF0));
    func_00282CC0(V(0x80),V(0x80),V(0xA60));
    func_00282C88((Quad *)V(0xA60));
    D_00189E20.field287=0;
    D_00189E20.field26c=0;
    if (func_00282DF0(V(0x100))<=0.0001f) {
        func_L00_002B5A88();
        func_L09_002B7238();
        func_00282CF0(V(0x110),V(0x80),oldPosition);
        func_PAL_L00_002B5178();
    } else func_L09_002B7238();
    func_00282CF0(V(0x120),V(0x80),oldPosition);
    qcopy(V(0x140),V(0x120));
    qcopy(V(0x130),V(0x120));
    func_00282F20(V(0x120),V(0x120),1.0f);
    { float dot;
    dot=func_00282DB0(V(0x120),V(0xF0));
    if (dot<0.0f) dot=0.0f;
    func_00282F20(V(0x120),V(0xF0),dot);
    }
    qcopy(horizontal,V(0xF0));
    func_L00_002D3960((char *)horizontal,(char *)horizontal);
    func_L00_002D3960(V(0x140),V(0x140));
    func_00282F20(V(0x140),V(0x140),1.0f);
    { float dot;
    dot=func_00282DB0(V(0x140),horizontal);
    if (dot<0.0f) dot=0.0f;
    func_00282F20(V(0x140),horizontal,dot);
    }
    qcopy(vertical,V(0xF0));
    func_L00_002D3BD8((char *)vertical,(char *)vertical,0.0f);
    func_L00_002D3BD8(V(0x130),V(0x130),0.0f);
    func_00282F20(V(0x130),V(0x130),1.0f);
    { float dot;
    dot=func_00282DB0(V(0x130),vertical);
    if (dot<0.0f) dot=0.0f;
    func_00282F20(V(0x130),vertical,dot);
    }
    D_00189E20.field170=func_00282DF0(V(0x120));
    D_00189E20.field174=func_L00_002D3A58(V(0x120));
    *(Quad *)horizontal=*(Quad *)V(0x120);
    D_00189E20.field178=func_L00_002B5590(horizontal);
    D_00189E20.field180=func_L00_002D3B00(V(0x120));
    if (D_00189E20.field178<0.0f) D_00189E20.field178=0.0f;
    qcopy(horizontal,V(0x80));
    if (func_00282DF0(V(0x100))>0.0001f) {
        func_00282CC0(V(0x80),V(0x80),V(0x100));
        saved=D_00189E20.field10c;
        func_00282C88((Quad *)V(0x100));
        D_00189E20.field10c=saved;
        func_L00_002B5A88();
        func_L09_002B7238();
        func_00282CF0(V(0x110),V(0x80),oldPosition);
        func_PAL_L00_002B5178();
    }
    func_00282CF0(V(0x150),V(0x80),horizontal);
    D_00189E20.field184=func_00282DF0(V(0x150));
    D_00189E20.field15c=D_00189E20.field10c;
    D_00189E20.field10c=0.0f;
    func_00282CF0(V(0x110),V(0x80),oldPosition);
    D_00189E20.field17c=0.0f;
    if (D_00189E20.field174>0.004f) {
        D_00189E20.field17c=D_00189E20.field118/D_00189E20.field174;
        if (D_00189E20.field17c>0.5f) D_00189E20.field17c=0.5f;
        else if (D_00189E20.field17c<-0.5f) D_00189E20.field17c=-0.5f;
    }
    if (D_00189E20.field170>1.0400001f) {
        func_00282D30(V(0x110),V(0x110),1.0400001f/D_00189E20.field170);
        D_00189E20.field170=1.0400001f;
    }
}
