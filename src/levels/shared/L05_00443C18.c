#include "include_asm.h"
#include "names.h"

extern void func_3066A0(char *, char *, float);

extern void func_306630(char *, char *, char *);

/* Works out where the ship is aiming from its lean and turn, and stores that aim point in the driven moby. */
void ship_update_aim_point(char *obj, char *moby)
{
    char *state = *(char **)(moby + 0x68);
    char *obj_alias = obj;
    char *input = *(char **)(obj + 0x70) + 0x50;
    char blend[16];
    char scratch[16];

    *(float *)(state + 0x0) = (*(float *)(input + 0x68)
                            / (*(float *)(input + 0x78) * 0.017453294f))
                           * *(float *)(state + 0x244);
    *(float *)(state + 0x4) = (-*(float *)(input + 0x64)
                            / (*(float *)(input + 0x74) * 0.017453294f))
                           * *(float *)(state + 0x248);
    func_3066A0(blend, obj_alias, *(float *)(state + 0x240));
    func_306630(blend, obj_alias + 0x30, blend);
    func_3066A0(scratch, obj_alias + 0x10, *(float *)(state + 0x0));
    func_306630(blend, blend, scratch);
    func_3066A0(scratch, obj_alias + 0x20, *(float *)(state + 0x4));
    func_306630(state + 0x20, blend, scratch);
}
