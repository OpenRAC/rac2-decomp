#include "names.h"
/* func_PAL_L17_00424618, the PAL copy of func_L17_0041ED58: the same C, where rename func_002B0A18 becomes func_PAL_002B1588; rename func_00288E18 becomes func_PAL_00289730. */
#include "common.h"

extern s32 g_moby_l17_pool __attribute__((sda));

/* func_L17_003C7C70 is defined in L17_003C7C70-tilt-g8.c. */

/* A 16-byte vector: the engine'vars helpers take and return these, and the copies between
   them are quadword moves. */
/* Turns the vector at a1 into the object'vars frame, then into the world with the matrix at
   a0 + 0xC0, and reports whether both of the first two coordinates stay below the two
   bounds. */
typedef struct {
    u8 pad00[0x80];
    f32 x;
    f32 y;
    f32 z;
    u8 pad8C[0x340 - 0x8C];
    s32 w340;
} L17Player;

extern L17Player g_hero_state;
extern f32 g_fan_var_value SDATA(D_L17_001B04BC);
/* `sda` on an array of unknown size: cc1 emits the one-instruction load, which the assembler
   expands absolute (`lui $r` / `lw $r,%lo($r)`), as retail has it in this -G0 unit; the limit
   word is loaded in a branch delay slot, so there it becomes the `$gp` form. The pool base is
   the word D_L17_001B2C1C declared above as an int, reached here as a pointer under a second
   name. */
extern u8 *D_L17_001B2C1C_base[] __asm__("D_L17_001B2C1C") __attribute__((sda));
/* The object'vars state record up to the group word and the word stored beside it. */
/* Walks the id list of the state'vars group and sets the state'vars mode word to 0x57 for every id
   that has an entity, stopping at the first that has none. */
/* Claims the shared slot at state+0x720 for this object (index into the object array):
   taken when free or when its holder is in state 0xFE/0xFD, then in mode 1 handed to the
   nearest candidate; returns 1 once this object holds it in mode 2. func_L17_003E6F20
   releases it. */
/* func_L17_00417DB0 is in L17_003C7C70-f7-g8.c. */

/* func_L17_0041E208 is defined in L17_0041E208-g8.c. */

/* func_L17_0041EAA8 is defined in L17_003C7C70-g8.c. */

typedef struct { unsigned char pad[0x464]; unsigned char flags[0]; } PickupFlags;
extern PickupFlags g_level_l17_save_state;
extern unsigned char g_moby_nibble_table[], g_grulch_reachable_flag, g_game_flag_table[];
extern int g_current_map_index SDATA(D_001A79F0);
typedef struct { unsigned char pad[0x20]; unsigned char state; unsigned char rest[0xDF]; } Entity;
extern Entity *entity_base_ptr __asm__("D_L17_001B2C1C") __attribute__((sda));
extern Entity *entity_base_gp SDATA(D_L17_001B2C1C);
extern char g_hero_position[];
extern float FastAddRotations(float,float), math_random_float_range(float,float), math_random_angle(void), math_random_signed_float_range(float,float);
extern int math_random_int_below(int);
extern void vec_build_spherical_offset(void *,float,float,float);
extern void *part_spawn_ground_effect(void *,int,unsigned,int,int,void *,float,float,float,int);
extern float vec_distance_xy(void *,void *);
extern void moby_set_flag_bit(void *,int),moby_set_state(void *,int,int),moby_mark_spawned(void *),value_set_entry_by_index_pal(int,int);
extern int subtitle_request_voice_line_pal(int,int);
/* Spins and sparkles an uncollected pickup; when the player comes within 1.5 units it bumps the
   pickup'vars saved count and triggers its linked entity, and when inactive it removes itself once
   that entity dies. */
void proximity_pickup_update_pal(unsigned char *moby)
{
    int *vars=*(int **)(moby+0x68);
    unsigned short id;
    unsigned char *position;
    int pass,sign,count;
    int bits;
    float size,ang,speed,scale;
    float vel[4] __attribute__((aligned(16)));
    float pos[4] __attribute__((aligned(16)));
    if(moby[0x20]!=0) goto inactive;
    id=*(unsigned short *)(moby+0xb2);
    if(g_level_l17_save_state.flags[(short)id]!=0) goto remove_self;
    {
        bits=g_moby_nibble_table[((short)id>>1)+(g_current_map_index<<10)];
        if(id&1) bits=(bits>>4)&7; else bits=bits&7;
        if(bits) goto remove_self;
        position=moby+0x10;
        {
            *(float *)(moby+0xf8)=FastAddRotations(*(float *)(moby+0xf8),0.087266474f);
            pass=1;
            do {
                size=math_random_float_range(2.0f,5.0f);
                sign=math_random_int_below(2); if(sign==0)--sign;
                ang=math_random_angle();
                speed=math_random_float_range(0.3490659f,1.5358899f);
                scale=math_random_float_range(0.05f,0.1f);
                vec_build_spherical_offset(vel,scale,ang,speed);
                qcopy(pos,position);
                pos[0]+=math_random_signed_float_range(0.0f,0.15f);
                pos[1]+=math_random_signed_float_range(0.0f,0.15f);
                pos[2]+=math_random_signed_float_range(0.0f,0.15f);
                part_spawn_ground_effect(pos,2,0x208020ff,0,sign,vel,size*0.1f,size,0.006f,0);
                part_spawn_ground_effect(pos,2,0x20ffffff,1,-sign,vel,size*0.03f,size*0.3f,0.006f,0);
            } while(--pass>=0);
            if(vec_distance_xy(position,g_hero_position)<1.5f) {
                unsigned short pickupId;
                unsigned char *counter;
                g_grulch_reachable_flag=1;
                pickupId=*(unsigned short *)(moby+0xb2);
                if(pickupId&1) {
                    counter=(((short)pickupId>>1)+(g_current_map_index<<10))+g_moby_nibble_table;
                    if(((*counter>>4)&7)!=7)*counter+=16;
                } else {
                    counter=(((short)pickupId>>1)+(g_current_map_index<<10))+g_moby_nibble_table;
                    if((*counter&7)!=7)++*counter;
                }
                if(*(int *)vars!=-1) {
                    ((unsigned short *)moby)[0x1a]|=1;
                    moby[0x31]=0;
                    moby_set_flag_bit(&entity_base_ptr[*vars],1);
                    moby_set_state(moby,1,-1);
                } else goto remove_self;
            }
            return;
        }
    }
remove_self:
    moby_mark_spawned(moby);
    return;
inactive:
    if(*(int *)vars!=-1) {
        int state;
        state=entity_base_gp[*vars].state;
        if(state==0xfe)goto dead;
        if(state!=0xfd)goto done;
    }
dead:
    {
        value_set_entry_by_index_pal(0x1292,0x64);
        count=g_game_flag_table[0x86]?1:2;
        if(g_game_flag_table[0x89])--count;
        if(count>0)subtitle_request_voice_line_pal(0xa0f,0x66);else subtitle_request_voice_line_pal(0xa10,0x67);
        moby_mark_spawned(moby);
    }
done:;
}

/* func_L17_0041F180 is defined in L17_collision.c. */

/* func_L17_0041F478 is defined in L17_003C7C70-link.c. */

/* func_L17_00420758 is defined in L17_collision.c. */

/* func_L17_00420A50 is defined in L17_00420A50-g8.c. */

/* func_L17_00420E08 is defined in L17_003C7C70-g8.c. */
