#include "names.h"
/* func_PAL_L03_003F5090, the PAL copy of func_L03_003F09C0: the same C, where each frame count
 * goes through the 50 Hz scale and its limits fall by a sixth. The scale divides by a register,
 * so its zero test stays wherever the division itself is reused: both `prev < scale` arms keep
 * two tests, which is why neither timer holds the scaled value in a local as USA's does.
 *
 * Its own unit: -G8 for the $gp-relative words and -frac2-zero-ti-por (config/cflags.txt) for
 * the local quadword clear, which retail keeps as `por` + `sq`.
 *
 * Two timers decide the shape of the help tests. `scaled - prev > 100` tests the long arm first:
 * the arm's cross-jumped tail then ends in a jump to a label where v0 is live, so reorg annuls
 * the `bnel` slot. The history[138] test is `!count && near`, else the timer, as near's failure
 * reaches the timer test in retail.
 */
#include "common.h"

typedef struct {
    u8 prefix[0x80]; float position[4];
    u8 pad90[0x128]; int field1B8;
    u8 pad1BC[0x20D8]; int field2294;
    u8 pad2298[0x1C]; u8 field22B4;
} Hero;
extern Hero g_hero_state;
typedef union {
    u8 bytes[0xA3];
    struct { u8 pad[0x78]; unsigned char bit0:1; unsigned char other:7; } bits;
} Flags;
extern Flags g_game_flag_table;
typedef struct { u8 pad00[0x70]; u32 field70; u8 pad74[0x7C]; u16 fieldF0; u16 padF2; u32 fieldF4; } HelpState;
extern HelpState g_progress_statistics;
/* Subtitle history records: count, last frame, and per-level flags. */
typedef struct { u16 count, pad; u32 time, levels; } SubtitleHistory;
extern SubtitleHistory g_subtitle_history[];
typedef struct {
    int active; u8 pad04[0x20]; int key; int type;
} VoiceState;
extern VoiceState g_help_voice_state;
extern u8 g_str_clank_scene_key[];
extern u8 *g_linked_effect_records[] __attribute__((sda));
extern u8 *g_moby_record_base[] __attribute__((sda));
extern u16 *g_entity_id_lists[];
extern int g_object_group_count __attribute__((sda));
extern int g_help_voice_draw_flag __attribute__((sda));
extern u32 g_frame_counter[] __attribute__((sda));
extern int g_current_map_index;
extern int g_frame_l03_counter __attribute__((nosda));
/* The published map identifies the persistent save block at this base. */
typedef struct { u8 pad00[0x12]; u8 field12; u8 pad13[0xFA]; u8 map_data_set; u8 pad10E[0xD804 - 0x10E]; } PlayerProgress;
extern PlayerProgress g_player_bolts __attribute__((sda));
extern u8 g_help_voice_suppress_flags[] __attribute__((sda));
extern void state_set_flag_one(void);
extern void hero_reset_position_and_direction_pal(void *,void *,int,int);
extern int moby_handle_request_slot_state(int);
extern void moby_mark_spawned(void *);
extern void moby_set_state(void *,int,int);
extern int IsPointInCuboid(void *,int);
extern int req_push_queue(void *,int);
extern int req_launch_queued(void *);
extern void game_set_stored_value_pair(void *,void *);
extern void endako_boss_start_area_objects_pal(void *);
extern int math_fast_float_d(void *);
extern int subtitle_request_voice_line_pal(int,int);
extern void subtitle_begin_close(void);
extern void trigger_subtitle_in_cuboid_pal(int,int,int,int,int);
extern float fast_vec_dist(void *,void *);
extern int level_count_active_entries(void);
extern void gfx_add_draw_callback_first(void *,void *);
extern void blast_call_helper_no_args(void *);
#define I(p,n) (*(int *)((p)+(n)))
/* Endako help voice: on start, sets up the area objects; each frame, plays the right help line
   when the hero is in one of the trigger boxes, with the timing limits scaled for 50 Hz. */
