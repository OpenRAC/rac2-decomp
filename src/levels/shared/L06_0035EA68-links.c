#include "common.h"
extern int func_00282948(int *);
extern void func_0029F338(void *);
extern void func_00282F20(void *,void *,float);
extern char *D_L06_001B281C[] __attribute__((sda));
extern int D_001A79F0[] __attribute__((sda));
extern int D_001A79F0_gp SDATA(D_001A79F0);
extern unsigned char D_0019B2E8[], D_0019B4A8[];
extern char D_L06_001AF320[],D_L06_001AF350[],D_L06_001AF380[];
extern void func_0026FEB8(char *,...);
extern float func_00283CE0(int);
extern int func_00283CF0(float);
extern void func_L06_003E11A0(void *,void *);
#define F14(p,o) (*(float *)((char *)(p)+(o)))
#define I14(p,o) (*(int *)((char *)(p)+(o)))
void func_L06_003E1498(unsigned char *m) {
    int count=0,i;
    char *target=0;
    char *v=*(char **)(m+0x68);
    char *links=v+0x18;
    char *link;
    if(I14(v,0x10)!=-1) target=D_L06_001B281C[0]+I14(v,0x10)*256;
    if((unsigned char)m[0xb0]!=255 && (D_0019B2E8[(unsigned char)m[0xb0]+D_001A79F0_gp*16]&128)) goto dispatch;
    if(!(unsigned char)m[0x20]) goto dispatch;
    { int j; char *scan;
    for(j=0;j<5;j++){ scan=links+j*8;
        if(I14(scan,0)!=-1) {
            char *other=D_L06_001B281C[0]+I14(scan,0)*256;
            if(other && *(short *)(other+0xaa)==*(short *)(scan+4) && (unsigned char)other[0x20]!=254 && (unsigned char)other[0x20]!=253) {
                unsigned short bits=*(unsigned short *)(other+0xb2);
                int n=D_0019B4A8[((short)bits>>1)+D_001A79F0[0]*1024];
                if (bits & 1) { if ((n >> 4) & 7) continue; }
                else if (n & 7) continue;
                if(((signed char)scan[6]==-1 || (unsigned char)other[0x20]!=(signed char)scan[6])) count++;
            }
        }
    }
 }
 dispatch:
    switch((unsigned char)m[0x20]) {
    case 0:
        if(target) {
            *(unsigned short *)(v+0x14)=*(unsigned short *)(target+0xaa);
            F14(v,0x44)=func_00283CE0((unsigned char)target[0x23]);
            if(I14(v,8)&0x10) qcopy(m+0x10,target+0x10);
            else if(I14(v,8)&0x40) qcopy(target+0x10,m+0x10);
            if(I14(v,8)&0x20) qcopy(m+0xf0,target+0xf0);
            else if(I14(v,8)&0x80) qcopy(target+0xf0,m+0xf0);
        } else func_0026FEB8(D_L06_001AF320);
        for(i=0,link=links;i<5;i++,link+=8) {
            if(I14(link,0)!=-1){
                char *base = D_L06_001B281C[0];
                char *other=(char *)(I14(link,0)*256+(s32)base);
                unsigned short uid=*(unsigned short *)(other+0xaa);
                *(unsigned short *)(link+4)=uid;
                func_0026FEB8(D_L06_001AF350,((char *)m-base)>>8,i,I14(link,0),(short)uid);
            } else func_0026FEB8(D_L06_001AF380,((char *)m-D_L06_001B281C[0])>>8,i);
        }
        {
            float a=F14(v,0),b=F14(v,4);
            F14(m,0x2c)=(b>a?b:a)*F14(*(char **)(m+0x24),0x24);
        }
        m[0x20]=1;
        *(unsigned short *)(m+0x34)|=0x100;
        break;
    case 1:
        if(!count){
            if(target && (signed char)v[0x16]!=-1) target[0x20]=v[0x16];
            I14(v,0x40)=I14(v,0xc);
            m[0x20]=2;
        }
        func_L06_003E11A0(m,v);
        break;
    case 2:
        if(target && !(I14(v,8)&2)) {
            float remaining=func_00283CE0(I14(v,0x40));
            float total=func_00283CE0(I14(v,0xc));
            target[0x23]=func_00283CF0(F14(v,0x44)*remaining/total);
        }
        if(!(I14(v,8)&4) && target && (signed char)v[0x17]!=-1 && (unsigned char)target[0x20]==(signed char)v[0x17]) m[0x20]=3;
        if(!(I14(v,8)&8) && func_00282948((int *)(v+0x40))) m[0x20]=3;
        func_L06_003E11A0(m,v);
        break;
    case 3:
        if(target && !(I14(v,8)&1)) func_0029F338(target);
        func_0029F338(m);
        return;
    case 4:
        break;
    }
    if(D_001A79F0[0]==13) func_00282F20(m+0xc0,m+0xc0,0.5f);
}
