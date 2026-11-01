#include "include_asm.h"

extern void func_00337210(int *);
extern char D_001AA7D8[];
extern int D_001AE470 __attribute__((sda));
extern int D_001AE474 __attribute__((sda));
extern int D_001AE478 __attribute__((sda));
extern int D_001AE480 __attribute__((sda));
extern int D_001AE488 __attribute__((sda));
extern int D_001AE490 __attribute__((sda));
extern int D_001AE498 __attribute__((sda));

void func_PAL_00348520(char *o)
{
    int f[23];

    f[20] = 0;
    f[11] = 0;
    f[13] = 0;
    f[21] = 1;
    f[19] = *(int *)(o + 0x504);
    f[21] = ((*(int *)(o + 0x508) ^ 3) == 0);
    f[3] = *(int *)(o + 0x4FC);
    f[4] = *(int *)(o + 0x500);
    f[16] = (int)(o + 0x4B8);
    f[9] = (int)&D_001AE498;
    f[14] = 3;
    f[1] = D_001AE470;
    f[2] = D_001AE474;
    f[0] = (int)D_001AA7D8;
    f[17] = (int)(o + 0x220);
    f[10] = (int)(o + 0x130);
    f[12] = (int)(o + 0x17C);
    f[15] = (int)(o + 0x278);
    f[18] = *(int *)(o + 0x470);
    f[8] = (int)&D_001AE490;
    f[7] = (int)&D_001AE488;
    f[6] = (int)&D_001AE480;
    f[5] = (int)&D_001AE478;
    f[22] = 1;
    func_00337210(f);
}

extern char D_001AA898[];
extern int D_001AE4A0 __attribute__((sda));
extern int D_001AE4A4 __attribute__((sda));
extern int D_001AE4A8 __attribute__((sda));
extern int D_001AE4B0 __attribute__((sda));
extern int D_001AE4B8 __attribute__((sda));
extern int D_001AE4C0 __attribute__((sda));
extern int D_001AE4C8 __attribute__((sda));

void func_PAL_00348628(char *o)
{
    int f[23];

    f[20] = 0;
    f[14] = 1;
    f[11] = 0;
    f[13] = 0;
    f[21] = 1;
    f[19] = *(int *)(o + 0x504);
    f[21] = ((*(int *)(o + 0x508) ^ 1) == 0);
    f[3] = *(int *)(o + 0x4FC);
    f[4] = *(int *)(o + 0x500);
    f[16] = (int)(o + 0x4B8);
    f[9] = (int)&D_001AE4C8;
    f[1] = D_001AE4A0;
    f[2] = D_001AE4A4;
    f[0] = (int)D_001AA898;
    f[17] = (int)(o + 0x220);
    f[10] = (int)(o + 0x130);
    f[12] = (int)(o + 0x17C);
    f[15] = (int)(o + 0x278);
    f[18] = *(int *)(o + 0x470);
    f[8] = (int)&D_001AE4C0;
    f[7] = (int)&D_001AE4B8;
    f[6] = (int)&D_001AE4B0;
    f[5] = (int)&D_001AE4A8;
    f[22] = 1;
    func_00337210(f);
}

extern void func_PAL_00347A50(char *, int);
extern void func_PAL_00347CD0(char *, int);
extern void func_00345D58(char *, int);
extern int D_00138344 __attribute__((section(".data")));
extern int func_PAL_002A9FA0(int,int,int,int,int);
extern int *func_00335E20(void *);
extern void func_00335E38(void *,float,float,float,float);
extern int ref_L00_00345F70_00 __attribute__((sda));
typedef struct {float x,y;} LayoutPair;
extern LayoutPair ref_L00_00345F70_01 __attribute__((section(".data")));
extern float ref_L00_00345F70_02 __attribute__((sda));
extern float ref_L00_00345F70_03 __attribute__((sda));
extern float ref_L00_00345F70_04 __attribute__((sda));
extern float ref_L00_00345F70_05 __attribute__((sda));
extern float ref_L00_00345F70_06 __attribute__((sda));
extern float ref_L00_00345F70_07 __attribute__((sda));
extern float ref_L00_00345F70_08 __attribute__((sda));
extern float ref_L00_00345F70_09 __attribute__((sda));
extern float ref_L00_00345F70_10 __attribute__((sda));
extern float ref_L00_00345F70_11 __attribute__((sda));
extern float ref_L00_00345F70_12[] __attribute__((sda));
extern float ref_L00_00345F70_13[] __attribute__((sda));
extern float ref_L00_00345F70_14[] __attribute__((sda));
extern float ref_L00_00345F70_15[] __attribute__((sda));
extern float ref_L00_00345F70_16[] __attribute__((sda));
extern float ref_L00_00345F70_17[] __attribute__((sda));
extern float ref_L00_00345F70_18[] __attribute__((sda));
extern float ref_L00_00345F70_19[] __attribute__((sda));
extern float ref_L00_00345F70_20[] __attribute__((sda));
extern float ref_L00_00345F70_21[] __attribute__((sda));

