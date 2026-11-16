#include "include_asm.h"

#include "common.h"
extern void moby_transform_joint_to_world(void *, s32, void *);
extern s32 coll_sweep_from_object(void *, void *, f32, s32, f32, f32, s32, s32, s32);
extern void vec_random_direction(void *, f32, f32);
extern f32 IntToFloat(s32);
extern void FastVecSub(void *, void *, void *);
extern void FastVecAdd(void *, void *, void *);
extern void vec_scale_to_length(void *, void *, f32);
extern void make_hit_descriptor(void *, void *, s32, void *, f32);
extern s32 CollLine(void *, void *, s32, void *, void *);
extern s32 joba_beam_pick_target_point(void *, void *, void *);
extern void func_PAL_L11_003F8E90(void *, s32);
extern void UpdateTwinRecordAnglesAndPositions(void *);
extern void snd_stop_voice(s32);
extern u8 g_sound_state[];
extern u8 *g_active_attacker_robot NOT_SDA;
extern s32 g_arena_progress_level;
typedef struct { u8 pad[0x18]; u8 *hit; u8 pad1c[4]; f32 point[4]; } PathHit;
extern PathHit g_collision_l11_result;
extern s32 g_joba_beam_repeat_count __attribute__((sda));
extern s32 g_joba_beam_phase_frames_a __attribute__((sda));
extern s32 g_joba_beam_phase_frames_b __attribute__((sda));
extern s32 g_joba_beam_hit_frames __attribute__((sda));
extern s32 g_joba_beam_phase_frames_c __attribute__((sda));
extern f32 g_joba_beam_dir_min_angle_a __attribute__((sda));
extern f32 g_joba_beam_dir_max_angle_a __attribute__((sda));
extern f32 g_joba_beam_dir_min_angle_b __attribute__((sda));
extern f32 g_joba_beam_dir_max_angle_b __attribute__((sda));
extern f32 g_joba_beam_dir_min_c __attribute__((sda));
extern f32 g_joba_beam_dir_max_c __attribute__((sda));
extern f32 g_joba_beam_dir_min_b __attribute__((sda));
extern f32 g_joba_beam_dir_max_b __attribute__((sda));
#define F(p,o) (*(f32 *)((u8 *)(p)+(o)))
#define H(p,o) (*(s16 *)((u8 *)(p)+(o)))
#define U(p,o) (*(u16 *)((u8 *)(p)+(o)))
#define P(p,o) (*(u8 **)((u8 *)(p)+(o)))
typedef struct { f32 x,y,z,w; } Vec4 __attribute__((aligned(16)));
typedef struct { Vec4 pos; Vec4 end; u8 pad20[0x80]; } PathRec;
typedef struct { u8 pad[0xA0]; PathRec path[2]; u8 pad1e0[0x10]; Vec4 target[2]; Vec4 origin[2]; Vec4 last[2]; u8 pad250[0x10]; f32 scale[2]; u8 *hit[2]; u8 pad270[4]; s16 timer[2]; u16 state[2]; s16 repeat[2]; u8 pad280[0x10]; s32 sound; } PathState;

