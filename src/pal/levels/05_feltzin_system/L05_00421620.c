#include "include_asm.h"


#include "common.h"
extern void func_306630(char *dst, char *src, char *src2);
extern float func_332B50(float a, float b);
extern float func_332C18(void);
extern void func_33B330(char *dst, float a, float b, float c);
extern char *func_379CA0(char *object);
extern void func_37AEC0(char *object, int flag);
extern void feltzin_enemy_init_position_fast(char *obj);
extern int g_feltzin_challenge_state[];
extern char *g_feltzin_enemy_table __attribute__((sda));

/* Sets up a new enemy: starts it at a random spot around its spawn point and resets its timers (faster movement). */
void feltzin_enemy_init_position_fast_pal(char *obj)
{
    char *state = *(char **)(obj + 0x68);
    char *table;
    float radius, angle_a, angle_b;

    *(unsigned char *)(obj + 0x20) = 1;
    *(unsigned short *)(obj + 0x34) = *(unsigned short *)(obj + 0x34) | 0x100;
    *(int *)(func_379CA0(obj) + 0x148) = 5;
    func_37AEC0(obj, 1);
    table = g_feltzin_enemy_table + g_feltzin_challenge_state[0] * 128;
    *(int *)(state + 0x268) = 0;
    *(float *)(state + 0x180) = 5.0f;
    *(float *)(obj + 0x2C) = 0.08f;
    radius = func_332B50(0.0f, *(float *)table);
    angle_a = func_332C18();
    angle_b = func_332C18();
    func_33B330(obj + 0x10, radius, angle_a, angle_b);
    func_306630(obj + 0x10, table + 0x30, obj + 0x10);
}


