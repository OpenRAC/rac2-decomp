#include "include_asm.h"
#include "common.h"

/* Built with -G8: the three small-data globals are reached through $gp in retail,
   the rest of the file's symbols are addressed absolutely. */

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

extern unsigned char g_level_l05_byte_flag __attribute__((sda));

extern void func_379F28(int a0);

extern void func_37D6E8(void);

extern void func_379F68(void);

extern void func_37B210(void);

extern void func_379F18(int a0);

extern int func_442860(void);

extern void func_445A98(void);

extern void func_328870(int a0);

extern int g_feltzin_challenge_data __attribute__((sda));

extern char *part_find_owned_effect_slot(char *a0, char *a1, int a2);

extern void gfx_update_color_fade(char *a0, char *a1);

extern void gfx_start_color_fade(char *a0, char *a1);

extern int snd_play_from_class_bank(int a0, int a1, char *a2, int a3);

extern int math_random_int_below(int kind);

extern float math_random_float_range(float a, float b);

extern char *func_L05_00398F18(void *a0, int a1, int a2, int a3, int a4, int a5, int a6, int a7,
                              float f8);

extern char *part_spawn_shockwave_burst(void *a0, void *a1, int a2, int a3, int a4, int a5, int a6, int a7,
                              int a8, int a9, int a10, float f12);

extern void func_L05_00421908(char *a0, int a1, int a2);

extern int moby_is_in_use(char *a0);

extern void moby_release_from_group(char *a0);

extern void moby_reset_action_state(char *a0);

