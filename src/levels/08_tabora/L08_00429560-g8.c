#include "common.h"
typedef unsigned int Quadword __attribute__((mode(TI)));
extern s32 level_is_resident_flag_clear(void);
extern f32 D_L08_002603E0[3][4][4],D_L08_002604A0[6][20][4];
extern f32 D_L08_001B3A40[3][4] MACRO_ADDR;
extern s32 g_beam_slot_state[3] MACRO_ADDR,g_beam_slot_key[3] MACRO_ADDR,D_L08_001B3A10[3] MACRO_ADDR,D_L08_001B3A00[3] MACRO_ADDR;
extern s32 D_L08_001B39E0[3] MACRO_ADDR,D_L08_001B39F0[3] MACRO_ADDR;
extern f32 D_L08_001B39B0[3] MACRO_ADDR,D_L08_001B39C0[3] MACRO_ADDR,D_L08_001B39D0[3] MACRO_ADDR,D_L08_001B3A70[3][4] MACRO_ADDR;
extern f32 D_0018A0E0[];
extern f32 D_L08_001A8F20[] MACRO_ADDR;
typedef struct { char pad[0x1830]; char *owner; } BeamOwnerGlobals;
typedef struct { char pad[0x18]; char *owner; } BeamOwnerState;
extern BeamOwnerGlobals g_hero_state;
extern BeamOwnerState D_L08_001BFF40;
extern char D_L08_001C7C80[];
extern f32 D_L08_001B1D24 __attribute__((sda)),D_L08_001B1D20 __attribute__((sda));
extern void FastVecSub(void *,void *,void *),FastVecAdd(void *,void *,void *);
extern void FastVecCross(void *,void *,void *),transform_vector(void *,void *,void *);
extern void matrix_mul_vec3(void *,void *,void *),vec_scale_to_length(void *,void *,f32),FastVecScale(void *,void *,f32);
extern f32 FastVecLength(void *),FastAddRotations(f32,f32),fast_subtract_rotations(f32,f32),IntToFloat(s32);
extern f32 coll_probe_ground_height_below(void *,s32,f32),math_wrap_angle_to_pi(f32),math_fast_sin_or_cos_b(f32),math_fast_sin_or_cos_a(f32);
extern f32 math_random_float_range(f32,f32),math_random_signed_float_range(f32,f32);
extern s32 math_random_int_below(s32);
extern void part_spawn_random_direction_effect(void *,f32,f32);
extern char *part_spawn_short_lived(void *,void *,s32,s32);
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
void update_slot_panes_and_effects(s32 unused,s32 slot) {
    f32 delta[4],point[4],step[4],basis[4][4],enddelta[4],end[4],velocity[4],temp[4];
    s32 first,second,i,j,k,light;
    f32 spacing,previous,advance,height,half,angleStep,weight,wave,twist,sway,swayAmount,twistCos,randomValue,indexF,kF;
    char *effect,*data,*owner,*lightData,*lightData2;
    f32 (*stripRow)[4],(*strip2Row)[4];
    s32 index=slot;

    if(!level_is_resident_flag_clear()) return;
    first=index*2;
    second=first+1;
    FastVecSub(delta,D_L08_001B3A40[index],D_L08_002603E0[index][3]);
    spacing=FastVecLength(delta)*0.05f;
    if(g_beam_slot_state[index]==2){
        g_beam_slot_state[index]=3;
        for(j=0;j<20;j++){
            D_L08_002604A0[first][j][1]=D_L08_002604A0[first][j][2]=0;
            D_L08_002604A0[first][j][3]=1;
            D_L08_002604A0[first][j][0]=spacing*(f32)j;
            D_L08_002604A0[second][j][0]=D_L08_002604A0[first][j][0];
            D_L08_002604A0[second][j][1]=D_L08_002604A0[second][j][2]=0;
            D_L08_002604A0[second][j][3]=1;
        }
    }
    D_L08_001B39B0[index]=FastAddRotations(D_L08_001B39B0[index],0.17453295f);
    D_L08_001B39C0[index]=fast_subtract_rotations(D_L08_001B39C0[index],0.80285156f);
    D_L08_001B39D0[index]=FastAddRotations(D_L08_001B39D0[index],0.05236f);
    *(Quadword *)(point)=*(Quadword *)(D_L08_002603E0[index][3]);
    vec_scale_to_length(step,delta,spacing);
    previous=0;
    advance=0;
    angleStep=(360.0f/(IntToFloat(20)*0.5f))*0.017453294f;
    for(i=0;i<19;i++){
        half=(advance+spacing)*0.5f;
        height=0;
        if(i>0){
            height=coll_probe_ground_height_below(point,0,0.5f)+D_L08_001B1D24;
            owner=g_hero_state.owner;
            if(owner && D_L08_001BFF40.owner==owner) height=*(f32 *)(owner+0x18);
            height=point[2]-height;
            if(previous+half<height) height=previous+half;
            else if(height>0) height=(height+previous)*0.5f;
            advance=height-previous;
            previous=height;
        }
        FastVecAdd(point,point,step);
        indexF=(f32)i;
        weight=(IntToFloat(i)/IntToFloat(20))*0.3f+0.1f;
        wave=math_wrap_angle_to_pi(D_L08_001B39B0[index]+indexF*angleStep);
        weight=weight*math_fast_sin_or_cos_b(wave);
        stripRow=D_L08_002604A0[first];
        stripRow[i][1]=0;
        stripRow[i][3]=1;
        stripRow[i][0]=spacing*indexF;
        stripRow[i][2]=weight-height;
    }
    qcopy_nc(basis[3],D_L08_002603E0[index][3]);
    FastVecSub(enddelta,D_L08_001B3A40[index],basis[3]);
    vec_scale_to_length(basis[0],enddelta,1.0f);
    FastVecCross(basis[1],basis[0],D_0018A0E0);
    vec_scale_to_length(basis[1],basis[1],-1.0f);
    FastVecCross(basis[2],basis[1],basis[0]);
    transform_vector(end,D_L08_002604A0[first][18],basis);
    *(Quadword *)(D_L08_001B3A70[index])=*(Quadword *)(end);
    strip2Row=D_L08_002604A0[second];
    for(k=0;k<19;k++){
        kF=(f32)k;
        (*strip2Row)[2]=0;
        twist=math_wrap_angle_to_pi(D_L08_001B39C0[index]+kF*0.99483776f);
        sway=math_wrap_angle_to_pi(D_L08_001B39D0[index]+kF*0.20944f);
        swayAmount=math_fast_sin_or_cos_b(sway)*0.5f;
        twistCos=math_fast_sin_or_cos_b(twist);
        randomValue=math_random_signed_float_range(0,0.2f);
        (*strip2Row)[2]=D_L08_002604A0[first][k][2];
        (*strip2Row)[2]=(*strip2Row)[2]+swayAmount*twistCos+randomValue;
        (*strip2Row)[1]=math_fast_sin_or_cos_a(twist)*0.3f;
        (*strip2Row)[3]=1;
        (*strip2Row)[0]=spacing*kF;
        strip2Row++;
    }
    randomValue=math_random_float_range(0.03f,0.12f);
    *(Quadword *)velocity=0;
    velocity[0]=1;
    velocity[3]=1;
    velocity[1]=math_random_float_range(-1,1);
    velocity[2]=math_random_float_range(-1,1);
    vec_scale_to_length(velocity,velocity,randomValue);
    matrix_mul_vec3(velocity,velocity,D_L08_002603E0[index]);
    part_spawn_short_lived(D_L08_002603E0[index][3],velocity,127,g_beam_slot_key[index]);
    if(!math_random_int_below(3)){
        FastVecScale(temp,D_L08_002603E0[index],0.3f);
        FastVecAdd(temp,temp,D_L08_002603E0[index][3]);
        effect=part_spawn_short_lived(temp,D_L08_001A8F20,127,g_beam_slot_key[index]);
        if(effect){
            *(s16 *)(effect+10)=4;
            *(f32 *)(effect+12)=120000.0f;
            data=effect+32;
            *(f32 *)(data+16)=1.0f/IntToFloat(4);
            *(s32 *)(data+24)=0x7F7F7F;
            if(D_L08_001B3A10[index]==1) *(s16 *)(data+22)=1;
        }
    }
    math_random_float_range(0.01f,0.05f);
    part_spawn_random_direction_effect(velocity,0.01f,0.05f);
    part_spawn_short_lived(end,velocity,127,g_beam_slot_key[index]);
    if(!math_random_int_below(3)){
        effect=part_spawn_short_lived(end,D_L08_001A8F20,127,g_beam_slot_key[index]);
        if(effect){
            *(s16 *)(effect+10)=4;
            *(f32 *)(effect+12)=120000.0f;
            data=effect+32;
            *(f32 *)(data+16)=1.0f/IntToFloat(4);
            *(s32 *)(data+24)=0x7F7F7F;
            if(D_L08_001B3A10[index]==1) *(s16 *)(data+22)=2;
        }
    }
    if(D_L08_001B3A00[index]){
        if(D_L08_001B3A00[index]&1){
            *(Quadword *)(temp)=*(Quadword *)(D_L08_002603E0[index][3]);
            temp[2]-=0.25f;
            if(D_L08_001B39E0[index]==-1) D_L08_001B39E0[index]=part_l00_alloc_effect_slot_2(temp,D_L08_001B1D20,0,2,1,2);
            light=D_L08_001B39E0[index];
            if(light>=0){
                lightData=D_L08_001C7C80+light*32;
                *(Quadword *)(lightData+16)=*(Quadword *)(temp);
                *(f32 *)(lightData+28)=D_L08_001B1D20;
            }
        }
        if(D_L08_001B3A00[index]&2){
            end[2]+=0.5f;
            if(D_L08_001B39F0[index]==-1) D_L08_001B39F0[index]=part_l00_alloc_effect_slot_2(end,D_L08_001B1D20,0,2,1,2);
            light=D_L08_001B39F0[index];
            if(light>=0){
                lightData2=D_L08_001C7C80+light*32;
                *(Quadword *)(lightData2+16)=*(Quadword *)(end);
                *(f32 *)(lightData2+28)=D_L08_001B1D20;
            }
        }
    }
}
