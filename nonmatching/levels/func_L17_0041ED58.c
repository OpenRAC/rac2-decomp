/* 30 October 2026 retained ordinary C; no linked match or semantic proof.
 * Profile: -O2 -G8 -ffunction-sections.
 * us: 17_smolg: 1028 bytes, expected 1064.
 * us2: func_L17_0041ED58 is in neither catalogue of us2.
 * pal: func_L17_0041ED58 is in neither catalogue of pal.
 * Complete pickup rotation, paired mote loop, packed per-level progress nibble and completion
 * paths. Full 16-byte vectors retained; func_002AF000 writes XYZ only, and downstream W
 * semantics of the particle request are not qualified.1028/1064 bytes;
 * allocation/counter/preheader lifetimes differ. Only USA identity carries.
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
extern u8 D_L17_0021EBB0[];
extern u8 D_0019B4A8[];
extern int D_001A79F0 __attribute__((sda));
extern u8 D_0013963C,D_0013963E,D_00139641;
extern char D_00189EA0[];
extern float func_00283B98(float,float);
extern float func_002A7878(float,float);
extern int func_002A77E0(int);
extern float func_002A7940(void);
extern float func_002A78D8(float,float);
extern void func_002AF000(void *,float,float,float);
extern char *func_002C2210(void *,int,u32,int,int,void *,int,float,float,float);
extern float func_00282E80(void *,void *);
extern void func_L00_003294F0(void *,int);
extern void func_002A7750(void *,int,int);
extern void func_0029F338(void *);
extern void func_002B0A18(int,int);
extern void func_00288E18(int,int);
/* Emits paired motes until collected, then updates the packed per-level pickup count. */
void func_L17_0041ED58(char *object)
{
    Vec velocity,position;
    char *state=P(object,0x68);
    unsigned char *counter;
    int index=H(object,0xb2),value,sign,i,lives;
    float size,heading,elevation,speed;
    if(!U(object,0x20)) {
        if(D_L17_0021EBB0[index+0x464]) {func_0029F338(object);return;}
        counter=D_0019B4A8+(index>>1)+(D_001A79F0<<10);
        value=*counter;
        if(index&1) value>>=4;
        if(value&7) {func_0029F338(object);return;}
        F(object,0xf8)=func_00283B98(F(object,0xf8),0.087266475f);
        for(i=1;i>=0;i--) {
            size=func_002A7878(2.0f,5.0f);sign=func_002A77E0(2);if(!sign) sign=-1;
            heading=func_002A7940();elevation=func_002A7878(0.3490659f,1.535889864f);
            speed=func_002A7878(0.05f,0.1f);func_002AF000(&velocity,speed,heading,elevation);
            position.q=*(Q *)(object+16);
            position.f[0]+=func_002A78D8(0,0.15f);position.f[1]+=func_002A78D8(0,0.15f);position.f[2]+=func_002A78D8(0,0.15f);
            func_002C2210(&position,3,0x208020ff,0,sign,&velocity,0,size*0.1f,size,0.006f);
            func_002C2210(&position,3,0x20ffffff,1,-sign,&velocity,0,size*0.03f,size*0.3f,0.006f);
        }
        if(func_00282E80(object+16,D_00189EA0)<1.5f) {
            D_0013963C=1;index=H(object,0xb2);counter=D_0019B4A8+(index>>1)+(D_001A79F0<<10);
            if(index&1) {if(((*counter>>4)&7)!=7) *counter+=16;}
            else if((*counter&7)!=7) ++*counter;
            if(I(state,0)!=-1) {
                U(object,0x31)=0;*(u16 *)(object+0x34)|=1;
                func_L00_003294F0(D_L17_001B2C1C+I(state,0)*256,1);
                func_002A7750(object,1,-1);
            } else func_0029F338(object);
        }
    } else {
        if(I(state,0)!=-1) {
            value=U(D_L17_001B2C1C+I(state,0)*256,0x20);
            if(value!=254 && value!=253) return;
        }
        func_002B0A18(0x1292,120);
        lives=D_0013963E?1:2;if(D_00139641) lives--;
        if(lives>0) func_00288E18(0xa0f,0x66);else func_00288E18(0xa10,0x67);
        func_0029F338(object);
    }
}
