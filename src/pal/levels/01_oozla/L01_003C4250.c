#include "include_asm.h"
#include "common.h"


/* func_PAL_L01_003C4768, the PAL copy of func_L01_003C08A0: the same C, without the func_0026FEB8
 * call, with 8.0f for 10.0f and 0.080000006f for 0.06666667f (the 50 Hz scale). */
extern char g_hero_state[];
extern void func_PAL_L01_002BEC60(int, int), func_PAL_L00_002D2668(int, int, float);
extern void moby_transform_joint_to_world(void *, int, void *);
extern void FastVecSub(void *, void *, void *), vec_clamp_length(void *, float);
extern void FastVecAdd(void *, void *, void *), vec_clear_128(void *);

void func_PAL_L01_003C4768(char *object)
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
        func_PAL_L01_002BEC60(0x6F, 1);
        func_PAL_L00_002D2668(10, 0, 8.0f);
        *(unsigned char *)(hero + 0x22B5) = saved_flag;
    }
    *(unsigned short *)(hero + 0x1F0) = 2;
    moby_transform_joint_to_world(object, 10, &joint_position);
    joint_position.z = joint_position.z - 1.0f;
    FastVecSub(offset, &joint_position, hero + 0x80);
    vec_clamp_length(offset, 0.080000006f);
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
