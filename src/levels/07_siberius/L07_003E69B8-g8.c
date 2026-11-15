#include "common.h"
#define INT_AT(p,n) (*(int *)((p)+(n)))
#define U16_AT(p,n) (*(unsigned short *)((p)+(n)))
#define FLOAT_AT(p,n) (*(float *)((p)+(n)))
extern int func_00283CF0(float);
extern int func_002A77E0(int);
extern void func_002A7750(void *,int,int);
extern void func_002A7470(void *,int,int,int);
extern void func_002B0178(void *,void *,void *);
extern float func_00282E48(void *,void *);
extern void func_002A93B0(void *);
extern char *func_002A9640(void *,int,int);
extern int func_002761F8(void *,void *,int,void *,void *);
extern int func_002B0ED8(void *,void *,int);
extern int func_002B3BA8(void *,int,float,float,int,int);
extern void func_00282CC0(void *,void *,void *);
extern void func_L07_003EA2D8(void *,void *,int,int);
extern void func_L07_003EA498(void *,void *);
extern void func_L07_003E6F40(void *);
extern void func_L07_003E7240(void *);
extern float D_L07_001B0B18 __attribute__((sda));
extern unsigned short D_L07_001B0B20 __attribute__((sda));
extern unsigned short D_L07_001B0B24[] __attribute__((sda));
extern int D_L07_001C9780 NOT_SDA;
extern char *D_L07_001B1F40[] __attribute__((sda));
extern char D_L07_001B9200[];
extern char D_00189F70[];

/* Initialize the entity, handle nearby collision targets, and update its animation. */
int func_L07_003E69B8(unsigned char *o)
{
    float from[4] __attribute__((aligned(16)));
    float to[4] __attribute__((aligned(16)));
    unsigned char *p=*(unsigned char **)(o+0x68);
    char *hit;
    float turn;
    if (!o[0x20]) {
        p[0x48]=FloatToInt(15.0f);
        p[0x4A]=FloatToInt(9.6f);
        qcopy(p+0x2F0,o+0x10);
        if (func_002A77E0(2)) U16_AT(o,0x34)|=0x8000;
        else U16_AT(o,0x34)&=0x7FFF;
        p[0x150]=8;
        INT_AT(p,0x188)=3;
        FLOAT_AT(p,0x17C)=0.15f;
        FLOAT_AT(p,0x170)=1.0f;
        FLOAT_AT(p,0x174)=1.0f;
        turn=D_L07_001B0B18;
        turn*=0.017453294f;
        FLOAT_AT(p,0x180)=FLOAT_AT(o,0x18)-3.0f;
        FLOAT_AT(p,0x54)=0.3f;
        FLOAT_AT(p,0x50)=1.0f;
        FLOAT_AT(p,0x60)=3.1415927f;
        if (func_002A77E0(2)) turn=-turn;
        FLOAT_AT(p,0x12C)=turn;
        U16_AT(p,0x132)=D_L07_001B0B20;
        U16_AT(p,0x134)=D_L07_001B0B24[0];
        p[0x2E]=1;
        func_L07_003EA2D8(o,p+0x330,0,2);
        if (FLOAT_AT(o,0x18)>FLOAT_AT((char *)&D_L07_001C9780,0x28)) {
            INT_AT(p,0x350)=1;
            o[0x30]=255;
        }
        FLOAT_AT(o,0x18)+=0.5f;
        func_002B0178(o+0x10,o,o+0x10);
        if (INT_AT(p,0x2B0)!=-1) {
            char *entry=D_L07_001B1F40[0]+INT_AT(p,0x2B0)*0x30;
            if (*(short *)(entry+0x30)) INT_AT(p,0x8C)=**(int **)(entry+0x3C);
            else INT_AT(p,0x8C)=-1;
        }
        if (!INT_AT(p,0x2BC)) {
            INT_AT(o,0x98)=0;
            U16_AT(o,0x34)=(U16_AT(o,0x34)|0x41)&0xEFFF;
            func_002A7750(o,11,4);
            if (o[0x43]) func_002A7470(o,0,0,0);
        } else if (INT_AT(p,0x2B8)==-1) {
            func_002A7750(o,1,0);
            if (o[0x43]!=2) func_002A7470(o,2,0,0);
        } else {
            func_002A7750(o,9,4);
            if (o[0x43]) func_002A7470(o,0,0,0);
        }
    }
    if (o[0x31] && fast_vec_dist(o+0x10,D_L07_001B9200)<24.0f) {
        func_002A93B0(o);
        o[0x6F]=22;
    }
    hit=func_002A9640(o,0x10000,0);
    if (hit && *(char **)(hit+0x20) && fast_vec_dist(*(char **)(hit+0x20)+0x10,o+0x10)<32.0f) {
        qcopy(from,*(char **)(hit+0x20)+0x10);
        from[2]+=0.5f;
        qcopy(to,o+0x10);
        to[2]+=0.5f;
        if (CollLine(from,to,2,o,0)) o[0xA8]=255;
    }
    if (func_002B0ED8(o,p+0x140,0)) {
        func_L07_003E6F40(o);
        if (FLOAT_AT(p,0x20)<=0) {
            func_L07_003E7240(o);
            return 1;
        }
        if (D_L07_001C9780) FLOAT_AT(p,0x180)=0;
    }
    if (p[0x2E]==2) {
        if (p+0x330)
            func_L07_003EA498(o,p+0x330);
        return 1;
    }
    INT_AT(p,0x2D4)=func_002B3BA8(o,INT_AT(p,0x2B0),FLOAT_AT(p,0x2B4),0,0,0);
    if (D_L07_001C9780) FastVecAdd(p+0x210,p+0x210,D_00189F70);
    return 0;
}
