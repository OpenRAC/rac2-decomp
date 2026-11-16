#include "include_asm.h"

#include "common.h"
extern void func_306630(char *dst, char *src, char *src2);
extern char *feltzin_helper_create(char *a0, int a1);
extern float func_332B50(float a, float b);
extern float func_332C18(void);
extern void func_33B330(char *dst, float a, float b, float c);
extern char *func_379CA0(char *object);
extern void func_37AEC0(char *object, int flag);
extern int g_feltzin_challenge_state[];
extern char *g_feltzin_enemy_table __attribute__((sda));

/* Sets up a new enemy: starts it at a random spot around its spawn point and creates its two helper objects when needed. */
void feltzin_enemy_init_with_helpers_pal(char *obj)
{
    char *state = *(char **)(obj + 0x68);
    char *effect_rec;
    char *table;
    float radius, angle_a, angle_b;

    *(unsigned char *)(obj + 0x20) = 1;
    *(unsigned short *)(obj + 0x34) = *(unsigned short *)(obj + 0x34) | 0x100;
    effect_rec = func_379CA0(obj);
    *(int *)(effect_rec + 0x148) = 5;
    func_37AEC0(obj, 1);
    table = g_feltzin_enemy_table + g_feltzin_challenge_state[0] * 128;
    *(int *)(state + 0x274) = -1;
    *(float *)(state + 0x180) = 5.0f;
    *(int *)(state + 0x268) = 0;
    radius = func_332B50(0.0f, *(float *)table);
    angle_a = func_332C18();
    angle_b = func_332C18();
    func_33B330(obj + 0x10, radius, angle_a, angle_b);
    func_306630(obj + 0x10, table + 0x30, obj + 0x10);
    if (*(int *)(effect_rec + 0x110) == 1) {
        *(int *)(state + 0x26C) = feltzin_helper_create(obj, 0);
        *(int *)(state + 0x270) = feltzin_helper_create(obj, 1);
    } else {
        *(int *)(state + 0x26C) = 0;
        *(int *)(state + 0x270) = 0;
    }
    *(float *)(obj + 0x2C) = 0.02f;
}

