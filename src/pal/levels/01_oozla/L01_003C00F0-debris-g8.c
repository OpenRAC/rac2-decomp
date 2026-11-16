#include "names.h"
/* func_PAL_L01_003C00F0, the PAL copy of func_L01_003BC540: the same C, where func_L01_003BCA38
   becomes func_PAL_L01_003C05E8; func_002A6C58 becomes func_PAL_002A7650; func_002A7470 becomes
   func_PAL_002A7E68. */
#include "common.h"

typedef int BC540Quad __attribute__((mode(TI)));

extern float math_random_float_range(float, float), math_random_angle(void), FastAddRotations(float, float);
extern void moby_mark_spawned(void *);
extern char *moby_l00_spawn_child(void *, int, int);
extern void vec_scale_to_length(void *, void *, float), FastVecAdd(void *, void *, void *);
extern void *breakable_spawn_copy(void *, void *);
extern int PlayMobySound(int, int, void *);
extern char *part_find_owned_effect_slot(void *, int, int);
extern void SetDeathBits_pal(void *, int, int);
extern void moby_transform_joint_to_world(void *, int, void *);
extern void anim_start_blended_pal(void *, int, int, int);
extern char *debris_l01_spawn_piece_pal(char *, int, void *, void *, int, int, void *, void *, void *, float);

typedef struct { u8 pad[0x464]; u8 collected[0]; } LevelSaveState;
extern LevelSaveState g_level_save_state_backup;
extern int g_current_map_index;
extern u8 g_moby_nibble_table[];
extern float g_zero_l01_vector[] MACRO_ADDR;

void breakable_l01_debris_update_pal(char *moby)
{
    float delta[4] __attribute__((aligned(16)));
    float position[4] __attribute__((aligned(16)));
    float rotation[4] __attribute__((aligned(16)));
    float dimensions[4] __attribute__((aligned(16)));
    char *state=*(char **)(moby+0x68), *hit,*piece;
    float step,scale,t,size;
    int i,j,nibble,index;
    float distance;
    if(*(unsigned char *)(moby+0x20)==0) {
        *(float *)(moby+0x2C)*=math_random_float_range(0.8f,1.1f);
        if(*(unsigned char *)(moby+0xB0)!=255) {
            if(g_level_save_state_backup.collected[*(short *)(moby+0xB2)]) goto remove_initial;
            nibble=g_moby_nibble_table[(*(short *)(moby+0xB2)>>1)+(g_current_map_index<<10)];
            if(*(short *)(moby+0xB2)&1) {
                if((nibble>>4)&7) goto remove_initial;
                goto initial_path;
            }
            if(!(nibble&7)) goto initial_path;
remove_initial:
            moby_l00_spawn_child(moby,0xA29,0);
            moby_mark_spawned(moby);
            return;
        }
initial_path:
        distance=*(float *)(state+0x50);
        if(distance>0.0f) {
            step=distance/ *(float *)(state+0x54);
            vec_scale_to_length(delta,moby+0xC0,step);
            FastVecAdd(position,moby+0x10,delta);
            for(t=step;t<*(float *)(state+0x50);t+=step) {
                breakable_spawn_copy(moby,position);
                FastVecAdd(position,position,delta);
            }
        }
        *(unsigned char *)(moby+0x20)=1;
    }
    else {
    hit=part_find_owned_effect_slot(moby,0x4010000,0);
    if(hit && *(float *)(hit+0x2C)>0.0f) {
        size=*(float *)(moby+0x2C)/ *(float *)(*(char **)(moby+0x24)+0x24);
        scale=size;
        qcopy(position,moby+0xF0);
        *(BC540Quad *)rotation=0;
        rotation[1]=-1.3790000f; rotation[2]=0.778f; rotation[3]=0.3f;
        PlayMobySound(0,0,moby);
        for(i=0;i<4;i++) {
            moby_transform_joint_to_world(moby,i,delta);
            position[2]=math_random_angle();
            for(j=2;j>=0;j--) {
                piece=debris_l01_spawn_piece_pal(moby,0xA28,delta,position,0,1,g_zero_l01_vector,g_zero_l01_vector,rotation,0.0f);
                *(float *)(piece+0x2C)*=scale;
                position[2]=FastAddRotations(position[2],2.0943954f);
            }
            scale*=0.85f;
        }
        *(BC540Quad *)dimensions=0;
        dimensions[0]=0.175f;dimensions[1]=0.136f;dimensions[2]=-0.691f;dimensions[3]=0.05f;
        moby_transform_joint_to_world(moby,4,delta);
        qcopy(position,moby+0xF0);
        for(j=2;j>=0;j--) {
            piece=debris_l01_spawn_piece_pal(moby,0xA27,delta,position,0,1,g_zero_l01_vector,g_zero_l01_vector,dimensions,0.0f);
            *(float *)(piece+0x2C)*=size;
            position[2]=FastAddRotations(position[2],2.0943954f);
        }
        moby_l00_spawn_child(moby,0xA29,0);
        SetDeathBits_pal(moby,0,3);
        if(*(short *)(moby+0xB2)&1) {
            index=(*(short *)(moby+0xB2)>>1)+(g_current_map_index<<10);
            if(((g_moby_nibble_table[index]>>4)&7)!=7) g_moby_nibble_table[index]+=16;
        } else {
            index=(*(short *)(moby+0xB2)>>1)+(g_current_map_index<<10);
            if((g_moby_nibble_table[index]&7)!=7) g_moby_nibble_table[index]++;
        }
        moby_mark_spawned(moby);
    }
    }
    if(*(unsigned char *)(moby+0xBC)) {
        if(*(unsigned char *)(moby+0x43)!=1) anim_start_blended_pal(moby,1,0,10);
        *(unsigned char *)(moby+0xBC)=0;
    } else if((*(unsigned char *)(moby+0x60)&2) && *(unsigned char *)(moby+0x43)!=0) anim_start_blended_pal(moby,0,0,60);
}
