/* functional: medium. Near-miss draft, not byte-compared in the latest sweep: paths the captured calls never take are unproven. */
/* 30 October 2026 retained ordinary C; no linked match or semantic proof.
 * Profile: -O2 -G8 -ffunction-sections.
 * us: 17_smolg: 1068 bytes, expected 1088.
 * us2: 17_smolg: 1068 bytes, expected 1088.
 * pal: func_L17_00385DE8 is in neither catalogue of pal.
 * Complete scene-list activation and both two-particle emission intervals. The first-result
 * predicate guarding writes through the second result is observed retail behavior, with an
 * unresolved partial-allocation risk. Full 16-byte position and velocity storage is retained.
 * Frame/allocation and store scheduling differ; constructor/helper W semantics remain
 * unqualified.
 */
#include "common.h"
typedef int Q __attribute__((mode(TI)));
typedef union { Q q; float f[4]; } Vec;
#define I(p,o) (*(int *)((char *)(p)+(o)))
#define F(p,o) (*(float *)((char *)(p)+(o)))
#define P(p,o) (*(char **)((char *)(p)+(o)))
#define H(p,o) (*(short *)((char *)(p)+(o)))
#define U(p,o) (*(u8 *)((char *)(p)+(o)))
extern int D_L17_001A8F00;
extern char D_L17_001BD8C0[];
extern char *D_L17_001B2C28;
extern int D_L17_001A8F00_gp __asm__("D_L17_001A8F00") MACRO_ADDR;
extern void func_0029FCC0(void *,int,void *);
extern void func_00282F20(void *,void *,float);
extern int func_002A77E0(int);
extern char *func_002BDCE8(void *,int,void *,u32,int,float,float,float,float);
extern int func_00283CF0(float);
/* Activates the scene objects and emits paired particles during two scene intervals. */
void func_L17_00385DE8(char *object)
{
    Vec velocity,position;
    char *scene=D_L17_001BD8C0,*entry,*first,*second,*data;
    int mode,sign;
    switch(U(object,0x20)) {
    case 0: U(object,0x20)=1; U(object,0x30)=255; break;
    case 1:
        if(D_L17_001A8F00!=2) break;
        mode=D_L17_001A8F00_gp;
        if(I(scene,0x30)==6) {
            for(entry=D_L17_001B2C28;entry;entry=P(entry,0x28)) {
                if(H(entry,0xaa)==0xb88 || H(entry,0xaa)==0x1249) {
                    I(entry,0x98)=0;
                    *(u16 *)(entry+0x34)=(*(u16 *)(entry+0x34)|0x43)&0xefff;
                }
            }
        }
        mode=D_L17_001A8F00;
        if(mode!=2) break;
        if(I(scene,0x30)==4 && (unsigned)(I(scene,0x34)-0x12d)<0x3b && H(P(scene,0x194),0xaa)==0x125e) {
            entry=P(scene,0x194);
            func_0029FCC0(entry,0,&position);
            func_00282F20(&velocity,entry+0xe0,-0.05f);
            sign=func_002A77E0(16);
            if(func_002A77E0(2)) sign=-sign;
            first=func_002BDCE8(&position,sign,&velocity,0x7f204080,0,0.1f,1.0f,0.9f,100000.0f);
            if(first) {
                *(u16 *)(first+0xa)=16;U(first,9)=func_00283CF0(4.0f)+64;
                data=first+0x20;U(data,0xa)=127;I(data,4)=mode;U(data,0xb)=U(first,0xa);
            }
            second=func_002BDCE8(&position,16,&velocity,0x7fffffff,0,0.05f,1.0f,0.97f,60000.0f);
            /* Retail gates the second result with the first result, preserving its behavior. */
            if(first) {
                data=second+0x20;U(second,9)=func_00283CF0(4.0f)+64;*(u16 *)(second+0xa)=16;
                U(second,8)=func_002A77E0(255);I(data,4)=mode;U(data,0xa)=127;U(data,0xb)=U(first,0xa);
            }
        }
        mode=D_L17_001A8F00;
        if(mode!=2) break;
        if(I(scene,0x30)==5 && I(scene,0x34)>=0x213 && H(P(scene,0x194),0xaa)==0x125e) {
            entry=P(scene,0x194);
            func_0029FCC0(entry,0,&position);
            func_00282F20(&velocity,entry+0xe0,-0.05f);
            sign=func_002A77E0(16);
            if(func_002A77E0(2)) sign=-sign;
            first=func_002BDCE8(&position,sign,&velocity,0x7f204080,0,0.1f,1.0f,0.9f,100000.0f);
            if(first) {
                *(u16 *)(first+0xa)=16;U(first,9)=func_00283CF0(4.0f)+64;
                data=first+0x20;U(data,0xa)=127;I(data,4)=mode;U(data,0xb)=U(first,0xa);
            }
            second=func_002BDCE8(&position,16,&velocity,0x7fffffff,0,0.05f,1.0f,0.97f,60000.0f);
            if(first) {
                data=second+0x20;U(second,9)=func_00283CF0(4.0f)+64;*(u16 *)(second+0xa)=16;
                U(second,8)=func_002A77E0(255);I(data,4)=mode;U(data,0xa)=127;U(data,0xb)=U(first,0xa);
            }
        }
        break;
    }
}
