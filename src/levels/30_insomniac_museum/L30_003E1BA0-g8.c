#include "names.h"
/* func_L30_003E1BA0 has a unit of its own (-O2 -G8 -ffunction-sections -Wa,-G32 in
 * config/cflags.txt): the assembler's -G32 makes the two 16-byte sda vectors $gp-relative.
 * The saved home position/rotation and the vector zeroed in state 0 are sda incomplete arrays: cc1
 * keeps their addresses whole and the assembler builds them absolute (lui/addiu, lui $at for
 * the store of its z), while the boot vector D_00189EA0 is split into %hi/%lo. */
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
extern int cam_moby_update(void *);
extern void *part_find_owned_effect_slot(void *,int,int);
extern void vec_clear_128(void *),vec_copy_helper_a(void *),FastVecSub(void *,void *,void *),FastVecCross(void *,void *,void *),matrix_mul_vec3(void *,void *,void *),FastVecAdd(void *,void *,void *),euler_rotation_basis(void *,void *);
extern void vec_fast_normalize_helper(void *,void *,float),vec_scale_to_length(void *,void *,float);
extern float math_fast_sin_or_cos_b(float),math_fast_sin_or_cos_a(float);
extern void SpawnTintedEffects(void *,void *,float,int,int,void *,unsigned,int,float,float,float);
extern void cam_moby_init_tracking(void *,int,int,void *,void *,int,float);
/* Updates a museum gadget (moby class 3142). When triggered it fires an effect from a fixed spot, waits for it to end, then fades and returns to its home place. */
void museum_firing_gadget_update(unsigned char *obj) {
    struct { float v[4], axis[4], up[4], pos[4]; } f;
    switch(obj[0x20]) {
    case 0:
        obj[0x30]=255; moby_set_state(obj,1,-1);
        *(unsigned short *)(obj+0x34)|=0x100;
        qcopy(g_gadget_position,obj+0x10); qcopy(g_gadget_rotation,obj+0xF0);
        vec_clear_128(g_gadget_aim_offset); g_gadget_aim_offset[2]=0.4f;
        break;
    case 1:
        if(part_find_owned_effect_slot(obj,0x10000,0)) {
            float frameTime=0.016666668f;
            float angleScale;
            FastVecSub(f.v,obj+0x10,g_hero_position);
            angleScale=0.00029088825f;
            vec_fast_normalize_helper(f.v,f.v,g_museum_gadget_move_scale*frameTime);
            f.v[2]=g_museum_gadget_lift_speed*frameTime;
            vec_copy_helper_a(f.up);
            FastVecCross(f.axis,f.v,f.up);
            vec_scale_to_length(f.axis,f.axis,math_fast_sin_or_cos_b(-g_museum_gadget_angle_scale*angleScale));
            f.axis[3]=math_fast_sin_or_cos_a(g_museum_gadget_angle_scale*angleScale);
            matrix_mul_vec3(f.pos,g_museum_gadget_muzzle_offset,obj+0xC0);
            FastVecAdd(f.pos,f.pos,obj+0x10);
            SpawnTintedEffects(obj,f.pos,g_museum_gadget_fx_scale,g_museum_gadget_fx_count,g_museum_gadget_fx_life,g_museum_gadget_effect_vec,0x50404040,0,g_museum_gadget_fx_speed,g_museum_gadget_fx_spread,g_museum_gadget_fx_fade);
            cam_moby_init_tracking(obj,0,-1,f.v,f.axis,255,15.0f);
            *(int *)(obj+0x98)=0; moby_set_state(obj,2,-1);
        }
        break;
    case 2: if(cam_moby_update(obj)) moby_set_state(obj,3,-1); break;
    case 3:
        if(obj[0x23]<2) {
            qcopy(obj+0x10,g_gadget_position); euler_rotation_basis(obj+0xC0,g_gadget_rotation);
            obj[0x23]=128; *(int *)(obj+0x98)=*(int *)(*(char **)(obj+0x24)+0x10); moby_set_state(obj,1,-1);
        } else obj[0x23]-=2;
        break;
    }
    obj[0xA8]=255;
}
