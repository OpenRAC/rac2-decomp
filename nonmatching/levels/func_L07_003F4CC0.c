/* func_L07_003F4CC0: retained near miss, opus-1 (v2224), 3 November 2026.
   Profile: -O2 -G8 -ffunction-sections -g (own -g8.c unit).
   check.py: 1124/1124 bytes, 0/1 places (USA v1.01); 21 non-relocation rows
   differ, and every one is a register rename: s3<->s4 (retail keeps the
   PRE/hoisted current-point copy in s3, the sprite pointer and object
   pointer p in s4) and f24<->f25 (retail alpha in f24, 0.0 in f25).
   Instruction sequence, frame, schedule and data address forms all match.
   Using the arrays directly (no current/end/direction pointers) gives the
   retail preheader `daddu` copy; D_L07_001B0EC8[] as an sda array read as
   [0]/[1] gives the unsplit CONST `lui at` alternate-width load.
   Both swaps are global-alloc priority near-ties (greg dump): the sprite
   copy outranks the current-point reaching reg (about 1694 vs 1666) and the
   0.0 pseudo outranks alpha (877 vs 864). Shifting either needs a few more
   loop refs or a shorter alpha/current life without adding code.
   Declarations: as below (sda scalars/arrays, D_L07_001B9200 NOT_SDA,
   SDATA(D_L07_001B0EE0)). Earlier draft (git 264b91515) has 6 differing rows
   with a different copy schedule and a v0 width load.
*/

#include "common.h"
extern void func_L07_003F4C18(void *,void *,void *);
extern void func_00282CF0(void *,void *,void *),func_00282DD8(void *,void *,void *),func_00282F20(void *,void *,f32),func_00282CC0(void *,void *,void *);
extern f32 func_00282DF0(void *),func_00283B98(f32,f32);
extern s32 func_00283D38(s32,s32,f32);
extern void func_00281DE8(void *,s32,s32,s32),func_00280B90(void *,void *,s32);
extern void func_00281EB8(void *,s32,s32,s32,f32,f32,f32);
extern u8 D_L07_001B9200[] NOT_SDA;
extern s32 D_L07_001B0EB0 __attribute__((sda)),D_L07_001B0EA8 __attribute__((sda)),D_L07_001B0ED0 __attribute__((sda));
extern s32 D_L07_001B0EAC[] __attribute__((sda)),D_L07_001B0ED4[] __attribute__((sda));
extern f32 D_L07_001B0EB8 __attribute__((sda)),D_L07_001B0EC0 __attribute__((sda));
extern f32 D_L07_001B0ED8 __attribute__((sda)),D_L07_001B0EDC __attribute__((sda));
extern f32 D_L07_001B0EBC[] __attribute__((sda));
extern f32 D_L07_001B0EC8[] __attribute__((sda));
extern f32 D_L07_001B0EE0[] SDATA(D_L07_001B0EE0);
extern f32 D_L07_001B0EE4[] __attribute__((sda));
#define F(p,o) (*(f32 *)((p)+(o)))
void func_L07_003F4CC0(u8 *a)
{
    f32 start[4],end[4],delta[4],side[4],normal[4],base[4];
    struct Vec4 {f32 x,y,z,w;};
    struct { struct Vec4 vertices[4];s32 colors[4];f32 uv[4][2];u8 rest[32]; } draw;
    f32 current[4],step[4];
    u8 *p=*(u8 **)(a+0x68);
    s32 i,color;
    f32 length,count,alpha,rotation,width;
    f32 uvOffset;
    func_L07_003F4C18(a,start,end);
    func_00282CF0(delta,end,start);func_00282CF0(side,D_L07_001B9200,a+0x10);
    func_00282DD8(normal,side,delta);func_00282F20(normal,normal,1);
    qzero_nc(side);qcopy_nc(base,start);base[3]=1;
    func_00281DE8(&draw,D_L07_001B0EB0,1,128);
    uvOffset=0.0f;
    color=func_00283D38(D_L07_001B0EA8&0xffffff,D_L07_001B0EA8,F(p,0x24));
    { s32 i; for(i=0;i<4;i++){
        struct Vec4 *v;
        draw.uv[i][0]=D_L07_001B0EE0[i*2]+uvOffset;draw.uv[i][1]=D_L07_001B0EE4[i*2];
        qzero_nc(&draw.vertices[i]);
        v=&draw.vertices[i];if(i<2)v->x=0;else v->x=1;
        v->z=D_L07_001B0EB8;if(!(i&1))v->z=-v->z;
        v->w=1;draw.colors[i]=color;
    }
    }
    func_00280B90(&draw,delta,0);
    color=func_00283D38(D_L07_001B0EAC[0]&0xffffff,D_L07_001B0EAC[0],F(p,0x24));
    {s32 i; for(i=0;i<4;i++){
        struct Vec4 *v=&draw.vertices[i];
        v->z=D_L07_001B0EBC[0];if(!(i&1))v->z=-D_L07_001B0EBC[0];
        draw.colors[i]=color;
    }
    }
    func_00280B90(&draw,delta,0);
    length=func_00282DF0(delta)/D_L07_001B0EC0;rotation=F(p,0x28);
    if(a[0x20]==0){alpha=1;count=(length*F(p,0x24))*2.0f;if(count>length+1)count=length+1;}
    else {alpha=F(p,0x24)*F(p,0x24);count=length+1;}
    qcopy(current,base);func_00282F20(step,delta,D_L07_001B0EC0);
    for(i=0;(f32)i<count;i++){
        f32 *pos=current;
        width=D_L07_001B0EC8[0];
        if((f32)i!=count-1 && !(i&1))width=D_L07_001B0EC8[1];
        color=func_00283D38(D_L07_001B0ED0&0xffffff,D_L07_001B0ED0,alpha);
        func_00281EB8(pos,49,color,1,width,0,rotation);
        color=func_00283D38(D_L07_001B0ED4[0]&0xffffff,D_L07_001B0ED4[0],alpha);
        func_00281EB8(pos,49,color,1,width,0,func_00283B98(rotation,D_L07_001B0ED8));
        rotation=-func_00283B98(rotation,D_L07_001B0EDC*0.017453294f);
        if((f32)i<length-1)func_00282CC0(current,current,step);else qcopy(current,end);
    }
}
