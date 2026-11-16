#include "names.h"
/* func_PAL_L08_0042ECD0, the PAL copy of func_L08_00429560: the same C, where rename func_L08_0034A078 becomes func_PAL_L08_0034C4A8. */
#include "common.h"
typedef unsigned int Quadword __attribute__((mode(TI)));
extern s32 level_is_resident_flag_clear(void);
extern f32 g_slot_pane_matrices[3][4][4],g_slot_pane_points[6][20][4];
extern f32 g_beam_targets[3][4] MACRO_ADDR;
extern s32 g_beam_slot_state[3] MACRO_ADDR,g_beam_slot_key[3] MACRO_ADDR,g_beam_modes[3] MACRO_ADDR,g_beam_light_masks[3] MACRO_ADDR;
extern s32 g_beam_start_light_ids[3] MACRO_ADDR,g_beam_end_light_ids[3] MACRO_ADDR;
extern f32 g_beam_wave_angles[3] MACRO_ADDR,g_beam_twist_angles[3] MACRO_ADDR,g_beam_sway_angles[3] MACRO_ADDR,g_beam_end_positions[3][4] MACRO_ADDR;
extern f32 g_hero_state_block[];
extern f32 g_str_effect_name[] MACRO_ADDR;
typedef struct { char pad[0x1830]; char *owner; } BeamOwnerGlobals;
typedef struct { char pad[0x18]; char *owner; } BeamOwnerState;
extern BeamOwnerGlobals g_hero_state;
extern BeamOwnerState g_collision_l08_result;
extern char g_effect_l08_light_table[];
extern f32 g_ground_probe_height_offset __attribute__((sda)),g_beam_light_radius __attribute__((sda));
extern void FastVecSub(void *,void *,void *),FastVecAdd(void *,void *,void *);
extern void FastVecCross(void *,void *,void *),transform_vector(void *,void *,void *);
extern void matrix_mul_vec3(void *,void *,void *),vec_scale_to_length(void *,void *,f32),FastVecScale(void *,void *,f32);
extern f32 FastVecLength(void *),FastAddRotations(f32,f32),fast_subtract_rotations(f32,f32),IntToFloat(s32);
extern f32 coll_probe_ground_height_below(void *,s32,f32),math_wrap_angle_to_pi(f32),math_fast_sin_or_cos_b(f32),math_fast_sin_or_cos_a(f32);
extern f32 math_random_float_range(f32,f32),math_random_signed_float_range(f32,f32);
extern s32 math_random_int_below(s32);
extern void part_spawn_random_direction_effect(void *,f32,f32);
extern char *func_PAL_L08_0034C4A8(void *,void *,s32,s32);
extern s32 part_l00_alloc_effect_slot_2(void *,f32,f32,f32,f32,f32);
/* Per-frame update of one beam slot: lays out the two 20-point strips between the slot's ends
   (a sine wave and a noisy one on top of it), spawns sparks at both ends and keeps the two
   lights at the ends.  RAC1's counterpart is update_slot_panes_and_effects.

   The wording carries the allocation:
   - index is the last top-level local: PRE sorts (index<<k) after the stack addresses only when
     its pseudo number is at least 114, which puts &end before index*16 and index*64 in the
     spill slots.
   - first and second are set before the first call: sched1 lets them drift past it.
   - In loop 1 a row pointer indexed by i gives one combined giv, and loop.c emits its %hi/%lo
     after gcse, so the base stays a local pair instead of the PRE register.
   - In loop 2 the row element is stored and then updated: that store lasts until flow2 and
     makes the 50 insns that keep 1.0 in the loop while 0.3 is hoisted. */
