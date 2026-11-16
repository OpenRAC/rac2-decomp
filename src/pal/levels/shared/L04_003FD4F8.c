#include "include_asm.h"
#include "names.h"

/* func_PAL_L04_003FD4F8 is in L04_003FD4F8-shot.c. */

/* func_PAL_L04_003FD8F0 is in L04_003FD4F8-homing.c. */

/* func_PAL_L04_003FDE38 is in L04_003FDE38-zero.c. */

#include "common.h"
typedef int Q16_B0e5d8f83 __attribute__((mode(TI)));
extern void vec_scale_to_length(char *, char *, float);
extern void FastVecAdd(void *, void *, void *);
extern void FastVecSub(void *, void *, void *);
typedef union {
    Q16_B0e5d8f83 q;
    float f[4];
} Vec;
typedef struct {
    u8 pad00[0x0F];
    u8 f0F;                      
    int f10;                     
    u8 pad14[0x24 - 0x14];
    float scale;                 
    u8 pad28[0x40 - 0x28];
    int f40;                     
    u16 modeBits;                
} MobyClass;
typedef struct Moby {
    u8 pad00[0x10];
    Vec position;                
    u8 state;                    
    u8 pad21[0x24 - 0x21];
    MobyClass *mclass;           
    u8 pad28[0x2C - 0x28];
    float scale;                 
    u8 f30;                      
    u8 f31;                      
    s16 f32;                     
    u16 modeBits;                
    s16 f36;                     
    u8 pad38[0x40 - 0x38];
    u8 f40[4];                   
    u8 pad44[0x61 - 0x44];
    u8 f61;                      
    u8 f62;                      
    u8 pad63[0x68 - 0x63];
    void *vars;                  
    u8 pad6C[0x7F - 0x6C];
    u8 f7F;                      
    u8 pad80[0x98 - 0x80];
    int f98;                     
    u8 pad9C[0xA8 - 0x9C];
    u8 impactSlot;               
    u8 padA9;
    s16 oClass;                  
    u8 padAC[0xB2 - 0xAC];
    s16 uid;                     
    u8 padB4[0xB8 - 0xB4];
    struct Moby *parent;         
    u8 fBC;                      
    u8 padBD[0xF0 - 0xBD];
    Vec rotation;                
} Moby;
typedef struct {
    float v[4];                  
    void *owner;                 
    int flags;                   
    u8 mode;                     
    u8 enabled;                  
    u16 oClass;                  
    float radius;                
    int active;                  
} CollisionProbe;
typedef struct {
    Vec point;                   
    u8 pad10[0x20 - 0x10];
    Vec normal;                  
    Vec f30;                     
    Vec f40;                     
} CollisionHit;
typedef struct {
    u8 pad00[0x18];
    Moby *moby;                  
    int count;                   
    CollisionHit hit;            
} Collision;
typedef struct {
    u8 pad00[0x20];
    Moby *ignored;               
} ProjectileVars;
extern void vec_fast_normalize_helper(void *, void *, float);
extern int CollLine(void *, void *, int, void *, void *);
extern float FastVecLength(void *);
extern void FastVecScale(void *, void *, float);
extern int coll_process_hit(float, void *, int, void *, void *);
extern void vec_fast_normalize(void *, void *, void *);
extern void func_001290E0(void *, void *);
extern void add_vectors(void *, void *, void *);
extern float FastVecDot(void *, void *);
extern float vec_length_xy(void *);
extern float mat_fast_helper_a(float, float);
extern void part_l04_spawn_burst_pal(void *, void *, int, int);
extern Collision g_probe_hit;
extern CollisionHit g_spark_origin_quad;
extern void FastVecSub(void *, void *, void *);
extern float FastVecDot(void *, void *);

/* Sweeps a projectile from *position by direction (a line probe over the whole move and,
   when that is clear, a 0.5 sphere probe every 0.49 units) and works out its response.
   Hitting a moby other than the ignored one sets fBC to 2, moves onto that moby (or
   stays, for class 0xA1F) and returns the projectile. A surface whose normal lies 45 to
   90 degrees from direction bends direction by the normal, re-aims the projectile and
   marks the hit point; any other surface hit sets fBC to 1 and moves to the hit point.
   Moby and stopping surface hits fill response, hitNormal and hitDelta. The final
   position is written back to *position; the result is 0 unless a moby was hit. */
