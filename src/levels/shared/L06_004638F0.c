#include "common.h"
extern void gfx_add_draw_callback_first(void *,void *);
extern void moby_set_state(void *,int,int);
extern int math_fast_float_d(int *);
extern void moby_mark_spawned(void *);
extern float math_fabs(float);
extern float mat_fast_helper_a(float,float);
extern int flag_set_first_pending(void *);
extern int math_random_int_range(int,int);
extern void add_vectors(void *,void *,void *);
extern void scale_vector_xyz_in_place(void *,void *,float);
extern void FastVecScale(void *,void *,float);
extern void FastVecAdd(void *,void *,void *);
extern float coll_probe_ground_height_below(void *,int,float);
extern float math_wrap_angle_to_pi(float);
extern float math_fast_sin_or_cos_b(float);
extern float square_root(float);
extern float math_random_float_range(float,float);
extern void gfx_draw_double_layer_quad(char *);
extern float g_sway_direction_vec[4] __attribute__((sda));
#define F38(p,o) (*(float *)((char *)(p)+(o)))
#define I38(p,o) (*(int *)((char *)(p)+(o)))
/* Updates a swaying effect moby (class 4535): it sways along an arc, then shrinks away and is removed. */
void swaying_effect_update(unsigned char *moby) {
    char *vars = *(char **)(moby+0x68);
    float tmp[4];
    float phase, wave, bend, height;
    if ((unsigned char)moby[0x20]) gfx_add_draw_callback_first(gfx_draw_double_layer_quad,moby);
    switch ((unsigned char)moby[0x20]) {
    case 0:
        *(u16 *)(moby+0x34) |= 0x800;
        F38(moby,0xf8)=mat_fast_helper_a(F38(vars,0x20),F38(vars,0x24));
        F38(moby,0xf4)=3.1415927f;
        moby_set_state(moby,1,-1);
        break;
    case 1:
        if(flag_set_first_pending(moby)) I38(vars,0x30)=math_random_int_range(20,40);
        add_vectors(tmp,moby+0x10,vars+0x20);
        scale_vector_xyz_in_place(tmp,vars+0x20,0.92f);
        if(math_fast_float_d((int *)(vars+0x30))) {
            FastVecScale(tmp,vars+0x10,-F38(vars,0x38));
            FastVecAdd(vars,tmp,moby+0x10);
            F38(vars,8)-=F38(vars,0x38)*0.5f;
            F38(vars,0x3c)=3.1415927f/(F38(vars,0x34)+F38(vars,0x34));
            F38(vars,0x40)=1.5707965f;
            moby_set_state(moby,2,-1);
        }
        break;
    case 2:
        if(flag_set_first_pending(moby)) {
            I38(vars,0x30)=900;
            F38(vars,0x48)=coll_probe_ground_height_below(moby+0x10,0,0.5f)+0.1f;
        }
        F38(vars,8)-=F38(vars,0x44);
        phase=math_wrap_angle_to_pi(F38(vars,0x3c)*F38(vars,0x34));
        wave=math_fast_sin_or_cos_b(phase);
        height=F38(vars,0x38);
        {
            float offset;
            bend=wave*3.0f;
            bend=height*(wave>=0.0f ? square_root(wave)+bend : bend-square_root(-wave))*0.25f;
            offset=F38(vars,0x38)*wave*wave*0.6366197f*F38(vars,0x40)*0.5f;
            F38(moby,0xf4)=-(F38(vars,0x40)*wave+1.5707965f);
            FastVecScale(tmp,g_sway_direction_vec,offset);
        }
        FastVecAdd(moby+0x10,tmp,vars);
        FastVecScale(tmp,vars+0x10,bend);
        FastVecAdd(moby+0x10,tmp,moby+0x10);
        if(math_fabs(phase)<0.1f) F38(vars,0x40)=math_random_float_range(30.0f,60.0f)*0.017453294f;
        if(F38(moby,0x18)<F38(vars,0x48) || math_fast_float_d((int *)(vars+0x30))) moby_set_state(moby,3,-1);
        break;
    case 3:
        if(flag_set_first_pending(moby)) I38(vars,0x30)=60;
        F38(moby,0xf4)=(F38(moby,0xf4)+1.5707964f)*0.95f-1.5707964f;
        moby[0x23]=(int)((float)I38(vars,0x30)*1.3333334f);
        if(math_fast_float_d((int *)(vars+0x30))) {moby_mark_spawned(moby);return;}
        break;
    }
    F38(vars,0x3c)+=1.0f;
}


