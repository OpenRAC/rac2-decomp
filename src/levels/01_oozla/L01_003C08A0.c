#include "common.h"

extern char g_hero_state[], g_str_swamp_monster_hold_debug[];
extern int g_oozla_intro_stage[] __attribute__((sda));
extern void set_hero_animation(int, int, float);
extern s32 SetHeroMoveState(int, int);
extern void STUB_printf(const char *, ...);
extern void moby_transform_joint_to_world(void *, int, void *);
extern void FastVecSub(void *, void *, void *), vec_clamp_length(void *, float);
extern void FastVecAdd(void *, void *, void *), vec_clear_128(void *);

/* Holds the player in the monster's grip, pulling him to the monster's hand and stopping him moving. */
void swamp_monster_hold_hero(char *moby)
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
        *(int *)(moby + 0x98) = 0;
        SetHeroMoveState(0x6F, 1);
        set_hero_animation(10, 0, 10.0f);
        STUB_printf(g_str_swamp_monster_hold_debug, g_oozla_intro_stage[0]);
        *(unsigned char *)(hero + 0x22B5) = saved_flag;
    }
    *(unsigned short *)(hero + 0x1F0) = 2;
    moby_transform_joint_to_world(moby, 10, &joint_position);
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
