#include "include_asm.h"

#include "common.h"
typedef unsigned int u128 __attribute__((mode(TI)));
extern float func_002B0178(void *, void *, void *);
extern int func_002AD0B0(void *);
extern int func_002ACBC8(void *, int);
extern int func_002B38B8(void *);
extern void func_002A7750(void *, int, int);
extern int func_002B3868(void *);
extern void func_PAL_002A7E68(void *, int, int, int);
extern int func_00282948(void *);
extern unsigned char *func_L07_003E5B70(int, int *);
extern void func_00283098(void *, void *, void *);
extern void func_00282CF0(void *, void *, void *);
extern void func_00282CC0(void *, void *, void *);
extern int func_00277258(void *, float, int, void *);
extern void func_L07_003E5C78(void *, void *, void *, int);
extern int func_002E5CF8(int, int, void *);
extern float func_002AA2E8(void *, float, float);
extern float func_00283B98(float, float);
extern void func_L00_002E6CF0(void (*)(char *), void *);
extern void func_L07_003E5070(char *);
extern int func_002A77E0(int);
extern void func_002AD0E0(void *, void *, void *, void *, void *, void *);
extern float func_002A7940(void);
extern float func_00283180(float);
extern float func_00283198(float);
extern float func_002A7878(float, float);
extern int func_00283D38(int, int, float);
extern int func_002A7820(int, int);
extern float func_00283CE0(int);
extern void func_002C3150(void *, void *, int, float, int, int, int);
struct Collision1310 { char pad[0x18]; void *object; };
extern struct Collision1310 D_L07_001BF640;
extern char D_00189EA0[];
extern float D_L07_001B0A50 __attribute__((sda));
extern int D_L07_001B0A48[] __attribute__((sda));
extern int D_L07_001B0A48_gp[] SDATA(D_L07_001B0A48);
extern float D_L07_001B0A40[] __attribute__((sda));

/* Update the launcher state, dispatch its target effect and emit particles. */
void func_PAL_L07_003E8E10(unsigned char *o)
{
    float a[4] __attribute__((aligned(16)));
    float b[4] __attribute__((aligned(16)));
    float c[4] __attribute__((aligned(16)));
    float d[4] __attribute__((aligned(16)));
    int count;
    char *p = *(char **)(o+0x68);
    unsigned char *target;
    float angle, size, speed;
    const float lift = 0.05f;
    const float turn = 0.0003490659f;
    int color, life;
    switch (o[0x20]) {
    case 0:
        D_L07_001BF640.object=0;
        func_002B0178(o+0x10,o,o+0x10);
        {
            float height = *(float *)(o + 0x18);
            height = lift + height;
            *(float *)(o + 0x18) = height;
        }
        *(int *)(p+0x20)=-1;
        if (D_L07_001BF640.object && func_002AD0B0(D_L07_001BF640.object))
            *(int *)(p+0x10)=(int)D_L07_001BF640.object;
        func_002A7750(o,1,-1);
        break;
    case 1:
        if (func_002ACBC8(D_00189EA0,*(int *)(p+4)) || func_002B38B8(o)) func_002A7750(o,2,-1);
        break;
    case 2:
        if (func_002B3868(o) && o[0x43]!=1) func_PAL_002A7E68(o,1,0,17);
        if (func_00282948(p+0x14)) {
            target=func_L07_003E5B70(*(int *)p,&count);
            if (target) {
                *(u128 *)a=0;
                a[2]=0.7f;
                func_00283098(a,a,o+0xC0);
                func_00282CC0(a,a,o+0x10);
                if (!func_00277258(a,0.5f,0,o)) {
                    *(u128 *)b=0;
                    b[2]=0.5f;
                    func_00282CC0(b,b,o+0x10);
                    func_L07_003E5C78(target,o+0x10,b,*(int *)(p+0x10));
                    func_002E5CF8(0,0,o);
                    *(int *)(p+0x14)=50;
                }
            } else if (!count) func_002A7750(o,3,-1);
        }
        func_002AA2E8(p+0x18,1.0f,0.060000002f);
        {
            float delta = D_L07_001B0A50;
            delta = turn * delta;
            *(float *)(p + 0x1C) = func_00283B98(*(float *)(p + 0x1C), delta);
        }
        func_L00_002E6CF0(func_L07_003E5070,o);
        if (o[0x31] && !func_002A77E0(5)) {
            qzero_nc(b); qzero_nc(a);
            if (*(void **)(p+0x10)) {
                func_002AD0E0(o,*(void **)(p+0x10),o+0x10,a,b,a);
                func_00282CF0(b,b,o+0x10);
            }
            angle=func_002A7940();
            c[0]=func_00283180(angle)*0.4f;
            c[1]=func_00283198(angle)*0.4f;
            c[2]=0;
            func_00282CC0(c,c,o+0x10);
            size=func_002A7878(D_L07_001B0A40[0],D_L07_001B0A40[1]);
            color=func_00283D38(D_L07_001B0A48_gp[0],D_L07_001B0A48[1],func_002A7878(0,1));
            speed=func_002A7878(1,2);
            life=((s32)(func_002A7820(30,60)) * 5 + 2) / 6;
            qcopy(d,b);
            d[2]=speed/func_00283CE0(life);
            func_002C3150(c,d,color,size,(unsigned char)life,(unsigned char)func_002A77E0(255),0);
        }
        break;
    case 3:
        if (func_002B3868(o) && o[0x43]) func_PAL_002A7E68(o,0,0,17);
        func_002AA2E8(p+0x18,0,0.060000002f);
        func_L00_002E6CF0(func_L07_003E5070,o);
        if (o[0x42]==o[0x43] && *(float *)(p+0x18)<=0) *(unsigned short *)(o+0x34)|=2;
        break;
    }
}