void endako_help_voice_update_pal(u8 *entity) {
    u8 *state = *(u8 **)(entity+0x68);
    int mode = entity[0x20];
    u16 *id_list;
    u8 *record;
    union { float f[4]; unsigned int q __attribute__((mode(TI))); } point;
    switch (mode) {
    case 0:
        entity[0x30] = 0xFF;
        I(state,0x74) = 0;
        if (g_player_bolts.map_data_set) {
            if (!g_game_flag_table.bytes[0xD]) {
                u8 *entry;
                state_set_flag_one();
                entry = g_linked_effect_records[0] + I(state,0x70)*0x80;
                hero_reset_position_and_direction_pal(entry+0x30,entry+0x70,0,1);
                moby_handle_request_slot_state(13);
            }
            if (g_player_bolts.map_data_set) {
                for(id_list=g_entity_id_lists[I(state,0x80)];
                    (I(state,0x80)&255)!=255 && I(state,0x80)<=g_object_group_count && id_list &&
                    ((id_list != 0 && (short)id_list[-1]>=0) || id_list==g_entity_id_lists[I(state,0x80)]); id_list++) {
                    record = g_moby_record_base[0] + ((*id_list&0x7fff)<<8);
                    if(!record) break;
                    moby_mark_spawned(record);
                }
            }
        }
        moby_set_state(entity,1,-1);
        break;
    case 1:
        if (!g_game_flag_table.bytes[0xD] && IsPointInCuboid(g_hero_state.position,I(state,0x6C)))
            g_game_flag_table.bytes[0xD] = mode;
        if (!g_game_flag_table.bytes[9] && IsPointInCuboid(g_hero_state.position,I(state,0x4C)) && req_push_queue(g_str_clank_scene_key,0x34)) {
            req_launch_queued(g_str_clank_scene_key);
            g_game_flag_table.bytes[9]=1;
            game_set_stored_value_pair(endako_boss_start_area_objects_pal,entity);
        }
        if (!g_hero_state.field22B4 && IsPointInCuboid(g_hero_state.position,I(state,8))) {
            if (math_fast_float_d(state+0x60)) {
                subtitle_request_voice_line_pal(0x9CB,0x22);
                I(state,0x60)=500;
            }
        } else if (IsPointInCuboid(g_hero_state.position,I(state,0xC))) {
            if(g_subtitle_history[34].count!=65535) {
                g_subtitle_history[34].count=65535;
                if (g_help_voice_state.active || g_help_voice_state.key!=-1) {
                    if (g_help_voice_state.type==0x22) subtitle_begin_close();
                }
            }
        }
        if(IsPointInCuboid(g_hero_state.position,I(state,0x10)) && !g_help_voice_state.active && g_help_voice_state.key==-1) {
            u32 prev = g_subtitle_history[35].time;
            if (((s32)g_frame_counter[0] * 5 + 2) / 6 - prev > 100) {
                subtitle_request_voice_line_pal(0x9CC,0x23);
                if (g_subtitle_history[35].time < ((s32)g_frame_counter[0] * 5 + 2) / 6) g_subtitle_history[35].time = ((s32)g_frame_counter[0] * 5 + 2) / 6;
            } else {
                if (prev < ((s32)g_frame_counter[0] * 5 + 2) / 6) g_subtitle_history[35].time = ((s32)g_frame_counter[0] * 5 + 2) / 6;
            }
        } else if(IsPointInCuboid(g_hero_state.position,I(state,0x14))) {
            if(g_subtitle_history[35].count!=65535) {
                g_subtitle_history[35].count=65535;
                if(g_help_voice_state.active || g_help_voice_state.key!=-1) subtitle_begin_close();
            }
        }
        if(IsPointInCuboid(g_hero_state.position,I(state,0x18))) {
            if(((s32)g_frame_counter[0] * 5 + 2) / 6-g_subtitle_history[36].time>2000) subtitle_request_voice_line_pal(0x9CD,0x24);
        } else if(IsPointInCuboid(g_hero_state.position,I(state,0x1C))) {
            g_game_flag_table.bytes[0xA2]=1;
            g_subtitle_history[36].count=65535;
            if(g_help_voice_state.active || g_help_voice_state.key!=-1) subtitle_begin_close();
        }
        if(IsPointInCuboid(g_hero_state.position,I(state,0x64)) && !g_subtitle_history[123].count) {
            g_game_flag_table.bytes[0xA2]=1;
            subtitle_request_voice_line_pal(0xA24,0x7B);
        }
        trigger_subtitle_in_cuboid_pal(0x9D3,0x2A,0,I(state,0x20),-1);
        if(IsPointInCuboid(g_hero_state.position,I(state,0x24)) && ((g_game_flag_table.bytes[0x78] ^ 1) & 1)) {
            u32 prev=g_subtitle_history[131].time;
            if(((s32)g_frame_counter[0] * 5 + 2) / 6-prev>900 || !prev) subtitle_request_voice_line_pal(0xA2C,0x83);
            else if(prev<((s32)g_frame_counter[0] * 5 + 2) / 6) g_subtitle_history[131].time=((s32)g_frame_counter[0] * 5 + 2) / 6;
        }
        trigger_subtitle_in_cuboid_pal(0x9D5,0x2C,0,I(state,0x40),-1);
        trigger_subtitle_in_cuboid_pal(0x9E5,0x3C,2,I(state,0x54),-1);
        if(IsPointInCuboid(g_hero_state.position,I(state,0x2C))) g_subtitle_history[43].count=65535;
        else if(IsPointInCuboid(g_hero_state.position,I(state,0x28))) {
            if(g_hero_state.field2294==0x23 && g_hero_state.field1B8==1) ++I(state,0x30);
            if(I(state,0x30)>=3 && g_hero_state.field2294==0x23) subtitle_request_voice_line_pal(0x9D4,0x2B);
        }
        if(g_hero_state.position[2]<155.5f) {
            point.q = 0;
            point.f[0]=400.0f;
            point.f[1]=222.0f;
            point.f[2]=155.0f;
            if(fast_vec_dist(g_hero_state.position,point.f)<24.0f) g_subtitle_history[37].time=0;
        }
        trigger_subtitle_in_cuboid_pal(0x9CE,0x25,1,I(state,0x28),I(state,0x2C));
        trigger_subtitle_in_cuboid_pal(0x9CE,0x25,3,I(state,0x28),I(state,0x2C));
        if(IsPointInCuboid(g_hero_state.position,I(state,0x7C))) {
            if(!g_progress_statistics.fieldF0 || ((s32)g_frame_counter[0] * 5 + 2) / 6-g_progress_statistics.fieldF4>60000) {
                u32 seen = g_subtitle_history[32].levels & (1 << g_current_map_index);
                if (!seen) subtitle_request_voice_line_pal(0x9C9,0x20);
            }
        }
        if(!g_player_bolts.field12 && g_frame_l03_counter>0 && !(g_frame_l03_counter&0x7F) && !g_help_voice_suppress_flags[0] && !level_count_active_entries()) {
            u32 count = g_subtitle_history[138].count;
            if (count < 3) {
                if (!count && IsPointInCuboid(g_hero_state.position,I(state,0x78))) subtitle_request_voice_line_pal(0xA33,0x8A);
                else if (((s32)g_frame_counter[0] * 5 + 2) / 6 - g_subtitle_history[138].time > 30000) subtitle_request_voice_line_pal(0xA33,0x8A);
            }
        }
        if(((s32)g_frame_counter[0] * 5 + 2) / 6-g_progress_statistics.field70>90000 && IsPointInCuboid(g_hero_state.position,I(state,0x78))) {
            u32 seen = g_subtitle_history[12].levels & (1 << g_current_map_index);
            if (!seen) subtitle_request_voice_line_pal(0x9B5,0xC);
        }
        break;
    }
    if(g_help_voice_draw_flag) gfx_add_draw_callback_first(blast_call_helper_no_args,entity);
}
