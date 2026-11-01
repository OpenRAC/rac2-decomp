#include "common.h"
typedef int Vector128 __attribute__((mode(TI)));
typedef struct { float x,y,z; } FamilyC94396F4Vector_Fc94396f4;
typedef struct { int timer; unsigned char fields[0x6c]; } TimedRecord;
extern char D_00189E20[];
typedef union { unsigned char b[0x2600]; short h[0x1300]; int i[0x980]; unsigned int u[0x980]; float f[0x980]; char *p[0x980]; Vector128 q[0x260]; } HeroTimerView;
#define HERO ((HeroTimerView *)D_00189E20)
extern int D_00138180[];

extern unsigned int D_00138320 __attribute__((nosda)),D_00138324 __attribute__((nosda));
extern int D_00138354 __attribute__((nosda));
extern unsigned char D_001A7AF8[] MACRO_ADDR;
extern int D_L18_001A8F00 MACRO_ADDR;
extern float D_L18_001B2260 MACRO_ADDR,D_L18_001B2264 MACRO_ADDR;
extern unsigned int D_L18_001B2348 MACRO_ADDR;
extern char *D_L18_001FB6E0[] __attribute__((nosda));
extern TimedRecord D_L18_002653E0[4];
extern Vector128 D_0018BBB0[32];
extern void func_L00_002B9380(void);
extern int func_00282978(short *);
extern int func_00282948(int *);
extern void func_L00_002A7A10(void);
extern int ref_L18_002DEFF8_00(int,int);
extern int func_002ABB78(char *);
extern int func_002A77E0(int);
extern float func_00282E48(void *,void *);
extern void func_00282CF0(void *,void *,void *);
extern void func_00282F20(void *,void *,float);
extern void func_002A8F70(void *,void *,unsigned int,void *,void *,float);
extern float func_L00_002D3B00(char *);
extern void func_00282C88(Vector128 *);
extern void func_00282CC0(void *,void *,void *);
extern void func_00282D30(void *,void *,float);
extern float func_00282DF0(void *);
extern void func_L00_002C3838(void);
extern void func_L00_002D36E0(float *,int,float,float,float);
extern void func_L00_002D3778(FamilyC94396F4Vector_Fc94396f4 *,FamilyC94396F4Vector_Fc94396f4 *,float);
extern void func_L00_002B30E8(void);
void func_L18_002DEFF8(void)
{
    Vector128 sum[1],delta[1];
    char **entry;
        unsigned int frame;
    int i,index,previous,n8;
    {
    char *player=D_00189E20;
    if(*(unsigned char *)(player+0x22bd)==0) func_L00_002B9380();
    (*(int *)(player+0x1b8))++; (*(int *)(player+0x1bc))++; (*(int *)(player+0x1c0))++; (*(int *)(player+0x1c4))++;
    func_00282978((short *)(player+0x1e0));
    func_00282978((short *)(player+0x1dc));
    func_00282978((short *)(player+0x1d2));
    func_00282978((short *)(player+0x1e4));
    func_00282978((short *)(player+0x1f8));
    func_00282978((short *)(player+0x1fe));
    func_00282948((int *)(player+0x1d4));
    func_00282978((short *)(player+0x210));
    func_00282978((short *)(player+0x1d0));
    func_00282978((short *)(player+0x1f4));
    func_00282978((short *)(player+0x1f6));
    func_00282978((short *)(player+0x204));
    func_00282978((short *)(player+0x206));
    func_00282978((short *)(player+0x1f0));
    func_00282978((short *)(player+0x1ec));
    func_00282978((short *)(player+0x1ee));
    func_00282978((short *)(player+0x208));
    func_00282978((short *)(player+0x200));
    func_00282978((short *)(player+0x20e));
    func_00282978((short *)(player+0x20a));
    func_00282978((short *)(player+0x214));
    func_00282978((short *)(player+0x212));
    func_00282978((short *)(player+0x1fc));
    func_00282978((short *)(player+0x216));
    func_00282978((short *)(player+0x1fa));
    func_00282978((short *)(player+0x218));
    func_00282978((short *)(player+0x1f2));
    func_00282978((short *)(player+0x21a));
    func_00282978((short *)(player+0x21c));
    func_00282978((short *)(player+0x1de));
    func_00282978((short *)(player+0x1e6));
    func_00282978((short *)(player+0x222));
    func_00282978((short *)(player+0x224));
    func_00282978((short *)(player+0x226));
    if((D_00138180[0x1a0/4]&4)==0) HERO->h[0x20c / 2]=0;
    if(HERO->h[0x21c / 2]!=0) func_L00_002A7A10();
    if(HERO->b[0x22b8 / 1]!=0) (HERO->i[0x1d8 / 4])++;
    else HERO->i[0x1d8 / 4]=0;
    if(D_00138180[0x1d4/4]!=0) { HERO->i[0x1c8 / 4]=0; (HERO->i[0x1cc / 4])++; }
    else { HERO->i[0x1cc / 4]=0; (HERO->i[0x1c8 / 4])++; }
    if(HERO->b[0x22c3 / 1]!=0 && HERO->i[0x229c / 4]==0 && HERO->i[0x340 / 4]!=0 && HERO->f[0x170 / 4]<0.001666666824f && HERO->f[0x184 / 4]<0.001666666824f) qcopy(&HERO->q[0x80/16],&HERO->q[0x2030/16]);
    if(HERO->h[0x1454 / 2]!=0) HERO->i[0x1e8 / 4]=0; else (HERO->i[0x1e8 / 4])++;
    if(HERO->i[0x24cc / 4]==0 || D_L18_001A8F00==0) {
        if(HERO->i[0x24cc / 4]!=0 && HERO->b[0x22b4 / 1]==4 && HERO->i[0x2294 / 4]!=0x6f && (D_00138180[0x1a4/4]&0x10)!=0) {
            HERO->h[0x1e0 / 2]=0; HERO->i[0x24cc / 4]=0; ref_L18_002DEFF8_00(0x91,1);
        }
        if(D_L18_001A8F00==0) {
            if(D_L18_001B2260>0.0f) (HERO->h[0x22a / 2])++; else HERO->h[0x22a / 2]=0;
            if(HERO->h[0x22a / 2]>120) { D_L18_001B2260=0.0f; HERO->h[0x22a / 2]=0; }
            if(D_L18_001B2264>0.0f) (HERO->h[0x228 / 2])++; else HERO->h[0x228 / 2]=0;
            if(HERO->h[0x228 / 2]>120) { HERO->h[0x228 / 2]=0; D_L18_001B2264=0.0f; }
        }
    }
    }
    {
    char *player=D_00189E20;
    if(HERO->h[0x224 / 2]!=0) {
        char *object;
        int j;
        object=D_L18_001FB6E0[0];
        for(j=0;object!=0;object=D_L18_001FB6E0[++j]) {
            if((func_002ABB78(object)!=0 || (object!=0 && *(void **)(object+0x24)!=0 && *(short *)(*(char **)(object+0x24)+0x46)==0x16)) && ((D_L18_001B2348&7)==((int)object>>8&7) || func_002A77E0(4)==0)) {
                if(func_00282E48(&HERO->q[0x80/16],object+0x10)<15.37f) {
                    func_00282CF0(sum,object+0x10,&HERO->q[0x80/16]);
                    func_00282F20(sum,sum,1.7f);
                    func_002A8F70(object,HERO->p[0x2290/4],0x4000000u,&HERO->q[0x80/16],sum,1.0f);
                }
            }
        }
    }
    for(i=0;i<4;i++) func_00282948(&D_L18_002653E0[i].timer);
    HERO->f[0x24dc / 4]=9999.0f;
    if(HERO->h[0x34e / 2]!=0 && func_L00_002D3B00(&HERO->q[0xf0/16])<0.0f) {
        if(HERO->i[0x23c8 / 4]==32) {
            func_00282C88(sum);
            n8=8;
            for(i=0;i<n8;i++) {
                index=(HERO->i[0x23c4 / 4]-i+31)%32;
                previous=(HERO->i[0x23c4 / 4]-i+30)%32;
                func_00282CF0(delta,&HERO->q[0x1d90/16+index],&HERO->q[0x1d90/16+previous]);
                func_00282CC0(sum,sum,delta);
            }
            func_00282D30(sum,sum,1.0f/n8);
            if(func_00282DF0(sum)<0.016666668f) (HERO->h[0x202 / 2])++;
            else HERO->h[0x202 / 2]=0;
        }
    } else HERO->h[0x202 / 2]=0;
    func_L00_002C3838();
    if(HERO->b[0x22b4 / 1]==4) func_L00_002D36E0((float *)(&HERO->q[0xe0/16]),1,0.0f,0.0f,0.4f);
    else func_L00_002D36E0((float *)(&HERO->q[0xe0/16]),1,0.0f,0.0f,0.7f);
    frame=D_L18_001B2348;
    if((frame&3)==0) {
        if(HERO->b[0x22b4 / 1]==4) { HERO->f[0x24a4 / 4]=2.125f; HERO->f[0x24a8 / 4]=1.25f; }
        else if(D_001A7AF8[7]!=0) { HERO->f[0x24a4 / 4]=14.0f; HERO->f[0x24a8 / 4]=4.5f; }
        else { HERO->f[0x24a4 / 4]=4.25f; HERO->f[0x24a8 / 4]=2.25f; }
    }
    if(HERO->f[0x31c / 4]<4.0f) {
        qcopy(&HERO->q[0xd0/16],&HERO->q[0x2d0/16]);
        func_L00_002D3778((FamilyC94396F4Vector_Fc94396f4 *)(&HERO->q[0xd0/16]),(FamilyC94396F4Vector_Fc94396f4 *)(&HERO->q[0xd0/16]),0.5f);
    } else qcopy(&HERO->q[0xd0/16],&HERO->q[0xe0/16]);
    {
    char *target=HERO->p[0x5c0/4];
    if(target!=0) {
        if((*(unsigned short *)(target+0x34)&0x1000)==0 || target==HERO->p[0x33c/4]) HERO->p[0x5c0/4]=0;
        if(HERO->p[0x5c0/4]!=0 && HERO->i[0x1248 / 4]!=0x2e) HERO->p[0x5c0/4]=0;
    }
    }
    if(HERO->f[0x88 / 4]<1.0f) func_L00_002B30E8();
    }
}
