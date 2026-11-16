#include "include_asm.h"

#include "common.h"
extern char g_gadget_position[] __attribute__((sda)), g_gadget_rotation[] __attribute__((sda)), g_hero_position[];
extern float g_gadget_aim_offset[] __attribute__((sda));
extern float g_museum_gadget_move_scale __attribute__((sda));
extern float g_museum_gadget_lift_speed __attribute__((sda));
extern float g_museum_gadget_angle_scale __attribute__((sda));
extern float g_museum_gadget_fx_scale __attribute__((sda));
extern float g_museum_gadget_fx_speed __attribute__((sda));
extern float g_museum_gadget_fx_spread __attribute__((sda));
extern float g_museum_gadget_fx_fade __attribute__((sda));
extern int g_museum_gadget_fx_count __attribute__((sda));
extern int g_museum_gadget_fx_life __attribute__((sda));
extern char g_museum_gadget_muzzle_offset[16] __attribute__((sda)), g_museum_gadget_effect_vec[16] __attribute__((sda));
extern void moby_set_state(void *,int,int);
extern int cam_moby_update_pal(void *);
extern void *part_find_owned_effect_slot(void *,int,int);
extern void vec_clear_128(void *),vec_copy_helper_a(void *),FastVecSub(void *,void *,void *),FastVecCross(void *,void *,void *),matrix_mul_vec3(void *,void *,void *),FastVecAdd(void *,void *,void *),euler_rotation_basis(void *,void *);
extern void vec_fast_normalize_helper(void *,void *,float),vec_scale_to_length(void *,void *,float);
extern float math_fast_sin_or_cos_b(float),math_fast_sin_or_cos_a(float);
extern void part_spawn_glow_fade_effects_pal(void *,void *,float,int,int,void *,unsigned,int,float,float,float);
extern void cam_moby_init_tracking_pal(void *,int,int,void *,void *,int,float);

/* Updates a museum gadget. When triggered it fires an effect from a fixed spot, waits for it to end, then fades and returns to its home place (PAL version). */
void museum_firing_gadget_update_pal(unsigned char *obj) {
    struct { float v[4], axis[4], up[4], pos[4]; } fx;
    switch(obj[0x20]) {
    case 0:
        obj[0x30]=255; moby_set_state(obj,1,-1);
        *(unsigned short *)(obj+0x34)|=0x100;
        qcopy(g_gadget_position,obj+0x10); qcopy(g_gadget_rotation,obj+0xF0);
        vec_clear_128(g_gadget_aim_offset); g_gadget_aim_offset[2]=0.4f;
        break;
    case 1:
        if(part_find_owned_effect_slot(obj,0x10000,0)) {
            float frame_time=0.020000001f;
            float angle_scale;
            FastVecSub(fx.v,obj+0x10,g_hero_position);
            angle_scale=0.0003490659f;
            vec_fast_normalize_helper(fx.v,fx.v,g_museum_gadget_move_scale*frame_time);
            fx.v[2]=g_museum_gadget_lift_speed*frame_time;
            vec_copy_helper_a(fx.up);
            FastVecCross(fx.axis,fx.v,fx.up);
            vec_scale_to_length(fx.axis,fx.axis,math_fast_sin_or_cos_b(-g_museum_gadget_angle_scale*angle_scale));
            fx.axis[3]=math_fast_sin_or_cos_a(g_museum_gadget_angle_scale*angle_scale);
            matrix_mul_vec3(fx.pos,g_museum_gadget_muzzle_offset,obj+0xC0);
            FastVecAdd(fx.pos,fx.pos,obj+0x10);
            part_spawn_glow_fade_effects_pal(obj,fx.pos,g_museum_gadget_fx_scale,g_museum_gadget_fx_count,g_museum_gadget_fx_life,g_museum_gadget_effect_vec,0x50404040,0,g_museum_gadget_fx_speed,g_museum_gadget_fx_spread,g_museum_gadget_fx_fade);
            cam_moby_init_tracking_pal(obj,0,-1,fx.v,fx.axis,255,15.0f);
            *(int *)(obj+0x98)=0; moby_set_state(obj,2,-1);
        }
        break;
    case 2: if(cam_moby_update_pal(obj)) moby_set_state(obj,3,-1); break;
    case 3:
        if(obj[0x23]<2) {
            qcopy(obj+0x10,g_gadget_position); euler_rotation_basis(obj+0xC0,g_gadget_rotation);
            obj[0x23]=128; *(int *)(obj+0x98)=*(int *)(*(char **)(obj+0x24)+0x10); moby_set_state(obj,1,-1);
        } else obj[0x23]-=2;
        break;
    }
    obj[0xA8]=255;
}
