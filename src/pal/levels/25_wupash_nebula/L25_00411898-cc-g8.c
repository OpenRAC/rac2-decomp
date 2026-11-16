#include "names.h"
/* func_PAL_L25_00411898, the PAL copy of func_L25_0040CDA0: the same C, where rename func_00288E18 becomes func_PAL_00289730; rename func_0029B758 becomes func_PAL_0029C0F0; rename func_L05_00442828 becomes func_PAL_L05_00448A58; rename func_L25_003752D8 becomes func_PAL_L25_00377A28. */
/* func_PAL_L25_00411898, the level's mission update (setup, timer, completion).
   The function lives in its own small-data unit; its callees func_PAL_L25_00377A28, 00376FE0 and
   00377608 are in L25_00373ED0-g8.c and really return void.

   The timer y passes through label_y, the HUD label idiom (see its comment, and
   L25_00373ED0-fade-g8.c). Its tests leave no instruction but keep the 1 in $s2 and decide
   the registers of the later quadword clears. Case 1 sets active = 1 again before
   func_L05_00379B60: retail sets $s2 there (addiu s2,zero,1 at +0x158). The countdown from six is
   in retail too (its backward branch and padding). */
#include "common.h"
typedef unsigned int Quad __attribute__((mode(TI)));

typedef struct MissionContext {
    float *health;
    char pad04[0xC];
    int paused;
    int completed;
    char pad18[0xC];
    int enabled;
    int pad28;
    int timer_visible;
    float scale;
    char pad34[0x20];
    int (*death_callback)(char *, int);
    char pad58[0x20];
    char *owner;
} MissionContext;
typedef struct InventoryView {
    char pad00[0x51c];
    unsigned short dialogue;
    char pad51e[0x186];
    unsigned int completed;
} InventoryView;
extern MissionContext g_hud_l25_state;
extern InventoryView g_subtitle_history;
extern char *g_mission_moby __attribute__((sda));
extern int g_hud_icon_a __attribute__((sda)), g_hud_icon_b __attribute__((sda));
extern int g_hud_icon_c __attribute__((sda)), g_mission_timer_active __attribute__((sda));
extern int g_mission_transition_start __attribute__((sda)), g_mission_transition_end __attribute__((sda));
extern int g_mission_family_mobys_removed __attribute__((sda));
extern char *g_hero_moby __attribute__((nosda));

extern int g_mission_timer_reset_value MACRO_ADDR, g_mission_timer_limit MACRO_ADDR;
extern int g_mission_entity_base MACRO_ADDR;
extern int g_pad_held_flags __attribute__((nosda));
extern char *g_hud_l25_resource_base MACRO_ADDR;
extern float g_hud_screen_scale MACRO_ADDR;
extern unsigned char g_mission_active_flag MACRO_ADDR;
extern int g_current_map_index MACRO_ADDR;
extern int moby_tick_death_timer(char *,int);
extern int subtitle_request_voice_line_pal(int,int);
extern int math_fast_float_d(void *);
extern void level_select_random_object(void);
extern void level_store_pair_with_increment(int,int);
extern int snd_play_from_class_bank(int,int,char *,int);
extern int DrawWupashCombatHud(void);
extern void level_store_value_pair_pal(int,void *);
extern void ship_start_transition_pal(void *,void *,int);
extern void ship_point_camera_at_target(void *,void *);
extern void entry_init_all_registered(void);
extern void data_set_small_value_and_refresh(int,int);
extern void effect_remove_family_mobys(void);
extern int cam_is_mode_active(void);
#define I(p,o) (*(int *)((char *)(p)+(o)))
#define B(p,o) (*(unsigned char *)((char *)(p)+(o)))
#define H(p,o) (*(unsigned short *)((char *)(p)+(o)))

extern void level_offer_entries_ptr_pal(u8 *);
extern void level_offer_entries_float(u8 *, f32);
extern void level_offer_entries_float_alt(u8 *, f32);

extern int g_hud_l25_layout_mode;

/* label_y, the HUD label idiom (accepted 7 November 2026; one shared definition, `active` the
   literal 1 at every call). Its tests do not change the result: flow deletes their stores and
   jump2 their jumps, but only after allocation and both scheduling passes. */
static __inline__ int label_y(void *handle, float value, float scale, float half, int active)
{
    int mode = g_hud_l25_layout_mode;
    float scaled = value * scale + half;
    int result = (int)scaled;
    void *copy;

    if (mode == active)
        scaled = scale;
    if (handle != 0)
        scaled = scale;
    copy = handle;
    if (copy != 0)
        scaled = half;
    return result;
}

