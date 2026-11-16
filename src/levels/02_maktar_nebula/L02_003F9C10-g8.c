#include "names.h"
#include "moby_classes.h"
/* func_L02_003F9C10 in its own unit (-G8 -Wa,-G64 with the qcopy profile: the class table
 * and the loadout bytes are small data reached through $gp).
 * The Maktar arena's encounter driver, the counterpart of Joba's func_L11_0043E1A0
 * (src/levels/11_joba/L11_0043E1A0-main-g64.c), and matched with the same idioms:
 * - The state block and the object are real structs (MaktarState, MaktarObj): struct
 *   accesses let the scheduler move global stores past them as retail does.
 * - The 0x284/0x288 owner record is a struct view, owner stored before timer.
 * - The sound-slot blocks read st->owner before the slot test; 0x001B3774 is element 1 of
 *   the slot pair at D_L02_001B3770 (an incomplete sda array: symbol+offset never fills a
 *   slot; a sized one goes to $gp everywhere) and the second slot's buffer is passed as a
 *   pointer plus 0xE0.
 * - 0x1A7A00 is the word at +0x10 of the player-progress block D_001A79F0, read as an
 *   element of it: retail never puts it in a delay slot (symbol+offset is length 2).
 * - The hero's 0x24A4 float is stored through the Hero view of D_00189E20, as in Joba; the
 *   early bare %hi(D_00189E20) orders gcse's insertions in the case 8 setup as retail has them.
 * - Case 8's clear loops count up; the counts loop has a counter of its own, the marks and
 *   loadout loops share one. Its wave end reads the class into cls1 and (u16) cls3 first.
 * - Case 7 clears the choice only when it is non-zero, and indexes the selection table
 *   index-first (D_00139586[D_L02_00264A70]), as retail adds the index first.
 */
#include "include_asm.h"
#include "names.h"

typedef unsigned char u8;
typedef unsigned short u16;
typedef short s16;
typedef int s32;

