#include "include_asm.h"

#include "common.h"
typedef struct { u8 data[256]; } AttachObject;
extern AttachObject *g_moby_l01_table __attribute__((sda));
extern u8 *g_path_l01_table[] NOT_SDA;
extern f32 vec_distance_xy(void *, void *);
extern void FastVecAdd(void *, void *, void *);
extern void FastVecSub(void *, void *, void *);
extern void vec_scale_to_length(void *, void *, f32);
extern void matrix_from_basis_rows(void *, void *);
extern void transform_vector(void *, void *, void *);
extern void matrix_mul_vec3(void *, void *, void *);
extern void vec_fast_divide_helper(void *, void *, f32);
extern s32 point_in_path_xy(void *, void *, s32);
extern f32 math_random_float_range(f32,f32);
extern f32 mat_fast_helper_a(f32, f32);
extern f32 fast_subtract_rotations(f32, f32);
extern f32 FastAddRotations(f32, f32);
extern s32 coll_sweep_from_object(void *, void *, f32, s32, f32, f32, s32, s32, s32);
extern s32 coll_cast_object_line(void *, void *, void *, f32, s32, f32, s32, s32, s32);
extern s32 func_001163B0(void);
extern s32 FloatToInt(f32);
extern u8 *part_spawn_trail(void *, void *, void *, u32, u32, s32, s32, s32, s32);
extern void moby_follow_attached(void *, void *);
extern s32 moby_l01_turn_toward_target(void *, void *);
extern f32 func_310648();
extern f32 func_310580(f32 x, f32 y);
extern s32 func_310528(s32 a, s32 b);
extern f32 func_2E3A48(f32 x);
extern f32 func_2E3A60(f32 x);
extern s32 coll_process_hit(f32 radius, void *pos, s32 flag, void *obj, s32 arg);
extern u32 g_contact_moby_list[];
extern s32 math_fast_float_d(void *);
extern f32 FastAddRotations(f32, f32);
extern f32 math_fast_sin_or_cos_b(f32);
extern s32 FloatToInt(f32);
extern s32 snd_play_from_class_bank(s32, s32, void *, s32);
extern s32 g_current_map_index[] __attribute__((sda));
extern u8 g_moby_nibble_table[];
extern u8 *g_camera_path_configs __attribute__((sda));
extern s32 cam_is_hero_in_trigger(void *);

void moby_follow_attached_pal(void *arg, void *fallback) {
    f32 pos[4] __attribute__((aligned(16)));
    f32 delta[4] __attribute__((aligned(16)));
    f32 matrix[16] __attribute__((aligned(16)));
    u8 *obj = arg;
    u8 *state = *(u8 **)(obj+0x68);
    u8 *target;
    u8 *path;
    s32 index = *(s32 *)(state+0x410);
    if (index != -1) {
        target = (u8 *)&g_moby_l01_table[index];
        if (!target) return;
        if (*(s16 *)(target+0xAA) == 0xA56) {
            if (vec_distance_xy(obj+0x10,target+0x10)>1.0f) {
                FastVecSub(delta,obj+0x10,target+0x10);
                vec_scale_to_length(delta,delta,1.0f);
                FastVecAdd(pos,target+0x10,delta);
            } else qcopy(pos,obj+0x10);
            if (pos[2] < *(f32 *)(target+0x18)+0.01f)
                pos[2] = *(f32 *)(target+0x18)+0.011f;
        } else if (*(s16 *)(target+0xAA) == 0xA53) {
            matrix_from_basis_rows(matrix,target+0xC0);
            FastVecSub(delta,obj+0x10,target+0x10);
            transform_vector(delta,delta,matrix);
            if (delta[0]>2.0f) delta[0]=2.0f;
            else if (delta[0]<-2.0f) delta[0]=-2.0f;
            if (delta[1]>5.0f) delta[1]=5.0f;
            else if(delta[1]<-5.0f) delta[1]=-5.0f;
            if (delta[2]<0.01f) delta[2]=0.01f;
            matrix_mul_vec3(delta,delta,target+0xC0);
            FastVecAdd(pos,target+0x10,delta);
        } else qcopy(pos,obj+0x10);
        FastVecSub(delta,pos,obj+0x10);
        vec_fast_divide_helper(delta,delta,0.120000005f);
        FastVecAdd(obj+0x10,obj+0x10,delta);
        if (*(f32 *)(obj+0x18)<pos[2]) *(f32 *)(obj+0x18)=pos[2]+0.001f;
    } else {
        s32 pathIndex=*(s32 *)(state+0x1FC);
        if(pathIndex!=-1) {
            path=g_path_l01_table[pathIndex];
            if(path && !point_in_path_xy(obj+0x10,path+0x10,*(s32 *)path)) qcopy(obj+0x10,fallback);
        }
        {
            u8 *other = *(u8 **)(state + 0x248);
            if (other && (*(s16 *)(other + 0xAA) == 0xA56 ||
                          *(s16 *)(other + 0xAA) == 0xA53))
                *(s32 *)(state + 0x410) = (AttachObject *)other - g_moby_l01_table;
        }
    }
}



