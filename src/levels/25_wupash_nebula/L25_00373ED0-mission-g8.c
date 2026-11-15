#include "names.h"
/* func_L25_0040CDA0, the level's mission update (setup, timer, completion).
   The function lives in its own small-data unit; its callees func_L25_003752D8, 00376FE0 and
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
    int timerVisible;
    float scale;
    char pad34[0x20];
    int (*deathCallback)(char *, int);
    char pad58[0x20];
    char *owner;
} MissionContext;
typedef struct InventoryView {
    char pad00[0x51c];
    unsigned short dialogue;
    char pad51e[0x186];
    unsigned int completed;
} InventoryView;
extern MissionContext D_L25_00221850;
extern InventoryView g_subtitle_history;
extern char *D_L25_001B0CE0 __attribute__((sda));
extern int D_L25_001B0CD0 __attribute__((sda)), D_L25_001B0CD4 __attribute__((sda));
extern int D_L25_001B0CD8 __attribute__((sda)), D_L25_001B0CDC __attribute__((sda));
extern int D_L25_001B0CC0 __attribute__((sda)), D_L25_001B0CB0 __attribute__((sda));
extern int D_L25_001B0CF8 __attribute__((sda));
extern char *g_hero_moby __attribute__((nosda));

extern int D_L25_001B3060 MACRO_ADDR, D_L25_001B1BC8 MACRO_ADDR;
extern int D_L25_001B209C MACRO_ADDR;
extern int D_00138324 __attribute__((nosda));
extern char *D_L25_001A904C MACRO_ADDR;
extern float D_L25_001B2904 MACRO_ADDR;
extern unsigned char D_001A7C01 MACRO_ADDR;
extern int g_current_map_index MACRO_ADDR;
extern int moby_tick_death_timer(char *,int);
extern int subtitle_request_voice_line(int,int);
extern int math_fast_float_d(void *);
extern void level_select_random_object(void);
extern void level_store_pair_with_increment(int,int);
extern int snd_play_from_class_bank(int,int,char *,int);
extern int DrawWupashCombatHud(void);
extern void level_store_value_pair(int,void *);
extern void ship_start_transition(void *,void *,int);
extern void ship_point_camera_at_target(void *,void *);
extern void entry_init_all_registered(void);
extern void data_set_small_value_and_refresh(int,int);
extern void effect_remove_family_mobys(void);
extern int cam_is_mode_active(void);
#define I(p,o) (*(int *)((char *)(p)+(o)))
#define F(p,o) (*(float *)((char *)(p)+(o)))
#define B(p,o) (*(unsigned char *)((char *)(p)+(o)))
#define H(p,o) (*(unsigned short *)((char *)(p)+(o)))

extern void level_offer_entries_ptr(u8 *);
extern void level_offer_entries_float(u8 *, f32);
extern void level_offer_entries_float_alt(u8 *, f32);


extern int D_L25_001B2900;

/* label_y, the HUD label idiom (accepted 7 November 2026; one shared definition, `active` the
   literal 1 at every call). Its tests do not change the result: flow deletes their stores and
   jump2 their jumps, but only after allocation and both scheduling passes. */
