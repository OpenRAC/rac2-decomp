/* func_L11_003F33E0: per-frame update of an object's two path records (one per
 * index of the pair at object+0x68). Needs -g for the nop pair before a div.s in
 * state 5 and -frac2-gcse-unsplit-edges for the hit[i] base in the delay slot of
 * the first test. D_0018C2BC is absolute here (NOT_SDA): its load
 * keeps its own %hi pseudo, and that insn sets the gcse table size which orders
 * the spill slots at 0x68/0x6C.
 */
#include "common.h"

extern void func_0029FCC0(void *, s32, void *);
extern s32 func_002A8C28(void *, void *, f32, s32, f32, f32, s32, s32, s32);
extern void func_002A7A00(void *, f32, f32);
extern f32 func_00283CE0(s32);
extern void func_00282CF0(void *, void *, void *);
extern void func_00282CC0(void *, void *, void *);
extern void func_00282F20(void *, void *, f32);
extern void func_002A8C00(void *, void *, s32, void *, f32);
extern s32 func_002761F8(void *, void *, s32, void *, void *);
extern s32 func_L11_003F3258(void *, void *, void *);
extern void func_L11_003F4A58(void *, s32);
extern void func_L11_003F4060(void *);
extern void func_002E59F8(s32);
extern u8 D_00188660[];
extern u8 *D_0018C2BC NOT_SDA;
extern s32 D_L11_001B30C8;
typedef struct { u8 pad[0x18]; u8 *hit; u8 pad1c[4]; f32 point[4]; } PathHit;
extern PathHit D_L11_001C0D00;
extern s32 D_L11_001B059C __attribute__((sda));
extern s32 D_L11_001B05A4 __attribute__((sda));
extern s32 D_L11_001B05A8 __attribute__((sda));
extern s32 D_L11_001B05AC __attribute__((sda));
extern s32 D_L11_001B05B0 __attribute__((sda));
extern f32 D_L11_001B05EC __attribute__((sda));
extern f32 D_L11_001B05F0 __attribute__((sda));
extern f32 D_L11_001B0614 __attribute__((sda));
extern f32 D_L11_001B0618 __attribute__((sda));
extern f32 D_L11_001B061C __attribute__((sda));
extern f32 D_L11_001B0620 __attribute__((sda));
extern f32 D_L11_001B05F4 __attribute__((sda));
extern f32 D_L11_001B05F8 __attribute__((sda));

#define F(p,o) (*(f32 *)((u8 *)(p)+(o)))
#define H(p,o) (*(s16 *)((u8 *)(p)+(o)))
#define U(p,o) (*(u16 *)((u8 *)(p)+(o)))
#define P(p,o) (*(u8 **)((u8 *)(p)+(o)))

typedef struct { f32 x,y,z,w; } Vec4 __attribute__((aligned(16)));
typedef struct { Vec4 pos; Vec4 end; u8 pad20[0x80]; } PathRec;
typedef struct { u8 pad[0xA0]; PathRec path[2]; u8 pad1e0[0x10]; Vec4 target[2]; Vec4 origin[2]; Vec4 last[2]; u8 pad250[0x10]; f32 scale[2]; u8 *hit[2]; u8 pad270[4]; s16 timer[2]; u16 state[2]; s16 repeat[2]; u8 pad280[0x10]; s32 sound; } PathState;

