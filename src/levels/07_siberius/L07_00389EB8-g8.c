#include "common.h"
#include "include_asm.h"

extern int D_L07_001B0AE0 __attribute__((sda));

extern void moby_mark_spawned(int);

/* Run the shared per-object pass once a level latch is set. */
/* Per-frame update for moby class 3361: removes the object once the level flag is set. */
void moby_destroy_when_level_flag(int moby)
{
    if (D_L07_001B0AE0 != 0)
        moby_mark_spawned(moby);
}

extern char *moby_get_private_value_2(char *);
extern void FastVecAdd(void *, void *, void *);
extern void FastVecSub(void *, void *, void *);
extern void matrix_mul_vec3(void *, void *, void *);
extern float FastVecLength(void *);
extern float square_root(float);
extern float FastVecDot(void *, void *);
extern float FastAddRotations(float, float);
extern float math_fast_sin_or_cos_b(float);
extern void vec_scale_to_length(void *, void *, float);
extern void vec_clamp_length(void *, float);
extern void math_step_value_toward_target(void *, void *, float, float, float, float);
extern void mat_combine_and_store(void *, void *, void *, void *);
extern float vec_distance_xy(void *, void *);
extern float D_L07_001B0C60 __attribute__((sda));
extern float D_L07_001B0C64 __attribute__((sda));
extern float D_L07_001B0C68 __attribute__((sda));
extern float D_L07_001B0C6C __attribute__((sda));
extern float D_L07_001B0C70 __attribute__((sda));
extern float D_L07_001B0C74 __attribute__((sda));
extern float D_L07_001B0C78 __attribute__((sda));
extern float D_L07_001B0C7C __attribute__((sda));
extern float D_L07_001B0C80 __attribute__((sda));
extern float D_L07_001B0C84 __attribute__((sda));
extern float D_L07_001B0C88 __attribute__((sda));

/* Steer the object's anchor toward its target (relative to the attached object when there is
   one) with a speed-limited, frame-scaled step, update the angular state, and return the
   remaining distance to the target (the caller compares it with 3.0). */
extern char *CreateMoby(int id);
extern void moby_init_child_from_parent(void *, void *);
extern float math_random_angle(void);
extern void euler_rotation_basis(void *, void *);
extern void vec_fast_normalize_helper(void *, void *, float);
extern float weapon_compute_shot_launch_speed(float *a, float *b, float *out, float d, float e);
extern void matrix_from_basis_rows(void *, void *);
extern float D_L07_001B0E30 __attribute__((sda));
extern float D_L07_001B0E34 __attribute__((sda));
extern float D_L07_001B0E38 __attribute__((sda));

/* The spawned object and its state block, as far as func_L07_003F43E0 uses them. */
typedef struct {
    char pad00[0x10];
    float pos[4];          /* 0x10 */
    char pad20[0x04];
    char *pClass;          /* 0x24: class data; +0x24 is its base scale */
    char pad28[0x04];
    float scale;           /* 0x2C */
    char pad30[0x04];
    unsigned short flags;  /* 0x34 */
    char pad36[0x32];
    char *pVars;           /* 0x68 */
    char pad6C[0x54];
    float mtx[12];         /* 0xC0 */
    float rot[4];          /* 0xF0 */
} F43E0Moby;

typedef struct {
    float offset[4];       /* 0x00 */
    float vel[4];          /* 0x10 */
    char *owner;           /* 0x20 */
    char pad24[0x10];
    float x34;             /* 0x34 */
} F43E0Vars;

/* Spawn an object of class 0xE1D at POS with a random rotation and the class scale, then aim it
   at TARGET: velocity toward the target at the configured speed, with the vertical component of
   a ballistic arc under the configured gravity (both per 60 Hz frame). With an owner, the
   velocity and the offset from the owner are kept in the owner's frame. Returns the object. */
char *SpawnBallisticMoby(char *parent, char *owner, char *spawn_pos, char *target_pos, float extra_value)
{
    F43E0Moby *obj = (F43E0Moby *)CreateMoby(0xE1D /* moby class 3613 */);

    if (obj != 0) {
        F43E0Vars *vars;
        float speed, gravity;
        float buf[16];

        moby_init_child_from_parent(obj, parent);
        qcopy(obj->pos, spawn_pos);
        obj->rot[2] = math_random_angle();
        obj->rot[0] = math_random_angle();
        euler_rotation_basis(obj->mtx, obj->rot);
        obj->flags |= 0x100;
        vars = (F43E0Vars *)obj->pVars;
        obj->scale = *(float *)(obj->pClass + 0x24) * D_L07_001B0E38;
        speed = D_L07_001B0E34 * (1.0f / 60.0f);
        gravity = D_L07_001B0E30 * (1.0f / 3600.0f);
        vars->owner = owner;
        FastVecSub(vars->vel, target_pos, obj->pos);
        vec_fast_normalize_helper(vars->vel, vars->vel, speed);
        vars->vel[2] = weapon_compute_shot_launch_speed(obj->pos, (float *)target_pos, 0, speed, -gravity);
        vars->vel[3] = gravity;
        vars->x34 = extra_value;
        if (owner != 0) {
            matrix_from_basis_rows(buf, owner + 0xC0);
            matrix_mul_vec3(vars->vel, vars->vel, buf);
            FastVecSub(vars->offset, obj->pos, owner + 0x10);
            matrix_mul_vec3(vars->offset, vars->offset, buf);
        }
    }
    return (char *)obj;
}
