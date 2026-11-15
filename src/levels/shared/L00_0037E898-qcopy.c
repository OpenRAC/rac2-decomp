#include "include_asm.h"
#include "common.h"

typedef unsigned int Quad __attribute__((mode(TI)));
typedef union { Quad bits; float f[4]; } Vector;

extern char *func_002FEC50(int);
extern void func_00282DD8(void *, void *, void *);
extern void func_00282F20(void *, void *, float);
extern void func_002AB600(void *, void *);
extern void func_0029FCC0(void *, int, void *);
extern void func_00283098(void *, void *, void *);
extern void func_00282CC0(void *, void *, void *);

/* Builds a rotation from the input direction and places the owner's part with it, then fixes up its position. */
void func_L00_00387BB0(char *owner, char *input)
{
    Vector local[7];
    char *transform = GetSlotByIndex(*(int *)(*(char **)(owner + 0x68) + 0x48));
    qcopy(&local[3], input);
    qcopy(&local[0], &local[3]);
    local[4].bits = 0;
    local[4].f[2] = 1.0f;
    FastVecCross(&local[1], &local[0], &local[4]);
    vec_scale_to_length(&local[1], &local[1], 1.0f);
    FastVecCross(&local[2], &local[1], &local[0]);
    TransformMatrixViaCopy(transform + 0x10, &local[0]);
    TransformMobyJointToWorld(owner, 0, &local[5]);
    matrix_mul_vec3(&local[3], input, owner + 0xC0);
    FastVecAdd(&local[6], &local[3], &local[5]);
}

/* Builds a rotation from the input direction and places the owner's part with it, then fixes up its position. */
void func_L00_0038A650(char *owner, char *input)
{
    Vector local[7];
    char *transform = GetSlotByIndex(*(int *)(*(char **)(owner + 0x68) + 0x48));
    qcopy(&local[3], input);
    qcopy(&local[0], &local[3]);
    local[4].bits = 0;
    local[4].f[2] = 1.0f;
    FastVecCross(&local[1], &local[0], &local[4]);
    vec_scale_to_length(&local[1], &local[1], 1.0f);
    FastVecCross(&local[2], &local[1], &local[0]);
    TransformMatrixViaCopy(transform + 0x10, &local[0]);
    TransformMobyJointToWorld(owner, 0, &local[5]);
    matrix_mul_vec3(&local[3], input, owner + 0xC0);
    FastVecAdd(&local[6], &local[3], &local[5]);
}

extern int func_00282948(int *);
extern float func_00283CE0(int);
extern int func_00283CF0(float);
/* Fades the object's colour back toward grey as its countdown runs out. */
void func_L00_0038D650(char *object)
{
    Vector colour;
    char *data = *(char **)(object + 0x68);
    float fraction;
    unsigned int r, g, b, c;
    colour.bits = 0;
    colour.f[0] = 128.0f;
    colour.f[1] = 128.0f;
    colour.f[2] = 128.0f;
    colour.f[3] = 255.0f;
    FastFloatHelperD((int *)(data + 0x10));
    fraction = IntToFloat(*(int *)(data + 0x10));
    fraction /= IntToFloat(30);
    r = FloatToInt((colour.f[0] - 255.0f) * fraction + 255.0f);
    g = FloatToInt((colour.f[1] - 64.0f) * fraction + 64.0f);
    b = FloatToInt((colour.f[2] - 64.0f) * fraction + 64.0f);
    c = (g << 8) | 0xFF000000;
    *(unsigned int *)(object + 0x78) = ((b << 16) | c) | r;
}

extern int D_001A79F0[] __attribute__((sda));
extern int D_L00_001B90C4[];
extern float D_L00_001B90C8[];
extern int D_L00_001B273C[] __attribute__((sda));
extern Quad D_L00_001AECC0[4] SDATA(D_L00_001AECC0);
extern float func_L00_00382BF0(void *);
extern void func_L00_00382CE8(void *);
extern void func_L00_00382F28(void *);
extern void func_L00_002E6CF0(void (*)(void *), void *);
/* Updates the lens flare object. At first it picks which sun to show for the current level; after that it measures how visible the sun is and draws the flare. */
void func_L00_00382AE8(unsigned char *object)
{
    Quad *data=*(Quad **)(object+0x68);
    switch (object[0x20]) {
    case 0: {
        int level;
        int index=0;
        object[0x30]=255;
        object[0x20]=1;
        D_L00_001B90C4[0]=0;
        level=gCurrentMapIndex[0];
        if (level==0) D_L00_001B273C[0]=0x49;
        else if (level==3) D_L00_001B273C[0]=0x40;
        else if (level==7) { D_L00_001B273C[0]=0x3F; index=1; }
        else if (level==12) { D_L00_001B273C[0]=0x41; index=2; }
        else if (level==14) { D_L00_001B273C[0]=0x4D; index=3; }
        *data=D_L00_001AECC0[index];
        InitSparkleTable(object);
        break;
    }
    case 1: {
        D_L00_001B90C8[0]=GetLensFlareVisibility(object);
        AddDrawCallbackToList1(DrawLevelLensFlare,object);
        break;
    }
    }
}
