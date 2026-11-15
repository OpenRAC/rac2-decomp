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
    struct { float x,y,z,w; } v __attribute__((aligned(16)));
    float z[4] __attribute__((aligned(16)));
    float angle,y;
    int dir;
    v.y=D_00189E20.x1fb4;v.x=D_00189E20.x1fb0;
    if(mode==1) {
        if(func_00282C48(v.y)>0.7f && func_00282C48(v.x)<0.12f) v.x=0.0f;
        if(func_00282C48(v.x)>0.7f && func_00282C48(v.y)<0.12f) v.y=0.0f;
    }
    {float length=vec_length_xy(&v);if(length>1.0f) divide_vector_xyz(&v,&v,length);}
    y=v.y;
    if(v.x==0.0f && y==0.0f) {
        D_00189E20.x1b0=0.0f;
        if(D_00189E20.x22c3) D_00189E20.x1a0=func_L00_002D3290();else D_00189E20.x1a0=D_00189E20.x98;
        *(InputQuad *)z=0;z[0]=1.0f;
        matrix_mul_vec3((char *)&D_00189E20+0x190,z,D_00189E20.x2290+0xc0);
    } else {
        D_00189E20.x1a0=func_00283248(-y,-v.x);
        if(D_00189E20.x1454) {
            angle=func_00283248(D_00189E20.x1fb0,D_00189E20.x1fb4);dir=2;
            if(FastDiffRots(angle,1.5707964897155762f)<0.7853982448577881f) dir=3;
            else if(FastDiffRots(angle,0.0f)<0.7853982448577881f) dir=1;
            else if(FastDiffRots(angle,3.1415929794311523f)<0.7853982448577881f) dir=0;
            D_00189E20.x1457=dir;
            if(dir==3 && D_00189E20.x24b8>0.15f) D_00189E20.x1456=1;else D_00189E20.x1456=0;
        }
        D_00189E20.x1a0=FastAddRotations(D_00189E20.x1a0,D_L00_001B8C80.angle);
        {float x=v.x,y=v.y;v.y=-x;v.x=-y;v.z=v.w=0.0f;if(D_001A7A44[0]) v.y=x;}
        matrix_mul_vec3((char *)&D_00189E20+0x190,&v,D_L00_001B8C80.matrix);
        D_00189E20.x1b0=scale*vec_length_xy(&v);
    }
}