/* The level's mission update (setup, timer, completion) (PAL). */
void mission_timer_update_pal(char *moby)
{
    char *vars = *(char **)(moby+0x68);
    float point_a[4] __attribute__((aligned(16)));
    float point_b[4] __attribute__((aligned(16)));
    float cam_pos[4] __attribute__((aligned(16)));
    float cam_target[4] __attribute__((aligned(16)));
    int delay;
    int active = 1;
    MissionContext *mission;
    switch (B(moby,0x20)) {
    case 0:
        mission = &g_hud_l25_state;
        
        mission->scale=8.0f;
        mission->death_callback=moby_tick_death_timer;
        g_mission_moby=moby;
        g_hud_icon_a=0; g_hud_icon_b=0;
        g_hud_icon_c=0; g_mission_timer_active=0;
        H(moby,0x32)=0x1ff; B(moby,0x30)=0xff; B(moby,0x20)=1;
        I(vars,0x2c)=125; I(vars,0x30)=250;
        I(vars,0x38)=150; I(vars,0x34)=600; I(vars,0x24)=0;
        mission->health=*(float **)vars;
        mission->enabled=1;
        g_mission_timer_reset_value=450;
        mission->owner=moby;
        if (g_hero_moby) H(g_hero_moby,0x34)|=0x41;
    case 1:
        
        if (!g_subtitle_history.dialogue) subtitle_request_voice_line_pal(0xa16,0x6d);
        
        if (math_fast_float_d(vars+0x34)) g_hud_l25_state.timer_visible=0;
        else g_hud_l25_state.timer_visible=1;
        active = 1;
        level_select_random_object();
        level_store_pair_with_increment(label_y(moby, -224.0f, g_hud_screen_scale, 0.5f, 1),2);
        qcopy(moby+0x10,(void *)((I(vars,0x20)<<8) + g_mission_entity_base + 0x10));
        if (g_pad_held_flags&0x10) snd_play_from_class_bank(0,0,moby,0xeee);
        if (g_hud_l25_resource_base && !g_mission_timer_active) {
            level_store_value_pair_pal(0,DrawWupashCombatHud);
            g_mission_timer_active=active;
        }
        /* Retail executes this counted wait before reading the mission state:
           6, decrement, padded backward bgez, decrement in its delay slot. */
        for (delay=6; delay>=0; delay--) {}
        if (g_hud_l25_state.paused || g_mission_timer_limit<6) break;
        if (g_hud_l25_state.completed<=0) {
            g_hud_l25_state.timer_visible=1;
            if (!math_fast_float_d(vars+0x2c)) break;
            I(vars,0x2c)=450;
            ship_start_transition_pal(&g_mission_transition_start,&g_mission_transition_end,240);
            *(Quad *)point_a=0; *(Quad *)point_b=0;
            B(moby,0x20)=3;
            point_a[0]=359.0f; point_a[1]=440.0f; point_a[2]=524.0f;
            point_b[0]=403.0f; point_b[1]=456.0f; point_b[2]=524.0f;
            level_offer_entries_ptr_pal((u8 *)1);
            level_offer_entries_float((u8 *)point_a,10.0f); level_offer_entries_float_alt((u8 *)point_b,10.0f);
            *(Quad *)cam_target = *(Quad *)cam_pos = 0;
            cam_pos[0]=417.18f; cam_pos[1]=454.03f; cam_pos[2]=532.6f;
            cam_target[0]=420.93f; cam_target[1]=413.79f; cam_target[2]=534.54f;
            ship_point_camera_at_target(cam_pos,cam_target);
        } else {
            if (math_fast_float_d(vars+0x2c)) {
                entry_init_all_registered(); level_store_value_pair_pal(0,0);
                g_mission_active_flag=1; data_set_small_value_and_refresh(2,1);
            } else {
                if (!g_mission_family_mobys_removed) {
                    effect_remove_family_mobys(); g_mission_family_mobys_removed=1;
                }
                { u32 seen = g_subtitle_history.completed & (1u << g_current_map_index);
                if (!seen) subtitle_request_voice_line_pal(0xa36,0x8d); }
            }
        }
        break;
    case 2:
        break;
    case 3:
        
        if (!cam_is_mode_active()) {
            g_hud_l25_state.timer_visible=0;
            g_hud_l25_state.completed++;
            B(moby,0x20)=active;
        }
        break;
    }
}
