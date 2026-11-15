#include "common.h"

extern void func_0029FC20(void *, int, void *);
extern void func_00282F20(void *, void *, float);
extern void func_00282CC0(void *, void *, void *);
extern void func_00281EB8(void *, float, float, float, int, int, int);
extern void func_002A7988(void *, float, float);
extern float func_002A7940(void);
extern int D_L19_001B1C00 __attribute__((sda));
extern int D_L19_001B1BFC __attribute__((sda));
extern float D_L19_001B1C04 __attribute__((sda));

void func_L19_00417CA0(char *obj)
{
 char *data=*(char **)(obj+0x68);
 char mat[0x40] __attribute__((aligned(16)));
 float pos[4] __attribute__((aligned(16)));
 float offset[4] __attribute__((aligned(16)));
 float random[4] __attribute__((aligned(16)));
 float point[4] __attribute__((aligned(16)));
 func_0029FC20(obj,0,mat);
 qcopy(pos,mat+0x30);
 vec_scale_to_length(offset,mat,0.25f);
 FastVecAdd(pos,pos,offset);
 pos[2]+=1.0f;
 func_00281EB8(pos,D_L19_001B1C04 * *(float *)(data+0x22C),0.08f,0.0f,D_L19_001B1C00,D_L19_001B1BFC,1);
 func_00281EB8(pos,D_L19_001B1C04 * *(float *)(data+0x22C)*1.2f,0.08f,0.0f,D_L19_001B1C00,0xFF804020,1);
 *(float *)(data+0x22C)+=0.12f;
 func_002A7988(random,0.25f,0.45f);
 FastVecAdd(point,random,pos);
 func_00281EB8(pos,*(float *)(data+0x228)*2.0f,0.08f,func_002A7940(),0x31,0x60804020,1);
 func_00281EB8(pos,*(float *)(data+0x228)*1.5f,0.08f,func_002A7940(),0x31,0x80808080,1);
 func_002A7988(random,0.25f,0.45f);
 FastVecAdd(point,random,pos);
 func_00281EB8(point,*(float *)(data+0x228)*2.0f,0.08f,func_002A7940(),0x31,0x60804020,1);
 func_00281EB8(point,*(float *)(data+0x228)*1.5f,0.08f,func_002A7940(),0x31,0x80808080,1);
 func_002A7988(random,0.25f,0.45f);
 FastVecAdd(point,random,pos);
 func_00281EB8(point,*(float *)(data+0x228)*2.0f,0.08f,func_002A7940(),0x31,0x60804020,1);
 func_00281EB8(point,*(float *)(data+0x228)*1.5f,0.08f,func_002A7940(),0x31,0x80808080,1);
}
