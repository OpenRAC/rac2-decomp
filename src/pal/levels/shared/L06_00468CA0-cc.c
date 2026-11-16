#include "names.h"
/* func_PAL_L06_00468CA0, the PAL copy of func_L06_004638F0: the same C, where scale func_002A7820(20,40). */
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
void func_PAL_L06_00468CA0(unsigned char *m) {
    char *v = *(char **)(m+0x68);
    float tmp[4];
    float phase, wave, bend, height;
    if ((unsigned char)m[0x20]) gfx_add_draw_callback_first(gfx_draw_double_layer_quad,m);
    switch ((unsigned char)m[0x20]) {
    case 0:
        *(u16 *)(m+0x34) |= 0x800;
        F38(m,0xf8)=mat_fast_helper_a(F38(v,0x20),F38(v,0x24));
        F38(m,0xf4)=3.1415927f;
        moby_set_state(m,1,-1);
        break;
    case 1:
        if(flag_set_first_pending(m)) I38(v,0x30)=(((int)(math_random_int_range(20,40)) * 5 + 2) / 6);
        add_vectors(tmp,m+0x10,v+0x20);
        scale_vector_xyz_in_place(tmp,v+0x20,0.90400004f);
        if(math_fast_float_d((int *)(v+0x30))) {
            FastVecScale(tmp,v+0x10,-F38(v,0x38));
            FastVecAdd(v,tmp,m+0x10);
            F38(v,8)-=F38(v,0x38)*0.5f;
            F38(v,0x3c)=3.1415927f/(F38(v,0x34)+F38(v,0x34));
            F38(v,0x40)=1.5707965f;
            moby_set_state(m,2,-1);
        }
        break;
    case 2:
        if(flag_set_first_pending(m)) {
            I38(v,0x30)=750;
            F38(v,0x48)=coll_probe_ground_height_below(m+0x10,0,0.5f)+0.1f;
        }
        F38(v,8)-=F38(v,0x44);
        phase=math_wrap_angle_to_pi(F38(v,0x3c)*F38(v,0x34));
        wave=math_fast_sin_or_cos_b(phase);
        height=F38(v,0x38);
        {
            float offset;
            bend=wave*3.0f;
            bend=height*(wave>=0.0f ? square_root(wave)+bend : bend-square_root(-wave))*0.25f;
            offset=F38(v,0x38)*wave*wave*0.6366197f*F38(v,0x40)*0.5f;
            F38(m,0xf4)=-(F38(v,0x40)*wave+1.5707965f);
            FastVecScale(tmp,g_sway_direction_vec,offset);
        }
        FastVecAdd(m+0x10,tmp,v);
        FastVecScale(tmp,v+0x10,bend);
        FastVecAdd(m+0x10,tmp,m+0x10);
        if(math_fabs(phase)<0.1f) F38(v,0x40)=math_random_float_range(30.0f,60.0f)*0.017453294f;
        if(F38(m,0x18)<F38(v,0x48) || math_fast_float_d((int *)(v+0x30))) moby_set_state(m,3,-1);
        break;
    case 3:
        if(flag_set_first_pending(m)) I38(v,0x30)=50;
        F38(m,0xf4)=(F38(m,0xf4)+1.5707964f)*0.94f-1.5707964f;
        m[0x23]=(int)((float)I38(v,0x30)*1.5999999f);
        if(math_fast_float_d((int *)(v+0x30))) {moby_mark_spawned(m);return;}
        break;
    }
    F38(v,0x3c)+=1.0f;
}