typedef int TI128 __attribute__((mode(TI)));
extern int sprintf(char *, const char *, ...);
extern void hero_reset_position_and_direction(void *, void *, int, int);
extern void hero_start_loader_state(int);
extern void hero_start_target_state(char *, int, float);
extern void gfx_add_draw_callback_first(void (*)(char *), char *);
extern void mem_clear(void *, int, int);
extern float vec_distance_xy(void *, void *);
extern float IntToFloat(int);
extern int flag_is_byte_set(void);
extern char *GetLocalizedString(int);
extern void load_scene_chunk(int, int);
extern int level_l00_call_module_handler_with_arg_9(char *, int);
extern void moby_set_state(char *, int, int);
extern int math_random_int_below(int);
extern int IsPointInCuboid(char *, int);
extern int coll_point_inside_record_volume(char *, int);
extern int moby_handle_request_slot_state(int);
extern int TryClaimNotice(int, int, int);
extern int flag_set_first_pending(char *);
extern void moby_set_flag_bit(char *, int);
extern void script_queue_keyed_request(int, int);
extern void level_capture_checkpoint_state(void *, void *);
extern void state_set_flag_one(void);
extern void chainblade_reset_to_idle(char *);
extern void chainblade_set_helper(char *, char *);
extern void chainblade_advance_health_phase(char *);
extern int moby_has_free_child_slot_state2(char *);
extern void brawler_set_watched_entity(char *, char *);
extern void tracked_moby_set_state(int, int);
extern int arena_get_challenge_progress_index(int);
extern int arena_get_challenge_save_index(int);
extern void blast_call_helper_no_args(char *);
extern void arena_tick_controller(char *);
extern void arena_reset_controller(char *);
extern void arena_start_enemy_tally(char *);
extern void arena_update_enemy_tally(char *);
extern int arena_claim_enemy(char *, int);
extern char * arena_claim_boss(char *, int, int);
extern void actor_pick_watched_entity(char *);
extern void arena_activate_spawn_slots(char *);
extern void arena_clear_spawn_slots(char *);
extern void arena_reset_group_enemies(char *);
extern void arena_pick_nearest_attackers(char *);
extern char * arena_get_camera_point(char *);
extern void arena_match_active_count_a(char *, int);
extern void arena_match_active_count_b(char *, int);
extern void arena_update_group_enemies(char *);
extern void actor_update_helper_offsets(char *);
extern int arena_l02_is_wave_complete(char *);
extern void scene_start_count_views(char *, int);
extern void arena_run_scenery_setup(char *);
extern void arena_command_group_attacks(char *);
extern void cutscene_setup_camera(char *);
extern void arena_check_hero_at_console(char *);
extern void arena_update_challenge_menu(char *);
extern void DrawMaktarChallengeHud(char *);
extern void moby_try_alloc_enter_state2(char *);
extern void menu_select_next_usable(char *);
extern void DrawRadialQuadEffect(char *);
extern void gfx_draw_screen_wipe(char *);
extern int arena_start_announcer_message(char *, int);
extern void actor_pick_watched_message(char *);
extern void arena_notify_mobys_challenge_start(void);
extern void part_queue_moby_for_glow(char *, int, void (*)(char *));
extern void global_object_start(int, int);
extern void SetCamera5Pose(void *, void *, int, int, int);
extern void cam_set_mode_state(int);
extern unsigned char g_arena_choice_enabled __attribute__((section(".data")));
extern unsigned char g_gravity_bomb_weapon_index __attribute__((section(".data")));
extern unsigned char g_game_flag_table[] __attribute__((section(".data")));
extern int g_arena_timer_a __attribute__((section(".data")));
extern int g_arena_timer_b __attribute__((section(".data")));
extern char g_hero_state[] __attribute__((section(".data")));
extern char g_hero_position[] __attribute__((section(".data")));
extern int g_weapon_slot __attribute__((section(".data")));
extern int g_moby_class_state_word __attribute__((section(".data")));
extern unsigned char g_class_flag_byte __attribute__((section(".data")));
extern int g_request_enabled_flag __attribute__((section(".data")));
extern char g_music_state[] __attribute__((section(".data")));
extern unsigned short g_arena_fade_value __attribute__((section(".data")));
extern int g_frame_counter[] __attribute__((sda));
extern int g_arena_state_flag[] __attribute__((sda));
extern int g_frame_counter_2[] __attribute__((sda));
extern int g_arena_state_words[] __attribute__((sda));
extern float g_zero_l02_vector[4] __attribute__((section(".sdata")));
extern int g_level_script_flag __attribute__((sda));
extern int g_arena_challenge_index[] __attribute__((sda));
extern char *g_arena_challenge_table_2[14] __attribute__((sda));
extern unsigned char g_arena_default_loadout[4] __attribute__((sda));
extern int g_saved_hero_flag __attribute__((sda));
extern char g_str_arena_panel_format[] __attribute__((section(".data")));
extern float g_grab_highlight_level __attribute__((sda));
extern char * g_moby_l02_pool[] __attribute__((sda));
extern char * g_moby_l02_list_head[] __attribute__((sda));
extern int g_challenge_progress_copy[] __attribute__((sda));
extern char * g_matrix_l02_record_table[] __attribute__((sda));
extern char * g_boss_owner_slots[] __attribute__((sda));
extern char g_hero_effect_state[] __attribute__((section(".data")));
extern int g_arena_l02_active_flag __attribute__((section(".data")));
extern char g_boss_damage_totals[] __attribute__((section(".data")));

/* The controller's state block (the object's 0x68 pointer). */
typedef struct MaktarState {
    u8 pad000[0x50];
    s32 loadout[4];      /* 0x50 */
    s32 lost;            /* 0x60 */
    u8 pad064[0xC];
    s32 trigger1;        /* 0x70 */
    s32 trigger2;        /* 0x74 */
    u8 pad078[4];
    s32 zone;            /* 0x7C */
    u8 pad080[0xC];
    s32 camera;          /* 0x8C */
    s32 counts[6];       /* 0x90 */
    char *slots[10];     /* 0xA8 */
    char *owner;         /* 0xD0 */
    s32 frames;          /* 0xD4 */
    s32 slot;            /* 0xD8 */
    u8 pad0DC[0x108 - 0xDC];
    s32 gate1;           /* 0x108 */
    s32 gate2;           /* 0x10C */
    u8 pad110[8];
    s16 result;          /* 0x118 */
    u8 pad11A[6];
    s16 cls;             /* 0x120 */
    s16 wave;            /* 0x122 */
    s16 fade;            /* 0x124 */
    u8 pad126[0x1D0 - 0x126];
    s16 marks[40];       /* 0x1D0 */
    s32 music;           /* 0x220 */
    u8 pad224[4];
    s32 volume;          /* 0x228 */
    u8 pad22C[4];
    s32 track;           /* 0x230 */
    s32 trackVolume;     /* 0x234 */
} MaktarState;

