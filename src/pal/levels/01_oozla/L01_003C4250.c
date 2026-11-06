#include "include_asm.h"

INCLUDE_ASM("asm/pal/levels", func_PAL_L01_003C4530);
#include "common.h"


/* func_PAL_L01_003C4768, the PAL copy of func_L01_003C08A0: the same C, without the func_0026FEB8
 * call, with 8.0f for 10.0f and 0.080000006f for 0.06666667f (the 50 Hz scale). */
extern char D_00189E20[];
extern void func_PAL_L01_002BEC60(int, int), func_PAL_L00_002D2668(int, int, float);
extern void func_0029FCC0(void *, int, void *);
extern void func_00282CF0(void *, void *, void *), func_002AC9F8(void *, float);
extern void func_00282CC0(void *, void *, void *), func_00282C88(void *);

void func_PAL_L01_003C4768(char *object)
{
    char *hero = D_00189E20;
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
    func_0029FCC0(object, 10, &joint_position);
    joint_position.z = joint_position.z - 1.0f;
    func_00282CF0(offset, &joint_position, hero + 0x80);
    func_002AC9F8(offset, 0.080000006f);
    func_00282CC0(hero + 0x80, hero + 0x80, offset);
    func_00282C88(hero + 0xF0);
    func_00282C88(hero + 0x110);
    func_00282C88(hero + 0x120);
    func_00282C88(hero + 0x130);
    *(unsigned char *)(hero + 0x149B) = 0;
    *(unsigned char *)(hero + 0x1496) = 0;
    *(int *)(hero + 0x1B8) = 0;
    *(int *)(hero + 0x18C0) = 0;
}

INCLUDE_ASM("asm/pal/levels", func_PAL_L01_003C4878);

