#include "include_asm.h"
#include "common.h"

/* Built with -G8: the three small-data globals are reached through $gp in retail,
   the rest of the file's symbols are addressed absolutely. */

extern int D_L05_00221D10[];

extern unsigned char D_L05_001B2000;

extern unsigned char D_L05_001B2001;

extern unsigned char D_L05_001B2002;

extern float D_L05_001B2004;

extern float D_L05_001B2008;

extern float D_L05_001B200C;

extern float D_L05_001B2010;

extern int D_L05_001B2014;

extern unsigned char D_L05_001B3558;

extern unsigned char D_L05_001B3559;

extern unsigned char D_L05_001B355A;

extern float D_L05_001B355C;

extern float D_L05_001B3560;

extern float D_L05_001B3564;

extern float D_L05_001B3568;

extern int D_L05_001B356C;

extern int D_L05_001B1360 __attribute__((sda));

extern int D_L05_001B1364 __attribute__((sda));

extern int D_L05_001B13E8 __attribute__((sda));

extern int D_L05_001B13B0 __attribute__((sda));

extern int D_L05_001B13B4 __attribute__((sda));

extern int D_L05_001B13B8 __attribute__((sda));

extern int D_L05_001B13F0 __attribute__((sda));

extern unsigned char D_L05_001B4568 __attribute__((sda));

extern void func_379F28(int a0);

extern void func_37D6E8(void);

extern void func_379F68(void);

extern void func_37B210(void);

extern void func_379F18(int a0);

extern int func_442860(void);

extern void func_445A98(void);

extern void func_328870(int a0);

extern int D_L05_001B1350 __attribute__((sda));

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
    p = (char *)D_L05_00221D10;
    *(int *)(p + 0x28) = 100;
    *(float *)(p + 0x30) = 8.0f;
    *(int *)(p + 0x10) = 0;
    *(int *)(p + 0xC) = 0;
    D_L05_001B1364 = 0;
    *(int *)(p + 0x14) = 0;
    *(int *)(p + 0x2C) = one;
    D_L05_001B13F0 = 0;
    func_379F28(0);
    if (func_442860() != 0) {
        *(int *)(p + 0x2C) = 0;
        *(unsigned char *)(D_L05_001B13B0 + 0x20) = one;
    }
    func_37D6E8();
    func_379F68();
    func_445A98();
    if (D_L05_001B13B4 != 0) {
        func_328870(D_L05_001B13B4);
        D_L05_001B13B4 = 0;
    }
    if (D_L05_001B13B8 != 0) {
        func_328870(D_L05_001B13B8);
        D_L05_001B13B8 = 0;
    }
    D_L05_001B2000 = D_L05_001B3558;
    D_L05_001B2001 = D_L05_001B3559;
    D_L05_001B2002 = D_L05_001B355A;
    D_L05_001B2008 = D_L05_001B3560;
    D_L05_001B2010 = D_L05_001B3568;
    D_L05_001B2004 = D_L05_001B355C;
    D_L05_001B200C = D_L05_001B3564;
    D_L05_001B2014 = D_L05_001B356C;
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
            if (D_L05_001B1350 == 0) {
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
    char *p = (char *)D_L05_00221D10;

    D_L05_001B1364 = 0;
    D_L05_001B1360 = -2;
    D_L05_001B13E8 = 1;
    *(int *)(p + 0x2C) = 1;
    *(int *)(p + 0x28) = 100;
    *(int *)(p + 0x14) = 0;
    *(float *)(p + 0x30) = 8.0f;
    func_379F28(0);
    func_37D6E8();
    func_379F68();
    D_L05_001B2000 = D_L05_001B3558;
    D_L05_001B2001 = D_L05_001B3559;
    D_L05_001B2002 = D_L05_001B355A;
    D_L05_001B2008 = D_L05_001B3560;
    D_L05_001B2010 = D_L05_001B3568;
    D_L05_001B2004 = D_L05_001B355C;
    D_L05_001B200C = D_L05_001B3564;
    D_L05_001B2014 = D_L05_001B356C;
}

typedef struct { int words[10]; } SpawnEntry;
extern SpawnEntry D_L05_002A1800[];
extern int func_37AAC8(int a0);

/* Resets the shared spawn table, frees the two cached records and copies the mode record into the live one. */
void feltzin_challenge_shutdown(void)
{
    char *p;
    int i;

    func_37B210();
    func_379F18(1);
    p = (char *)D_L05_00221D10;
    D_L05_001B1360 = -2;
    *(int *)(p + 0x10) = 0;
    *(int *)(p + 0xC) = 0;
    D_L05_001B13E8 = 1;
    *(int *)(p + 0x2C) = 1;
    *(int *)(p + 0x28) = 100;
    D_L05_001B1364 = 0;
    *(int *)(p + 0x14) = 0;
    i = func_37AAC8(6);
    D_L05_001B13F0 = 0;
    D_L05_002A1800[i].words[5] = D_L05_002A1800[i].words[4];
    func_37D6E8();
    func_379F68();
    func_445A98();
    *(float *)(p + 0x30) = 8.0f;
    func_379F28(0);
    if (D_L05_001B13B4 != 0) {
        func_328870(D_L05_001B13B4);
        D_L05_001B13B4 = 0;
    }
    if (D_L05_001B13B8 != 0) {
        func_328870(D_L05_001B13B8);
        D_L05_001B13B8 = 0;
    }
    D_L05_001B2000 = D_L05_001B3558;
    D_L05_001B2001 = D_L05_001B3559;
    D_L05_001B2002 = D_L05_001B355A;
    D_L05_001B2008 = D_L05_001B3560;
    D_L05_001B2010 = D_L05_001B3568;
    D_L05_001B2004 = D_L05_001B355C;
    D_L05_001B200C = D_L05_001B3564;
    D_L05_001B2014 = D_L05_001B356C;
}
