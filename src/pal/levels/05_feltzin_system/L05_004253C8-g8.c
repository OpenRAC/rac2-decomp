#include "include_asm.h"
#include "common.h"
extern int g_feltzin_challenge_state[];
extern unsigned char g_ship_settings_byte_a;
extern unsigned char g_ship_settings_byte_b;
extern unsigned char g_ship_settings_byte_c;
extern float g_ship_settings_float_c;
extern float g_ship_settings_float_a;
extern float g_ship_settings_float_d;
extern float g_ship_settings_float_b;
extern int g_ship_settings_word;
extern unsigned char g_feltzin_record_flag_a;
extern unsigned char g_feltzin_record_flag_b;
extern unsigned char g_feltzin_record_flag_c;
extern float g_feltzin_record_float_a;
extern float g_feltzin_record_float_b;
extern float g_feltzin_record_float_c;
extern float g_feltzin_record_float_d;
extern int g_feltzin_record_word;
extern int g_feltzin_menu_mode __attribute__((sda));
extern int g_feltzin_challenge_active __attribute__((sda));
extern int g_feltzin_needs_reset __attribute__((sda));
extern int g_feltzin_controller_moby __attribute__((sda));
extern int g_feltzin_record_a __attribute__((sda));
extern int g_feltzin_record_b __attribute__((sda));
extern int g_feltzin_menu_started __attribute__((sda));
extern void func_379F28(int a0);
extern void func_37D6E8(void);
extern void func_379F68(void);
extern void func_37B210(void);
extern void func_379F18(int a0);
extern int func_442860(void);
extern void func_445A98(void);
extern void func_328870(int a0);
typedef struct { int words[10]; } SpawnEntry;
extern SpawnEntry g_spawn_entry_table[];
extern int func_37AAC8(int a0);

/* Same reset, plus the shutdown of the two cached records. */
void feltzin_challenge_reset_free_records_pal(void)
{
    char *challenge;
    int one = 1;

    func_37B210();
    func_379F18(1);
    challenge = (char *)g_feltzin_challenge_state;
    *(int *)(challenge + 0x28) = 100;
    *(float *)(challenge + 0x30) = 8.0f;
    *(int *)(challenge + 0x10) = 0;
    *(int *)(challenge + 0xC) = 0;
    g_feltzin_challenge_active = 0;
    *(int *)(challenge + 0x14) = 0;
    *(int *)(challenge + 0x2C) = one;
    g_feltzin_menu_started = 0;
    func_379F28(0);
    if (func_442860() != 0) {
        *(int *)(challenge + 0x2C) = 0;
        *(unsigned char *)(g_feltzin_controller_moby + 0x20) = one;
    }
    func_37D6E8();
    func_379F68();
    func_445A98();
    if (g_feltzin_record_a != 0) {
        func_328870(g_feltzin_record_a);
        g_feltzin_record_a = 0;
    }
    if (g_feltzin_record_b != 0) {
        func_328870(g_feltzin_record_b);
        g_feltzin_record_b = 0;
    }
    g_ship_settings_byte_a = g_feltzin_record_flag_a;
    g_ship_settings_byte_b = g_feltzin_record_flag_b;
    g_ship_settings_byte_c = g_feltzin_record_flag_c;
    g_ship_settings_float_a = g_feltzin_record_float_b;
    g_ship_settings_float_b = g_feltzin_record_float_d;
    g_ship_settings_float_c = g_feltzin_record_float_a;
    g_ship_settings_float_d = g_feltzin_record_float_c;
    g_ship_settings_word = g_feltzin_record_word;
}

/* func_PAL_L05_00425518, the PAL copy of func_L05_0041FE98, with the shutdown test of func_PAL_L05_004253C8. */
void feltzin_challenge_shutdown_pal(void)
{
    char *challenge;
    int i;
    int one = 1;

    func_37B210();
    func_379F18(1);
    challenge = (char *)g_feltzin_challenge_state;
    g_feltzin_menu_mode = -2;
    *(int *)(challenge + 0x10) = 0;
    *(int *)(challenge + 0x28) = 100;
    *(int *)(challenge + 0xC) = 0;
    g_feltzin_needs_reset = one;
    g_feltzin_challenge_active = 0;
    *(int *)(challenge + 0x14) = 0;
    *(int *)(challenge + 0x2C) = one;
    i = func_37AAC8(6);
    g_feltzin_menu_started = 0;
    g_spawn_entry_table[i].words[5] = g_spawn_entry_table[i].words[4];
    func_37D6E8();
    func_379F68();
    func_445A98();
    *(float *)(challenge + 0x30) = 8.0f;
    func_379F28(0);
    if (func_442860() != 0) {
        *(int *)(challenge + 0x2C) = 0;
        *(unsigned char *)(g_feltzin_controller_moby + 0x20) = one;
    }
    if (g_feltzin_record_a != 0) {
        func_328870(g_feltzin_record_a);
        g_feltzin_record_a = 0;
    }
    if (g_feltzin_record_b != 0) {
        func_328870(g_feltzin_record_b);
        g_feltzin_record_b = 0;
    }
    g_ship_settings_byte_a = g_feltzin_record_flag_a;
    g_ship_settings_byte_b = g_feltzin_record_flag_b;
    g_ship_settings_byte_c = g_feltzin_record_flag_c;
    g_ship_settings_float_a = g_feltzin_record_float_b;
    g_ship_settings_float_b = g_feltzin_record_float_d;
    g_ship_settings_float_c = g_feltzin_record_float_a;
    g_ship_settings_float_d = g_feltzin_record_float_c;
    g_ship_settings_word = g_feltzin_record_word;
}
