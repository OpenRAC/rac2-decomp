/* Emit sixteen textured annular quads between the two radii and angles. */
#include "common.h"
extern unsigned long func_0027C878(int);
extern float func_00283B98(float,float),func_00283180(float),func_00283198(float);
extern int func_00283CF0(float);
extern void func_0027E920(const long *,const int *,const int *,unsigned long,int);
void func_0027EE58(int x,int y,int inner,int outer,int *colors,int *uv,int textureId,int segments,float start,float end)
{
    long depth=0xFFFFF000000000L;
    unsigned long texture=GetEffectTextureDescriptor(textureId);
    float step=(end-start)/(float)segments;
    float angle=FastAddRotations(start,1.5707964897155762f);
    float next=FastAddRotations(angle,step);
    {
        int i;
        for (i = 15; i >= 0; i--) {
            long vertices[4];
            float a[3],b[3];
            a[0]=func_00283180(angle);
            a[1]=func_00283198(angle);
            a[2]=0;
            b[0]=func_00283180(next);
            b[1]=func_00283198(next);
            b[2]=0;
            angle=next;
            vertices[0]=vertices[1]=vertices[2]=vertices[3]=0;
            vertices[0]+=(long)FloatToInt(a[0]*(float)inner)+x;
            vertices[0]+=((long)FloatToInt(a[1]*(float)inner)+y)<<16;
            vertices[1]+=(long)FloatToInt(a[0]*(float)outer)+x;
            vertices[1]+=((long)FloatToInt(a[1]*(float)outer)+y)<<16;
            vertices[2]+=(long)FloatToInt(b[0]*(float)inner)+x;
            vertices[2]+=((long)FloatToInt(b[1]*(float)inner)+y)<<16;
            vertices[3]+=(long)FloatToInt(b[0]*(float)outer)+x;
            vertices[3]+=((long)FloatToInt(b[1]*(float)outer)+y)<<16;
            vertices[0]+=depth;
            vertices[1]+=depth;
            vertices[2]+=depth;
            vertices[3]+=depth;
            AppendDisplayListEntry(vertices,uv,colors,texture,1);
            next=FastAddRotations(angle,step);
        }
    }
}
