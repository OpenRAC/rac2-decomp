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

extern char *D_L16_001BFF58 NOT_SDA;
extern Quad16 D_L16_001A8F20 MACRO_ADDR;
extern float D_L16_001B1CA0 __attribute__((sda));
extern float D_L16_001B1CA4 __attribute__((sda));
extern float D_L16_001B1CA8 __attribute__((sda));
/* Runs a glowing marker that spins and pulses, and reports when the player or a shot touches it. */
void spinning_marker_update(char *object)
{
    MarkerWorkspace local;
    float *state=*(float **)(object+0x68);
    float value;
    int i;
    switch (*(unsigned char *)(object+0x20)) { case 1: goto active; case 0: break; case 2: default: goto common; }

        state[0]=1.0f;
        state[8]=math_random_angle();
        state[2]=0.5f;
        state[1]=0.0f;
        state[0]=1.0f;
        for(i=3;i>=0;i--) state[i+4]=1.0f;
        *(unsigned char *)(object+0x30)=0xff;
        moby_set_state((unsigned char *)object,1,-1);
        object[0x31]=0;
        *(unsigned short *)(object+0x34)|=1;
    goto common;
active:
    if (g_current_map_index==16) {

        qcopy(&local.position,&H->q[8]);
        vec_scale_to_length(&local.offset,H->ptr[2212]+0xe0,0.75f);
        FastVecAdd(&local.position,&local.position,&local.offset);
        if (coll_test_point(&local.position,0,H->ptr[2212],0.5f)!=0 && D_L16_001BFF58!=0 && D_L16_001BFF58==object) {
            make_hit_descriptor((char *)&local.request,(int)object,1,100.0f,&D_L16_001A8F20);
            local.request.id=*(unsigned short *)(object+0xaa);
            hero_record_play_counters();
        }
        if (H->ptr[207]!=0 && H->ptr[207]==object && H->i[208]!=0) {
            ((float *)&local.direction)[0]=0.0f;
            ((float *)&local.direction)[1]=1.0f;
            ((float *)&local.direction)[2]=0.0f;
            ((float *)&local.direction)[3]=1.0f;
            vec_scale_to_length(&local.direction,&local.direction,10.0f);
            make_hit_descriptor((char *)&local.request,(int)object,1,10.0f,(Quad16 *)&local.direction);
            local.request.id=*(unsigned short *)(object+0xaa);
            hero_record_play_counters();
        }
    }
common:
    if (state[0]!=0.0f) {
        scale_vector(&local.position,object,0.0009765625f);
        state[8]=FastAddRotations(state[8],D_L16_001B1CA0*0.0002908882452f);
        state[3]+=(D_L16_001B1CA4+math_random_signed_float_range(0.25f,0.5f))*0.016666668f;
        if (state[3]>1.0f) state[3]-=1.0f;
        for(i=1;i<=2;i++) {
            value=state[i]+D_L16_001B1CA8*0.016666668f;
            state[i]=value;
            if(value>1.0f) state[i]=value-1.0f;
        }
        gfx_add_draw_callback_first(gfx_draw_pulsing_glow_strip,object);
        ApproachValue(state,1.0f,0.008333333768f);
    }
}
