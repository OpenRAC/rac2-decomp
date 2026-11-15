#include "common.h"
typedef int TI128 __attribute__((mode(TI)));
extern int D_L11_001B359C __attribute__((sda));
extern char D_L11_001BA8C0[];
extern void func_00282CF0(float *, const float *, const float *);
extern void func_00282F20(char *, char *, float);
extern void func_00282CC0(char *, char *, char *);
extern int func_00283CF0(float);
extern void func_002A7750(void *, int, int);
extern char *func_002A9640(char *, int, int);
extern float func_002A96A0(char *, char *);
extern void func_002AB800(char *, char *);
extern int D_L11_001FFA78[];
extern void func_L11_00439640(char *, char *);
extern void func_L11_004393D8(char *, int, int);
extern void func_L11_00439BF0(char *);
extern void func_L11_0043AB28(char *);
extern void func_L11_004417A8(char *, char *);
extern void func_002A7A00(float *, float, float);
extern void func_002B0A68(char *, int, float *, float, float, float, float, unsigned char);
extern int func_002B3BA8(char *, int, int, int, float, float);
extern float func_00282E48(void *, void *);
extern void func_002A93B0(char *);
typedef struct { char pad[0x330]; int children[10]; char gap[0x28]; unsigned char flags[10]; } ChildSlots;
#define CHILD(o,i) ((char *)(D_L11_001B359C + (((ChildSlots *)(*(char **)((o)+0x68)))->children[i] << 8)))

void func_L11_004375B8(char *);

void func_L11_004375B8(char *obj)
{
    char *s = *(char **)(obj+0x68);
    float v[4], direction[4], velocity[4], random[4], pos[4];
    int i, j, k, consumed;
    char *hit;
    float damage, scale;
    if (*(unsigned char *)(obj+0x20)==0) {
        *(unsigned char *)(s+0x48)=FloatToInt(15.0f);
        *(unsigned char *)(s+0x4A)=FloatToInt(4.0f);
        *(int *)(s+0x38C)=-1;
        if (*(short *)(s+0x24)==0) {
            *(short *)(s+0x24)=30;
            *(float *)(s+0x20)=30.0f;
        }
        func_L11_00439BF0(obj);
    }
    if (*(unsigned char *)(obj+0x20)>=3 && !*(int *)(s+0x364)) {
        consumed=0;
        for (i=0;i<10;i++) {
            if (!((ChildSlots *)s)->flags[i]) {
                hit=func_002A9640(CHILD(obj,i),0x10000,0);
                damage=func_002A96A0(obj,hit);
                if (damage!=0.0f) {
                    D_L11_001FFA78[*(unsigned char *)(s+0x37)]+=(int)(damage*32.0f);
                    func_002AB800(CHILD(obj,i),s+0x70);
                    if (*(float *)(hit+0x2C)>3.0f) {
                        scale=damage*0.125f;
                        if (scale>1.0f) scale=1.0f;
                        else if (scale<0.0f) scale=0.0f;
                        vec_scale_to_length((char *)v,hit+0x10,scale*0.2777777910232544f);
                        FastVecAdd(s+0x110+i*16,s+0x110+i*16,(char *)v);
                        func_002A7750(obj,5,-1);
                    }
                }
                if (*(short *)(s+0x378)>=4) {
                    *(float *)(s+0x360)+=damage;
                    if (!consumed && *(float *)(s+0x360)>10.0f) {
                        char *records=(char *)D_L11_001B359C;
                        *(float *)(s+0x20)-=*(float *)(s+0x360);
                        (*(short *)(s+0x378))--;
                        *(float *)(s+0x360)=0;
                        consumed=1;
                        func_L11_00439640(obj,records+(((ChildSlots *)*(char **)(obj+0x68))->children[i]<<8)+0x10);
                        func_L11_004393D8(obj,i,1);
                        func_002A7750(obj,5,-1);
                    }
                } else *(float *)(s+0x20)-=damage;
                *(unsigned char *)((((ChildSlots *)*(char **)(obj+0x68))->children[i]<<8)+D_L11_001B359C+0xA8)=255;
            }
        }
        hit=func_002A9640(obj,0x10000,0);
        damage=func_002A96A0(obj,hit);
        if (damage!=0.0f) {
            func_002AB800(obj,s+0x70);
            D_L11_001FFA78[*(unsigned char *)(s+0x37)]+=(int)(damage*32.0f);
            if (*(float *)(hit+0x2C)>3.0f) {
                scale=damage*0.125f;
                if (scale>1.0f) scale=1.0f;
                else if (scale<0.0f) scale=0.0f;
                vec_scale_to_length((char *)direction,hit+0x10,scale*0.5555555820465088f);
                FastVecAdd(obj+0x10,obj+0x10,(char *)direction);
            }
            if (*(short *)(s+0x378)>=4) *(float *)(s+0x360)+=damage;
            else *(float *)(s+0x20)-=damage;
        }
        *(unsigned char *)(obj+0xA8)=255;
        if (*(unsigned char *)(obj+0x20)!=6 && *(unsigned char *)(obj+0x20)!=1 &&
            *(unsigned char *)(obj+0x20)!=7 && *(unsigned char *)(obj+0x20)!=0 && *(float *)(s+0x20)<=0.0f)
            func_002A7750(obj,6,2);
    } else {
        *(unsigned char *)(obj+0xA8)=255;
        for (j=0;j<10;j++) if (!((ChildSlots *)s)->flags[j]) *(unsigned char *)((((ChildSlots *)*(char **)(obj+0x68))->children[j]<<8)+D_L11_001B359C+0xA8)=255;
        *(float *)(s+0x360)=0;
    }
    if (*(char **)(s+0x364) && *(unsigned char *)(*(char **)(s+0x364)+0x20)<2) {
        *(int *)(s+0x364)=0;
        func_L11_004417A8(*(char **)(obj+0xB8),obj);
    }
    if (*(unsigned char *)(obj+0x20)>=2 && *(unsigned char *)(s+0x2E)==2) {
        *(float *)(s+0x20)=0;
        func_L11_00439BF0(obj);
        FastVecSub(direction,(float *)D_L11_001BA8C0,(float *)(obj+0x10));
        vec_scale_to_length((char *)direction,(char *)direction,0.5f);
        qcopy(v,s+0x100);
        func_L11_00439640(obj,(char *)v);
        func_002A7A00(random,0.03333333507180214f,0.06666667014360428f);
        FastVecAdd((char *)velocity,(char *)direction,(char *)random);
        for (k=0;k<10;k++) {
            if (!((ChildSlots *)s)->flags[k]) {
                qcopy(pos,s+0x100+k*16);
                func_002A7A00(random,0.1666666716337204f,0.3333333432674408f);
                FastVecAdd((char *)velocity,(char *)direction,(char *)random);
                func_002B0A68(CHILD(obj,k),3,velocity,3,6,3,6,255);
                func_L11_00439640(obj,(char *)pos);
                func_L11_0043AB28(CHILD(obj,k));
            }
        }
    }
    *(int *)(s+0x328)=func_002B3BA8(obj,*(int *)(s+0x36C),0,0,255,255);
    if (*(unsigned char *)(obj+0x31) && fast_vec_dist(obj+0x10,D_L11_001BA8C0)<48.0f) {
        func_002A93B0(obj);
        *(unsigned char *)(obj+0x6F)=45;
    }
}