void update_slot_panes_and_effects_pal(s32 unused,s32 slot) {
    f32 delta[4],point[4],step[4],basis[4][4],enddelta[4],end[4],velocity[4],temp[4];
    s32 first,second,i,j,k,light;
    f32 spacing,previous,advance,height,half,angleStep,weight,wave,twist,sway,b,c,r,t,tn;
    char *effect,*data,*owner,*s,*s2;
    f32 (*p)[4],(*q)[4];
    s32 index=slot;

    if(!level_is_resident_flag_clear()) return;
    first=index*2;
    second=first+1;
    FastVecSub(delta,g_beam_targets[index],g_slot_pane_matrices[index][3]);
    spacing=FastVecLength(delta)*0.05f;
    if(g_beam_slot_state[index]==2){
        g_beam_slot_state[index]=3;
        for(j=0;j<20;j++){
            g_slot_pane_points[first][j][1]=g_slot_pane_points[first][j][2]=0;
            g_slot_pane_points[first][j][3]=1;
            g_slot_pane_points[first][j][0]=spacing*(f32)j;
            g_slot_pane_points[second][j][0]=g_slot_pane_points[first][j][0];
            g_slot_pane_points[second][j][1]=g_slot_pane_points[second][j][2]=0;
            g_slot_pane_points[second][j][3]=1;
        }
    }
    g_beam_wave_angles[index]=FastAddRotations(g_beam_wave_angles[index],0.17453295f);
    g_beam_twist_angles[index]=fast_subtract_rotations(g_beam_twist_angles[index],0.80285156f);
    g_beam_sway_angles[index]=FastAddRotations(g_beam_sway_angles[index],0.05236f);
    *(Quadword *)(point)=*(Quadword *)(g_slot_pane_matrices[index][3]);
    vec_scale_to_length(step,delta,spacing);
    previous=0;
    advance=0;
    angleStep=(360.0f/(IntToFloat(20)*0.5f))*0.017453294f;
    for(i=0;i<19;i++){
        half=(advance+spacing)*0.5f;
        height=0;
        if(i>0){
            height=coll_probe_ground_height_below(point,0,0.5f)+g_ground_probe_height_offset;
            owner=g_hero_state.owner;
            if(owner && g_collision_l08_result.owner==owner) height=*(f32 *)(owner+0x18);
            height=point[2]-height;
            if(previous+half<height) height=previous+half;
            else if(height>0) height=(height+previous)*0.5f;
            advance=height-previous;
            previous=height;
        }
        FastVecAdd(point,point,step);
        t=(f32)i;
        weight=(IntToFloat(i)/IntToFloat(20))*0.3f+0.1f;
        wave=math_wrap_angle_to_pi(g_beam_wave_angles[index]+t*angleStep);
        weight=weight*math_fast_sin_or_cos_b(wave);
        p=g_slot_pane_points[first];
        p[i][1]=0;
        p[i][3]=1;
        p[i][0]=spacing*t;
        p[i][2]=weight-height;
    }
    qcopy_nc(basis[3],g_slot_pane_matrices[index][3]);
    FastVecSub(enddelta,g_beam_targets[index],basis[3]);
    vec_scale_to_length(basis[0],enddelta,1.0f);
    FastVecCross(basis[1],basis[0],g_hero_state_block);
    vec_scale_to_length(basis[1],basis[1],-1.0f);
    FastVecCross(basis[2],basis[1],basis[0]);
    transform_vector(end,g_slot_pane_points[first][18],basis);
    *(Quadword *)(g_beam_end_positions[index])=*(Quadword *)(end);
    q=g_slot_pane_points[second];
    for(k=0;k<19;k++){
        tn=(f32)k;
        (*q)[2]=0;
        twist=math_wrap_angle_to_pi(g_beam_twist_angles[index]+tn*0.99483776f);
        sway=math_wrap_angle_to_pi(g_beam_sway_angles[index]+tn*0.20944f);
        b=math_fast_sin_or_cos_b(sway)*0.5f;
        c=math_fast_sin_or_cos_b(twist);
        r=math_random_signed_float_range(0,0.2f);
        (*q)[2]=g_slot_pane_points[first][k][2];
        (*q)[2]=(*q)[2]+b*c+r;
        (*q)[1]=math_fast_sin_or_cos_a(twist)*0.3f;
        (*q)[3]=1;
        (*q)[0]=spacing*tn;
        q++;
    }
    r=math_random_float_range(0.03f,0.12f);
    *(Quadword *)velocity=0;
    velocity[0]=1;
    velocity[3]=1;
    velocity[1]=math_random_float_range(-1,1);
    velocity[2]=math_random_float_range(-1,1);
    vec_scale_to_length(velocity,velocity,r);
    matrix_mul_vec3(velocity,velocity,g_slot_pane_matrices[index]);
    func_PAL_L08_0034C4A8(g_slot_pane_matrices[index][3],velocity,127,g_beam_slot_key[index]);
    if(!math_random_int_below(3)){
        FastVecScale(temp,g_slot_pane_matrices[index],0.3f);
        FastVecAdd(temp,temp,g_slot_pane_matrices[index][3]);
        effect=func_PAL_L08_0034C4A8(temp,g_str_effect_name,127,g_beam_slot_key[index]);
        if(effect){
            *(s16 *)(effect+10)=3;
            *(f32 *)(effect+12)=120000.0f;
            data=effect+32;
            *(f32 *)(data+16)=1.0f/IntToFloat(3);
            *(s32 *)(data+24)=0x7F7F7F;
            if(g_beam_modes[index]==1) *(s16 *)(data+22)=1;
        }
    }
    math_random_float_range(0.01f,0.05f);
    part_spawn_random_direction_effect(velocity,0.01f,0.05f);
    func_PAL_L08_0034C4A8(end,velocity,127,g_beam_slot_key[index]);
    if(!math_random_int_below(3)){
        effect=func_PAL_L08_0034C4A8(end,g_str_effect_name,127,g_beam_slot_key[index]);
        if(effect){
            *(s16 *)(effect+10)=3;
            *(f32 *)(effect+12)=120000.0f;
            data=effect+32;
            *(f32 *)(data+16)=1.0f/IntToFloat(3);
            *(s32 *)(data+24)=0x7F7F7F;
            if(g_beam_modes[index]==1) *(s16 *)(data+22)=2;
        }
    }
    if(g_beam_light_masks[index]){
        if(g_beam_light_masks[index]&1){
            *(Quadword *)(temp)=*(Quadword *)(g_slot_pane_matrices[index][3]);
            temp[2]-=0.25f;
            if(g_beam_start_light_ids[index]==-1) g_beam_start_light_ids[index]=part_l00_alloc_effect_slot_2(temp,g_beam_light_radius,0,2,1,2);
            light=g_beam_start_light_ids[index];
            if(light>=0){
                s=g_effect_l08_light_table+light*32;
                *(Quadword *)(s+16)=*(Quadword *)(temp);
                *(f32 *)(s+28)=g_beam_light_radius;
            }
        }
        if(g_beam_light_masks[index]&2){
            end[2]+=0.5f;
            if(g_beam_end_light_ids[index]==-1) g_beam_end_light_ids[index]=part_l00_alloc_effect_slot_2(end,g_beam_light_radius,0,2,1,2);
            light=g_beam_end_light_ids[index];
            if(light>=0){
                s2=g_effect_l08_light_table+light*32;
                *(Quadword *)(s2+16)=*(Quadword *)(end);
                *(f32 *)(s2+28)=g_beam_light_radius;
            }
        }
    }
}