int func_PAL_003480C8(char *o,int buttons,int *out)
{
 LayoutPair offset;
 int *color;
 int mode;
 *out=*(int *)(o+0x508);
 *(int *)(o+0x504)=0;
 mode=*(int *)(o+0x508);
 ref_L00_00345F70_00=-1;
 offset=ref_L00_00345F70_01;
 switch(mode) {
 case 0:*out=0;func_PAL_00347A50(o,buttons);break;
 case 3:*out=mode;func_PAL_00347CD0(o,buttons);break;
 case 1:*out=mode;func_00345D58(o,buttons);break;
 }
 if(D_00138344&0xf000) func_PAL_002A9FA0(0,0,1,0,1);
 color=func_00335E20(o+0x17c);
 *color=func_PAL_002A9FA0(0x60442d00,0x70fffeed,20,0,0);
 func_00335E38(o+0x0,ref_L00_00345F70_02+(*(float **)(o+0x470))[0],ref_L00_00345F70_12[0]+(*(float **)(o+0x470))[1],0.0f,0.0f);
 func_00335E38(o+0x4c,ref_L00_00345F70_03+(*(float **)(o+0x470))[0],ref_L00_00345F70_13[0]+(*(float **)(o+0x470))[1],0.0f,0.0f);
 func_00335E38(o+0x98,ref_L00_00345F70_04+(*(float **)(o+0x470))[0],ref_L00_00345F70_14[0]+(*(float **)(o+0x470))[1],0.0f,0.0f);
 func_00335E38(o+0xe4,ref_L00_00345F70_05+(*(float **)(o+0x470))[0],ref_L00_00345F70_15[0]+(*(float **)(o+0x470))[1],0.0f,0.0f);
 func_00335E38(o+0x130,ref_L00_00345F70_06+(*(float **)(o+0x470))[0],ref_L00_00345F70_16[0]+(*(float **)(o+0x470))[1],0.0f,0.0f);
 func_00335E38(o+0x1c8,offset.x+(*(float **)(o+0x470))[0],offset.y+(*(float **)(o+0x470))[1],0.0f,0.0f);
 func_00335E38(o+0x310,ref_L00_00345F70_07+(*(float **)(o+0x470))[0],ref_L00_00345F70_17[0]+(*(float **)(o+0x470))[1],0.0f,0.0f);
 func_00335E38(o+0x2B8,ref_L00_00345F70_08+(*(float **)(o+0x470))[0],ref_L00_00345F70_18[0]+(*(float **)(o+0x470))[1],0.0f,0.0f);
 func_00335E38(o+0x368,ref_L00_00345F70_09+(*(float **)(o+0x470))[0],ref_L00_00345F70_19[0]+(*(float **)(o+0x470))[1],0.0f,0.0f);
 func_00335E38(o+0x3C0,ref_L00_00345F70_10+(*(float **)(o+0x470))[0],ref_L00_00345F70_20[0]+(*(float **)(o+0x470))[1],0.0f,0.0f);
 func_00335E38(o+0x418,ref_L00_00345F70_11+(*(float **)(o+0x470))[0],ref_L00_00345F70_21[0]+(*(float **)(o+0x470))[1],0.0f,0.0f);
 return 0;
}

typedef struct { unsigned int lo; unsigned int hi; } Word2_462A8;
extern char D_00259CE0[];
extern Word2_462A8 D_001AE0B0 __attribute__((nosda));
extern int D_001AE440 __attribute__((sda));
extern int D_001AE444 __attribute__((sda));
extern int D_001AE448 __attribute__((sda));
extern int D_001AE450 __attribute__((sda));
extern int D_001AE458 __attribute__((sda));
extern int D_001AE460 __attribute__((sda));
extern int D_001AE468 __attribute__((sda));
static __inline__ void initDescriptor_462A8(int *f) { f[20] = 0; f[21] = 1; }

void func_PAL_00348400(char *o)
{
    struct { Word2_462A8 q; int f[23] __attribute__((aligned(16))); } local;

    local.q = D_001AE0B0;

    initDescriptor_462A8(local.f);
    local.f[19] = *(int *)(o + 0x504);
    local.f[21] = (*(int *)(o + 0x508) == 0);
    local.f[3] = *(int *)(o + 0x4FC);
    local.f[4] = *(int *)(o + 0x500);
    local.f[16] = (int)(o + 0x4B8);
    local.f[9] = (int)&D_001AE468;
    local.f[1] = D_001AE440;
    local.f[2] = D_001AE444;
    local.f[0] = (int)D_00259CE0;
    local.f[17] = (int)(o + 0x220);
    local.f[10] = (int)(o + 0x130);
    local.f[12] = (int)(o + 0x17C);
    local.f[15] = (int)(o + 0x278);
    local.f[18] = *(int *)(o + 0x470);
    local.f[8] = (int)&D_001AE460;
    local.f[7] = (int)&D_001AE458;
    local.f[6] = (int)&D_001AE450;
    local.f[5] = (int)&D_001AE448;
    local.f[14] = 0;
    local.f[11] = 0;
    local.f[13] = 0;
    local.f[20] = (int)&local.q;
    local.f[22] = 1;
    func_00337210(local.f);
}
