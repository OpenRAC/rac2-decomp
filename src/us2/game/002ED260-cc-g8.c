#include "names.h"
/* func_US2_002ED260, the USA v2.00 copy of func_002EC408: the same C, where rename func_00298F00 becomes func_US2_00299CF0; rename func_002E9268 becomes func_US2_002EA0C0; rename func_002EA8E8 becomes func_US2_002EB740; rename func_00133710 becomes func_00133700; rename func_00132828 becomes func_00132818; rename func_001336D0 becomes func_001336C0. */
#include "common.h"
extern unsigned char g_map_unlocked_flags[] __attribute__((sda));
extern char D_00188660[], D_001A63A8_3[], D_00152C00[], D_001393E0[], D_001B9040[], D_001BAF80[], D_001BADC0[], D_001AC1E0[], D_001C5540[], D_00240450[], D_001B8840_raw[] __asm__("D_001B8840");
extern int g_equipment_pieces[];
extern int g_transition_pending_sound __attribute__((sda)), g_transition_flag __attribute__((sda));
extern void mem_clear(void *, int, int), FlushCache(int);
extern s16 snd_pump_music_and_disc_read(int);
extern void *snd_set_stop_callback(void (*)(s32));
extern int snd_Pump(void), snd_CheckLoadInProgress(int), sceGsSyncV(int), UpdatePlaybackScene_us2(void), ServiceLevelArchiveLoad(void);
extern char *CreateMoby(int);
extern void moby_clear_object_slots(), snd_send_cmd50_five_values(), snd_clear_flag_and_update(), snd_clear_all_voices(), snd_wait_for_music_idle(), snd_send_cmd6(), STUB_printf(), SetBackgroundColor(), mc_update_state_us2(), map_update_state_machine(), gfx_remove_dma_handlers(), FadeToBlack(), load_copy_setup_entry(), SpawnEquipmentPieces(), part_init_effect_table(), SubmitBufferedDmaChain(), gfx_swap_packet_buffer(), PutDrawBufferSmall(), gfx_queue_second_strip_packet(), gfx_append_draw_list_header(), pad_poll_ports(), gfx_wait_for_dma_status_bits(), InitializeLevelRuntime(), transition_draw_background_us2();
extern int LoadLevelChunkFromDisc();
extern void snd_send_cmd8();
extern int g_small_data_value[] __attribute__((sda));
extern int g_current_map_index[] __attribute__((sda));
extern int g_current_game_mode[] __attribute__((sda));
extern int g_progress_flags_d __attribute__((nosda));
extern int g_pad_button_mask __attribute__((nosda));
extern int g_progress_flags_a __attribute__((nosda));
extern int g_progress_flags_b __attribute__((nosda));
extern int g_progress_flags_c __attribute__((nosda));
extern int g_loader_archives[] __attribute__((sda));
extern int g_save_menu_flags[] __attribute__((sda));
extern int g_global_sound_bank_table[] __attribute__((sda));
extern int g_transition_effect_list[] __attribute__((sda));
extern unsigned char g_glow_marker_flag __attribute__((nosda));
extern unsigned char g_map_visited_flags[] __attribute__((sda));
extern int g_scene_sound_block_a[] MACRO_ADDR __attribute__((sda));
extern int g_frame_counter_3[] __attribute__((sda));

typedef struct { unsigned char a,b,c,pad; float x,y,z,w; } Config;
extern Config g_fog_color __attribute__((sda));
typedef struct { char pad[0x17a0]; int handles[6]; } TransitionEngine;
typedef struct { char pad[0x2c]; short phase, scene; } TransitionState;
typedef struct { char pad[0x18]; short requested; char pad1[0x142]; int state; int pad2; int request; char pad3[0x14]; int playing; } TransitionAudio;
typedef struct { char pad[0x218]; float near_plane, far_plane, pad2[2], near_intensity, far_intensity; int red, green, blue; } TransitionFog;
typedef struct { char pad[0x10]; unsigned flags; } TransitionArchive;
typedef struct { char pad[0x54]; char *current; } TransitionScene;

