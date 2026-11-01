#include "include_asm.h"

#include "common.h"
typedef unsigned int TI128 __attribute__((mode(TI)));
typedef union { TI128 q; float v[4]; } Vector;
typedef struct {
    unsigned char reserved0000[0x80]; Vector position;
    unsigned char reserved0090[0x774-0x90]; float pitch,yaw;
    unsigned char reserved077C[0x1500-0x77C]; int blocked;
    unsigned char reserved1504[0x2290-0x1504]; unsigned char *player;
    unsigned char reserved2294[0x24EC-0x2294]; short paused;
} PartialRoot;
extern char D_00189E20[];
extern int D_001A79F0 MACRO_ADDR;
extern Vector D_L00_001B8DC0;
extern int func_00282978(void *),func_002AB1F0(unsigned char *);
extern void func_00282D30(void *,void *,float),func_00282CC0(void *,void *,void *);
extern void func_002AF000(float *,float,float,float);
extern unsigned char *func_L00_00324D18(void *,void *,int,float,float,float,float,float);
extern float func_00282E48(void *,void *),func_00282C48(float);
extern void func_00273318(void *,unsigned int,void *,int,int,int,float,float,float);

void func_PAL_L00_003B9C00(unsigned char *object)
{
    Vector point,projection,facing;
    char *context=*(char **)(object+0x68);
    unsigned char *target,*descriptor;
    float aperture,distance;
    func_00282978(context+0x1E);
    if(object[0x20]==1 && !((PartialRoot *)D_00189E20)->blocked && !((PartialRoot *)D_00189E20)->paused && !*(short *)((char *)(context) + 0x1E)) {
        func_00282D30(&projection,((PartialRoot *)D_00189E20)->player+0xE0,0.75f);
        func_00282CC0(&projection,&((PartialRoot *)D_00189E20)->position,&projection);
        func_002AF000(facing.v,1.0f,((PartialRoot *)D_00189E20)->yaw,((PartialRoot *)D_00189E20)->pitch);
        aperture=0.17453295f;
        if(D_001A79F0==1 && *(unsigned char **)((char *)(context) + 0x14) && (unsigned)(*(unsigned short *)((char *)(*(unsigned char **)((char *)(context) + 0x14)) + 0xAA)-0xA8D)<2)
            aperture=0.30543268f;
        target=func_L00_00324D18(&projection,&facing,0,aperture,0.3490659f,30.0f,0.78539824f,0.6108653f);
        if(target) {
            if(target==*(unsigned char **)((char *)(context) + 0x18)) {
                if(func_00282978(context+0x1C)) {*(unsigned char **)((char *)(context) + 0x14)=target;*(short *)((char *)(context) + 0x1E)=2;}
            } else *(short *)((char *)(context) + 0x1C)=3;
        } else {*(unsigned char **)((char *)(context) + 0x14)=0;*(short *)((char *)(context) + 0x1C)=3;}
        *(unsigned char **)((char *)(context) + 0x18)=target;
    } else if(((PartialRoot *)D_00189E20)->blocked) *(unsigned char **)((char *)(context) + 0x14)=0;
    if(*(unsigned char **)((char *)(context) + 0x14)) {
        descriptor=(unsigned char *)func_002AB1F0(*(unsigned char **)((char *)(context) + 0x14));
        if(descriptor) {
            func_00282D30(&projection,*(unsigned char **)((char *)(context) + 0x14)+0xE0,*(float *)((char *)(descriptor) + 0x10));
            func_00282CC0(&point,*(unsigned char **)((char *)(context) + 0x14)+0x10,&projection);
        } else point.q=*(TI128 *)(*(unsigned char **)((char *)(context) + 0x14)+0x10);
        distance=func_00282E48(&D_L00_001B8DC0,&point);
        aperture=func_00282C48(0.9f-distance*0.006666667f*0.65f);
        func_00273318(object,0xFF0FFF0F,&point,0x26,-1,4,aperture,0.0f,90.0f);
    }
}
