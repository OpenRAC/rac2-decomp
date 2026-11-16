/* func_PAL_00303578, the PAL copy of func_00302470: the same C, where rename func_003022A0 becomes func_PAL_003033A8. */
#include "common.h"

typedef int ParticleWord __attribute__((mode(TI)));
typedef union { ParticleWord word; float f[4]; } ParticleVector;
extern float ref_00302470_03 SDATA(ref_00302470_03);
extern float ref_00302470_04 SDATA(ref_00302470_04);
extern float ref_00302470_05 SDATA(ref_00302470_05);
extern float ref_00302470_06 SDATA(ref_00302470_06);
extern float ref_00302470_07 SDATA(ref_00302470_07);
extern float ref_00302470_08 SDATA(ref_00302470_08);
extern float ref_00302470_09 SDATA(ref_00302470_09);
extern int ref_00302470_01 SDATA(ref_00302470_01);
extern ParticleVector ref_00302470_02 __attribute__((nosda));
extern int g_player_state_shorts[] MACRO_ADDR;
extern char *g_hero_moby __attribute__((nosda));
extern float fast_vec_dist(void *, void *);
extern char *CreateMoby(int);
extern void euler_rotation_basis(void *, void *);
extern void moby_set_light_color(void *, int);
extern void get_moby_color(void *, u32 *, u32 *, u32 *);
extern void gfx_pack_render_command_fields(unsigned long long *, unsigned long long,
    unsigned long long, unsigned long long, unsigned long long);
extern void set_moby_color(void *, u32, u32, u32);
extern int math_random_int_below(int);
extern float math_random_angle(void);
extern float math_random_float_range(float, float);
extern void FastVecSub(void *, void *, void *);
extern void FastVecCross(void *, void *, void *);
extern void vec_scale_to_length(void *, void *, float);
extern void math_build_axis_angle_quat(void *, int, float);
extern int pickup_start_fly_to_target_pal(char *, char *, float, float);
extern void func_002A0F48(void *);

typedef struct BoltVars {
    u8 pad00[0x20];
    ParticleVector velocity, spin;
    u8 kind;
    u8 pad41[0xF];
    float angle;
    u8 pad54;
    u8 flags;
    u8 pad56[2];
    float phase;
    u8 pad5c[0xC];
    float startZ;
} BoltVars;
typedef struct BoltClass { u8 pad00[0x24]; float scale; } BoltClass;
typedef struct BoltSpawnObject {
    u8 pad00[0x10];
    ParticleVector position;
    u8 state, pad21[3];
    BoltClass *objectClass;
    u8 pad28[4];
    float scale;
    u8 updateDistance, visible;
    short drawDistance;
    unsigned short flags;
    u8 pad36[0x2d];
    u8 life;
    u8 pad64[4];
    BoltVars *vars;
    u8 pad6c[0x4c];
    struct BoltSpawnObject *parent;
    u8 padbc[4];
    ParticleVector orientation[3];
    ParticleVector rotation;
} BoltSpawnObject;
/* Allocate the denomination near the camera and initialize its pickup motion. */
BoltSpawnObject *func_PAL_00303578(BoltSpawnObject *source, void *position, void *velocity, u32 flags, int value, int kind)
{
    BoltSpawnObject *object, *parent;
    BoltVars *state;
    ParticleVector *orientation;
    ParticleVector crossed, difference;
    u32 red, green, blue;
    float scale, spin, angle;
    if (fast_vec_dist(position,&ref_00302470_02)>=64.0f) {
        g_player_state_shorts[1]+=value;
        return 0;
    }
    switch (value) {
    default:
    case 1: object=(BoltSpawnObject *)CreateMoby(13); scale=ref_00302470_03; break;
    case 5: object=(BoltSpawnObject *)CreateMoby(14); scale=ref_00302470_04; break;
    case 20: object=(BoltSpawnObject *)CreateMoby(15); scale=ref_00302470_05; break;
    case 50: object=(BoltSpawnObject *)CreateMoby(16); scale=ref_00302470_06; break;
    case 100: object=(BoltSpawnObject *)CreateMoby(17); scale=ref_00302470_07; break;
    case 500: object=(BoltSpawnObject *)CreateMoby(18); scale=ref_00302470_08; break;
    case 1000: object=(BoltSpawnObject *)CreateMoby(19); scale=ref_00302470_09; break;
    }
    if (object) {
    state=object->vars;
    state->kind=(u8)kind;
    orientation=object->orientation;
    parent=source;
    if (parent) while (parent->parent) parent=parent->parent;
    object->parent=parent;
    object->life=0x14;
    object->flags|=0x100;
    object->updateDistance=0x40;
    object->drawDistance=0x40;
    object->visible=1;
    object->state=1;
    object->scale=object->objectClass->scale*scale;
    euler_rotation_basis(orientation,&object->rotation);
    moby_set_light_color(object,ref_00302470_01);
    get_moby_color(object,&red,&green,&blue);
    gfx_pack_render_command_fields((unsigned long long *)object,0,13,0,0);
    set_moby_color(object,red,green,blue);
    qcopy(&object->position,position);
    qcopy(&state->velocity,velocity);
    if (math_random_int_below(2)) state->flags|=1;
    state->angle=math_random_angle();
    state->phase=math_random_angle();
    state->startZ=object->position.f[2];
    spin=math_random_float_range(0.0f,720.0f)*0.0003490659f;
    FastVecSub(&difference,&source->position,&object->position);
    FastVecCross(&crossed,&state->velocity,&difference);
    vec_scale_to_length(&state->spin,&crossed,1.0f);
    math_build_axis_angle_quat(&state->spin,(int)(&state->spin),spin);
    if (flags&2) {
        angle=0.0f;
        if (flags&0x10) angle=math_random_float_range(-30.0f,30.0f)*0.017453294f;
        pickup_start_fly_to_target_pal((char *)object,g_hero_moby,angle,0.0f);
    }
    func_002A0F48(object);
    }
    return object;
}
