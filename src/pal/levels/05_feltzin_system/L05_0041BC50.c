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
    char *sub = *(char **)(object + 0x68);
    char buf[16];
    char buf2[16];
    char *r;
    char *base;
    int value;

    r = func_379CA0(*(char **)(sub + 0x50));
    func_329960(object, 0, buf);
    func_306660(buf2, buf, object + 0x10);
    if (func_2F6C50(arg1, buf, 0, object, 0) == 0)
        return;
    base = g_collision_l05_result;
    value = *(int *)(base + 0x18);
    if (value == 0)
        return;
    if (value != *(int *)(r + 0x120))
        return;
    func_306630(object + 0x10, buf2, base + 0x20);
    func_37AC80(2.0f);
    {
        char *state = g_hero_l05_state;

        *(float *)(state + 0x160) = 0.05f;
        *(int *)(state + 0x168) = 0x19;
        *(int *)(state + 0x16C) = 0;
    }
    *(unsigned char *)(object + 0x20) = 4;
}

