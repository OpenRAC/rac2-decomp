#include "include_asm.h"
#include "names.h"

typedef unsigned char u8;
typedef unsigned short u16;
typedef short s16;
typedef int s32;
typedef int TI128 __attribute__((mode(TI)));
extern int sprintf(char *, const char *, ...);
extern void func_PAL_L00_002B9CD8(void *, void *, int, int);
extern void hero_start_loader_state(int);
extern void hero_start_target_state(char *, int, float);
extern void gfx_add_draw_callback_first(void (*)(char *), char *);
extern void mem_clear(void *, int, int);
extern float vec_distance_xy(void *, void *);
extern float IntToFloat(int);
extern int flag_is_byte_set(void);
extern char * GetLocalizedString(int);
extern void func_PAL_L00_00305110(int, int);
extern void func_PAL_L00_0030FBC0(char *, int);
extern void moby_set_state(char *, int, int);
extern int math_random_int_below(int);
extern int IsPointInCuboid(char *, int);
extern int coll_point_inside_record_volume(char *, int);
extern void moby_handle_request_slot_state(int);
extern void TryClaimNotice(int, int, int);
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
extern void func_PAL_L00_003E38E8(int, int);
extern int arena_get_challenge_progress_index(int);
extern int arena_get_challenge_save_index(int);
extern void blast_call_helper_no_args(char *);
extern void func_PAL_L02_003FF640(char *);
extern void arena_reset_controller(char *);
extern void func_PAL_L02_003FF718(char *);
extern void func_PAL_L02_003FF858(char *);
extern int arena_claim_enemy(char *, int);
extern char * arena_claim_boss(char *, int, int);
extern void actor_pick_watched_entity(char *);
extern void arena_activate_spawn_slots(char *);
extern void arena_clear_spawn_slots(char *);
extern void func_PAL_L02_004002E8(char *);
extern void arena_pick_nearest_attackers(char *);
extern char * arena_get_camera_point(char *);
extern void arena_match_active_count_a(char *, int);
extern void arena_match_active_count_b(char *, int);
extern void func_PAL_L02_00400F20(char *);
extern void func_PAL_L02_00401118(char *);
extern int arena_l02_is_wave_complete(char *);
extern void func_PAL_L02_004013F8(char *, int);
extern void arena_run_scenery_setup(char *);
extern void func_PAL_L02_00401980(char *);
extern void func_PAL_L02_00401EC8(char *);
extern void arena_check_hero_at_console(char *);
extern void func_PAL_L02_00402030(char *);
extern void DrawMaktarChallengeHud(char *);
extern void func_PAL_L02_00403FA0(char *);
extern void func_PAL_L02_004042C0(char *);
extern void func_PAL_L02_004046D0(char *);
extern void gfx_draw_screen_wipe(char *);
extern int arena_start_announcer_message(char *, int);
extern void actor_pick_watched_message(char *);
extern void func_PAL_L02_00405450(void);
extern void part_queue_moby_for_glow(char *, int, void (*)(char *));
extern void func_PAL_L00_004071F0(int, int);
extern void SetCamera5Pose(void *, void *, int, int, int);
extern void cam_set_mode_state(int);
extern unsigned char D_00139586 __attribute__((section(".data")));
extern unsigned char D_00139592 __attribute__((section(".data")));
extern unsigned char D_001395B8[] __attribute__((section(".data")));
extern int D_00139700 __attribute__((section(".data")));
extern int D_00139730 __attribute__((section(".data")));
extern char g_hero_state[] __attribute__((section(".data")));
extern char g_hero_position[] __attribute__((section(".data")));
extern int D_0018B068 __attribute__((section(".data")));
extern int D_0018B6F4 __attribute__((section(".data")));
extern unsigned char D_0018C0D7 __attribute__((section(".data")));
extern int D_0018C2EC __attribute__((section(".data")));
extern char g_music_state[] __attribute__((section(".data")));
extern unsigned short D_001A65D2 __attribute__((section(".data")));
extern int D_001A7390[] __attribute__((sda));
extern int D_001A7904[] __attribute__((sda));
extern int D_001A7BC0[] __attribute__((sda));
extern int D_L02_001A8F00[] __attribute__((sda));
extern float D_L02_001A8F20[4] __attribute__((section(".sdata")));
extern int D_L02_001A9010 __attribute__((sda));
extern int D_L02_001AA1B0[] __attribute__((sda));
extern char *D_L02_001B1190[14] __attribute__((sda));
extern unsigned char D_L02_001B11C8[4] __attribute__((sda));
extern int D_L02_001B1224 __attribute__((sda));
extern char D_L02_001B1228[] __attribute__((section(".data")));
extern float D_L02_001B2FE0 __attribute__((sda));
extern char * g_moby_l02_pool[] __attribute__((sda));
extern char * D_L02_001B35A8[] __attribute__((sda));
extern int D_L02_001B3680[] __attribute__((sda));
extern char * D_L02_001B368C[] __attribute__((sda));
extern char * D_L02_001B3770[] __attribute__((sda));
extern char D_L02_001BA3C0[] __attribute__((section(".data")));
extern int D_L02_001CAA80 __attribute__((section(".data")));
extern char D_L02_001FF6B8[] __attribute__((section(".data")));
typedef struct MaktarState {
    u8 pad000[0x50];
    s32 loadout[4];       
    s32 lost;             
    u8 pad064[0xC];
    s32 trigger1;         
    s32 trigger2;         
    u8 pad078[4];
    s32 zone;             
    u8 pad080[0xC];
    s32 camera;           
    s32 counts[6];        
    char *slots[10];      
    char *owner;          
    s32 frames;           
    s32 slot;             
    u8 pad0DC[0x108 - 0xDC];
    s32 gate1;            
    s32 gate2;            
    u8 pad110[8];
    s16 result;           
    u8 pad11A[6];
    s16 cls;              
    s16 wave;             
    s16 fade;             
    u8 pad126[0x1D0 - 0x126];
    s16 marks[40];        
    s32 music;            
    u8 pad224[4];
    s32 volume;           
    u8 pad22C[4];
    s32 track;            
    s32 trackVolume;      
} MaktarState;
typedef struct MaktarObj {
    u8 pad00[0x20];
    u8 state;             
    u8 pad21[0x68 - 0x21];
    MaktarState *st;      
    u8 pad6C[0x96 - 0x6C];
    u16 timer;            
    u8 pad98[0xBC - 0x98];
    u8 phase;             
    u8 padBD;
    u8 flags;             
} MaktarObj;
typedef struct { u8 pad0[0x284]; char *owner; s32 timer; } MaktarFlags;
extern int g_current_map_index[] __attribute__((sda));
typedef struct {
    u8 pad0[4];
    u8 enabled;           
    u8 pad5[0xE0 - 5];
} MaktarChoice;
extern MaktarChoice D_L02_00264A70[] __attribute__((section(".data")));
typedef union { u8 b[0x2600]; s16 h[0x1300]; s32 i[0x980]; float f[0x980]; void *ptr[0x980]; } Hero;
#define HERO ((Hero *)D_00189E20)
#define W(p,o) (*(int *)((p)+(o)))
#define H(p,o) (*(short *)((p)+(o)))
#define U(p,o) (*(unsigned short *)((p)+(o)))
#define B(p,o) (*(unsigned char *)((p)+(o)))
#define P(p,o) (*(char **)((p)+(o)))
#define OBJ ((MaktarObj *)actor)

