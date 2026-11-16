/* func_PAL_L08_003FB594, the PAL copy of func_L08_003F6E18: the same C, with the block on the hero
 * before the D_L08_001CA080.state test added and the hero struct base moved. */
#include "common.h"
typedef struct {
    u8 pad00[0x20]; u8 state; u8 pad21[0x68-0x21];
    void *data; u8 pad6c[0xB0-0x6c]; u8 id; u8 padB1;
    s16 index; u8 padB4[0x100-0xB4];
} TaboraMoby;
extern TaboraMoby *g_moby_array;
/* D_00139568_1 is D_00139568. gcse hashes a symbol's spelling, and the two PRE base registers in
 * TaboraStageComplete tie at global priority, so their pseudo order depends on this name. */
extern u8 g_game_flag_table[], D_00139568_1[];
typedef struct { u8 pad[0x50]; int flags[2]; } TaboraProgress;
extern TaboraProgress g_request_flag_table;
typedef struct { int state; u8 pad[0x24]; float value; } FlareStatus;
extern FlareStatus g_init_context;
typedef struct { u8 pad[4]; u8 count; u8 rest[0xDB]; } StageStatus;
extern u8 g_item_stage_records[];
typedef struct { u8 pad[0x464]; u8 flags[1]; } TaboraLevelFlags;
extern TaboraLevelFlags g_moby_spawn_state_flags_b, g_moby_spawn_state_flags_a;
extern u8 g_moby_group_flags[], g_moby_nibble_table[], g_level_progress_flags[];
extern u8 g_moby_state_flags[] MACRO_ADDR;
extern int g_current_map_index, g_tabora_seen_mask NOT_SDA;
typedef struct {
    u8 pad00[0x88]; float value;
    u8 pad8C[0x1830-0x8C]; u8 *object;
    u8 pad1834[0x2294-0x1834]; int state;
} Hero;
extern Hero g_hero_state;
extern int g_voice_line_trigger_flag NOT_SDA;
extern float g_level_pair_scale;
extern void level_store_pair_with_increment(int,int);
extern u8 g_item_owned_flags[] __attribute__((sda));
extern int g_tabora_progress_mode NOT_SDA, g_cutscene_l08_active_flag, g_tabora_progress_flag;
extern float g_tabora_float_param __attribute__((sda));
extern float g_tabora_ground_height NOT_SDA;
extern char g_request_l08_queue[], g_hero_position[];
extern char g_str_tabora_debug[], g_str_tabora_progress_first[], g_str_tabora_progress_second[], g_str_tabora_progress_third[], g_str_tabora_progress_fourth[], g_str_tabora_progress_fifth[], g_str_tabora_progress_sixth[], g_str_tabora_progress_seventh[], g_str_tabora_progress_mode[], g_str_tabora_progress_eighth[], g_str_tabora_progress_ninth[], g_str_tabora_progress_tenth[], g_str_tabora_progress_eleventh[], g_str_tabora_progress_twelfth[];
extern void STUB_printf(char *, ...);
extern void hero_reset_position_and_direction(void *,void *,int,int);
extern void gfx_add_draw_callback_first(void *,void *);
extern int menu_seek_chain_entry(int,int);
extern void help_show_message_for_id(int);
extern int req_push_queue(void *,int);
extern int req_launch_queued(void *);
extern int flag_is_byte_set(void);
extern int subtitle_request_voice_line(int,int);
extern void TriggerSubtitleInCuboid(int,int,int,int,int);
extern void gfx_run_screen_update_steps(int);
extern void load_scene_chunk(int,int);
extern int MemcardSave(int,int);
extern void moby_mark_spawned(void *);
extern void moby_set_state(void *,int,int);
extern int coll_point_inside_region(void *,int);
extern void moby_disable_object_list_flags(void);
extern void state_set_flag_one(void);
extern void game_set_slowdown_factor(void);
extern int game_is_either_mode_two(void);
extern void moby_replace_tracked(void *);
extern float level_get_height_map_ground(void *);
extern void part_start_sparkle_burst(void *);
extern void moby_set_far_target_point(void *);
extern void gfx_l08_draw_lens_flare(void *);

