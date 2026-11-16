#include "include_asm.h"

#include "common.h"
extern void FastVecSub(void *, void *, void *);
extern void matrix_mul_vec3(void *, void *, void *);
extern char *CreateMoby(int id);
extern void moby_init_child_from_parent(void *, void *);
extern float math_random_angle(void);
extern void euler_rotation_basis(void *, void *);
extern void vec_fast_normalize_helper(void *, void *, float);
extern float weapon_compute_shot_launch_speed(float *a, float *b, float *out, float d, float e);
extern void matrix_from_basis_rows(void *, void *);
extern float g_debris_l07_gravity __attribute__((sda));
extern float g_debris_speed __attribute__((sda));
extern float g_debris_l07_scale_factor __attribute__((sda));
typedef struct {
    char pad00[0x10];
    float pos[4];           
    char pad20[0x04];
    char *pClass;           
    char pad28[0x04];
    float scale;            
    char pad30[0x04];
    unsigned short flags;   
    char pad36[0x32];
    char *pVars;            
    char pad6C[0x54];
    float mtx[12];          
    float rot[4];           
} F43E0Moby;
typedef struct {
    float offset[4];        
    float vel[4];           
    char *owner;            
    char pad24[0x10];
    float x34;              
} F43E0Vars;

/* Spawn an object of class 0xE1D at POS with a random rotation and the class scale, then aim it
   at TARGET: velocity toward the target at the configured speed, with the vertical component of
   a ballistic arc under the configured gravity (both per 60 Hz frame). With an owner, the
   velocity and the offset from the owner are kept in the owner's frame. Returns the object. */
char *func_PAL_L07_003F8B18(char *a0, char *a1, char *a2, char *a3, float a4)
{
    F43E0Moby *obj = (F43E0Moby *)CreateMoby(0xE1D);

    if (obj != 0) {
        F43E0Vars *st;
        float speed, gravity;
        float buf[16];

        moby_init_child_from_parent(obj, a0);
        qcopy(obj->pos, a2);
        obj->rot[2] = math_random_angle();
        obj->rot[0] = math_random_angle();
        euler_rotation_basis(obj->mtx, obj->rot);
        obj->flags |= 0x100;
        st = (F43E0Vars *)obj->pVars;
        obj->scale = *(float *)(obj->pClass + 0x24) * g_debris_l07_scale_factor;
        speed = g_debris_speed * (0.020000001f);
        gravity = g_debris_l07_gravity * (0.00040000002f);
        st->owner = a1;
        FastVecSub(st->vel, a3, obj->pos);
        vec_fast_normalize_helper(st->vel, st->vel, speed);
        st->vel[2] = weapon_compute_shot_launch_speed(obj->pos, (float *)a3, 0, speed, -gravity);
        st->vel[3] = gravity;
        st->x34 = a4;
        if (a1 != 0) {
            matrix_from_basis_rows(buf, a1 + 0xC0);
            matrix_mul_vec3(st->vel, st->vel, buf);
            FastVecSub(st->offset, obj->pos, a1 + 0x10);
            matrix_mul_vec3(st->offset, st->offset, buf);
        }
    }
    return (char *)obj;
}

extern f32 func_2E5318(f32 a, f32 b);
extern f32 func_2E4918(f32 a, f32 b);
extern f32 g_unused_float_param __attribute__((sda));
extern u8 *g_moby_l07_array __attribute__((sda));
extern u8 *func_2CD050(s32 a);
extern s32 func_312FA8(u8 *a, s32 b, s32 c);
extern f32 func_313008(u8 *a, s32 b);
extern f32 g_boss_cam_distance __attribute__((sda));
extern f32 g_boss_cam_height __attribute__((sda));
extern u32 g_boss_screen_color __attribute__((sda));
extern f32 g_bomb_scale __attribute__((sda));
extern f32 g_beam_fade_in_rate __attribute__((sda));
extern f32 g_beam_fade_out_rate __attribute__((sda));
extern f32 g_beam_spin_rate __attribute__((sda));
extern f32 ApproachValue(f32 *value, f32 target, f32 step);
extern void moby_set_state(u8 *a, u8 b, s32 c);
extern void moby_mark_spawned(void *a);
extern f32 FastAddRotations(f32 a, f32 b);
extern void gfx_add_draw_callback_first(void *a, void *b);
extern void beam_get_end_points(void *a, void *b, void *c);
extern s32 coll_cast_object_line(void *a, void *b, void *c, s32 d, f32 e, f32 f, s32 g, s32 h, s32 i);
extern char DrawSegmentedBeam[];
extern f32 g_hero_reset_offset_z;
extern u8 g_hero_l07_reset_position __attribute__((sda));
extern u16 **g_group_l07_id_lists;
extern u8 *g_joint_record_table;
extern u8 *g_matrix_l07_record_table;
extern s32 g_ship_phase_state;
extern u8 *cam_alloc_override_slot(s32);
extern f32 func_2E49C8(f32 a, f32 b);
extern f32 func_2E5360(f32 a, f32 b);
extern f32 g_aim_yaw_turn_accel __attribute__((sda));
extern f32 g_aim_yaw_max_turn_speed __attribute__((sda));
extern u8 *g_world_info __attribute__((nosda));
extern u8 *g_snowfall_target_moby MACRO_ADDR;
extern u8 g_aim_yaw_init_flag;
extern u8 g_hero_state[];
extern u32 g_frame_l07_counter MACRO_ADDR;
extern f32 fast_vec_dist(u8 *a, u8 *b);
extern f32 g_bomb_scale __attribute__((sda));
extern u8 *g_hit_object_list[];

/* Advances the object's own state: three step kinds by the 0x20 flag, then the shared
   spin and the two sampled vectors. */
void func_PAL_L07_003F90C8(u8 *a0)
{
    u8 *s1 = a0;
    u8 *s2 = *(u8 **)(a0 + 0x68);
    u8 v1 = *(u8 *)(a0 + 0x20);
    f32 v[4];
    f32 w[4];

    switch (v1) {
    case 0:
        {
            u32 n = *(u16 *)(s1 + 0x96) + 1;

            *(u16 *)(s1 + 0x96) = n;
            if ((u16)n == 1) {
                break;
            }
            ApproachValue((f32 *)(s2 + 0x24), 1.0f, g_beam_fade_in_rate * (0.020000001f));
            if (1.0f <= *(f32 *)(s2 + 0x24)) {
                moby_set_state(s1, 1, -1);
            }
        }
        break;
    case 1:
        ApproachValue((f32 *)(s2 + 0x24), 0.0f, g_beam_fade_out_rate * (0.020000001f));
        if (*(f32 *)(s2 + 0x24) <= 0.0f) {
            moby_mark_spawned(s1);
            return;
        }
        break;
    }
    *(f32 *)(s2 + 0x28) = FastAddRotations(*(f32 *)(s2 + 0x28), g_beam_spin_rate * 0.0003490659f);
    gfx_add_draw_callback_first(DrawSegmentedBeam, s1);
    if (0.333f < *(f32 *)(s2 + 0x24)) {
        beam_get_end_points(s1, v, w);
        coll_cast_object_line(*(u32 *)(s1 + 0xB8), v, w, 1, *(f32 *)(s2 + 0x2C), 1.0f, 0, 1, 0);
    }
}
