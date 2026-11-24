#include "names.h"
/* func_US2_L01_003C1CA8, the USA v2.00 copy of func_L01_003C08A0: the same C, without the debug print. */
#include "common.h"

extern char g_hero_state[];
extern int SetHeroMoveState_us2(int, int);
extern void set_hero_animation(int, int, float);
extern void moby_transform_joint_to_world(void *, int, void *);
extern void FastVecSub(void *, void *, void *), vec_clamp_length(void *, float);
extern void FastVecAdd(void *, void *, void *), vec_clear_128(void *);

/* Drags the hero along with the swamp monster's joint while it holds him in its grip. */
void swamp_monster_hold_hero_us2(char *object)
{
    char *hero = g_hero_state;
    struct L01_003C08A0_S {
        float x;
        float y;
        float z;
    } joint_position;
    float offset[4];
    int saved_flag;

    if (*(int *)(hero + 0x2294) != 0x6F) {
        saved_flag = *(unsigned char *)(hero + 0x22B5) != 0;
        *(int *)(object + 0x98) = 0;
        SetHeroMoveState_us2(0x6F, 1);
        set_hero_animation(10, 0, 10.0f);
        *(unsigned char *)(hero + 0x22B5) = saved_flag;
    }
    *(unsigned short *)(hero + 0x1F0) = 2;
    moby_transform_joint_to_world(object, 10, &joint_position);
    joint_position.z = joint_position.z - 1.0f;
    FastVecSub(offset, &joint_position, hero + 0x80);
    vec_clamp_length(offset, 0.06666667f);
    FastVecAdd(hero + 0x80, hero + 0x80, offset);
    vec_clear_128(hero + 0xF0);
    vec_clear_128(hero + 0x110);
    vec_clear_128(hero + 0x120);
    vec_clear_128(hero + 0x130);
    *(unsigned char *)(hero + 0x149B) = 0;
    *(unsigned char *)(hero + 0x1496) = 0;
    *(int *)(hero + 0x1B8) = 0;
    *(int *)(hero + 0x18C0) = 0;
}
