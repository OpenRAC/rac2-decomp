#include "common.h"

extern char D_00189E20[], D_L01_001AFF00[];
extern int D_L01_001B2088[] __attribute__((sda));
extern void func_L01_002BEB90(int, int), func_L00_002D2168(int, int, float);
extern void func_0026FEB8(const char *, ...);
extern void func_0029FCC0(void *, int, void *);
extern void func_00282CF0(void *, void *, void *), func_002AC9F8(void *, float);
extern void func_00282CC0(void *, void *, void *), func_00282C88(void *);

/* Holds the player in the monster's grip, pulling him to the monster's hand and stopping him moving. */
void func_L01_003C08A0(char *moby)
{
    char *hero = gHeroState;
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
        STUB_printf(D_L01_001AFF00, D_L01_001B2088[0]);
        *(unsigned char *)(hero + 0x22B5) = saved_flag;
    }
    *(unsigned short *)(hero + 0x1F0) = 2;
    TransformMobyJointToWorld(moby, 10, &joint_position);
    joint_position.z = joint_position.z - 1.0f;
    FastVecSub(offset, &joint_position, hero + 0x80);
    ClampVectorLength(offset, 0.06666667f);
    FastVecAdd(hero + 0x80, hero + 0x80, offset);
    ClearVector128(hero + 0xF0);
    ClearVector128(hero + 0x110);
    ClearVector128(hero + 0x120);
    ClearVector128(hero + 0x130);
    *(unsigned char *)(hero + 0x149B) = 0;
    *(unsigned char *)(hero + 0x1496) = 0;
    *(int *)(hero + 0x1B8) = 0;
    *(int *)(hero + 0x18C0) = 0;
}
