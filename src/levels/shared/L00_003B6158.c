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
/* Looks for an enemy in front of the player and locks on to it, drawing a marker on the target. */
void func_L00_003B6158(unsigned char *object)
{
    Vector point,projection,facing;
    char *context=*(char **)(object+0x68);
    unsigned char *target,*descriptor;
    float aperture,distance;
    FastDecTimer(context+0x1E);
    if(object[0x20]==1 && !((PartialRoot *)gHeroState)->blocked && !((PartialRoot *)gHeroState)->paused && !*(short *)((char *)(context) + 0x1E)) {
        FastVecScale(&projection,((PartialRoot *)gHeroState)->player+0xE0,0.75f);
        FastVecAdd(&projection,&((PartialRoot *)gHeroState)->position,&projection);
        BuildSphericalOffset(facing.v,1.0f,((PartialRoot *)gHeroState)->yaw,((PartialRoot *)gHeroState)->pitch);
        aperture=0.17453295f;
        if(gCurrentMapIndex==1 && *(unsigned char **)((char *)(context) + 0x14) && (unsigned)(*(unsigned short *)((char *)(*(unsigned char **)((char *)(context) + 0x14)) + 0xAA)-0xA8D /* Swamp Monster I Arm */)<2)
            aperture=0.30543268f;
        target=GetOrFindTargetMoby(&projection,&facing,0,aperture,0.3490659f,30.0f,0.78539824f,0.6108653f);
        if(target) {
            if(target==*(unsigned char **)((char *)(context) + 0x18)) {
                if(FastDecTimer(context+0x1C)) {*(unsigned char **)((char *)(context) + 0x14)=target;*(short *)((char *)(context) + 0x1E)=2;}
            } else *(short *)((char *)(context) + 0x1C)=4;
        } else {*(unsigned char **)((char *)(context) + 0x14)=0;*(short *)((char *)(context) + 0x1C)=4;}
        *(unsigned char **)((char *)(context) + 0x18)=target;
    } else if(((PartialRoot *)gHeroState)->blocked) *(unsigned char **)((char *)(context) + 0x14)=0;
    if(*(unsigned char **)((char *)(context) + 0x14)) {
        descriptor=(unsigned char *)GetMobyPrivateValue0(*(unsigned char **)((char *)(context) + 0x14));
        if(descriptor) {
            FastVecScale(&projection,*(unsigned char **)((char *)(context) + 0x14)+0xE0,*(float *)((char *)(descriptor) + 0x10));
            FastVecAdd(&point,*(unsigned char **)((char *)(context) + 0x14)+0x10,&projection);
        } else point.q=*(TI128 *)(*(unsigned char **)((char *)(context) + 0x14)+0x10);
        distance=fast_vec_dist(&gCameraPosition_L00,&point);
        aperture=FloatAbs(0.9f-distance*0.006666667f*0.65f);
        AddMobyMarker(object,0xFF0FFF0F,&point,0x26,-1,4,aperture,0.0f,90.0f);
    }
}
