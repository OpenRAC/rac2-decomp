#include "common.h"
typedef struct {
    u8 pad00[0x20]; u8 state; u8 pad21[0x68-0x21];
    void *data; u8 pad6c[0xB0-0x6c]; u8 id; u8 padB1;
    s16 index; u8 padB4[0x100-0xB4];
} TaboraMoby;
extern TaboraMoby *D_L08_001B29DC;
extern u8 D_001395B8[], g_item_slot_to_record[];
typedef struct { u8 pad[0x50]; int flags[2]; } TaboraProgress;
extern TaboraProgress D_00139768;
typedef struct { int state; u8 pad[0x24]; float value; } FlareStatus;
extern FlareStatus D_L08_001CA080;
typedef struct { u8 pad[4]; u8 count; u8 rest[0xDB]; } StageStatus;
extern u8 D_L08_0026CCF0[];
typedef struct { u8 pad[0x464]; u8 flags[1]; } TaboraLevelFlags;
extern TaboraLevelFlags D_L08_0021EAF0, D_L08_0021DE80;
extern u8 D_0019B2E8[], D_0019B4A8[], D_0019B278[];
extern u8 D_L08_001B2840[] MACRO_ADDR;
extern int g_current_map_index, D_0018CD20 NOT_SDA;
extern float D_00189EA8 NOT_SDA;
extern u8 g_item_owned_flags[] __attribute__((sda));
extern int D_L08_0021F758 NOT_SDA, D_L08_001A8F00, D_L08_001B2514;
extern float D_L08_001B2420 __attribute__((sda));
extern float D_L08_001B9E08 NOT_SDA;
extern char D_L08_001BFD00[], g_hero_position[];
extern char D_L08_002B53E0[], D_L08_001B0BE8[], D_L08_001B0C00[], D_L08_001B0C28[], D_L08_001B0C50[], D_L08_001B0C70[], D_L08_001B0C90[], D_L08_001B0CC0[], D_L08_001B0CF0[], D_L08_001B0D08[], D_L08_001B0D30[], D_L08_001B0D48[], D_L08_001B0D70[], D_L08_001B0DA8[];
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
    if (((StageStatus *)D_L08_0026CCF0)[g_item_slot_to_record[0xA]].count >= threshold) return 1;
    return 0;
}

