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
char *SpawnBallisticMoby_pal(char *parent, char *owner, char *spawn_pos, char *target_pos, float extra_value)
{
    F43E0Moby *moby = (F43E0Moby *)CreateMoby(0xE1D);

    if (moby != 0) {
        F43E0Vars *vars;
        float speed, gravity;
        float basis[16];

        moby_init_child_from_parent(moby, parent);
        qcopy(moby->pos, spawn_pos);
        moby->rot[2] = math_random_angle();
        moby->rot[0] = math_random_angle();
        euler_rotation_basis(moby->mtx, moby->rot);
        moby->flags |= 0x100;
        vars = (F43E0Vars *)moby->pVars;
        moby->scale = *(float *)(moby->pClass + 0x24) * g_debris_l07_scale_factor;
        speed = g_debris_speed * (0.020000001f);
        gravity = g_debris_l07_gravity * (0.00040000002f);
        vars->owner = owner;
        FastVecSub(vars->vel, target_pos, moby->pos);
        vec_fast_normalize_helper(vars->vel, vars->vel, speed);
        vars->vel[2] = weapon_compute_shot_launch_speed(moby->pos, (float *)target_pos, 0, speed, -gravity);
        vars->vel[3] = gravity;
        vars->x34 = extra_value;
        if (owner != 0) {
            matrix_from_basis_rows(basis, owner + 0xC0);
            matrix_mul_vec3(vars->vel, vars->vel, basis);
            FastVecSub(vars->offset, moby->pos, owner + 0x10);
            matrix_mul_vec3(vars->offset, vars->offset, basis);
        }
    }
    return (char *)moby;
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
void beam_update_pal(u8 *moby)
{
    u8 *beam = moby;
    u8 *vars = *(u8 **)(moby + 0x68);
    u8 state = *(u8 *)(moby + 0x20);
    f32 start[4];
    f32 end[4];

    switch (state) {
    case 0:
        {
            u32 n = *(u16 *)(beam + 0x96) + 1;

            *(u16 *)(beam + 0x96) = n;
            if ((u16)n == 1) {
                break;
            }
            ApproachValue((f32 *)(vars + 0x24), 1.0f, g_beam_fade_in_rate * (0.020000001f));
            if (1.0f <= *(f32 *)(vars + 0x24)) {
                moby_set_state(beam, 1, -1);
            }
        }
        break;
    case 1:
        ApproachValue((f32 *)(vars + 0x24), 0.0f, g_beam_fade_out_rate * (0.020000001f));
        if (*(f32 *)(vars + 0x24) <= 0.0f) {
            moby_mark_spawned(beam);
            return;
        }
        break;
    }
    *(f32 *)(vars + 0x28) = FastAddRotations(*(f32 *)(vars + 0x28), g_beam_spin_rate * 0.0003490659f);
    gfx_add_draw_callback_first(DrawSegmentedBeam, beam);
    if (0.333f < *(f32 *)(vars + 0x24)) {
        beam_get_end_points(beam, start, end);
        coll_cast_object_line(*(u32 *)(beam + 0xB8), start, end, 1, *(f32 *)(vars + 0x2C), 1.0f, 0, 1, 0);
    }
}