static __inline__ int label_y(void *handle, float value, float scale, float half, int active)
{
    int mode = D_L25_001B2900;
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

/* Updates the mission object: sets up the level, runs the timer and moves on when the mission is done. */
void mission_timer_update(char *mission_moby)
{
    char *vars = *(char **)(mission_moby+0x68);
    float target_pos_a[4] __attribute__((aligned(16)));
    float target_pos_b[4] __attribute__((aligned(16)));
    float cam_pos[4] __attribute__((aligned(16)));
    float cam_look_at[4] __attribute__((aligned(16)));
    int wait_counter;
    int active = 1;
    MissionContext *ctx;
    switch (B(mission_moby,0x20)) {
    case 0:
        ctx = &D_L25_00221850;
        
        ctx->scale=8.0f;
        ctx->deathCallback=moby_tick_death_timer;
        D_L25_001B0CE0=mission_moby;
        D_L25_001B0CD0=0; D_L25_001B0CD4=0;
        D_L25_001B0CD8=0; D_L25_001B0CDC=0;
        H(mission_moby,0x32)=0x1ff; B(mission_moby,0x30)=0xff; B(mission_moby,0x20)=1;
        I(vars,0x2c)=150; I(vars,0x30)=300;
        I(vars,0x38)=180; I(vars,0x34)=720; I(vars,0x24)=0;
        ctx->health=*(float **)vars;
        ctx->enabled=1;
        D_L25_001B3060=540;
        ctx->owner=mission_moby;
        if (g_hero_moby) H(g_hero_moby,0x34)|=0x41;
    case 1:
        
        if (!g_subtitle_history.dialogue) subtitle_request_voice_line(0xa16,0x6d);
        
        if (math_fast_float_d(vars+0x34)) D_L25_00221850.timerVisible=0;
        else D_L25_00221850.timerVisible=1;
        active = 1;
        level_select_random_object();
        level_store_pair_with_increment(label_y(mission_moby, -224.0f, D_L25_001B2904, 0.5f, 1),2);
        qcopy(mission_moby+0x10,(void *)((I(vars,0x20)<<8) + D_L25_001B209C + 0x10));
        if (D_00138324&0x10) snd_play_from_class_bank(0,0,mission_moby,0xeee);
        if (D_L25_001A904C && !D_L25_001B0CDC) {
            level_store_value_pair(0,DrawWupashCombatHud);
            D_L25_001B0CDC=active;
        }
        /* Retail executes this counted wait before reading the mission vars:
           6, decrement, padded backward bgez, decrement in its waitCounter slot. */
        for (wait_counter=6; wait_counter>=0; wait_counter--) {}
        if (D_L25_00221850.paused || D_L25_001B1BC8<6) break;
        if (D_L25_00221850.completed<=0) {
            D_L25_00221850.timerVisible=1;
            if (!math_fast_float_d(vars+0x2c)) break;
            I(vars,0x2c)=540;
            ship_start_transition(&D_L25_001B0CC0,&D_L25_001B0CB0,240);
            *(Quad *)target_pos_a=0; *(Quad *)target_pos_b=0;
            B(mission_moby,0x20)=3;
            target_pos_a[0]=359.0f; target_pos_a[1]=440.0f; target_pos_a[2]=524.0f;
            target_pos_b[0]=403.0f; target_pos_b[1]=456.0f; target_pos_b[2]=524.0f;
            level_offer_entries_ptr((u8 *)1);
            level_offer_entries_float((u8 *)target_pos_a,10.0f); level_offer_entries_float_alt((u8 *)target_pos_b,10.0f);
            *(Quad *)cam_look_at = *(Quad *)cam_pos = 0;
            cam_pos[0]=417.18f; cam_pos[1]=454.03f; cam_pos[2]=532.6f;
            cam_look_at[0]=420.93f; cam_look_at[1]=413.79f; cam_look_at[2]=534.54f;
            ship_point_camera_at_target(cam_pos,cam_look_at);
        } else {
            if (math_fast_float_d(vars+0x2c)) {
                entry_init_all_registered(); level_store_value_pair(0,0);
                D_001A7C01=1; data_set_small_value_and_refresh(2,1);
            } else {
                if (!D_L25_001B0CF8) {
                    effect_remove_family_mobys(); D_L25_001B0CF8=1;
                }
                { u32 seen = g_subtitle_history.completed & (1u << g_current_map_index);
                if (!seen) subtitle_request_voice_line(0xa36,0x8d); }
            }
        }
        break;
    case 2:
        break;
    case 3:
        
        if (!cam_is_mode_active()) {
            D_L25_00221850.timerVisible=0;
            D_L25_00221850.completed++;
            B(mission_moby,0x20)=active;
        }
        break;
    }
}