/* Per-frame update of the level's progress controller moby (class 3114): checks which goals are done, plays the talk lines, moves between states and retires its helper mobys. */
void tabora_progress_update(u8 *moby)
{
    u8 *vars = *(u8 **)(moby+0x68);
    TaboraMoby *other;
    int mode;
    int bits;
    unsigned int seen;
    switch ((u8)moby[0x20]) {
    case 0:
        moby[0x30]=255;
        *(u16 *)(moby+0x96)=0;
        if (!D_001395B8[0x1C]) state_set_flag_one();
        if (*(int *)(vars+4)!=-1 && D_00189EA8 < D_L08_001CA080.value) {
            other=(D_L08_001B29DC+*(int *)(vars+4));
            if (other->state || (D_0019B2E8[other->id+(g_current_map_index<<4)]&128) ||
                D_L08_0021EAF0.flags[other->index])
                goto relocate_child;
            bits = D_0019B4A8[(other->index>>1)+(g_current_map_index<<10)];
            if (((u16)other->index & 1) ? ((bits >> 4) & 7) : (bits & 7)) {
relocate_child:
                STUB_printf(D_L08_002B53E0);
                hero_reset_position_and_direction((u8 *)other+0x10,(u8 *)other+0xF0,0,1);
                moby_set_state(moby,5,-1);
            }
        }
        if (TaboraStageComplete()) {
            if (*(int *)(vars+0x30)!=-1) {
                moby_mark_spawned((D_L08_001B29DC+*(int *)(vars+0x30)));
                *(int *)(vars+0x30)=-1;
            }
            if (D_00189EA8 < D_L08_001CA080.value) {
                mode=0;
                STUB_printf(D_L08_001B0BE8);
                D_L08_0021F758=0;
                state_set_flag_one();
                moby_set_state(moby,5,-1);
            } else {
                mode=1;
                STUB_printf(D_L08_001B0C00);
                D_L08_0021F758=mode;
                moby_set_state(moby,5,-1);
            }
            moby_replace_tracked(moby);
        } else if (!(D_00139768.flags[0]&0x80000) || !(D_00139768.flags[1]&0x100000)) {
            mode=1;
            STUB_printf(D_L08_001B0C28);
            if (req_push_queue(D_L08_001BFD00,0x53)) {
                req_push_queue(D_L08_001BFD00,0x54);
                req_launch_queued(D_L08_001BFD00);
                game_set_slowdown_factor();
                state_set_flag_one();
                moby_set_state(moby,1,-1);
            }
        } else if (D_00139768.flags[1]&0x200000) {
            mode=0;
            STUB_printf(D_L08_001B0C50);
            D_L08_0021F758=0;
            state_set_flag_one();
            moby_set_state(moby,3,-1);
        } else {
            mode=0;
            STUB_printf(D_L08_001B0C70);
            state_set_flag_one();
            moby_set_state(moby,1,-1);
            *(u16 *)(moby+0x96)=6;
        }
        if (g_item_owned_flags[0x15] && *(int *)(vars+0x20)!=-1 &&
            (D_L08_001B29DC+*(int *)(vars+0x20))->state!=0xFE &&
            (D_L08_001B29DC+*(int *)(vars+0x20))->state!=0xFD &&
            *(int *)(vars+0x24)!=-1 &&
            (D_L08_001B29DC+*(int *)(vars+0x24))->state!=0xFE &&
            (D_L08_001B29DC+*(int *)(vars+0x24))->state!=0xFD) {
            STUB_printf(D_L08_001B0C90);
            if (!D_0019B278[*(int *)D_L08_001B29DC[*(int *)(vars+0x24)].data+(g_current_map_index<<2)]) {
                mode=1;
                D_L08_0021F758=mode;
                STUB_printf(D_L08_001B0CC0);
                {
                    TaboraMoby *replacement = D_L08_001B29DC + *(int *)(vars+0x20);
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
        STUB_printf(D_L08_001B0CF0,mode);
        load_scene_chunk(mode,0);
        moby_set_far_target_point(moby);
        part_start_sparkle_burst(moby);
        break;
    case 1:
        if (!game_is_either_mode_two() && *(u16 *)(moby+0x96)>=6) {
            D_001395B8[0x19]=1;
            if (req_push_queue(D_L08_001BFD00,0x55)) {
                req_launch_queued(D_L08_001BFD00);
                D_L08_0021F758=0;
                STUB_printf(D_L08_001B0D08);
                game_set_slowdown_factor();
                D_L08_001B2514=1;
                D_L08_001B2420=1.2f;
                moby_disable_object_list_flags();
                load_scene_chunk(0,0);
                moby_set_state(moby,2,-1);
            }
        }
        break;
    case 2:
        if (!game_is_either_mode_two() && *(u16 *)(moby+0x96)>=6) {
            D_001395B8[0x1A]=1;
            STUB_printf(D_L08_001B0D30);
            MemcardSave(0,-1);
            moby_set_state(moby,3,-1);
        }
        break;
    case 3:
        if (coll_point_inside_region(g_hero_position,*(int *)vars)) {
            if (req_push_queue(D_L08_001BFD00,0x56)) {
                req_launch_queued(D_L08_001BFD00);
                STUB_printf(D_L08_001B0D48);
                moby_set_state(moby,4,-1);
            }
        }
        break;
    case 4:
        if (D_L08_001A8F00==2 && *(int *)(vars+0x30)!=-1) {
            moby_mark_spawned((D_L08_001B29DC+*(int *)(vars+0x30)));
            *(int *)(vars+0x30)=-1;
        }
        if (!game_is_either_mode_two() && *(u16 *)(moby+0x96)>=6) {
            if (flag_is_byte_set()) menu_seek_chain_entry(10,4);
            else menu_seek_chain_entry(10,1);
            gfx_run_screen_update_steps(1);
            help_show_message_for_id(10);
            moby_replace_tracked(moby);
            if (*(int *)(vars+8)!=-1) {
                other=D_L08_001B29DC + *(int *)(vars+8);
                STUB_printf(D_L08_001B0D70);
                D_L08_0021DE80.flags[other->index]=other->id+2;
                {
                    int id = other->id;
                    if (id == 255 || (!(D_L08_001B2840[(u8)id] & 128) &&
                        (D_0019B2E8[(u8)id + (g_current_map_index << 4)] & 128)))
                        D_L08_0021EAF0.flags[other->index]=id+2;
                }
            }
            STUB_printf(D_L08_001B0DA8);
            MemcardSave(0,-1);
            moby_set_state(moby,5,-1);
        }
        break;
    }
    ++*(u16 *)(moby+0x96);
    if (D_001395B8[0x1C]) {
        seen = (unsigned)D_0018CD20 & (1 << g_current_map_index);
        if (!seen) subtitle_request_voice_line(0x9F9,0x50);
    }
    TriggerSubtitleInCuboid(0xA3A,0x91,0,*(int *)(vars+0xC),-1);
    if (D_L08_001CA080.state==1) {
        D_L08_001B9E08=level_get_height_map_ground(moby);
        gfx_add_draw_callback_first(gfx_l08_draw_lens_flare,moby);
    }
}