/* The object's own fields: state 0x20, the state block 0x68, timer 0x96, phase 0xBC. */
typedef struct MaktarObj {
    u8 pad00[0x20];
    u8 state;            /* 0x20 */
    u8 pad21[0x68 - 0x21];
    MaktarState *st;     /* 0x68 */
    u8 pad6C[0x96 - 0x6C];
    u16 timer;           /* 0x96 */
    u8 pad98[0xBC - 0x98];
    u8 phase;            /* 0xBC */
    u8 padBD;
    u8 flags;            /* 0xBE */
} MaktarObj;

typedef struct { u8 pad0[0x284]; char *owner; s32 timer; } MaktarFlags;

/* The persistent player-progress block starts at D_001A79F0 (the level index); its word at
   +0x10 (0x1A7A00) is read here as an element of it. */
extern int g_current_map_index[] __attribute__((sda));

/* One 0xE0-byte record of the level's selection table. */
typedef struct {
    u8 pad0[4];
    u8 enabled;          /* 0x04 */
    u8 pad5[0xE0 - 5];
} MaktarChoice;
extern MaktarChoice g_material_l02_table[] __attribute__((section(".data")));

/* The hero block at D_00189E20; 0x80 is the position read as D_00189EA0 elsewhere. */
typedef union { u8 b[0x2600]; s16 h[0x1300]; s32 i[0x980]; float f[0x980]; void *ptr[0x980]; } Hero;
#define HERO ((Hero *)D_00189E20)

