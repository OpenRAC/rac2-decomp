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
extern char g_hero_state[];
extern int g_current_map_index MACRO_ADDR;
extern Vector g_camera_l00_position;
extern int FastDecTimer(void *);
extern char *moby_get_private_value_0(unsigned char *);
extern void FastVecScale(void *,void *,float),FastVecAdd(void *,void *,void *);
extern void vec_build_spherical_offset(float *,float,float,float);
extern unsigned char *moby_get_or_find_target(void *,void *,int,float,float,float,float,float);
extern float fast_vec_dist(void *,void *),math_fabs(float);
extern void hud_add_moby_marker(void *,unsigned int,void *,int,int,int,float,float,float);

void weapon_update_target_lock_pal(unsigned char *object)
{
    Vector point,projection,facing;
    char *context=*(char **)(object+0x68);
    unsigned char *target,*descriptor;
    float aperture,distance;
    FastDecTimer(context+0x1E);
    if(object[0x20]==1 && !((PartialRoot *)g_hero_state)->blocked && !((PartialRoot *)g_hero_state)->paused && !*(short *)((char *)(context) + 0x1E)) {
        FastVecScale(&projection,((PartialRoot *)g_hero_state)->player+0xE0,0.75f);
        FastVecAdd(&projection,&((PartialRoot *)g_hero_state)->position,&projection);
        vec_build_spherical_offset(facing.v,1.0f,((PartialRoot *)g_hero_state)->yaw,((PartialRoot *)g_hero_state)->pitch);
        aperture=0.17453295f;
        if(g_current_map_index==1 && *(unsigned char **)((char *)(context) + 0x14) && (unsigned)(*(unsigned short *)((char *)(*(unsigned char **)((char *)(context) + 0x14)) + 0xAA)-0xA8D)<2)
            aperture=0.30543268f;
        target=moby_get_or_find_target(&projection,&facing,0,aperture,0.3490659f,30.0f,0.78539824f,0.6108653f);
        if(target) {
            if(target==*(unsigned char **)((char *)(context) + 0x18)) {
                if(FastDecTimer(context+0x1C)) {*(unsigned char **)((char *)(context) + 0x14)=target;*(short *)((char *)(context) + 0x1E)=2;}
            } else *(short *)((char *)(context) + 0x1C)=3;
        } else {*(unsigned char **)((char *)(context) + 0x14)=0;*(short *)((char *)(context) + 0x1C)=3;}
        *(unsigned char **)((char *)(context) + 0x18)=target;
    } else if(((PartialRoot *)g_hero_state)->blocked) *(unsigned char **)((char *)(context) + 0x14)=0;
    if(*(unsigned char **)((char *)(context) + 0x14)) {
        descriptor=(unsigned char *)moby_get_private_value_0(*(unsigned char **)((char *)(context) + 0x14));
        if(descriptor) {
            FastVecScale(&projection,*(unsigned char **)((char *)(context) + 0x14)+0xE0,*(float *)((char *)(descriptor) + 0x10));
            FastVecAdd(&point,*(unsigned char **)((char *)(context) + 0x14)+0x10,&projection);
        } else point.q=*(TI128 *)(*(unsigned char **)((char *)(context) + 0x14)+0x10);
        distance=fast_vec_dist(&g_camera_l00_position,&point);
        aperture=math_fabs(0.9f-distance*0.006666667f*0.65f);
        hud_add_moby_marker(object,0xFF0FFF0F,&point,0x26,-1,4,aperture,0.0f,90.0f);
    }
}
