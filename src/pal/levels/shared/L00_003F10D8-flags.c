#include "include_asm.h"

#include "common.h"
typedef int TI128 __attribute__((mode(TI)));
typedef union { TI128 q; float f[4]; } Vector;
extern char g_camera_l00_position[];
extern void func_002A0F48(void *);
typedef struct { char pad[0x2290]; char *camera; int mode; char gap[0x254]; short alternate; } ProjectileOwner;
extern ProjectileOwner g_hero_state;
extern void FastVecScale(char *, char *, float);
extern float math_random_angle(void);
extern char *CreateMoby(int);
extern unsigned char g_kilonoid_weapon_index;
typedef struct { char pad[0x50]; float speed; char rest[0x8C]; } ProjectileTuning;
extern ProjectileTuning g_weapon_l00_table[];
extern char g_hero_l00_position[];
extern void FastVecAdd(void *, void *, void *);
extern void FastVecSub(void *, void *, void *);
extern void vec_scale_to_length(void *, void *, float);
extern int CollLine(void *, void *, int, void *, int);
extern char *moby_get_private_value_0(void *);
extern void cam_compute_view_direction(void *, void *, int);
extern void vec_add_transformed_or_copy(void *, void *, void *);
extern void moby_pulse_axis_scale(void *);
extern int FloatToInt(float);
extern float IntToFloat(int);
extern float math_random_float_range(float, float);

/* Allocate a projectile and initialize its position, velocity and random phases. */
char *homing_l00_shot_spawn_pal(char *position, char *source, char *target)
{
    Vector vec_a,vec_b,vec_c,vec_d;
    char *object = CreateMoby(0xCBB);
    char *state, *private_data;
    float speed;
    if (object) {
        *(unsigned char *)(object+0x30) = 255;
        *(short *)(object+0x34) = 256;
        *(short *)(object+0x32) = 255;
        object[0x31] = 1;
        *(char **)(object+0xB8) = source;
        object[0x20] = 0;
        state = *(char **)(object+0x68);
        speed = (*(ProjectileTuning *)(g_kilonoid_weapon_index * 224 + (char *)g_weapon_l00_table)).speed * 0.020000001f;
        if (g_hero_state.mode==29 && (*(unsigned short *)(g_hero_state.camera+0x34)&1)) {
            qcopy(object+0x10,g_camera_l00_position);
            FastVecScale((char *)&vec_a,g_camera_l00_position+0x250,-0.5f);
            FastVecAdd(object+0x10,object+0x10,&vec_a);
            FastVecScale((char *)&vec_b,g_camera_l00_position+0x240,-0.25f);
            FastVecAdd(object+0x10,object+0x10,&vec_b);
            FastVecScale((char *)&vec_c,g_camera_l00_position+0x230,0.1f);
            FastVecAdd(object+0x10,object+0x10,&vec_c);
            FastVecScale((char *)&vec_d,g_camera_l00_position+0x230,20.0f);
            FastVecAdd(&vec_d,g_camera_l00_position,&vec_d);
            if(CollLine(g_camera_l00_position,&vec_d,0,g_hero_state.camera,0)) qcopy(&vec_d,g_hero_l00_position);
            FastVecSub(state+0x20,&vec_d,object+0x10);
            vec_scale_to_length(state+0x20,state+0x20,speed);
        } else {
            if (g_hero_state.alternate==1) {
                vec_scale_to_length(state+0x20,source+0xD0,-speed);
                qcopy(object+0x10,position);
            } else {
                if(target) {
                    qcopy(&vec_a,target+0x10);
                    private_data=moby_get_private_value_0(target);
                    if(private_data) {
                        cam_compute_view_direction(target+0x10,&vec_b,1);
                        FastVecScale((char *)&vec_b,(char *)&vec_b,*(float *)(private_data+0x10));
                        FastVecAdd(&vec_a,&vec_a,&vec_b);
                    }
                    FastVecSub(state+0x20,&vec_a,position);
                    vec_scale_to_length(state+0x20,state+0x20,speed);
                } else vec_scale_to_length(state+0x20,source+0xC0,speed);
                qcopy(object+0x10,position);
            }
        }
        *(float *)(state+0x2C)=speed;
        vec_add_transformed_or_copy(state+0x20,state+0x20,position);
        moby_pulse_axis_scale(object);
        *(int *)(state+0x38)=((s32)(FloatToInt(16.666666f)) * 5 + 2) / 6;
        { float duration = IntToFloat(*(int *)(state+0x38));
            *(float *)(state+0x3C)=1.0f/duration; }
        *(float *)(object+0x2C)=*(float *)(*(char **)(object+0x24)+0x24)*6.0f;
        object[0x20]=0;
        *(char **)(state+0x1C)=target;
        if(target) {
            private_data=moby_get_private_value_0(target);
            if(private_data) *(unsigned short *)(private_data+0x1E)|=0x80;
        }
        *(float *)(state+0x30)=0.0f;
        *(float *)(state+0x40)=1.0f;
        speed=*(float *)(state+0x30);
        *(float *)(state+0x44)=math_random_float_range(speed,0.069813177f);
        *(float *)(state+0x48)=math_random_float_range(speed,0.13962635f);
        *(float *)(state+0x4C)=math_random_float_range(speed,0.2792527f);
        *(float *)(object+0xF0)=math_random_angle();
        *(float *)(object+0xF4)=math_random_angle();
        *(float *)(object+0xF8)=math_random_angle();
        *(float *)(state+4)=math_random_angle();
        *(float *)(state+8)=math_random_angle();
        *(float *)(state+12)=math_random_angle();
        func_002A0F48(object);
    }
    return object;
}