Moby *SweepProjectileCollision_pal(Moby *projectile, ProjectileVars *vars, float *position,
    float *direction, float *response, float *hit_normal, float *hit_delta)
{
    float pos[4];
    float unit[4];
    float step[4];
    CollisionProbe probe;
    float forward[4];
    float hit_point[4];
    float target[4];
    Collision *collision;
    Moby *hit_moby;
    Moby *result = 0;
    float remaining;
    float stride = 0;
    float dot;
    int line_hit;
    int collided = 0;

    *(Q16_B0e5d8f83 *)pos = *(Q16_B0e5d8f83 *)position;
    probe.flags = 0x30000;
    probe.radius = 2;
    probe.owner = projectile;
    probe.active = 1;
    qcopy(probe.v, direction);
    vec_fast_normalize_helper(&probe, &probe, 1);
    probe.enabled = 1;
    probe.v[3] = 5627.925f;
    probe.mode = 3;
    probe.oClass = projectile->oClass;
    probe.v[2] = 1;

    FastVecAdd(step, pos, direction);
    line_hit = CollLine(pos, step, 0, vars->ignored, &probe);
    if (line_hit) {
        collided = 1;
        remaining = 0;
    } else {
        stride = 0.49f;
        remaining = FastVecLength(direction);
        if (remaining > 0)
            FastVecScale(unit, direction, 1.0f / remaining);
        else
            qzero(unit);
    }
    while (remaining > 0 && !collided) {
        if (stride < remaining) {
            FastVecScale(step, unit, stride);
            remaining -= stride;
        } else {
            FastVecScale(step, unit, remaining);
            remaining = 0;
        }
        FastVecAdd(pos, pos, step);
        if (coll_process_hit(0.5f, pos, 0, vars->ignored, &probe))
            collided = 1;
    }

    if (collided) {
        collision = &g_probe_hit;
        if (collision->moby) {
            if (collision->moby == vars->ignored)
                goto done;
            projectile->fBC = 2;
            hit_moby = collision->moby;
            if (hit_moby->oClass == 0xA1F)
                qcopy(pos, &projectile->position);
            else
                qcopy(pos, &hit_moby->position);
            FastVecSub(hit_delta, &g_spark_origin_quad.f30, &g_spark_origin_quad.f40);
            vec_scale_to_length((char *)hit_delta, (char *)hit_delta, 1);
            result = projectile;
            vec_fast_normalize(response, direction, &g_spark_origin_quad.normal);
            vec_scale_to_length((char *)response, (char *)response, 0.040000003f);
            vec_scale_to_length((char *)hit_normal, (char *)&g_spark_origin_quad.normal, 1);
        } else if (collision->count > 0) {
            *(Q16_B0e5d8f83 *)forward = *(Q16_B0e5d8f83 *)direction;
            func_001290E0(&collision->hit.normal, &collision->hit.normal);
            func_001290E0(forward, forward);
            dot = FastVecDot(forward, &collision->hit.normal);
            if (dot > 0 && dot < 0.707f) {
                FastVecScale(&collision->hit.normal, &collision->hit.normal, dot);
                FastVecAdd(direction, direction, &collision->hit.normal);
                add_vectors(target, pos, direction);
                projectile->rotation.f[2] = mat_fast_helper_a(direction[0], direction[1]);
                projectile->rotation.f[1] = -mat_fast_helper_a(vec_length_xy(direction), direction[2]);
                *(Q16_B0e5d8f83 *)hit_point = collision->hit.point.q;
                part_l04_spawn_burst_pal(hit_point, direction, 4, 0);
            } else {
                projectile->fBC = 1;
                qcopy(pos, &g_spark_origin_quad.point);
                FastVecSub(hit_delta, &g_spark_origin_quad.f30, &g_spark_origin_quad.f40);
                vec_scale_to_length((char *)hit_delta, (char *)hit_delta, 1);
                vec_fast_normalize(response, direction, &g_spark_origin_quad.normal);
                vec_scale_to_length((char *)response, (char *)response, 0.040000003f);
                vec_scale_to_length((char *)hit_normal, (char *)&g_spark_origin_quad.normal, 1);
            }
        }
    }
done:
    *(Q16_B0e5d8f83 *)position = *(Q16_B0e5d8f83 *)pos;
    return result;
}



extern void *CreateMoby(void *a0);
extern void func_002A0F48(void *a0);
extern void ref_L04_003FA5A8_00(void *, float, float, float);
extern unsigned char *ref_L04_003FA5A8_01(void *, void *, void *, float *, float *, float *, float, float);
extern void ref_L04_003FA5A8_02(void *, void *, void *);
extern void ref_L04_003FA5A8_03(void *, void *, void *, void *, void *, void *, void *);