void func_PAL_L11_003F7778(u8 *object) {
    f32 starts[2][4] __attribute__((aligned(16)));
    f32 delta[4] __attribute__((aligned(16)));
    struct { u8 pad[0x18]; u8 kind, flags; u16 id; u8 tail[0x14]; } query __attribute__((aligned(16)));
    u8 *data = P(object,0x68);
    s32 i;
    f32 t;
    moby_transform_joint_to_world(object,1,starts[0]);
    moby_transform_joint_to_world(object,0,starts[1]);
    for (i=0;i<2;i++) {
        ((PathState *)data)->scale[i]=0;
        switch ((s16)(((PathState *)data)->state[i]-1)) {
        case 0:
            qcopy(data+0xA0+i*0xA0,starts[i]);
            qcopy(data+0xB0+i*0xA0,starts[i^1]);
            break;
        case 1:
            qcopy(data+0xA0+i*0xA0,starts[i]);
            qcopy(data+0xB0+i*0xA0,starts[i^1]);
            coll_sweep_from_object(object,starts[0],0.2f,0x10001,data[0x34],1.0f,0,1,0);
            coll_sweep_from_object(object,starts[1],0.2f,0x10001,data[0x34],1.0f,0,1,0);
            if (((PathState *)data)->timer[i]>g_joba_beam_phase_frames_a) {
                u8 *path=data+0xA0+i*0xA0;
                vec_random_direction(path+0x60,g_joba_beam_dir_min_angle_b*0.0003490659f,g_joba_beam_dir_max_angle_b*0.0003490659f);
                vec_random_direction(path+0x70,g_joba_beam_dir_min_angle_b*0.0003490659f,g_joba_beam_dir_max_angle_b*0.0003490659f);
                vec_random_direction(path+0x80,g_joba_beam_dir_min_c,g_joba_beam_dir_max_c);
                vec_random_direction(path+0x90,g_joba_beam_dir_min_c,g_joba_beam_dir_max_c);
                ((PathState *)data)->timer[i]=0;
                ((PathState *)data)->state[i]=3;
                ((PathState *)data)->repeat[i]=0;
                qcopy(data+0x210+i*16,starts[i]);
                qcopy(data+0xA0+i*0xA0,data+0x210+i*16);
                if (joba_beam_pick_target_point(object,data+0x210+i*16,data+0x1F0+i*16))
                    ((PathState *)data)->repeat[i]=g_joba_beam_repeat_count;
            } else {
                t=IntToFloat(((PathState *)data)->timer[i]);
                t/=IntToFloat(g_joba_beam_phase_frames_a);
                ((PathState *)data)->scale[i]=t;
            }
            break;
        case 2:
            coll_sweep_from_object(object,starts[i],0.2f,0x10001,data[0x34],1.0f,0,1,0);
            if (((PathState *)data)->timer[i]<=((s32)(g_joba_beam_phase_frames_b) * 5 + 2) / 6) {
                u8 *path;
                s32 off;
                t=IntToFloat(((PathState *)data)->timer[i]);
                t/=IntToFloat(((s32)(g_joba_beam_phase_frames_b) * 5 + 2) / 6);
                off=i*0xA0;
                path=data+0xA0+off;
                F(data+off,0xB0)=((PathState *)data)->origin[i].x+(((PathState *)data)->target[i].x-((PathState *)data)->origin[i].x)*t;
                F(data+off,0xB4)=((PathState *)data)->origin[i].y+(((PathState *)data)->target[i].y-((PathState *)data)->origin[i].y)*t;
                F(data+off,0xB8)=((PathState *)data)->origin[i].z+(((PathState *)data)->target[i].z-((PathState *)data)->origin[i].z)*t;
                FastVecSub(delta,path+0x10,path);
                vec_scale_to_length(delta,delta,0.040000003f);
                make_hit_descriptor(&query,object,0x210001,delta,data[0x34]);
                query.kind=5;
                query.flags=3;
                query.id=U(object,0xAA);
                if (CollLine(path,path+0x10,0,object,&query)) {
                    u8 *hit=g_collision_l11_result.hit;
                    if (hit && H(hit,0xAA)!=0xC7D) {
                        u8 *snapshot;
                        func_PAL_L11_003F8E90(path+0x10,15);
                        qcopy(data+0x1F0+i*16,data+i*0xA0+0xB0);
                        ((PathState *)data)->timer[i]=0;
                        ((PathState *)data)->state[i]=4;
                        snapshot=g_collision_l11_result.hit;
                        ((PathState *)data)->hit[i]=snapshot;
                        qcopy(data+i*0xA0+0xB0,g_collision_l11_result.point);
                        qcopy(data+0x230+i*16,snapshot+0x10);
                        if (g_active_attacker_robot==object) H(data,0x296)=1;
                    }
                }
            } else {
                u8 *end=data+i*0xA0+0xB0;
                ((PathState *)data)->state[i]=5;
                func_PAL_L11_003F8E90(end,10);
                ((PathState *)data)->timer[i]=0;
            }
            break;
        case 3: {
            u8 *hit;
            if (((PathState *)data)->timer[i]<=((s32)(g_joba_beam_hit_frames) * 5 + 2) / 6 && (hit=((PathState *)data)->hit[i]) && hit[0x20]!=0xFE && hit[0x20]!=0xFD) {
                u8 *end;
                FastVecSub(delta,hit+0x10,data+0x230+i*16);
                end=data+i*0xA0+0xB0;
                FastVecAdd(end,end,delta);
                qcopy(data+0x230+i*16,((PathState *)data)->hit[i]+0x10);
                if ((g_arena_progress_level&15)==(((s32)object>>8)&15)) func_PAL_L11_003F8E90(end,1);
            } else {
                ((PathState *)data)->timer[i]=0;
                ((PathState *)data)->hit[i]=0;
                ((PathState *)data)->repeat[i]=g_joba_beam_repeat_count;
                ((PathState *)data)->state[i]=5;
            }
            break;
        }
        case 4:
            if (((PathState *)data)->timer[i]<((s32)(g_joba_beam_phase_frames_c) * 5 + 2) / 6) {
                t=IntToFloat(((PathState *)data)->timer[i]);
                t/=IntToFloat(((s32)(g_joba_beam_phase_frames_c) * 5 + 2) / 6);
                F(data+i*0xA0,0xA0)=((PathState *)data)->origin[i].x+(((PathState *)data)->target[i].x-((PathState *)data)->origin[i].x)*t;
                F(data+i*0xA0,0xA4)=((PathState *)data)->origin[i].y+(((PathState *)data)->target[i].y-((PathState *)data)->origin[i].y)*t;
                F(data+i*0xA0,0xA8)=((PathState *)data)->origin[i].z+(((PathState *)data)->target[i].z-((PathState *)data)->origin[i].z)*t;
            } else if (((PathState *)data)->repeat[i]<g_joba_beam_repeat_count) {
                u8 *path=data+0xA0+i*0xA0;
                ((PathState *)data)->repeat[i]++;
                vec_random_direction(path+0x60,g_joba_beam_dir_min_angle_b*0.0003490659f,g_joba_beam_dir_max_angle_b*0.0003490659f);
                vec_random_direction(path+0x70,g_joba_beam_dir_min_angle_b*0.0003490659f,g_joba_beam_dir_max_angle_b*0.0003490659f);
                vec_random_direction(path+0x80,g_joba_beam_dir_min_c,g_joba_beam_dir_max_c);
                vec_random_direction(path+0x90,g_joba_beam_dir_min_c,g_joba_beam_dir_max_c);
                ((PathState *)data)->timer[i]=0;
                ((PathState *)data)->state[i]=3;
                qcopy(data+0x210+i*16,data+0x1F0+i*16);
                qcopy(data+0xA0+i*0xA0,data+0x210+i*16);
                if (joba_beam_pick_target_point(object,data+0x210+i*16,data+0x1F0+i*16)) ((PathState *)data)->repeat[i]=g_joba_beam_repeat_count;
            } else {
                s32 sound=((PathState *)data)->sound;
                u8 *path;
                if (sound!=-1) {
                    u8 *slot=g_sound_state+sound*0x70;
                    if (P(slot,0x88)==object && slot[0x74]) snd_stop_voice(sound);
                }
                ((PathState *)data)->sound=-1;
                ((PathState *)data)->timer[i]=0;
                ((PathState *)data)->state[i]=0;
                path=data+0xA0+i*0xA0;
                vec_random_direction(path+0x60,g_joba_beam_dir_min_angle_a*0.0003490659f,g_joba_beam_dir_max_angle_a*0.0003490659f);
                vec_random_direction(path+0x70,g_joba_beam_dir_min_angle_a*0.0003490659f,g_joba_beam_dir_max_angle_a*0.0003490659f);
                vec_random_direction(path+0x80,g_joba_beam_dir_min_b,g_joba_beam_dir_max_b);
                vec_random_direction(path+0x90,g_joba_beam_dir_min_b,g_joba_beam_dir_max_b);
            }
            break;
        }
    }
    UpdateTwinRecordAnglesAndPositions(object);
}