/* Same reset, plus the shutdown of the two cached records. */
void feltzin_challenge_reset_free_records(void)
{
    char *p;
    int one = 1;

    func_37B210();
    func_379F18(1);
    p = (char *)g_feltzin_challenge_state;
    *(int *)(p + 0x28) = 100;
    *(float *)(p + 0x30) = 8.0f;
    *(int *)(p + 0x10) = 0;
    *(int *)(p + 0xC) = 0;
    g_feltzin_challenge_active = 0;
    *(int *)(p + 0x14) = 0;
    *(int *)(p + 0x2C) = one;
    g_feltzin_menu_started = 0;
    func_379F28(0);
    if (func_442860() != 0) {
        *(int *)(p + 0x2C) = 0;
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

/* The moby's death timer: it ticks the stored time down and, once it reaches zero,
   fires the object's effect and takes the moby down, which it reports. */
int feltzin_target_damage(char *obj, int flag)
{
    char *attached;
    float *health;
    char *hit_source;
    char *vars;
    float burst_pos[3];
    int ret = 0;

    hit_source = part_find_owned_effect_slot(obj, (char *)0x230000, 0);
    *(unsigned char *)(obj + 0xA8) = 0xFF;
    vars = *(char **)(obj + 0x68);
    attached = *(char **)(vars + 0x10);
    health = *(float **)(vars + 0x0);
    if (attached != 0) {
        gfx_update_color_fade(obj, attached);
    }
    if (hit_source != 0) {
        if (attached != 0) {
            *(unsigned char *)(attached + 7) = 0xFF;
            gfx_start_color_fade(obj, attached);
        }
        *health = *health - *(float *)(hit_source + 0x2C);
        if (*(short *)(obj + 0xAA) != 0xB73) {
            snd_play_from_class_bank(0xD, 0, obj, 0xFBF);
            if (math_random_int_below(3) == 0) {
                if (*(short *)(obj + 0xAA) == 0x10F5) {
                    snd_play_from_class_bank(1, 0, obj, 0x10F5);
                } else {
                    snd_play_from_class_bank(0xB, 0, obj, 0xFBF);
                }
            }
        }
        if (*health <= 0.0f) {
            *health = 0.0f;
            if (*(short *)(obj + 0xAA) == 0x10F5) {
                func_L05_00398F18(obj + 0x10, 0, 0x19, 0, 0, 0x1E, 0, 1, 0.8f);
            } else if (*(short *)(obj + 0xAA) == 0x111A) {
                func_L05_00398F18(obj + 0x10, 0, 0xF, 0, 0, 0x1E, 0, 0, 2.0f);
                burst_pos[0] = *(float *)(obj + 0x10) + math_random_float_range(1.5f, -1.5f);
                burst_pos[1] = *(float *)(obj + 0x14) + math_random_float_range(1.5f, -1.5f);
                burst_pos[2] = *(float *)(obj + 0x18) + math_random_float_range(1.5f, -1.5f);
                func_L05_00398F18(burst_pos, 0, 0xF, 0, 0, 0x1E, 0, 0, 2.0f);
                burst_pos[0] = *(float *)(obj + 0x10) + math_random_float_range(1.5f, -1.5f);
                burst_pos[1] = *(float *)(obj + 0x14) + math_random_float_range(1.5f, -1.5f);
                burst_pos[2] = *(float *)(obj + 0x18) + math_random_float_range(1.5f, -1.5f);
                func_L05_00398F18(burst_pos, 0, 0xF, 0, 0, 0x1E, 0, 0, 2.0f);
            } else {
                part_spawn_shockwave_burst(obj + 0x10, 0, 0x32, 0x1E, 0x1E, 0x1E, 0x28, 1, 1, 0, 0, 0.75f);
            }
            if (g_feltzin_challenge_data == 0) {
                func_L05_00421908(obj, 1, 5);
            } else {
                func_L05_00421908(obj, 0, 5);
            }
            if (moby_is_in_use(obj)) {
                moby_release_from_group(obj);
            }
            if (flag == 0) {
                moby_reset_action_state(obj);
            }
            ret = 1;
        }
    }
    return ret;
}

/* Resets the shared spawn table and copies the mode record into the live one. */
void feltzin_challenge_reset(void)
{
    char *p = (char *)g_feltzin_challenge_state;

    g_feltzin_challenge_active = 0;
    g_feltzin_menu_mode = -2;
    g_feltzin_needs_reset = 1;
    *(int *)(p + 0x2C) = 1;
    *(int *)(p + 0x28) = 100;
    *(int *)(p + 0x14) = 0;
    *(float *)(p + 0x30) = 8.0f;
    func_379F28(0);
    func_37D6E8();
    func_379F68();
    g_ship_settings_byte_a = g_feltzin_record_flag_a;
    g_ship_settings_byte_b = g_feltzin_record_flag_b;
    g_ship_settings_byte_c = g_feltzin_record_flag_c;
    g_ship_settings_float_a = g_feltzin_record_float_b;
    g_ship_settings_float_b = g_feltzin_record_float_d;
    g_ship_settings_float_c = g_feltzin_record_float_a;
    g_ship_settings_float_d = g_feltzin_record_float_c;
    g_ship_settings_word = g_feltzin_record_word;
}

typedef struct { int words[10]; } SpawnEntry;
extern SpawnEntry g_spawn_entry_table[];
extern int func_37AAC8(int a0);

/* Resets the shared spawn table, frees the two cached records and copies the mode record into the live one. */
void feltzin_challenge_shutdown(void)
{
    char *p;
    int i;

    func_37B210();
    func_379F18(1);
    p = (char *)g_feltzin_challenge_state;
    g_feltzin_menu_mode = -2;
    *(int *)(p + 0x10) = 0;
    *(int *)(p + 0xC) = 0;
    g_feltzin_needs_reset = 1;
    *(int *)(p + 0x2C) = 1;
    *(int *)(p + 0x28) = 100;
    g_feltzin_challenge_active = 0;
    *(int *)(p + 0x14) = 0;
    i = func_37AAC8(6);
    g_feltzin_menu_started = 0;
    g_spawn_entry_table[i].words[5] = g_spawn_entry_table[i].words[4];
    func_37D6E8();
    func_379F68();
    func_445A98();
    *(float *)(p + 0x30) = 8.0f;
    func_379F28(0);
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
