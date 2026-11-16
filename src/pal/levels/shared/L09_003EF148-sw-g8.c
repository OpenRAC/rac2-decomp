#include "include_asm.h"

#include "common.h"
#define FIELD(p,t,o) (*(t *)((char *)(p)+(o)))
extern int g_hover_tank_disabled __attribute__((sda));
extern float g_hover_tank_limit_turn_a __attribute__((sda)), g_hover_tank_limit_turn_b __attribute__((sda)), g_hover_tank_limit_turn_c __attribute__((sda)), g_hover_tank_limit_turn_d __attribute__((sda));
extern float g_hover_tank_limit_move_a __attribute__((sda)), g_hover_tank_limit_move_b __attribute__((sda)), g_hover_tank_limit_move_c __attribute__((sda)), g_hover_tank_limit_move_d __attribute__((sda));
extern char g_str_hover_tank_debug[];
extern int moby_is_in_selected_zone(void *);
extern void enemy_step_animation(void *);
extern void STUB_printf(void *,int,int);
extern int flag_is_third_pending_set(void *);
extern void moby_set_state(void *,int,int);
extern void moby_set_controller_speed_limits(void *,float,float,float,float);
extern void func_PAL_002A7E68(void *,int,int,int);
extern int path_advance_index_and_move(void *,int);
extern int path_start_moby_on_entry(void *,int,int);
extern int path_get_entry_id(int);
extern int path_steer_moby_to_nearest(void *,int);
extern long long moby_dispatch_action_by_kind(void *,void *);
extern void moby_destroy_with_explosion_pal(void *);
extern void func_PAL_L09_003EDEE8(void *);
extern void func_PAL_L09_003EE908(void *);
extern void func_PAL_L09_003EDFA8(void *);
extern void enemy_bump_frame_counter(void *);

void hover_tank_update_pal(char *object)
{
    char *state;
    char *position;
    int ready;
    if (g_hover_tank_disabled) return;
    position=object+0x10;
    if (!moby_is_in_selected_zone(position)) return;
    state=FIELD(object,char *,0x68);
    enemy_step_animation(object);
    qcopy(position,state+0x330);
    switch (FIELD(object,unsigned char,0x95)) {
    case 0: STUB_printf(g_str_hover_tank_debug,FIELD(object,short,0xB2),FIELD(object,short,0xAA)); break;
    case 1:
        if (FIELD(state,int,0x154)==1 || flag_is_third_pending_set(object)) {
            FIELD(state,int,0x354)=FIELD(state,int,0x378);
            moby_set_state(object,2,2);
        }
        break;
    case 3:
        if (FIELD(state,int,0x154)==1) {
            moby_set_controller_speed_limits(object,g_hover_tank_limit_move_a*0.00040000002f,g_hover_tank_limit_move_b*0.020000001f,g_hover_tank_limit_move_c*6.981318e-06f,g_hover_tank_limit_move_d*0.0003490659f);
            moby_set_state(object,4,4);
        }
        break;
    case 2: case 5: break;
    case 4:
        if (FIELD(state,int,0x154)!=1 && !FIELD(state,unsigned char,0x369)) {
            if (FIELD(object,unsigned char,0x43)) func_PAL_002A7E68(object,0,0,0);
            moby_set_controller_speed_limits(object,g_hover_tank_limit_turn_a*0.00040000002f,g_hover_tank_limit_turn_b*0.020000001f,g_hover_tank_limit_turn_c*6.981318e-06f,g_hover_tank_limit_turn_d*0.0003490659f);
            moby_set_state(object,3,3);
        }
        break;
    }
    switch (FIELD(object,unsigned char,0x20)) {
    case 0: STUB_printf(g_str_hover_tank_debug,FIELD(object,short,0xB2),FIELD(object,short,0xAA)); break;
    case 1: break;
    case 2:
        ready = 1;
        if (FIELD(state,int,0x36C)!=-1) ready = path_advance_index_and_move(object,FIELD(state,int,0x36C)) != 0;
        if (ready) {
            moby_set_controller_speed_limits(object,g_hover_tank_limit_turn_a*0.00040000002f,g_hover_tank_limit_turn_b*0.020000001f,g_hover_tank_limit_turn_c*6.981318e-06f,g_hover_tank_limit_turn_d*0.0003490659f);
            path_start_moby_on_entry(object,FIELD(state,int,0x350),-1);
            FIELD(state,int,0x380)=1;
            moby_set_state(object,3,3);
        } break;
    case 3:
        ready = 1;
        if (FIELD(state,int,0x350)!=-1) ready = path_advance_index_and_move(object,FIELD(state,int,0x350)) != 0;
        if (ready) {
            if(FIELD(state,short,0x11A)) FIELD(state,short,0x11A)=0;
            else FIELD(state,short,0x11A)=path_get_entry_id(FIELD(state,int,0x350));
        } break;
    case 4:
        if(FIELD(state,int,0x350)!=-1) path_steer_moby_to_nearest(object,FIELD(state,int,0x350));
        break;
    case 5:
        if(moby_dispatch_action_by_kind(object,state+0x180)&2) {
            if(FIELD(state,float,0x20)<=0) moby_set_state(object,6,-1);
            else {
                FIELD(state,int,0x37C)=0;
                if(FIELD(state,int,0x380)) {
                    FIELD(state,unsigned char,0x369)=0;
                    FIELD(state,int,0x354)=FIELD(state,int,0x378);
                    moby_set_state(object,4,4);
                } else {
                    if(FIELD(object,unsigned char,0x43)) func_PAL_002A7E68(object,0,0,0);
                    FIELD(state,int,0x354)=FIELD(state,int,0x378);
                    moby_set_state(object,2,2);
                }
            }
        } break;
    case 6: moby_destroy_with_explosion_pal(object); break;
    }
    func_PAL_L09_003EDEE8(object);
    FIELD(object,int,0xF0)=0;
    func_PAL_L09_003EE908(object);
    func_PAL_L09_003EDFA8(object);
    enemy_bump_frame_counter(object);
}
