#include "include_asm.h"

INCLUDE_ASM("asm/pal/levels", func_PAL_L11_0043C288);


#include "common.h"
extern int D_L11_001B359C __attribute__((sda));
extern char D_L11_001BA8C0[];
extern void func_00282CF0(float *, const float *, const float *);
extern void func_00282F20(char *, char *, float);
extern void func_00282CC0(char *, char *, char *);
extern int func_00283CF0(float);
extern void func_002A7750(void *, int, int);
extern char *func_002A9640(char *, int, int);
extern float func_PAL_002AA108(char *, char *);
extern void func_PAL_002AC290(char *, char *);
extern int D_L11_001FFA78[];
extern void func_PAL_L11_0043EBD0(char *, char *);
extern void func_PAL_L11_0043E968(char *, int, int);
extern void func_L11_00439BF0(char *);
extern void func_PAL_L11_004400D0(char *);
extern void func_L11_004417A8(char *, char *);
extern void func_002A7A00(float *, float, float);
extern void func_PAL_002B15D8(char *, int, float *, float, float, float, float, unsigned char);
extern int func_002B3BA8(char *, int, int, int, float, float);
extern float func_00282E48(void *, void *);
extern void func_002A93B0(char *);
typedef struct { char pad[0x330]; int children[10]; char gap[0x28]; unsigned char flags[10]; } ChildSlots;
#define CHILD(o,i) ((char *)(D_L11_001B359C + (((ChildSlots *)(*(char **)((o)+0x68)))->children[i] << 8)))
void func_L11_004375B8(char *);

void func_PAL_L11_0043CB48(char *obj)
{
    char *s = *(char **)(obj+0x68);
    float v[4], direction[4], velocity[4], random[4], pos[4];
    int i, j, k, consumed;
    char *hit;
    float damage, scale;
    if (*(unsigned char *)(obj+0x20)==0) {
        *(unsigned char *)(s+0x48)=func_00283CF0(15.0f);
        *(unsigned char *)(s+0x4A)=func_00283CF0(4.0f);
        *(int *)(s+0x38C)=-1;
        if (*(short *)(s+0x24)==0) {
            *(short *)(s+0x24)=30;
            *(float *)(s+0x20)=3e+01f;
        }
        func_L11_00439BF0(obj);
    }
    if (*(unsigned char *)(obj+0x20)>=3 && !*(int *)(s+0x364)) {
        consumed=0;
        for (i=0;i<10;i++) {
            if (!((ChildSlots *)s)->flags[i]) {
                hit=func_002A9640(CHILD(obj,i),0x10000,0);
                damage=func_PAL_002AA108(obj,hit);
                if (damage!=0.0f) {
                    D_L11_001FFA78[*(unsigned char *)(s+0x37)]+=(int)(damage*32.0f);
                    func_PAL_002AC290(CHILD(obj,i),s+0x70);
                    if (*(float *)(hit+0x2C)>3.0f) {
                        scale=damage*0.125f;
                        if (scale>1.0f) scale=1.0f;
                        else if (scale<0.0f) scale=0.0f;
                        func_00282F20((char *)v,hit+0x10,scale*0.4f);
                        func_00282CC0(s+0x110+i*16,s+0x110+i*16,(char *)v);
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
                        func_PAL_L11_0043EBD0(obj,records+(((ChildSlots *)*(char **)(obj+0x68))->children[i]<<8)+0x10);
                        func_PAL_L11_0043E968(obj,i,1);
                        func_002A7750(obj,5,-1);
                    }
                } else *(float *)(s+0x20)-=damage;
                *(unsigned char *)((((ChildSlots *)*(char **)(obj+0x68))->children[i]<<8)+D_L11_001B359C+0xA8)=255;
            }
        }
        hit=func_002A9640(obj,0x10000,0);
        damage=func_PAL_002AA108(obj,hit);
        if (damage!=0.0f) {
            func_PAL_002AC290(obj,s+0x70);
            D_L11_001FFA78[*(unsigned char *)(s+0x37)]+=(int)(damage*32.0f);
            if (*(float *)(hit+0x2C)>3.0f) {
                scale=damage*0.125f;
                if (scale>1.0f) scale=1.0f;
                else if (scale<0.0f) scale=0.0f;
                func_00282F20((char *)direction,hit+0x10,scale*0.8f);
                func_00282CC0(obj+0x10,obj+0x10,(char *)direction);
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
        func_00282CF0(direction,(float *)D_L11_001BA8C0,(float *)(obj+0x10));
        func_00282F20((char *)direction,(char *)direction,0.6f);
        qcopy(v,s+0x100);
        func_PAL_L11_0043EBD0(obj,(char *)v);
        func_002A7A00(random,0.040000003f,0.080000006f);
        func_00282CC0((char *)velocity,(char *)direction,(char *)random);
        for (k=0;k<10;k++) {
            if (!((ChildSlots *)s)->flags[k]) {
                qcopy(pos,s+0x100+k*16);
                func_002A7A00(random,0.20000002f,0.40000004f);
                func_00282CC0((char *)velocity,(char *)direction,(char *)random);
                func_PAL_002B15D8(CHILD(obj,k),3,velocity,3,6,3,6,255);
                func_PAL_L11_0043EBD0(obj,(char *)pos);
                func_PAL_L11_004400D0(CHILD(obj,k));
            }
        }
    }
    *(int *)(s+0x328)=func_002B3BA8(obj,*(int *)(s+0x36C),0,0,255,255);
    if (*(unsigned char *)(obj+0x31) && func_00282E48(obj+0x10,D_L11_001BA8C0)<48.0f) {
        func_002A93B0(obj);
        *(unsigned char *)(obj+0x6F)=45;
    }
}


extern unsigned char D_L11_00438880[];
extern void func_802F8AD0(void *a0, void *a1);
extern void func_80338398(void *a0, void *a1, int a2, int a3, float f12);
extern void func_L11_004395C8(char *p);
extern void func_L11_00437EA8(char *p);
extern void func_L11_00437FD0(char *p);
extern void func_L11_00438460(char *p);
extern void func_L11_004386B8(char *p);

/* Runs the ten rotors' update, one frame each, and restarts the entry timer. */
void func_PAL_L11_0043D280(char *p)
{
    char *q = *(char **)(p + 0x68);
    int i;

    func_802F8AD0((void *)D_L11_00438880, p);

    for (i = 12; i >= 0; i--)
        ;

    if (*(unsigned char *)(p + 0x20) >= 2) {
        func_L11_004395C8(p);
        func_L11_00437EA8(p);
        func_L11_00437FD0(p);
        func_L11_00438460(p);
        func_L11_004386B8(p);
    }
    if (*(unsigned short *)(p + 0x96) <= 0xFFFE) {
        (*(unsigned short *)(p + 0x96))++;
    }
    func_80338398(p, q + 0x80, 1, 1, 2.5f);
}