static __inline__ int TaboraStageComplete(void)
{
    int threshold;
    if (flag_is_byte_set()) threshold = 4;
    else threshold = 1;
    if (((StageStatus *)g_item_stage_records)[D_00139568_1[0xA]].count >= threshold) return 1;
    return 0;
}

/* Per-frame update of the level's progress controller moby (class 3114): checks which goals are done, plays the talk lines, moves between states and retires its helper mobys (PAL version). */
void tabora_progress_update_pal(u8 *moby)
{
    u8 *state = *(u8 **)(moby+0x68);
    TaboraMoby *other_moby;
    int mode;
    int bits;
    unsigned int seen;
    switch ((u8)moby[0x20]) {
    case 0:
        moby[0x30]=255;
        *(u16 *)(moby+0x96)=0;
        if (!g_game_flag_table[0x1C]) state_set_flag_one();
        if (*(int *)(state+4)!=-1 && g_hero_state.value < g_init_context.value) {
            other_moby=(g_moby_array+*(int *)(state+4));
            if (other_moby->state || (g_moby_group_flags[other_moby->id+(g_current_map_index<<4)]&128) ||
                g_moby_spawn_state_flags_b.flags[other_moby->index])
                goto relocate_child;
            bits = g_moby_nibble_table[(other_moby->index>>1)+(g_current_map_index<<10)];
            if (((u16)other_moby->index & 1) ? ((bits >> 4) & 7) : (bits & 7)) {
relocate_child:
                STUB_printf(g_str_tabora_debug);
                hero_reset_position_and_direction((u8 *)other_moby+0x10,(u8 *)other_moby+0xF0,0,1);
                moby_set_state(moby,5,-1);
            }
        }
        if (TaboraStageComplete()) {
            if (*(int *)(state+0x30)!=-1) {
                moby_mark_spawned((g_moby_array+*(int *)(state+0x30)));
                *(int *)(state+0x30)=-1;
            }
            if (g_hero_state.value < g_init_context.value) {
                mode=0;
                STUB_printf(g_str_tabora_progress_first);
                g_tabora_progress_mode=0;
                state_set_flag_one();
                moby_set_state(moby,5,-1);
            } else {
                mode=1;
                STUB_printf(g_str_tabora_progress_second);
                g_tabora_progress_mode=mode;
                moby_set_state(moby,5,-1);
            }
            moby_replace_tracked(moby);
        } else if (!(g_request_flag_table.flags[0]&0x80000) || !(g_request_flag_table.flags[1]&0x100000)) {
            mode=1;
            STUB_printf(g_str_tabora_progress_third);
            if (req_push_queue(g_request_l08_queue,0x53)) {
                req_push_queue(g_request_l08_queue,0x54);
                req_launch_queued(g_request_l08_queue);
                game_set_slowdown_factor();
                state_set_flag_one();
                moby_set_state(moby,1,-1);
            }
        } else if (g_request_flag_table.flags[1]&0x200000) {
            mode=0;
            STUB_printf(g_str_tabora_progress_fourth);
            g_tabora_progress_mode=0;
            state_set_flag_one();
            moby_set_state(moby,3,-1);
        } else {
            mode=0;
            STUB_printf(g_str_tabora_progress_fifth);
            state_set_flag_one();
            moby_set_state(moby,1,-1);
            *(u16 *)(moby+0x96)=6;
        }
        if (g_item_owned_flags[0x15] && *(int *)(state+0x20)!=-1 &&
            (g_moby_array+*(int *)(state+0x20))->state!=0xFE &&
            (g_moby_array+*(int *)(state+0x20))->state!=0xFD &&
            *(int *)(state+0x24)!=-1 &&
            (g_moby_array+*(int *)(state+0x24))->state!=0xFE &&
            (g_moby_array+*(int *)(state+0x24))->state!=0xFD) {
            STUB_printf(g_str_tabora_progress_sixth);
            if (!g_level_progress_flags[*(int *)g_moby_array[*(int *)(state+0x24)].data+(g_current_map_index<<2)]) {
                mode=1;
                g_tabora_progress_mode=mode;
                STUB_printf(g_str_tabora_progress_seventh);
                {
                    TaboraMoby *replacement = g_moby_array + *(int *)(state+0x20);
                    hero_reset_position_and_direction((u8 *)replacement+0x10,(u8 *)replacement+0xF0,0,1);
                }
                state_set_flag_one();
            }
            if (TaboraStageComplete()) {
                if (flag_is_byte_set()) menu_seek_chain_entry(10,4);
                else menu_seek_chain_entry(10,1);
                gfx_run_screen_update_steps(1);
            }
            moby_set_state(moby,5,-1);
        }
        STUB_printf(g_str_tabora_progress_mode,mode);
        load_scene_chunk(mode,0);
        moby_set_far_target_point(moby);
        part_start_sparkle_burst(moby);
        break;
    case 1:
        if (!game_is_either_mode_two() && *(u16 *)(moby+0x96)>=6) {
            g_game_flag_table[0x19]=1;
            if (req_push_queue(g_request_l08_queue,0x55)) {
                req_launch_queued(g_request_l08_queue);
                g_tabora_progress_mode=0;
                STUB_printf(g_str_tabora_progress_eighth);
                game_set_slowdown_factor();
                g_tabora_progress_flag=1;
                g_tabora_float_param=1.2f;
                moby_disable_object_list_flags();
                load_scene_chunk(0,0);
                moby_set_state(moby,2,-1);
            }
        }
        break;
    case 2:
        if (!game_is_either_mode_two() && *(u16 *)(moby+0x96)>=6) {
            g_game_flag_table[0x1A]=1;
            STUB_printf(g_str_tabora_progress_ninth);
            MemcardSave(0,-1);
            moby_set_state(moby,3,-1);
        }
        break;
    case 3:
        if (coll_point_inside_region(g_hero_position,*(int *)state)) {
            if (req_push_queue(g_request_l08_queue,0x56)) {
                req_launch_queued(g_request_l08_queue);
                STUB_printf(g_str_tabora_progress_tenth);
                moby_set_state(moby,4,-1);
            }
        }
        break;
    case 4:
        if (g_cutscene_l08_active_flag==2 && *(int *)(state+0x30)!=-1) {
            moby_mark_spawned((g_moby_array+*(int *)(state+0x30)));
            *(int *)(state+0x30)=-1;
        }
        if (!game_is_either_mode_two() && *(u16 *)(moby+0x96)>=6) {
            if (flag_is_byte_set()) menu_seek_chain_entry(10,4);
            else menu_seek_chain_entry(10,1);
            gfx_run_screen_update_steps(1);
            help_show_message_for_id(10);
            moby_replace_tracked(moby);
            if (*(int *)(state+8)!=-1) {
                other_moby=g_moby_array + *(int *)(state+8);
                STUB_printf(g_str_tabora_progress_eleventh);
                g_moby_spawn_state_flags_a.flags[other_moby->index]=other_moby->id+2;
                {
                    int id = other_moby->id;
                    if (id == 255 || (!(g_moby_state_flags[(u8)id] & 128) &&
                        (g_moby_group_flags[(u8)id + (g_current_map_index << 4)] & 128)))
                        g_moby_spawn_state_flags_b.flags[other_moby->index]=id+2;
                }
            }
            STUB_printf(g_str_tabora_progress_twelfth);
            MemcardSave(0,-1);
            moby_set_state(moby,5,-1);
        }
        break;
    }
    ++*(u16 *)(moby+0x96);
    if (g_game_flag_table[0x1C]) {
        seen = (unsigned)g_tabora_seen_mask & (1 << g_current_map_index);
        if (!seen) subtitle_request_voice_line(0x9F9,0x50);
    }
    TriggerSubtitleInCuboid(0xA3A,0x91,0,*(int *)(state+0xC),-1);
    if (g_hero_state.state==0x31 && g_hero_state.object && *(s16 *)(g_hero_state.object+0xAA)==0xEEF) {
        if (g_voice_line_trigger_flag>=0) subtitle_request_voice_line(0xA40,0x97);
        {
            float k = -65.0f;
            level_store_pair_with_increment((int)(g_level_pair_scale * k + 0.5f),2);
        }
    }
    if (g_init_context.state==1) {
        g_tabora_ground_height=level_get_height_map_ground(moby);
        gfx_add_draw_callback_first(gfx_l08_draw_lens_flare,moby);
    }
}
