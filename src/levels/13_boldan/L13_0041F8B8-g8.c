#include "common.h"
typedef int HeroQ __attribute__((mode(TI)));
typedef union { unsigned char b[0x2600]; signed char c[0x2600]; short h[0x1300]; unsigned short uh[0x1300]; int i[0x980]; unsigned int u[0x980]; float f[0x980]; char *ptr[0x980]; HeroQ q[0x260]; } Hero;
extern unsigned char g_hero_state[];
#define H ((Hero *)D_00189E20)
typedef int Vector128 __attribute__((mode(TI)));
typedef struct { int a,b,c,d; } __attribute__((aligned(16))) Quad16;
typedef struct { Quad16 vector; int owner,flags; unsigned char enabled,kind; unsigned short id; float distance; int active; } CollisionRequest;
typedef struct { Vector128 position,offset; CollisionRequest request; Vector128 direction; } MarkerWorkspace;
extern float math_random_angle(void);
extern void moby_set_state(unsigned char *,int,int);
extern void vec_scale_to_length(void *,void *,float);
extern void FastVecAdd(void *,void *,void *);
extern int coll_test_point(void *,int,void *,float);
extern void make_hit_descriptor(char *,int,int,float,Quad16 *);
extern void hero_record_play_counters(void);
extern void scale_vector(void *,void *,float);
extern float FastAddRotations(float,float);
extern float math_random_signed_float_range(float,float);
extern void gfx_add_draw_callback_first(void (*)(void *),void *);
extern void gfx_draw_pulsing_glow_strip(void *);
extern float ApproachValue(float *,float,float);
extern int g_current_map_index;

extern char *g_hit_l13_result NOT_SDA;
extern Quad16 g_default_l13_effect_vector MACRO_ADDR;
extern float g_marker_rotation_speed __attribute__((sda));
extern float g_marker_l13_rise_speed __attribute__((sda));
extern float g_marker_value_speed __attribute__((sda));
/* Updates a floating marker the player can target. It spins, glows, and reacts when the player aims at it or touches it. */
void targetable_marker_update(char *moby)
{
    MarkerWorkspace work;
    float *vars=*(float **)(moby+0x68);
    float value;
    int i;
    switch (*(unsigned char *)(moby+0x20)) { case 1: goto active; case 0: break; case 2: default: goto common; }

        vars[0]=1.0f;
        vars[8]=math_random_angle();
        vars[2]=0.5f;
        vars[1]=0.0f;
        vars[0]=1.0f;
        for(i=3;i>=0;i--) vars[i+4]=1.0f;
        *(unsigned char *)(moby+0x30)=0xff;
        moby_set_state((unsigned char *)moby,1,-1);
        moby[0x31]=0;
        *(unsigned short *)(moby+0x34)|=1;
    goto common;
active:
    if (g_current_map_index==16) {

        qcopy(&work.position,&H->q[8]);
        vec_scale_to_length(&work.offset,H->ptr[2212]+0xe0,0.75f);
        FastVecAdd(&work.position,&work.position,&work.offset);
        if (coll_test_point(&work.position,0,H->ptr[2212],0.5f)!=0 && g_hit_l13_result!=0 && g_hit_l13_result==moby) {
            make_hit_descriptor((char *)&work.request,(int)moby,1,100.0f,&g_default_l13_effect_vector);
            work.request.id=*(unsigned short *)(moby+0xaa);
            hero_record_play_counters();
        }
        if (H->ptr[207]!=0 && H->ptr[207]==moby && H->i[208]!=0) {
            ((float *)&work.direction)[0]=0.0f;
            ((float *)&work.direction)[1]=1.0f;
            ((float *)&work.direction)[2]=0.0f;
            ((float *)&work.direction)[3]=1.0f;
            vec_scale_to_length(&work.direction,&work.direction,10.0f);
            make_hit_descriptor((char *)&work.request,(int)moby,1,10.0f,(Quad16 *)&work.direction);
            work.request.id=*(unsigned short *)(moby+0xaa);
            hero_record_play_counters();
        }
    }
common:
    if (vars[0]!=0.0f) {
        scale_vector(&work.position,moby,0.0009765625f);
        vars[8]=FastAddRotations(vars[8],g_marker_rotation_speed*0.0002908882452f);
        vars[3]+=(g_marker_l13_rise_speed+math_random_signed_float_range(0.25f,0.5f))*0.016666668f;
        if (vars[3]>1.0f) vars[3]-=1.0f;
        for(i=1;i<=2;i++) {
            value=vars[i]+g_marker_value_speed*0.016666668f;
            vars[i]=value;
            if(value>1.0f) vars[i]=value-1.0f;
        }
        gfx_add_draw_callback_first(gfx_draw_pulsing_glow_strip,moby);
        ApproachValue(vars,1.0f,0.008333333768f);
    }
}
