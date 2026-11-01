#include "include_asm.h"

#include "common.h"
typedef unsigned int Quad __attribute__((mode(TI)));
typedef union { Quad q; float f[4]; } Vec;
#define F(p,o) (*(float *)((char *)(p)+(o)))
#define I(p,o) (*(int *)((char *)(p)+(o)))
#define P(p,o) (*(char **)((char *)(p)+(o)))
extern float D_L30_001AF8EC __attribute__((sda));
extern float D_L30_001AF914 __attribute__((sda));
extern float D_L30_001AF8E4 __attribute__((sda));
extern float D_L30_001AF910 __attribute__((sda));
extern float D_L30_001AF8F0 __attribute__((sda));
extern float D_L30_001AF8B8 __attribute__((sda));
extern float D_L30_001AF8B0 __attribute__((sda));
extern float D_L30_001AF8D0 __attribute__((sda));
extern float D_L30_001AF8A4 __attribute__((sda));
extern float D_L30_001AF904 __attribute__((sda));
extern float D_L30_001AF8E8 __attribute__((sda));
extern float D_L30_001AF8F8 __attribute__((sda));
extern float D_L30_001AF8C8 __attribute__((sda));
extern float D_L30_001AF960 __attribute__((sda));
extern float D_L30_001AF8C4 __attribute__((sda));
extern float D_L30_001AF900 __attribute__((sda));
extern float D_L30_001AF90C __attribute__((sda));
extern float D_L30_001AF8C0 __attribute__((sda));
extern float D_L30_001AF8A8 __attribute__((sda));
extern float D_L30_001AF8D4 __attribute__((sda));
extern float D_L30_001AF95C __attribute__((sda));
extern float D_L30_001AF908 __attribute__((sda));
extern float D_L30_001AF8E0 __attribute__((sda));
extern float D_L30_001AF8CC __attribute__((sda));
extern float D_L30_001AF958 __attribute__((sda));
extern float D_L30_001AF8AC __attribute__((sda));
extern float D_L30_001AF954 __attribute__((sda));
extern float D_L30_001AF950 __attribute__((sda));
extern float D_L30_001AF8FC __attribute__((sda));
extern float D_L30_001AF964 __attribute__((sda));
extern float D_L30_001AF8BC __attribute__((sda));
extern float D_L30_001AF8B4 __attribute__((sda));
extern float D_L30_001AF8A0 __attribute__((sda));
extern float D_L30_001AF8F4 __attribute__((sda));
extern int D_L30_001AF8D8 __attribute__((sda));
extern int D_L30_001AF8DC __attribute__((sda));
extern char * func_002A9640(void *,int,int);
extern float func_002A0558(void *,void *);
extern int func_002B0C28(int,int,int);
extern void func_PAL_L00_002C4480(int,int);
extern void func_PAL_L00_002D2668(int,int,float);
extern float func_00282DF0(void *);
extern float func_00283B98(float,float);
extern float func_00283180(float);
extern float func_00283198(float);
extern float func_00282C48(float);
extern float func_L08_003277C0(int,float);
extern void func_00282CC0(void *,void *,void *);
extern float func_002A89A8(void *,int,float);
extern float func_00283BE0(float,float);
extern void func_00282D30(void *,void *,float);
extern void func_PAL_L00_00337918(void *,void *,float);
extern void func_00282F20(void *,void *,float);
extern void func_00282DD8(void *,void *,void *);
extern void func_002AB6D8(void *,void *);
extern void func_00283698(void *,void *);
extern void func_002830C0(void *,void *,void *);
extern void func_00283098(void *,void *,void *);
extern void func_002A8C00(void *,void *,int,void *,float);
extern void func_0029FCC0(void *,int,void *);
extern void func_00282CF0(void *,void *,void *);
extern int func_00277258(void *,int,void *,float);
extern float func_00282DB0(void *,void *);
extern void func_00277F48(void *,int,void *,void *,float);
extern void func_PAL_002AC718(void *, void *, void *, float, float, int, int, int, float, float, float, float, int, float, int, int, int, int, int);
extern void func_0029F338(void *);
extern void func_002AEF28(void *,void *,void *,float,float,float);
extern void func_L00_002E6CF0(void (*)(char *),void *);
extern float func_00282E48(void *,void *);
extern void func_002A93B0(void *);
extern void func_L30_003B3E60(float *,float *,float *,float *);
extern void func_PAL_L30_003B74B0(char *);
typedef struct {
    char pad00[0x80]; Vec position, rotation;
    char padA0[0x1830-0xA0]; void *vehicle;
    char pad1834[0x2290-0x1834]; char *moby; int mode;
} Hero;
typedef struct { char pad[0x18]; char *hit; int count; Vec vector, point, normal; } Collision;
extern Hero D_00189E20 NOT_SDA;
extern Collision D_L30_001C0200 NOT_SDA;
extern char D_0018B650[] NOT_SDA;
extern int D_00138324 NOT_SDA;
extern char D_L30_001B9DC0[] NOT_SDA;
typedef struct { char pad[0x10]; int flags; char pad14[0x10]; float radius; } MobyClass;
typedef struct {
    Vec velocity, other;
    float lean, pitch, heading;
    float gap2C[3];
    float phase, bob, tiltX, tiltY, baseHeight, throttle, health;
} HoverState;
typedef struct {
    char pad00[0x10]; Vec position;
    u8 state; char pad21[3]; MobyClass *mclass;
    char pad28[4]; float radius;
    u8 pad30, interaction; char pad32[0x68-0x32];
    HoverState *data; char pad6C[3]; u8 touchTimer;
    char pad70[0x98-0x70]; int flags;
    char pad9C[0xA8-0x9C]; u8 damageFlag;
    char padA9[0xC0-0xA9]; Vec basis[3]; Vec rotation;
} HoverMoby;

