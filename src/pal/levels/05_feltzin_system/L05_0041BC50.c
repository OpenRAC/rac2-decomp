#include "include_asm.h"

#include "common.h"
extern void func_306630(char *dst, char *src, char *src2);
extern void func_306660(char *dst, char *src, char *src2);
extern char *func_379CA0(char *object);
extern int func_2F6C50(char *a0, char *a1, int a2, char *a3, int a4);
extern void func_329960(char *object, int a1, char *out);
extern void func_37AC80(float value);
extern char g_collision_l05_result[];
extern char g_hero_l05_state[];

/* Builds the sub-record's three planes and blends them onto the object's transform. */

/* Blends the sub-record into the object's transform once three guards clear. */
void feltzin_helper_check_hit_attach_pal(char *object, char *arg1)
{
    char *vars = *(char **)(object + 0x68);
    char buf[16];
    char buf2[16];
    char *target_rec;
    char *hit_result;
    int hit_object;

    target_rec = func_379CA0(*(char **)(vars + 0x50));
    func_329960(object, 0, buf);
    func_306660(buf2, buf, object + 0x10);
    if (func_2F6C50(arg1, buf, 0, object, 0) == 0)
        return;
    hit_result = g_collision_l05_result;
    hit_object = *(int *)(hit_result + 0x18);
    if (hit_object == 0)
        return;
    if (hit_object != *(int *)(target_rec + 0x120))
        return;
    func_306630(object + 0x10, buf2, hit_result + 0x20);
    func_37AC80(2.0f);
    {
        char *hero_state = g_hero_l05_state;

        *(float *)(hero_state + 0x160) = 0.05f;
        *(int *)(hero_state + 0x168) = 0x19;
        *(int *)(hero_state + 0x16C) = 0;
    }
    *(unsigned char *)(object + 0x20) = 4;
}

