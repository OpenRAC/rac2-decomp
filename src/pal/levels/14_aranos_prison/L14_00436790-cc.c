/* func_PAL_L14_00436790, the PAL copy of func_L14_00430E08: the same C, where the frame count at 0xA8
   is scaled for 50 Hz. The initial value of color takes gcse's expression table from 109 to 111 buckets,
   which gives the three spilled PRE bases retail's stack slots. */
#include "common.h"
extern unsigned int func_00283D38(unsigned int, unsigned int, float);
extern char D_L14_001B9500[];
extern char D_0018A0E0[];
extern void func_002FC560(unsigned int, unsigned long);
extern void func_00281DE8(void *, int, int, int);
extern void func_00282F20(void *, void *, float);
extern void func_00282DD8(void *, void *, void *);
extern void func_00282CC0(void *, void *, void *);
extern void func_00282CF0(void *, void *, void *);
extern void func_00280B90(void *, int, int);
typedef struct {
    float pos[4][4];
    int color[4];
    float uv[4][2];
    long long mode;
    char pad[24];
} PrisonQuad;
extern float D_L14_002602F0[32], D_L14_00260270[32];
extern float func_002A7878(float, float);
extern void func_002ACEC0(void *, void *, void *, float);

void func_PAL_L14_00436790(void *arg)
{
    char *object = arg;
    PrisonQuad q;
    float right[4], rotated[4], delta[4], axis[4];
    char *state = *(char **)(object + 0x68);
    int i, j, color = 0, corners = 4, reg = 0x47, mode = 5, alpha = 128;
    unsigned long testOn = 0x53001, testOff = 0x5360B;
    float scale;
    for (i = 0; i < 32; i++) {
        D_L14_002602F0[i]+=1.0f/((*(int *)(state+0xa8) * 5 + 2) / 6);
        if (D_L14_002602F0[i]>1.0f) { D_L14_002602F0[i]=0; D_L14_00260270[i]=func_002A7878(-1.57079637f,1.57079637f); }
    }
    func_00281DE8(&q,*(int *)(state+0xb0),1,alpha);
    q.mode=mode;
    q.uv[0][0]=0; q.uv[0][1]=0; q.uv[1][0]=0; q.uv[1][1]=1;
    q.uv[2][0]=1; q.uv[2][1]=0; q.uv[3][0]=1; q.uv[3][1]=1;
    func_00282CF0(right,D_L14_001B9500,object+16);
    func_00282F20(right,right,*(float *)(state+0x80)*0.5f);
    func_00282F20(axis,D_0018A0E0,-1.0f);
    for (i = 0; i < 32; i++) {
        if (*(float *)(state+0xac)<D_L14_002602F0[i]) color=*(int *)(state+0x98);
        else color=func_00283D38(*(int *)(state+0x94),*(int *)(state+0x98),D_L14_002602F0[i]/ *(float *)(state+0xac));
        q.color[0]=q.color[1]=q.color[2]=q.color[3]=color;
        func_002ACEC0(rotated,axis,right,D_L14_00260270[i]);
        func_00282DD8(delta,right,rotated);
        func_00282F20(delta,delta,*(float *)(state+0xb4)*(1.0f-D_L14_002602F0[i]));
        scale=*(float *)(state+0xa4)+D_L14_002602F0[i]*(*(float *)(state+0xa0)-*(float *)(state+0xa4));
        if (scale>1.0f) scale=1.0f;
        func_002FC560(reg,testOn);
        for (j = 0; j < corners; j++) {
            qcopy(q.pos[j],object+16);
            if (j>=2) func_00282CC0(q.pos[j],q.pos[j],delta);
            else func_00282CF0(q.pos[j],q.pos[j],delta);
            if (!(j&1)) {
                func_00282F20(rotated,rotated,*(float *)(state+0x80)*(1.0f-scale));
                func_00282CC0(q.pos[j],q.pos[j],rotated);
            } else {
                func_00282F20(rotated,rotated,*(float *)(state+0x80));
                func_00282CC0(q.pos[j],q.pos[j],rotated);
                q.color[j]=*(int *)(state+0xc);
            }
            func_00282CC0(q.pos[j],q.pos[j],right);
        }
        func_00280B90(&q,0,0);
    }
    func_002FC560(reg,testOff);
}
