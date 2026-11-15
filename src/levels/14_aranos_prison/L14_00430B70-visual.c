#include "common.h"
typedef struct { char pad[0x20]; float rate[4]; unsigned int start[4]; unsigned int end[4]; int timer[4]; float angle[4]; } PrisonVisualState;
extern void func_L14_004308D0(void *, int, int, int, float, float, float);
extern float func_L14_00430898(float);
extern void func_L14_00430E08(void *);
extern int func_00282948(void *);
extern unsigned int func_00283D38(unsigned int, unsigned int, float);
extern float func_00283B98(float, float);

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

/* Draws the pulse effect: a glowing center quad, two fading rotating quads and the sparks. */
void func_L14_00430B70(char *self)
{
    char *state = *(char **)(self + 0x68);
    int i;
    unsigned int color;
    float t, scale, angle;
    DrawRotatedBillboardQuad(self + 0x10, *(int *)(state+0xb8), *(int *)(state+0xc0), 1,
        *(float *)(state+0xbc) * *(float *)(state+0x80), *(float *)(state+0x80)*0.5f, 0.0f);
    for (i=0; i<2; i++) {
        if (FastFloatHelperD(state+0x50+i*4))
            ((PrisonVisualState *)state)->timer[i] = (int)((float)*(int *)(state+0x10) / ((PrisonVisualState *)state)->rate[i]);
        t = 1.0f - (float)((PrisonVisualState *)state)->timer[i] /
            (float)(int)((float)*(int *)(state+0x10) / ((PrisonVisualState *)state)->rate[i]);
        if (*(float *)(state+0x14) < t) {
            color = ((PrisonVisualState *)state)->end[i];
            color = (color & 0xffffff) + (((int)((1.0f-t)/(1.0f-*(float *)(state+0x14))*80.0f)+48)<<24);
        } else {
            color = FastTweenColor(((PrisonVisualState *)state)->start[i], ((PrisonVisualState *)state)->end[i], t / *(float *)(state+0x14));
            color = (color & 0xffffff) + (((int)(t / *(float *)(state+0x14)*80.0f)+48)<<24);
        }
        scale = *(float *)(state+0x80) * *(float *)(state+0x18);
        angle = WrapAngleFullTurn(t * (((PrisonVisualState *)state)->angle[i] * 6.2831855f));
        DrawRotatedBillboardQuad(self+0x10, *(int *)(state+0x1c), color, 1, scale, *(float *)(state+0x80)*0.5f, angle + -3.1415927f);
    }
    *(float *)state = FastAddRotations(*(float *)state, 0.007f);
    DrawRotatedBillboardQuad(self+0x10, *(int *)(state+4), *(int *)(state+12), 1,
        *(float *)(state+8)* *(float *)(state+0x80), *(float *)(state+0x80)*0.5f, *(float *)state);
    DrawPrisonSparkQuads(self);
}

/* Draws 32 small spark quads that drift away from the object and fade out. */
void func_L14_00430E08(void *owner)
{
    char *object = owner;
    PrisonQuad q;
    float right[4], rotated[4], delta[4], axis[4];
    char *state = *(char **)(object + 0x68);
    int i, j, color, corners = 4, reg = 0x47, mode = 5, alpha = 128;
    unsigned long testOn = 0x53001, testOff = 0x5360B;
    float scale;
    for (i = 0; i < 32; i++) {
        D_L14_002602F0[i]+=1.0f/ *(int *)(state+0xa8);
        if (D_L14_002602F0[i]>1.0f) { D_L14_002602F0[i]=0; D_L14_00260270[i]=RandomFloatRange(-1.57079637f,1.57079637f); }
    }
    InitQuadPacketState(&q,*(int *)(state+0xb0),1,alpha);
    q.mode=mode;
    q.uv[0][0]=0; q.uv[0][1]=0; q.uv[1][0]=0; q.uv[1][1]=1;
    q.uv[2][0]=1; q.uv[2][1]=0; q.uv[3][0]=1; q.uv[3][1]=1;
    FastVecSub(right,D_L14_001B9500,object+16);
    vec_scale_to_length(right,right,*(float *)(state+0x80)*0.5f);
    vec_scale_to_length(axis,D_0018A0E0,-1.0f);
    for (i = 0; i < 32; i++) {
        if (*(float *)(state+0xac)<D_L14_002602F0[i]) color=*(int *)(state+0x98);
        else color=FastTweenColor(*(int *)(state+0x94),*(int *)(state+0x98),D_L14_002602F0[i]/ *(float *)(state+0xac));
        q.color[0]=q.color[1]=q.color[2]=q.color[3]=color;
        ApplyAxisRotationToQuaternion(rotated,axis,right,D_L14_00260270[i]);
        FastVecCross(delta,right,rotated);
        vec_scale_to_length(delta,delta,*(float *)(state+0xb4)*(1.0f-D_L14_002602F0[i]));
        scale=*(float *)(state+0xa4)+D_L14_002602F0[i]*(*(float *)(state+0xa0)-*(float *)(state+0xa4));
        if (scale>1.0f) scale=1.0f;
        VU1_addGSregister(reg,testOn);
        for (j = 0; j < corners; j++) {
            qcopy(q.pos[j],object+16);
            if (j>=2) FastVecAdd(q.pos[j],q.pos[j],delta);
            else FastVecSub(q.pos[j],q.pos[j],delta);
            if (!(j&1)) {
                vec_scale_to_length(rotated,rotated,*(float *)(state+0x80)*(1.0f-scale));
                FastVecAdd(q.pos[j],q.pos[j],rotated);
            } else {
                vec_scale_to_length(rotated,rotated,*(float *)(state+0x80));
                FastVecAdd(q.pos[j],q.pos[j],rotated);
                q.color[j]=*(int *)(state+0xc);
            }
            FastVecAdd(q.pos[j],q.pos[j],right);
        }
        draw_world_quad(&q,0,0);
    }
    VU1_addGSregister(reg,testOff);
}
