#include "include_asm.h"

#include "common.h"
typedef int EffectQuad10 __attribute__((mode(TI)));
extern void moby_set_state(void *,int,int),moby_mark_spawned(void *);
extern char *part_find_owned_effect_slot(void *,int,int);
extern float math_random_float_range(float,float);
extern void FastVecScale(void *,void *,float),FastVecSub(void *,void *,void *),FastVecAdd(void *,void *,void *);
extern int g_hit_flash_piece_param SDATA(D_L00_001B1370);
extern char g_hit_flash_piece_table_b[8] SDATA(D_L00_001B1368);
extern char g_hit_flash_piece_table_a[8] SDATA(D_L00_001B1360);
extern void part_explode_object_into_pieces_pal(void *,void *,void *,void *,int,int,int,int,int,int,int);

void hit_l00_flash_update_pal(unsigned char *object) {
    float minimum[4],maximum[4],size[4];
    int *state=*(int **)(object+0x68);
    char *hit;
    switch(object[0x20]) {
    case 0: moby_set_state(object,1,-1);break;
    case 1:
        hit=part_find_owned_effect_slot(object,0x04010000,0);
        if(hit && !state[0]) {
            *(EffectQuad10 *)size=0;
            size[0]=3.5f;size[1]=3.5f;
            *(float *)(hit+0x18)=1.0f;
            FastVecScale(minimum,hit+0x10,math_random_float_range(4.0f,8.0f));
            qcopy(maximum,minimum);
            FastVecSub(minimum,minimum,size);
            FastVecAdd(maximum,maximum,size);
            part_explode_object_into_pieces_pal(object,minimum,g_hit_flash_piece_table_b,g_hit_flash_piece_table_a,65535,0,g_hit_flash_piece_param,8,65535,255,0);
            moby_set_state(object,2,-1);
        }
        object[0xa8]=255;break;
    case 2: moby_mark_spawned(object);break;
    }
}