/* Runs the whole level transition: shows the transition scene until the next level is loaded (USA v2.00). */
void RunLevelTransition_us2(void)
{
    int i,ready,done,kind,current;
    mem_clear(g_visibility_bitmap,-1,0x80);
    g_current_game_mode[0]=6;
    ((TransitionState *)g_hero_moby_default)->phase=0;
    ((TransitionState *)g_hero_moby_default)->scene=0;
    if(g_small_data_value[0]==22 || g_current_map_index[0]==22) ((TransitionState *)g_hero_moby_default)->scene=1;
    else if(g_small_data_value[0]==23 || g_current_map_index[0]==23) ((TransitionState *)g_hero_moby_default)->scene=1;
    else if(g_small_data_value[0]==26 || g_current_map_index[0]==26) ((TransitionState *)g_hero_moby_default)->scene=2;
    if(g_small_data_value[0]==14 && !g_glow_marker_flag) ((TransitionState *)g_hero_moby_default)->scene=3;
    if(g_map_unlocked_flags[0] && g_small_data_value[0] && !(g_progress_flags_d&0x200)) g_transition_pending_sound=0xa9;
    else if(g_map_unlocked_flags[1] && g_small_data_value[0]!=1 && !(g_progress_flags_a&0x800000))g_transition_pending_sound=23;
    else if(g_map_unlocked_flags[5] && g_small_data_value[0]!=5 && !(g_progress_flags_d&0x800))g_transition_pending_sound=0xab;
    else if(g_map_unlocked_flags[8] && g_small_data_value[0]!=8 && !(g_pad_button_mask&0x2000))g_transition_pending_sound=0xad;
    else if((g_map_visited_flags[10] || g_map_visited_flags[11]) && !(g_progress_flags_b&0x4000000))g_transition_pending_sound=26;
    else if(g_small_data_value[0]==13 && !(g_progress_flags_b&0x8000000))g_transition_pending_sound=27;
    else if(g_map_unlocked_flags[16] && g_small_data_value[0]!=16 && !(g_pad_button_mask&0x8000))g_transition_pending_sound=0xaf;
    ((TransitionArchive *)g_collision_hit)->flags|=0x80000000;
    moby_clear_object_slots();
    FlushCache(0);
    snd_send_cmd50_five_values(2,0,0,0,0);
    snd_clear_flag_and_update();
    snd_Pump();
    snd_clear_all_voices();
    snd_wait_for_music_idle();
    D_001A63A8_3[7]=1;
    for (i=0; i<6; i++)if(((TransitionEngine *)g_sound_state)->handles[i]){
        snd_send_cmd6(((TransitionEngine *)g_sound_state)->handles[i]);
        snd_send_cmd8();
        STUB_printf(g_str_transition_handle,((TransitionEngine *)g_sound_state)->handles[i]);
        g_global_sound_bank_table[0]=0;
        ((TransitionEngine *)g_sound_state)->handles[i]=0;
    }
    ((TransitionFog *)g_view_params)->red=0;
    ((TransitionFog *)g_view_params)->green=0;
    ((TransitionFog *)g_view_params)->blue=16;
    ((TransitionFog *)g_view_params)->near_plane=0;
    ((TransitionFog *)g_view_params)->far_plane=524288.0f;
    ((TransitionFog *)g_view_params)->near_intensity=255.0f;
    ((TransitionFog *)g_view_params)->far_intensity=128.0f;
    g_fog_color.a=*(unsigned char *)&((TransitionFog *)g_view_params)->red;
    g_fog_color.b=*(unsigned char *)&((TransitionFog *)g_view_params)->green;
    g_fog_color.c=*(unsigned char *)&((TransitionFog *)g_view_params)->blue;
    g_fog_color.x=((TransitionFog *)g_view_params)->near_plane;
    g_fog_color.y=((TransitionFog *)g_view_params)->far_plane;
    g_fog_color.z=((TransitionFog *)g_view_params)->near_intensity;
    g_fog_color.w=((TransitionFog *)g_view_params)->far_intensity;
    SetBackgroundColor(0,0,0);
    if(g_small_data_value[0]<0) {
        while(((TransitionAudio *)g_memcard_state)->state>=3 || ((TransitionAudio *)g_memcard_state)->request>=0){
            mc_update_state_us2();
            map_update_state_machine();
        }
        if(((TransitionAudio *)g_memcard_state)->playing)((TransitionAudio *)g_memcard_state)->playing=0;
        if(((TransitionAudio *)g_memcard_state)->requested>=0)((TransitionAudio *)g_memcard_state)->requested=-1;
        g_save_menu_flags[0]=g_save_menu_flags[0]&~0x200;
        snd_set_stop_callback(0);
        D_001A63A8_3[7]=0;
        snd_pump_music_and_disc_read(1);
        while(snd_Pump()){
        }
        D_001A63A8_3[7]=1;
        FadeToBlack(6);
        g_current_map_index[0]=g_small_data_value[0];
        LoadLevelChunkFromDisc();
        snd_CheckLoadInProgress(0);
        D_001A63A8_3[7]=0;
        gfx_remove_dma_handlers();
        return;
    }
    current=g_current_map_index[0];
    if((unsigned)current<19 && (current || (g_progress_flags_c&2)) && current<28)g_map_unlocked_flags[current]=2;
    g_current_map_index[0]=g_small_data_value[0];
    g_loader_archives[0]=0;
    g_loader_archives[1]=1;
    ((TransitionArchive *)g_collision_hit)->flags|=0x80000000;
    ready=0;
    InitializeLevelRuntime();
    load_copy_setup_entry(g_current_map_index[0],g_setup_entry_buffer);
    kind=((TransitionState *)g_hero_moby_default)->scene;
    if(kind==3){
        g_transition_effect_list[0]=CreateMoby(0x1342);
        *(unsigned short *)(((TransitionScene *)D_001B8840_raw)->current+0x34)|=1;
    }
    else if(kind==1){
        g_transition_effect_list[0]=CreateMoby(0x128c);
        *(unsigned short *)(((TransitionScene *)D_001B8840_raw)->current+0x34)|=1;
    }
    else if(kind==2){
        g_transition_effect_list[0]=CreateMoby(0x128d);
        *(unsigned short *)(((TransitionScene *)D_001B8840_raw)->current+0x34)|=1;
    }
    else{
        int i;
        for(i=0;g_equipment_pieces[i];i++)g_equipment_pieces[i]=0;
        SpawnEquipmentPieces(((TransitionScene *)D_001B8840_raw)->current);
    }
    part_init_effect_table(g_effect_record_table_2);
    do {
        SubmitBufferedDmaChain();
        gfx_swap_packet_buffer();
        PutDrawBufferSmall();
        gfx_queue_second_strip_packet();
        gfx_append_draw_list_header();
        pad_poll_ports();
        done=UpdatePlaybackScene_us2();
        transition_draw_background_us2();
        mc_update_state_us2();
        map_update_state_machine();
        gfx_wait_for_dma_status_bits(1);
        sceGsSyncV(0);
        g_frame_counter_3[0]=g_frame_counter_3[0]+1;
        if(!g_transition_pending_sound && !ready)ready=ServiceLevelArchiveLoad();
    }
    while(!done);
    g_transition_flag=0;
    if(!ready){
        do{
            FlushCache(0);
            sceGsSyncV(0);
            mc_update_state_us2();
            map_update_state_machine();
        }
        while(!ServiceLevelArchiveLoad());
    }
    while(((TransitionAudio *)g_memcard_state)->state!=2 || ((TransitionAudio *)g_memcard_state)->request>=0){
        FlushCache(0);
        sceGsSyncV(0);
        mc_update_state_us2();
        map_update_state_machine();
    }
    if(g_scene_sound_block_a[2])snd_send_cmd6(g_scene_sound_block_a[2]);
    if(g_scene_sound_block_a[4])snd_send_cmd6(g_scene_sound_block_a[4]);
    while(snd_Pump()){
    }
    snd_send_cmd8();
    snd_set_stop_callback(0);
    snd_CheckLoadInProgress(0);
    snd_CheckLoadInProgress(0);
    D_001A63A8_3[7]=0;
    gfx_remove_dma_handlers();
}
