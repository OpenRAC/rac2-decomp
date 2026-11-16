#include "common.h"

typedef unsigned int CarrierQuad __attribute__((mode(TI)));
typedef union { CarrierQuad q; float f[4]; } CarrierVector;
typedef struct {
    float bobPhase, bobOffset, swayPhase, tiltPhase;
    int platform, passenger, destination, timer, path, flags;
    float riseTime, fallTime, rise;
    int motionState, motionTimer;
    float baseZ, minRise, maxRise, minWait, maxWait, spin;
    int sound, source, stopped, idleSound;
} CarrierVars;
typedef struct { int count; int pad[3]; CarrierVector points[1]; } CarrierPath;
typedef struct CarrierMoby {
    char pad0[0x10]; CarrierVector position;
    unsigned char state; char pad21[0x47]; CarrierVars *vars;
    char pad6c[0xC]; int color; char pad7c[0x2E];
    short classId; char padac[6]; short uid; char padb4[8];
    unsigned char hit; char padbd[3]; char matrix[0x30]; float rotation[4];
} CarrierMoby;
typedef struct { char bytes[0x70]; } CarrierSoundRecord;
typedef struct { char pad0[0x74]; unsigned char active; char pad75[0x13]; CarrierMoby *owner; } CarrierVoice;
extern CarrierSoundRecord g_sound_state[];
extern CarrierMoby *g_moby_l17_pool MACRO_ADDR;
extern int g_flash_frame_counter[] __attribute__((sda));
extern CarrierPath *g_path_l17_table[];
extern char g_str_carrier_debug_a[] NOT_SDA, g_str_carrier_debug_b[] NOT_SDA;
/* A fixed scalar: storing it does not alias the struct loads scheduled after it. */
extern int g_carrier_moby_state MACRO_ADDR;
extern int g_carrier_platform_state __attribute__((sda));
extern float g_carrier_bob_period __attribute__((sda));
extern float g_carrier_bob_default __attribute__((sda));
extern float g_carrier_bob_no_platform __attribute__((sda));
extern float g_carrier_sway_amplitude __attribute__((sda));
extern float g_carrier_sway_period __attribute__((sda));
extern float g_carrier_tilt_period __attribute__((sda));
extern float g_carrier_hit_seconds __attribute__((sda));
extern float g_carrier_wait_seconds __attribute__((sda));
extern float g_carrier_move_seconds __attribute__((sda));
extern float g_carrier_height_offset_a __attribute__((sda));
extern float g_carrier_snap_distance __attribute__((sda));
extern float g_carrier_height_offset_b __attribute__((sda));
extern float g_carrier_height_offset_c __attribute__((sda));
extern float g_carrier_z_step_a __attribute__((sda));
extern float g_carrier_z_step_b __attribute__((sda));
extern void moby_set_state(void *, int, int);
extern float math_random_float_range(float, float), IntToFloat(int), math_fast_sin_or_cos_a(float), math_fast_sin_or_cos_b(float);
extern int math_random_int_below(int), math_random_int_range(int, int), FloatToInt(float), math_fast_float_d(int *);
extern void moby_mark_spawned(void *), math_update_wrapped_angle_offset(void *,void *,void *,float,float,float);
extern void moby_scale_owner_words_by_angles(void *,void *,void *,float,float,float);
extern float FastAddRotations(float,float), fast_vec_dist(void *,void *), vec_distance_xy(void *,void *), mat_fast_helper_a(float,float);
extern void matrix_mul_vec3(void *,void *,void *), FastVecAdd(void *,void *,void *), add_vectors(void *,void *,void *);
extern void snd_stop_voice(int);
extern int PlayMobySound(int,int,void *), flag_set_first_pending(void *), platform_is_waiting(void *);
extern void DrawIndexedRibbonSegments(void *);
extern int snd_play_from_class_bank(int,int,void *,int);
extern void gfx_add_draw_callback_first(void *,void *), STUB_printf(void *), vec_build_spherical_offset(void *,float,float,float);

