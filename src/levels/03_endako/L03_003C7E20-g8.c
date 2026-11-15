#include "common.h"

typedef int TI128 __attribute__((mode(TI)));

extern void moby_set_state(char *,s32,s32);
extern void FastVecSub(char *,char *,char *);
extern s32 g_current_map_index MACRO_ADDR;
extern unsigned char D_0019B4A8[];
extern struct { char pad[0x464]; u8 flags[1]; } D_L03_0021EA30;
typedef struct {
    char pad00[0x30]; f32 position[4]; char pad40[0x40];
} Node7E20;
extern Node7E20 *D_L03_001B2B0C MACRO_ADDR;
extern s32 g_frame_l03_counter MACRO_ADDR;
typedef struct {
    char pad[0x26C]; char *object26C; char *object270;
    char pad274[0xC8]; char *object33C;
    char pad340[0x248]; char *object588;
} HeroContacts7E20;
extern HeroContacts7E20 g_hero_state;
extern s32 D_0018C0B4[];
extern char D_L03_001B9980[];
typedef struct {
    char pad[0x160]; f32 f160; char pad164[4]; s32 i168, i16C;
    char pad170[0x10]; f32 f180; char pad184[4]; s32 i188;
} EffectState7E20;
extern EffectState7E20 D_L03_001B9840;
extern f32 coll_probe_ground_height_below(char *,s32,f32);
extern s32 IsPointInCuboid(char *,s32);
extern f32 FastVecLength(char *);
extern void math_approach_target_with_braking(f32 *,f32,f32,f32,f32);
extern void vec_scale_to_length(char *,char *,f32);
extern void moby_transform_joint_to_world(s32,s32,void *);
extern void FastVecAdd(char *,char *,char *);
extern int path_push_point_away(s32,char *,char *,f32);
extern s32 GetCollHitMaterial(void);
extern s32 snd_play_from_class_bank(s32,s32,char *,s32);
extern void vec_clear_128(char *);
extern void moby_init_effect_track(char *);
extern s32 flag_set_first_pending(char *);
extern s32 FastDecTimer(void *);
extern int coll_sweep_from_object(char *,char *,s32,s32,s32,s32,f32,f32,f32);
extern char *part_spawn_blast_effect_moby(char *,char *,char *,f32);
extern s32 coll_test_point(char *,s32,char *,f32);
extern s32 moby_fuse_linked_objects(char *,char *,char *,s32,s32);
extern s32 math_fast_float_d(void *);
extern char *part_find_owned_effect_slot(char *,s32,s32);

typedef struct {
    char pad[0x5C]; s32 flags, effect, index; char pad68[8];
    f32 home[4], velocity[4], displacement[4];
    s32 node, unknownA4; f32 ground, damping; s32 pending, drawFlags;
    s16 delay, respawnDelay; s32 effectTimer;
} Private7E20;

typedef struct {
    char pad00[0x10]; f32 position[4]; u8 state; char pad21[3];
    char *classData; char pad28[0xC]; u16 flags; char pad36[0x32];
    Private7E20 *privateData; char pad6C[0xC]; s32 drawFlags;
    char pad7C[0x1C]; s32 collision; char pad9C[0xC];
    u8 alpha; char padA9; s16 type; char padAC[6]; s16 uid;
    char padB4[0x3C]; f32 rotation[4];
} Actor7E20;

/* Every state, and an out-of-range one, ends at the private block's effect timer, which keeps
   the private pointer live across the whole switch.
   &p->displacement and &p->velocity are written out each time: gcse keeps the first computation
   in a saved register. */
