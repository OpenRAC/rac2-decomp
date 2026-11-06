#include "common.h"

/* func_PAL_L17_003CBDF4, the PAL copy of func_L17_003C7C70: the same C at 50 Hz. It has a unit of its own: it needs -G8 for its $gp tuning values and -g,
   which gives the nop pairs retail has before each division, and its jump table is this
   unit's only .rodata. */

/* The tuning value the first rate divides by is read-only here: as const its load carries no
   anti-dependences on the flag stores, so sched1 issues it after the 360.0f numerator, which
   lengthens that constant's life and leaves $f20 to the scale constant, as in retail. */
extern const float D_L17_001B03B4 __attribute__((sda));
extern float D_L17_001B03B8 __attribute__((sda));
extern float D_L17_001B03BC __attribute__((sda));
extern float D_L17_001B03C0 __attribute__((sda));
extern float D_L17_001B03C4 __attribute__((sda));
extern float D_L17_001B03C8 __attribute__((sda));
extern float D_L17_001B03CC __attribute__((sda));
extern float D_L17_001B03D0 __attribute__((sda));
extern float D_L17_001B03D4 __attribute__((sda));
extern float D_L17_001B03D8 __attribute__((sda));
extern void func_002AEE70(void *,void *,void *,float,float,float),func_002AEF28(void *,void *,void *,float,float,float);
extern int func_L00_00324120(void *),func_002B3868(void *),func_00282948(void *),func_00283CF0(float);
extern void func_002A7750(void *,int,int),func_002E5CF8(int,int,void *);
extern float func_00283CE0(int),func_002ABB18(float),func_00283198(float),func_00283180(float),func_00283B98(float,float),func_00283C28(float);
extern void func_00282CF0(void *,void *,void *),func_002AD6F0(void *,void *,void *,void *);
typedef int Quad __attribute__((mode(TI)));
typedef union { Quad q; float f[4]; } UpdateVector;
typedef struct {
    u8 pad00[0x3e];
    u16 flags3e;
    u8 pad40[0x4c];
    int flags8c;
    UpdateVector origin;
    float a0, a4, a8, ac;
    int b0, b4, b8;
} UpdateState;
typedef struct {
    u8 pad00[0x10];
    UpdateVector position;
    u8 mode;
    u8 pad21[0x13];
    u16 flags34;
    u8 pad36[0x32];
    UpdateState *state;
    u8 pad6c[0x84];
    UpdateVector rotation;
} UpdateObject;
void func_PAL_L17_003CBDF4(UpdateObject *o)
{
    float oldpos[4] __attribute__((aligned(16)));
    float pos[4] __attribute__((aligned(16)));
    float oldrot[4] __attribute__((aligned(16)));
    float rot[4] __attribute__((aligned(16)));
    UpdateState *s;
    float first_rate;
    float rate_scale = 0.0003490659f;
    first_rate=360.0f/D_L17_001B03B4;
    *(Quad *)oldpos=o->position.q;
    *(Quad *)oldrot=o->rotation.q;
    s=o->state;
    s->flags8c|=1;
    s->flags3e|=8;
    o->flags34|=0x20;
    func_002AEE70(o,&s->a0,&s->a4,D_L17_001B03B8,first_rate*rate_scale,-1.0f);
    func_002AEF28(o,&s->a8,&s->ac,D_L17_001B03BC,(360.0f/D_L17_001B03C0)*rate_scale,(360.0f/D_L17_001B03C4)*rate_scale);
    switch(o->mode) {
    case 0:
        s->origin.q=*(Quad *)oldpos;
        o->mode=1;
        break;
    case 1:
        if(func_L00_00324120(o)) {
            func_002A7750(o,2,-1);
            s->b0=func_00283CF0((D_L17_001B03C8*300.0f+2.0f)*0.16666667f);
        }
        break;
    case 2: {
        float t;
        if(func_002B3868(o))func_002E5CF8(0,0,o);
        if(s->b0==50)func_002E5CF8(0,0,o);
        if(func_00282948(&s->b0)) {
            s->b4=func_00283CF0((D_L17_001B03CC*300.0f+2.0f)*0.16666667f);
            o->mode=3;
        } else {
            rot[0]=func_00283198(func_002ABB18(func_00283CE0(s->b0)*0.75f))*0.017453294f;
            rot[1]=func_00283180(func_002ABB18(func_00283CE0(s->b0)*0.89f))*0.017453294f;
            if((float)s->b4>(D_L17_001B03C8*300.0f+2.0f)*0.16666667f-25.0f) {
                t=func_00283CE0(s->b0)/((D_L17_001B03C8*300.0f+2.0f)*0.16666667f-25.333334f);
                o->rotation.f[0]=o->rotation.f[0]*t+rot[0]*(1.0f-t);
                o->rotation.f[1]=o->rotation.f[1]*t+rot[1]*(1.0f-t);
            } else {
                o->rotation.f[1]=rot[1];
                o->rotation.f[0]=rot[0];
            }
        }
        break;
    }
    case 3: {
        float t,f,b,ax,ay;
        t=func_00283CE0(s->b4)/((D_L17_001B03CC*300.0f+2.0f)*0.16666667f);
        f=(1.0f-t)*D_L17_001B03D4;
        o->rotation.f[1]=0;
        o->rotation.f[0]=(1.0f-t)*1.57079649f;
        ax=func_00283180(func_00283B98(1.57079649f,o->rotation.f[2]));
        b=func_00283198(o->rotation.f[0]);
        ax*=f*b;
        o->position.f[0]=ax;
        ay=func_00283198(func_00283B98(1.57079649f,o->rotation.f[2]));
        b=func_00283198(o->rotation.f[0]);
        ay*=f*b;
        o->position.f[1]=ay;
        o->position.f[2]=0;
        o->position.f[0]+=s->origin.f[0];
        ay+=s->origin.f[1];
        o->position.f[1]=ay;
        f*=func_00283180(o->rotation.f[0]);
        o->position.f[2]=s->origin.f[2]-f;
        o->position.f[2]-=func_00283180(t*1.57079649f)*D_L17_001B03D8;
        s->flags8c&=~1;
        s->flags3e&=~8;
        o->flags34&=~0x20;
        if(func_00282948(&s->b4)) {
            o->mode=4;
            s->b8=func_00283CF0((D_L17_001B03D0*300.0f+2.0f)*0.16666667f);
        }
        break;
    }
    case 4: {
        float t,f,b,c,ax,ay;
        t=func_00283CE0(s->b8)/((D_L17_001B03D0*300.0f+2.0f)*0.16666667f);
        *(Quad *)rot=o->rotation.q;
        c=1.0f-t;
        f=(1.0f-c)*D_L17_001B03D4;
        o->rotation.f[0]=func_00283C28((rot[0]*c+c*4.71238947f)+1.57079649f);
        o->rotation.f[1]=rot[1]*c;
        ax=func_00283180(func_00283B98(1.57079649f,o->rotation.f[2]));
        b=func_00283198(o->rotation.f[0]);
        ax*=f*b;
        o->position.f[0]=ax;
        ay=func_00283198(func_00283B98(1.57079649f,o->rotation.f[2]));
        b=func_00283198(o->rotation.f[0]);
        ay*=f*b;
        o->position.f[1]=ay;
        o->position.f[2]=0;
        o->position.f[0]+=s->origin.f[0];
        ay+=s->origin.f[1];
        o->position.f[1]=ay;
        f*=func_00283180(o->rotation.f[0]);
        o->position.f[2]=s->origin.f[2]-f;
        o->position.f[2]-=func_00283180(c*1.57079649f)*D_L17_001B03D8;
        s->flags8c&=~1;
        s->flags3e&=~8;
        o->flags34&=~0x20;
        if(func_00282948(&s->b8)) {
            o->mode=1;
            {
                Quad home = s->origin.q;
                o->rotation.q=*(Quad *)rot;
                o->position.q=home;
            }
        }
        break;
    }
    }
    if(o->mode<3) {
        func_00282CF0(pos,&o->position,oldpos);
        func_002AD6F0((u8 *)s+0x50,pos,oldrot,&o->rotation);
    }
}
