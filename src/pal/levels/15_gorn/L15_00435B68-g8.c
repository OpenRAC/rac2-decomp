#include "include_asm.h"

#include "common.h"
extern char *D_L15_001B261C;
extern char g_sound_state[];
typedef struct { char pad[0x270]; int id; } GornData;
extern int D_L15_001A8F00 MACRO_ADDR;
extern int D_L15_001A904C __attribute__((sda));
extern int D_L15_001B15CC __attribute__((sda));
extern int D_L15_001B1520[4] __attribute__((sda));
extern int D_L15_001B15D8[4][3] __attribute__((sda));
extern int D_L15_001B157C __attribute__((sda)), D_L15_001B1578 __attribute__((sda));
extern int D_L15_001B15C8 __attribute__((sda)), D_L15_001B15BC __attribute__((sda));
extern int D_L15_001B36A4, g_player_bolts;
extern unsigned char D_001A7A0A;
extern int D_00138324 NOT_SDA;
extern int D_L15_001B1520_4[] MACRO_ADDR;
extern void snd_stop_voice(int);
extern int math_fast_float_d(void *);
extern void FadeToBlack(int);
extern void func_PAL_0029C0F0(int, void *);
extern s32 func_PAL_L15_00435B68(void);
extern void snd_clamp_copy_volumes(void);
extern int MemcardSave(int,int);
extern void hero_set_state_value_c(int);
extern void ResetGornStageCounters(void *);
extern int request_begin_slot(int,int,int,int,int);

void func_PAL_L15_00436118(char *self, int stage)
{
    char *state = *(char **)(self + 0x68);
    char *obj = D_L15_001B261C + (*(int *)(state + 0x20) << 8);
    GornData *data = *(GornData **)(obj + 0x68);
    int id = data->id;
    if (id != -1) {
        char *entry = g_sound_state + id * 0x70;
        if (*(char **)(entry + 0x88) == obj && *(unsigned char *)(entry + 0x74))
            snd_stop_voice(id);
    }
    data->id = -1;
    if (D_L15_001A8F00 == 2) {
        return;
    }
    if (!math_fast_float_d(state + 0x6C)) {
        return;
    }
    if (D_L15_001A904C && !D_L15_001B15CC) {
        int count, value;
        FadeToBlack(25);
        func_PAL_0029C0F0(0, func_PAL_L15_00435B68);
        count = D_L15_001B1520[stage];
        value = D_L15_001B15D8[stage][count < 3 ? count : 2];
        D_L15_001B15CC = 1;
        D_L15_001B36A4 = stage;
        D_L15_001B157C = 0;
        D_L15_001B1578 = 0;
        if (D_001A7A0A) value *= 10;
        D_L15_001B1520[stage] = count + 1;
        g_player_bolts = g_player_bolts + value;
        snd_clamp_copy_volumes();
        MemcardSave(0, -1);
    }
    hero_set_state_value_c(1);
    if (!math_fast_float_d(state + 0x50)) {
        if (D_00138324 & 0x40) {
            D_L15_001B15CC = 0;
            *(int *)(state + 0x50) = 4500;
            FadeToBlack(25);
            hero_set_state_value_c(0);
            *(int *)(state + 0x6C) = 100;
            if (D_L15_001B1520[0]) {
                if (D_L15_001B1520_4[1] && D_L15_001B1520_4[2]) {
                    D_L15_001B15C8 = 3;
                } else if (D_L15_001B1520[0]) {
                    if (D_L15_001B1520_4[1]) {
                        D_L15_001B15C8 = 2;
                    } else {
                        D_L15_001B15C8 = 1;
                    }
                }
            }
            D_L15_001B15BC = 0;
            ResetGornStageCounters(self);
        } else if (D_00138324 & 0x10) {
            request_begin_slot(3, 1, 4, 0, 0);
        }
    } else {
        *(int *)(state + 0x50) = 4500;
    }
}
