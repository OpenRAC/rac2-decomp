#include "names.h"
/* func_PAL_L06_00404FE8, the PAL copy of func_L06_004012B0: the same C, where rename func_0032DA58 becomes func_PAL_0032F3B8; rename func_002B0A68 becomes func_PAL_002B15D8; rename func_002C16C0 becomes func_PAL_002C23B8; scale func_002A7820(20,10); scale func_002A7820(0,10). */
/*
 * func_PAL_L06_00404FE8: four-state update of an effect object. State 3 leaves the switch and emits its
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
extern char *part_spawn_blast_effect_moby_pal(char *, void *, void *, float);
extern int coll_sweep_from_object(char *, float, void *, int, float, float, int, int, int);
extern void part_spawn_masked_debris_pal(char *, int, float, void *, float, float, float, unsigned char);
extern void moby_mark_spawned(char *);
extern float math_step_value_toward_target(void *, float, void *, float, float, float);
extern char *part_spawn_burst_pal(void *, void *, int, int, int, int, float, float, float, float, float);
typedef struct { char pad[0x140]; Vec position; char gap[0x10]; float scale; int unused; int duration, timer; char gap2[0x10]; float speed; int unused2, limit; } Effect;
extern Effect g_camera_state;

extern unsigned char *g_particle_l06_byte_ptr;
typedef struct { int timer; float speed, height; int handle; Vec velocity; } UpdateState;
void hit_reaction_burst_update_pal(char *obj) {
    struct { Vec pos, direction, random; } frame;
    UpdateState *state = *(UpdateState **)(obj+0x68);
    char *hit, *particle;
    float speed;
    char *position;
    Vec *velocity;

    switch ((unsigned char)obj[0x20]) {
    case 0:
        qcopy(&frame.pos,obj+0x10);
        frame.pos.f[2] += 10.0f;
        FastVecAdd(&state->velocity,obj+0x10,&frame.pos);
        state->handle=-1;
        obj[0x20]=1;
        return;
    case 1:
        hit=part_find_owned_effect_slot(obj,0x10000,0);
        if (hit) {
          if (*(short *)(*(char **)(hit+0x20)+0xAA)!=0x8B8) {
            if (math_random_int_below(3)==1) {
                state->timer=(((int)(math_random_int_range(20,10)) * 5 + 2) / 6);
                state->height=*(float *)(obj+0x18)+20.0f;
                obj[0x20]=3;
            } else {
                state->timer=(((int)(math_random_int_range(0,10)) * 5 + 2) / 6);
                obj[0x20]=2;
            }

          }
        }
        *(unsigned char *)(obj+0xA8)=255;
        return;
    case 2:
        if (math_fast_float_d(state)) {
            float unit = 1.0f;
            PlayMobySound(0,0,obj);
            frame.random.q=0;
            frame.random.f[2]=0.060000002f;
            FastVecSub(&frame.direction,&g_camera_state.position,&frame.pos);
            vec_scale_to_length(&frame.direction,&frame.direction,unit);
            part_spawn_blast_effect_moby_pal(obj,obj+0x10,&frame.direction,5.0f);
            g_camera_state.speed=0.1f;
            g_camera_state.limit=75;
            g_camera_state.scale=0.2f;
            g_camera_state.duration=50;
            g_camera_state.timer=0;
            coll_sweep_from_object(obj,3.0f,obj+0x10,0x10000,3.0f,1.0f,0,1,0);
            part_spawn_masked_debris_pal(obj,0xEF,3.0f,&frame.random,6.0f,3.0f,6.0f,255);
            moby_mark_spawned(obj);
        }
        return;
    case 3:
        if (math_fast_float_d(state)) {obj[0x20]=2; return;}
        math_step_value_toward_target(obj+0x18,state->height,&state->speed,0.040000003f,0.040000003f,0.40000004f);
        *(float *)(obj+0xF0)=FastAddRotations(*(float *)(obj+0xF0),math_random_int_range(-10,10)*0.017453294f);
        *(float *)(obj+0xF4)=FastAddRotations(*(float *)(obj+0xF4),math_random_int_range(-10,10)*0.017453294f);
        *(float *)(obj+0xF8)=FastAddRotations(*(float *)(obj+0xF8),math_random_int_range(-5,25)*0.017453294f);
        velocity=&state->velocity;
        vec_scale_to_length(velocity,velocity,state->speed);
        break;
    default:
        speed = 0.0f;
        return;
    }
    speed=state->speed;
    frame.random.q=0;
    position=obj+0x10;
    frame.random.f[0]=math_random_float_range(-1.0f,1.0f);
    frame.random.f[1]=math_random_float_range(-1.0f,1.0f);
    frame.random.f[2]=math_random_float_range(-1.0f,1.0f);
    frame.direction.q=frame.random.q;
    vec_scale_to_length(&frame.direction,&frame.direction,math_random_float_range(0.1f,0.2f)*0.020000001f);
    vec_scale_to_length(&frame.pos,velocity,-math_random_float_range(0.002f,0.020000001f));
    FastVecAdd(&frame.direction,&frame.direction,&frame.pos);
    vec_scale_to_length(&frame.pos,velocity,math_random_float_range(0.0f,1.0f)*speed);
    FastVecAdd(&frame.pos,&frame.pos,position);
    particle=part_spawn_burst_pal(&frame.pos,&frame.direction,17,60,0x606060,3,80000.0f,40000.0f,1.0f,-0.0002f,0.0f);
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
    obj+=0x10;
    part_spawn_burst_pal(obj,&frame.direction,6,127,0xB0B0B0,3,80000.0f,40000.0f,1.0f,-0.0004f,0.0f);
}
