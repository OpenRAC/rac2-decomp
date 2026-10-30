/* 30 October 2026 retained ordinary C; no linked match or semantic proof.
 * Profile: -O2 -G8 -ffunction-sections.
 * us: 17_smolg: 1156 bytes, expected 1144.
 * us2: 17_smolg: 1156 bytes, expected 1144.
 * pal: 17_smolg: 1156 bytes, expected 1144.
 * Complete five-slot class-checked target list, packed progress checks, position/rotation
 * copies, timer, alpha and cleanup states.1156/1144 bytes; frame0x60 instead of0x70 and
 * list/base allocation differ. All three releases carry this identity.
 */
#include "common.h"
typedef int Q __attribute__((mode(TI)));
typedef union { Q q; float f[4]; } Vec;
#define I(p,o) (*(int *)((char *)(p)+(o)))
#define F(p,o) (*(float *)((char *)(p)+(o)))
#define P(p,o) (*(char **)((char *)(p)+(o)))
#define H(p,o) (*(short *)((char *)(p)+(o)))
#define U(p,o) (*(u8 *)((char *)(p)+(o)))
extern char *D_L17_001B2C1C;
extern int D_001A79F0 __attribute__((sda));
extern u8 D_0019B2E8[],D_0019B4A8[];
extern char D_L17_001B1FB8[],D_L17_001B1FE8[],D_L17_001B2018[];
extern int func_002B38B8(void *);
extern void func_L00_003294F0(void *,int);
extern float func_00283CE0(int);
extern int func_00283CF0(float);
extern void func_0026FEB8(const char *,...);
extern int func_00282948(void *);
extern void func_L17_0041F180(void *,void *);
extern void func_0029F338(void *);
/* Coordinates five class-checked targets and the lifetime of their controlling object. */
void func_L17_0041F478(char *object)
{
    char *state=P(object,0x68),*partner=0,*entry,*record;
    int count=0,i,index,value;
    unsigned char *progress;
    float alpha;
    if(I(state,0x54)!=-1) {
        entry=D_L17_001B2C1C+I(state,0x10)*256;U(entry,0x20)=2;
        if(!func_002B38B8(object)) {I(object,0x98)=0;U(object,0x31)=0;*(u16 *)(object+0x34)|=0x41;return;}
        I(state,0x54)=-1;func_L00_003294F0(object,0);U(entry,0x20)=1;
    }
    if(I(state,0x10)!=-1) partner=D_L17_001B2C1C+I(state,0x10)*256;
    if((U(object,0xb0)==255 || !(D_0019B2E8[U(object,0xb0)+(D_001A79F0<<4)]&128)) && U(object,0x20)) {
        for(i=0,record=state+0x18;i<5;i++,record+=8) {
            index=I(record,0);
            if(index==-1) continue;
            entry=D_L17_001B2C1C+index*256;
            if(func_002B38B8(object)) continue;
            if(!entry || H(entry,0xaa)!=H(record,4) || U(entry,0x20)==254 || U(entry,0x20)==253) {count=0;continue;}
            index=H(entry,0xb2);progress=D_0019B4A8+(index>>1)+(D_001A79F0<<10);value=*progress;
            if(index&1) value>>=4;
            if(value&7) {count=0;continue;}
            count++;
            if(*(signed char *)(record+6)!=-1 && U(entry,0x20)==*(signed char *)(record+6)) count=0;
        }
    }
    switch(U(object,0x20)) {
    case 0:
        if(partner) {
            *(u16 *)(state+0x14)=*(u16 *)(partner+0xaa);F(state,0x44)=func_00283CE0(U(partner,0x23));
            if(I(state,8)&16) *(Q *)(object+16)=*(Q *)(partner+16);
            else if(I(state,8)&64) *(Q *)(partner+16)=*(Q *)(object+16);
            if(I(state,8)&32) *(Q *)(object+0xf0)=*(Q *)(partner+0xf0);
            else if(I(state,8)&128) *(Q *)(partner+0xf0)=*(Q *)(object+0xf0);
        } else func_0026FEB8(D_L17_001B1FB8);
        for(i=0,record=state+0x18;i<5;i++,record+=8) {
            if(I(record,0)!=-1) {
                H(record,4)=H(D_L17_001B2C1C+I(record,0)*256,0xaa);
                func_0026FEB8(D_L17_001B1FE8,(object-D_L17_001B2C1C)>>8,i,I(record,0),H(record,4));
            } else func_0026FEB8(D_L17_001B2018,(object-D_L17_001B2C1C)>>8,i);
        }
        alpha=F(state,0)>F(state,4)?F(state,0):F(state,4);
        U(object,0x20)=1;F(object,0x2c)=alpha*F(P(object,0x24),0x24);
        break;
    case 1:
        if(!count) {
            if(partner && *(signed char *)(state+0x16)!=-1) U(partner,0x20)=U(state,0x16);
            I(state,0x40)=I(state,0xc);U(object,0x20)=2;
        }
        break;
    case 2:
        if(partner && !(I(state,8)&2)) {
            alpha=func_00283CE0(I(state,0x40));
            alpha=F(state,0x44)*alpha/func_00283CE0(I(state,0xc));U(partner,0x23)=func_00283CF0(alpha);
        }
        if(!(I(state,8)&4) && partner && *(signed char *)(state+0x17)!=-1 && U(partner,0x20)==*(signed char *)(state+0x17)) U(object,0x20)=3;
        if(!(I(state,8)&8) && func_00282948(state+0x40)) U(object,0x20)=3;
        func_L17_0041F180(object,state);break;
    case 3:
        if(partner && !(I(state,8)&1)) func_0029F338(partner);
        func_0029F338(object);break;
    }
}
