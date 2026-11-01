#include "include_asm.h"

#include "common.h"
extern void func_L09_003F9040(char *);
extern void func_L09_003F7788(char *, char *);
extern void func_PAL_L09_003FC118(char *);
extern void func_0029FCC0(char *, int, void *);
extern void func_002AAA00(void *, void *, int, float, float,float, float);
extern void func_00282CF0(void *, void *,void *);
extern float func_00282E20(void *);
extern float func_00283248(float, float);
extern float func_00283BE0(float, float);
extern void func_002AEC48(char *,void *, int, float, float);
extern float func_002A7878(float, float);
#define I(p, o) (*(int *)((p) + (o)))
#define F(p, o) (*(float *)((p) + (o)))
#define B(p, o) (*(unsigned char *)((p) + (o)))
#define P(p, o) (*(char **)((p) + (o)))

void func_PAL_L09_003FDB18(char *object)
{
    char *data=P(object,0x68);

    float v[4] __attribute__((aligned(16)));
    int i;
    float angle;
    func_L09_003F9040(object);
    {
        char *partner = P(data, 0x2F8);
        if (!partner || *(short *)(partner + 0xAA) != 0xD0E ||
            B(partner, 0x20) == 254 || B(partner, 0x20) == 253)
            return;
        func_L09_003F7788(object, partner);
    }
    func_L09_003F9040(P(data,0x2F8));
    func_0029FCC0(object,0,P(data,0x2F8)+0x10);
    func_002AAA00(P(data,0x2F8)+0xF8,data+0x2FC,0,F(data,0x2EC),F(data,0x114),F(data,0x118),F(data,0x11C));
    F(P(data,0x2F8),0x48)=F(object,0x48);
    if ((unsigned)(B(object,0x20)-1)<3 || B(object,0x20)==16) func_PAL_L09_003FC118(object);
    if (I(data,0x204)==1 && !B(data,0x30F)) {
        func_0029FCC0(P(data,0x2F8),4,v);
        func_00282CF0(v,data+0x1F0,v);
        angle=func_00282E20(v);
        angle=-func_00283248(angle,v[2]);
        F(data,0x274)=func_00283BE0(angle,F(P(data,0x2F8),0xF4));
        angle=func_00283248(v[0],v[1]);
        F(data,0x278)=func_00283BE0(angle,F(P(data,0x2F8),0xF8));
    }
    func_002AEC48(P(data,0x2F8),data+0x210,3,0.028800001f,0.43200004f);
    if (!B(data,0x30F) && (unsigned)B(P(data,0x2F8),0x42)>=8 && (unsigned)B(P(data,0x2F8),0x42)<11) {
        for(i=0;i<2;i++) {
            char *part=data+i*0x80;
            if ((*(unsigned short *)(P(data,0x2F8)+0x7C)>>(i+4))&1) {
                func_0029FCC0(P(data,0x2F8),i,v);
                func_00282CF0(v,data+0x1F0,v);
                angle=func_00282E20(v);
                F(part,0x384)=-func_00283248(angle,v[2]);
                angle=func_00283248(v[0],v[1]);
                F(part,0x388)=func_00283BE0(angle,F(P(data,0x2F8),0xF8));
                if (i) {
                    if (F(part, 0x388) > 0.087266475f)
                        F(part, 0x388) = 0.087266475f;
                } else {
                    if (F(data, 0x388) < -0.087266475f)
                        F(data, 0x388) = -0.087266475f;
                }
            }
        }
    } else if (B(data,0x30F)) {
        char *part=data;
        for(i=1;i>=0;i--,part+=0x80) {
            F(part,0x384)=func_002A7878(-1.57079637f,1.57079637f)*0.5f;
            F(part,0x388)=func_002A7878(-1.57079637f,1.57079637f)*0.5f;
        }
    }
    for(i=0;i<2;i++)
        func_002AEC48(P(data,0x2F8),data+0x320+i*0x80,i+7,0.028800001f,0.43200004f);
}
