/* func_US2_L08_003F82AC, the USA v2.00 copy of func_L08_003F6E18: the same C, where the 0x88 float
   is read as a member of D_00189E20 and a block runs after func_L01_002EABA8 while the mode word is
   0x31 and the level's object is class 0xEEF. D_00139568_1 is D_00139568: gcse numbers its reaching
   registers by a hash of the symbol's name, and the tied $s4/$s5 pair follows that order. */
#include "common.h"
typedef struct {
    u8 pad00[0x20]; u8 state; u8 pad21[0x68-0x21];
    void *data; u8 pad6c[0xB0-0x6c]; u8 id; u8 padB1;
    s16 index; u8 padB4[0x100-0xB4];
} TaboraMoby;
extern TaboraMoby *D_L08_001B29DC;
extern u8 D_001395B8[], D_00139568_1[];
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
extern void level_store_pair_with_increment(int,int);
typedef struct { u8 pad[0x88]; float value; u8 pad8c[0x1830-0x8C]; u8 *object; u8 pad1834[0x2294-0x1834]; int mode; } LevelGlobals;
extern LevelGlobals g_hero_state;
extern int D_0018D074 NOT_SDA;
extern float D_L08_001B3244;

static __inline__ int TaboraStageComplete(void)
{
    int threshold;
    if (flag_is_byte_set()) threshold = 4;
    else threshold = 1;
    if (((StageStatus *)D_L08_0026CCF0)[D_00139568_1[0xA]].count >= threshold) return 1;
    return 0;
}

