#include "common.h"

/* Debris burst of an Oozla moby: kept in its own -G8 -g unit. */
typedef int BC540Quad __attribute__((mode(TI)));

extern float math_random_float_range(float, float), math_random_angle(void), FastAddRotations(float, float);
extern void moby_l00_spawn_child(void *, int, int), moby_mark_spawned(void *);
extern void vec_scale_to_length(void *, void *, float), FastVecAdd(void *, void *, void *);
extern void breakable_spawn_copy(void *, void *);
extern int PlayMobySound(int, int, void *);
extern char *part_find_owned_effect_slot(void *, int, int);
extern void moby_transform_joint_to_world(void *, int, void *), SetDeathBits(void *, int, int);
extern void anim_start_blended(void *, int, int, int);
extern char *debris_l01_spawn_piece(char *, int, void *, void *, int, int, void *, void *, void *, float);

/* Level save state: collected[] is indexed by a moby's save id (s16 at +0xB2). */
typedef struct { u8 pad[0x464]; u8 collected[0]; } LevelSaveState;
extern LevelSaveState D_L01_0021E4B0;
extern int g_current_map_index;
extern u8 D_0019B4A8[];
/* Its address is rebuilt (unsplit la) before each spawn call, as in L01_00388FD0-tether-g8.c. */
extern float D_L01_001A8F60[] MACRO_ADDR;

/* Updates the breakable Oozla object. When it is hit it bursts into spinning debris pieces, plays a sound, removes itself and records that it was destroyed. */
void breakable_l01_debris_update(char *moby)
{
    float delta[4] __attribute__((aligned(16)));
    float position[4] __attribute__((aligned(16)));
    float rotation[4] __attribute__((aligned(16)));
    float dimensions[4] __attribute__((aligned(16)));
    char *vars=*(char **)(moby+0x68), *hit_moby,*debris_piece;
    float step,scale,travelled,size_ratio;
    int i,j,save_byte,save_index;
    float distance;
    if(*(unsigned char *)(moby+0x20)==0) {
        *(float *)(moby+0x2C)*=math_random_float_range(0.8f,1.1f);
        if(*(unsigned char *)(moby+0xB0)!=255) {
            if(D_L01_0021E4B0.collected[*(short *)(moby+0xB2)]) goto remove_initial;
            save_byte=D_0019B4A8[(*(short *)(moby+0xB2)>>1)+(g_current_map_index<<10)];
            if(*(short *)(moby+0xB2)&1) {
                if((save_byte>>4)&7) goto remove_initial;
                goto initial_path;
            }
            if(!(save_byte&7)) goto initial_path;
remove_initial:
            moby_l00_spawn_child(moby,0xA29,0);
            moby_mark_spawned(moby);
            return;
        }
initial_path:
        distance=*(float *)(vars+0x50);
        if(distance>0.0f) {
            step=distance/ *(float *)(vars+0x54);
            vec_scale_to_length(delta,moby+0xC0,step);
            FastVecAdd(position,moby+0x10,delta);
            for(travelled=step;travelled<*(float *)(vars+0x50);travelled+=step) {
                breakable_spawn_copy(moby,position);
                FastVecAdd(position,position,delta);
            }
        }
        *(unsigned char *)(moby+0x20)=1;
    }
    else {
    hit_moby=part_find_owned_effect_slot(moby,0x4010000,0);
    if(hit_moby && *(float *)(hit_moby+0x2C)>0.0f) {
        size_ratio=*(float *)(moby+0x2C)/ *(float *)(*(char **)(moby+0x24)+0x24);
        scale=size_ratio;
        qcopy(position,moby+0xF0);
        *(BC540Quad *)rotation=0;
        rotation[1]=-1.3790000f; rotation[2]=0.778f; rotation[3]=0.3f;
        PlayMobySound(0,0,moby);
        for(i=0;i<4;i++) {
            moby_transform_joint_to_world(moby,i,delta);
            position[2]=math_random_angle();
            for(j=2;j>=0;j--) {
                debris_piece=debris_l01_spawn_piece(moby,0xA28 /* moby class 2600 */,delta,position,0,1,D_L01_001A8F60,D_L01_001A8F60,rotation,0.0f);
                *(float *)(debris_piece+0x2C)*=scale;
                position[2]=FastAddRotations(position[2],2.0943954f);
            }
            scale*=0.85f;
        }
        *(BC540Quad *)dimensions=0;
        dimensions[0]=0.175f;dimensions[1]=0.136f;dimensions[2]=-0.691f;dimensions[3]=0.05f;
        moby_transform_joint_to_world(moby,4,delta);
        qcopy(position,moby+0xF0);
        for(j=2;j>=0;j--) {
            debris_piece=debris_l01_spawn_piece(moby,0xA27 /* moby class 2599 */,delta,position,0,1,D_L01_001A8F60,D_L01_001A8F60,dimensions,0.0f);
            *(float *)(debris_piece+0x2C)*=size_ratio;
            position[2]=FastAddRotations(position[2],2.0943954f);
        }
        moby_l00_spawn_child(moby,0xA29,0);
        SetDeathBits(moby,0,3);
        if(*(short *)(moby+0xB2)&1) {
            save_index=(*(short *)(moby+0xB2)>>1)+(g_current_map_index<<10);
            if(((D_0019B4A8[save_index]>>4)&7)!=7) D_0019B4A8[save_index]+=16;
        } else {
            save_index=(*(short *)(moby+0xB2)>>1)+(g_current_map_index<<10);
            if((D_0019B4A8[save_index]&7)!=7) D_0019B4A8[save_index]++;
        }
        moby_mark_spawned(moby);
    }
    }
    if(*(unsigned char *)(moby+0xBC)) {
        if(*(unsigned char *)(moby+0x43)!=1) anim_start_blended(moby,1,0,10);
        *(unsigned char *)(moby+0xBC)=0;
    } else if((*(unsigned char *)(moby+0x60)&2) && *(unsigned char *)(moby+0x43)!=0) anim_start_blended(moby,0,0,60);
}
