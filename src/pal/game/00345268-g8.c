#include "include_asm.h"
#include "names.h"

typedef unsigned char u8;
extern int menu_list_get_count(u8 *);
extern void object_set_flag_value(u8 *, int);
extern void object_set_first_float4(void *, float, float, float, float);
extern float D_001AE214;
extern float D_001AE210 __attribute__((sda));

void func_PAL_00345640(u8 *a0) {
    if (menu_list_get_count(a0 + 0x2C8) == 0) {
        object_set_flag_value(a0 + 0x208, 0);
    } else {
        int *v = *(int **)(a0 + 0x2B8);
        object_set_first_float4(a0 + 0x208, D_001AE210 + *(float *)v,
                      D_001AE214 + *(float *)((u8 *)v + 4), 0.0f, 0.0f);
    }
}
