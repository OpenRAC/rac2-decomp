#include "include_asm.h"

#include "common.h"
extern int g_museum_selector_flag __attribute__((sda));
extern char g_hero_position[];
extern struct { char pad[0x24]; int pending; char gap[0x40]; int busy; short timer; char gap2[4]; unsigned short mode; } g_music_state;
extern int g_pad_held_flags NOT_SDA;
extern void moby_set_state(void *,int,int);
extern s32 snd_resume_music_stream(void);
extern int ForceClaimNotice(int,int,int);
extern int museum_find_active_exhibit_entry(void *),museum_start_exhibit_entry_timer(void *),museum_schedule_next_exhibit_entry(void *),IsPointInCuboid(void *,int);
extern void gfx_queue_draw_callback(void *,void *),museum_draw_selected_exhibit_entry_pal(char *);

/* Updates the museum exhibit selector. It finds an active entry, shows it, and steps through the show and wait states (PAL version). */
void museum_exhibit_selector_update_pal(unsigned char *obj) {
    char *st=*(char **)(obj+0x68);
    switch(obj[0x20]) {
    case 0:
        obj[0x30]=255; g_museum_selector_flag=0;
        *(int *)(st+0x140)=-1; *(int *)(st+0x144)=0;
        moby_set_state(obj,1,-1); break;
    case 1: if(museum_find_active_exhibit_entry(obj)!=-1) moby_set_state(obj,2,-1); break;
    case 2:
        if(!IsPointInCuboid(g_hero_position,*(int *)(st+0x140))) moby_set_state(obj,1,-1);
        else if(g_pad_held_flags&0x10) moby_set_state(obj,3,-1);
        else ForceClaimNotice(12,0x1BC7,1);
        break;
    case 3: if(museum_schedule_next_exhibit_entry(obj)) moby_set_state(obj,4,-1);
        gfx_queue_draw_callback(museum_draw_selected_exhibit_entry_pal,obj); break;
    case 4:
        if((short)g_music_state.mode==3 && g_music_state.timer<6000) {snd_resume_music_stream();moby_set_state(obj,5,-1);}
        gfx_queue_draw_callback(museum_draw_selected_exhibit_entry_pal,obj); break;
    case 5:
        if(museum_start_exhibit_entry_timer(obj)) moby_set_state(obj,6,-1);
        gfx_queue_draw_callback(museum_draw_selected_exhibit_entry_pal,obj); break;
    case 6:
        if((short)g_music_state.mode==3 && g_music_state.timer<6000) {snd_resume_music_stream();moby_set_state(obj,7,-1);}
        gfx_queue_draw_callback(museum_draw_selected_exhibit_entry_pal,obj); break;
    case 7:
        if(*(unsigned short *)(obj+0x96)>=10 && g_music_state.busy==0 && g_music_state.pending==-1) moby_set_state(obj,2,-1);
        gfx_queue_draw_callback(museum_draw_selected_exhibit_entry_pal,obj); break;
    }
    if(obj[0x20]>=3) {
        ForceClaimNotice(1,0,1);
        if((g_pad_held_flags&0x10) && (g_music_state.busy!=0 || g_music_state.pending!=-1)) {
            if((unsigned)(g_music_state.mode-6)>=2) g_music_state.mode=5;
            moby_set_state(obj,2,-1);
        }
    }
    ++*(unsigned short *)(obj+0x96);
}
