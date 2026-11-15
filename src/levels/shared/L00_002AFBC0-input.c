#include "common.h"

typedef int InputQuad __attribute__((mode(TI)));

typedef struct {
    unsigned char pad0[152];
    float x98;
    unsigned char pad9c[260];
    float x1a0;
    unsigned char pad1a4[12];
    float x1b0;
    unsigned char pad1b4[4768];
    short x1454;
    unsigned char x1456;
    unsigned char x1457;
    unsigned char pad1458[2904];
    float x1fb0;
    float x1fb4;
    unsigned char pad1fb8[728];
    char * x2290;
    unsigned char pad2294[47];
    unsigned char x22c3;
    unsigned char pad22c4[500];
    float x24b8;
} PlayerInputState;
extern PlayerInputState D_00189E20;
typedef struct {char pad[0x158];float angle;char gap[0x370-0x15c];char matrix[64];} InputCamera;
extern InputCamera D_L00_001B8C80;
extern unsigned char D_001A7A44[] __attribute__((sda));
extern float func_00282C48(float);
extern float func_00282E20(void *);
extern void func_00282D90(void *,void *,float);
extern float func_L00_002D3290(void);
extern void func_00283098(void *,void *,void *);
extern float func_00283248(float,float);
extern float func_00283C80(float,float);
extern float func_00283B98(float,float);

/* Resolve stick input into a camera-relative movement direction and target speed. */
void func_L00_002B39F0(int mode,float scale) {
    struct { float x,y,z,w; } stick __attribute__((aligned(16)));
    float z[4] __attribute__((aligned(16)));
    float angle,y;
    int dir;
    stick.y=gHeroState.x1fb4;stick.x=gHeroState.x1fb0;
    if(mode==1) {
        if(FloatAbs(stick.y)>0.7f && FloatAbs(stick.x)<0.12f) stick.x=0.0f;
        if(FloatAbs(stick.x)>0.7f && FloatAbs(stick.y)<0.12f) stick.y=0.0f;
    }
    {float length=vec_length_xy(&stick);if(length>1.0f) divide_vector_xyz(&stick,&stick,length);}
    y=stick.y;
    if(stick.x==0.0f && y==0.0f) {
        gHeroState.x1b0=0.0f;
        if(gHeroState.x22c3) gHeroState.x1a0=ComputeHeroAimAngle();else gHeroState.x1a0=gHeroState.x98;
        *(InputQuad *)z=0;z[0]=1.0f;
        matrix_mul_vec3((char *)&gHeroState+0x190,z,gHeroState.x2290+0xc0);
    } else {
        gHeroState.x1a0=FastMatrixHelperA(-y,-stick.x);
        if(gHeroState.x1454) {
            angle=FastMatrixHelperA(gHeroState.x1fb0,gHeroState.x1fb4);dir=2;
            if(FastDiffRots(angle,1.5707964897155762f)<0.7853982448577881f) dir=3;
            else if(FastDiffRots(angle,0.0f)<0.7853982448577881f) dir=1;
            else if(FastDiffRots(angle,3.1415929794311523f)<0.7853982448577881f) dir=0;
            gHeroState.x1457=dir;
            if(dir==3 && gHeroState.x24b8>0.15f) gHeroState.x1456=1;else gHeroState.x1456=0;
        }
        gHeroState.x1a0=FastAddRotations(gHeroState.x1a0,D_L00_001B8C80.angle);
        {float x=stick.x,y=stick.y;stick.y=-x;stick.x=-y;stick.z=stick.w=0.0f;if(D_001A7A44[0]) stick.y=x;}
        matrix_mul_vec3((char *)&gHeroState+0x190,&stick,D_L00_001B8C80.matrix);
        gHeroState.x1b0=scale*vec_length_xy(&stick);
    }
}