#define W(p,o) (*(int *)((p)+(o)))
#define H(p,o) (*(short *)((p)+(o)))
#define U(p,o) (*(unsigned short *)((p)+(o)))
#define B(p,o) (*(unsigned char *)((p)+(o)))
#define P(p,o) (*(char **)((p)+(o)))
#define OBJ ((MaktarObj *)actor)
/* Per-frame update of the Maktar arena controller (moby class 2905). It runs the challenge menu, starts each wave of enemies, and ends the challenge. */
void UpdateArenaController(char *actor) {
    MaktarState *st = OBJ->st;
    float fadeLevel;
    float pos[4];
    char text[112];
    blast_call_helper_no_args(actor);
    g_level_script_flag = 1;
    g_game_flag_table[2] = g_game_flag_table[arena_get_challenge_save_index(0)] != 0;
    switch (OBJ->state) {
    case 0:
        arena_reset_controller(actor);
        arena_run_scenery_setup(actor);
        if (g_arena_state_flag[0] == 2) {
            g_arena_state_flag[0] = 0;
            moby_set_state(actor,2,-1);
            state_set_flag_one();
            st->fade = g_arena_fade_value;
            gfx_add_draw_callback_first(gfx_draw_screen_wipe,actor);
            OBJ->timer = 31;
        }
        break;
    case 1:
        if (coll_point_inside_record_volume(g_hero_position,st->zone)) moby_set_state(actor,4,-1);
        else if (IsPointInCuboid(g_hero_position,st->trigger1)) {
            TryClaimNotice(4,0x2f3c,1);
            moby_try_alloc_enter_state2(actor);
        } else if (g_game_flag_table[arena_get_challenge_save_index(0)] && coll_point_inside_record_volume(g_hero_position,st->trigger2)) {
            TryClaimNotice(4,0x2f3c,1);
            moby_try_alloc_enter_state2(actor);
        }
        if (g_arena_state_flag[0] == 2) {
            g_arena_state_flag[0] = 0;
            moby_set_state(actor,2,-1);
            state_set_flag_one();
            st->fade = g_arena_fade_value;
            gfx_add_draw_callback_first(gfx_draw_screen_wipe,actor);
            OBJ->timer = 31;
        }
        g_level_script_flag = 0;
        break;
    case 2: {
        char *a;
        if (flag_set_first_pending(actor)) {
            arena_match_active_count_a(actor,0); arena_match_active_count_b(actor,0); OBJ->phase=0;
            break;
        }
        if (OBJ->phase==0) {
            if (OBJ->timer<31) {
                fadeLevel=IntToFloat(OBJ->timer)*0.05f;
                if (fadeLevel<1.0f) fadeLevel=IntToFloat(OBJ->timer)*0.05f;
                else fadeLevel=1.0f;
                g_grab_highlight_level=fadeLevel;
                break;
            }
            st->fade=g_arena_fade_value;
            gfx_add_draw_callback_first(gfx_draw_screen_wipe,actor);
            if (g_arena_l02_active_flag!=1) load_scene_chunk(1,st->music);
            a=g_matrix_l02_record_table[0]+st->camera*128;
            hero_reset_position_and_direction(a+0x30,a+0x70,0x6f,1);
            level_capture_checkpoint_state(g_hero_position,g_hero_position+0x10);
            script_queue_keyed_request(st->music,st->volume);
            *(TI128 *)pos=*(TI128 *)(g_matrix_l02_record_table[0]+st->camera*128+0x30);
            pos[2]+=2.0f;
            SetCamera5Pose(pos,g_matrix_l02_record_table[0]+st->camera*128+0x70,1,0,0);
            OBJ->phase=2;
        } else if (OBJ->phase==2) {
            gfx_add_draw_callback_first(gfx_draw_screen_wipe,actor);
            g_grab_highlight_level=0;
            if (st->fade>0) break;
            if (!g_game_flag_table[5]) {
                g_game_flag_table[5]=1; OBJ->phase=1;
                moby_set_flag_bit(g_moby_l02_pool[0]+st->gate1*256,1);
                OBJ->timer=0;
                break;
            }
            goto beginApproach;
        } else if (OBJ->phase==1 && OBJ->timer>=61 && g_arena_state_words[0]!=2) {
        beginApproach:
            OBJ->phase=3;
            hero_start_loader_state(0);
            hero_start_target_state(arena_get_camera_point(actor),0,0.0f);
        } else if (OBJ->phase==3) {
            if (g_game_flag_table[arena_get_challenge_save_index(0)]) {
                if (vec_distance_xy(g_hero_position,arena_get_camera_point(actor))<10.0f) moby_set_state(actor,4,-1);
                else if (OBJ->timer>=61) cam_set_mode_state(2);
            } else {
                st->cls=0; st->wave=0;
                g_game_flag_table[0x3c]=st->result;
                moby_set_state(actor,8,-1);
                cam_set_mode_state(2); hero_start_loader_state(0);
            }
        }
        break;
    }
    case 5:
        if (OBJ->timer<180) {
            arena_match_active_count_a(actor,0); arena_match_active_count_b(actor,0);
            HERO->f[0x24A4/4]=200.0f;
            arena_update_group_enemies(actor); gfx_add_draw_callback_first(DrawRadialQuadEffect,actor);
            break;
        }
    case 4:
        if (flag_set_first_pending(actor)) {
            if (OBJ->state==5) scene_start_count_views(actor,st->cls);
            arena_run_scenery_setup(actor); arena_reset_group_enemies(actor);
            arena_match_active_count_a(actor,0); arena_match_active_count_b(actor,0);
            hero_reset_position_and_direction(arena_get_camera_point(actor),g_zero_l02_vector,0x6f,1);
            level_capture_checkpoint_state(g_hero_position,g_hero_position+0x10);
            cutscene_setup_camera(actor);
        }
        arena_check_hero_at_console(actor); HERO->f[0x24A4/4]=200.0f;
        break;
    case 10:
        if (OBJ->timer<360) {
            arena_match_active_count_a(actor,0); arena_match_active_count_b(actor,0);
            if (OBJ->timer>180) HERO->f[0x24A4/4]=200.0f;
            arena_update_group_enemies(actor); gfx_add_draw_callback_first(DrawRadialQuadEffect,actor);
            break;
        }
        moby_set_state(actor,4,-1);
        break;
    case 11:
        if (flag_set_first_pending(actor)) { arena_match_active_count_a(actor,0); arena_match_active_count_b(actor,0); OBJ->phase=0; }
        if (!OBJ->phase) {
            if (OBJ->timer<180) {
                HERO->f[0x24A4/4]=200.0f;
                arena_update_group_enemies(actor); gfx_add_draw_callback_first(DrawRadialQuadEffect,actor);
            } else { moby_set_flag_bit(g_moby_l02_pool[0]+st->gate2*256,1); OBJ->phase=1; }
        } else if (g_request_enabled_flag>0 && g_arena_state_words[0]!=2 && OBJ->timer>=241) {
            OBJ->state=5; OBJ->flags&=0xfe;
        }
        break;
    case 6:
        if (flag_set_first_pending(actor) && !g_game_flag_table[arena_get_challenge_save_index(st->cls)]) {
            switch(st->cls) {
            case 0: arena_start_announcer_message(actor,10); break;
            case 3: arena_start_announcer_message(actor,13); break;
            case 1: case 2: case 4: case 5: case 6: case 10: arena_start_announcer_message(actor,math_random_int_below(2)+11); break;
            }
        }
        menu_select_next_usable(actor);
        break;
    case 7: {
        int choice;
        if (flag_set_first_pending(actor)) {
            choice=g_game_flag_table[0x3c];
            if (choice && (!g_game_flag_table[arena_get_challenge_save_index(W(g_arena_challenge_table_2[choice],8))] ||
                           (choice>=12 && !flag_is_byte_set()) ||
                           (choice==7 && !g_arena_choice_enabled[g_material_l02_table].enabled) ||
                           (choice==8 && !g_gravity_bomb_weapon_index[g_material_l02_table].enabled))) choice=0;
            st->result=choice;
            arena_start_announcer_message(actor,math_random_int_below(2));
        }
        arena_update_challenge_menu(actor);
        break;
    }
    case 8: {
        char *row, *entity;
        int frames, spawned, allowed;
        arena_get_challenge_save_index(0);
        if (flag_set_first_pending(actor)) {
            int i, k;
            char *row;
            st->wave=0;
            for(k=0;k<6;k++) st->counts[k]=0;
            st->frames=0; st->lost=0;
            arena_run_scenery_setup(actor); arena_start_enemy_tally(actor); arena_command_group_attacks(actor);
            row=P(g_arena_challenge_table_2[st->cls],4);
            row+=st->wave*20;
            arena_match_active_count_a(actor,H(row,10)); arena_match_active_count_b(actor,H(row,8));
            for(i=39;i>=0;i--) st->marks[i]=0;
            for(i=0;i<4;i++) st->loadout[i]=g_arena_default_loadout[i];
            if (st->cls==7) { char *g=g_hero_state; g_arena_timer_a=300; g_saved_hero_flag=W(g,0x18d4); W(g,0x18d4)=0; }
            else if(st->cls==8) { char *g=g_hero_state; g_arena_timer_b=8; g_saved_hero_flag=W(g,0x18d4); W(g,0x18d4)=0; }
            if(st->cls==13) { char *g=g_hero_state; g_saved_hero_flag=W(g,0x18d4); W(g,0x18d4)=0; }
            { char *g=g_hero_state; W(g,0x24cc)=g_current_map_index[4]; }
            arena_notify_mobys_challenge_start();
        }
        arena_update_enemy_tally(actor);
        if (arena_l02_is_wave_complete(actor)) {
            int i, cls1;
            unsigned int cls3;
            char *row;
            st->wave++;
            for(i=5;i>=0;i--) st->counts[i]=0;
            st->lost=0;
            { MaktarFlags *g=(MaktarFlags *)g_hero_effect_state; if(g->owner==st->owner) g->owner=0; }
            cls1=st->cls;
            cls3=(u16)st->cls;
            st->owner=0;
            if(st->wave>=H(g_arena_challenge_table_2[cls1],0)) {
                if(cls3-7U<2 || cls1==13) g_moby_class_state_word=g_saved_hero_flag;
                tracked_moby_set_state(1,-1); global_object_start(1,-1);
                if(!st->cls && !g_game_flag_table[arena_get_challenge_save_index(0)]) moby_set_state(actor,11,-1);
                else moby_set_state(actor,5,-1);
                st->result=st->cls;
                return;
            }
            if(cls1>=14) st->cls=13;
            arena_command_group_attacks(actor);
            row=P(g_arena_challenge_table_2[st->cls],4);
            row+=st->wave*20;
            arena_match_active_count_a(actor,H(row,10)); arena_match_active_count_b(actor,H(row,8));
        }
        frames=++st->frames;
        if((st->cls==3 && frames>=1801) || (st->cls==5 && frames>=3601)) {
            char *format, *buffer, *a, *b;
            int sum=0, j, count;
            buffer=text;
            for(j=0;j<6;j++) sum+=st->counts[j];
            format=g_str_arena_panel_format;
            a=GetLocalizedString(0x3269);
            count=st->wave*15+sum-st->lost;
            b=GetLocalizedString(0x2f61);
            sprintf(buffer,format,a,count,b);
            level_l00_call_module_handler_with_arg_9(buffer,-1);
            moby_set_state(actor,10,-1); tracked_moby_set_state(1,-1); global_object_start(1,-1);
            return;
        }
        if(st->cls==7 && g_weapon_slot==30 && g_arena_timer_a<=0) {
            allowed=1;
            for(entity=g_moby_l02_list_head[0];entity;entity=P(entity,0x28)) {
                if(B(entity,0x20)==0xfe) continue;
                if(B(entity,0x20)==0xfd) continue;
                if(H(entity,0xaa)==0xc89 /* moby class 3209 */ || H(entity,0xaa)==0xbfe /* moby class 3070 */) allowed=0;
            }
            if(allowed) {
                level_l00_call_module_handler_with_arg_9(GetLocalizedString(0x326b),-1);
                moby_set_state(actor,10,-1); tracked_moby_set_state(1,-1); global_object_start(1,-1);
                return;
            }
        } else if(st->cls==8 && g_weapon_slot==42 && g_arena_timer_b<=0) {
            allowed=1;
            for(entity=g_moby_l02_list_head[0];entity;entity=P(entity,0x28)) {
                if(B(entity,0x20)==0xfe) continue;
                if(B(entity,0x20)==0xfd) continue;
                if((unsigned short)(U(entity,0xaa)-0xc06)<=1) allowed=0;
            }
            if(allowed) {
                level_l00_call_module_handler_with_arg_9(GetLocalizedString(0x326c),-1);
                moby_set_state(actor,10,-1); tracked_moby_set_state(1,-1); global_object_start(1,-1);
                return;
            }
        } else if(st->cls==12) {
            if(g_request_enabled_flag<g_current_map_index[4]) {
                { MaktarFlags *g=(MaktarFlags *)g_hero_effect_state; if(g->owner==st->owner) g->owner=0; }
                st->owner=0;
                level_l00_call_module_handler_with_arg_9(GetLocalizedString(0x326a),-1);
                moby_set_state(actor,10,-1); tracked_moby_set_state(1,-1); global_object_start(1,-1);
                return;
            }
            if(st->frames>=7201) {
                part_queue_moby_for_glow(st->owner,0,chainblade_reset_to_idle);
                { MaktarFlags *g=(MaktarFlags *)g_hero_effect_state; if(g->owner==st->owner) g->owner=0; }
                st->owner=0;
                moby_set_state(actor,5,-1); tracked_moby_set_state(1,-1); global_object_start(1,-1);
                return;
            }
        } else if(st->cls==13 && g_request_enabled_flag<g_current_map_index[4]) {
            level_l00_call_module_handler_with_arg_9(GetLocalizedString(0x326a),-1);
            moby_set_state(actor,10,-1); tracked_moby_set_state(1,-1); global_object_start(1,-1);
            return;
        }
        gfx_add_draw_callback_first(DrawMaktarChallengeHud,actor);
        row=P(g_arena_challenge_table_2[st->cls],4)+st->wave*20;
        if(OBJ->timer<61 && !U(row,16)) goto spawn;
        arena_clear_spawn_slots(actor); spawned=0; actor_pick_watched_entity(actor);
        if(st->slots[st->slot] && moby_has_free_child_slot_state2(st->slots[st->slot])) {
            int i;
            for(i=st->counts[3];i<H(row,6);i++) spawned|=arena_claim_enemy(actor,MOBY_CLASS_PX6_BLADEBALL);
            for(i=st->counts[1];i<H(row,2);i++) spawned|=arena_claim_enemy(actor,0xb22 /* moby class 2850 */);
            for(i=st->counts[2];i<H(row,4);i++) spawned|=arena_claim_enemy(actor,MOBY_CLASS_MEGACORP_SECURITY_ROBOT_FLAMETHROWER);
            for(i=st->counts[0];i<H(row,0);i++) spawned|=arena_claim_enemy(actor,0x9ca /* moby class 2506 */);
        }
        if(!st->counts[4] && B(row,16) && !st->counts[5] && B(row,17)) {
            char *a, *b;
            a=arena_claim_boss(actor,MOBY_CLASS_CHAINBLADE,0); b=arena_claim_boss(actor,MOBY_CLASS_B2_BRAWLER_LEGS,1);
            chainblade_set_helper(a,b); brawler_set_watched_entity(b,a); chainblade_advance_health_phase(a); st->owner=a;
            { MaktarFlags *g=(MaktarFlags *)g_hero_effect_state; if(!g->owner) { g->owner=a; g->timer=0; } }
            if(!g_boss_owner_slots[0]) { g_boss_owner_slots[0]=a; mem_clear(g_boss_damage_totals,0,224); }
            if(!g_boss_owner_slots[1]) { char *buf=g_boss_damage_totals; g_boss_owner_slots[1]=b; mem_clear(buf+224,0,224); }
            arena_start_announcer_message(actor,15); script_queue_keyed_request(st->track,st->trackVolume);
        } else if(!st->counts[4] && B(row,16)) {
            char *a;
            a=arena_claim_boss(actor,MOBY_CLASS_CHAINBLADE,0); st->owner=a;
            { MaktarFlags *g=(MaktarFlags *)g_hero_effect_state; if(!g->owner) { g->owner=a; g->timer=0; } }
            { char *snd=st->owner; if(!g_boss_owner_slots[0]) { g_boss_owner_slots[0]=snd; mem_clear(g_boss_damage_totals,0,224); } }
            arena_start_announcer_message(actor,14); script_queue_keyed_request(st->track,st->trackVolume);
        } else if(!st->counts[5] && B(row,17)) {
            char *a;
            a=arena_claim_boss(actor,MOBY_CLASS_B2_BRAWLER_LEGS,0); st->owner=a;
            { MaktarFlags *g=(MaktarFlags *)g_hero_effect_state; if(!g->owner) { g->owner=a; g->timer=0; } }
            { char *snd=st->owner; if(!g_boss_owner_slots[1]) { char *buf=g_boss_damage_totals; g_boss_owner_slots[1]=snd; mem_clear(buf+224,0,224); } }
            arena_start_announcer_message(actor,20); script_queue_keyed_request(st->track,st->trackVolume);
        }
        if(!U(row,16)) { char *g=g_music_state; if(B(g,0x48)!=st->music && B(g,0x3c)!=st->music) script_queue_keyed_request(st->music,st->volume); }
        if(spawned) arena_activate_spawn_slots(actor);
    spawn:
        if(st->cls==7) moby_handle_request_slot_state(30);
        else if(st->cls==8) moby_handle_request_slot_state(42);
        else if(st->cls==13) { moby_handle_request_slot_state(10); g_class_flag_byte=1; }
        actor_update_helper_offsets(actor); actor_pick_watched_message(actor);
        if(!(g_frame_counter_2[0]&3)) arena_pick_nearest_attackers(actor);
        arena_update_group_enemies(actor); gfx_add_draw_callback_first(DrawRadialQuadEffect,actor);
        if(arena_get_challenge_progress_index(st->cls)!=-1) {
            g_arena_challenge_index[0]=arena_get_challenge_progress_index(st->cls); g_challenge_progress_copy[0]=g_frame_counter[0];
        }
        break;
    }
    }
    arena_tick_controller(actor);
}
