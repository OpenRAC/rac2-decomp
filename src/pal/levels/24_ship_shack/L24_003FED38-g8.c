#include "common.h"

/* The three effect tables are small-data pointers; this unit requires -G8. */
typedef int EffectVectorBits __attribute__((mode(TI)));
typedef union { int i[0x980]; float f[0x980]; unsigned char b[0x2600]; char *p[0x980]; } EffectHeroState;
typedef struct { char pad[0x70]; float value; char rest[0x6c]; } EffectClassEntry;
typedef struct { char pad[0x74]; unsigned char active; char gap[0x13]; char *owner; } EffectSoundSlot;
typedef struct { char pad[0x30]; int active; char rest[12]; } EffectParticleSlot;
typedef struct { char pad[0x514]; int active; char rest[24]; } EffectLargeSlot;
typedef struct { char pad[0x38]; int handle; int rest; } EffectHandleSlot;
extern EffectHeroState g_hero_state;
extern int g_pad_state[];
extern unsigned char g_item_slot_to_record[];
extern EffectClassEntry g_weapon_l00_table[];
extern EffectSoundSlot g_sound_state[];
extern char *g_lava_gun_particle_slots __attribute__((sda));
extern char *g_lava_gun_ring_entries __attribute__((sda));
extern char *g_lava_gun_beam_slots __attribute__((sda));
extern char *g_area_hit_targets[];
extern int g_hero_locked_flag;
extern int g_game_l00_mode;
extern char ref_L00_00419C98_00[];
extern void table_clear_entry_flag(int);
extern int AcquireEntitySlot(char *, int, int *);
extern char *level_get_slot_body(int, int);
extern unsigned char *mem_align_up_sixteen_alt(int);
extern void snd_stop_voice(int);
extern void moby_transform_joint_to_world(char *, int, char *);
extern void anim_start_blended_with_flags(char *, int, int, int, int);
extern int math_fast_float_d(int *);
extern int get_ammo(int);
extern float math_spring_float_to_goal(float *, float *, float, float, float, float);
extern int weapon_spend_ammo(int, int);
extern int snd_is_voice_playing_for_owner(char *, int);
extern int PlayMobySound(int, int, char *);
extern void anim_start_blended(char *, int, int, int);
extern int coll_process_hit(float, char *, int, char *, int);
extern void FastVecSub(void *, void *, void *);
extern void vec_scale_to_length(void *, void *, float);
extern void make_hit_descriptor(void *, char *, int, void *, float);
extern void QueueMobyImpact(char *, void *);
extern int StartAttachedEffect(char *, int, char *);
extern s32 hero_l00_set_action(int, int);
extern void vec_clear_128(void *);
extern void matrix_mul_vec3(void *, void *, void *);
extern void vec_compute_object_to_target(char *, char *, void *, float);
extern void FastVecScale(void *, void *, float);
extern void FastVecAdd(void *, void *, void *);
extern void math_apply_axis_rotation_to_quat(void *, void *, void *, float);
extern void AppendVectorRingEntry(char *, char *, void *, int);
extern void lava_gun_update_blobs(char *);
extern void lava_gun_update_ring_entries(char *);
extern void part_l00_update_effect_slots_2(char *);
extern void ref_L00_00419C98_01(void *, char *);

/* func_PAL_L24_003FED38, the PAL copy of func_L00_00419C98: the same C, where the two
   40-frame counts take the 50 Hz scale and the six func_002AA3A8 rates are multiplied by 6/5. */

/* Initializes the effect tables on first update, processes nearby targets while active,
   and advances the emission vector and scrolling phases. */
