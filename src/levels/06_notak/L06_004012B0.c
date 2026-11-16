#include "names.h"
/*
 * func_L06_004012B0: four-state update of an effect object. State 3 leaves the switch and emits its
 * two particles after it; every other path returns. Built with -frac2-keep-block-order, which keeps
 * the default block between the two: the store there is dead and costs no word, but the block lives
 * until jump2, so the end of case 3 stays a block boundary through local-alloc and both sched passes.
 * It has a unit of its own for that flag and for its prototypes, which differ from L06_0033BDC0.c's.
 */
#include "common.h"
typedef unsigned int Quad __attribute__((mode(TI)));
typedef union { Quad q; float f[4]; } Vec;
extern char *part_find_owned_effect_slot(char *, int, int);
extern int math_random_int_below(int);
extern int math_random_int_range(int, int);
extern float math_random_float_range(float, float);
extern int math_fast_float_d(void *);
extern void FastVecAdd(void *, void *, void *);
extern void FastVecSub(void *, void *, void *);
extern void vec_scale_to_length(void *, void *, float);
extern float FastAddRotations(float, float);
extern int PlayMobySound(int, int, char *);
extern char *part_spawn_blast_effect_moby(char *, void *, void *, float);
extern int coll_sweep_from_object(char *, float, void *, int, float, float, int, int, int);
extern void part_spawn_masked_debris(char *, int, float, void *, float, float, float, unsigned char);
extern void moby_mark_spawned(char *);
extern float math_step_value_toward_target(void *, float, void *, float, float, float);
extern char *part_spawn_burst(void *, void *, int, int, int, int, float, float, float, float, float);
typedef struct { char pad[0x140]; Vec position; char gap[0x10]; float scale; int unused; int duration, timer; char gap2[0x10]; float speed; int unused2, limit; } Effect;
extern Effect g_camera_state;

extern unsigned char *g_particle_l06_byte_ptr;
typedef struct { int timer; float speed, height; int handle; Vec velocity; } UpdateState;
/* Updates an object (moby class 2232) that waits to be hit, then either floats up trailing smoke or bursts with a blast, and goes away. */
void hit_reaction_burst_update(char *moby) {
    struct { Vec pos, direction, random; } frame;
    UpdateState *vars = *(UpdateState **)(moby+0x68);
    char *hit, *particle;
    float speed;
    char *position;
    Vec *velocity;

    switch ((unsigned char)moby[0x20]) {
    case 0:
        qcopy(&frame.pos,moby+0x10);
        frame.pos.f[2] += 10.0f;
        FastVecAdd(&vars->velocity,moby+0x10,&frame.pos);
        vars->handle=-1;
        moby[0x20]=1;
        return;
    case 1:
        hit=part_find_owned_effect_slot(moby,0x10000,0);
        if (hit) {
          if (*(short *)(*(char **)(hit+0x20)+0xAA)!=0x8B8 /* moby class 2232 */) {
            if (math_random_int_below(3)==1) {
                vars->timer=math_random_int_range(20,10);
                vars->height=*(float *)(moby+0x18)+20.0f;
                moby[0x20]=3;
            } else {
                vars->timer=math_random_int_range(0,10);
                moby[0x20]=2;
            }

          }
        }
        *(unsigned char *)(moby+0xA8)=255;
        return;
    case 2:
        if (math_fast_float_d(vars)) {
            float unit = 1.0f;
            PlayMobySound(0,0,moby);
            frame.random.q=0;
            frame.random.f[2]=0.050000004f;
            FastVecSub(&frame.direction,&g_camera_state.position,&frame.pos);
            vec_scale_to_length(&frame.direction,&frame.direction,unit);
            part_spawn_blast_effect_moby(moby,moby+0x10,&frame.direction,5.0f);
            g_camera_state.speed=0.1f;
            g_camera_state.limit=90;
            g_camera_state.scale=0.2f;
            g_camera_state.duration=60;
            g_camera_state.timer=0;
            coll_sweep_from_object(moby,3.0f,moby+0x10,0x10000,3.0f,1.0f,0,1,0);
            part_spawn_masked_debris(moby,0xEF,3.0f,&frame.random,6.0f,3.0f,6.0f,255);
            moby_mark_spawned(moby);
        }
        return;
    case 3:
        if (math_fast_float_d(vars)) {moby[0x20]=2; return;}
        math_step_value_toward_target(moby+0x18,vars->height,&vars->speed,0.027777778f,0.027777778f,0.33333334f);
        *(float *)(moby+0xF0)=FastAddRotations(*(float *)(moby+0xF0),math_random_int_range(-10,10)*0.017453294f);
        *(float *)(moby+0xF4)=FastAddRotations(*(float *)(moby+0xF4),math_random_int_range(-10,10)*0.017453294f);
        *(float *)(moby+0xF8)=FastAddRotations(*(float *)(moby+0xF8),math_random_int_range(-5,25)*0.017453294f);
        velocity=&vars->velocity;
        vec_scale_to_length(velocity,velocity,vars->speed);
        break;
    default:
        speed = 0.0f;
        return;
    }
    speed=vars->speed;
    frame.random.q=0;
    position=moby+0x10;
    frame.random.f[0]=math_random_float_range(-1.0f,1.0f);
    frame.random.f[1]=math_random_float_range(-1.0f,1.0f);
    frame.random.f[2]=math_random_float_range(-1.0f,1.0f);
    frame.direction.q=frame.random.q;
    vec_scale_to_length(&frame.direction,&frame.direction,math_random_float_range(0.1f,0.2f)*0.016666668f);
    vec_scale_to_length(&frame.pos,velocity,-math_random_float_range(0.0016666668f,0.016666668f));
    FastVecAdd(&frame.direction,&frame.direction,&frame.pos);
    vec_scale_to_length(&frame.pos,velocity,math_random_float_range(0.0f,1.0f)*speed);
    FastVecAdd(&frame.pos,&frame.pos,position);
    particle=part_spawn_burst(&frame.pos,&frame.direction,20,60,0x606060,3,80000.0f,40000.0f,1.0f,-0.0002f,0.0f);
    if (particle) {
        particle[2]=*g_particle_l06_byte_ptr;
        particle[3]=0x44;
        if (math_random_int_range(0,1)) {
            particle[3]=0x48;
            *(int *)(particle+4)=0x70707F;
            {char *payload=particle+0x20;
            payload[0x11]=0x70;
            payload[0x12]=0x70;
            payload[0x13]=0x70;
            *(short *)(payload+0x1E)=0x7F;}
        }
    }
    moby+=0x10;
    part_spawn_burst(moby,&frame.direction,7,127,0xB0B0B0,3,80000.0f,40000.0f,1.0f,-0.0004f,0.0f);
}
