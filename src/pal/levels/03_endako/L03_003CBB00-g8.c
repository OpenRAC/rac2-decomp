#include "names.h"
/* func_PAL_L03_003CBB00, the PAL copy of func_L03_003C7AC0: the same C, where 1.0f / 60.0f becomes
   0.020000001f; 0.000277777785f becomes 0.00040000002f. */
#include "common.h"
typedef int TI128 __attribute__((mode(TI)));
extern float g_held_platform_turn_degrees __attribute__((sda)),g_held_platform_move_scale __attribute__((sda)),g_held_platform_other_move_scale __attribute__((sda)),g_held_platform_special_move_scale __attribute__((sda));
extern float g_held_platform_clamp_scale __attribute__((sda)),g_held_platform_other_clamp_scale __attribute__((sda)),g_held_platform_special_clamp_scale __attribute__((sda));
extern u8 g_held_platform_state_byte __attribute__((sda));
extern float g_hero_l03_aux_state NOT_SDA, g_collision_hit_height NOT_SDA;
typedef struct { float vec[4]; char pad[0x2d4]; int mode; } PlayerState;
extern PlayerState g_player_state;
typedef struct { char pad[0x74]; u8 active; char pad75[0x13]; char *owner; } L03ControlEntry;
extern u8 g_sound_state[];
extern float FastAddRotations(float,float);
extern void euler_rotation_basis(void *,void *);
extern float FastVecLength(void *);
extern int PlayMobySound(int,int,void *);
extern void snd_stop_voice(int);
extern void matrix_mul_vec3(void *,void *,void *);
extern void FastVecScale(void *,void *,float);
extern void vec_clear_128(void *);
extern void FastVecSub(void *,void *,void *);
extern void vec_clamp_length(void *,float);
extern void FastVecAdd(void *,void *,void *);
extern int path_push_point_away(int,void *,void *,float);
extern void moby_transform_joint_to_world(void *,int,void *);
extern int CollLine(void *,void *,int,void *,int);
extern void moby_update_ground_check(void *);
void held_platform_move_by_input_pal(char *obj)
{
    float a[4],b[4],c[4];
    union { float m[12]; struct { float pad[4], d[4]; } v; } scratch;
    char *state=*(char **)(obj+0x68);
    char *other;
    int id;
    if(*(u8 *)(obj+0x20)==2) {
        *(TI128 *)c=0;
        c[2]=FastAddRotations(g_hero_l03_aux_state,g_held_platform_turn_degrees*0.017453294f);
        *(TI128 *)(b)=*(TI128 *)(c);
        euler_rotation_basis(scratch.m,b);
        qcopy(a,g_player_state.vec);
        if(FastVecLength(a)>0.0f && g_player_state.mode==0x31) {
            L03ControlEntry *entry=(L03ControlEntry *)(g_sound_state+*(int *)(state+0x108)*0x70);
            if(entry->owner!=obj || !entry->active)
                *(int *)(state+0x108)=PlayMobySound(0,4,obj);
        } else {
            id=*(int *)(state+0x108);
            if(id!=-1) {
                L03ControlEntry *entry=(L03ControlEntry *)(g_sound_state+id*0x70);
                if(entry->owner==obj && entry->active) snd_stop_voice(id);
            }
            *(int *)(state+0x108)=-1;
        }
        a[0]=-a[0];
        matrix_mul_vec3(a,a,scratch.m);
        other=*(char **)(state+0xf0);
        if(other) {
            if(*(short *)(other+0xaa)==0xb85) FastVecScale(a,a,g_held_platform_special_move_scale*(0.020000001f));
            else FastVecScale(a,a,g_held_platform_other_move_scale*(0.020000001f));
        } else FastVecScale(a,a,g_held_platform_move_scale*(0.020000001f));
    } else {
        id=*(int *)(state+0x108);
        if(id!=-1) {
            L03ControlEntry *entry=(L03ControlEntry *)(g_sound_state+id*0x70);
            if(entry->owner==obj && entry->active) snd_stop_voice(id);
        }
        *(int *)(state+0x108)=-1;
        vec_clear_128(a);
    }
    FastVecSub(b,a,state+0xe0);
    b[2]=0;
    other=*(char **)(state+0xf0);
    if(other) {
        if(*(short *)(other+0xaa)==0xb85) vec_clamp_length(b,g_held_platform_special_clamp_scale*0.00040000002f);
        else vec_clamp_length(b,g_held_platform_other_clamp_scale*0.00040000002f);
    } else {
        vec_clamp_length(b,g_held_platform_clamp_scale*0.00040000002f);
    }
    FastVecAdd(state+0xe0,state+0xe0,b);
    FastVecAdd(obj+0x10,obj+0x10,state+0xe0);
    path_push_point_away(*(int *)state,obj+0x10,obj+0x10,1.25f);
    moby_transform_joint_to_world(obj,2,c);
    qcopy(scratch.m,c);
    scratch.m[2]+=20.0f;
    qcopy(scratch.v.d,c);
    scratch.v.d[2]+=0.5f;
    if(CollLine(scratch.v.d,scratch.m,2,obj,0)) *(float *)(state+0xf4)=g_collision_hit_height;
    moby_update_ground_check(obj);
    *(u8 *)(obj+0xbd)=g_held_platform_state_byte;
}
