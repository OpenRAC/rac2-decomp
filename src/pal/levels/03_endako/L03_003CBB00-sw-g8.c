#include "include_asm.h"

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
extern char *func_PAL_0032F3B8(char *,char *,char *,f32);
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
void func_PAL_L03_003CBE60(char *a0)
{
    char buf[0x10] __attribute__((aligned(16)));
    char direction[0x10] __attribute__((aligned(16)));
    char hit[0x10] __attribute__((aligned(16)));
    Actor7E20 *actor=(Actor7E20 *)a0;
    Private7E20 *p = actor->privateData;
    switch (actor->state) {
    case 0: {
        u16 id;
        p->drawFlags=actor->drawFlags;
        p->ground=actor->position[2];
        qcopy((char *)&p->home,(char *)actor->position);
        p->flags|=1;
        if (actor->type==0xB85) {
            id=(u16)actor->uid;
            if (D_L03_0021EA30.flags[(s16)id] ||
                ((D_0019B4A8[((s16)id>>1)+(g_current_map_index<<10)] >> ((id&1)?4:0))&7)) {
                qcopy((char *)actor->position,D_L03_001B2B0C[p->index].position);
            }
        }
        moby_set_state(a0,1,-1);
        break;
    }
    case 1: {
        u16 id;
        if (!(g_frame_l03_counter&7)) {
            if (coll_probe_ground_height_below((char *)actor->position,0,0.5f)+0.05f<=actor->position[2])
                moby_set_state(a0,3,-1);
        }
        if (actor->type==0xCFC) {
            char *v=part_find_owned_effect_slot(a0,0x10001,0);
            if (v) {
                moby_set_state(a0,4,-1);
                if (*(char **)(v+0x20) && *(s16 *)(*(char **)(v+0x20)+0xAA)==0xB85)
                    p->delay=1;
                else p->delay=8;
            }
            if (g_hero_state.object26C==a0 || g_hero_state.object33C==a0 ||
                g_hero_state.object270==a0 || g_hero_state.object588==a0)
                moby_set_state(a0,4,-1);
        } else if (p->pending && D_0018C0B4[0]!=0x31) {
            p->pending=0;
            if (IsPointInCuboid((char *)actor->position,p->index)) {
                qcopy((char *)actor->position,D_L03_001B2B0C[p->index].position);
                id=(u16)actor->uid;
                if (id&1) {
                    u8 *b=&D_0019B4A8[((s16)id>>1)+(g_current_map_index<<10)];
                    if (((*b>>4)&7)!=7) *b+=16;
                } else {
                    u8 *b=&D_0019B4A8[((s16)id>>1)+(g_current_map_index<<10)];
                    if ((*b&7)!=7) *b+=1;
                }
            } else path_push_point_away(p->effect,(char *)actor->position,(char *)actor->position,2.5f);
        }
        break;
    }
    case 2: {
        f32 length;
        f32 offset=2.3f;
        p->displacement[2]+=offset;
        length=FastVecLength((char *)&p->displacement);
        if (length!=0.0f) {
            math_approach_target_with_braking(&p->damping,length,0.00040000002f,0.00040000002f,0.020000001f);
            length-=p->damping;
            if (length<0.0f) length=0.0f;
            vec_scale_to_length((char *)&p->displacement,(char *)&p->displacement,length);
        }
        p->displacement[2]-=offset;
        moby_transform_joint_to_world(p->node,2,buf);
        FastVecAdd((char *)actor->position,buf,(char *)&p->displacement);
        break;
    }
    case 3: {
        p->velocity[2]-=0.012f;
        FastVecAdd((char *)actor->position,(char *)actor->position,(char *)&p->velocity);
        path_push_point_away(p->effect,(char *)actor->position,(char *)actor->position,1.25f);
        p->ground=coll_probe_ground_height_below((char *)actor->position,0,0.5f);
        if (actor->position[2]<=p->ground) {
            if (actor->type==0xCFC) {
                if (GetCollHitMaterial()==1) moby_set_state(a0,5,-1);
                else moby_set_state(a0,4,-1);
            } else moby_set_state(a0,1,-1);
            snd_play_from_class_bank(3,0,a0,0x94A);
            p->effectTimer=2;
            vec_clear_128((char *)&p->velocity);
            actor->position[2]=p->ground;
            p->pending=1;
        }
        moby_init_effect_track(a0);
        break;
    }
    case 4:
        if (flag_set_first_pending(a0) && !p->delay) p->delay=108;
        if (FastDecTimer((char *)&p->delay)) moby_set_state(a0,5,-1);
        if (p->delay%50<8) {
            snd_play_from_class_bank(0,0,a0,0xCFC);
            actor->drawFlags=0x800000C0;
        } else actor->drawFlags=p->drawFlags;
        break;
    case 5: {
        char *position=(char *)actor->position;
        qcopy(buf,position);
        *(f32 *)(buf+8)+=1.0f;
        snd_play_from_class_bank(1,0,a0,0xCFC);
        FastVecSub(direction,D_L03_001B9980,buf);
        vec_scale_to_length(direction,direction,1.0f);
        *(TI128 *)(hit)=0;
        *(f32 *)(hit+8)=1.0f;
        FastVecAdd(hit,hit,position);
        coll_sweep_from_object(a0,hit,0x10001,0,1,0,4.0f,4.0f,1.0f);
        func_PAL_0032F3B8(a0,buf,direction,0.0f);
        actor->collision=0;
        actor->flags=(actor->flags|0x41)&~0x1000;
        moby_set_state(a0,6,-1);
        break;
    }
    case 6:
        if (flag_set_first_pending(a0)) p->respawnDelay=50;
        if (FastDecTimer((char *)&p->respawnDelay)) {
            qcopy((char *)actor->position,(char *)&p->home);
            qcopy(buf,(char *)actor->position);
            *(f32 *)(buf+8)+=1.3f;
            if (!coll_test_point(buf,0,a0,1.2f) &&
                (*(f32 *)(buf+8)+=1.0f,!coll_test_point(buf,0,a0,1.2f))) {
                moby_set_state(a0,1,-1);
                actor->drawFlags=p->drawFlags;
                actor->flags=(actor->flags&~0x41)|0x1000;
                actor->collision=*(s32 *)(*(char **)(a0+0x24)+0x10);
                moby_fuse_linked_objects(a0,(char *)&p->home,(char *)actor->rotation,0,0);
                actor->alpha=255;
            } else p->respawnDelay=25;
        }
        break;
    }
    if (math_fast_float_d((char *)&p->effectTimer)==2) {
        D_L03_001B9840.f180=0.1f;
        D_L03_001B9840.i188=50;
        D_L03_001B9840.f160=0.1f;
        D_L03_001B9840.i168=25;
        D_L03_001B9840.i16C=0;
    }
}