void func_PAL_L30_003B7808(HoverMoby *obj) {
    struct {
        Vec dir, accel, old;
        Vec matrix[4];
        Vec pos;
        union { Vec inverse[4]; struct { Vec delta, normal; } contact; } scratch;
    } frame;
    struct { float x,y,z,w; int active; } in;
    float limit, speed, cap, sign, thrust, height, target;
    HoverState *st=obj->data;
    char *hit;
    if (obj->state) {
        obj->position.f[2]=st->baseHeight;
        hit=func_002A9640(obj,0x30001,0);
        if (hit && P(hit,0x20) && *(short *)(P(hit,0x20)+0xAA)!=0x853) {
            st->health-=F(hit,0x2c);
            if(st->health<=0) obj->state=5;
        }
        obj->damageFlag=255;
    } else {
        st->baseHeight=obj->position.f[2];
    }
    {
        MobyClass *cls=obj->mclass;
        in.active=0;
        obj->radius=cls->radius*D_L30_001AF950;
    }
    switch(obj->state) {
    case 0:
        qzero(st);
        st->health=D_L30_001AF964;
        obj->state=1;
        break;
    case 1:
        if(func_002A0558(obj,D_00189E20.moby)<D_L30_001AF8A0 && D_00189E20.mode!=0x31) {
            int request = func_002B0C28(7,0x12EA,1)!=0;
            if(D_00138324&16) in.active=request;
        }
        if(in.active) {
            func_PAL_L00_002C4480(0x31,0);
            func_PAL_L00_002D2668(D_L30_001AF8D8,0,15.0f);
            qcopy_nc(&D_00189E20.rotation,&obj->rotation);
            qcopy_nc(&D_00189E20.position,&obj->position);
            D_00189E20.vehicle=obj;
            obj->state=3;
            I(D_00189E20.moby,0x9c)=-1;
        }
        /* fall through */
    case 3:
        obj->flags=0;
        in.w=in.z=in.y=in.x=0.0f;
        if(obj->state==3) {
            if(D_L30_001AF8DC!=D_L30_001AF8D8)func_PAL_L00_002D2668(D_L30_001AF8D8,0,15.0f);
            func_L30_003B3E60(&in.x,&in.y,&in.z,&in.w);
        }
        st->throttle=in.y;
        in.z*=0.01745329424738884f;
        in.z*=D_L30_001AF908;
        speed=func_00282DF0(st);
        cap=D_L30_001AF8C8*(0.020000001f);
        limit=D_L30_001AF910*(0.020000001f);
        {
            float amount=in.x*((speed<limit?speed:limit)/limit*D_L30_001AF90C+(1-D_L30_001AF90C));
            amount*=0.0003490659f;
            st->heading=func_00283B98(st->heading,D_L30_001AF8B8*amount);
        }
        {
            float rad=in.x*0.01745329424738884f;
            float lean=D_L30_001AF8F0*rad;
            lean*=D_L30_001AF8FC*in.y+(1-D_L30_001AF8FC);
            st->lean+=(lean-obj->rotation.f[0])*D_L30_001AF8EC;
        }
        frame.dir.f[0]=func_00283180(st->heading);
        frame.dir.f[1]=func_00283198(st->heading);
        frame.dir.f[2]=0;
        if(in.y<0)in.y*=D_L30_001AF8F4;
        sign=1.0f;
        if(in.y<0) sign=-1.0f;
        {
            float magnitude=func_00282C48(in.x), throttle=func_L08_003277C0(2,(cap-speed)/cap);
            float amount=in.y+D_L30_001AF8F8*magnitude*sign;
            amount*=0.00040000002f;
            amount*=D_L30_001AF8C4;
            thrust=amount*throttle;
        }
        func_00282CC0(&frame.old,&obj->position,st);
        height=func_002A89A8(&frame.old,0,0.5f);
        st->velocity.f[2]-=D_L30_001AF8E0*0.00040000002f;
        if(height!=0) {
            target=height+D_L30_001AF8CC;
            if(target<frame.old.f[2]) {
                st->pitch=func_00283B98(st->pitch,func_00283BE0(in.z,st->pitch)*D_L30_001AF904);
                goto physics;
            } else if(frame.old.f[2]+0.1f<height) {
                frame.old.f[2]=height;
                func_00282D30(st,st,D_L30_001AF8E8);
            } else {
                st->velocity.f[2]+=((target-frame.old.f[2])*D_L30_001AF8D0-st->velocity.f[2])*D_L30_001AF8D0;
            }
            func_PAL_L00_00337918(&D_L30_001C0200.vector,obj->basis,speed*0.9f);
            if(in.w>0) {
                float drag=1-D_L30_001AF914*in.w;
                st->velocity.f[0]*=drag;
                st->velocity.f[1]*=drag;
            }
            {
                Vec *right=&frame.matrix[0], *up, *ahead=&frame.matrix[2];
                func_00282F20(ahead,&D_L30_001C0200.normal,1.0f);
                up=&frame.matrix[1];
                func_00282DD8(up,obj->basis,ahead);
                func_00282DD8(right,up,ahead);
            }
            qzero_nc(&frame.matrix[3]);
            func_002AB6D8(&frame.matrix[0],&frame.pos);
            st->pitch=func_00283B98(st->pitch,func_00283BE0(func_00283B98(-frame.pos.f[1],in.z),st->pitch)*D_L30_001AF900);
            func_00282D30(st,st,D_L30_001AF8BC);
            func_00283698(frame.scratch.inverse,obj->basis);
            func_002830C0(st,st,frame.scratch.inverse);
            st->velocity.f[1]*=D_L30_001AF8C0;
            func_00283098(st,st,obj->basis);
            func_00282F20(&frame.accel,obj->basis,thrust);
            func_00282CC0(st,st,&frame.accel);
        }
physics:
        func_002A8C00(&frame.matrix[0],obj,0x10000,st,D_L30_001AF954);
        qcopy_nc(&obj->position,&frame.old);
        func_0029FCC0(obj,0,&frame.matrix[3]);
        frame.matrix[3].f[2]+=D_L30_001AF8D4;
        func_00282CF0(&frame.pos,&obj->position,&frame.matrix[3]);
        if(func_00277258(&frame.matrix[3],0,obj,D_L30_001AF8D4) && D_L30_001C0200.hit!=D_00189E20.moby) {
            func_00282CC0(&obj->position,&D_L30_001C0200.point,&frame.pos);
            func_00282DD8(&frame.scratch.contact.normal,&D_L30_001C0200.normal,st);
            func_00282DD8(&frame.scratch.contact.delta,&frame.scratch.contact.normal,&D_L30_001C0200.normal);
            func_00282F20(&frame.scratch.contact.delta,&frame.scratch.contact.delta,1.0f);
            func_00282F20(st,&frame.scratch.contact.delta,func_00282DB0(st,&frame.scratch.contact.delta));
            func_00282D30(st,st,D_L30_001AF8E4);
            func_PAL_L00_00337918(&D_L30_001C0200.vector,obj->basis,0.0f);
        }
        speed = func_00282DF0(st);
        if(D_L30_001AF960*(0.020000001f)<speed) {
            frame.matrix[3].f[2]+=D_L30_001AF95C;
            func_00277F48(&frame.matrix[3],0,obj,&frame.matrix[0],D_L30_001AF8D4);
            func_0029FCC0(obj,3,&frame.scratch.contact.delta);
            func_00277F48(&frame.scratch.contact.delta,0,obj,&frame.matrix[0],D_L30_001AF958);
        }
        if(!in.active && P(D_0018B650,0)==obj && (D_00138324&16))obj->state=4;
        break;
    case 4:
        obj->flags=obj->mclass->flags;
        I(D_00189E20.moby,0x9c)=0;
        func_PAL_L00_002C4480(0,1);
        D_00189E20.vehicle=0;
        obj->state=1;
        break;
    case 5:
        obj->flags=obj->mclass->flags;
        I(D_00189E20.moby,0x9c)=0;
        func_PAL_L00_002C4480(0,1);
        func_0029FCC0(obj,0,&frame.dir);
        func_PAL_002AC718(obj,st,&frame.dir,0.0f,0.0f,10,3,16,4.0f,2.0f,9.0f,1.0f,-1,15.0f,1,1,-1,0,0x810001);
        func_0029F338(obj);
        return;
    case 2:
    case 6:
        break;
    }
    st->baseHeight=obj->position.f[2];
    st->phase=func_00283B98(st->phase,D_L30_001AF8A8*0.0003490659f);
    st->bob=func_00283198(st->phase)*D_L30_001AF8A4;
    obj->position.f[2]+=st->bob;
    func_002AEF28(obj,&st->tiltX,&st->tiltY,D_L30_001AF8AC*0.01745329424738884f,D_L30_001AF8B0*0.0003490659f,D_L30_001AF8B4*0.0003490659f);
    obj->rotation.f[2]=st->heading;
    obj->rotation.f[0]=func_00283B98(obj->rotation.f[0],st->lean);
    obj->rotation.f[1]=func_00283B98(obj->rotation.f[1],st->pitch);
    if(obj->state==3) {
        func_0029FCC0(obj,1,&D_00189E20.position);
        qcopy_nc(&D_00189E20.rotation,&obj->rotation);
        func_L00_002E6CF0(func_PAL_L30_003B74B0,obj);
    }
    obj->flags=obj->mclass->flags;
    if(obj->interaction && func_00282E48(&obj->position,D_L30_001B9DC0)<64.0f) {
        func_002A93B0(obj);
        obj->touchTimer=60;
    }
}