/* Per-frame update of moby class 2380 (Explosive Crate) and the two classes that share its code (2949 and 3324): they sit, get knocked up, fall, flash, then blow up and respawn. */
void explosive_crate_update(char *moby)
{
    char temp_pos[0x10] __attribute__((aligned(16)));
    char direction[0x10] __attribute__((aligned(16)));
    char hit[0x10] __attribute__((aligned(16)));
    Actor7E20 *actor=(Actor7E20 *)moby;
    Private7E20 *vars = actor->privateData;
    switch (actor->state) {
    case 0: {
        u16 id;
        vars->drawFlags=actor->drawFlags;
        vars->ground=actor->position[2];
        qcopy((char *)&vars->home,(char *)actor->position);
        vars->flags|=1;
        if (actor->type==0xB85 /* moby class 2949 */) {
            id=(u16)actor->uid;
            if (D_L03_0021EA30.flags[(s16)id] ||
                ((D_0019B4A8[((s16)id>>1)+(g_current_map_index<<10)] >> ((id&1)?4:0))&7)) {
                qcopy((char *)actor->position,D_L03_001B2B0C[vars->index].position);
            }
        }
        moby_set_state(moby,1,-1);
        break;
    }
    case 1: {
        u16 id;
        if (!(g_frame_l03_counter&7)) {
            if (coll_probe_ground_height_below((char *)actor->position,0,0.5f)+0.05f<=actor->position[2])
                moby_set_state(moby,3,-1);
        }
        if (actor->type==0xCFC /* moby class 3324 */) {
            char *hit_moby=part_find_owned_effect_slot(moby,0x10001,0);
            if (hit_moby) {
                moby_set_state(moby,4,-1);
                if (*(char **)(hit_moby+0x20) && *(s16 *)(*(char **)(hit_moby+0x20)+0xAA)==0xB85)
                    vars->delay=1;
                else vars->delay=10;
            }
            if (g_hero_state.object26C==moby || g_hero_state.object33C==moby ||
                g_hero_state.object270==moby || g_hero_state.object588==moby)
                moby_set_state(moby,4,-1);
        } else if (vars->pending && D_0018C0B4[0]!=0x31) {
            vars->pending=0;
            if (IsPointInCuboid((char *)actor->position,vars->index)) {
                qcopy((char *)actor->position,D_L03_001B2B0C[vars->index].position);
                id=(u16)actor->uid;
                if (id&1) {
                    u8 *packed_byte=&D_0019B4A8[((s16)id>>1)+(g_current_map_index<<10)];
                    if (((*packed_byte>>4)&7)!=7) *packed_byte+=16;
                } else {
                    u8 *packed_byte=&D_0019B4A8[((s16)id>>1)+(g_current_map_index<<10)];
                    if ((*packed_byte&7)!=7) *packed_byte+=1;
                }
            } else path_push_point_away(vars->effect,(char *)actor->position,(char *)actor->position,2.5f);
        }
        break;
    }
    case 2: {
        f32 pull_length;
        f32 offset=2.3f;
        vars->displacement[2]+=offset;
        pull_length=FastVecLength((char *)&vars->displacement);
        if (pull_length!=0.0f) {
            math_approach_target_with_braking(&vars->damping,pull_length,0.00027777778f,0.00027777778f,0.016666668f);
            pull_length-=vars->damping;
            if (pull_length<0.0f) pull_length=0.0f;
            vec_scale_to_length((char *)&vars->displacement,(char *)&vars->displacement,pull_length);
        }
        vars->displacement[2]-=offset;
        moby_transform_joint_to_world(vars->node,2,temp_pos);
        FastVecAdd((char *)actor->position,temp_pos,(char *)&vars->displacement);
        break;
    }
    case 3: {
        vars->velocity[2]-=0.008333334f;
        FastVecAdd((char *)actor->position,(char *)actor->position,(char *)&vars->velocity);
        path_push_point_away(vars->effect,(char *)actor->position,(char *)actor->position,1.25f);
        vars->ground=coll_probe_ground_height_below((char *)actor->position,0,0.5f);
        if (actor->position[2]<=vars->ground) {
            if (actor->type==0xCFC /* moby class 3324 */) {
                if (GetCollHitMaterial()==1) moby_set_state(moby,5,-1);
                else moby_set_state(moby,4,-1);
            } else moby_set_state(moby,1,-1);
            snd_play_from_class_bank(3,0,moby,0x94A);
            vars->effectTimer=2;
            vec_clear_128((char *)&vars->velocity);
            actor->position[2]=vars->ground;
            vars->pending=1;
        }
        moby_init_effect_track(moby);
        break;
    }
    case 4:
        if (flag_set_first_pending(moby) && !vars->delay) vars->delay=130;
        if (FastDecTimer((char *)&vars->delay)) moby_set_state(moby,5,-1);
        if (vars->delay%60<10) {
            snd_play_from_class_bank(0,0,moby,0xCFC);
            actor->drawFlags=0x800000C0;
        } else actor->drawFlags=vars->drawFlags;
        break;
    case 5: {
        char *position=(char *)actor->position;
        qcopy(temp_pos,position);
        *(f32 *)(temp_pos+8)+=1.0f;
        snd_play_from_class_bank(1,0,moby,0xCFC);
        FastVecSub(direction,D_L03_001B9980,temp_pos);
        vec_scale_to_length(direction,direction,1.0f);
        *(TI128 *)(hit)=0;
        *(f32 *)(hit+8)=1.0f;
        FastVecAdd(hit,hit,position);
        coll_sweep_from_object(moby,hit,0x10001,0,1,0,4.0f,4.0f,1.0f);
        part_spawn_blast_effect_moby(moby,temp_pos,direction,0.0f);
        actor->collision=0;
        actor->flags=(actor->flags|0x41)&~0x1000;
        moby_set_state(moby,6,-1);
        break;
    }
    case 6:
        if (flag_set_first_pending(moby)) vars->respawnDelay=60;
        if (FastDecTimer((char *)&vars->respawnDelay)) {
            qcopy((char *)actor->position,(char *)&vars->home);
            qcopy(temp_pos,(char *)actor->position);
            *(f32 *)(temp_pos+8)+=1.3f;
            if (!coll_test_point(temp_pos,0,moby,1.2f) &&
                (*(f32 *)(temp_pos+8)+=1.0f,!coll_test_point(temp_pos,0,moby,1.2f))) {
                moby_set_state(moby,1,-1);
                actor->drawFlags=vars->drawFlags;
                actor->flags=(actor->flags&~0x41)|0x1000;
                actor->collision=*(s32 *)(*(char **)(moby+0x24)+0x10);
                moby_fuse_linked_objects(moby,(char *)&vars->home,(char *)actor->rotation,0,0);
                actor->alpha=255;
            } else vars->respawnDelay=30;
        }
        break;
    }
    if (math_fast_float_d((char *)&vars->effectTimer)==2) {
        D_L03_001B9840.f180=0.1f;
        D_L03_001B9840.i188=60;
        D_L03_001B9840.f160=0.1f;
        D_L03_001B9840.i168=30;
        D_L03_001B9840.i16C=0;
    }
}
