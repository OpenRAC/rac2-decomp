#include "names.h"
/* func_US2_002ED260, the USA v2.00 copy of func_002EC408: the same C, where rename func_00298F00 becomes func_US2_00299CF0; rename func_002E9268 becomes func_US2_002EA0C0; rename func_002EA8E8 becomes func_US2_002EB740; rename func_00133710 becomes func_00133700; rename func_00132828 becomes func_00132818; rename func_001336D0 becomes func_001336C0. */
#include "common.h"
extern unsigned char D_001A7BE8[] __attribute__((sda));
extern char D_00188660[], D_001A63A8_3[], D_00152C00[], D_001393E0[], D_001B9040[], D_001BAF80[], D_001BADC0[], D_001AC1E0[], D_001C5540[], D_00240450[], D_001B8840_raw[] __asm__("D_001B8840");
extern int g_equipment_pieces[];
extern int D_001ABEB0 __attribute__((sda)), D_001ABF0C __attribute__((sda));
extern void mem_clear(void *, int, int), FlushCache(int), snd_pump_music_and_disc_read(int);
extern void *snd_set_stop_callback(void (*)(s32));
extern int snd_Pump(void), snd_CheckLoadInProgress(int), sceGsSyncV(int), CreateMoby(int), func_US2_002EA0C0(void), ServiceLevelArchiveLoad(void);
extern void moby_clear_object_slots(),
    func_00133700(),
    func_00133230(),
    func_002E5FE0(),
    func_002B7170(),
    func_00132858(),
    func_00132818(),
    func_0026FEB8(),
    func_00284E18(),
    func_US2_00299CF0(),
    func_00298178(),
    func_002939D0(),
    func_002FCDA8(),
    func_0027D330(),
    func_00133AA0(),
    func_002E6178(),
    func_002ED260(),
    func_002FC280(),
    func_002FC220(),
    func_00284FC0(),
    func_00285338(),
    func_00284EA8(),
    func_002B9000(),
    func_002FC3C0(),
    func_002EAB18(),
    func_US2_002EB740();
extern int D_001B1680[] __attribute__((sda));
extern int g_current_map_index[] __attribute__((sda));
extern int g_current_game_mode[] __attribute__((sda));
extern int D_00139810 __attribute__((nosda));
extern int D_00139814 __attribute__((nosda));
extern int D_0013977C __attribute__((nosda));
extern int D_00139780 __attribute__((nosda));
extern int D_00139788 __attribute__((nosda));
extern int D_001A7280[] __attribute__((sda));
extern int g_save_menu_flags[] __attribute__((sda));
extern int D_001B16AC[] __attribute__((sda));
extern int D_001B2148[] __attribute__((sda));
extern unsigned char D_001395E3 __attribute__((nosda));
extern unsigned char D_001A7BC8[] __attribute__((sda));
extern int D_001B2130[] MACRO_ADDR __attribute__((sda));
extern int D_001B1598[] __attribute__((sda));

typedef struct { unsigned char a,b,c,pad; float x,y,z,w; } Config;
extern Config D_001B1640 __attribute__((sda));
typedef struct { char pad[0x17a0]; int handles[6]; } TransitionEngine;
typedef struct { char pad[0x2c]; short phase, scene; } TransitionState;
typedef struct { char pad[0x18]; short requested; char pad1[0x142]; int state; int pad2; int request; char pad3[0x14]; int playing; } TransitionAudio;
typedef struct { char pad[0x218]; float near_plane, far_plane, pad2[2], near_intensity, far_intensity; int red, green, blue; } TransitionFog;
typedef struct { char pad[0x10]; unsigned flags; } TransitionArchive;
typedef struct { char pad[0x54]; char *current; } TransitionScene;

