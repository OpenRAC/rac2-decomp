#include "include_asm.h"

#include "common.h"
extern int math_fast_float_d(void *);
extern void func_PAL_002AC3C0(void *, unsigned char *);
extern void func_PAL_L03_003C8588(unsigned char *);
extern void moby_update_eased_node(void *, void *, int, float, float);
extern int route_get_node_value(unsigned int, int);
extern unsigned char D_001A7A43;

void func_PAL_L03_003C8478(unsigned char *object)
{
    unsigned char *state = *(unsigned char **)(object + 0x68);
    func_PAL_002AC3C0(object, state + 0x50);
    if (*(unsigned short *)(object + 0x96) < 0xFFFF)
        ++*(unsigned short *)(object + 0x96);
    math_fast_float_d(state + 0x364);
    func_PAL_L03_003C8588(object);
    if (D_001A7A43 != 0 && object[0x20] != 1)
        *(float *)(state + 0x2B0) = 1.75f;
    moby_update_eased_node(object, state + 0x240, 1, 0.0432f, 0.43200004f);
    moby_update_eased_node(object, state + 0x2C0, 0, 0.0432f, 0.43200004f);
    if (object[0x95] != 7 && object[0x20] != 1)
        *(int *)(state + 0x14C) = route_get_node_value(*(unsigned int *)(state + 0x220), *(int *)(state + 0x368));
}