/* Runs the two Joba beams, one per side. Each one aims, shoots out, sparks where it hits something, and then resets. */
void func_L11_003F33E0(u8 *object) {
    f32 starts[2][4] __attribute__((aligned(16)));
    f32 delta[4] __attribute__((aligned(16)));
    struct { u8 pad[0x18]; u8 kind, flags; u16 id; u8 tail[0x14]; } query __attribute__((aligned(16)));
    u8 *data = P(object,0x68);
    s32 i;
    f32 t;
    TransformMobyJointToWorld(object,1,starts[0]);
    TransformMobyJointToWorld(object,0,starts[1]);
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
            SweepCollisionFromObject(object,starts[0],0.2f,0x10001,data[0x34],1.0f,0,1,0);
            SweepCollisionFromObject(object,starts[1],0.2f,0x10001,data[0x34],1.0f,0,1,0);
            if (((PathState *)data)->timer[i]>D_L11_001B05A4) {
                u8 *path=data+0xA0+i*0xA0;
                RandomDirectionVector(path+0x60,D_L11_001B0614*0.0002908882452175021f,D_L11_001B0618*0.0002908882452175021f);
                RandomDirectionVector(path+0x70,D_L11_001B0614*0.0002908882452175021f,D_L11_001B0618*0.0002908882452175021f);
                RandomDirectionVector(path+0x80,D_L11_001B061C,D_L11_001B0620);
                RandomDirectionVector(path+0x90,D_L11_001B061C,D_L11_001B0620);
                ((PathState *)data)->timer[i]=0;
                ((PathState *)data)->state[i]=3;
                ((PathState *)data)->repeat[i]=0;
                qcopy(data+0x210+i*16,starts[i]);
                qcopy(data+0xA0+i*0xA0,data+0x210+i*16);
                if (PickBeamTargetPoint(object,data+0x210+i*16,data+0x1F0+i*16))
                    ((PathState *)data)->repeat[i]=D_L11_001B059C;
            } else {
                t=IntToFloat(((PathState *)data)->timer[i]);
                t/=IntToFloat(D_L11_001B05A4);
                ((PathState *)data)->scale[i]=t;
            }
            break;
        case 2:
            SweepCollisionFromObject(object,starts[i],0.2f,0x10001,data[0x34],1.0f,0,1,0);
            if (((PathState *)data)->timer[i]<=D_L11_001B05A8) {
                u8 *path;
                s32 off;
                t=IntToFloat(((PathState *)data)->timer[i]);
                t/=IntToFloat(D_L11_001B05A8);
                off=i*0xA0;
                path=data+0xA0+off;
                F(data+off,0xB0)=((PathState *)data)->origin[i].x+(((PathState *)data)->target[i].x-((PathState *)data)->origin[i].x)*t;
                F(data+off,0xB4)=((PathState *)data)->origin[i].y+(((PathState *)data)->target[i].y-((PathState *)data)->origin[i].y)*t;
                F(data+off,0xB8)=((PathState *)data)->origin[i].z+(((PathState *)data)->target[i].z-((PathState *)data)->origin[i].z)*t;
                FastVecSub(delta,path+0x10,path);
                vec_scale_to_length(delta,delta,0.03333333507180214f);
                make_hit_descriptor(&query,object,0x210001,delta,data[0x34]);
                query.kind=5;
                query.flags=3;
                query.id=U(object,0xAA);
                if (CollLine(path,path+0x10,0,object,&query)) {
                    u8 *hit=D_L11_001C0D00.hit;
                    if (hit && H(hit,0xAA)!=0xC7D /* moby class 3197 */) {
                        u8 *snapshot;
                        SpawnBeamHitSparks(path+0x10,15);
                        qcopy(data+0x1F0+i*16,data+i*0xA0+0xB0);
                        ((PathState *)data)->timer[i]=0;
                        ((PathState *)data)->state[i]=4;
                        snapshot=D_L11_001C0D00.hit;
                        ((PathState *)data)->hit[i]=snapshot;
                        qcopy(data+i*0xA0+0xB0,D_L11_001C0D00.point);
                        qcopy(data+0x230+i*16,snapshot+0x10);
                        if (gActiveAttackerRobot==object) H(data,0x296)=1;
                    }
                }
            } else {
                u8 *end=data+i*0xA0+0xB0;
                ((PathState *)data)->state[i]=5;
                SpawnBeamHitSparks(end,10);
                ((PathState *)data)->timer[i]=0;
            }
            break;
        case 3: {
            u8 *hit;
            if (((PathState *)data)->timer[i]<=D_L11_001B05AC && (hit=((PathState *)data)->hit[i]) && hit[0x20]!=0xFE && hit[0x20]!=0xFD) {
                u8 *end;
                FastVecSub(delta,hit+0x10,data+0x230+i*16);
                end=data+i*0xA0+0xB0;
                FastVecAdd(end,end,delta);
                qcopy(data+0x230+i*16,((PathState *)data)->hit[i]+0x10);
                if ((D_L11_001B30C8&15)==(((s32)object>>8)&15)) SpawnBeamHitSparks(end,1);
            } else {
                ((PathState *)data)->timer[i]=0;
                ((PathState *)data)->hit[i]=0;
                ((PathState *)data)->repeat[i]=D_L11_001B059C;
                ((PathState *)data)->state[i]=5;
            }
            break;
        }
        case 4:
            if (((PathState *)data)->timer[i]<D_L11_001B05B0) {
                t=IntToFloat(((PathState *)data)->timer[i]);
                t/=IntToFloat(D_L11_001B05B0);
                F(data+i*0xA0,0xA0)=((PathState *)data)->origin[i].x+(((PathState *)data)->target[i].x-((PathState *)data)->origin[i].x)*t;
                F(data+i*0xA0,0xA4)=((PathState *)data)->origin[i].y+(((PathState *)data)->target[i].y-((PathState *)data)->origin[i].y)*t;
                F(data+i*0xA0,0xA8)=((PathState *)data)->origin[i].z+(((PathState *)data)->target[i].z-((PathState *)data)->origin[i].z)*t;
            } else if (((PathState *)data)->repeat[i]<D_L11_001B059C) {
                u8 *path=data+0xA0+i*0xA0;
                ((PathState *)data)->repeat[i]++;
                RandomDirectionVector(path+0x60,D_L11_001B0614*0.0002908882452175021f,D_L11_001B0618*0.0002908882452175021f);
                RandomDirectionVector(path+0x70,D_L11_001B0614*0.0002908882452175021f,D_L11_001B0618*0.0002908882452175021f);
                RandomDirectionVector(path+0x80,D_L11_001B061C,D_L11_001B0620);
                RandomDirectionVector(path+0x90,D_L11_001B061C,D_L11_001B0620);
                ((PathState *)data)->timer[i]=0;
                ((PathState *)data)->state[i]=3;
                qcopy(data+0x210+i*16,data+0x1F0+i*16);
                qcopy(data+0xA0+i*0xA0,data+0x210+i*16);
                if (PickBeamTargetPoint(object,data+0x210+i*16,data+0x1F0+i*16)) ((PathState *)data)->repeat[i]=D_L11_001B059C;
            } else {
                s32 sound=((PathState *)data)->sound;
                u8 *path;
                if (sound!=-1) {
                    u8 *slot=gSoundState+sound*0x70;
                    if (P(slot,0x88)==object && slot[0x74]) StopSoundVoice(sound);
                }
                ((PathState *)data)->sound=-1;
                ((PathState *)data)->timer[i]=0;
                ((PathState *)data)->state[i]=0;
                path=data+0xA0+i*0xA0;
                RandomDirectionVector(path+0x60,D_L11_001B05EC*0.0002908882452175021f,D_L11_001B05F0*0.0002908882452175021f);
                RandomDirectionVector(path+0x70,D_L11_001B05EC*0.0002908882452175021f,D_L11_001B05F0*0.0002908882452175021f);
                RandomDirectionVector(path+0x80,D_L11_001B05F4,D_L11_001B05F8);
                RandomDirectionVector(path+0x90,D_L11_001B05F4,D_L11_001B05F8);
            }
            break;
        }
    }
    UpdateTwinRecordAnglesAndPositions(object);
}