void func_PAL_L02_003FE328(char *actor) {
    MaktarState *st = OBJ->st;
    float f;
    float pos[4];
    char text[112];
    blast_call_helper_no_args(actor);
    D_L02_001A9010 = 1;
    D_001395B8[2] = D_001395B8[arena_get_challenge_save_index(0)] != 0;
    switch (OBJ->state) {
    case 0:
        arena_reset_controller(actor);
        arena_run_scenery_setup(actor);
        if (D_001A7904[0] == 2) {
            D_001A7904[0] = 0;
            moby_set_state(actor,2,-1);
            state_set_flag_one();
            st->fade = D_001A65D2;
            gfx_add_draw_callback_first(gfx_draw_screen_wipe,actor);
            OBJ->timer = 26;
        }
        break;
    case 1:
        if (coll_point_inside_record_volume(g_hero_position,st->zone)) moby_set_state(actor,4,-1);
        else if (IsPointInCuboid(g_hero_position,st->trigger1)) {
            TryClaimNotice(4,0xE61,1);
            func_PAL_L02_00403FA0(actor);
        } else if (D_001395B8[arena_get_challenge_save_index(0)] && coll_point_inside_record_volume(g_hero_position,st->trigger2)) {
            TryClaimNotice(4,0xE61,1);
            func_PAL_L02_00403FA0(actor);
        }
        if (D_001A7904[0] == 2) {
            D_001A7904[0] = 0;
            moby_set_state(actor,2,-1);
            state_set_flag_one();
            st->fade = D_001A65D2;
            gfx_add_draw_callback_first(gfx_draw_screen_wipe,actor);
            OBJ->timer = 26;
        }
        D_L02_001A9010 = 0;
        break;
    case 2: {
        char *a;
        if (flag_set_first_pending(actor)) {
            arena_match_active_count_a(actor,0); arena_match_active_count_b(actor,0); OBJ->phase=0;
            break;
        }
        if (OBJ->phase==0) {
            if (OBJ->timer<26) {
                f=IntToFloat(OBJ->timer)*0.05882353f;
                if (f<1.0f) f=IntToFloat(OBJ->timer)*0.05882353f;
                else f=1.0f;
                D_L02_001B2FE0=f;
                break;
            }
            st->fade=D_001A65D2;
            gfx_add_draw_callback_first(gfx_draw_screen_wipe,actor);
            if (D_L02_001CAA80!=1) func_PAL_L00_00305110(1,st->music);
            a=D_L02_001B368C[0]+st->camera*128;
            func_PAL_L00_002B9CD8(a+0x30,a+0x70,0x6f,1);
            level_capture_checkpoint_state(g_hero_position,g_hero_position+0x10);
            script_queue_keyed_request(st->music,st->volume);
            *(TI128 *)pos=*(TI128 *)(D_L02_001B368C[0]+st->camera*128+0x30);
            pos[2]+=2.0f;
            SetCamera5Pose(pos,D_L02_001B368C[0]+st->camera*128+0x70,1,0,0);
            OBJ->phase=2;
        } else if (OBJ->phase==2) {
            gfx_add_draw_callback_first(gfx_draw_screen_wipe,actor);
            D_L02_001B2FE0=0;
            if (st->fade>0) break;
            if (!D_001395B8[5]) {
                D_001395B8[5]=1; OBJ->phase=1;
                moby_set_flag_bit(g_moby_l02_pool[0]+st->gate1*256,1);
                OBJ->timer=0;
                break;
            }
            goto beginApproach;
        } else if (OBJ->phase==1 && OBJ->timer>=51 && D_L02_001A8F00[0]!=2) {
        beginApproach:
            OBJ->phase=3;
            hero_start_loader_state(0);
            hero_start_target_state(arena_get_camera_point(actor),0,0.0f);
        } else if (OBJ->phase==3) {
            if (D_001395B8[arena_get_challenge_save_index(0)]) {
                if (vec_distance_xy(g_hero_position,arena_get_camera_point(actor))<10.0f) moby_set_state(actor,4,-1);
                else if (OBJ->timer>=51) cam_set_mode_state(2);
            } else {
                st->cls=0; st->wave=0;
                D_001395B8[0x3c]=st->result;
                moby_set_state(actor,8,-1);
                cam_set_mode_state(2); hero_start_loader_state(0);
            }
        }
        break;
    }
    case 5:
        if (OBJ->timer<150) {
            arena_match_active_count_a(actor,0); arena_match_active_count_b(actor,0);
            HERO->f[0x24A4/4]=200.0f;
            func_PAL_L02_00400F20(actor); gfx_add_draw_callback_first(func_PAL_L02_004046D0,actor);
            break;
        }
    case 4:
        if (flag_set_first_pending(actor)) {
            if (OBJ->state==5) func_PAL_L02_004013F8(actor,st->cls);
            arena_run_scenery_setup(actor); func_PAL_L02_004002E8(actor);
            arena_match_active_count_a(actor,0); arena_match_active_count_b(actor,0);
            func_PAL_L00_002B9CD8(arena_get_camera_point(actor),D_L02_001A8F20,0x6f,1);
            level_capture_checkpoint_state(g_hero_position,g_hero_position+0x10);
            func_PAL_L02_00401EC8(actor);
        }
        arena_check_hero_at_console(actor); HERO->f[0x24A4/4]=200.0f;
        break;
    case 10:
        if (OBJ->timer<300) {
            arena_match_active_count_a(actor,0); arena_match_active_count_b(actor,0);
            if (OBJ->timer>150) HERO->f[0x24A4/4]=200.0f;
            func_PAL_L02_00400F20(actor); gfx_add_draw_callback_first(func_PAL_L02_004046D0,actor);
            break;
        }
        moby_set_state(actor,4,-1);
        break;
    case 11:
        if (flag_set_first_pending(actor)) { arena_match_active_count_a(actor,0); arena_match_active_count_b(actor,0); OBJ->phase=0; }
        if (!OBJ->phase) {
            if (OBJ->timer<150) {
                HERO->f[0x24A4/4]=200.0f;
                func_PAL_L02_00400F20(actor); gfx_add_draw_callback_first(func_PAL_L02_004046D0,actor);
            } else { moby_set_flag_bit(g_moby_l02_pool[0]+st->gate2*256,1); OBJ->phase=1; }
        } else if (D_0018C2EC>0 && D_L02_001A8F00[0]!=2 && OBJ->timer>=201) {
            OBJ->state=5; OBJ->flags&=0xfe;
        }
        break;
    case 6:
        if (flag_set_first_pending(actor) && !D_001395B8[arena_get_challenge_save_index(st->cls)]) {
            switch(st->cls) {
            case 0: arena_start_announcer_message(actor,10); break;
            case 3: arena_start_announcer_message(actor,13); break;
            case 1: case 2: case 4: case 5: case 6: case 10: arena_start_announcer_message(actor,math_random_int_below(2)+11); break;
            }
        }
        func_PAL_L02_004042C0(actor);
        break;
    case 7: {
        int choice;
        if (flag_set_first_pending(actor)) {
            choice=D_001395B8[0x3c];
            if (choice && (!D_001395B8[arena_get_challenge_save_index(W(D_L02_001B1190[choice],8))] ||
                           (choice>=12 && !flag_is_byte_set()) ||
                           (choice==7 && !D_00139586[D_L02_00264A70].enabled) ||
                           (choice==8 && !D_00139592[D_L02_00264A70].enabled))) choice=0;
            st->result=choice;
            arena_start_announcer_message(actor,math_random_int_below(2));
        }
        func_PAL_L02_00402030(actor);
        break;
    }
    case 8: {
        char *row, *e;
        int n, spawned, allowed;
        arena_get_challenge_save_index(0);
        if (flag_set_first_pending(actor)) {
            int i, k;
            char *row;
            st->wave=0;
            for(k=0;k<6;k++) st->counts[k]=0;
            st->frames=0; st->lost=0;
            arena_run_scenery_setup(actor); func_PAL_L02_003FF718(actor); func_PAL_L02_00401980(actor);
            row=P(D_L02_001B1190[st->cls],4);
            row+=st->wave*20;
            arena_match_active_count_a(actor,H(row,10)); arena_match_active_count_b(actor,H(row,8));
            for(i=39;i>=0;i--) st->marks[i]=0;
            for(i=0;i<4;i++) st->loadout[i]=D_L02_001B11C8[i];
            if (st->cls==7) { char *g=g_hero_state; D_00139700=300; D_L02_001B1224=W(g,0x18d4); W(g,0x18d4)=0; }
            else if(st->cls==8) { char *g=g_hero_state; D_00139730=8; D_L02_001B1224=W(g,0x18d4); W(g,0x18d4)=0; }
            if(st->cls==13) { char *g=g_hero_state; D_L02_001B1224=W(g,0x18d4); W(g,0x18d4)=0; }
            { char *g=g_hero_state; W(g,0x24cc)=g_current_map_index[4]; }
            func_PAL_L02_00405450();
        }
        func_PAL_L02_003FF858(actor);
        if (arena_l02_is_wave_complete(actor)) {
            int i, cls1;
            unsigned int cls3;
            char *row;
            st->wave++;
            for(i=5;i>=0;i--) st->counts[i]=0;
            st->lost=0;
            { MaktarFlags *g=(MaktarFlags *)D_L02_001BA3C0; if(g->owner==st->owner) g->owner=0; }
            cls1=st->cls;
            cls3=(u16)st->cls;
            st->owner=0;
            if(st->wave>=H(D_L02_001B1190[cls1],0)) {
                if(cls3-7U<2 || cls1==13) D_0018B6F4=D_L02_001B1224;
                func_PAL_L00_003E38E8(1,-1); func_PAL_L00_004071F0(1,-1);
                if(!st->cls && !D_001395B8[arena_get_challenge_save_index(0)]) moby_set_state(actor,11,-1);
                else moby_set_state(actor,5,-1);
                st->result=st->cls;
                return;
            }
            if(cls1>=14) st->cls=13;
            func_PAL_L02_00401980(actor);
            row=P(D_L02_001B1190[st->cls],4);
            row+=st->wave*20;
            arena_match_active_count_a(actor,H(row,10)); arena_match_active_count_b(actor,H(row,8));
        }
        n=++st->frames;
        if((st->cls==3 && n>=1501) || (st->cls==5 && n>=3001)) {
            char *format, *buffer, *a, *b;
            int sum=0, j, count;
            buffer=text;
            for(j=0;j<6;j++) sum+=st->counts[j];
            format=D_L02_001B1228;
            a=GetLocalizedString(0x1B37);
            count=st->wave*15+sum-st->lost;
            b=GetLocalizedString(0xE86);
            sprintf(buffer,format,a,count,b);
            func_PAL_L00_0030FBC0(buffer,-1);
            moby_set_state(actor,10,-1); func_PAL_L00_003E38E8(1,-1); func_PAL_L00_004071F0(1,-1);
            return;
        }
        if(st->cls==7 && D_0018B068==30 && D_00139700<=0) {
            allowed=1;
            for(e=D_L02_001B35A8[0];e;e=P(e,0x28)) {
                if(B(e,0x20)==0xfe) continue;
                if(B(e,0x20)==0xfd) continue;
                if(H(e,0xaa)==0xc89 || H(e,0xaa)==0xbfe) allowed=0;
            }
            if(allowed) {
                func_PAL_L00_0030FBC0(GetLocalizedString(0x1B39),-1);
                moby_set_state(actor,10,-1); func_PAL_L00_003E38E8(1,-1); func_PAL_L00_004071F0(1,-1);
                return;
            }
        } else if(st->cls==8 && D_0018B068==42 && D_00139730<=0) {
            allowed=1;
            for(e=D_L02_001B35A8[0];e;e=P(e,0x28)) {
                if(B(e,0x20)==0xfe) continue;
                if(B(e,0x20)==0xfd) continue;
                if((unsigned short)(U(e,0xaa)-0xc06)<=1) allowed=0;
            }
            if(allowed) {
                func_PAL_L00_0030FBC0(GetLocalizedString(0x1B3A),-1);
                moby_set_state(actor,10,-1); func_PAL_L00_003E38E8(1,-1); func_PAL_L00_004071F0(1,-1);
                return;
            }
        } else if(st->cls==12) {
            if(D_0018C2EC<g_current_map_index[4]) {
                { MaktarFlags *g=(MaktarFlags *)D_L02_001BA3C0; if(g->owner==st->owner) g->owner=0; }
                st->owner=0;
                func_PAL_L00_0030FBC0(GetLocalizedString(0x1B38),-1);
                moby_set_state(actor,10,-1); func_PAL_L00_003E38E8(1,-1); func_PAL_L00_004071F0(1,-1);
                return;
            }
            if(st->frames>=6001) {
                part_queue_moby_for_glow(st->owner,0,chainblade_reset_to_idle);
                { MaktarFlags *g=(MaktarFlags *)D_L02_001BA3C0; if(g->owner==st->owner) g->owner=0; }
                st->owner=0;
                moby_set_state(actor,5,-1); func_PAL_L00_003E38E8(1,-1); func_PAL_L00_004071F0(1,-1);
                return;
            }
        } else if(st->cls==13 && D_0018C2EC<g_current_map_index[4]) {
            func_PAL_L00_0030FBC0(GetLocalizedString(0x1B38),-1);
            moby_set_state(actor,10,-1); func_PAL_L00_003E38E8(1,-1); func_PAL_L00_004071F0(1,-1);
            return;
        }
        gfx_add_draw_callback_first(DrawMaktarChallengeHud,actor);
        row=P(D_L02_001B1190[st->cls],4)+st->wave*20;
        if(OBJ->timer<51 && !U(row,16)) goto spawn;
        arena_clear_spawn_slots(actor); spawned=0; actor_pick_watched_entity(actor);
        if(st->slots[st->slot] && moby_has_free_child_slot_state2(st->slots[st->slot])) {
            int i;
            for(i=st->counts[3];i<H(row,6);i++) spawned|=arena_claim_enemy(actor,0xc3e);
            for(i=st->counts[1];i<H(row,2);i++) spawned|=arena_claim_enemy(actor,0xb22);
            for(i=st->counts[2];i<H(row,4);i++) spawned|=arena_claim_enemy(actor,0xc3b);
            for(i=st->counts[0];i<H(row,0);i++) spawned|=arena_claim_enemy(actor,0x9ca);
        }
        if(!st->counts[4] && B(row,16) && !st->counts[5] && B(row,17)) {
            char *a, *b;
            a=arena_claim_boss(actor,0x9f8,0); b=arena_claim_boss(actor,0xa44,1);
            chainblade_set_helper(a,b); brawler_set_watched_entity(b,a); chainblade_advance_health_phase(a); st->owner=a;
            { MaktarFlags *g=(MaktarFlags *)D_L02_001BA3C0; if(!g->owner) { g->owner=a; g->timer=0; } }
            if(!D_L02_001B3770[0]) { D_L02_001B3770[0]=a; mem_clear(D_L02_001FF6B8,0,224); }
            if(!D_L02_001B3770[1]) { char *buf=D_L02_001FF6B8; D_L02_001B3770[1]=b; mem_clear(buf+224,0,224); }
            arena_start_announcer_message(actor,15); script_queue_keyed_request(st->track,st->trackVolume);
        } else if(!st->counts[4] && B(row,16)) {
            char *a;
            a=arena_claim_boss(actor,0x9f8,0); st->owner=a;
            { MaktarFlags *g=(MaktarFlags *)D_L02_001BA3C0; if(!g->owner) { g->owner=a; g->timer=0; } }
            { char *snd=st->owner; if(!D_L02_001B3770[0]) { D_L02_001B3770[0]=snd; mem_clear(D_L02_001FF6B8,0,224); } }
            arena_start_announcer_message(actor,14); script_queue_keyed_request(st->track,st->trackVolume);
        } else if(!st->counts[5] && B(row,17)) {
            char *a;
            a=arena_claim_boss(actor,0xa44,0); st->owner=a;
            { MaktarFlags *g=(MaktarFlags *)D_L02_001BA3C0; if(!g->owner) { g->owner=a; g->timer=0; } }
            { char *snd=st->owner; if(!D_L02_001B3770[1]) { char *buf=D_L02_001FF6B8; D_L02_001B3770[1]=snd; mem_clear(buf+224,0,224); } }
            arena_start_announcer_message(actor,20); script_queue_keyed_request(st->track,st->trackVolume);
        }
        if(!U(row,16)) { char *g=g_music_state; if(B(g,0x48)!=st->music && B(g,0x3c)!=st->music) script_queue_keyed_request(st->music,st->volume); }
        if(spawned) arena_activate_spawn_slots(actor);
    spawn:
        if(st->cls==7) moby_handle_request_slot_state(30);
        else if(st->cls==8) moby_handle_request_slot_state(42);
        else if(st->cls==13) { moby_handle_request_slot_state(10); D_0018C0D7=1; }
        func_PAL_L02_00401118(actor); actor_pick_watched_message(actor);
        if(!(D_001A7BC0[0]&3)) arena_pick_nearest_attackers(actor);
        func_PAL_L02_00400F20(actor); gfx_add_draw_callback_first(func_PAL_L02_004046D0,actor);
        if(arena_get_challenge_progress_index(st->cls)!=-1) {
            D_L02_001AA1B0[0]=arena_get_challenge_progress_index(st->cls); D_L02_001B3680[0]=D_001A7390[0];
        }
        break;
    }
    }
    func_PAL_L02_003FF640(actor);
}
