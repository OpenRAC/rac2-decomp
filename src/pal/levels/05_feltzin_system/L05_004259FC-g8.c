#include "include_asm.h"

#include "common.h"
extern u8 *D_L05_001B251C;
extern u8 g_sound_state[];
extern int D_L05_001A8F00;
extern int D_L05_001A904C __attribute__((sda));
extern int D_L05_001B13F0 __attribute__((sda));
extern int D_L05_001B1350[] MACRO_ADDR;
extern int D_L05_001B1350_gp[] SDATA(D_L05_001B1350);
extern int D_L05_001B13F8[][3];
extern int D_L05_001B13F8_gp[][3] SDATA(D_L05_001B13F8);
extern int D_L05_001B13AC __attribute__((sda));
extern int D_L05_001B13A8 __attribute__((sda));
extern int D_L05_001B13EC __attribute__((sda));
extern int D_L05_001B3578;
extern u8 D_001A7A0A;
extern int g_player_bolts;
extern int D_001A79F8_gp SDATA(D_001A79F8);
extern unsigned int D_00138324;
extern void snd_stop_voice(int);
extern int math_fast_float_d(void *);
extern void FadeToBlack(int);
extern void func_PAL_0029C0F0(int, int);
extern int hud_draw_feltzin_mission_reward(void);
extern void feltzin_mission_clamp_save_counts(void);
extern int MemcardSave(int, int);
extern void hero_set_state_value_c(int);
extern void feltzin_challenge_reset(void *);
extern int request_begin_slot(int, int, int, int, u8 *);
typedef struct { u8 pad[0x270]; int id; } MissionState;

/* Once per mission slot: pays the bolt reward for this completion (the table's column is capped
   at the third, times ten when D_001A7A0A is set), then waits for the prompt's buttons. */
void func_PAL_L05_00425FB0(u8 *actor, int mission)
{
    u8 *state = *(u8 **)(actor + 0x68);
    u8 *owner = D_L05_001B251C + (*(int *)(state + 0x24) << 8);
    MissionState *ownerState = *(MissionState **)(owner + 0x68);
    int sound = ownerState->id;
    if (sound != -1) {
        u8 *record = g_sound_state + sound * 0x70;
        if (*(u8 **)(record + 0x88) == owner && record[0x74] != 0)
            snd_stop_voice(sound);
    }
    ownerState->id = -1;
    if (D_L05_001A8F00 == 2)
        return;
    if (math_fast_float_d(state + 0x58) == 0)
        return;
    if (D_L05_001A904C != 0 && D_L05_001B13F0 == 0) {
        int *count;
        int previous;
        int rank;
        int reward;
        FadeToBlack(25);
        func_PAL_0029C0F0(0, (int)hud_draw_feltzin_mission_reward);
        count = &D_L05_001B1350_gp[mission];
        previous = *count;
        rank = previous < 3 ? previous : 2;
        D_L05_001B13F0 = 1;
        D_L05_001B3578 = mission;
        D_L05_001B13AC = 0;
        D_L05_001B13A8 = 0;
        reward = D_L05_001B13F8_gp[mission][rank];
        if (D_001A7A0A != 0)
            reward *= 10;
        D_001A79F8_gp = g_player_bolts + reward;
        *count = previous + 1;
        feltzin_mission_clamp_save_counts();
        MemcardSave(0, -1);
    }
    hero_set_state_value_c(1);
    if (math_fast_float_d(state + 0x40) == 0) {
        unsigned int buttons = D_00138324;
        int completed = buttons & 0x40;
        if (completed) {
            D_L05_001B13F0 = 0;
            *(int *)(state + 0x40) = 4500;
            FadeToBlack(25);
            hero_set_state_value_c(0);
            *(int *)(state + 0x58) = 100;
            *(int *)(state + 0x44) = 6000;
            if (D_L05_001B1350_gp[0] != 0) {
                completed = D_L05_001B1350[1];
                if (completed != 0 && D_L05_001B1350[2] != 0)
                    D_L05_001B13EC = 3;
                else if (D_L05_001B1350_gp[0] != 0) {
                    if (completed != 0)
                        D_L05_001B13EC = 2;
                    else
                        D_L05_001B13EC = 1;
                }
            }
            feltzin_challenge_reset(actor);
        } else if (buttons & 0x10) {
            request_begin_slot(3, 1, 4, 0, 0);
        }
    } else {
        *(int *)(state + 0x40) = 500;
    }
}