void func_US2_L08_003F82AC(u8 *o)
{
    u8 *s = *(u8 **)(o+0x68);
    TaboraMoby *p;
    int mode;
    int bits;
    unsigned int seen;
    switch ((u8)o[0x20]) {
    case 0:
        o[0x30]=255;
        *(u16 *)(o+0x96)=0;
        if (!D_001395B8[0x1C]) state_set_flag_one();
        if (*(int *)(s+4)!=-1 && g_hero_state.value < D_L08_001CA080.value) {
            p=(D_L08_001B29DC+*(int *)(s+4));
            if (p->state || (D_0019B2E8[p->id+(g_current_map_index<<4)]&128) ||
                D_L08_0021EAF0.flags[p->index])
                goto relocate_child;
            bits = D_0019B4A8[(p->index>>1)+(g_current_map_index<<10)];
            if (((u16)p->index & 1) ? ((bits >> 4) & 7) : (bits & 7)) {
relocate_child:
                STUB_printf(D_L08_002B53E0);
                hero_reset_position_and_direction((u8 *)p+0x10,(u8 *)p+0xF0,0,1);
                moby_set_state(o,5,-1);
            }
        }
        if (TaboraStageComplete()) {
            if (*(int *)(s+0x30)!=-1) {
                moby_mark_spawned((D_L08_001B29DC+*(int *)(s+0x30)));
                *(int *)(s+0x30)=-1;
            }
            if (g_hero_state.value < D_L08_001CA080.value) {
                mode=0;
                STUB_printf(D_L08_001B0BE8);
                D_L08_0021F758=0;
                state_set_flag_one();
                moby_set_state(o,5,-1);
            } else {
                mode=1;
                STUB_printf(D_L08_001B0C00);
                D_L08_0021F758=mode;
                moby_set_state(o,5,-1);
            }
            moby_replace_tracked(o);
        } else if (!(D_00139768.flags[0]&0x80000) || !(D_00139768.flags[1]&0x100000)) {
            mode=1;
            STUB_printf(D_L08_001B0C28);
            if (req_push_queue(D_L08_001BFD00,0x53)) {
                req_push_queue(D_L08_001BFD00,0x54);
                req_launch_queued(D_L08_001BFD00);
                game_set_slowdown_factor();
                state_set_flag_one();
                moby_set_state(o,1,-1);
            }
        } else if (D_00139768.flags[1]&0x200000) {
            mode=0;
            STUB_printf(D_L08_001B0C50);
            D_L08_0021F758=0;
            state_set_flag_one();
            moby_set_state(o,3,-1);
        } else {
            mode=0;
            STUB_printf(D_L08_001B0C70);
            state_set_flag_one();
            moby_set_state(o,1,-1);
            *(u16 *)(o+0x96)=6;
        }
        if (g_item_owned_flags[0x15] && *(int *)(s+0x20)!=-1 &&
            (D_L08_001B29DC+*(int *)(s+0x20))->state!=0xFE &&
            (D_L08_001B29DC+*(int *)(s+0x20))->state!=0xFD &&
            *(int *)(s+0x24)!=-1 &&
            (D_L08_001B29DC+*(int *)(s+0x24))->state!=0xFE &&
            (D_L08_001B29DC+*(int *)(s+0x24))->state!=0xFD) {
            STUB_printf(D_L08_001B0C90);
            if (!D_0019B278[*(int *)D_L08_001B29DC[*(int *)(s+0x24)].data+(g_current_map_index<<2)]) {
                mode=1;
                D_L08_0021F758=mode;
                STUB_printf(D_L08_001B0CC0);
                {
                    TaboraMoby *replacement = D_L08_001B29DC + *(int *)(s+0x20);
                    hero_reset_position_and_direction((u8 *)replacement+0x10,(u8 *)replacement+0xF0,0,1);
                }
                state_set_flag_one();
            }
            if (TaboraStageComplete()) {
                if (flag_is_byte_set()) menu_seek_chain_entry(10,4);
                else menu_seek_chain_entry(10,1);
                gfx_run_screen_update_steps(1);
            }
            moby_set_state(o,5,-1);
        }
        STUB_printf(D_L08_001B0CF0,mode);
        load_scene_chunk(mode,0);
        moby_set_far_target_point(o);
        part_start_sparkle_burst(o);
        break;
    case 1:
        if (!game_is_either_mode_two() && *(u16 *)(o+0x96)>=6) {
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
                moby_set_state(o,2,-1);
            }
        }
        break;
    case 2:
        if (!game_is_either_mode_two() && *(u16 *)(o+0x96)>=6) {
            D_001395B8[0x1A]=1;
            STUB_printf(D_L08_001B0D30);
            MemcardSave(0,-1);
            moby_set_state(o,3,-1);
        }
        break;
    case 3:
        if (coll_point_inside_region(g_hero_position,*(int *)s)) {
            if (req_push_queue(D_L08_001BFD00,0x56)) {
                req_launch_queued(D_L08_001BFD00);
                STUB_printf(D_L08_001B0D48);
                moby_set_state(o,4,-1);
            }
        }
        break;
    case 4:
        if (D_L08_001A8F00==2 && *(int *)(s+0x30)!=-1) {
            moby_mark_spawned((D_L08_001B29DC+*(int *)(s+0x30)));
            *(int *)(s+0x30)=-1;
        }
        if (!game_is_either_mode_two() && *(u16 *)(o+0x96)>=6) {
            if (flag_is_byte_set()) menu_seek_chain_entry(10,4);
            else menu_seek_chain_entry(10,1);
            gfx_run_screen_update_steps(1);
            help_show_message_for_id(10);
            moby_replace_tracked(o);
            if (*(int *)(s+8)!=-1) {
                p=D_L08_001B29DC + *(int *)(s+8);
                STUB_printf(D_L08_001B0D70);
                D_L08_0021DE80.flags[p->index]=p->id+2;
                {
                    int id = p->id;
                    if (id == 255 || (!(D_L08_001B2840[(u8)id] & 128) &&
                        (D_0019B2E8[(u8)id + (g_current_map_index << 4)] & 128)))
                        D_L08_0021EAF0.flags[p->index]=id+2;
                }
            }
            STUB_printf(D_L08_001B0DA8);
            MemcardSave(0,-1);
            moby_set_state(o,5,-1);
        }
        break;
    }
    ++*(u16 *)(o+0x96);
    if (D_001395B8[0x1C]) {
        seen = (unsigned)D_0018CD20 & (1 << g_current_map_index);
        if (!seen) subtitle_request_voice_line(0x9F9,0x50);
    }
    TriggerSubtitleInCuboid(0xA3A,0x91,0,*(int *)(s+0xC),-1);
    if (g_hero_state.mode==0x31 && g_hero_state.object && *(short *)(g_hero_state.object+0xAA)==0xEEF) {
        if (D_0018D074>=0) subtitle_request_voice_line(0xA40,0x97);
        {
            float scale = -65.0f;
            level_store_pair_with_increment((int)(D_L08_001B3244 * scale + 0.5f), 2);
        }
    }
    if (D_L08_001CA080.state==1) {
        D_L08_001B9E08=level_get_height_map_ground(o);
        gfx_add_draw_callback_first(gfx_l08_draw_lens_flare,o);
    }
}