void func_US2_002ED260(void)
{
    int i,ready,done,kind,current;
    mem_clear(D_001BADC0,-1,0x80);
    g_current_game_mode[0]=6;
    ((TransitionState *)g_hero_moby_default)->phase=0;
    ((TransitionState *)g_hero_moby_default)->scene=0;
    if(D_001B1680[0]==22 || g_current_map_index[0]==22) ((TransitionState *)g_hero_moby_default)->scene=1;
    else if(D_001B1680[0]==23 || g_current_map_index[0]==23) ((TransitionState *)g_hero_moby_default)->scene=1;
    else if(D_001B1680[0]==26 || g_current_map_index[0]==26) ((TransitionState *)g_hero_moby_default)->scene=2;
    if(D_001B1680[0]==14 && !D_001395E3) ((TransitionState *)g_hero_moby_default)->scene=3;
    if(D_001A7BE8[0] && D_001B1680[0] && !(D_00139810&0x200)) D_001ABEB0=0xa9;
    else if(D_001A7BE8[1] && D_001B1680[0]!=1 && !(D_0013977C&0x800000))D_001ABEB0=23;
    else if(D_001A7BE8[5] && D_001B1680[0]!=5 && !(D_00139810&0x800))D_001ABEB0=0xab;
    else if(D_001A7BE8[8] && D_001B1680[0]!=8 && !(D_00139814&0x2000))D_001ABEB0=0xad;
    else if((D_001A7BC8[10] || D_001A7BC8[11]) && !(D_00139780&0x4000000))D_001ABEB0=26;
    else if(D_001B1680[0]==13 && !(D_00139780&0x8000000))D_001ABEB0=27;
    else if(D_001A7BE8[16] && D_001B1680[0]!=16 && !(D_00139814&0x8000))D_001ABEB0=0xaf;
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
        STUB_printf(D_001AC1E0,((TransitionEngine *)g_sound_state)->handles[i]);
        D_001B16AC[0]=0;
        ((TransitionEngine *)g_sound_state)->handles[i]=0;
    }
    ((TransitionFog *)D_001B9040)->red=0;
    ((TransitionFog *)D_001B9040)->green=0;
    ((TransitionFog *)D_001B9040)->blue=16;
    ((TransitionFog *)D_001B9040)->near_plane=0;
    ((TransitionFog *)D_001B9040)->far_plane=524288.0f;
    ((TransitionFog *)D_001B9040)->near_intensity=255.0f;
    ((TransitionFog *)D_001B9040)->far_intensity=128.0f;
    D_001B1640.a=*(unsigned char *)&((TransitionFog *)D_001B9040)->red;
    D_001B1640.b=*(unsigned char *)&((TransitionFog *)D_001B9040)->green;
    D_001B1640.c=*(unsigned char *)&((TransitionFog *)D_001B9040)->blue;
    D_001B1640.x=((TransitionFog *)D_001B9040)->near_plane;
    D_001B1640.y=((TransitionFog *)D_001B9040)->far_plane;
    D_001B1640.z=((TransitionFog *)D_001B9040)->near_intensity;
    D_001B1640.w=((TransitionFog *)D_001B9040)->far_intensity;
    SetBackgroundColor(0,0,0);
    if(D_001B1680[0]<0) {
        while(((TransitionAudio *)g_memcard_state)->state>=3 || ((TransitionAudio *)g_memcard_state)->request>=0){
            func_US2_00299CF0();
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
        g_current_map_index[0]=D_001B1680[0];
        LoadLevelChunkFromDisc();
        snd_CheckLoadInProgress(0);
        D_001A63A8_3[7]=0;
        gfx_remove_dma_handlers();
        return;
    }
    current=g_current_map_index[0];
    if((unsigned)current<19 && (current || (D_00139788&2)) && current<28)D_001A7BE8[current]=2;
    g_current_map_index[0]=D_001B1680[0];
    D_001A7280[0]=0;
    D_001A7280[1]=1;
    ((TransitionArchive *)g_collision_hit)->flags|=0x80000000;
    ready=0;
    InitializeLevelRuntime();
    load_copy_setup_entry(g_current_map_index[0],D_001C5540);
    kind=((TransitionState *)g_hero_moby_default)->scene;
    if(kind==3){
        D_001B2148[0]=CreateMoby(0x1342);
        *(unsigned short *)(((TransitionScene *)D_001B8840_raw)->current+0x34)|=1;
    }
    else if(kind==1){
        D_001B2148[0]=CreateMoby(0x128c);
        *(unsigned short *)(((TransitionScene *)D_001B8840_raw)->current+0x34)|=1;
    }
    else if(kind==2){
        D_001B2148[0]=CreateMoby(0x128d);
        *(unsigned short *)(((TransitionScene *)D_001B8840_raw)->current+0x34)|=1;
    }
    else{
        int i;
        for(i=0;g_equipment_pieces[i];i++)g_equipment_pieces[i]=0;
        SpawnEquipmentPieces(((TransitionScene *)D_001B8840_raw)->current);
    }
    part_init_effect_table(D_00240450);
    do {
        SubmitBufferedDmaChain();
        gfx_swap_packet_buffer();
        PutDrawBufferSmall();
        gfx_queue_second_strip_packet();
        gfx_append_draw_list_header();
        pad_poll_ports();
        done=func_US2_002EA0C0();
        func_US2_002EB740();
        func_US2_00299CF0();
        map_update_state_machine();
        gfx_wait_for_dma_status_bits(1);
        sceGsSyncV(0);
        D_001B1598[0]=D_001B1598[0]+1;
        if(!D_001ABEB0 && !ready)ready=ServiceLevelArchiveLoad();
    }
    while(!done);
    D_001ABF0C=0;
    if(!ready){
        do{
            FlushCache(0);
            sceGsSyncV(0);
            func_US2_00299CF0();
            map_update_state_machine();
        }
        while(!ServiceLevelArchiveLoad());
    }
    while(((TransitionAudio *)g_memcard_state)->state!=2 || ((TransitionAudio *)g_memcard_state)->request>=0){
        FlushCache(0);
        sceGsSyncV(0);
        func_US2_00299CF0();
        map_update_state_machine();
    }
    if(D_001B2130[2])snd_send_cmd6(D_001B2130[2]);
    if(D_001B2130[4])snd_send_cmd6(D_001B2130[4]);
    while(snd_Pump()){
    }
    snd_send_cmd8();
    snd_set_stop_callback(0);
    snd_CheckLoadInProgress(0);
    snd_CheckLoadInProgress(0);
    D_001A63A8_3[7]=0;
    gfx_remove_dma_handlers();
}
