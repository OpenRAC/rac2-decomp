#include "include_asm.h"

#include "common.h"
typedef int Quad __attribute__((mode(TI)));
extern void moby_set_state(void *, int, int);
extern void *part_find_owned_effect_slot(void *, int, int);
extern float math_random_float_range(float, float);
extern void FastVecScale(void *, void *, float);
extern void FastVecSub(void *, void *, void *);
extern void FastVecAdd(void *, void *, void *);
extern void part_explode_object_into_pieces_pal(void *,void *,void *,void *,int,int,int,int,int,unsigned char,int);
extern void *SpawnExplosion_pal(void *,int,int,int,int,int,int,int,float,float,int,int,int,int);
extern void moby_mark_spawned(void *);
extern int g_pickup_piece_lifetime __attribute__((sda));
extern int g_pickup_piece_spread_range __attribute__((sda));
extern int g_pickup_piece_speed_range __attribute__((sda));
extern int g_pickup_piece_offset __attribute__((sda));
extern unsigned char g_breakable_pickup_mask NOT_SDA;
extern struct { char pad[0xA0]; unsigned char bits; } g_game_flag_table;

void breakable_pickup_update_pal(u8 *o) {
    u8 *s=*(u8 **)(o+0x68), *hit;
    float a[4] __attribute__((aligned(16))), b[4] __attribute__((aligned(16)));
    float spread[4] __attribute__((aligned(16)));
    switch(o[0x20]) {
    case 0: moby_set_state(o,1,-1); break;
    case 1:
        hit=part_find_owned_effect_slot(o,0x4010000,0);
        if(hit && !*(int *)s) {
            *(Quad *)spread=0;
            spread[0]=3.0f;
            spread[1]=3.0f;
            *(float *)(hit+0x18)=1.0f;
            FastVecScale(a,hit+0x10,math_random_float_range(6.0f,8.0f));
            qcopy(b,a);
            FastVecSub(a,a,spread);
            FastVecAdd(b,b,spread);
            part_explode_object_into_pieces_pal(o,a,&g_pickup_piece_spread_range,&g_pickup_piece_speed_range,65535,-1,g_pickup_piece_lifetime,9,1,255,0);
            moby_set_state(o,2,-1);
        }
        o[0xA8]=255;
        break;
    case 2:
        if((unsigned)*(int *)(s+4)>=8 || (((g_breakable_pickup_mask>>*(int *)(s+4))^1)&1)) {
            part_explode_object_into_pieces_pal(o,&g_pickup_piece_offset,&g_pickup_piece_spread_range,&g_pickup_piece_speed_range,65535,0,g_pickup_piece_lifetime,16,254,255,0);
            if((unsigned)*(int *)(s+4)<8) g_game_flag_table.bits |= 1<<*(int *)(s+4);
        } else part_explode_object_into_pieces_pal(o,&g_pickup_piece_offset,&g_pickup_piece_spread_range,&g_pickup_piece_speed_range,65535,0,g_pickup_piece_lifetime,0,254,255,0);
        SpawnExplosion_pal(o+0x10,0,5,5,5,5,5,0,*(float *)(o+0x2C)*10.0f,20.0f,1,0,1,0);
        moby_mark_spawned(o);
        break;
    }
}
