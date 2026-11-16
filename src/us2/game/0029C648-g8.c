#include "include_asm.h"
#include "names.h"

extern char *g_resident_data_base;
extern int func_US2_00349728(void *, int);

int func_US2_0029CFA0(int value) {
    if (g_resident_data_base != 0)
        return func_US2_00349728(g_resident_data_base + 0x39160, value);
    return 0;
}

extern int func_US2_00347B88(void *, int);

int func_US2_0029D040(int value) {
    if (g_resident_data_base != 0)
        return func_US2_00347B88(g_resident_data_base + 0x39620, value);
    return 0;
}

/* func_US2_0029CC48, the v2.00 copy of func_L00_0030CF60: the same call, with the camera's
   projection scale set around it, as the tail of func_0029BF08 does in v1.01. */
typedef struct { char pad[0xB0]; float scale; } CamCc;
extern CamCc ref_L00_0030CFE0_01;
extern void UpdateViewContext(void);
extern void hud_update_subobject_alt_us2(void *);

void func_US2_0029CC48(void)
{
    if (g_resident_data_base != 0) {
        float saved = ref_L00_0030CFE0_01.scale;

        ref_L00_0030CFE0_01.scale = 0.62f;
        UpdateViewContext();
        hud_update_subobject_alt_us2(g_resident_data_base + 0x36F28);
        ref_L00_0030CFE0_01.scale = saved;
        UpdateViewContext();
    }
}