/* -ffast-math: combine folds K - (-x) to K + x with K first, retail's add.s order. It would also
   re-associate a literal 0.5f factor, so that value is held in a local. */
void UpdateCarrierPlatform(CarrierMoby *moby)
{
    CarrierVector offset, target, rotation, result;
    CarrierVector *rotationPtr;
    CarrierVars *vars = moby->vars;
    CarrierMoby *platform, *destination, *passenger;
    CarrierVars *destinationVars;
    float bob, ratio, wave, half, distance, blend, angle, pitch;
    float heightDelta, randomSpin, travelDistance;
    int color, lo, hi, ready, flash;
    if (vars->platform == -1) bob = g_carrier_bob_no_platform;
    else bob = g_carrier_bob_default;
    flash = (g_flash_frame_counter[0] + moby->uid) % 60 < 15;
    color = flash ? 0x80FFFFFF : 0x80404040;
    moby->color = color;
    if (moby->state == 0) {
        vars->idleSound = -1;
        if (vars->source != -1) {
            qcopy_nc(&moby->position,&g_moby_l17_pool[vars->source].position);
            moby->position.f[2] += g_carrier_z_step_a;
            qcopy_nc(&g_moby_l17_pool[vars->platform].position,&g_moby_l17_pool[vars->source].position);
            g_moby_l17_pool[vars->platform].position.f[2] += g_carrier_z_step_b;
            moby_set_state(moby,1,-1);
            return;
        }
        if (vars->destination != -1 && vars->path != -1) {
            CarrierPath *path = g_path_l17_table[vars->path];
            moby->position.f[2] = path->points[path->count-1].f[2] + g_carrier_height_offset_a + g_carrier_height_offset_b + 10.0f;
        }
        if (vars->platform != -1)
            g_moby_l17_pool[vars->platform].position.f[2] = moby->position.f[2] - g_carrier_height_offset_c - g_carrier_height_offset_a;
        vars->baseZ = moby->position.f[2];
        randomSpin = math_random_float_range(0.004363324f,0.013089972f);
        if (math_random_int_below(2)) randomSpin = -randomSpin;
        vars->spin = randomSpin;
        moby_set_state(moby,1,-1);
    }
    if (vars->source != -1) {
        gfx_add_draw_callback_first(DrawIndexedRibbonSegments,moby);
        qcopy_nc(&moby->position,&g_moby_l17_pool[vars->source].position);
        moby->position.f[2] += g_carrier_z_step_a;
        qcopy_nc(&g_moby_l17_pool[vars->platform].position,&g_moby_l17_pool[vars->source].position);
        g_moby_l17_pool[vars->platform].position.f[2] += g_carrier_z_step_b;
        return;
    }
    if (vars->platform == -1) {
        switch (vars->motionState) {
        case 0:
            vars->baseZ = moby->position.f[2];
            vars->rise = math_random_float_range(vars->minRise,vars->maxRise);
            if (math_random_int_below(2)) { moby->position.f[2] += vars->rise; vars->motionState=3; }
            else vars->motionState=1;
            lo=FloatToInt(vars->minWait*60.0f); hi=FloatToInt(vars->maxWait*60.0f);
            vars->motionTimer=math_random_int_range(lo,hi);
            vars->motionTimer=math_random_int_range(0,vars->motionTimer);
            break;
        case 1:
            if (math_fast_float_d(&vars->motionTimer)) { vars->motionTimer=FloatToInt(vars->riseTime*60.0f); vars->motionState=2; }
            moby->position.f[2]=vars->baseZ; break;
        case 2:
            if (math_fast_float_d(&vars->motionTimer)) {
                moby->position.f[2]=vars->baseZ+vars->rise; vars->motionState=3;
                lo=FloatToInt(vars->minWait*60.0f); hi=FloatToInt(vars->maxWait*60.0f);
                vars->motionTimer=math_random_int_range(lo,hi);
            } else {
                ratio=IntToFloat(vars->motionTimer)/(vars->riseTime*60.0f);
                wave=math_fast_sin_or_cos_a(ratio*3.141593f);
                half=0.5f;
                moby->position.f[2]=vars->baseZ+vars->rise*(wave*half)+vars->rise*half;
            } break;
        case 3:
            if (math_fast_float_d(&vars->motionTimer)) { vars->motionTimer=FloatToInt(vars->fallTime*60.0f); vars->motionState=4; }
            moby->position.f[2]=vars->baseZ+vars->rise; break;
        case 4:
            if (math_fast_float_d(&vars->motionTimer)) {
                moby->position.f[2]=vars->baseZ; vars->motionState=1;
                lo=FloatToInt(vars->minWait*60.0f); hi=FloatToInt(vars->maxWait*60.0f);
                vars->motionTimer=math_random_int_range(lo,hi);
            } else {
                ratio=IntToFloat(vars->motionTimer)/(vars->fallTime*60.0f);
                wave=math_fast_sin_or_cos_a((1.0f-ratio)*3.141593f);
                half=0.5f;
                moby->position.f[2]=vars->baseZ+vars->rise*(wave*half)+vars->rise*half;
            } break;
        }
    } else moby->position.f[2]=vars->baseZ;
    math_update_wrapped_angle_offset(moby,&vars->bobPhase,&vars->bobOffset,bob,360.0f/g_carrier_bob_period*0.00029088825f,moby->position.f[2]);
    moby_scale_owner_words_by_angles(moby,&vars->swayPhase,&vars->tiltPhase,g_carrier_sway_amplitude,360.0f/g_carrier_sway_period*0.00029088825f,360.0f/g_carrier_tilt_period*0.00029088825f);
    moby->rotation[2]=FastAddRotations(moby->rotation[2],vars->spin);
    qzero(&offset); offset.f[2]=g_carrier_height_offset_c;
    matrix_mul_vec3(&offset,&offset,moby->matrix);
    add_vectors(&target,&offset,&moby->position);
    if (((CarrierVoice *)&g_sound_state[vars->idleSound])->owner != moby || !((CarrierVoice *)&g_sound_state[vars->idleSound])->active)
        vars->idleSound=PlayMobySound(2,4,moby);
    if (vars->platform == -1 || g_moby_l17_pool[vars->platform].classId != 0x93B) return;
    gfx_add_draw_callback_first(DrawIndexedRibbonSegments,moby);
    if (vars->passenger == -1 || vars->path == -1 || vars->destination == -1) return;
    destination=&g_moby_l17_pool[vars->destination]; destinationVars=destination->vars;
    platform=&g_moby_l17_pool[vars->platform]; passenger=&g_moby_l17_pool[vars->passenger];
    target.q=destination->position.q;
    target.f[2]+=g_carrier_height_offset_b;
    bob=offset.f[2]-g_carrier_height_offset_a;
    heightDelta=bob-target.f[2];
    platform->position.q=offset.q; platform->position.f[2]=bob;
    switch (moby->state) {
    case 1:
        if (vars->sound != -1 && ((CarrierVoice *)&g_sound_state[vars->sound])->owner==moby && ((CarrierVoice *)&g_sound_state[vars->sound])->active) snd_stop_voice(vars->sound);
        vars->sound=-1;
        if (passenger->hit) { moby_set_state(moby,2,-1); vars->timer=FloatToInt(g_carrier_hit_seconds*60.0f); }
        platform->position.f[2]=bob; vars->stopped=0; break;
    case 2:
        ratio=IntToFloat(vars->timer)/(g_carrier_hit_seconds*60.0f);
        platform->position.f[2]=bob-heightDelta*math_fast_sin_or_cos_b((1.0f-ratio)*1.5707965f);
        if (((CarrierVoice *)&g_sound_state[vars->sound])->owner!=moby || !((CarrierVoice *)&g_sound_state[vars->sound])->active) vars->sound=PlayMobySound(0,4,moby);
        STUB_printf(g_str_carrier_debug_a); vars->stopped=0;
        if (math_fast_float_d(&vars->timer)) { moby_set_state(moby,3,-1); vars->timer=FloatToInt(g_carrier_wait_seconds*60.0f); }
        break;
    case 3:
        if (flag_set_first_pending(moby)) PlayMobySound(0,0,platform);
        platform->position.f[2]=bob-heightDelta; ready=0;
        if (platform_is_waiting(destination)) {
            if (vars->sound != -1 && ((CarrierVoice *)&g_sound_state[vars->sound])->owner==moby && ((CarrierVoice *)&g_sound_state[vars->sound])->active) snd_stop_voice(vars->sound);
            vars->sound=-1;
        } else if (((CarrierVoice *)&g_sound_state[vars->sound])->owner!=moby || !((CarrierVoice *)&g_sound_state[vars->sound])->active) vars->sound=PlayMobySound(1,4,moby);
        if (vars->destination && destination->classId==0x935 && destinationVars) {
            if ((*(int *)((char *)destinationVars+0xAC)==2 || *(int *)((char *)destinationVars+0xA0)==-1) && *(int *)((char *)destinationVars+0xBC)!=3) {
                ready=1; platform->position.q=target.q; vars->timer=0;
            } else if (*(int *)((char *)destinationVars+0xAC)==1 && fast_vec_dist(&platform->position,&target)<1.0f) { vars->timer=0; ready=1; }
        }
        if (!ready && math_fast_float_d(&vars->timer)) {
            if (vars->sound != -1 && ((CarrierVoice *)&g_sound_state[vars->sound])->owner==moby && ((CarrierVoice *)&g_sound_state[vars->sound])->active) snd_stop_voice(vars->sound);
            vars->sound=-1; moby_set_state(moby,4,-1); snd_play_from_class_bank(1,0,moby,0x93B); vars->timer=FloatToInt(g_carrier_move_seconds*60.0f);
        } break;
    case 4:
        ratio=IntToFloat(vars->timer)/(g_carrier_move_seconds*60.0f);
        platform->position.f[2]=bob-heightDelta*math_fast_sin_or_cos_b(ratio*1.5707965f);
        passenger->hit=0;
        if (((CarrierVoice *)&g_sound_state[vars->sound])->owner!=moby || !((CarrierVoice *)&g_sound_state[vars->sound])->active) vars->sound=PlayMobySound(1,4,moby);
        STUB_printf(g_str_carrier_debug_b);
        if (math_fast_float_d(&vars->timer)) moby_set_state(moby,1,-1);
        break;
    }
    distance=fast_vec_dist(&target,&platform->position);
    if (distance<g_carrier_snap_distance && distance>0.01f) {
        blend=1.0f-distance/g_carrier_snap_distance;
        travelDistance=offset.f[2]-platform->position.f[2];
        angle=vec_distance_xy(&offset,&target);
        pitch=-mat_fast_helper_a(angle,target.f[2]-offset.f[2]);
        pitch=1.5707965f-(1.5707965f-pitch)*blend;
        rotationPtr=&rotation;
        angle=mat_fast_helper_a(target.f[0]-offset.f[0],target.f[1]-offset.f[1]);
        pitch=-pitch;
        vec_build_spherical_offset(rotationPtr,travelDistance,angle,pitch);
        FastVecAdd(&result,&offset,rotationPtr);
        platform->position.q=result.q;
        platform->rotation[1]=FastAddRotations(pitch,1.5707965f);
        moby->rotation[1]=FastAddRotations(moby->rotation[1],platform->rotation[1]);
        g_carrier_moby_state=moby->state; g_carrier_platform_state=platform->state;
        if (vars->sound != -1 && ((CarrierVoice *)&g_sound_state[vars->sound])->owner==moby && ((CarrierVoice *)&g_sound_state[vars->sound])->active) snd_stop_voice(vars->sound);
        vars->sound=-1;
    }
}