void lava_l24_gun_update_pal(char *moby)
{
    float emit_vec[4];
    union { EffectVectorBits word; float v[4]; } direction;
    struct { union { EffectVectorBits word; float position[4]; } u; char pad[8]; unsigned char a,b; short id; int pad3c; int flags; } packet;
    int slot_out, i = 0, hit_count, enabled;
    char *vars = *(char **)(moby+0x68);
    char **hit_target;
    if (g_hero_state.i[0x1244/4]==3 && g_lava_gun_ring_entries) {
        for (;i<35;i++) { char *ring_entry=g_lava_gun_ring_entries+i*64; if (*(int *)(ring_entry+0x38)>=0) { table_clear_entry_flag(*(int *)(ring_entry+0x38)); *(int *)(ring_entry+0x38)=-1; } }
    }
    if (!((unsigned char *)moby)[0x20]) {
        *(int *)(vars+0x34)=AcquireEntitySlot(moby,0,&slot_out);
        g_lava_gun_beam_slots=level_get_slot_body(*(short *)(moby+0xaa),*(int *)(vars+0x34));
        g_lava_gun_particle_slots=(char *)mem_align_up_sixteen_alt((int)g_lava_gun_beam_slots+0x33e0);
        g_lava_gun_ring_entries=(char *)mem_align_up_sixteen_alt((int)g_lava_gun_particle_slots+0x1f40);
        for (i=124;i>=0;i--) ((EffectParticleSlot *)g_lava_gun_particle_slots)[i].active=1;
        for (i=9;i>=0;i--) ((EffectLargeSlot *)g_lava_gun_beam_slots)[i].active=0;
        { int invalid=-1; for (i=34;i>=0;i--) ((EffectHandleSlot *)g_lava_gun_ring_entries)[i].handle=invalid; }
        *(int *)(vars+0x3c)=0; *(int *)(vars+0x48)=0; *(int *)(vars+0x40)=0; *(int *)(vars+0x44)=0;
        *(int *)(vars+0x54)=0; *(int *)(vars+0x50)=0; *(int *)(vars+0x58)=0; *(int *)(vars+0x5c)=0;
        *(int *)(vars+0x60)=0; *(int *)(vars+0x64)=0; ((unsigned char *)moby)[0x20]=1; *(int *)(vars+0x38)=-1;
    }
    if (g_hero_state.i[0x1244/4]==3) {
        { int handle=*(int *)(vars+0x38);
        if (handle!=-1 && ((EffectSoundSlot *)((char *)g_sound_state+handle*0x70))->owner==moby && ((EffectSoundSlot *)((char *)g_sound_state+handle*0x70))->active) snd_stop_voice(handle); }
        *(int *)(vars+0x38)=-1;
        return;
    }
    moby_transform_joint_to_world(moby,0,vars);
    if (((unsigned char *)moby)[0x42]==((unsigned char *)moby)[0x43] && (((unsigned char *)moby)[0x60]&2)) anim_start_blended_with_flags(moby,1,0,2,0);
    enabled=1;
    if (g_hero_state.i[0x2294/4]==29) { if (!math_fast_float_d(&g_hero_state.i[0x2534/4])) enabled=0; }
    else g_hero_state.i[0x2534/4]=((s32)(40) * 5 + 2) / 6;
    if ((g_pad_state[0x1a0/4]&g_hero_state.i[0x1230/4]) && enabled && get_ammo(-1) && !g_hero_state.b[0x22bc]) {
        math_spring_float_to_goal((float *)(vars+0x50),(float *)(vars+0x54),10.0f,0.009000001f,0.0024f,12.0f);
        { int divisor=10; if (*(int *)(vars+0x60)%divisor==0) weapon_spend_ammo(-1,1); }
        ++*(int *)(vars+0x60);
        if (!snd_is_voice_playing_for_owner(moby,*(int *)(vars+0x38))) *(int *)(vars+0x38)=PlayMobySound(0,4,moby);
        if (((unsigned char *)moby)[0x43]!=2) anim_start_blended(moby,2,0,0);
        hit_count=coll_process_hit(0.5f,vars,16,moby,0);
        if (hit_count>0) { int targets_left; hit_target=g_area_hit_targets; targets_left=hit_count; do {
            if (*hit_target!=g_hero_state.p[0x2290/4]) {
            FastVecSub(&direction,*hit_target+0x10,moby+0x10);
            vec_scale_to_length(&direction,&direction,1.0f);
            vec_scale_to_length(&packet,&packet,1.0f);
            make_hit_descriptor(&packet,moby,0x910000,&direction,((EffectClassEntry *)((unsigned int)g_weapon_l00_table+g_item_slot_to_record[29]*0xe0))->value);
            packet.u.word=direction.word; packet.u.position[3]=5627.925f;
            packet.flags=1; packet.a=9; packet.b=1; packet.id=*(short *)(*hit_target+0xaa);
            QueueMobyImpact(*hit_target,&packet);
            StartAttachedEffect(*hit_target,29,moby); PlayMobySound(1,0,moby);
            }
            hit_target++;
        } while (--targets_left); }
    } else {
        { int handle=*(int *)(vars+0x38);
        if (handle!=-1 && ((EffectSoundSlot *)((char *)g_sound_state+handle*0x70))->owner==moby && ((EffectSoundSlot *)((char *)g_sound_state+handle*0x70))->active) snd_stop_voice(handle); }
        *(int *)(vars+0x38)=-1;
        if ((g_pad_state[0x1a4/4]&g_hero_state.i[0x1230/4]) && !get_ammo(-1) && !g_hero_state.b[0x22bc]) PlayMobySound(2,0,moby);
        math_spring_float_to_goal((float *)(vars+0x50),(float *)(vars+0x54),0,0.072000004f,0.012f,0.15f);
        *(int *)(vars+0x60)=0;
    }
    if (g_hero_state.i[0x2294/4]==1) hero_l00_set_action(29,1);
    moby_transform_joint_to_world(moby,0,vars);
    vec_clear_128(emit_vec); emit_vec[1]=-1;
    matrix_mul_vec3(emit_vec,emit_vec,moby+0xc0);
    emit_vec[2]+=0.02f;
    vec_scale_to_length(emit_vec,emit_vec,*(float *)(vars+0x50)*0.05f);
    if (g_hero_state.p[0x1450/4]) {
        g_hero_state.p[0xbf8/4]=g_hero_state.p[0x1450/4];
        vec_compute_object_to_target(g_hero_state.p[0x1450/4],vars,emit_vec,*(float *)(vars+0x50)*0.05f);
        if (g_hero_locked_flag) { FastVecScale(&direction,moby+0xe0,0.02f); FastVecAdd(emit_vec,emit_vec,&direction); }
        else emit_vec[2]+=0.02f;
    }
    qcopy(vars+0x10,vars);
    if (g_hero_state.i[0x2294/4]) math_apply_axis_rotation_to_quat(emit_vec,emit_vec,g_hero_state.p[0x2290/4]+0xd0,-0.09817477f);
    if (*(float *)(vars+0x50)!=0) AppendVectorRingEntry(moby,vars,emit_vec,((s32)(40) * 5 + 2) / 6);
    *(float *)(vars+0x58)-=0.1f; if (*(float *)(vars+0x58)<=-8) *(float *)(vars+0x58)+=8;
    *(float *)(vars+0x5c)-=0.025f; if (*(float *)(vars+0x5c)<=-8) *(float *)(vars+0x5c)+=8;
    if (*(float *)(vars+0x50)!=0) { lava_gun_update_blobs(moby); lava_gun_update_ring_entries(moby); }
    else { *(int *)(vars+0x44)=0; *(int *)(vars+0x3c)=0; *(int *)(vars+0x48)=0; *(int *)(vars+0x40)=0; }
    part_l00_update_effect_slots_2(moby);
    if (g_game_l00_mode!=2 && ((unsigned char *)moby)[0x31]) ref_L00_00419C98_01(ref_L00_00419C98_00,moby);
}
