#include "include_asm.h"
#include "names.h"
typedef int Q128 __attribute__((mode(TI)));

extern void func_0029FCC0(void *entity, int a, void *out);
extern void func_00282F20(void *, void *, float);
extern void func_L04_0030C4C0(void *, void *, void *, void *, void *, void *, int, int, int);
extern void func_L07_003F6528(char *);
extern char *func_L07_003F65E8(int);

/* Launches every member of the object's group away from it at a fixed speed. */
void func_L07_003F8CD0(char *moby)
{
    char *vars = *(char **)(moby + 0x68);
    float start[4];
    float velocity[4];
    float offset[4];
    char *member;

    TransformMobyJointToWorld(moby, 0, start);
    *(Q128 *)offset = 0;
    offset[2] = 5.0f;
    vec_scale_to_length(velocity, moby + 0xC0, 2.0f);
    for (;;) {
        member = PickRandomActiveGroupEntity(*(int *)(vars + 0x180));
        if (member == 0) break;
        StartSwingingTurret(member);
        BuildSpawnRecordFromBlocks(member, start, velocity, member + 0x10, offset, member + 0xF0, 0x5A, 0, 0);
    }
}
