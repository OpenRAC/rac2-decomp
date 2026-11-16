/* func_US2_L00_00406CF8, the USA v2.00 copy of func_L00_00405808: the same C, where rename func_L00_002C42E0 becomes func_US2_L00_002C4560; rename func_002B0A18 becomes func_US2_002B1880; rename func_L00_00408800 becomes func_US2_L00_00409CF0. */
#include "common.h"

#define H(p,o) (*(short *)((char *)(p)+(o)))
#define U(p,o) (*(unsigned short *)((char *)(p)+(o)))
#define B(p,o) (*(unsigned char *)((char *)(p)+(o)))
#define F(p,o) (*(float *)((char *)(p)+(o)))
typedef int Quad __attribute__((mode(TI)));
typedef struct { float x,y,z,w; } __attribute__((aligned(16))) Vec;
typedef struct {
    char pad0[0x730]; float basis[12];
    char pad760[0x1230-0x760]; int buttons;
    char pad1234[0x1244-0x1234]; int item_state;
    char pad1248[0x2290-0x1248]; char *object; int current;
    int pad2298; unsigned int control;
    char pad22a0[0x24ec-0x22a0]; short direction;
    char pad24ee[0x2534-0x24ee]; int timer;
} Hero;
typedef struct { char pad[0x360]; unsigned short kills, pad362; unsigned int best, levels; } Stats;
typedef struct { int present; unsigned char type; char pad[219]; } Upgrade;
typedef struct { float color[4]; float pos[3]; float radius; } Light;
typedef struct { float pos[4]; char *target; float total, left; short timer, seen;
    char pad20[0x44-0x20]; int delay; float yaw,pitch; } Ray;
typedef struct { char pad0[0x74]; unsigned char playing; char pad75[0x88-0x75]; char *owner; } Voice;
extern Hero g_hero_state;
extern Stats g_statistics_table;
typedef struct { unsigned char pad0[0x10]; unsigned char current; unsigned char pad11[0x48-0x11]; unsigned char equipped; } Inventory;
extern Inventory g_item_slot_to_record;
extern char g_sound_state[];
extern Upgrade g_weapon_l00_table[];
extern char g_scalar_transition_state[];
extern Light g_light_table[];
extern int g_frame_counter MACRO_ADDR, g_current_map_index MACRO_ADDR;
extern unsigned char g_item_enabled_flags[32] __attribute__((sda));
extern int g_pad_pressed_flags __attribute__((nosda));
extern int g_sheepinator_l00_light_2 MACRO_ADDR;
extern int g_sheepinator_l00_light_timer_2 MACRO_ADDR;
extern int g_sheepinator_l00_sound_2 MACRO_ADDR;

extern int g_sheepinator_shot_counter __attribute__((sda));
extern float g_sheepinator_l00_drain_rate_2 __attribute__((sda));
extern float g_sheepinator_gauge_fraction __attribute__((sda));
extern int g_sheepinator_l00_beam_reset_2 __attribute__((sda));
extern int g_collection_progress_flag;
extern float moby_get_anim_value(void *);
extern int math_fast_float_d(void *);
extern int FastDecTimer(void *);
extern void anim_start_blended(void *,int,int,int);
extern void matrix_mul_vec3(void *,void *,void *);
extern void FastVecAdd(void *,void *,void *);
extern s32 hero_l00_change_action_us2(int,int);
extern void copy_matrix3x4(void *,void *);
extern void matrix_from_basis_rows(void *,void *);
extern void transform_vector(void *,void *,void *);
extern void FastVecScale(void *,void *,float);
extern float mat_fast_helper_a(float,float);
extern float vec_length_xy(void *);
extern char *sheepinator_find_target(void *,void *,void *,void *);
extern char *moby_get_private_value_0(void *);
extern float IntToFloat(int);
extern void gauge_popup_show(int,int,int,float);
extern int snd_play_from_global_bank(int,int,void *);
extern void value_set_entry_by_index_us2(int,int);
extern int PlayMobySound(int,int,void *);
extern void *dark_sheep_spawn_from_object_us2(void *);
extern void sheepinator_update_beam_shape(void *);
extern int gfx_add_point_light(void *,float,float,unsigned int);
extern void vec_scale_to_length(void *,void *,float);
extern int snd_is_voice_playing_for_owner(void *,int);
extern void gfx_free_point_light(int);
extern void snd_stop_voice(int);
extern void anim_start_blended_with_flags(void *,int,int,int,int);

