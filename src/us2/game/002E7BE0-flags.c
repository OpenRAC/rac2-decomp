#include "include_asm.h"

#include "common.h"
typedef struct { char pad00[0x20]; short unk20; short unk22; } Sel52C00;
extern Sel52C00 g_hero_moby_default;
extern float ref_L00_00360ED0_00 MACRO_ADDR;
extern int ref_L00_00360ED0_01 MACRO_ADDR;
extern int ref_L00_00360ED0_02 __attribute__((sda));
typedef struct { char pad00[0x0C]; int unk0C; int unk10; } World2E71B8;
typedef struct {
    char pad00[0x34];
    int unk34;
    char pad38[0x34];
    int unk6C;
    int unk70;
} State2E71B8;
extern World2E71B8 ref_L00_00360ED0_03;
extern State2E71B8 ref_L00_00360ED0_04;
extern void gfx_select_packet_buffer_setup(void);
extern void func_US2_002E7BE0(int);

void func_US2_002E8010(void)
{
    int base;

    ref_L00_00360ED0_00 = 1.0f;
    g_hero_moby_default.unk20 = 0;
    g_hero_moby_default.unk22 = -1;
    gfx_select_packet_buffer_setup();

    base = ref_L00_00360ED0_01 - 0x60000;
    ref_L00_00360ED0_04.unk6C = ref_L00_00360ED0_03.unk0C + base;
    ref_L00_00360ED0_04.unk70 = ref_L00_00360ED0_03.unk10 + base;
    ref_L00_00360ED0_02 = base;
    func_US2_002E7BE0(3);
    ref_L00_00360ED0_04.unk34 = 1;
}
