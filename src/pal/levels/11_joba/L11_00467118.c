#include "names.h"
/* func_PAL_L11_00467118, the PAL copy of func_L11_00461308: the same C, where func_002A7470
   becomes func_PAL_002A7E68; func_L11_003DD068 becomes func_PAL_L11_003E0F10; 0.00027777778f
   becomes 0.00040000002f; 0.034906592f becomes 0.04188791f; func_002A05A8 becomes
   func_PAL_002A0F68; 1.0f / 60.0f becomes 0.020000001f. */
#include "common.h"
typedef int TI128 __attribute__((mode(TI)));
extern char *CreateMoby(int);
extern void moby_init_child_from_parent(char *, char *);
extern void func_PAL_002A7E68(char *, int, int, int);
extern void moby_set_state(char *, int, int);
extern int IsPointInCuboid(void *, int);
extern void moby_transform_joint_to_world(char *, int, void *);
extern void transform_vector(void *, void *, void *);
extern u8 *func_PAL_L11_003E0F10(u8 *, u8 *, u8 *, float);
extern float math_random_float_range(float, float);
extern float FastAddRotations(float, float);
extern float math_fast_sin_or_cos_a(float);
extern float math_fast_sin_or_cos_b(float);
extern void FastVecScale(void *, void *, float);
extern void FastVecAdd(void *, void *, void *);
extern void func_PAL_002A0F68(char *);
extern void func_002A0F48(char *);
extern void *part_spawn_object_relative_particle(char *, void *, void *, void *, int);
extern int D_L11_001B089C[] NOT_SDA __attribute__((sda));
typedef struct { int unused; int flags; char pad[56]; } Entry61308;
extern Entry61308 D_L11_002B6D40[];
extern char *g_moby_l11_table[] NOT_SDA __attribute__((sda));
extern char *D_L11_001B368C[] NOT_SDA __attribute__((sda));
extern char g_hero_position[];
extern float D_L11_001B2388 SDATA(D_L11_001B2388);
extern float D_L11_001B2388_block[] __asm__("D_L11_001B2388") __attribute__((sda));
extern char D_L11_001B2378[] NOT_SDA __attribute__((sda));
extern char D_L11_001B2368[] NOT_SDA __attribute__((sda));
extern char D_L11_001B2358[] SDATA(D_L11_001B2358);
#define F(p,o) (*(float *)((char *)(p)+(o)))
#define I(p,o) (*(int *)((char *)(p)+(o)))
#define P(p,o) (*(char **)((char *)(p)+(o)))
#define H(p,o) (*(unsigned short *)((char *)(p)+(o)))
void func_PAL_L11_00467118(char *p)
{
    float v[4], pos[4], dir[4], tmp[4];
    char *s = P(p,0x68);
    int active=0, i, ready;
    float t, sn, cs;
    switch ((unsigned char)p[0x20]) {
    case 0:
        P(s,0x10)=CreateMoby(0xCF6);
        F(s,0x14)=0; F(s,0x18)=0;
        if(P(s,0x10)) {
            moby_init_child_from_parent(P(s,0x10),0);
            H(P(s,0x10),0x34)|=6;
            func_PAL_002A7E68(P(s,0x10),0x10,0,0);
        }
        moby_set_state(p,1,-1);
        break;
    case 1:
        if ((D_L11_002B6D40[D_L11_001B089C[0]].flags&0x10) && !I(s,8)) {
            H(p,0x34)|=0x41;
            H(P(s,0x10),0x34)|=0x41;
            I(p,0x98)=0;
            return;
        }
        active=1;
        H(p,0x34)&=0xFFBE;
        H(P(s,0x10),0x34)&=0xFFBE;
        I(p,0x98)=I(P(p,0x24),0x10);
        ready=1;
        if(I(s,0xC)!=-1) { char *m=g_moby_l11_table[0]+(I(s,0xC)<<8); ready=0; if((unsigned char)m[0x20]!=3) ready=active; }
        if (ready && IsPointInCuboid(g_hero_position,I(s,0)))
            moby_set_state(p,2,-1);
        break;
    case 2:
        active=1;
        t=math_random_float_range(0.0f,0.333f);
        for(i=0;i<3;i++) {
            moby_transform_joint_to_world(p,i==0?3:i==1?2:4,v);
            *(TI128 *)tmp = 0;
            tmp[0]=math_random_float_range(-1.0f,1.0f);
            tmp[3]=1.0f;
            tmp[1]=t+t-1.0f;
            t+=0.333f;
            *(TI128 *)dir=*(TI128 *)tmp;
            transform_vector(dir,dir,D_L11_001B368C[0]+(I(s,4)<<7));
            {
                float high = D_L11_001B2388_block[1];
                float low = D_L11_001B2388;
                func_PAL_L11_003E0F10(p,v,dir,math_random_float_range(low,high)*0.00040000002f);
            }
        }
        moby_set_state(p,3,-1);
        break;
    case 3:
        active=1;
        if(!IsPointInCuboid(g_hero_position,I(s,0))) moby_set_state(p,1,-1);
        break;
    }
    if(active) {
        F(s,0x14)=FastAddRotations(F(s,0x14),0.04188791f);
        sn=math_fast_sin_or_cos_a(F(s,0x14));
        cs=math_fast_sin_or_cos_b(F(s,0x14));
        F(p,0x18)-=F(s,0x18);
        F(s,0x18)=cs*0.1f;
        F(p,0x18)+=F(s,0x18);
        F(p,0xF4)+=cs*0.0015f;
        F(p,0xF0)+=sn*0.0015f;
        *(TI128 *)(P(s,0x10)+0xF0)=*(TI128 *)(p+0xF0);
        FastVecScale(v,p+0xE0,1.46f);
        FastVecAdd(P(s,0x10)+0x10,p+0x10,v);
        func_PAL_002A0F68(P(s,0x10));
        func_002A0F48(P(s,0x10));
        FastVecScale(v,p+0xE0,0.59f);
        FastVecAdd(pos,p+0x10,v);
        v[0]=v[1]=0.0f;
        v[2]=-(math_random_float_range(2.25f,3.5f)*(0.020000001f));
        part_spawn_object_relative_particle(p,pos,v,D_L11_001B2378,1);
        v[2]=-(math_random_float_range(3.0f,5.0f)*(0.020000001f));
        part_spawn_object_relative_particle(p,pos,v,D_L11_001B2368,1);
        v[2]=-(math_random_float_range(4.0f,8.0f)*(0.020000001f));
        part_spawn_object_relative_particle(p,pos,v,D_L11_001B2358,1);
    }
}