/* Spawns a homing rocket for an owner: picks a target if none is given, sets its speed, turning and lifetime values and starts it moving. */
unsigned char *homing_rocket_spawn_pal(unsigned char *owner, float *pos,
    unsigned char *target, float x, float y, float z, float angle, float tilt)
{
    float origin[4], matrix[16], position[4];
    unsigned char *moby = CreateMoby((void *)0xABD);
    unsigned char *state;

    if (moby != 0) {
        moby[0x30] = 255;
        *(short *)(moby + 0x32) = 255;
        moby[0x31] = 1;
        moby[0x20] = 0;
        *(float *)(moby + 0xF8) = angle;
        *(float *)(moby + 0xF4) = tilt;
        *(float *)(moby + 0x2C) =
            *(float *)(*(unsigned char **)(moby + 0x24) + 0x24) * 3.0f;
        state = *(unsigned char **)(moby + 0x68);
        if (target == 0) {
            ref_L04_003FA5A8_00(matrix, 0.40000004f, angle, tilt);
            *(Q16_B0e5d8f83 *)position = *(Q16_B0e5d8f83 *)pos;
            target = ref_L04_003FA5A8_01(moby, position, matrix, &x, &y, &z,
                0.349065899848938f, 30.0f);
        }
        *(void **)(state + 0x20) = owner;
        qcopy(moby + 0x10, pos);
        *(int *)(state + 0x48) = 1;
        *(float *)(state + 0x44) = 1.0000001f;
        *(int *)(state + 0x34) = 0;
        *(int *)(state + 0x38) = 0;
        *(int *)(state + 0x30) = 0;
        *(int *)(state + 0x54) = -1;
        *(int *)(state + 0x50) = -1;
        *(void **)(state + 0x28) = target;
        *(float *)(state + 0x3C) = x;
        *(float *)(state + 0x40) = y;
        *(int *)(state + 0x24) = 250;
        if (target != 0) {
            qcopy(state, target + 0x10);
            *(float *)(state + 8) += z;
            *(float *)(state + 0x2C) = z;
        }
        if (owner != 0 && *(short *)(owner + 0xAA) == 0xBBC) {
            *(short *)(state + 0x4E) = 50;
            *(short *)(state + 0x4C) = 50;
        } else {
            *(short *)(state + 0x4E) = 1;
            *(short *)(state + 0x4C) = 1;
        }
        *(Q16_B0e5d8f83 *)origin = *(Q16_B0e5d8f83 *)(owner + 0x10);
        origin[2] = pos[2];
        ref_L04_003FA5A8_02(matrix, pos, origin);
        if (target != 0 && *(short *)(target + 0xAA) != 0xBBC) {
            ref_L04_003FA5A8_03(moby, state, origin, matrix,
                matrix + 12, matrix + 4, matrix + 8);
        }
        func_002A0F48(moby);
        *(float *)(moby + 0x2C) += *(float *)(moby + 0x2C);
    }
    return moby;
}




extern int FloatToInt(float);
typedef struct {
    unsigned char pad0[0x74];
    unsigned char active;
    unsigned char pad75[0x88 - 0x75];
    void *owner;
} L04_C678Slot;
typedef int L04_C678Quad __attribute__((mode(TI)));
typedef struct {
    unsigned char pad0[0x74];
    unsigned char *owner;
    int timer;
    float age;
} L04_C678Vars;
extern int math_fast_float_d(void *);
extern int FloatToInt(float);
extern void moby_mark_spawned(void *);
extern float StepAngleTowardTarget(void *, int, float, float);
extern void snd_stop_voice(int);
extern void gfx_add_draw_callback_second(void *, void *);
extern void moby_damage_in_firing_cone_pal(unsigned char *, L04_C678Vars *);
extern void DrawDomeEffect_pal(void);
extern unsigned char g_sound_state[];
extern int g_shield_dome_sound_handle __attribute__((sda));

/* Updates the shield dome: follows its owner, ages, fades out and frees itself when its timer ends, and otherwise damages what is inside. */
void blast_effect_update_pal(unsigned char *moby)
{
    L04_C678Vars *vars = *(L04_C678Vars **)(moby + 0x68);
    int sound_handle;
    L04_C678Slot *slot;

    *(L04_C678Quad *)(moby + 0x10) = *(L04_C678Quad *)(vars->owner + 0x10);
    StepAngleTowardTarget(moby + 0xF8, 0, *(float *)(vars->owner + 0xF8), 0.031415932f);
    vars->age = vars->age + 1.0f;
    if (vars->timer != 0 && math_fast_float_d(&vars->timer) != 0) {
        sound_handle = g_shield_dome_sound_handle;
        if (sound_handle != -1) {
            slot = (L04_C678Slot *)(g_sound_state + sound_handle * 0x70);
            if (slot->owner == vars->owner && slot->active != 0) {
                snd_stop_voice(sound_handle);
            }
        }
        g_shield_dome_sound_handle = -1;
        moby_mark_spawned(moby);
        return;
    }
    if (25.0f < vars->age && vars->timer == 0) {
        vars->timer = FloatToInt(12.833334f);
    } else {
        moby_damage_in_firing_cone_pal(moby, vars);
    }
    gfx_add_draw_callback_second(DrawDomeEffect_pal, moby);
}

