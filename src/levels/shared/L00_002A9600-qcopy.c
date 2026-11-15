#include "include_asm.h"
#include "names.h"

/* func_L00_002A9600 in its own unit for the grouped lq/sq profile. Its first two
   callees differ by level (ref_ names). */

typedef int TI128 __attribute__((mode(TI)));

typedef struct {
    char pad000[0x80];
    TI128 position;
    TI128 unk90;
    char padA0[0x150];
    short unk1F0;
    char pad1F2[0x5E];
    float unk250;
    float unk254;
    char pad258[0xC];
    float unk264;
    char pad268[0x2028];
    unsigned char *moby;
    char pad2294[0x20];
    unsigned char unk22B4;
    unsigned char unk22B5;
} HeroView_L00_002A9600;

extern char g_hero_state[];
extern void ref_L00_002A9600_00(void);
extern void ref_L00_002A9600_01(void);
extern void hero_set_objects_flag_bit(void);
extern void mem_copy_aligned(void *, void *, int);
extern void func_002A0F48(void *);
extern void hero_apply_mode_transform_reversed(void *, void *, float);
extern void vec_store_transformed_entry(void *, int, void *, float, float);

/* Places the hero's moby at the hero and, when it is standing on something,
   updates its two foot contacts. */
void hero_update_moby_from_hero(void)
{
    float footPos[4] __attribute__((aligned(16)));
    float footHeight;
    unsigned char *mobyPtr;

    if (((HeroView_L00_002A9600 *)g_hero_state)->unk22B5 != 0)
        ref_L00_002A9600_00();
    else
        ref_L00_002A9600_01();
    if (((HeroView_L00_002A9600 *)g_hero_state)->unk22B4 != 4)
        hero_set_objects_flag_bit();
    ((HeroView_L00_002A9600 *)g_hero_state)->moby[0xA8] = 0xFF;
    mobyPtr = ((HeroView_L00_002A9600 *)g_hero_state)->moby;
    *(TI128 *)(mobyPtr + 0x10) = ((HeroView_L00_002A9600 *)g_hero_state)->position;
    *(TI128 *)(mobyPtr + 0xF0) = ((HeroView_L00_002A9600 *)g_hero_state)->unk90;
    mem_copy_aligned(mobyPtr + 0xC0, g_hero_state, 0x30);
    func_002A0F48(((HeroView_L00_002A9600 *)g_hero_state)->moby);
    if (((HeroView_L00_002A9600 *)g_hero_state)->unk1F0 != 0 || *(int *)(((HeroView_L00_002A9600 *)g_hero_state)->moby + 0x98) == 0)
        return;
    *(TI128 *)footPos = ((HeroView_L00_002A9600 *)g_hero_state)->position;
    hero_apply_mode_transform_reversed(footPos, footPos, ((HeroView_L00_002A9600 *)g_hero_state)->unk254);
    vec_store_transformed_entry(((HeroView_L00_002A9600 *)g_hero_state)->moby, 0, footPos, ((HeroView_L00_002A9600 *)g_hero_state)->unk264, ((HeroView_L00_002A9600 *)g_hero_state)->unk250 - ((HeroView_L00_002A9600 *)g_hero_state)->unk254);
    footHeight = ((HeroView_L00_002A9600 *)g_hero_state)->unk264 + 0.05f;
    *(TI128 *)footPos = ((HeroView_L00_002A9600 *)g_hero_state)->position;
    hero_apply_mode_transform_reversed(footPos, footPos, footHeight);
    vec_store_transformed_entry(((HeroView_L00_002A9600 *)g_hero_state)->moby, 1, footPos, ((HeroView_L00_002A9600 *)g_hero_state)->unk264, ((HeroView_L00_002A9600 *)g_hero_state)->unk250 - footHeight);
}