/* Updates the Morphoray: while fired it aims the beam, drains the target's gauge and turns it into a dark sheep when empty, and runs the beam light and sound (US2 copy of MorphorayUpdate). */
void MorphorayUpdate_us2(char *morphoray)
{
    Vec offset;
    Vec direction;
    Vec matrix[3];
    Vec basis[4];
    Ray *beam=*(Ray **)(morphoray+0x68);
    char *target, *info; Light *entry;
    int special=0;
    float rate, value;
    int index;
    int boosted;
    int near;
    if (g_hero_state.item_state==3) special=1;
    if (!B(morphoray,0x20)) {
        B(morphoray,0x20)=1;
        g_sheepinator_l00_light_2=-1;
        g_sheepinator_l00_sound_2=-1;
        g_sheepinator_l00_light_timer_2=0;
    }
    /* RAC1 also gates the beam on near; here nothing reads it, so only the call survives. */
    near=1;
    if (!B(morphoray,0x43) && moby_get_anim_value(morphoray)<6.0f) near=0;
    {
    Hero *player=&g_hero_state;
    int permitted=1;
    if (player->current==29) { if (!math_fast_float_d(&player->timer)) permitted=0; }
    else g_hero_state.timer=40;
    FastDecTimer(&beam->timer);
    if ((unsigned int)g_hero_state.control<2 && (g_pad_pressed_flags&g_hero_state.buttons) && permitted) {
        if (B(morphoray,0x43)!=2) anim_start_blended(morphoray,2,0,0);
        if (!beam->seen) {
            beam->seen=1;
            if (g_statistics_table.kills<65535) g_statistics_table.kills++;
            if ((unsigned int)g_frame_counter>g_statistics_table.best) g_statistics_table.best=g_frame_counter;
            g_statistics_table.levels = (g_statistics_table.levels | (1<<g_current_map_index)) | 0x80000000;
        }
        if (!beam->timer) beam->timer=15;
        *(Quad *)&offset=0;
        offset.x=0.15f; offset.y=-1.0f; offset.z=0.06f; offset.w=1.0f;
        matrix_mul_vec3(&offset,&offset,morphoray+0xc0);
        FastVecAdd(beam,morphoray+0x10,&offset);
        if (g_hero_state.current==1) hero_l00_change_action_us2(29,1);
        *(Quad *)&direction=0;
        if (g_hero_state.current==29 && (U(g_hero_state.object,0x34)&1)) {
            copy_matrix3x4(matrix,g_scalar_transition_state);
            matrix_from_basis_rows(basis,matrix);
            direction.z=1.0f;
            transform_vector(&direction,&direction,basis);
        } else if (g_hero_state.direction==1) FastVecScale(&direction,morphoray+0xd0,-1.0f);
        else {
            direction.x=1.0f;
            matrix_mul_vec3(&direction,&direction,g_hero_state.basis);
        }
        beam->yaw=mat_fast_helper_a(direction.x,direction.y);
        value=vec_length_xy(&direction);
        beam->pitch=mat_fast_helper_a(value,direction.z);
        *(Quad *)matrix=*(Quad *)beam;
        target=sheepinator_find_target(morphoray,matrix,&beam->yaw,&beam->pitch);
        math_fast_float_d(&beam->delay);
        if (beam->target) {
            if (B(beam->target,0x20)==254) goto clear_target;
            if (B(beam->target,0x20)==253) {
clear_target:
                beam->target=0; beam->delay=0;
            }
        }
        if (target || beam->delay) {
            if (target) {
                info=moby_get_private_value_0(target);
                if (target!=beam->target && !beam->delay) {
                    beam->target=target;
                    beam->total=IntToFloat(H(info,4));
                    beam->left=F(info,0);
                    beam->delay=30;
                    if (beam->total<=1.0f) beam->left=0;
                }
            }
            {
            Inventory *inventory=&g_item_slot_to_record;
            Upgrade *upgrades=g_weapon_l00_table;
            rate=1.0f;
            if (upgrades[inventory->equipped].type) rate=1.33f;
            boosted=upgrades[inventory->current].present!=0 && upgrades[inventory->current].type==3;
            }
            g_sheepinator_l00_drain_rate_2=boosted?50.0f:12.5f;
            beam->left-=g_sheepinator_l00_drain_rate_2*(rate*0.016666668f);
            if (beam->left<0.0f) beam->left=0.0f;
            g_sheepinator_gauge_fraction=beam->left/beam->total;
        } else g_sheepinator_gauge_fraction=1.0f;
        gauge_popup_show(1,0x60000000,0,g_sheepinator_gauge_fraction);
        if (beam->target && beam->left<=0.0f) {
            int target_class=H(beam->target,0xaa);
            if (g_current_map_index==12 && target_class==MOBY_CLASS_MUTANT_TEST_SQUIRREL) {
                if (++g_sheepinator_shot_counter>=16 && !g_item_enabled_flags[22]) {
                    g_item_enabled_flags[22]=1; snd_play_from_global_bank(1,0,0); value_set_entry_by_index_us2(4659,-1); g_collection_progress_flag=1;
                }
            }
            PlayMobySound(3,0,morphoray);
            dark_sheep_spawn_from_object_us2(beam->target); beam->target=0;
        }
        sheepinator_update_beam_shape(morphoray);
        if (g_sheepinator_l00_light_2==-1) g_sheepinator_l00_light_2=gfx_add_point_light(morphoray+0x10,7.5f,0.0f,0x207f7f);
        if (g_sheepinator_l00_light_2>=0) {
            g_sheepinator_l00_light_timer_2=20;
            vec_scale_to_length(matrix,morphoray+0xd0,-0.5f);
            FastVecAdd(&matrix[1],beam,matrix);
            { Light *light=&g_light_table[g_sheepinator_l00_light_2];
            float x=matrix[1].x, y=matrix[1].y, z=matrix[1].z; light->pos[0]=x; light->pos[1]=y; light->pos[2]=z; light->radius=7.5f; }
        }
        if (!snd_is_voice_playing_for_owner(morphoray,g_sheepinator_l00_sound_2)) g_sheepinator_l00_sound_2=PlayMobySound(1,4,morphoray);
    } else {
        beam->target=0; beam->seen=0; beam->delay=0; g_sheepinator_l00_beam_reset_2=1;
        if (g_sheepinator_l00_light_2>=0) {
            vec_scale_to_length(&offset,morphoray+0xd0,-0.5f);
            FastVecAdd(&direction,beam,&offset);
            entry=&g_light_table[g_sheepinator_l00_light_2];
            { float x=direction.x, y=direction.y, z=direction.z; entry->pos[0]=x; entry->pos[1]=y; entry->pos[2]=z; entry->radius=7.5f; }
            value=IntToFloat(g_sheepinator_l00_light_timer_2)*0.05f;
            entry=&g_light_table[g_sheepinator_l00_light_2];
            entry->color[0]=value; entry->color[1]=value; entry->color[2]=value*0.25f;
            if (math_fast_float_d(&g_sheepinator_l00_light_timer_2)) { gfx_free_point_light(g_sheepinator_l00_light_2); g_sheepinator_l00_light_2=-1; }
        }
    if (g_sheepinator_l00_light_2>=0 && !g_sheepinator_l00_light_timer_2) { gfx_free_point_light(g_sheepinator_l00_light_2); g_sheepinator_l00_light_2=-1; }
    index=g_sheepinator_l00_sound_2;
    if (index>=0) {
        if (index!=-1 && ((Voice *)(g_sound_state+index*112))->owner==morphoray && ((Voice *)(g_sound_state+index*112))->playing) snd_stop_voice(index);
        g_sheepinator_l00_sound_2=-1;
    }
    if (B(morphoray,0x60)&2) anim_start_blended_with_flags(morphoray,1,0,1,0);
    }
    }
    if (special && g_sheepinator_l00_light_2>=0) { gfx_free_point_light(g_sheepinator_l00_light_2); g_sheepinator_l00_light_2=-1; }
}
