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

/* Per-frame effects for the level 10 story scene: marks some objects as always drawn,
   and in the boss scene sets off explosions and random sparks on the boss. */
void hrugis_update_scene_effects(void) {
    f32 pos[4] __attribute__((aligned(16)));
    union { f32 matrix[12]; struct { f32 v[4]; f32 d[4]; } vectors; } scratch __attribute__((aligned(16)));
    u8 *boss, *state, *spark;
    s32 i;
    f32 side;
    anim_start_startup_animations();
    for(i=0;i<g_scene_marker_state.count;i++) {
        u8 *object=g_scene_marker_state.objects[i];
        if(object && *(s16 *)(object+0xAA)==0xE29 /* moby class 3625 */) *(u16 *)(object+0x34)|=0x800;
        if(*(s16 *)(object+0xAA)==0xD54 /* moby class 3412 */) UpdateEquipmentPieces(object);
        if(object && *(s16 *)(object+0xAA)==MOBY_CLASS_TV_SCREENS) {
            state=*(u8 **)(object+0x68);
            if(state) math_store_angle_update_result(object,state+0xC,0x80AAAAD2,0x80396464,0.061086535f);
        }
    }
    if(g_current_map_index!=10 || g_scene_marker_state.active) return;
    boss=g_scene_marker_state.objects[2];
    if(g_scene_marker_state.frame==0x195) {
        vec_fast_to_int_helper(*(u8 **)(boss+0x58)+0x10,scratch.matrix);
        quaternion_to_rotation_basis(scratch.matrix,(f32 *)(boss+0xC0));
        moby_compute_local_point(boss,pos,4.0f,3.0f,5.0f);
        func_L10_00425930(pos,1,1.5f,25,20,20,20,45,1,1,1,0);
        moby_compute_local_point(boss,pos,9.0f,4.0f,4.0f);
        func_L10_00425930(pos,35,1.0f,50,30,30,30,50,1,1,1,1);
    }
    if(!((u32)(g_scene_marker_state.frame-0x187)<0x79 || g_scene_marker_state.frame>=0x327)) return;
    if(math_random_int_below(4)) return;
    side=1.0f;
    if(math_random_int_below(2)) side=-1.0f;
    spark=g_scene_spark_table+math_random_int_below(3)*32;
    moby_compute_local_point(boss,pos,*(f32 *)spark,*(f32 *)(spark+4),*(f32 *)(spark+8));
    moby_compute_local_point(boss,scratch.vectors.v,*(f32 *)(spark+0x10),*(f32 *)(spark+0x14),*(f32 *)(spark+0x18));
    scratch.vectors.v[0]+=math_random_signed_float_range(0.5f,1.5f);
    scratch.vectors.v[1]+=math_random_signed_float_range(0.5f,1.5f);
    scratch.vectors.v[2]+=math_random_signed_float_range(0.5f,1.5f);
    FastVecSub((u8 *)scratch.vectors.d,(u8 *)scratch.vectors.v,(u8 *)pos);
    vec_scale_to_length(scratch.vectors.d,scratch.vectors.d,1.16666675f);
    /* The two packed RGB colours become the effect's start/end colours. */
    moby_spawn_shot_effect(boss,pos,scratch.vectors.d,0x46BE20,0x327814,1,0,1,side);
}
