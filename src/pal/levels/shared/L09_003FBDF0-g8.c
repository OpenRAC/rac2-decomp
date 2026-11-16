#include "include_asm.h"

#include "common.h"
extern const char g_str_enemy_state_debug[];
extern float g_trooper_limit_turn_a __attribute__((sda)), g_trooper_limit_turn_b __attribute__((sda));
extern float g_enemy_anim_limit_turn_a __attribute__((sda)), g_enemy_anim_limit_turn_b __attribute__((sda));
extern float g_trooper_limit_turn_c __attribute__((sda)), g_trooper_limit_turn_d __attribute__((sda));
extern void STUB_printf(const char *, ...);
extern void moby_set_controller_speed_limits(void *, float, float, float, float);
extern void anim_start_blended_pal(void *, int, int, int);
#define I(p,o) (*(int *)((p)+(o)))
#define F(p,o) (*(float *)((p)+(o)))
#define B(p,o) (*(unsigned char *)((p)+(o)))

/* Switches the enemy and its partner to a new animation and sets how fast it turns and moves in that animation (PAL). */
void enemy_set_animation_state_pal(char *object, int state, int start_frame, int blend_time) {
    char *data = *(char **)(object+0x68);
    STUB_printf(g_str_enemy_state_debug, *(short *)(object+0xB2), state);
    if (state == 12) {
        moby_set_controller_speed_limits(object, g_trooper_limit_turn_a * 0.00040000002f, g_trooper_limit_turn_b * 0.020000001f,
                      g_trooper_limit_turn_c * 6.981318e-06f, g_trooper_limit_turn_d * 0.0003490659f);
        F(data,0x118) += F(data,0x118);
    } else {
        moby_set_controller_speed_limits(object, g_enemy_anim_limit_turn_a * 0.00040000002f, g_enemy_anim_limit_turn_b * 0.020000001f,
                      g_trooper_limit_turn_c * 6.981318e-06f, g_trooper_limit_turn_d * 0.0003490659f);
        F(data,0x118) += F(data,0x118);
    }
    if ((unsigned)(state-13)<3) {
        I(data,0x6C)=0; I(data,0x70)=0; I(data,0x74)=0; I(data,0x78)=0; I(data,0x7C)=0;
        B(data,0x61)=15; B(data,0x62)=15; B(data,0x66)=15;
        B(data,0xBC)=7; B(data,0xBD)=19; B(data,0xBE)=7; B(data,0xBF)=19;
        B(data,0xC2)=7; B(data,0xC3)=19; B(data,0xC6)=1;
    } else if (state==16) {
        F(data,0x6C)=0.44000003f; F(data,0x70)=0.14000002f; F(data,0x74)=0.006f;
        F(data,0x78)=0.012f; F(data,0x7C)=0.006f;
        B(data,0x61)=18; B(data,0x62)=17; B(data,0x66)=20;
        B(data,0xBC)=5; B(data,0xBD)=9; B(data,0xBE)=4; B(data,0xBF)=7;
        B(data,0xC2)=10; B(data,0xC3)=17; B(data,0xC6)=0;
    }
    if ((I(data,0x428) || (I(data,0x2DC)!=-1 && I(data,0x2DC)==I(data,0x2B0))) && state!=15) {
        if (B(object,0x43)!=14) anim_start_blended_pal(object,14,start_frame,blend_time);
    } else if (B(object,0x43)!=state) anim_start_blended_pal(object,state,start_frame,blend_time);
    { char *partner=*(char **)(data+0x2F8);
    if (partner && B(partner,0x43)!=state) anim_start_blended_pal(partner,state,start_frame,blend_time); }
}
