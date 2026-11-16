#include "include_asm.h"

#include "common.h"
extern void anim_start_startup_animations(void);
extern s32 g_current_map_index MACRO_ADDR;
extern s32 math_random_int_below(s32);
extern void quaternion_to_rotation_basis(f32 *,f32 *);
extern void FastVecSub(u8 *,u8 *,u8 *);
extern void vec_scale_to_length(void *,void *,f32);
typedef struct SceneState {
    u8 pad00[0x30];
    s32 active, frame;
    u8 pad38[0xC];
    s16 count;
    u8 pad46[0x146];
    u8 *objects[0];
} SceneState;
extern SceneState g_scene_marker_state;
extern void UpdateEquipmentPieces(u8 *);
extern void math_store_angle_update_result(u8 *,void *,u32,u32,f32);
extern void vec_fast_to_int_helper(void *,void *);
extern void moby_compute_local_point(u8 *,void *,f32,f32,f32);
extern void func_L10_00425930(void *,s32,f32,s32,s32,s32,s32,s32,s32,s32,s32,s32);
extern f32 math_random_signed_float_range(f32,f32);
extern char *moby_spawn_shot_effect(u8 *,void *,void *,s32,s32,s32,s32,s32,f32);
extern u8 g_scene_spark_table[];

/*
 * func_PAL_L10_00318FF8, the PAL copy of func_L10_00317528: the same C at 50 Hz (frames 0x195, 0x187,
 * 0x79 and 0x327 become 0x151, 0x146, 0x65 and 0x2A1, the effect's rates grow by 6/5), and the 0xFA0
 * objects are skipped while D_001A79F0 is 0x33. `type` gives 0xFA0 a longer life in the loop, so loop.c
 * hoists it on its first pass, ahead of the object pointer's giv init, and leaves 0x33 for the second.
 */
void hrugis_update_scene_effects_pal(void) {
    f32 pos[4] __attribute__((aligned(16)));
    union { f32 matrix[12]; struct { f32 v[4]; f32 d[4]; } vectors; } scratch __attribute__((aligned(16)));
    u8 *target_obj, *state, *entry;
    s32 i;
    f32 sign;
    anim_start_startup_animations();
    for(i=0;i<g_scene_marker_state.count;i++) {
        u8 *object=g_scene_marker_state.objects[i];
        if(object && *(s16 *)(object+0xAA)==0xE29) *(u16 *)(object+0x34)|=0x800;
        if(*(s16 *)(object+0xAA)==0xD54) UpdateEquipmentPieces(object);
        if(object) {
            s32 type=MOBY_CLASS_TV_SCREENS;
            if(*(s16 *)(object+0xAA)==type && g_current_map_index!=0x33) {
                state=*(u8 **)(object+0x68);
                if(state) math_store_angle_update_result(object,state+0xC,0x80AAAAD2,0x80396464,0.07330384f);
            }
        }
    }
    if(g_current_map_index!=10 || g_scene_marker_state.active) return;
    target_obj=g_scene_marker_state.objects[2];
    if(g_scene_marker_state.frame==0x151) {
        vec_fast_to_int_helper(*(u8 **)(target_obj+0x58)+0x10,scratch.matrix);
        quaternion_to_rotation_basis(scratch.matrix,(f32 *)(target_obj+0xC0));
        moby_compute_local_point(target_obj,pos,4.0f,3.0f,5.0f);
        func_L10_00425930(pos,1,1.5f,25,20,20,20,45,1,1,1,0);
        moby_compute_local_point(target_obj,pos,9.0f,4.0f,4.0f);
        func_L10_00425930(pos,35,1.0f,50,30,30,30,50,1,1,1,1);
    }
    if(!((u32)(g_scene_marker_state.frame-0x146)<0x65 || g_scene_marker_state.frame>=0x2A1)) return;
    if(math_random_int_below(4)) return;
    sign=1.0f;
    if(math_random_int_below(2)) sign=-1.0f;
    entry=g_scene_spark_table+math_random_int_below(3)*32;
    moby_compute_local_point(target_obj,pos,*(f32 *)entry,*(f32 *)(entry+4),*(f32 *)(entry+8));
    moby_compute_local_point(target_obj,scratch.vectors.v,*(f32 *)(entry+0x10),*(f32 *)(entry+0x14),*(f32 *)(entry+0x18));
    scratch.vectors.v[0]+=math_random_signed_float_range(0.5f,1.5f);
    scratch.vectors.v[1]+=math_random_signed_float_range(0.5f,1.5f);
    scratch.vectors.v[2]+=math_random_signed_float_range(0.5f,1.5f);
    FastVecSub((u8 *)scratch.vectors.d,(u8 *)scratch.vectors.v,(u8 *)pos);
    vec_scale_to_length(scratch.vectors.d,scratch.vectors.d,1.4000001f);
    /* The two packed RGB colours become the effect's start/end colours. */
    moby_spawn_shot_effect(target_obj,pos,scratch.vectors.d,0x46BE20,0x327814,1,0,1,sign);
}
