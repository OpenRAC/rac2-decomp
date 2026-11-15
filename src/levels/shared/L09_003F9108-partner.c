#include "common.h"

/* Keep the attachment and random-angle paths separate, as in retail. */
extern void func_L09_003F9040(char *);
extern void func_L09_003F7788(char *, char *);
extern void func_L09_003F7840(char *);
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

/* Keeps the trooper torso attached to the enemy and turns its head and arms toward the hero. */
void func_L09_003F9108(char *object)
{
    char *data=P(object,0x68);

    float point[4] __attribute__((aligned(16)));
    int i;
    float angle;
    ApplyLevelColourTint(object);
    {
        char *partner = P(data, 0x2F8);
        if (!partner || *(short *)(partner + 0xAA) != 0xD0E /* Megacorp Trooper Torso */ ||
            B(partner, 0x20) == 254 || B(partner, 0x20) == 253)
            return;
        CopyMobyColor(object, partner);
    }
    ApplyLevelColourTint(P(data,0x2F8));
    TransformMobyJointToWorld(object,0,P(data,0x2F8)+0x10);
    ApproachTargetWithDirectionMode(P(data,0x2F8)+0xF8,data+0x2FC,0,F(data,0x2EC),F(data,0x114),F(data,0x118),F(data,0x11C));
    F(P(data,0x2F8),0x48)=F(object,0x48);
    if ((unsigned)(B(object,0x20)-1)<3 || B(object,0x20)==16) DrawTrooperFlameSprays(object);
    if (I(data,0x204)==1 && !B(data,0x30F)) {
        TransformMobyJointToWorld(P(data,0x2F8),4,point);
        FastVecSub(point,data+0x1F0,point);
        angle=vec_length_xy(point);
        angle=-FastMatrixHelperA(angle,point[2]);
        F(data,0x274)=fast_subtract_rotations(angle,F(P(data,0x2F8),0xF4));
        angle=FastMatrixHelperA(point[0],point[1]);
        F(data,0x278)=fast_subtract_rotations(angle,F(P(data,0x2F8),0xF8));
    }
    UpdateEasedNode(P(data,0x2F8),data+0x210,3,0.02f,0.3f);
    if (!B(data,0x30F) && (unsigned)B(P(data,0x2F8),0x42)>=8 && (unsigned)B(P(data,0x2F8),0x42)<11) {
        for(i=0;i<2;i++) {
            char *part=data+i*0x80;
            if ((*(unsigned short *)(P(data,0x2F8)+0x7C)>>(i+4))&1) {
                TransformMobyJointToWorld(P(data,0x2F8),i,point);
                FastVecSub(point,data+0x1F0,point);
                angle=vec_length_xy(point);
                F(part,0x384)=-FastMatrixHelperA(angle,point[2]);
                angle=FastMatrixHelperA(point[0],point[1]);
                F(part,0x388)=fast_subtract_rotations(angle,F(P(data,0x2F8),0xF8));
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
            F(part,0x384)=RandomFloatRange(-1.57079637f,1.57079637f)*0.5f;
            F(part,0x388)=RandomFloatRange(-1.57079637f,1.57079637f)*0.5f;
        }
    }
    for(i=0;i<2;i++)
        UpdateEasedNode(P(data,0x2F8),data+0x320+i*0x80,i+7,0.02f,0.3f);
}
