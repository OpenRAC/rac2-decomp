#include "include_asm.h"

#include "common.h"
extern int func_332AB8(int kind);
extern void func_3719A8(int a0, int a1, char *object, int a3);
extern char *func_379CA0(char *object);
extern void func_379FA0(char *object, int a1, int a2, int a3, float f0, float f1, float f2,
                        float f3, int a8, int a9, int a10);

/* Spawns the object's effect after three guards, then runs the follow-up by kind. */
void feltzin_enemy_fire_shot_pal(char *object)
{
    char *state = *(char **)(object + 0x68);
    char *effect_rec;

    effect_rec = func_379CA0(object);
    if (effect_rec == 0)
        return;
    if (*(int *)(effect_rec + 0x120) == 0)
        return;
    if (*(int *)(state + 0x268) != 0)
        return;
    func_379FA0(object, 0x60408020, 1, 0, 0.75f, 5.0f, 1.0f, 1.0f, 0, -1, 0);
    if (func_332AB8(3) != 0)
        func_3719A8(0, 0, object, 0xF76);
    *(int *)(state + 0x268) = 0xC;
}


