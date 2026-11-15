#include "common.h"
typedef int TI128 __attribute__((mode(TI)));
typedef union { TI128 q; float f[4]; } Vector;
extern char D_L00_001B8DC0[];
extern void func_002A0F48(void *);
typedef struct { char pad[0x2290]; char *camera; int mode; char gap[0x254]; short alternate; } ProjectileOwner;
extern ProjectileOwner D_00189E20;
extern void func_00282D30(char *, char *, float);
extern float func_002A7940(void);
extern char *func_0029EFD0(int);
extern unsigned char D_00139587;
typedef struct { char pad[0x50]; float speed; char rest[0x8C]; } ProjectileTuning;
extern ProjectileTuning D_L00_00262570[];
extern char D_L00_001BF220[];
extern void func_00282CC0(void *, void *, void *);
extern void func_00282CF0(void *, void *, void *);
extern void func_00282F20(void *, void *, float);
extern int func_002761F8(void *, void *, int, void *, int);
extern char *func_002AB1F0(void *);
extern void func_002AFFD8(void *, void *, int);
extern void func_003001E0(void *, void *, void *);
extern void func_L00_003EE100(void *);
extern int func_00283CF0(float);
extern float func_00283CE0(int);
extern float func_002A7878(float, float);

/* Allocate a projectile and initialize its position, velocity and random phases. */
char *func_L00_003ECD80(char *position, char *source, char *target)
{
    Vector a,b,c,d;
    char *object = CreateMoby(0xCBB);
    char *state, *info;
    float speed;
    if (object) {
        *(unsigned char *)(object+0x30) = 255;
        *(short *)(object+0x34) = 256;
        *(short *)(object+0x32) = 255;
        object[0x31] = 1;
        *(char **)(object+0xB8) = source;
        object[0x20] = 0;
        state = *(char **)(object+0x68);
        speed = (*(ProjectileTuning *)(D_00139587 * 224 + (char *)D_L00_00262570)).speed * 0.016666667f;
        if (D_00189E20.mode==29 && (*(unsigned short *)(D_00189E20.camera+0x34)&1)) {
            qcopy(object+0x10,D_L00_001B8DC0);
            FastVecScale((char *)&a,D_L00_001B8DC0+0x250,-0.5f);
            FastVecAdd(object+0x10,object+0x10,&a);
            FastVecScale((char *)&b,D_L00_001B8DC0+0x240,-0.25f);
            FastVecAdd(object+0x10,object+0x10,&b);
            FastVecScale((char *)&c,D_L00_001B8DC0+0x230,0.1f);
            FastVecAdd(object+0x10,object+0x10,&c);
            FastVecScale((char *)&d,D_L00_001B8DC0+0x230,20.0f);
            FastVecAdd(&d,D_L00_001B8DC0,&d);
            if(CollLine(D_L00_001B8DC0,&d,0,D_00189E20.camera,0)) qcopy(&d,D_L00_001BF220);
            FastVecSub(state+0x20,&d,object+0x10);
            vec_scale_to_length(state+0x20,state+0x20,speed);
        } else {
            if (D_00189E20.alternate==1) {
                vec_scale_to_length(state+0x20,source+0xD0,-speed);
                qcopy(object+0x10,position);
            } else {
                if(target) {
                    qcopy(&a,target+0x10);
                    info=func_002AB1F0(target);
                    if(info) {
                        func_002AFFD8(target+0x10,&b,1);
                        FastVecScale((char *)&b,(char *)&b,*(float *)(info+0x10));
                        FastVecAdd(&a,&a,&b);
                    }
                    FastVecSub(state+0x20,&a,position);
                    vec_scale_to_length(state+0x20,state+0x20,speed);
                } else vec_scale_to_length(state+0x20,source+0xC0,speed);
                qcopy(object+0x10,position);
            }
        }
        *(float *)(state+0x2C)=speed;
        func_003001E0(state+0x20,state+0x20,position);
        func_L00_003EE100(object);
        *(int *)(state+0x38)=FloatToInt(20.0f);
        { float duration = IntToFloat(*(int *)(state+0x38));
            *(float *)(state+0x3C)=1.0f/duration; }
        *(float *)(object+0x2C)=*(float *)(*(char **)(object+0x24)+0x24)*6.0f;
        object[0x20]=0;
        *(char **)(state+0x1C)=target;
        if(target) {
            info=func_002AB1F0(target);
            if(info) *(unsigned short *)(info+0x1E)|=0x80;
        }
        *(float *)(state+0x30)=0.0f;
        *(float *)(state+0x40)=1.0f;
        speed=*(float *)(state+0x30);
        *(float *)(state+0x44)=func_002A7878(speed,0.069813177f);
        *(float *)(state+0x48)=func_002A7878(speed,0.13962635f);
        *(float *)(state+0x4C)=func_002A7878(speed,0.2792527f);
        *(float *)(object+0xF0)=func_002A7940();
        *(float *)(object+0xF4)=func_002A7940();
        *(float *)(object+0xF8)=func_002A7940();
        *(float *)(state+4)=func_002A7940();
        *(float *)(state+8)=func_002A7940();
        *(float *)(state+12)=func_002A7940();
        func_002A0F48(object);
    }
    return object;
}
