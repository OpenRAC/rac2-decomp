#include "common.h"
typedef int TI4BF0 __attribute__((mode(TI)));
typedef float Vec4BF0[4] __attribute__((aligned(16)));
typedef struct { char prefix[0x74]; float damage; char tail[0x68]; } Weapon4BF0;
extern Weapon4BF0 D_L00_00262570[] __attribute__((nosda));
extern unsigned char D_00139568[];
typedef struct { char pad[0x2290]; char *target; } Hero4BF0;
extern Hero4BF0 D_00189E20;
typedef struct { char pad[0x160]; float amount; int unused, timer, state; } Camera4BF0;
extern Camera4BF0 D_L00_001B8C80;
extern char *D_L00_001B2BB4 __attribute__((sda));
extern char *D_L00_001B2BB8;
extern int *D_L00_001B2BBC[] MACRO_ADDR;
extern float D_L00_001B0830 __attribute__((sda));
extern float D_L00_001B0834 __attribute__((sda));
extern char *D_L00_001B2BB4_1 MACRO_ADDR;
extern char *D_L00_001C3280[];
extern int func_002B4038(short,int);
extern void func_00300190(void *,void *);
extern int func_L00_00329E90(void *,int,void *);
extern char *func_L00_0032A088(short,int);
extern int func_L00_003EEE20(int);
extern void func_002AFFD8(void *,void *,int);
extern void func_00282CC0(void *,void *,void *);
extern void func_002AC728(void *,void *,int,float,float);
extern void func_L00_003EFF58(void *,int,void *,void *,float);
extern void func_L00_003EF560(void *,void *);
extern int func_00283DB8(void *,float);
extern float func_00283CE0(int);
extern int func_00283CF0(float);
extern int func_00277F48(void *,int,void *,int,float);
extern int func_002AB1F0(void *);
extern void func_00282CF0(void *,void *,void *);
extern void func_00282F20(void *,void *,float);
extern void func_002A8C00(float,void *,void *,int,void *);
extern void func_002A8E20(void *,void *);
extern void func_0032D758(void *,int,int);
extern int func_00282948(void *);
extern void func_L00_003EF550(void);
extern void func_0029F338(void *);
extern void func_L00_003F00A0(void *);
extern void ref_L00_003EEE90_00(void (*)(void *),void *);
extern void func_L00_003EFA00(void *);
typedef struct { char pad[0x10]; float phase; int timer; float rate; int alpha, unused, count, handle; } State4BF0;
void func_L00_003EEE90(char *object)
{
    Vec4BF0 center, query, direction;
    struct { Vec4BF0 point; char pad[8]; unsigned char type, flags; short id; int unused; int active; } hit;
    int allocation;
    int *timer;
    State4BF0 *data = *(State4BF0 **)(object+0x68);
    float scale;
    if (*(unsigned char *)(object+0x20) && !func_002B4038(*(short *)(object+0xAA),data->handle)) goto destroy;
    func_00300190(object+0x10,object+0x10);
    switch (*(unsigned char *)(object+0x20)) {
    case 0: {
        int i;
        char *mem;
        *(unsigned char *)(object+0x20)=1;
        data->phase=0;
        data->timer=20;
        data->rate=2.0f/3.0f;
        data->alpha=127;
        data->count=111;
        data->handle=func_L00_00329E90(object,0,&allocation);
        mem=func_L00_0032A088(*(short *)(object+0xAA),data->handle);
        D_L00_001B2BB4=mem;
        D_L00_001B2BB8=(char *)func_L00_003EEE20((int)(mem+0x50));
        D_L00_001B2BBC[0]=(int *)func_L00_003EEE20((int)(D_L00_001B2BB8+0xA000));
        i=0;
        do { D_L00_001B2BBC[0][i]=0; i++; } while(i<144);
        { char *p = D_L00_001B2BB8+319*128+124;
        for(i=319;i>=0;i--,p-=128) *(int *)p=0; }
        *(int *)(D_L00_001B2BB4_1+0x30)=0;
        qcopy(center,object+0x10);
        center[2]+=1.0f;
        func_L00_003EFF58(object,20,object+0x10,data,1.0f/6.0f);
        func_L00_003EF560(object,object+0x10);
        qcopy(query,center);
        query[3]=2.0f;
        if(func_00283DB8(query,100.0f)!=-1) {
            D_L00_001B8C80.amount=0.45f;
            D_L00_001B8C80.timer=40;
            D_L00_001B8C80.state=0;
        }
    }
    case 1: {
        int count;
        int i;
        data->count-=5;
        if(data->count<0) data->count=0;
        data->phase+=data->rate;
        timer=&data->timer;
        scale=1.0f-func_00283CE0(*timer)/func_00283CE0(20);
        scale*=6.0f;
        count=func_00277F48(object+0x10,0,object,0,scale+0.001f);
        for(i=0;i<count;i++) {
            if((func_002AB1F0(D_L00_001C3280[i]) || (*(unsigned short *)(D_L00_001C3280[i]+0x34)&0x4000)) && D_L00_001C3280[i]!=D_00189E20.target && *(short *)(D_L00_001C3280[i]+0xAA)!=0xA5A) {
                func_00282CF0(direction,D_L00_001C3280[i]+0x10,object+0x10);
                func_00282F20(direction,direction,1.0f);
                func_00282F20(&hit,&hit,1.0f);
                func_002A8C00(((Weapon4BF0 *)((unsigned int)D_L00_00262570 + D_00139568[0x2A] * sizeof(Weapon4BF0)))->damage,&hit,object,0x830000,direction);
                *(TI4BF0 *)hit.point = *(TI4BF0 *)direction;
                hit.flags=3; hit.type=5; hit.active=1;
                hit.point[3]=5627.925f;
                hit.id=*(short *)(D_L00_001C3280[i]+0xAA);
                func_002A8E20(D_L00_001C3280[i],&hit);
                func_0032D758(D_L00_001C3280[i],42,*(int *)(object+0xB8));
            }
        }
        if(func_00282948(timer)) {
            *(unsigned char *)(object+0x20)=2;
            data->timer=40;
        }
        break;
    }
    case 2:
        data->phase+=data->rate;
        scale=func_00283CE0(data->timer)*0.025f;
        if(func_00282948(&data->timer)) {
            if(data->alpha) --data->alpha;
            else { data->alpha=0; *(unsigned char *)(object+0x20)=6; }
        } else data->alpha=func_00283CF0(func_00283CE0(127)*scale);
        break;
    case 6:
        data->phase+=data->rate;
        if(!*(int *)(D_L00_001B2BB4_1+0x38)) {
destroy:
            func_L00_003EF550();
            func_0029F338(object); return;
        }
        break;
    }
    D_L00_001B0834-=0.04f;
    if(D_L00_001B0830 < -8.0f) D_L00_001B0830+=8.0f;
    if(D_L00_001B0834 < -8.0f) D_L00_001B0834+=8.0f;
    func_L00_003F00A0(object);
    ref_L00_003EEE90_00(func_L00_003EFA00,object);
}
